#pragma once

#include "TipArbitraryType.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipArbitraryType : TipArbitraryTypeT<TipArbitraryType>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipArbitraryType : TipArbitraryTypeT<TipArbitraryType, implementation::TipArbitraryType>
    {
    };
}
