#pragma once

#include "TipEE.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipEE : TipEET<TipEE>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipEE : TipEET<TipEE, implementation::TipEE>
	{
	};
}
