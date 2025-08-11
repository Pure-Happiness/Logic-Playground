#pragma once

#include "TipEEB.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipEEB : TipEEBT<TipEEB>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipEEB : TipEEBT<TipEEB, implementation::TipEEB>
	{
	};
}
