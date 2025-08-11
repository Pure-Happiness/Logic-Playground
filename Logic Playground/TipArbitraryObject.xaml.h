#pragma once

#include "TipArbitraryObject.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipArbitraryObject : TipArbitraryObjectT<TipArbitraryObject>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipArbitraryObject : TipArbitraryObjectT<TipArbitraryObject, implementation::TipArbitraryObject>
	{
	};
}
