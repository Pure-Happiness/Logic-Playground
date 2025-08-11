#pragma once

#include "TipAssume.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct TipAssume : TipAssumeT<TipAssume>
	{
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct TipAssume : TipAssumeT<TipAssume, implementation::TipAssume>
	{
	};
}
