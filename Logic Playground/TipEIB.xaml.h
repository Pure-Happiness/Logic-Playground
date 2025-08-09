#pragma once

#include "TipEIB.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipEIB : TipEIBT<TipEIB>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipEIB : TipEIBT<TipEIB, implementation::TipEIB>
    {
    };
}
