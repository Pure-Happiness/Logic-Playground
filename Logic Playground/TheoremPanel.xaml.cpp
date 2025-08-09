#include "pch.h"
#include "TheoremPanel.xaml.h"
#if __has_include("TheoremPanel.g.cpp")
#include "TheoremPanel.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	void TheoremPanel::Name(TheoremP CR _name)
	{
		定理名称().Child(name = _name);
		for (const UIElementCollection items = 定理内容().Children(); UIElement CR item : ObjP::Generate(name.Definition()))
			items.Append(item);
	}

	void TheoremPanel::ShowCopyName(IInspectable CR, RightTappedRoutedEventArgs CR)
	{
		const MenuFlyout menu;
		{
			const MenuFlyoutItem item;
			item.Text(ResourceLoader().GetString(L"Copy"));
			item.Click([this](IInspectable CR, RoutedEventArgs CR)
				{
					const DataPackage package;
					package.SetText(name.Label());
					Clipboard::SetContent(package);
				});
			menu.Items().Append(item);
		}
		menu.ShowAt(定理名称());
	}

	void TheoremPanel::ShowCopyContent(IInspectable CR, RightTappedRoutedEventArgs CR)
	{
		const MenuFlyout menu;
		{
			const MenuFlyoutItem item;
			item.Text(ResourceLoader().GetString(L"Copy"));
			item.Click([this](IInspectable CR, RoutedEventArgs CR)
				{
					const DataPackage package;
					package.SetText(ObjP::GenerateText(name.Definition()));
					Clipboard::SetContent(package);
				});
			menu.Items().Append(item);
		}
		menu.ShowAt(定理内容());
	}
}
