#pragma once

#include "Settings.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct Settings : SettingsT<Settings>
	{
		void Position(TabViewItem CR _position);

		void ThemeChoiceLoaded(IInspectable CR, RoutedEventArgs CR);
		void ThemeSelectionChanged(IInspectable CR, SelectionChangedEventArgs CR);
		void LanguageChoiceLoaded(IInspectable CR, RoutedEventArgs CR);
		void LanguageSelectionChanged(IInspectable CR, SelectionChangedEventArgs CR);
		void RecoveryLoaded(IInspectable CR, RoutedEventArgs CR);

	private:
		weak_ref<TabViewItem> position;
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct Settings : SettingsT<Settings, implementation::Settings>
	{
	};
}
