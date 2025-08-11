#pragma once

#include "TipUT.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipUT : TipUTT<TipUT>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipUT : TipUTT<TipUT, implementation::TipUT>
	{
	};
}
