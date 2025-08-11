#pragma once

#include "TipUF.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipUF : TipUFT<TipUF>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipUF : TipUFT<TipUF, implementation::TipUF>
	{
	};
}
