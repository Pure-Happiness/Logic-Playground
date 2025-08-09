#pragma once

#include "TheoremPanel.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TheoremPanel : TheoremPanelT<TheoremPanel>
	{
		void Name(TheoremP CR _name);

		void ShowCopyName(IInspectable CR, RightTappedRoutedEventArgs CR);
		void ShowCopyContent(IInspectable CR, RightTappedRoutedEventArgs CR);

	private:
		TheoremP name;
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TheoremPanel : TheoremPanelT<TheoremPanel, implementation::TheoremPanel>
	{
	};
}
