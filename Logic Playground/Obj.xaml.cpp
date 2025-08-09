#include "pch.h"
#include "Obj.xaml.h"
#if __has_include("Obj.g.cpp")
#include "Obj.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	Obj::Obj(UIElement CR _position, MainPageP CR _page_position) :ObjT(), position(_position), page_position(_page_position)
	{
	}

	void Obj::Self(ObjP CR _self)
	{
		self = _self;
	}

	MainPageP Obj::PagePosition() const
	{
		return page_position.get();
	}

	ObjectCategory Obj::Category() const
	{
		return category;
	}

	hstring Obj::Label() const
	{
		return label;
	}

	ObjP Obj::Left() const
	{
		return left;
	}

	ObjP Obj::Right() const
	{
		return right;
	}

	TypeP Obj::MyType() const
	{
		return type;
	}

	IVector<ObjP> Obj::Sames() const
	{
		return sames;
	}

	void Obj::ChainCheck()
	{
		chain_click = true;
		Child().IsChecked(true);
	}

	void Obj::ChainUncheck()
	{
		chain_click = true;
		Child().IsChecked(false);
	}

	void Obj::Display() const
	{
		page_position.get().Display(position.get());
	}

	void Obj::InitAsTrue()
	{
		category = ObjectCategory::True;
		Child().Content(BoldCode(label = L"true"));
		type = HiddenBool;
	}

	void Obj::InitAsFalse()
	{
		category = ObjectCategory::False;
		Child().Content(BoldCode(label = L"false"));
		type = HiddenBool;
	}

	void Obj::InitAsParameter(TypeP CR _type, param::hstring CR _label)
	{
		category = ObjectCategory::Parameter;
		Child().Content(LightCode(label = _label));
		type = _type;
		(sames = single_threaded_vector<ObjP>()).Append(left = self.get());
	}

	void Obj::InitAsParameter2(ObjP CR _declaration)
	{
		category = ObjectCategory::Parameter;
		Child().Content(LightCode(label = (left = _declaration.Left()).Label()));
		type = left.MyType();
		(sames = left.Sames()).Append(self.get());
	}

	void Obj::InitAsType(TypeP CR _type)
	{
		category = ObjectCategory::Type;
		type = _type;
	}

	void Obj::InitAsDeclareF(ObjP CR _left, ObjP CR _right)
	{
		category = ObjectCategory::DeclareF;
		const TextBlock content = RegularCode(label = L"@");
		content.Foreground(ThemeBlueAqua);
		Child().Content(content);
		(type = TypeP()).InitAsFunction((left = _left).MyType(), (right = _right).MyType());
	}

	void Obj::InitAsDeclareT(ObjP CR _left, ObjP CR _right)
	{
		category = ObjectCategory::DeclareT;
		const TextBlock content = RegularCode(label = L"@");
		content.Foreground(ThemeRedPurple);
		Child().Content(content);
		(type = TypeP()).InitAsTemplate((left = _left).MyType(), (right = _right).MyType());
	}

	void Obj::InitAsApplyF(ObjP CR _left, ObjP CR _right)
	{
		category = ObjectCategory::ApplyF;
		const TextBlock content = RegularCode(label = L"#");
		content.Foreground(ThemeBlueAqua);
		Child().Content(content);
		type = (left = _left).MyType().Right(), right = _right;
	}

	void Obj::InitAsApplyT(ObjP CR _left, ObjP CR _right)
	{
		category = ObjectCategory::ApplyT;
		const TextBlock content = RegularCode(label = L"#");
		content.Foreground(ThemeRedPurple);
		Child().Content(content);
		type = TypeP::ApplyTemplate((left = _left).MyType(), (right = _right).MyType());
	}

	void Obj::InitAsForallF(ObjP CR _x)
	{
		category = ObjectCategory::ForallF;
		const TextBlock content = RegularCode(label = L"!");
		content.Foreground(ThemeBlueAqua);
		Child().Content(content);
		type = HiddenBool, right = _x;
	}

	void Obj::InitAsForallT(ObjP CR _x)
	{
		category = ObjectCategory::ForallT;
		const TextBlock content = RegularCode(label = L"!");
		content.Foreground(ThemeRedPurple);
		Child().Content(content);
		type = HiddenBool, right = _x;
	}

	void Obj::InitAsEqual(ObjP CR _left, ObjP CR _right)
	{
		category = ObjectCategory::Equal;
		const TextBlock content = RegularCode(label = L"=");
		content.Foreground(ThemeGreenYellow);
		Child().Content(content);
		type = HiddenBool, left = _left, right = _right;
	}

	void Obj::InitAsOptions(ObjP CR _left, ObjP CR _right)
	{
		category = ObjectCategory::Options;
		const TextBlock content = RegularCode(label = L"?");
		content.Foreground(ThemeBlueAqua);
		Child().Content(content);
		type = (left = _left).MyType(), right = _right;
	}

	void Obj::InitAsChoose(ObjP CR _left, ObjP CR _right)
	{
		category = ObjectCategory::Choose;
		const TextBlock content = RegularCode(label = L"?");
		content.Foreground(ThemeRedPurple);
		Child().Content(content);
		type = (right = _right).MyType(), left = _left;
	}

	void Obj::InitAsAlias(ObjP CR _definition, param::hstring CR _label)
	{
		category = ObjectCategory::Alias;
		Child().Content(RegularCode(label = _label));
		type = (right = _definition).MyType();
		(sames = single_threaded_vector<ObjP>()).Append(left = self.get());
	}

	void Obj::InitAsAlias2(ObjP CR _declaration)
	{
		category = ObjectCategory::Alias;
		Child().Content(RegularCode(label = (left = _declaration).Label()));
		type = (right = left.Right()).MyType();
		(sames = left.Sames()).Append(self.get());
	}

	IVectorView<UIElement> Obj::Generate(ObjP CR obj)
	{
		unordered_set<ObjP> need_bracket;
		return [&need_bracket](this auto&& generate, ObjP CR current)->IVectorView<UIElement>
			{
				constexpr array LeftP{ 0, 0, 0, 0, 7, 7, 3, 3, 5, 5, 5, 7, 7, 0 }, RightP{ 0, 0, 0, 0, 2, 2, 4, 4, 0, 0, 6, 6, 6, 0 };
				const IVector result = single_threaded_vector<UIElement>();
				if (const ObjectCategory cat = current.Category(); LeftP[static_cast<size_t>(cat)])
				{
					if (ObjP lf = current.Left(); lf && !need_bracket.contains(lf))
						for (; LeftP[static_cast<size_t>(lf.Category())]; lf = lf.Right())
							if (LeftP[static_cast<size_t>(lf.Category())] > RightP[static_cast<size_t>(cat)])
							{
								need_bracket.insert(lf);
								break;
							}
					if (ObjP rt = current.Right(); !need_bracket.contains(rt))
						for (; RightP[static_cast<size_t>(rt.Category())]; rt = rt.Left())
							if (RightP[static_cast<size_t>(rt.Category())] > LeftP[static_cast<size_t>(cat)])
							{
								need_bracket.insert(rt);
								break;
							}
					if (need_bracket.contains(current))
					{
						const Bracket lb, rb;
						Bracket::Link(lb, rb);
						result.Append(lb);
						if (ObjP lf = current.Left())
							for (UIElement CR element : generate(lf))
								result.Append(element);
						result.Append(current);
						for (UIElement CR element : generate(current.Right()))
							result.Append(element);
						result.Append(rb);
					}
					else
					{
						if (ObjP lf = current.Left())
							for (UIElement CR element : generate(lf))
								result.Append(element);
						result.Append(current);
						for (UIElement CR element : generate(current.Right()))
							result.Append(element);
					}
				}
				else if (cat != ObjectCategory::Type)
				{
					result.Append(current);
					if (cat == ObjectCategory::Parameter && current.Left() == current)
					{
						result.Append(Colon());
						for (UIElement CR element : Type::Generate(current.MyType()))
							result.Append(element);
					}
				}
				else
					for (UIElement CR element : Type::Generate(current.MyType()))
						result.Append(element);
				return result.GetView();
			}(obj);
	}

	hstring Obj::GenerateText(ObjP CR obj)
	{
		unordered_set<ObjP> need_bracket;
		return [&need_bracket](this auto&& generate_text, ObjP CR current)->hstring
			{
				constexpr array LeftP{ 0, 0, 0, 0, 7, 7, 3, 3, 5, 5, 5, 7, 7, 0 }, RightP{ 0, 0, 0, 0, 2, 2, 4, 4, 0, 0, 6, 6, 6, 0 };
				const ObjectCategory cat = current.Category();
				if (LeftP[static_cast<size_t>(cat)])
				{
					if (ObjP lf = current.Left(); lf && !need_bracket.contains(lf))
						for (; LeftP[static_cast<size_t>(lf.Category())]; lf = lf.Right())
							if (LeftP[static_cast<size_t>(lf.Category())] > RightP[static_cast<size_t>(cat)])
							{
								need_bracket.insert(lf);
								break;
							}
					if (ObjP rt = current.Right(); !need_bracket.contains(rt))
						for (; RightP[static_cast<size_t>(rt.Category())]; rt = rt.Left())
							if (RightP[static_cast<size_t>(rt.Category())] > LeftP[static_cast<size_t>(cat)])
							{
								need_bracket.insert(rt);
								break;
							}
					if (need_bracket.contains(current))
						return hstring(L"(") + generate_text(current.Left()) + current.Label() + generate_text(current.Right()) + L')';
					return generate_text(current.Left()) + current.Label() + generate_text(current.Right());
				}
				if (cat != ObjectCategory::Type)
				{
					if (cat == ObjectCategory::Parameter && current.Left() == current)
						return current.Label() + L':' + TypeP::GenerateText(current.MyType());
					return current.Label();
				}
				return TypeP::GenerateText(current.MyType());
			}(obj);
	}

	bool Obj::Equal(ObjP CR x, ObjP CR y)
	{
		unordered_map<ObjP, unsigned> XCodeO, YCodeO;
		unordered_map<TypeP, unsigned> XCodeT, YCodeT;
		return [&XCodeO, &YCodeO, &XCodeT, &YCodeT](this auto&& equal, ObjP x, ObjP y, unsigned code = 1)
			{
				auto et = [&XCodeT, &YCodeT](this auto&& et, TypeP x, TypeP y, unsigned code)
					{
						TypeCategory x_cat;
						while ((x_cat = x.Category()) == TypeCategory::Alias)
							x = x.Right();
						TypeCategory y_cat;
						while ((y_cat = y.Category()) == TypeCategory::Alias)
							y = y.Right();
						if (x_cat != y_cat)
							return false;
						XCodeT[x] = code, YCodeT[y] = code;
						if (x_cat == TypeCategory::Bool)
							return true;
						if (x_cat == TypeCategory::Parameter)
							return XCodeT[x.Left()] == YCodeT[y.Left()];
						return et(x.Left(), y.Left(), code <<= 1) && et(x.Right(), y.Right(), code |= 1);
					};
				ObjectCategory x_cat;
				while ((x_cat = x.Category()) == ObjectCategory::Alias)
					x = x.Right();
				ObjectCategory y_cat;
				while ((y_cat = y.Category()) == ObjectCategory::Alias)
					y = y.Right();
				if (x_cat != y_cat)
					return false;
				if (x_cat == ObjectCategory::Type)
					return et(x.MyType(), y.MyType(), code);
				XCodeO[x] = code, YCodeO[y] = code;
				if (x_cat == ObjectCategory::True || x_cat == ObjectCategory::False)
					return true;
				if (x_cat == ObjectCategory::Parameter)
				{
					if (x.Left() == x)
						return et(x.MyType(), y.MyType(), code);
					return XCodeO[x.Left()] == YCodeO[y.Left()];
				}
				bool result = true;
				code <<= 1;
				if (x.Left())
					result &= equal(x.Left(), y.Left(), code);
				return result && equal(x.Right(), y.Right(), code |= 1);
			}(x, y);
	}

	ObjP Obj::ApplyFunction(ObjP CR func, ObjP CR arg, UIElement CR _position, MainPageP CR _page_position)
	{
		unordered_map<ObjP, ObjP> mapO;
		unordered_map<TypeP, TypeP> mapT;
		return [target = func.Left(), &arg, &mapO, &mapT, &_position, &_page_position](this auto&& apply, ObjP CR original)->ObjP
			{
				auto ct = [&mapT, &_position, &_page_position](this auto&& ct, TypeP CR original)->TypeP
					{
						const TypeP result(_position, _page_position);
						result.Self(result);
						switch (original.Category())
						{
						case TypeCategory::Bool:
							result.InitAsBool();
							break;
						case TypeCategory::Function:
							result.InitAsFunction(ct(original.Left()), ct(original.Right()));
							break;
						case TypeCategory::Template:
						{
							const TypeP sb = ct(original.Left());
							result.InitAsTemplate(sb, ct(original.Right()));
						}
						break;
						case TypeCategory::Alias:
							result.InitAsAlias2(original.Left());
							break;
						case TypeCategory::Parameter:
							if (const TypeP oL = original.Left(); original != oL)
								result.InitAsParameter2(mapT.contains(oL) ? mapT[oL] : oL);
							else
							{
								result.InitAsParameter(original.Label());
								mapT[original] = result;
							}
						}
						return result;
					};
				ObjP result(_position, _page_position);
				result.Self(result);
				switch (original.Category())
				{
				case ObjectCategory::Type:
					result.InitAsType(ct(original.MyType()));
					break;
				case ObjectCategory::True:
					result.InitAsTrue();
					break;
				case ObjectCategory::False:
					result.InitAsFalse();
					break;
				case ObjectCategory::DeclareF:
				{
					const ObjP sb = apply(original.Left());
					result.InitAsDeclareF(sb, apply(original.Right()));
				}
				break;
				case ObjectCategory::DeclareT:
				{
					const ObjP sb = apply(original.Left());
					result.InitAsDeclareT(sb, apply(original.Right()));
				}
				break;
				case ObjectCategory::ApplyF:
					result.InitAsApplyF(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::ApplyT:
					result.InitAsApplyT(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::ForallF:
					result.InitAsForallF(apply(original.Right()));
					break;
				case ObjectCategory::ForallT:
					result.InitAsForallT(apply(original.Right()));
					break;
				case ObjectCategory::Equal:
					result.InitAsEqual(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::Options:
					result.InitAsOptions(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::Choose:
					result.InitAsChoose(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::Alias:
					result.InitAsAlias2(original.Left());
					break;
				case ObjectCategory::Parameter:
					if (const ObjP oL = original.Left(); original != oL)
						if (oL != target)
							result.InitAsParameter2(mapO.contains(oL) ? mapO[oL] : oL);
						else
							result = Clone(arg, _position, _page_position);
					else
					{
						result.InitAsParameter(ct(original.MyType()), original.Label());
						mapO[original] = result;
					}
				}
				return result;
			}(func.Right());
	}

	ObjP Obj::ApplyTemplate(ObjP CR temp, TypeP CR arg, UIElement CR _position, MainPageP CR _page_position)
	{
		unordered_map<ObjP, ObjP> mapO;
		unordered_map<TypeP, TypeP> mapT;
		/*return [target = temp.Left().MyType(), &arg, &mapO, &mapT, &_position, &_page_position](this auto&& apply, ObjP CR original)->ObjP
			{
				auto ct = [&target, &arg, &mapT, &_position, &_page_position](this auto&& ct, TypeP CR original)->TypeP
					{
						TypeP result(_position, _page_position);
						result.Self(result);
						switch (original.Category())
						{
						case TypeCategory::Bool:
							result.InitAsBool();
							break;
						case TypeCategory::Function:
							result.InitAsFunction(ct(original.Left()), ct(original.Right()));
							break;
						case TypeCategory::Template:
						{
							const TypeP sb = ct(original.Left());
							result.InitAsTemplate(sb, ct(original.Right()));
						}
						break;
						case TypeCategory::Alias:
							result.InitAsAlias2(original.Left());
							break;
						case TypeCategory::Parameter:
							if (const TypeP oL = original.Left(); original != oL)
								if (oL != target)
									result.InitAsParameter2(mapT.contains(oL) ? mapT[oL] : oL);
								else
									result = Type::Clone(arg, _position, _page_position);
							else
							{
								result.InitAsParameter(original.Label());
								mapT[original] = result;
							}
						}
						return result;
					};
				ObjP result(_position, _page_position);
				result.Self(result);
				switch (original.Category())
				{
				case ObjectCategory::Type:
					result.InitAsType(ct(original.MyType()));
					break;
				case ObjectCategory::True:
					result.InitAsTrue();
					break;
				case ObjectCategory::False:
					result.InitAsFalse();
					break;
				case ObjectCategory::DeclareF:
				{
					const ObjP sb = apply(original.Left());
					result.InitAsDeclareF(sb, apply(original.Right()));
				}
				break;
				case ObjectCategory::DeclareT:
				{
					const ObjP sb = apply(original.Left());
					result.InitAsDeclareT(sb, apply(original.Right()));
				}
				break;
				case ObjectCategory::ApplyF:
					result.InitAsApplyF(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::ApplyT:
					result.InitAsApplyT(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::ForallF:
					result.InitAsForallF(apply(original.Right()));
					break;
				case ObjectCategory::ForallT:
					result.InitAsForallT(apply(original.Right()));
					break;
				case ObjectCategory::Equal:
					result.InitAsEqual(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::Options:
					result.InitAsOptions(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::Choose:
					result.InitAsChoose(apply(original.Left()), apply(original.Right()));
					break;
				case ObjectCategory::Alias:
					result.InitAsAlias2(original.Left());
					break;
				case ObjectCategory::Parameter:
					if (const ObjP oL = original.Left(); original != oL)
						result.InitAsParameter2(mapO.contains(oL) ? mapO[oL] : oL);
					else
					{
						result.InitAsParameter(ct(original.MyType()), original.Label());
						mapO[original] = result;
					}
				}
				return result;
			}(temp.Right());*/
		auto shit = [target = temp.Left().MyType(), &arg, &mapO, &mapT, &_position, &_page_position](auto&& apply, ObjP CR original)->ObjP
			{
				auto ct = [&target, &arg, &mapT, &_position, &_page_position](this auto&& ct, TypeP CR original)->TypeP
					{
						TypeP result(_position, _page_position);
						result.Self(result);
						switch (original.Category())
						{
						case TypeCategory::Bool:
							result.InitAsBool();
							break;
						case TypeCategory::Function:
							result.InitAsFunction(ct(original.Left()), ct(original.Right()));
							break;
						case TypeCategory::Template:
						{
							const TypeP sb = ct(original.Left());
							result.InitAsTemplate(sb, ct(original.Right()));
						}
						break;
						case TypeCategory::Alias:
							result.InitAsAlias2(original.Left());
							break;
						case TypeCategory::Parameter:
							if (const TypeP oL = original.Left(); original != oL)
								if (oL != target)
									result.InitAsParameter2(mapT.contains(oL) ? mapT[oL] : oL);
								else
									result = Type::Clone(arg, _position, _page_position);
							else
							{
								result.InitAsParameter(original.Label());
								mapT[original] = result;
							}
						}
						return result;
					};
				ObjP result(_position, _page_position);
				result.Self(result);
				switch (original.Category())
				{
				case ObjectCategory::Type:
					result.InitAsType(ct(original.MyType()));
					break;
				case ObjectCategory::True:
					result.InitAsTrue();
					break;
				case ObjectCategory::False:
					result.InitAsFalse();
					break;
				case ObjectCategory::DeclareF:
				{
					const ObjP sb = apply(apply, original.Left());
					result.InitAsDeclareF(sb, apply(apply, original.Right()));
				}
				break;
				case ObjectCategory::DeclareT:
				{
					const ObjP sb = apply(apply, original.Left());
					result.InitAsDeclareT(sb, apply(apply, original.Right()));
				}
				break;
				case ObjectCategory::ApplyF:
					result.InitAsApplyF(apply(apply, original.Left()), apply(apply, original.Right()));
					break;
				case ObjectCategory::ApplyT:
					result.InitAsApplyT(apply(apply, original.Left()), apply(apply, original.Right()));
					break;
				case ObjectCategory::ForallF:
					result.InitAsForallF(apply(apply, original.Right()));
					break;
				case ObjectCategory::ForallT:
					result.InitAsForallT(apply(apply, original.Right()));
					break;
				case ObjectCategory::Equal:
					result.InitAsEqual(apply(apply, original.Left()), apply(apply, original.Right()));
					break;
				case ObjectCategory::Options:
					result.InitAsOptions(apply(apply, original.Left()), apply(apply, original.Right()));
					break;
				case ObjectCategory::Choose:
					result.InitAsChoose(apply(apply, original.Left()), apply(apply, original.Right()));
					break;
				case ObjectCategory::Alias:
					result.InitAsAlias2(original.Left());
					break;
				case ObjectCategory::Parameter:
					if (const ObjP oL = original.Left(); original != oL)
						result.InitAsParameter2(mapO.contains(oL) ? mapO[oL] : oL);
					else
					{
						result.InitAsParameter(ct(original.MyType()), original.Label());
						mapO[original] = result;
					}
				}
				return result;
			};
		return shit(shit, temp.Right());
	}

	ObjP Obj::Clone(ObjP CR _original, UIElement CR _position, MainPageP CR _page_position)
	{
		unordered_map<ObjP, ObjP> mapO;
		unordered_map<TypeP, TypeP> mapT;
		return [&mapO, &mapT, &_position, &_page_position](this auto&& clone, ObjP CR original)->ObjP
			{
				auto ct = [&mapT, &_position, &_page_position](this auto&& ct, TypeP CR original)->TypeP
					{
						const TypeP result(_position, _page_position);
						result.Self(result);
						switch (original.Category())
						{
						case TypeCategory::Bool:
							result.InitAsBool();
							break;
						case TypeCategory::Function:
							result.InitAsFunction(ct(original.Left()), ct(original.Right()));
							break;
						case TypeCategory::Template:
						{
							const TypeP sb = ct(original.Left());
							result.InitAsTemplate(sb, ct(original.Right()));
						}
						break;
						case TypeCategory::Alias:
							result.InitAsAlias2(original.Left());
							break;
						case TypeCategory::Parameter:
							if (const TypeP oL = original.Left(); original != oL)
								result.InitAsParameter2(mapT.contains(oL) ? mapT[oL] : oL);
							else
							{
								result.InitAsParameter(original.Label());
								mapT[original] = result;
							}
						}
						return result;
					};
				const ObjP result(_position, _page_position);
				result.Self(result);
				switch (original.Category())
				{
				case ObjectCategory::Type:
					result.InitAsType(ct(original.MyType()));
					break;
				case ObjectCategory::True:
					result.InitAsTrue();
					break;
				case ObjectCategory::False:
					result.InitAsFalse();
					break;
				case ObjectCategory::DeclareF:
				{
					const ObjP sb = clone(original.Left());
					result.InitAsDeclareF(sb, clone(original.Right()));
				}
				break;
				case ObjectCategory::DeclareT:
				{
					const ObjP sb = clone(original.Left());
					result.InitAsDeclareT(sb, clone(original.Right()));
				}
				break;
				case ObjectCategory::ApplyF:
					result.InitAsApplyF(clone(original.Left()), clone(original.Right()));
					break;
				case ObjectCategory::ApplyT:
					result.InitAsApplyT(clone(original.Left()), clone(original.Right()));
					break;
				case ObjectCategory::ForallF:
					result.InitAsForallF(clone(original.Right()));
					break;
				case ObjectCategory::ForallT:
					result.InitAsForallT(clone(original.Right()));
					break;
				case ObjectCategory::Equal:
					result.InitAsEqual(clone(original.Left()), clone(original.Right()));
					break;
				case ObjectCategory::Options:
					result.InitAsOptions(clone(original.Left()), clone(original.Right()));
					break;
				case ObjectCategory::Choose:
					result.InitAsChoose(clone(original.Left()), clone(original.Right()));
					break;
				case ObjectCategory::Alias:
					result.InitAsAlias2(original.Left());
					break;
				case ObjectCategory::Parameter:
					if (const ObjP oL = original.Left(); original != oL)
						result.InitAsParameter2(mapO.contains(oL) ? mapO[oL] : oL);
					else
					{
						result.InitAsParameter(ct(original.MyType()), original.Label());
						mapO[original] = result;
					}
				}
				return result;
			}(_original);
	}

	void Obj::LoadedEvent(IInspectable CR, RoutedEventArgs CR)
	{
		if (!loaded)
		{
			loaded = true;
			if (category == ObjectCategory::Parameter || category == ObjectCategory::Alias)
			{
				Child().Checked([this](IInspectable CR, RoutedEventArgs CR)
					{
						if (chain_click)
							chain_click = false;
						else
						{
							for (ObjP CR same : sames)
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
							for (ObjP CR same : sames)
								if (same != self.get())
									same.ChainUncheck();
					});
			}
			else if (category != ObjectCategory::Type)
				Child().Checked([this](IInspectable CR, RoutedEventArgs CR)
					{
						Child().IsChecked(false);
					});
		}
	}
}
