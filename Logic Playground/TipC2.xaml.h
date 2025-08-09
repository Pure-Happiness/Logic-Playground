#pragma once

#include "TipC2.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipC2 : TipC2T<TipC2>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipC2 : TipC2T<TipC2, implementation::TipC2>
    {
    };
}
