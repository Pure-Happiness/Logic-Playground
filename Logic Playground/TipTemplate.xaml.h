#pragma once

#include "TipTemplate.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipTemplate : TipTemplateT<TipTemplate>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipTemplate : TipTemplateT<TipTemplate, implementation::TipTemplate>
    {
    };
}
