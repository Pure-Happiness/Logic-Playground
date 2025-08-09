#pragma once

#include "RecentListItem.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct RecentListItem : RecentListItemT<RecentListItem>
	{
		RecentListItem(param::hstring CR _token, NewTabP CR _position);
		void Self(RecentListItemP CR _self);

		fire_and_forget LoadedEvent(IInspectable CR, RoutedEventArgs CR);
		fire_and_forget OpenFile(SwipeItem CR, SwipeItemInvokedEventArgs CR) const;
		void RemoveItem(SwipeItem CR, SwipeItemInvokedEventArgs CR) const;
		fire_and_forget OpenFilePanel(IInspectable CR, TappedRoutedEventArgs CR) const;
		void RemoveItemList(IInspectable CR, RightTappedRoutedEventArgs CR) const;

	private:
		hstring token;
		weak_ref<RecentListItemP> self;
		weak_ref<NewTabP> position;
		bool loaded{};
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct RecentListItem : RecentListItemT<RecentListItem, implementation::RecentListItem>
	{
	};
}
