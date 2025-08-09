#pragma once

#include "TipEI.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipEI : TipEIT<TipEI>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipEI : TipEIT<TipEI, implementation::TipEI>
    {
    };
}
