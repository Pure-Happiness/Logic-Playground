#pragma once

#include "TipC0.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipC0 : TipC0T<TipC0>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipC0 : TipC0T<TipC0, implementation::TipC0>
    {
    };
}
