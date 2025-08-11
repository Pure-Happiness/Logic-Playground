#pragma once

#include "TipET.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipET : TipETT<TipET>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipET : TipETT<TipET, implementation::TipET>
	{
	};
}
