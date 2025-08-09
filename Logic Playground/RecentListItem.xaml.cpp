#include "pch.h"
#include "RecentListItem.xaml.h"
#if __has_include("RecentListItem.g.cpp")
#include "RecentListItem.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	RecentListItem::RecentListItem(param::hstring CR _token, NewTabP CR _position) :RecentListItemT(), token(_token), position(_position)
	{
	}

	void RecentListItem::Self(RecentListItemP CR _self)
	{
		self = _self;
	}

	fire_and_forget RecentListItem::LoadedEvent(IInspectable CR, RoutedEventArgs CR)
	{
		if (!loaded)
		{
			loaded = true;
			try
			{
				const StorageFile file = co_await StorageApplicationPermissions::MostRecentlyUsedList().GetFileAsync(token);
				name().Text(file.DisplayName());
				path().Text(file.Path());
			}
			catch (...)
			{
				name().Text(L"???");
				path().Text(L"???");
			}
		}
	}

	fire_and_forget RecentListItem::OpenFile(SwipeItem CR, SwipeItemInvokedEventArgs CR) const
	{
		try
		{
			position.get().OpenFile(co_await StorageApplicationPermissions::MostRecentlyUsedList().GetFileAsync(token));
		}
		catch (...)
		{
			const Flyout flyout;
			{
				const TextBlock content;
				content.Text(ResourceLoader().GetString(L"OpenFileFailure"));
				flyout.Content(content);
			}
			flyout.ShowAt(self.get());
		}
	}

	void RecentListItem::RemoveItem(SwipeItem CR, SwipeItemInvokedEventArgs CR) const
	{
		position.get().RemoveItem(self.get());
		StorageApplicationPermissions::MostRecentlyUsedList().Remove(token);
	}

	fire_and_forget RecentListItem::OpenFilePanel(IInspectable CR, TappedRoutedEventArgs CR) const
	{
		try
		{
			position.get().OpenFile(co_await StorageApplicationPermissions::MostRecentlyUsedList().GetFileAsync(token));
		}
		catch (...)
		{
			const Flyout flyout;
			{
				const TextBlock content;
				content.Text(ResourceLoader().GetString(L"OpenFileFailure"));
				flyout.Content(content);
			}
			flyout.ShowAt(self.get());
		}
	}

	void RecentListItem::RemoveItemList(IInspectable CR, RightTappedRoutedEventArgs CR) const
	{
		const MenuFlyout menu;
		{
			const MenuFlyoutItem item;
			item.Text(L"RemoveItem");
			item.Click([this](IInspectable CR, RoutedEventArgs CR)
				{
					position.get().RemoveItem(self.get());
					StorageApplicationPermissions::MostRecentlyUsedList().Remove(token);
				});
			menu.Items().Append(item);
		}
		menu.ShowAt(self.get());
	}
}
