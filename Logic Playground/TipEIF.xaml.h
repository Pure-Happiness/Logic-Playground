#pragma once

#include "TipEIF.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipEIF : TipEIFT<TipEIF>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipEIF : TipEIFT<TipEIF, implementation::TipEIF>
    {
    };
}
