#pragma once

#include "TipC3.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipC3 : TipC3T<TipC3>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipC3 : TipC3T<TipC3, implementation::TipC3>
	{
	};
}
