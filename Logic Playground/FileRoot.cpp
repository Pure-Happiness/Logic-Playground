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

	fire_and_forget FileRoot::ReadContent(hstring _content)
	{
		{
			const apartment_context ui;
			co_await resume_after(114514us);
			co_await ui;
		}
		wistringstream input{ wstring(_content) };
		while (true)
		{
			wstring op;
			input >> op;
			if (input.fail())
			{
				if (file && temp_file && content == co_await FileIO::ReadTextAsync(file))
				{
					ApplicationData::GetDefault().LocalSettings().CreateContainer(L"ProtectiveSave", ApplicationDataCreateDisposition::Always).Values().Remove(edit_time);
					temp_file.DeleteAsync();
					temp_file = nullptr;
				}
				co_return;
			}
			try
			{
				if (op == L"Object")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring name;
					input >> name;
					if (input.fail() || !CheckIllegal(name, IsValidName))
						goto Error;
					wstring expression;
					input >> expression;
					if (input.fail() || !CheckIllegal(expression) || !co_await focus.OperationObject(ID, name, expression, false))
						goto Error;
				}
				else if (op == L"Type")
				{
					wstring name;
					input >> name;
					if (input.fail() || !CheckIllegal(name, IsValidName))
						goto Error;
					wstring expression;
					input >> expression;
					if (input.fail() || !CheckIllegal(expression, IsValidTypeExpression) || !co_await focus.OperationType(name, expression, false))
						goto Error;
				}
				else if (op == L"Copy")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id) || !co_await focus.OperationCopy(ID, id, false))
						goto Error;
				}
				else if (op == L"Function")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring param;
					input >> param;
					if (input.fail() || !CheckIllegal(param, IsValidName))
						goto Error;
					wstring image;
					input >> image;
					if (input.fail() || !CheckIllegal(image))
						goto Error;
					wstring arg;
					input >> arg;
					if (input.fail() || !CheckIllegal(arg) || !co_await focus.OperationFunction(ID, param, image, arg, false))
						goto Error;
				}
				else if (op == L"Template")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring param;
					input >> param;
					if (input.fail() || !CheckIllegal(param, IsValidName))
						goto Error;
					wstring image;
					input >> image;
					if (input.fail() || !CheckIllegal(image))
						goto Error;
					wstring arg;
					input >> arg;
					if (input.fail() || !CheckIllegal(arg, IsValidTypeExpression) || !co_await focus.OperationTemplate(ID, param, image, arg, false))
						goto Error;
				}
				else if (op == L"EI")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring a;
					input >> a;
					if (input.fail() || !CheckIllegal(a) || !co_await focus.OperationEI(ID, a, false))
						goto Error;
				}
				else if (op == L"EIB")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id) || !co_await focus.OperationEIB(ID, id, false))
						goto Error;
				}
				else if (op == L"EIF")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id) || !co_await focus.OperationEIF(ID, id, false))
						goto Error;
				}
				else if (op == L"EIT")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id) || !co_await focus.OperationEIT(ID, id, false))
						goto Error;
				}
				else if (op == L"EE")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id))
						goto Error;
					wstring f;
					input >> f;
					if (input.fail() || !CheckIllegal(f) || !co_await focus.OperationEE(ID, id, f, false))
						goto Error;
				}
				else if (op == L"EEB")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id) || !co_await focus.OperationEEB(ID, id, false))
						goto Error;
				}
				else if (op == L"ET")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring idA;
					input >> idA;
					if (input.fail() || !CheckIllegal(idA))
						goto Error;
					wstring idB;
					input >> idB;
					if (input.fail() || !CheckIllegal(idB) || !co_await focus.OperationET(ID, idA, idB, false))
						goto Error;
				}
				else if (op == L"ER")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id) || !co_await focus.OperationER(ID, id, false))
						goto Error;
				}
				else if (op == L"C0")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id))
						goto Error;
					wstring a;
					input >> a;
					if (input.fail() || !CheckIllegal(a))
						goto Error;
					wstring b;
					input >> b;
					if (input.fail() || !CheckIllegal(b) || !co_await focus.OperationC0(ID, id, a, b, false))
						goto Error;
				}
				else if (op == L"C1")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id))
						goto Error;
					wstring a;
					input >> a;
					if (input.fail() || !CheckIllegal(a))
						goto Error;
					wstring b;
					input >> b;
					if (input.fail() || !CheckIllegal(b) || !co_await focus.OperationC1(ID, id, a, b, false))
						goto Error;
				}
				else if (op == L"C2")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring idA;
					input >> idA;
					if (input.fail() || !CheckIllegal(idA))
						goto Error;
					wstring idB;
					input >> idB;
					if (input.fail() || !CheckIllegal(idB) || !co_await focus.OperationC2(ID, idA, idB, false))
						goto Error;
				}
				else if (op == L"C3")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id) || !co_await focus.OperationC3(ID, id, false))
						goto Error;
				}
				else if (op == L"UF")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id))
						goto Error;
					wstring a;
					input >> a;
					if (input.fail() || !CheckIllegal(a) || !co_await focus.OperationUF(ID, id, a, false))
						goto Error;
				}
				else if (op == L"UT")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring id;
					input >> id;
					if (input.fail() || !CheckIllegal(id))
						goto Error;
					wstring t;
					input >> t;
					if (input.fail() || !CheckIllegal(t, IsValidTypeExpression) || !co_await focus.OperationUT(ID, id, t, false))
						goto Error;
				}
				else if (op == L"Scope")
				{
					wstring NAME;
					input >> NAME;
					if (input.fail() || !CheckIllegal(NAME) || !co_await focus.OperationScope(NAME, false))
						goto Error;
				}
				else if (op == L"Assume")
				{
					wstring NAME;
					input >> NAME;
					if (input.fail() || !CheckIllegal(NAME))
						goto Error;
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID))
						goto Error;
					wstring p;
					input >> p;
					if (input.fail() || !CheckIllegal(p) || !co_await focus.OperationAssume(NAME, ID, p, false))
						goto Error;
				}
				else if (op == L"ArbitraryObject")
				{
					wstring NAME;
					input >> NAME;
					if (input.fail() || !CheckIllegal(NAME))
						goto Error;
					wstring name;
					input >> name;
					if (input.fail() || !CheckIllegal(name, IsValidName))
						goto Error;
					wstring t;
					input >> t;
					if (input.fail() || !CheckIllegal(t, IsValidTypeExpression) || !co_await focus.OperationArbitraryObject(NAME, name, t, false))
						goto Error;
				}
				else if (op == L"ArbitraryType")
				{
					wstring NAME;
					input >> NAME;
					if (input.fail() || !CheckIllegal(NAME))
						goto Error;
					wstring name;
					input >> name;
					if (input.fail() || !CheckIllegal(name, IsValidName) || !co_await focus.OperationArbitraryType(NAME, name, false))
						goto Error;
				}
				else if (op == L"Export")
				{
					wstring ID;
					input >> ID;
					if (input.fail() || !CheckIllegal(ID) || !co_await focus.OperationExport(ID, false))
						goto Error;
				}
				else if (op == L"Exit")
				{
					if (!co_await focus.OperationExit(false))
						goto Error;
				}
				else
					goto Error;
			}
			catch (...)
			{
				AppNotificationManager::Default().Show(AppNotificationBuilder().AddText(ResourceLoader().GetString(L"未知错误")).BuildNotification());
			}
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

	IAsyncAction FileRoot::AddOperation(const OperationP _operation, const bool redo)
	{
		if (!temp_file)
			co_await CreateTempFile();
		if (!redo)
			recover = {};
		operations.push(_operation);
		wstring result;
		result.append(array{
				L"Object", L"Type",
				L"Copy",
				L"Function", L"Template",
				L"EI", L"EIB", L"EIF", L"EIT", L"EE", L"EEB", L"ET", L"ER",
				L"C0", L"C1", L"C2", L"C3",
				L"UF", L"UT",
				L"Scope", L"Assume", L"ArbitraryObject", L"ArbitraryType", L"Export", L"Exit"
			} [static_cast<size_t>(_operation.Category())] );
		for (hstring CR s : _operation.Contents())
			result.append(L" ").append(s);
		result.append(L"\n");
		content.append(result);
		co_await FileIO::AppendTextAsync(temp_file, result);
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
				focus.RemoveObject(contents.GetAt(0), contents.GetAt(1));
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
			switch (const IVector contents = operation.Contents(); operation.Category())
			{
			case OperationCategory::Object:
				focus.OperationObject(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), true);
				break;
			case OperationCategory::Type:
				focus.OperationType(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::Copy:
				focus.OperationCopy(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::Function:
				focus.OperationFunction(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), contents.GetAt(3), true);
				break;
			case OperationCategory::Template:
				focus.OperationTemplate(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), contents.GetAt(3), true);
				break;
			case OperationCategory::EI:
				focus.OperationEI(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::EIB:
				focus.OperationEIB(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::EIF:
				focus.OperationEIF(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::EIT:
				focus.OperationEIT(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::EE:
				focus.OperationEE(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), true);
				break;
			case OperationCategory::EEB:
				focus.OperationEEB(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::ET:
				focus.OperationET(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), true);
				break;
			case OperationCategory::ER:
				focus.OperationER(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::C0:
				focus.OperationC0(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), contents.GetAt(3), true);
				break;
			case OperationCategory::C1:
				focus.OperationC1(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), contents.GetAt(3), true);
				break;
			case OperationCategory::C2:
				focus.OperationC2(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), true);
				break;
			case OperationCategory::C3:
				focus.OperationC3(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::UF:
				focus.OperationUF(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), true);
				break;
			case OperationCategory::UT:
				focus.OperationUT(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), true);
				break;
			case OperationCategory::Scope:
				focus.OperationScope(contents.GetAt(0), true);
				break;
			case OperationCategory::Assume:
				focus.OperationAssume(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), true);
				break;
			case OperationCategory::ArbitraryO:
				focus.OperationArbitraryObject(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), true);
				break;
			case OperationCategory::ArbitraryT:
				focus.OperationArbitraryType(contents.GetAt(0), contents.GetAt(1), true);
				break;
			case OperationCategory::Export:
				focus.OperationExport(contents.GetAt(0), true);
				break;
			case OperationCategory::Exit:
				focus.OperationExit(true);
			}
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

	bool FileRoot::CheckIllegal(wstring CR s)
	{
		for (auto CR c : s)
			if (c <= L' ')
				return false;
		return true;
	}

	bool FileRoot::CheckIllegal(wstring CR s, auto CR check)
	{
		for (auto CR c : s)
			if (!check(c))
				return false;
		return true;
	}
}
