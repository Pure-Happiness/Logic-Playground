#pragma once

#include "TipET.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct TipET : TipETT<TipET>
    {
        TipET()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct TipET : TipETT<TipET, implementation::TipET>
    {
    };
}
