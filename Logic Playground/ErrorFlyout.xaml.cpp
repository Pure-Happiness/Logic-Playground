#include "pch.h"
#include "ErrorFlyout.xaml.h"
#if __has_include("ErrorFlyout.g.cpp")
#include "ErrorFlyout.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	ErrorFlyout::ErrorFlyout(IVectorView<Inline> CR _message, uint32_t CR _position, param::hstring CR _context) :ErrorFlyoutT(), message(_message), position(to_hstring(_position) + L' ' + _context)
	{
	}

	void ErrorFlyout::MessageLoaded(IInspectable CR, RoutedEventArgs CR)
	{
		for (Inline CR item : message)
			¥ÌŒÛœ˚œ¢().Inlines().Append(item);
	}

	void ErrorFlyout::PositionLoaded(IInspectable CR, RoutedEventArgs CR)
	{
		¥ÌŒÛŒª÷√().Text(position);
	}
}
