#pragma once

#include "TipC1.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipC1 : TipC1T<TipC1>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipC1 : TipC1T<TipC1, implementation::TipC1>
	{
	};
}
