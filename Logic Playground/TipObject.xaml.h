#pragma once

#include "TipObject.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipObject : TipObjectT<TipObject>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipObject : TipObjectT<TipObject, implementation::TipObject>
    {
    };
}
