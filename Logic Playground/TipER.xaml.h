#pragma once

#include "TipER.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipER : TipERT<TipER>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipER : TipERT<TipER, implementation::TipER>
	{
	};
}
