#pragma once

#include "TipScope.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipScope : TipScopeT<TipScope>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipScope : TipScopeT<TipScope, implementation::TipScope>
    {
    };
}
