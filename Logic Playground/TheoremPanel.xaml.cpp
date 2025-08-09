#include "pch.h"
#include "TheoremPanel.xaml.h"
#if __has_include("TheoremPanel.g.cpp")
#include "TheoremPanel.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	void TheoremPanel::Name(TheoremP CR _name)
	{
		��������().Child(name = _name);
		for (const UIElementCollection items = ��������().Children(); UIElement CR item : ObjP::Generate(name.Definition()))
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
		menu.ShowAt(��������());
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
		menu.ShowAt(��������());
	}
}
