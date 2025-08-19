#include "pch.h"
#include "FileRoot.h"
#if __has_include("FileRoot.g.cpp")
#include "FileRoot.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	void FileRoot::Self(FileRootP CR _self)
	{
		self = _self;
	}

	void FileRoot::InitAsNewFile() const
	{
		page_root.Self(page_root);
		page_root.Root(self.get());
		page_root.Header(ResourceLoader().GetString(L"未命名"));
		const BreadcrumbItem item(page_root, page_root);
		page_root.Path().Append(item);
	}

	IAsyncOperation<hstring> FileRoot::InitAsFile(StorageFile CR _file)
	{
		page_root.Self(page_root);
		page_root.Root(self.get());
		page_root.Header((file = _file).DisplayName());
		const BreadcrumbItem item(page_root, page_root);
		page_root.Path().Append(item);
		return FileIO::ReadTextAsync(file);
	}

	fire_and_forget FileRoot::ReadContent(hstring CR _content)
	{
		recover = {};
		wistringstream input{ wstring(_content) };
		while (true)
		{
			wstring line;
			if (!getline(input, line))
			{
				if (file)
				{
					wstring fr(co_await FileIO::ReadTextAsync(file));
					auto CR[ret, last] = ranges::remove(fr, L'\r');
					fr.erase(ret, last);
					if (content == fr)
						co_return;
				}
				if (!temp_file)
					CreateTempFile();
				else
					FileIO::WriteTextAsync(temp_file, content);
				co_return;
			}
			if (const OperationP operation = focus.ParseOperation(line))
			{
				operations.push(operation);
				wstring result = array{ L"Object", L"Type", L"Copy", L"Function", L"Template", L"EI", L"EIB", L"EIF", L"EIT", L"EE", L"EEB", L"ET", L"ER", L"C0", L"C1", L"C2", L"C3", L"UF", L"UT", L"Scope", L"Assume", L"ArbitraryObject", L"ArbitraryType", L"Export", L"Exit" }[static_cast<size_t>(operation.Category())];
				for (hstring CR s : operation.Contents())
					result.append(L" ").append(s);
				result.append(L"\n");
				content.append(result);
			}
			else
				goto Error;
		}
	Error:
		AppNotificationManager::Default().Show(AppNotificationBuilder().AddText(ResourceLoader().GetString(L"文件读取错误")).BuildNotification());
	}

	MainPageP FileRoot::PageRoot() const
	{
		return page_root;
	}

	MainPageP FileRoot::Focus() const
	{
		return focus;
	}

	void FileRoot::Focus(MainPageP CR _focus)
	{
		focus = _focus;
	}

	void FileRoot::AddOperationS(OperationP CR _operation)
	{
		recover = {};
		operations.push(_operation);
		wstring result = array{ L"Object", L"Type", L"Copy", L"Function", L"Template", L"EI", L"EIB", L"EIF", L"EIT", L"EE", L"EEB", L"ET", L"ER", L"C0", L"C1", L"C2", L"C3", L"UF", L"UT", L"Scope", L"Assume", L"ArbitraryObject", L"ArbitraryType", L"Export", L"Exit" } [static_cast<size_t>(_operation.Category())] ;
		for (hstring CR s : _operation.Contents())
			result.append(L" ").append(s);
		result.append(L"\n");
		content.append(result);
		if (!temp_file)
			CreateTempFile();
		else
			FileIO::AppendTextAsync(temp_file, result);
	}

	IAsyncAction FileRoot::Save(TabViewItem CR _position)
	{
		if (!file)
			try
		{
			if (!co_await FetchFile(_position))
				co_return;
		}
		catch (...)
		{
			AppNotificationManager::Default().Show(AppNotificationBuilder().AddText(ResourceLoader().GetString(L"OpenFilePickerFailure")).BuildNotification());
		}
		SaveFile();
	}

	fire_and_forget FileRoot::SaveAs(TabViewItem CR _position)
	{
		try
		{
			if (!co_await FetchFile(_position))
				co_return;
		}
		catch (...)
		{
			AppNotificationManager::Default().Show(AppNotificationBuilder().AddText(ResourceLoader().GetString(L"OpenFilePickerFailure")).BuildNotification());
		}
		SaveFile();
	}

	void FileRoot::Undo()
	{
		if (!operations.empty())
		{
			const OperationP operation = operations.top();
			operations.pop();
			recover.push(operation);
			do
				content.pop_back();
			while (!content.empty() && content.back() != L'\n');
			if (!temp_file)
				CreateTempFile();
			else
				FileIO::WriteTextAsync(temp_file, content);
			switch (const IVector contents = operation.Contents(); operation.Category())
			{
			case OperationCategory::Object:
				focus.RemoveObject(*contents.First());
				break;
			case OperationCategory::Type:
				focus.RemoveType(*contents.First());
				break;
			case OperationCategory::Scope:
			case OperationCategory::Assume:
			case OperationCategory::ArbitraryO:
			case OperationCategory::ArbitraryT:
				focus.RemoveScope();
				break;
			case OperationCategory::Export:
				focus.RemoveExport(*contents.First());
				break;
			case OperationCategory::Exit:
				focus.RemoveExit();
				break;
			default:
				focus.RemoveTheorem(*contents.First());
			}
		}
	}

	void FileRoot::Redo()
	{
		if (!recover.empty())
		{
			const OperationP operation = recover.top();
			recover.pop();
			operations.push(operation);
			focus.RedoOperation(operation);
			wstring result = array{ L"Object", L"Type", L"Copy", L"Function", L"Template", L"EI", L"EIB", L"EIF", L"EIT", L"EE", L"EEB", L"ET", L"ER", L"C0", L"C1", L"C2", L"C3", L"UF", L"UT", L"Scope", L"Assume", L"ArbitraryObject", L"ArbitraryType", L"Export", L"Exit" }[static_cast<size_t>(operation.Category())];
			for (hstring CR s : operation.Contents())
				result.append(L" ").append(s);
			result.append(L"\n");
			content.append(result);
			if (!temp_file)
				CreateTempFile();
			else
				FileIO::WriteTextAsync(temp_file, content);
		}
	}

	void FileRoot::Add()
	{
		++count;
	}

	void FileRoot::JustRelease()
	{
		--count;
	}

	bool FileRoot::TryRelease(TabViewItem CR _position, Func CR op)
	{
		if (--count || !temp_file)
			return true;
		const ContentDialog confirm;
		confirm.XamlRoot(_position.XamlRoot());
		confirm.Title(box_value(ResourceLoader().GetString(L"是否保存")));
		confirm.PrimaryButtonText(ResourceLoader().GetString(L"是"));
		confirm.PrimaryButtonClick([this, _position, op](ContentDialog CR, ContentDialogButtonClickEventArgs CR)->fire_and_forget
			{
				const Func alive_op = op;
				co_await Save(_position);
				alive_op();
			});
		confirm.SecondaryButtonText(ResourceLoader().GetString(L"否"));
		confirm.SecondaryButtonClick([op](ContentDialog CR, ContentDialogButtonClickEventArgs CR)
			{
				op();
			});
		confirm.CloseButtonText(ResourceLoader().GetString(L"取消"));
		confirm.CloseButtonClick([this](ContentDialog CR, ContentDialogButtonClickEventArgs CR)
			{
				++count;
			});
		confirm.DefaultButton(ContentDialogButton::Primary);
		confirm.ShowAsync();
		return false;
	}

	IAsyncOperation<bool> FileRoot::FetchFile(TabViewItem CR _position)
	{
		const FileSavePicker picker(GetMainWindow[_position].get().AppWindow().Id());
		picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
		{
			const IVector vec = single_threaded_vector<hstring>();
			vec.Append(L".logic");
			picker.FileTypeChoices().Insert(L"Logic Playground File", vec);
		}
		if (const PickFileResult result = co_await picker.PickSaveFileAsync())
			try
		{
			StorageApplicationPermissions::MostRecentlyUsedList().Add(file = co_await StorageFile::GetFileFromPathAsync(result.Path()));
			co_return true;
		}
		catch (...)
		{
			AppNotificationManager::Default().Show(AppNotificationBuilder().AddText(ResourceLoader().GetString(L"OpenFileFailure")).BuildNotification());
			co_return false;
		}
		co_return false;
	}

	void FileRoot::SaveFile()
	{
		try
		{
			FileIO::WriteTextAsync(file, content);
		}
		catch (...)
		{
			AppNotificationManager::Default().Show(AppNotificationBuilder().AddText(ResourceLoader().GetString(L"无法写入文件")).BuildNotification());
		}
		if (temp_file)
		{
			ApplicationData::GetDefault().LocalSettings().CreateContainer(L"ProtectiveSave", ApplicationDataCreateDisposition::Always).Values().Remove(edit_time);
			temp_file.DeleteAsync();
			temp_file = nullptr;
		}
	}

	IAsyncAction FileRoot::CreateTempFile()
	{
	loop:
		try
		{
			const hstring save_path = to_hstring(GetRandom()) + L".logic", p = (file ? file.Path() : hstring()) + L"?" + save_path;
			temp_file = co_await ApplicationData::GetDefault().LocalFolder().CreateFileAsync(save_path, CreationCollisionOption::FailIfExists);
			const Calendar t;
			t.SetToNow();
			ApplicationData::GetDefault().LocalSettings().CreateContainer(L"ProtectiveSave", ApplicationDataCreateDisposition::Always).Values().Insert(
				edit_time = t.YearAsPaddedString(4) + L'-' + t.MonthAsPaddedNumericString(2) + L'-' + t.DayAsPaddedString(2) + L' ' + t.HourAsPaddedString(2) + L':' + t.MinuteAsPaddedString(2) + L':' + t.SecondAsPaddedString(2),
				box_value(p));
		}
		catch (...)
		{
			goto loop;
		}
		co_await FileIO::WriteTextAsync(temp_file, content);
	}
}
