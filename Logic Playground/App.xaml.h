#pragma once

#include "App.xaml.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct App : AppT<App>
	{
		App();

		static void OnLaunched(LaunchActivatedEventArgs CR);
	};
}
