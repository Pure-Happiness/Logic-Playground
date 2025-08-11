#pragma once

#include "TipEITShit.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipEITShit : TipEITShitT<TipEITShit>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipEITShit : TipEITShitT<TipEITShit, implementation::TipEITShit>
	{
	};
}
