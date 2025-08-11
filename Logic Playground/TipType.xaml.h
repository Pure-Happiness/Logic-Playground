#pragma once

#include "TipType.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipType : TipTypeT<TipType>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipType : TipTypeT<TipType, implementation::TipType>
	{
	};
}
