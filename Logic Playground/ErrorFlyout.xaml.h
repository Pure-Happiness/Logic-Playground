#pragma once

#include "ErrorFlyout.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct ErrorFlyout : ErrorFlyoutT<ErrorFlyout>
    {
        ErrorFlyout(IVectorView<Inline> CR _message, uint32_t CR _position, param::hstring CR _context);

        void MessageLoaded(IInspectable CR, RoutedEventArgs CR);
        void PositionLoaded(IInspectable CR, RoutedEventArgs CR);

    private:
        IVectorView<Inline> message;
    	hstring position;
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct ErrorFlyout : ErrorFlyoutT<ErrorFlyout, implementation::ErrorFlyout>
    {
    };
}
