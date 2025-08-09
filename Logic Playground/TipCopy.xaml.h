#pragma once

#include "TipCopy.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipCopy : TipCopyT<TipCopy>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipCopy : TipCopyT<TipCopy, implementation::TipCopy>
    {
    };
}
