#pragma once

#include "TipExport.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipExport : TipExportT<TipExport>
    {
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipExport : TipExportT<TipExport, implementation::TipExport>
    {
    };
}
