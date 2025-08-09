#include "pch.h"
#include "Theorem.xaml.h"
#if __has_include("Theorem.g.cpp")
#include "Theorem.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	Theorem::Theorem(UIElement CR _position, MainPageP CR _page_position) :TheoremT(), position(_position), page_position(_page_position)
	{
	}

	void Theorem::Self(TheoremP CR _self)
	{
		self = _self;
	}

	MainPageP Theorem::PagePosition() const
	{
		return page_position.get();
	}

	hstring Theorem::Label() const
	{
		return label;
	}

	TheoremP Theorem::Declaration() const
	{
		return declaration.get();
	}

	ObjP Theorem::Definition() const
	{
		return definition;
	}

	IVector<TheoremP> Theorem::Sames() const
	{
		return sames;
	}

	void Theorem::ChainCheck()
	{
		chain_click = true;
		Child().IsChecked(true);
	}

	void Theorem::ChainUncheck()
	{
		chain_click = true;
		Child().IsChecked(false);
	}

	void Theorem::Display() const
	{
		page_position.get().Display(position.get());
	}

	void Theorem::Init(ObjP CR _definition, param::hstring CR _label)
	{
		Child().Content(box_value(label = _label));
		definition = _definition;
		(sames = single_threaded_vector<TheoremP>()).Append((declaration = self).get());
	}

	void Theorem::Init2(TheoremP CR _declaration)
	{
		Child().Content(box_value(label = _declaration.Label()));
		definition = _declaration.Definition();
		(sames = _declaration.Sames()).Append(self.get());
		declaration = _declaration;
	}

	void Theorem::LoadedEvent(IInspectable CR, RoutedEventArgs CR)
	{
		if (!loaded)
		{
			loaded = true;
			Child().Checked([this](IInspectable CR, RoutedEventArgs CR)
				{
					if (chain_click)
						chain_click = false;
					else
					{
						for (TheoremP CR same : sames)
							if (same != self.get())
								same.ChainCheck();
						const MenuFlyout menu;
						if (const MainPageP page = declaration.get().PagePosition(); page.Position())
						{
							const MenuFlyoutItem item;
							item.Text(ResourceLoader().GetString(L"Go to definition"));
							item.Click([this](IInspectable CR, RoutedEventArgs CR)
								{
									declaration.get().Display();
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
										declaration.get().Display();
									});
								sub_item.Items().Append(item);
							}
							{
								const MenuFlyoutItem item;
								item.Text(ResourceLoader().GetString(L"Open in new tab"));
								item.Click([this, page](IInspectable CR, RoutedEventArgs CR)
									{
										GetMainWindow[page_position.get().Position()].get().OpenTab(page, box_value(page.Header()));
										declaration.get().Display();
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
						for (TheoremP CR same : sames)
							if (same != self.get())
								same.ChainUncheck();
				});
		}
	}
}
