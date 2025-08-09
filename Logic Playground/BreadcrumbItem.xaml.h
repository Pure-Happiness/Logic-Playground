#pragma once

#include "BreadcrumbItem.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct BreadcrumbItem : BreadcrumbItemT<BreadcrumbItem>
	{
		BreadcrumbItem(MainPageP CR _target, MainPage CR _position);
		BreadcrumbItemP Clone(MainPageP CR _position) const;

		void LoadedEvent(IInspectable CR, RoutedEventArgs CR);
		void NameClick(IInspectable CR, RoutedEventArgs CR) const;
		void NameMiddleClick(IInspectable CR, PointerRoutedEventArgs CR args);
		void NameRightClick(IInspectable CR, RightTappedRoutedEventArgs);
		void MenuClick(IInspectable CR, RoutedEventArgs CR);
		void MenuClosed(IInspectable CR, IInspectable CR);

	private:
		weak_ref<MainPageP> target;
		weak_ref<MainPageP> position;
		bool loaded{};
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct BreadcrumbItem : BreadcrumbItemT<BreadcrumbItem, implementation::BreadcrumbItem>
	{
	};
}
