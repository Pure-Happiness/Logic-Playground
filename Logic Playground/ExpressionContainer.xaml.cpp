#include "pch.h"
#include "ExpressionContainer.xaml.h"
#if __has_include("ExpressionContainer.g.cpp")
#include "ExpressionContainer.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	void ExpressionContainer::Text(param::hstring CR _text)
	{
		text = _text;
	}

	UIElementCollection ExpressionContainer::Items()
	{
		return items().Children();
	}

	void ExpressionContainer::ShowCopy(IInspectable CR, RightTappedRoutedEventArgs CR)
	{
		const MenuFlyout menu;
		{
			const MenuFlyoutItem item;
			item.Text(ResourceLoader().GetString(L"Copy"));
			item.Click([this](IInspectable CR, RoutedEventArgs CR)
				{
					const DataPackage package;
					package.SetText(text);
					Clipboard::SetContent(package);
				});
			menu.Items().Append(item);
		}
		menu.ShowAt(items());
	}
}
