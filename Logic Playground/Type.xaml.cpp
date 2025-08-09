#include "pch.h"
#include "Type.xaml.h"
#if __has_include("Type.g.cpp")
#include "Type.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	Type::Type(UIElement CR _position, MainPageP CR _page_position) :TypeT(), position(_position), page_position(_page_position)
	{
	}

	void Type::Self(TypeP CR _self)
	{
		self = _self;
	}

	MainPageP Type::PagePosition() const
	{
		return page_position.get();
	}

	TypeCategory Type::Category() const
	{
		return category;
	}

	hstring Type::Label() const
	{
		return label;
	}

	TypeP Type::Left() const
	{
		return left;
	}

	TypeP Type::Right() const
	{
		return right;
	}

	IVector<TypeP> Type::Sames() const
	{
		return sames;
	}

	void Type::ChainCheck()
	{
		chain_click = true;
		Child().IsChecked(true);
	}

	void Type::ChainUncheck()
	{
		chain_click = true;
		Child().IsChecked(false);
	}

	void Type::Display() const
	{
		page_position.get().Display(position.get());
	}

	void Type::InitAsBool()
	{
		category = TypeCategory::Bool;
		Child().Content(BoldItalicCode(label = L"bool"));
	}

	void Type::InitAsParameter(param::hstring CR _label)
	{
		category = TypeCategory::Parameter;
		Child().Content(LightItalicCode(label = _label));
		(sames = single_threaded_vector<TypeP>()).Append(left = self.get());
	}

	void Type::InitAsParameter2(TypeP CR _declaration)
	{
		category = TypeCategory::Parameter;
		Child().Content(LightItalicCode(label = (left = _declaration).Label()));
		(sames = left.Sames()).Append(self.get());
	}

	void Type::InitAsFunction(TypeP CR _left, TypeP CR _right)
	{
		category = TypeCategory::Function;
		const TextBlock content = RegularCode(label = L"~");
		content.Foreground(ThemeBlueAqua);
		Child().Content(content);
		left = _left, right = _right;
	}

	void Type::InitAsTemplate(TypeP CR _left, TypeP CR _right)
	{
		category = TypeCategory::Template;
		const TextBlock content = RegularCode(label = L"`");
		content.Foreground(ThemeRedPurple);
		Child().Content(content);
		left = _left, right = _right;
	}

	void Type::InitAsAlias(TypeP CR _definition, param::hstring CR _label)
	{
		category = TypeCategory::Alias;
		Child().Content(ItalicCode(label = _label));
		right = _definition;
		(sames = single_threaded_vector<TypeP>()).Append(left = self.get());
	}

	void Type::InitAsAlias2(TypeP CR _declaration)
	{
		category = TypeCategory::Alias;
		Child().Content(ItalicCode(label = (left = _declaration).Label()));
		right = left.Right();
		(sames = left.Sames()).Append(self.get());
	}

	IVectorView<UIElement> Type::Generate(TypeP CR type)
	{
		return [](this auto&& generate, TypeP CR current, bool CR bracket = false)->IVectorView<UIElement>
			{
				const IVector result = single_threaded_vector<UIElement>();
				if (const TypeCategory cat = current.Category(); cat == TypeCategory::Function || cat == TypeCategory::Template)
					if (bracket)
					{
						const BracketP lb, rb;
						BracketP::Link(lb, rb);
						result.Append(lb);
						for (UIElement CR item : generate(current.Left(), true))
							result.Append(item);
						result.Append(current);
						for (UIElement CR item : generate(current.Right()))
							result.Append(item);
						result.Append(rb);
					}
					else
					{
						for (UIElement CR item : generate(current.Left(), true))
							result.Append(item);
						result.Append(current);
						for (UIElement CR item : generate(current.Right()))
							result.Append(item);
					}
				else
					result.Append(current);
				return result.GetView();
			}(type);
	}

	hstring Type::GenerateText(TypeP CR type)
	{
		return [](this auto&& generate_text, TypeP CR current, bool CR bracket = false)->hstring
			{
				if (const TypeCategory cat = current.Category(); cat == TypeCategory::Function || cat == TypeCategory::Template)
				{
					if (bracket)
						return hstring(L"(") + generate_text(current.Left(), true) + current.Label() + generate_text(current.Right()) + L')';
					return generate_text(current.Left(), true) + current.Label() + generate_text(current.Right());
				}
				return current.Label();
			}(type);
	}

	bool Type::Equal(TypeP CR x, TypeP CR y)
	{
		unordered_map<TypeP, unsigned> XCode, YCode;
		return [&XCode, &YCode](this auto&& equal, TypeP x, TypeP y, unsigned code = 1)
			{
				TypeCategory x_cat;
				while ((x_cat = x.Category()) == TypeCategory::Alias)
					x = x.Right();
				TypeCategory y_cat;
				while ((y_cat = y.Category()) == TypeCategory::Alias)
					y = y.Right();
				if (x_cat != y_cat)
					return false;
				XCode[x] = code, YCode[y] = code;
				if (x_cat == TypeCategory::Bool)
					return true;
				if (x_cat == TypeCategory::Parameter)
					return XCode[x.Left()] == YCode[y.Left()];
				return equal(x.Left(), y.Left(), code <<= 1) && equal(x.Right(), y.Right(), code |= 1);
			}(x, y);
	}

	TypeP Type::ApplyTemplate(TypeP temp, TypeP CR arg)
	{
		while (temp.Category() == TypeCategory::Alias)
			temp = temp.Right();
		return [target = temp.Left(), &arg](this auto&& apply, TypeP CR original)
			{
				const TypeCategory cat = original.Category();
				if (cat == TypeCategory::Parameter)
					return original.Left() == target ? arg : original;
				if (cat == TypeCategory::Bool || cat == TypeCategory::Alias)
					return original;
				TypeP result;
				if (cat == TypeCategory::Function)
					result.InitAsFunction(apply(original.Left()), apply(original.Right()));
				else
					result.InitAsTemplate(apply(original.Left()), apply(original.Right()));
				return result;
			}(temp.Right());
	}

	TypeP Type::Clone(TypeP CR _original, UIElement CR _position, MainPageP CR _page_position)
	{
		unordered_map<TypeP, TypeP> mapT;
		return [&mapT, &_position, &_page_position](this auto&& clone, TypeP CR original)->TypeP
			{
				const TypeP result(_position, _page_position);
				result.Self(result);
				switch (original.Category())
				{
				case TypeCategory::Bool:
					result.InitAsBool();
					break;
				case TypeCategory::Function:
					result.InitAsFunction(clone(original.Left()), clone(original.Right()));
					break;
				case TypeCategory::Template:
				{
					const TypeP sb = clone(original.Left());
					result.InitAsTemplate(sb, clone(original.Right()));
				}
				break;
				case TypeCategory::Alias:
					result.InitAsAlias2(original.Left());
					break;
				case TypeCategory::Parameter:
					if (original != original.Left())
						result.InitAsParameter2(mapT[original.Left()]);
					else
					{
						result.InitAsParameter(original.Label());
						mapT[original] = result;
					}
				}
				return result;
			}(_original);
	}

	void Type::LoadedEvent(IInspectable CR, RoutedEventArgs CR)
	{
		if (!loaded)
		{
			loaded = true;
			if (category == TypeCategory::Parameter || category == TypeCategory::Alias)
			{
				Child().Checked([this](IInspectable CR, RoutedEventArgs CR)
					{
						if (chain_click)
							chain_click = false;
						else
						{
							for (TypeP CR same : sames)
								if (same != self.get())
									same.ChainCheck();
							const MenuFlyout menu;
							if (const MainPageP page = left.PagePosition(); page.Position())
							{
								const MenuFlyoutItem item;
								item.Text(ResourceLoader().GetString(L"Go to definition"));
								item.Click([this](IInspectable CR, RoutedEventArgs CR)
									{
										left.Display();
									});
								menu.Items().Append(item);
							}
							else
							{
								const MenuFlyoutSubItem sub_item;
								sub_item.Text(ResourceLoader().GetString(L"Go to definition"));
								{
									const MenuFlyoutItem item;
									item.Text(ResourceLoader().GetString(L"Open here"));
									item.Click([this, page](IInspectable CR, RoutedEventArgs CR)
										{
											const TabViewItem tab = page_position.get().Position();
											GetMainWindow[tab].get().ChangePage(tab, page, box_value(page.Header()));
											left.Display();
										});
									sub_item.Items().Append(item);
								}
								{
									const MenuFlyoutItem item;
									item.Text(ResourceLoader().GetString(L"Open in new tab"));
									item.Click([this, page](IInspectable CR, RoutedEventArgs CR)
										{
											GetMainWindow[page_position.get().Position()].get().OpenTab(page, box_value(page.Header()));
											left.Display();
										});
									sub_item.Items().Append(item);
								}
								menu.Items().Append(sub_item);
							}
							menu.ShowAt(self.get());
						}
					});
				Child().Unchecked([this](IInspectable CR, RoutedEventArgs CR)
					{
						if (chain_click)
							chain_click = false;
						else
							for (TypeP CR same : sames)
								if (same != self.get())
									same.ChainUncheck();
					});
			}
			else
				Child().Checked([this](IInspectable CR, RoutedEventArgs CR)
					{
						Child().IsChecked(false);
					});
		}
	}
}
