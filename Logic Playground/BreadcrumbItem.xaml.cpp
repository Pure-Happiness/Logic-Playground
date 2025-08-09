#include "pch.h"
#include "BreadcrumbItem.xaml.h"
#if __has_include("BreadcrumbItem.g.cpp")
#include "BreadcrumbItem.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	BreadcrumbItem::BreadcrumbItem(MainPageP CR _target, MainPageP CR _position) : BreadcrumbItemT(), target(_target), position(_position)
	{
	}

	BreadcrumbItemP BreadcrumbItem::Clone(MainPageP CR _position) const
	{
		return BreadcrumbItemP(target.get(), _position);
	}

	void BreadcrumbItem::LoadedEvent(IInspectable CR, RoutedEventArgs CR)
	{
		if (!loaded)
		{
			loaded = true;
			name().Content(box_value(target.get().Header()));
		}
	}

	void BreadcrumbItem::NameClick(IInspectable CR, RoutedEventArgs CR) const
	{
		if (const MainPage page = target.get(); page.Position())
			page.Display();
		else
		{
			const TabViewItem place = position.get().Position();
			GetMainWindow[place].get().ChangePage(place, page, box_value(page.Header()));
		}
	}

	void BreadcrumbItem::NameMiddleClick(IInspectable CR, PointerRoutedEventArgs CR args)
	{
		if (args.GetCurrentPoint(name()).Properties().IsMiddleButtonPressed())
			if (const MainPage page = target.get(); page.Position())
				page.Display();
			else
				GetMainWindow[position.get().Position()].get().OpenTab(page, box_value(page.Header()));
	}

	void BreadcrumbItem::NameRightClick(IInspectable CR, RightTappedRoutedEventArgs)
	{
		if (const MainPage page = target.get(); page.Position())
		{
			const MenuFlyout flyout;
			{
				const MenuFlyoutItem item;
				item.Text(ResourceLoader().GetString(L"µ¼º½µ½") + target.get().Header());
				item.Click([page](IInspectable CR, RoutedEventArgs CR)
					{
						page.Display();
					});
				flyout.Items().Append(item);
			}
			flyout.ShowAt(name());
		}
		else
		{
			const MenuFlyout flyout;
			{
				const MenuFlyoutItem item;
				item.Text(ResourceLoader().GetString(L"Open here"));
				item.Click([this, page](IInspectable CR, RoutedEventArgs CR)
					{
						const TabViewItem place = position.get().Position();
						GetMainWindow[place].get().ChangePage(place, page, box_value(page.Header()));
					});
				flyout.Items().Append(item);
			}
			{
				const MenuFlyoutItem item;
				item.Text(ResourceLoader().GetString(L"Open in new tab"));
				item.Click([this, page](IInspectable CR, RoutedEventArgs CR)
					{
						GetMainWindow[position.get().Position()].get().OpenTab(page, box_value(page.Header()));
					});
				flyout.Items().Append(item);
			}
			flyout.ShowAt(name());
		}
	}

	void BreadcrumbItem::MenuClick(IInspectable CR, RoutedEventArgs CR)
	{
		icon().Glyph(L"\uE70D");
		const IVector<MenuFlyoutItemBase> items = menu().Items();
		items.Clear();
		for (MainPageP CR child : target.get().Children())
			if (child.Position())
			{
				const MenuFlyoutItem item;
				item.Text(child.Header());
				item.Click([child](IInspectable CR, RoutedEventArgs CR)
					{
						child.Display();
					});
				items.Append(item);
			}
			else
			{
				const MenuFlyoutSubItem sub_item;
				sub_item.Text(child.Header());
				{
					const MenuFlyoutItem item;
					item.Text(ResourceLoader().GetString(L"Open here"));
					item.Click([child, this](IInspectable CR, RoutedEventArgs CR)
						{
							const TabViewItem place = position.get().Position();
							GetMainWindow[place].get().ChangePage(place, child, box_value(child.Header()));
						});
					sub_item.Items().Append(item);
				}
				{
					const MenuFlyoutItem item;
					item.Text(ResourceLoader().GetString(L"Open in new tab"));
					item.Click([child, this](IInspectable CR, RoutedEventArgs CR)
						{
							GetMainWindow[position.get().Position()].get().OpenTab(child, box_value(child.Header()));
						});
					sub_item.Items().Append(item);
				}
				items.Append(sub_item);
			}
	}

	void BreadcrumbItem::MenuClosed(IInspectable CR, IInspectable CR)
	{
		icon().Glyph(L"\uE76C");
	}
}
