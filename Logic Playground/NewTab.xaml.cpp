#include "pch.h"
#include "NewTab.xaml.h"
#if __has_include("NewTab.g.cpp")
#include "NewTab.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	void NewTab::Self(NewTabP CR _self)
	{
		self = _self;
	}

	TabViewItem NewTab::Position() const
	{
		return position.get();
	}

	void NewTab::Position(TabViewItem CR _position)
	{
		position = _position;
	}

	void NewTab::RemoveItem(UIElement CR _item)
	{
		const UIElementCollection items = recentFiles().Children();
		uint32_t index;
		items.IndexOf(_item, index);
		items.RemoveAt(index);
	}

	fire_and_forget NewTab::OpenFile(StorageFile CR _file)
	{
		const FileRoot root;
		root.Self(root);
		try
		{
			const hstring content = co_await root.InitAsFile(_file);
			GetMainWindow[position.get()].get().ChangePage(position.get(), root.PageRoot(), box_value(root.PageRoot().Header()));
			const ContentDialog dialog;
			dialog.XamlRoot(XamlRoot());
			dialog.Title(box_value(ResourceLoader().GetString(L"«Î…‘∫Ú°≠°≠")));
			dialog.ShowAsync();
			{
				const apartment_context ui;
				co_await resume_after(114514us);
				co_await ui;
			}
			root.ReadContent(content);
			dialog.Hide();
		}
		catch (...)
		{
			const Flyout flyout;
			flyout.Content(RegularText(ResourceLoader().GetString(L"OpenFileFailure")));
			flyout.ShowAt(top());
		}
	}

	void NewTab::LoadedEvent(IInspectable CR, RoutedEventArgs CR)
	{
		const UIElementCollection items = recentFiles().Children();
		items.Clear();
		for (auto CR[token, _] : StorageApplicationPermissions::MostRecentlyUsedList().Entries())
		{
			RecentListItemP item(token, self.get());
			item.Self(item);
			items.Append(item);
		}
	}

	void NewTab::NewFileClick(IInspectable CR, RoutedEventArgs CR) const
	{
		const FileRootP root;
		root.Self(root);
		root.InitAsNewFile();
		GetMainWindow[position.get()].get().ChangePage(position.get(), root.PageRoot(), box_value(root.PageRoot().Header()));
	}

	fire_and_forget NewTab::OpenFileClick(IInspectable CR, RoutedEventArgs CR)
	{
		try
		{
			const FileOpenPicker picker(GetMainWindow[position.get()].get().AppWindow().Id());
			picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			picker.FileTypeFilter().Append(L".logic");
			if (const PickFileResult result = co_await picker.PickSingleFileAsync())
				try
			{
				const StorageFile file = co_await StorageFile::GetFileFromPathAsync(result.Path());
				StorageApplicationPermissions::MostRecentlyUsedList().Add(file);
				OpenFile(file);
			}
			catch (...)
			{
				const Flyout flyout;
				flyout.Content(RegularText(ResourceLoader().GetString(L"OpenFileFailure")));
				flyout.ShowAt(top());
			}
		}
		catch (...)
		{
			const Flyout flyout;
			flyout.Content(RegularText(ResourceLoader().GetString(L"OpenFilePickerFailure")));
			flyout.ShowAt(top());
		}
	}

	void NewTab::SettingsClick(IInspectable CR, RoutedEventArgs CR) const
	{
		GetMainWindow[position.get()].get().OpenTab(SettingsP(), box_value(ResourceLoader().GetString(L"Settings")));
	}
}
