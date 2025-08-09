#pragma once

#include "TipFunction.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipFunction : TipFunctionT<TipFunction>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipFunction : TipFunctionT<TipFunction, implementation::TipFunction>
    {
    };
}
