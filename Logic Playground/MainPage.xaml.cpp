#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	void MainPage::Self(MainPageP CR _self)
	{
		self = _self;
	}

	TabViewItem MainPage::Position() const
	{
		return position.get();
	}

	void MainPage::Position(TabViewItem CR _position)
	{
		position = _position;
	}

	void MainPage::Parent(MainPageP CR _parent)
	{
		parent = _parent;
		objects.Parent(_parent.Objects());
		types.Parent(_parent.Types());
		theorems.Parent(_parent.Theorems());
		��һ��().IsEnabled(true);
	}

	FileRootP MainPage::Root() const
	{
		return root.get();
	}

	void MainPage::Root(FileRootP CR _root)
	{
		root = _root;
	}

	hstring MainPage::Header() const
	{
		return header;
	}

	void MainPage::Header(param::hstring CR _header)
	{
		header = _header;
	}

	void MainPage::InitAsAssume(TheoremP CR _assumption, TheoremPanelP CR _panel)
	{
		category = ScopeCategory::Assume;
		theorems.Insert(_assumption.Label(), assumption = _assumption);
		�����().Children().Append(_panel);
	}

	void MainPage::InitAsArbitraryO(ObjP CR _aO)
	{
		category = ScopeCategory::Object;
		objects.Insert(_aO.Label(), aO = _aO);
	}

	void MainPage::InitAsArbitraryT(TypeP CR _aT)
	{
		category = ScopeCategory::Type;
		types.Insert(_aT.Label(), aT = _aT);
	}

	OperationP MainPage::ParseOperation(param::hstring CR str)
	{
		wistringstream input{ wstring(hstring(str)) };
		wstring op;
		input >> op;
		if (input.fail())
			return nullptr;
		try
		{
			if (op == L"Object")
			{
				wstring name;
				input >> name;
				if (input.fail() || !CheckIllegal(name, IsValidName))
					return nullptr;
				wstring expression;
				input >> expression;
				if (input.fail() || !CheckIllegal(expression))
					return nullptr;
				return OperationObject(name, expression);
			}
			if (op == L"Type")
			{
				wstring name;
				input >> name;
				if (input.fail() || !CheckIllegal(name, IsValidName))
					return nullptr;
				wstring expression;
				input >> expression;
				if (input.fail() || !CheckIllegal(expression, IsValidTypeExpression))
					return nullptr;
				return OperationType(name, expression);
			}
			if (op == L"Copy")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				return OperationCopy(ID, id);
			}
			if (op == L"Function")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring param;
				input >> param;
				if (input.fail() || !CheckIllegal(param, IsValidName))
					return nullptr;
				wstring image;
				input >> image;
				if (input.fail() || !CheckIllegal(image))
					return nullptr;
				wstring arg;
				input >> arg;
				if (input.fail() || !CheckIllegal(arg))
					return nullptr;
				return OperationFunction(ID, param, image, arg);
			}
			if (op == L"Template")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring param;
				input >> param;
				if (input.fail() || !CheckIllegal(param, IsValidName))
					return nullptr;
				wstring image;
				input >> image;
				if (input.fail() || !CheckIllegal(image))
					return nullptr;
				wstring arg;
				input >> arg;
				if (input.fail() || !CheckIllegal(arg, IsValidTypeExpression))
					return nullptr;
				return OperationTemplate(ID, param, image, arg);
			}
			if (op == L"EI")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring a;
				input >> a;
				if (input.fail() || !CheckIllegal(a))
					return nullptr;
				return OperationEI(ID, a);
			}
			if (op == L"EIB")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				return OperationEIB(ID, id);
			}
			if (op == L"EIF")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				return OperationEIF(ID, id);
			}
			if (op == L"EIT")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				return OperationEIT(ID, id);
			}
			if (op == L"EE")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				wstring f;
				input >> f;
				if (input.fail() || !CheckIllegal(f))
					return nullptr;
				return OperationEE(ID, id, f);
			}
			if (op == L"EEB")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				return OperationEEB(ID, id);
			}
			if (op == L"ET")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring idA;
				input >> idA;
				if (input.fail() || !CheckIllegal(idA))
					return nullptr;
				wstring idB;
				input >> idB;
				if (input.fail() || !CheckIllegal(idB))
					return nullptr;
				return OperationET(ID, idA, idB);
			}
			if (op == L"ER")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				return OperationER(ID, id);
			}
			if (op == L"C0")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				wstring a;
				input >> a;
				if (input.fail() || !CheckIllegal(a))
					return nullptr;
				wstring b;
				input >> b;
				if (input.fail() || !CheckIllegal(b))
					return nullptr;
				return OperationC0(ID, id, a, b);
			}
			if (op == L"C1")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				wstring a;
				input >> a;
				if (input.fail() || !CheckIllegal(a))
					return nullptr;
				wstring b;
				input >> b;
				if (input.fail() || !CheckIllegal(b))
					return nullptr;
				return OperationC1(ID, id, a, b);
			}
			if (op == L"C2")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring idA;
				input >> idA;
				if (input.fail() || !CheckIllegal(idA))
					return nullptr;
				wstring idB;
				input >> idB;
				if (input.fail() || !CheckIllegal(idB))
					return nullptr;
				return OperationC2(ID, idA, idB);
			}
			if (op == L"C3")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				return OperationC3(ID, id);
			}
			if (op == L"UF")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				wstring a;
				input >> a;
				if (input.fail() || !CheckIllegal(a))
					return nullptr;
				return OperationUF(ID, id, a);
			}
			if (op == L"UT")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring id;
				input >> id;
				if (input.fail() || !CheckIllegal(id))
					return nullptr;
				wstring t;
				input >> t;
				if (input.fail() || !CheckIllegal(t, IsValidTypeExpression))
					return nullptr;
				return OperationUT(ID, id, t);
			}
			if (op == L"Scope")
			{
				wstring NAME;
				input >> NAME;
				if (input.fail() || !CheckIllegal(NAME))
					return nullptr;
				return OperationScope(NAME);
			}
			if (op == L"Assume")
			{
				wstring NAME;
				input >> NAME;
				if (input.fail() || !CheckIllegal(NAME))
					return nullptr;
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				wstring p;
				input >> p;
				if (input.fail() || !CheckIllegal(p))
					return nullptr;
				return OperationAssume(NAME, ID, p);
			}
			if (op == L"ArbitraryObject")
			{
				wstring NAME;
				input >> NAME;
				if (input.fail() || !CheckIllegal(NAME))
					return nullptr;
				wstring name;
				input >> name;
				if (input.fail() || !CheckIllegal(name, IsValidName))
					return nullptr;
				wstring t;
				input >> t;
				if (input.fail() || !CheckIllegal(t, IsValidTypeExpression))
					return nullptr;
				return OperationArbitraryObject(NAME, name, t);
			}
			if (op == L"ArbitraryType")
			{
				wstring NAME;
				input >> NAME;
				if (input.fail() || !CheckIllegal(NAME))
					return nullptr;
				wstring name;
				input >> name;
				if (input.fail() || !CheckIllegal(name, IsValidName))
					return nullptr;
				return OperationArbitraryType(NAME, name);
			}
			if (op == L"Export")
			{
				wstring ID;
				input >> ID;
				if (input.fail() || !CheckIllegal(ID))
					return nullptr;
				return OperationExport(ID);
			}
			if (op == L"Exit")
				return OperationExit();
			error_flyout.Content(RegularText(ResourceLoader().GetString(L"δ֪����")));
			return nullptr;
		}
		catch (...)
		{
			return nullptr;
		}
	}

	OperationP MainPage::RedoOperation(OperationP CR operation)
	{
		switch (const IVector contents = operation.Contents(); operation.Category())
		{
		case OperationCategory::Object:
			return OperationObject(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::Type:
			return OperationType(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::Copy:
			return OperationCopy(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::Function:
			return OperationFunction(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), contents.GetAt(3));
		case OperationCategory::Template:
			return OperationTemplate(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), contents.GetAt(3));
		case OperationCategory::EI:
			return OperationEI(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::EIB:
			return OperationEIB(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::EIF:
			return OperationEIF(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::EIT:
			return OperationEIT(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::EE:
			return OperationEE(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2));
		case OperationCategory::EEB:
			return OperationEEB(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::ET:
			return OperationET(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2));
		case OperationCategory::ER:
			return OperationER(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::C0:
			return OperationC0(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), contents.GetAt(3));
		case OperationCategory::C1:
			return OperationC1(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2), contents.GetAt(3));
		case OperationCategory::C2:
			return OperationC2(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2));
		case OperationCategory::C3:
			return OperationC3(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::UF:
			return OperationUF(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2));
		case OperationCategory::UT:
			return OperationUT(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2));
		case OperationCategory::Scope:
			return OperationScope(contents.GetAt(0));
		case OperationCategory::Assume:
			return OperationAssume(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2));
		case OperationCategory::ArbitraryO:
			return OperationArbitraryObject(contents.GetAt(0), contents.GetAt(1), contents.GetAt(2));
		case OperationCategory::ArbitraryT:
			return OperationArbitraryType(contents.GetAt(0), contents.GetAt(1));
		case OperationCategory::Export:
			return OperationExport(contents.GetAt(0));
		case OperationCategory::Exit:
			return OperationExit();
		}
	}

	void MainPage::RemoveObject(param::hstring CR _name)
	{
		objects.Remove(_name);
		�����().Children().RemoveAtEnd();
	}

	void MainPage::RemoveType(param::hstring CR _name)
	{
		types.Remove(_name);
		�����().Children().RemoveAtEnd();
	}

	void MainPage::RemoveTheorem(param::hstring CR _name)
	{
		theorems.Remove(_name);
		const UIElementCollection items = �����().Children();
		items.RemoveAtEnd(), items.RemoveAtEnd();
	}

	void MainPage::RemoveScope() const
	{
		const MainPageP pa = parent.get();
		root.get().Focus(pa);
		pa.RemoveScope2(header);
		if (pa.Position())
		{
			pa.Display();
			if (pa.Position() != position.get())
				GetMainWindow[position.get()].get().CloseTab(position.get());
		}
		else
			GetMainWindow[position.get()].get().ChangePage(position.get(), pa, box_value(pa.Header()));
	}

	void MainPage::RemoveExport(param::hstring CR _name)
	{
		to_export.pop_back();
		exported.erase(_name);
		�����().Children().RemoveAtEnd();
	}

	void MainPage::RemoveExit()
	{
		const UIElementCollection items = �����().Children();
		while (const auto thp = (*prev(items.end())).try_as<TheoremPanelP>())
		{
			theorems.Remove(thp.Content().as<ScrollView>().Content().as<StackPanel>().Children().GetAt(0).as<Border>().Child().as<TheoremP>().Label());
			items.RemoveAtEnd();
		}
		const hstring name = unbox_value<hstring>((*prev(items.end())).as<ExpressionContainerP>().Content().as<ScrollView>().Content().as<StackPanel>().Children().GetAt(1).as<Button>().Content());
		const MainPageP child = children[name];
		root.get().Focus(child);
		if (child.Position())
			child.Display();
		else
			GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
	}

	void MainPage::AddTheorem(TheoremP CR theorem, TheoremPanelP CR panel)
	{
		theorems.Insert(theorem.Label(), theorem);
		�����().Children().Append(panel);
	}

	void MainPage::RemoveScope2(param::hstring CR _name)
	{
		children.erase(_name);
		�����().Children().RemoveAtEnd();
	}

	IVectorView<MainPageP> MainPage::Children() const
	{
		const IVector<MainPageP> result = single_threaded_vector<MainPageP>();
		for (MainPageP CR child : children | views::values)
			result.Append(child);
		return result.GetView();
	}

	UIElementCollection MainPage::Path()
	{
		return ·��().Children();
	}

	LinkedMapP MainPage::Objects() const
	{
		return objects;
	}

	LinkedMapP MainPage::Types() const
	{
		return types;
	}

	LinkedMapP MainPage::Theorems() const
	{
		return theorems;
	}

	void MainPage::Display() const
	{
		GetMainWindow[position.get()].get().Display(position.get());
	}

	fire_and_forget MainPage::Display(UIElement _item)
	{
		GetMainWindow[position.get()].get().Display(position.get());
		{
			const apartment_context ui;
			co_await resume_after(114514us);
			co_await ui;
		}
		auto CR[x, y] = _item.TransformToVisual(�����()).TransformPoint({ 0, 0 });
		��().ScrollTo(x, y - 16);
	}

	void MainPage::MoveToParent(IInspectable CR, RoutedEventArgs CR) const
	{
		if (const MainPageP page = parent.get(); page.Position())
			page.Display();
		else
			GetMainWindow[position.get()].get().ChangePage(position.get(), page, box_value(page.Header()));
	}

	void MainPage::ParentMiddleClick(IInspectable CR, PointerRoutedEventArgs CR args)
	{
		if (args.GetCurrentPoint(��һ��()).Properties().IsMiddleButtonPressed())
			if (const MainPageP page = parent.get(); page.Position())
				page.Display();
			else
				GetMainWindow[position.get()].get().OpenTab(page, box_value(page.Header()));
	}

	void MainPage::ParentRightClick(IInspectable CR, RightTappedRoutedEventArgs CR)
	{
		if (const MainPageP page = parent.get(); page.Position())
		{
			const MenuFlyout flyout;
			{
				const MenuFlyoutItem item;
				item.Text(ResourceLoader().GetString(L"��������һ��"));
				item.Click([page](IInspectable CR, RoutedEventArgs CR)
					{
						page.Display();
					});
				flyout.Items().Append(item);
			}
			flyout.ShowAt(��һ��());
		}
		else
		{
			const MenuFlyout flyout;
			{
				const MenuFlyoutItem item;
				item.Text(ResourceLoader().GetString(L"Open here"));
				item.Click([this, page](IInspectable CR, RoutedEventArgs CR)
					{
						GetMainWindow[position.get()].get().ChangePage(position.get(), page, box_value(page.Header()));
					});
				flyout.Items().Append(item);
			}
			{
				const MenuFlyoutItem item;
				item.Text(ResourceLoader().GetString(L"Open in new tab"));
				item.Click([this, page](IInspectable CR, RoutedEventArgs CR)
					{
						GetMainWindow[position.get()].get().OpenTab(page, box_value(page.Header()));
					});
				flyout.Items().Append(item);
			}
			flyout.ShowAt(��һ��());
		}
	}

	void MainPage::OpenSettings(IInspectable CR, RoutedEventArgs CR) const
	{
		GetMainWindow[position.get()].get().OpenTab(SettingsP(), box_value(ResourceLoader().GetString(L"Settings")));
	}

	void MainPage::SaveClick(IInspectable CR, RoutedEventArgs CR) const
	{
		root.get().Save(position.get());
	}

	void MainPage::SaveAsClick(IInspectable CR, RoutedEventArgs CR) const
	{
		root.get().SaveAs(position.get());
	}

	void MainPage::UndoClick(IInspectable CR, RoutedEventArgs CR) const
	{
		root.get().Undo();
	}

	void MainPage::RedoClick(IInspectable CR, RoutedEventArgs CR) const
	{
		root.get().Redo();
	}

	void MainPage::OperationCategoryChosen(IInspectable CR, SelectionChangedEventArgs CR)
	{
		if (IsLoaded())
			switch (�������().SelectedIndex())
			{
			case 0:
				��������().Visibility(Visibility::Visible);
				���Ʋ���().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				���ڲ���().Visibility(Visibility::Collapsed);
				ѡ�����().Visibility(Visibility::Collapsed);
				���ʲ���().Visibility(Visibility::Collapsed);
				��Χ����().Visibility(Visibility::Collapsed);
				�������().Visibility(Visibility::Collapsed);
				ֱ�Ӵ���().Visibility(Visibility::Collapsed);
				break;
			case 1:
				��������().Visibility(Visibility::Collapsed);
				���Ʋ���().Visibility(Visibility::Visible);
				��������().Visibility(Visibility::Collapsed);
				���ڲ���().Visibility(Visibility::Collapsed);
				ѡ�����().Visibility(Visibility::Collapsed);
				���ʲ���().Visibility(Visibility::Collapsed);
				��Χ����().Visibility(Visibility::Collapsed);
				�������().Visibility(Visibility::Collapsed);
				ֱ�Ӵ���().Visibility(Visibility::Collapsed);
				�¶�������().Focus(FocusState::Programmatic);
				break;
			case 2:
				��������().Visibility(Visibility::Collapsed);
				���Ʋ���().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Visible);
				���ڲ���().Visibility(Visibility::Collapsed);
				ѡ�����().Visibility(Visibility::Collapsed);
				���ʲ���().Visibility(Visibility::Collapsed);
				��Χ����().Visibility(Visibility::Collapsed);
				�������().Visibility(Visibility::Collapsed);
				ֱ�Ӵ���().Visibility(Visibility::Collapsed);
				break;
			case 3:
				��������().Visibility(Visibility::Collapsed);
				���Ʋ���().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				���ڲ���().Visibility(Visibility::Visible);
				ѡ�����().Visibility(Visibility::Collapsed);
				���ʲ���().Visibility(Visibility::Collapsed);
				��Χ����().Visibility(Visibility::Collapsed);
				�������().Visibility(Visibility::Collapsed);
				ֱ�Ӵ���().Visibility(Visibility::Collapsed);
				break;
			case 4:
				��������().Visibility(Visibility::Collapsed);
				���Ʋ���().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				���ڲ���().Visibility(Visibility::Collapsed);
				ѡ�����().Visibility(Visibility::Visible);
				���ʲ���().Visibility(Visibility::Collapsed);
				��Χ����().Visibility(Visibility::Collapsed);
				�������().Visibility(Visibility::Collapsed);
				ֱ�Ӵ���().Visibility(Visibility::Collapsed);
				break;
			case 5:
				��������().Visibility(Visibility::Collapsed);
				���Ʋ���().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				���ڲ���().Visibility(Visibility::Collapsed);
				ѡ�����().Visibility(Visibility::Collapsed);
				���ʲ���().Visibility(Visibility::Visible);
				��Χ����().Visibility(Visibility::Collapsed);
				�������().Visibility(Visibility::Collapsed);
				ֱ�Ӵ���().Visibility(Visibility::Collapsed);
				break;
			case 6:
				��������().Visibility(Visibility::Collapsed);
				���Ʋ���().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				���ڲ���().Visibility(Visibility::Collapsed);
				ѡ�����().Visibility(Visibility::Collapsed);
				���ʲ���().Visibility(Visibility::Collapsed);
				��Χ����().Visibility(Visibility::Visible);
				�������().Visibility(Visibility::Collapsed);
				ֱ�Ӵ���().Visibility(Visibility::Collapsed);
				break;
			case 7:
				��������().Visibility(Visibility::Collapsed);
				���Ʋ���().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				���ڲ���().Visibility(Visibility::Collapsed);
				ѡ�����().Visibility(Visibility::Collapsed);
				���ʲ���().Visibility(Visibility::Collapsed);
				��Χ����().Visibility(Visibility::Collapsed);
				�������().Visibility(Visibility::Visible);
				ֱ�Ӵ���().Visibility(Visibility::Collapsed);
				break;
			case 8:
				��������().Visibility(Visibility::Collapsed);
				���Ʋ���().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				���ڲ���().Visibility(Visibility::Collapsed);
				ѡ�����().Visibility(Visibility::Collapsed);
				���ʲ���().Visibility(Visibility::Collapsed);
				��Χ����().Visibility(Visibility::Collapsed);
				�������().Visibility(Visibility::Collapsed);
				ֱ�Ӵ���().Visibility(Visibility::Visible);
			default:;
			}
	}

	void MainPage::AliasesOperationCategoryChosen(IInspectable CR, SelectionChangedEventArgs CR)
	{
		if (IsLoaded())
			switch (�����������().SelectedIndex())
			{
			case 0:
				�������().Visibility(Visibility::Visible);
				���ͱ���().Visibility(Visibility::Collapsed);
				��������().Focus(FocusState::Programmatic);
				break;
			case 1:
				�������().Visibility(Visibility::Collapsed);
				���ͱ���().Visibility(Visibility::Visible);
				��������().Focus(FocusState::Programmatic);
				break;
			default:;
			}
	}

	void MainPage::ObjectNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(��������(), IsValidName);
	}

	void MainPage::ObjectNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			������ʽ().Focus(FocusState::Programmatic);
	}

	void MainPage::ObjectExpressionChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(������ʽ());
	}

	void MainPage::ObjectExpressionFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckObjectName(��������().Text()))
				��������().Focus(FocusState::Programmatic);
			else
				ObjectConfirm(nullptr, nullptr);
	}

	void MainPage::ObjectConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationObject(��������().Text(), ������ʽ().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::TypeNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(��������(), IsValidName);
	}

	void MainPage::TypeNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			���ͱ��ʽ().Focus(FocusState::Programmatic);
	}

	void MainPage::TypeExpressionChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(���ͱ��ʽ(), IsValidTypeExpression);
	}

	void MainPage::TypeExpressionFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTypeName(��������().Text()))
				��������().Focus(FocusState::Programmatic);
			else
				TypeConfirm(nullptr, nullptr);
	}

	void MainPage::TypeConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationType(��������().Text(), ���ͱ��ʽ().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::CopyNewChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(�¶�������());
	}

	void MainPage::CopyNewFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			ԭ��������().Focus(FocusState::Programmatic);
	}

	void MainPage::CopyOriginalChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ԭ��������());
	}

	void MainPage::CopyOriginalFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(�¶�������().Text()))
				�¶�������().Focus(FocusState::Programmatic);
			else if (theorems.Lookup(ԭ��������().Text()))
				CopyConfirm(nullptr, nullptr);
	}

	void MainPage::CopyConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationCopy(�¶�������().Text(), ԭ��������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::FTOperationCategoryChosen(IInspectable CR, SelectionChangedEventArgs CR)
	{
		if (IsLoaded())
			switch (�����������().SelectedIndex())
			{
			case 0:
				����().Visibility(Visibility::Visible);
				ģ��().Visibility(Visibility::Collapsed);
				������������().Focus(FocusState::Programmatic);
				break;
			case 1:
				����().Visibility(Visibility::Collapsed);
				ģ��().Visibility(Visibility::Visible);
				ģ�嶨������().Focus(FocusState::Programmatic);
				break;
			default:;
			}
	}

	void MainPage::FunctionTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(������������());
	}

	void MainPage::FunctionTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			������������().Focus(FocusState::Programmatic);
	}

	void MainPage::FunctionParameterNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(������������(), IsValidName);
	}

	void MainPage::FunctionParameterNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			��������ʽ().Focus(FocusState::Programmatic);
	}

	void MainPage::FunctionImageExpressionChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(��������ʽ());
	}

	void MainPage::FunctionImageExpressionFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			����ʵ�α��ʽ().Focus(FocusState::Programmatic);
	}

	void MainPage::FunctionArgumentExpressionChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(����ʵ�α��ʽ());
	}

	void MainPage::FunctionArgumentExpressionFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(������������().Text()))
				������������().Focus(FocusState::Programmatic);
			else if (������������().Text().empty())
				������������().Focus(FocusState::Programmatic);
			else
				FunctionConfirm(nullptr, nullptr);
	}

	void MainPage::FunctionConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationFunction(������������().Text(), ������������().Text(), ��������ʽ().Text(), ����ʵ�α��ʽ().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::TemplateTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ģ�嶨������());
	}

	void MainPage::TemplateTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			ģ���������().Focus(FocusState::Programmatic);
	}

	void MainPage::TemplateParameterNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ģ���������(), IsValidName);
	}

	void MainPage::TemplateParameterNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			ģ������ʽ().Focus(FocusState::Programmatic);
	}

	void MainPage::TemplateImageExpressionChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ģ������ʽ());
	}

	void MainPage::TemplateImageExpressionFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			ģ��ʵ�α��ʽ().Focus(FocusState::Programmatic);
	}

	void MainPage::TemplateArgumentExpressionChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ģ��ʵ�α��ʽ(), IsValidTypeExpression);
	}

	void MainPage::TemplateArgumentExpressionFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(ģ�嶨������().Text()))
				ģ�嶨������().Focus(FocusState::Programmatic);
			else if (ģ���������().Text().empty())
				ģ���������().Focus(FocusState::Programmatic);
			else
				TemplateConfirm(nullptr, nullptr);
	}

	void MainPage::TemplateConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationTemplate(ģ�嶨������().Text(), ģ���������().Text(), ģ������ʽ().Text(), ģ��ʵ�α��ʽ().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::EqualityOperationCategoryChosen(IInspectable CR, SelectionChangedEventArgs CR)
	{
		if (IsLoaded())
			switch (���ڲ������().SelectedIndex())
			{
			case 0:
				EI().Visibility(Visibility::Visible);
				EIB().Visibility(Visibility::Collapsed);
				EIF().Visibility(Visibility::Collapsed);
				EIT().Visibility(Visibility::Collapsed);
				EE().Visibility(Visibility::Collapsed);
				EEB().Visibility(Visibility::Collapsed);
				ET().Visibility(Visibility::Collapsed);
				ER().Visibility(Visibility::Collapsed);
				EI��������().Focus(FocusState::Programmatic);
				break;
			case 1:
				EI().Visibility(Visibility::Collapsed);
				EIB().Visibility(Visibility::Visible);
				EIF().Visibility(Visibility::Collapsed);
				EIT().Visibility(Visibility::Collapsed);
				EE().Visibility(Visibility::Collapsed);
				EEB().Visibility(Visibility::Collapsed);
				ET().Visibility(Visibility::Collapsed);
				ER().Visibility(Visibility::Collapsed);
				EIB��������().Focus(FocusState::Programmatic);
				break;
			case 2:
				EI().Visibility(Visibility::Collapsed);
				EIB().Visibility(Visibility::Collapsed);
				EIF().Visibility(Visibility::Visible);
				EIT().Visibility(Visibility::Collapsed);
				EE().Visibility(Visibility::Collapsed);
				EEB().Visibility(Visibility::Collapsed);
				ET().Visibility(Visibility::Collapsed);
				ER().Visibility(Visibility::Collapsed);
				EIF��������().Focus(FocusState::Programmatic);
				break;
			case 3:
				EI().Visibility(Visibility::Collapsed);
				EIB().Visibility(Visibility::Collapsed);
				EIF().Visibility(Visibility::Collapsed);
				EIT().Visibility(Visibility::Visible);
				EE().Visibility(Visibility::Collapsed);
				EEB().Visibility(Visibility::Collapsed);
				ET().Visibility(Visibility::Collapsed);
				ER().Visibility(Visibility::Collapsed);
				EIT��������().Focus(FocusState::Programmatic);
				break;
			case 4:
				EI().Visibility(Visibility::Collapsed);
				EIB().Visibility(Visibility::Collapsed);
				EIF().Visibility(Visibility::Collapsed);
				EIT().Visibility(Visibility::Collapsed);
				EE().Visibility(Visibility::Visible);
				EEB().Visibility(Visibility::Collapsed);
				ET().Visibility(Visibility::Collapsed);
				ER().Visibility(Visibility::Collapsed);
				EE��������().Focus(FocusState::Programmatic);
				break;
			case 5:
				EI().Visibility(Visibility::Collapsed);
				EIB().Visibility(Visibility::Collapsed);
				EIF().Visibility(Visibility::Collapsed);
				EIT().Visibility(Visibility::Collapsed);
				EE().Visibility(Visibility::Collapsed);
				EEB().Visibility(Visibility::Visible);
				ET().Visibility(Visibility::Collapsed);
				ER().Visibility(Visibility::Collapsed);
				EEB��������().Focus(FocusState::Programmatic);
				break;
			case 6:
				EI().Visibility(Visibility::Collapsed);
				EIB().Visibility(Visibility::Collapsed);
				EIF().Visibility(Visibility::Collapsed);
				EIT().Visibility(Visibility::Collapsed);
				EE().Visibility(Visibility::Collapsed);
				EEB().Visibility(Visibility::Collapsed);
				ET().Visibility(Visibility::Visible);
				ER().Visibility(Visibility::Collapsed);
				ET��������().Focus(FocusState::Programmatic);
				break;
			case 7:
				EI().Visibility(Visibility::Collapsed);
				EIB().Visibility(Visibility::Collapsed);
				EIF().Visibility(Visibility::Collapsed);
				EIT().Visibility(Visibility::Collapsed);
				EE().Visibility(Visibility::Collapsed);
				EEB().Visibility(Visibility::Collapsed);
				ET().Visibility(Visibility::Collapsed);
				ER().Visibility(Visibility::Visible);
				ER��������().Focus(FocusState::Programmatic);
				break;
			default:;
			}
	}

	void MainPage::EITheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EI��������());
	}

	void MainPage::EITheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			EI��������().Focus(FocusState::Programmatic);
	}

	void MainPage::EIObjectChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EI��������());
	}

	void MainPage::EIObjectFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(EI��������().Text()))
				EI��������().Focus(FocusState::Programmatic);
			else
				EIConfirm(nullptr, nullptr);
	}

	void MainPage::EIConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationEI(EI��������().Text(), EI��������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::EIBTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EIB��������());
	}

	void MainPage::EIBTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			EIB��������().Focus(FocusState::Programmatic);
	}

	void MainPage::EIBReasonNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EIB��������());
	}

	void MainPage::EIBReasonNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(EIB��������().Text()))
				EIB��������().Focus(FocusState::Programmatic);
			else if (theorems.Lookup(EIB��������().Text()))
				EIBConfirm(nullptr, nullptr);
	}

	void MainPage::EIBConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationEIB(EIB��������().Text(), EIB��������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::EIFTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EIF��������());
	}

	void MainPage::EIFTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			EIF��������().Focus(FocusState::Programmatic);
	}

	void MainPage::EIFReasonNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EIF��������());
	}

	void MainPage::EIFReasonNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(EIF��������().Text()))
				EIF��������().Focus(FocusState::Programmatic);
			else if (theorems.Lookup(EIF��������().Text()))
				EIFConfirm(nullptr, nullptr);
	}

	void MainPage::EIFConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationEIF(EIF��������().Text(), EIF��������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::EITTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EIT��������());
	}

	void MainPage::EITTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			EIT��������().Focus(FocusState::Programmatic);
	}

	void MainPage::EITReasonNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EIT��������());
	}

	void MainPage::EITReasonNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(EIT��������().Text()))
				EIT��������().Focus(FocusState::Programmatic);
			else if (theorems.Lookup(EIT��������().Text()))
				EITConfirm(nullptr, nullptr);
	}

	void MainPage::EITConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationEIT(EIT��������().Text(), EIT��������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::EETheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EE��������());
	}

	void MainPage::EETheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			EE��������().Focus(FocusState::Programmatic);
	}

	void MainPage::EEReasonNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EE��������());
	}

	void MainPage::EEReasonNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			EE����().Focus(FocusState::Programmatic);
	}

	void MainPage::EEFunctionChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EE����());
	}

	void MainPage::EEFunctionFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(EE��������().Text()))
				EE��������().Focus(FocusState::Programmatic);
			else if (!theorems.Lookup(EE��������().Text()))
				EE��������().Focus(FocusState::Programmatic);
			else
				EEConfirm(nullptr, nullptr);
	}

	void MainPage::EEConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationEE(EE��������().Text(), EE��������().Text(), EE����().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::EEBTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EEB��������());
	}

	void MainPage::EEBTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			EEB��������().Focus(FocusState::Programmatic);
	}

	void MainPage::EEBReasonNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(EEB��������());
	}

	void MainPage::EEBReasonNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(EEB��������().Text()))
				EEB��������().Focus(FocusState::Programmatic);
			else if (theorems.Lookup(EEB��������().Text()))
				EEBConfirm(nullptr, nullptr);
	}

	void MainPage::EEBConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationEEB(EEB��������().Text(), EEB��������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::ETTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ET��������());
	}

	void MainPage::ETTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			ETidA().Focus(FocusState::Programmatic);
	}

	void MainPage::ETidAChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ETidA());
	}

	void MainPage::ETidAFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			ETidB().Focus(FocusState::Programmatic);
	}

	void MainPage::ETidBChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ETidB());
	}

	void MainPage::ETidBFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(ET��������().Text()))
				ET��������().Focus(FocusState::Programmatic);
			else if (!theorems.Lookup(ETidA().Text()))
				ETidA().Focus(FocusState::Programmatic);
			else if (!theorems.Lookup(ETidB().Text()))
				ETidB().Focus(FocusState::Programmatic);
			else
				ETConfirm(nullptr, nullptr);
	}

	void MainPage::ETConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationET(ET��������().Text(), ETidA().Text(), ETidB().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::ERTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ER��������());
	}

	void MainPage::ERTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			ER��������().Focus(FocusState::Programmatic);
	}

	void MainPage::ERReasonNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(ER��������());
	}

	void MainPage::ERReasonNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(ER��������().Text()))
				ER��������().Focus(FocusState::Programmatic);
			else if (theorems.Lookup(ER��������().Text()))
				ERConfirm(nullptr, nullptr);
	}

	void MainPage::ERConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationER(ER��������().Text(), ER��������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::ChoicesOperationCategoryChosen(IInspectable CR, SelectionChangedEventArgs CR)
	{
		if (IsLoaded())
			switch (ѡ��������().SelectedIndex())
			{
			case 0:
				C0().Visibility(Visibility::Visible);
				C1().Visibility(Visibility::Collapsed);
				C2Shit().Visibility(Visibility::Collapsed);
				C3().Visibility(Visibility::Collapsed);
				C0ID().Focus(FocusState::Programmatic);
				break;
			case 1:
				C0().Visibility(Visibility::Collapsed);
				C1().Visibility(Visibility::Visible);
				C2Shit().Visibility(Visibility::Collapsed);
				C3().Visibility(Visibility::Collapsed);
				C1ID().Focus(FocusState::Programmatic);
				break;
			case 2:
				C0().Visibility(Visibility::Collapsed);
				C1().Visibility(Visibility::Collapsed);
				C2Shit().Visibility(Visibility::Visible);
				C3().Visibility(Visibility::Collapsed);
				C2ID().Focus(FocusState::Programmatic);
				break;
			case 3:
				C0().Visibility(Visibility::Collapsed);
				C1().Visibility(Visibility::Collapsed);
				C2Shit().Visibility(Visibility::Collapsed);
				C3().Visibility(Visibility::Visible);
				C3ID().Focus(FocusState::Programmatic);
				break;
			default:;
			}
	}

	void MainPage::C0IDChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C0ID());
	}

	void MainPage::C0IDFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C0id().Focus(FocusState::Programmatic);
	}

	void MainPage::C0idChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C0id());
	}

	void MainPage::C0idFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C0a().Focus(FocusState::Programmatic);
	}

	void MainPage::C0aChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C0a());
	}

	void MainPage::C0aFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C0b().Focus(FocusState::Programmatic);
	}

	void MainPage::C0bChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C0b());
	}

	void MainPage::C0bFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(C0ID().Text()))
				C0ID().Focus(FocusState::Programmatic);
			else if (!theorems.Lookup(C0id().Text()))
				C0id().Focus(FocusState::Programmatic);
			else
				C0Confirm(nullptr, nullptr);
	}

	void MainPage::C0Confirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationC0(C0ID().Text(), C0id().Text(), C0a().Text(), C0b().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::C1IDChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C1ID());
	}

	void MainPage::C1IDFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C1id().Focus(FocusState::Programmatic);
	}

	void MainPage::C1idChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C1id());
	}

	void MainPage::C1idFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C1a().Focus(FocusState::Programmatic);
	}

	void MainPage::C1aChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C1a());
	}

	void MainPage::C1aFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C1b().Focus(FocusState::Programmatic);
	}

	void MainPage::C1bChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C1b());
	}

	void MainPage::C1bFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(C1ID().Text()))
				C1ID().Focus(FocusState::Programmatic);
			else if (!theorems.Lookup(C1id().Text()))
				C1id().Focus(FocusState::Programmatic);
			else
				C1Confirm(nullptr, nullptr);
	}

	void MainPage::C1Confirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationC1(C1ID().Text(), C1id().Text(), C1a().Text(), C1b().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::C2IDChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C2ID());
	}

	void MainPage::C2IDFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C2idA().Focus(FocusState::Programmatic);
	}

	void MainPage::C2idAChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C2idA());
	}

	void MainPage::C2idAFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C2idB().Focus(FocusState::Programmatic);
	}

	void MainPage::C2idBChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C2idB());
	}

	void MainPage::C2idBFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(C2ID().Text()))
				C2ID().Focus(FocusState::Programmatic);
			else if (!theorems.Lookup(C2idA().Text()))
				C2idA().Focus(FocusState::Programmatic);
			else if (theorems.Lookup(C2idB().Text()))
				C2Confirm(nullptr, nullptr);
	}

	void MainPage::C2Confirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationC2(C2ID().Text(), C2idA().Text(), C2idB().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::C3IDChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C3ID());
	}

	void MainPage::C3IDFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			C3id().Focus(FocusState::Programmatic);
	}

	void MainPage::C3idChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(C3id());
	}

	void MainPage::C3idFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(C3ID().Text()))
				C3ID().Focus(FocusState::Programmatic);
			else if (theorems.Lookup(C3id().Text()))
				C3Confirm(nullptr, nullptr);
	}

	void MainPage::C3Confirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationC3(C3ID().Text(), C3id().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::UQOperationCategoryChosen(IInspectable CR, SelectionChangedEventArgs CR)
	{
		if (IsLoaded())
			switch (���ʲ������().SelectedIndex())
			{
			case 0:
				UF().Visibility(Visibility::Visible);
				UT().Visibility(Visibility::Collapsed);
				UFID().Focus(FocusState::Programmatic);
				break;
			case 1:
				UF().Visibility(Visibility::Collapsed);
				UT().Visibility(Visibility::Visible);
				UTID().Focus(FocusState::Programmatic);
				break;
			default:;
			}
	}

	void MainPage::UFIDChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(UFID());
	}

	void MainPage::UFIDFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			UFid().Focus(FocusState::Programmatic);
	}

	void MainPage::UFidChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(UFid());
	}

	void MainPage::UFidFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			UFa().Focus(FocusState::Programmatic);
	}

	void MainPage::UFaChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(UFa());
	}

	void MainPage::UFaFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(UFID().Text()))
				UFID().Focus(FocusState::Programmatic);
			else if (!theorems.Lookup(UFid().Text()))
				UFid().Focus(FocusState::Programmatic);
			else
				UFConfirm(nullptr, nullptr);
	}

	void MainPage::UFConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationUF(UFID().Text(), UFid().Text(), UFa().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::UTIDChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(UTID());
	}

	void MainPage::UTIDFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			UTid().Focus(FocusState::Programmatic);
	}

	void MainPage::UTidChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(UTid());
	}

	void MainPage::UTidFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			UTt().Focus(FocusState::Programmatic);
	}

	void MainPage::UTtChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(UTt(), IsValidTypeExpression);
	}

	void MainPage::UTtFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckTheoremName(UTID().Text()))
				UTID().Focus(FocusState::Programmatic);
			else if (!theorems.Lookup(UTid().Text()))
				UTid().Focus(FocusState::Programmatic);
			else
				UTConfirm(nullptr, nullptr);
	}

	void MainPage::UTConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationUT(UTID().Text(), UTid().Text(), UTt().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::ScopeOperationCategoryChosen(IInspectable CR, SelectionChangedEventArgs CR)
	{
		if (IsLoaded())
			switch (��Χ�������().SelectedIndex())
			{
			case 0:
				��ͨ��Χ().Visibility(Visibility::Visible);
				����().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Collapsed);
				ȷ���뿪().Visibility(Visibility::Collapsed);
				��Χ����().Focus(FocusState::Programmatic);
				break;
			case 1:
				��ͨ��Χ().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Visible);
				��������().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Collapsed);
				ȷ���뿪().Visibility(Visibility::Collapsed);
				��������().Focus(FocusState::Programmatic);
				break;
			case 2:
				��ͨ��Χ().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Visible);
				��������().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Collapsed);
				ȷ���뿪().Visibility(Visibility::Collapsed);
				�������巶Χ����().Focus(FocusState::Programmatic);
				break;
			case 3:
				��ͨ��Χ().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Visible);
				����().Visibility(Visibility::Collapsed);
				ȷ���뿪().Visibility(Visibility::Collapsed);
				�������ͷ�Χ����().Focus(FocusState::Programmatic);
				break;
			case 4:
				��ͨ��Χ().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Visible);
				ȷ���뿪().Visibility(Visibility::Collapsed);
				��������().Focus(FocusState::Programmatic);
				break;
			case 5:
				��ͨ��Χ().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				��������().Visibility(Visibility::Collapsed);
				����().Visibility(Visibility::Collapsed);
				ȷ���뿪().Visibility(Visibility::Visible);
				break;
			default:;
			}
	}

	void MainPage::ScopeNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(��Χ����());
	}

	void MainPage::ScopeNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter && CheckScopeName(��Χ����().Text()))
			ScopeConfirm(nullptr, nullptr);
	}

	void MainPage::ScopeConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationScope(��Χ����().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::AssumeNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(��������());
	}

	void MainPage::AssumeNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			���趨������().Focus(FocusState::Programmatic);
	}

	void MainPage::AssumeTheoremNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(���趨������());
	}

	void MainPage::AssumeTheoremNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			���趨��().Focus(FocusState::Programmatic);
	}

	void MainPage::AssumeTheoremChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(���趨��());
	}

	void MainPage::AssumeTheoremFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckScopeName(��������().Text()))
				��������().Focus(FocusState::Programmatic);
			else if (!CheckTheoremName(���趨������().Text()))
				���趨������().Focus(FocusState::Programmatic);
			else
				AssumeConfirm(nullptr, nullptr);
	}

	void MainPage::AssumeConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationAssume(��������().Text(), ���趨������().Text(), ���趨��().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::ArbitraryObjectScopeNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(�������巶Χ����());
	}

	void MainPage::ArbitraryObjectScopeNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			������������().Focus(FocusState::Programmatic);
	}

	void MainPage::ArbitraryObjectNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(������������(), IsValidName);
	}

	void MainPage::ArbitraryObjectNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			������������().Focus(FocusState::Programmatic);
	}

	void MainPage::ArbitraryObjectTypeChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(������������(), IsValidTypeExpression);
	}

	void MainPage::ArbitraryObjectTypeFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckScopeName(�������巶Χ����().Text()))
				�������巶Χ����().Focus(FocusState::Programmatic);
			else if (!CheckObjectName(������������().Text()))
				������������().Focus(FocusState::Programmatic);
			else
				ArbitraryObjectConfirm(nullptr, nullptr);
	}

	void MainPage::ArbitraryObjectConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationArbitraryObject(�������巶Χ����().Text(), ������������().Text(), ������������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::ArbitraryTypeScopeNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(�������ͷ�Χ����());
	}

	void MainPage::ArbitraryTypeScopeNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			������������().Focus(FocusState::Programmatic);
	}

	void MainPage::ArbitraryTypeNameChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(������������(), IsValidName);
	}

	void MainPage::ArbitraryTypeNameFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			if (!CheckScopeName(�������ͷ�Χ����().Text()))
				�������ͷ�Χ����().Focus(FocusState::Programmatic);
			else if (CheckTypeName(������������().Text()))
				ArbitraryTypeConfirm(nullptr, nullptr);
	}

	void MainPage::ArbitraryTypeConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationArbitraryType(�������ͷ�Χ����().Text(), ������������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::ExportTheoremChanged(IInspectable CR, TextChangedEventArgs CR)
	{
		RemoveIllegal(��������());
	}

	void MainPage::ExportTheoremFinished(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter && theorems.InCurrent(��������().Text()) && !exported.contains(��������().Text()))
			ExportConfirm(nullptr, nullptr);
	}

	void MainPage::ExportConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationExport(��������().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	void MainPage::ExitConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (const OperationP operation = OperationExit())
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	fire_and_forget MainPage::ImportClick(IInspectable CR, RoutedEventArgs CR)
	{
		try
		{
			const FileOpenPicker picker(GetMainWindow[position.get()].get().AppWindow().Id());
			picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			picker.FileTypeFilter().Append(L".logic");
			for (PickFileResult CR result : co_await picker.PickMultipleFilesAsync())
				try
			{
				const ContentDialog dialog;
				dialog.XamlRoot(XamlRoot());
				dialog.Title(box_value(ResourceLoader().GetString(L"���Ժ򡭡�")));
				dialog.ShowAsync();
				{
					const apartment_context ui;
					co_await resume_after(114514us);
					co_await ui;
				}
				root.get().ReadContent(co_await FileIO::ReadTextAsync(co_await StorageFile::GetFileFromPathAsync(result.Path())));
				dialog.Hide();
			}
			catch (...)
			{
				const Flyout flyout;
				flyout.Content(RegularText(ResourceLoader().GetString(L"OpenFileFailure")));
				flyout.ShowAt(�������());
			}
		}
		catch (...)
		{
			const Flyout flyout;
			flyout.Content(RegularText(ResourceLoader().GetString(L"OpenFilePickerFailure")));
			flyout.ShowAt(�������());
		}
	}

	void MainPage::CodeKeyDown(IInspectable CR, KeyRoutedEventArgs CR args)
	{
		if (args.Key() == VirtualKey::Enter)
			CodeConfirm(nullptr, nullptr);
	}

	void MainPage::CodeConfirm(IInspectable CR, RoutedEventArgs CR)
	{
		if (CheckStatus())
			if (OperationP CR operation = ParseOperation(����().Text()))
			{
				root.get().AddOperationS(operation);
				return;
			}
		error_flyout.ShowAt(�������());
	}

	bool MainPage::CheckObjectName(hstring CR s) const
	{
		return !s.empty() && !objects.Lookup(s);
	}

	bool MainPage::CheckTypeName(hstring CR s) const
	{
		return !s.empty() && !types.Lookup(s);
	}

	bool MainPage::CheckTheoremName(hstring CR s) const
	{
		return !s.empty() && !theorems.Lookup(s);
	}

	bool MainPage::CheckScopeName(hstring CR s) const
	{
		return !s.empty() && !children.contains(s);
	}

	bool MainPage::CheckStatus() const
	{
		if (root.get().Focus() != self.get())
		{
			error_flyout.Content(RegularText(ResourceLoader().GetString(L"�ǽ���")));
			return false;
		}
		return true;
	}

	bool MainPage::IsValidName(wchar_t CR ch)
	{
		return ch > L' ' && ch != L'~' && ch != L'`' && ch != L'!' && ch != L'@' && ch != L'#' && ch != L'=' && ch != L'?' && ch != L':' && ch != L'(' && ch != L')';
	}

	bool MainPage::IsValidTypeExpression(wchar_t CR ch)
	{
		return ch > L' ' && ch != L'!' && ch != L'@' && ch != L'#' && ch != L'=' && ch != L'?' && ch != L':';
	}

	void MainPage::RemoveIllegal(TextBox CR box)
	{
		wstring s(box.Text());
		int32_t pos(box.SelectionStart());
		for (auto it = s.cbegin(); it < s.cend();)
			if (*it <= L' ')
			{
				if (pos > it - s.cbegin())
					--pos;
				it = s.erase(it);
			}
			else
				++it;
		box.Text(s);
		box.SelectionStart(pos);
	}

	void MainPage::RemoveIllegal(TextBox CR box, auto CR check)
	{
		wstring s(box.Text());
		int32_t pos(box.SelectionStart());
		for (auto it = s.cbegin(); it < s.cend();)
			if (!check(*it))
			{
				if (pos > it - s.cbegin())
					--pos;
				it = s.erase(it);
			}
			else
				++it;
		box.Text(s);
		box.SelectionStart(pos);
	}

	OperationP MainPage::MakeOperation(OperationCategory CR _category, const initializer_list<hstring> _contents)
	{
		const OperationP operation(_category);
		for (hstring CR content : _contents)
			operation.Contents().Append(content);
		return operation;
	}

	OperationP MainPage::OperationObject(param::hstring CR _name, param::hstring CR _expression)
	{
		if (!CheckObjectName(_name))
		{
			ObjectNameExist(_name);
			return nullptr;
		}
		const ExpressionContainerP container;
		if (const ObjP value = MakeObject(_expression, container))
		{
			const ObjP declaration(container, self.get());
			declaration.Self(declaration);
			declaration.InitAsAlias(value, _name);
			objects.Insert(_name, declaration);
			{
				const UIElementCollection items = container.Items();
				items.Append(declaration);
				items.Append(ObjectDefinition());
				for (UIElement CR item : ObjP::Generate(value))
					items.Append(item);
			}
			container.Text(wstring(L"Object ").append(L" ").append(hstring(_name)).append(L" ").append(hstring(_expression)));
			�����().Children().Append(container);
			return MakeOperation(OperationCategory::Object, { _name, _expression });
		}
		return nullptr;
	}

	OperationP MainPage::OperationType(param::hstring CR _name, param::hstring CR _expression)
	{
		if (!CheckTypeName(_name))
		{
			TypeNameExist(_name);
			return nullptr;
		}
		const ExpressionContainerP container;
		if (const TypeP value = MakeType(_expression, container))
		{
			const TypeP declaration(container, self.get());
			declaration.Self(declaration);
			declaration.InitAsAlias(value, _name);
			types.Insert(_name, declaration);
			{
				const UIElementCollection items = container.Items();
				items.Append(declaration);
				items.Append(TypeDefinition());
				for (UIElement CR item : TypeP::Generate(value))
					items.Append(item);
			}
			container.Text(wstring(L"Type ").append(hstring(_name)).append(L" ").append(hstring(_expression)));
			�����().Children().Append(container);
			return MakeOperation(OperationCategory::Type, { _name, _expression });
		}
		return nullptr;
	}

	OperationP MainPage::OperationCopy(param::hstring CR ID, param::hstring CR id)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		const ExpressionContainerP container;
		const TheoremP original = FetchTheorem(id, container);
		const TheoremPanelP panel;
		const TheoremP th(container, self.get());
		th.Self(th);
		th.Init(ObjP::Clone(original.Definition(), panel, self.get()), ID);
		theorems.Insert(ID, th);
		{
			const UIElementCollection items = container.Items();
			items.Append(RegularText(L"Copy \u200B"));
			items.Append(th);
			items.Append(RegularText(L" \u200B"));
			items.Append(original);
		}
		container.Text(wstring(L"Copy ").append(hstring(id)).append(L" ").append(hstring(id)));
		�����().Children().Append(container);
		{
			const TheoremP tth(panel, self.get());
			tth.Self(tth);
			tth.Init2(th);
			panel.Name(tth);
		}
		�����().Children().Append(panel);
		return MakeOperation(OperationCategory::Copy, { ID, id });
	}

	OperationP MainPage::OperationFunction(param::hstring CR ID, param::hstring CR _param, param::hstring CR _image, param::hstring CR _arg)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (hstring(_param).empty())
		{
			error_flyout.Content(RegularText(ResourceLoader().GetString(L"EmptyParameterName")));
			return nullptr;
		}
		const ExpressionContainer container;
		if (const ObjP argument = MakeObject(_arg, container))
		{
			const ObjP param(container, self.get());
			param.Self(param);
			param.InitAsParameter(Type::Clone(argument.MyType(), container, self.get()), _param);
			{
				const LinkedMapP current;
				current.Parent(objects);
				(objects = current).Insert(_param, param);
				const LinkedMapP ph;
				ph.Parent(types);
				types = ph;
			}
			if (const ObjP image = MakeObject(_image, container))
			{
				const TheoremPanelP panel;
				const TheoremP th(container, self.get());
				th.Self(th);
				{
					const ObjP equal(panel, self.get());
					equal.Self(equal);
					{
						const ObjP func(panel, self.get());
						func.Self(func);
						{
							const ObjP pparam = ObjP::Clone(param, panel, self.get());
							func.InitAsDeclareF(pparam, RemoveCurrent(image, panel, self.get(), pparam, nullptr));
						}
						objects = objects.Parent(), types = types.Parent();
						const ObjP apply(panel, self.get());
						apply.Self(apply);
						apply.InitAsApplyF(func, ObjP::Clone(argument, panel, self.get()));
						if (const ObjP ooo = ObjP::ApplyFunction(func, argument, panel, self.get()))
							equal.InitAsEqual(apply, ooo);
						else
						{
							error_flyout.Content(RegularText(ResourceLoader().GetString(L"��ͻ")));
							return nullptr;
						}
					}
					th.Init(equal, ID);
				}
				theorems.Insert(ID, th);
				{
					const UIElementCollection items = container.Items();
					items.Append(RegularText(L"Function \u200B"));
					items.Append(param);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(image))
						items.Append(item);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(argument))
						items.Append(item);
				}
				container.Text(wstring(L"Function ").append(hstring(_param)).append(L" ").append(hstring(_image)).append(L" ").append(hstring(_arg)));
				�����().Children().Append(container);
				{
					const TheoremP tth(panel, self.get());
					tth.Self(tth);
					tth.Init2(th);
					panel.Name(tth);
				}
				�����().Children().Append(panel);
				return MakeOperation(OperationCategory::Function, { ID, _param, _image, _arg });
			}
			objects = objects.Parent(), types = types.Parent();
		}
		return nullptr;
	}

	OperationP MainPage::OperationTemplate(param::hstring CR ID, param::hstring CR _param, param::hstring CR _image, param::hstring CR _arg)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (hstring(_param).empty())
		{
			error_flyout.Content(RegularText(ResourceLoader().GetString(L"EmptyParameterName")));
			return nullptr;
		}
		const ExpressionContainer container;
		if (const TypeP aaa = MakeType(_arg, container))
		{
			const ObjP argument(container, self.get());
			argument.Self(argument);
			argument.InitAsType(aaa);
			const TypeP tp(container, self.get());
			tp.Self(tp);
			tp.InitAsParameter(_param);
			const ObjP param(container, self.get());
			param.Self(param);
			param.InitAsType(tp);
			{
				const LinkedMapP current;
				current.Parent(types);
				(types = current).Insert(_param, tp);
				const LinkedMapP ph;
				ph.Parent(objects);
				objects = ph;
			}
			if (const ObjP image = MakeObject(_image, container))
			{
				const TheoremPanelP panel;
				const TheoremP th(container, self.get());
				th.Self(th);
				{
					const ObjP equal(panel, self.get());
					equal.Self(equal);
					{
						const ObjP temp(panel, self.get());
						temp.Self(temp);
						{
							const TypeP ttp = TypeP::Clone(tp, panel, self.get());
							const ObjP pparam(panel, self.get());
							pparam.Self(pparam);
							pparam.InitAsType(ttp);
							temp.InitAsDeclareT(pparam, RemoveCurrent(image, panel, self.get(), nullptr, ttp));
						}
						types = types.Parent(), objects = objects.Parent();
						const ObjP apply(panel, self.get());
						apply.Self(apply);
						apply.InitAsApplyT(temp, ObjP::Clone(argument, panel, self.get()));
						if (const ObjP ooo = ObjP::ApplyTemplate(temp, aaa, panel, self.get()))
							equal.InitAsEqual(apply, ooo);
						else
						{
							error_flyout.Content(RegularText(ResourceLoader().GetString(L"��ͻ")));
							return nullptr;
						}
					}
					th.Init(equal, ID);
				}
				theorems.Insert(ID, th);
				{
					const UIElementCollection items = container.Items();
					items.Append(RegularText(L"Template \u200B"));
					items.Append(tp);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(image))
						items.Append(item);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : TypeP::Generate(aaa))
						items.Append(item);
				}
				container.Text(wstring(L"Template ").append(hstring(_param)).append(L" ").append(hstring(_image)).append(L" ").append(hstring(_arg)));
				�����().Children().Append(container);
				{
					const TheoremP tth(panel, self.get());
					tth.Self(tth);
					tth.Init2(th);
					panel.Name(tth);
				}
				�����().Children().Append(panel);
				return MakeOperation(OperationCategory::Template, { ID, _param, _image, _arg });
			}
			types = types.Parent(), objects = objects.Parent();
		}
		return nullptr;
	}

	OperationP MainPage::OperationEI(param::hstring CR ID, param::hstring CR a)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		const ExpressionContainer container;
		if (const ObjP obj = MakeObject(a, container))
		{
			const TheoremPanelP panel;
			const TheoremP th(container, self.get());
			th.Self(th);
			{
				const ObjP equal(panel, self.get());
				equal.Self(equal);
				equal.InitAsEqual(ObjP::Clone(obj, panel, self.get()), ObjP::Clone(obj, panel, self.get()));
				th.Init(equal, ID);
			}
			theorems.Insert(ID, th);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"EI \u200B"));
				items.Append(th);
				items.Append(RegularText(L" \u200B"));
				for (UIElement CR item : ObjP::Generate(obj))
					items.Append(item);
			}
			container.Text(wstring(L"EI ").append(hstring(ID)).append(L" ").append(hstring(a)));
			�����().Children().Append(container);
			{
				const TheoremP tth(panel, self.get());
				tth.Self(tth);
				tth.Init2(th);
				panel.Name(tth);
			}
			�����().Children().Append(panel);
			return MakeOperation(OperationCategory::EI, { ID, a });
		}
		return nullptr;
	}

	OperationP MainPage::OperationEIB(param::hstring CR ID, param::hstring CR id)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		const ExpressionContainerP container;
		const TheoremP original = FetchTheorem(id, container);
		const TheoremPanelP panel;
		const TheoremP th(container, self.get());
		th.Self(th);
		{
			const ObjP equal(panel, self.get());
			equal.Self(equal);
			{
				const ObjP tr(panel, self.get());
				tr.Self(tr);
				tr.InitAsTrue();
				equal.InitAsEqual(ObjP::Clone(original.Definition(), panel, self.get()), tr);
			}
			th.Init(equal, ID);
		}
		theorems.Insert(ID, th);
		{
			const UIElementCollection items = container.Items();
			items.Append(RegularText(L"EIB \u200B"));
			items.Append(th);
			items.Append(RegularText(L" \u200B"));
			items.Append(original);
		}
		container.Text(wstring(L"EIB ").append(hstring(ID)).append(L" ").append(hstring(id)));
		�����().Children().Append(container);
		{
			const TheoremP tth(panel, self.get());
			tth.Self(tth);
			tth.Init2(th);
			panel.Name(tth);
		}
		�����().Children().Append(panel);
		return MakeOperation(OperationCategory::EIB, { ID, id });
	}

	OperationP MainPage::OperationEIF(param::hstring CR ID, param::hstring CR id)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP original = FetchTheorem(id, container);
			ObjP current = original.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::ForallF)
				goto Error;
			current = current.Right();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::DeclareF)
				goto Error;
			current = current.Right();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Equal)
				goto Error;
			ObjP now = current.Left();
			while ((cat = now.Category()) == ObjectCategory::Alias)
				now = now.Right();
			if (cat != ObjectCategory::ApplyF)
				goto Error;
			const ObjP a = now.Left();
			now = now.Right();
			while ((cat = now.Category()) == ObjectCategory::Alias)
				now = now.Right();
			if (cat != ObjectCategory::Parameter)
				goto Error;
			now = current.Right();
			while ((cat = now.Category()) == ObjectCategory::Alias)
				now = now.Right();
			if (cat != ObjectCategory::ApplyF)
				goto Error;
			const ObjP b = now.Left();
			now = now.Right();
			while ((cat = now.Category()) == ObjectCategory::Alias)
				now = now.Right();
			if (cat != ObjectCategory::Parameter)
				goto Error;
			const TheoremPanelP panel;
			const TheoremP th(container, self.get());
			th.Self(th);
			{
				const ObjP equal(panel, self.get());
				equal.Self(equal);
				equal.InitAsEqual(ObjP::Clone(a, panel, self.get()), ObjP::Clone(b, panel, self.get()));
				th.Init(equal, ID);
			}
			theorems.Insert(ID, th);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"EIF \u200B"));
				items.Append(th);
				items.Append(RegularText(L" \u200B"));
				items.Append(original);
			}
			container.Text(wstring(L"EIF ").append(hstring(ID)).append(L" ").append(hstring(id)));
			�����().Children().Append(container);
			{
				const TheoremP tth(panel, self.get());
				tth.Self(tth);
				tth.Init2(th);
				panel.Name(tth);
			}
			�����().Children().Append(panel);
			return MakeOperation(OperationCategory::EIF, { ID, id });
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationEIT(param::hstring CR ID, param::hstring CR id)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP original = FetchTheorem(id, container);
			ObjP current = original.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::ForallT)
				goto Error;
			current = current.Right();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::DeclareT)
				goto Error;
			current = current.Right();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Equal)
				goto Error;
			ObjP now = current.Left();
			while ((cat = now.Category()) == ObjectCategory::Alias)
				now = now.Right();
			if (cat != ObjectCategory::ApplyT)
				goto Error;
			const ObjP a = now.Left();
			now = now.Right();
			if (now.Category() != ObjectCategory::Type || now.MyType().Category() != TypeCategory::Parameter)
				goto Error;
			now = current.Right();
			while ((cat = now.Category()) == ObjectCategory::Alias)
				now = now.Right();
			if (cat != ObjectCategory::ApplyT)
				goto Error;
			const ObjP b = now.Left();
			now = now.Right();
			if (now.Category() != ObjectCategory::Type || now.MyType().Category() != TypeCategory::Parameter)
				goto Error;
			const TheoremPanelP panel;
			const TheoremP th(container, self.get());
			th.Self(th);
			{
				const ObjP equal(panel, self.get());
				equal.Self(equal);
				equal.InitAsEqual(ObjP::Clone(a, panel, self.get()), ObjP::Clone(b, panel, self.get()));
				th.Init(equal, ID);
			}
			theorems.Insert(ID, th);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"EIT \u200B"));
				items.Append(th);
				items.Append(RegularText(L" \u200B"));
				items.Append(original);
			}
			container.Text(wstring(L"EIT ").append(hstring(ID)).append(L" ").append(hstring(id)));
			�����().Children().Append(container);
			{
				const TheoremP tth(panel, self.get());
				tth.Self(tth);
				tth.Init2(th);
				panel.Name(tth);
			}
			�����().Children().Append(panel);
			return MakeOperation(OperationCategory::EIT, { ID, id });
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationEE(param::hstring CR ID, param::hstring CR id, param::hstring CR f)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP original = FetchTheorem(id, container);
			ObjP current = original.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Equal)
				goto Error;
			const ObjP a = current.Left(), b = current.Right();
			if (const ObjP func = MakeObject(f, container))
			{
				current = func;
				while ((cat = current.Category()) == ObjectCategory::Alias)
					current = current.Right();
				if (cat != ObjectCategory::DeclareF)
					goto Error;
				if (!Type::Equal(a.MyType(), current.Left().MyType()))
					goto Error;
				const TheoremPanelP panel;
				const TheoremP th(container, self.get());
				th.Self(th);
				{
					const ObjP equal(panel, self.get());
					equal.Self(equal);
					{
						const ObjP lf(panel, self.get());
						lf.Self(lf);
						lf.InitAsApplyF(ObjP::Clone(func, panel, self.get()), ObjP::Clone(a, panel, self.get()));
						const ObjP rt(panel, self.get());
						rt.Self(rt);
						rt.InitAsApplyF(ObjP::Clone(func, panel, self.get()), ObjP::Clone(b, panel, self.get()));
						equal.InitAsEqual(lf, rt);
					}
					th.Init(equal, ID);
				}
				theorems.Insert(ID, th);
				{
					const UIElementCollection items = container.Items();
					items.Append(RegularText(L"EE \u200B"));
					items.Append(th);
					items.Append(RegularText(L" \u200B"));
					items.Append(original);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(func))
						items.Append(item);
				}
				container.Text(wstring(L"EE ").append(hstring(ID)).append(L" ").append(hstring(id)).append(L" ").append(hstring(f)));
				�����().Children().Append(container);
				{
					const TheoremP tth(panel, self.get());
					tth.Self(tth);
					tth.Init2(th);
					panel.Name(tth);
				}
				�����().Children().Append(panel);
				return MakeOperation(OperationCategory::EE, { ID, id, f });
			}
			return nullptr;
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationEEB(param::hstring CR ID, param::hstring CR id)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP original = FetchTheorem(id, container);
			ObjP current = original.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Equal)
				goto Error;
			const ObjP a = current.Left();
			current = current.Right();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::True)
				goto Error;
			const TheoremPanelP panel;
			const TheoremP th(container, self.get());
			th.Self(th);
			th.Init(ObjP::Clone(a, panel, self.get()), ID);
			theorems.Insert(ID, th);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"EEB \u200B"));
				items.Append(th);
				items.Append(RegularText(L" \u200B"));
				items.Append(original);
			}
			container.Text(wstring(L"EEB ").append(hstring(ID)).append(L" ").append(hstring(id)));
			�����().Children().Append(container);
			{
				const TheoremP tth(panel, self.get());
				tth.Self(tth);
				tth.Init2(th);
				panel.Name(tth);
			}
			�����().Children().Append(panel);
			return MakeOperation(OperationCategory::EEB, { ID, id });
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationET(param::hstring CR ID, param::hstring CR idA, param::hstring CR idB)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(idA))
		{
			TheoremNotFound(idA);
			return nullptr;
		}
		if (!theorems.Lookup(idB))
		{
			TheoremNotFound(idB);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP originalA = FetchTheorem(idA, container), originalB = FetchTheorem(idB, container);
			ObjP current = originalA.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Equal)
				goto Error;
			const ObjP a = current.Left(), b = current.Right();
			current = originalB.Definition();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Equal || !ObjP::Equal(b, current.Left()))
				goto Error;
			const TheoremPanelP panel;
			const TheoremP th(container, self.get());
			th.Self(th);
			{
				const ObjP equal;
				equal.Self(equal);
				equal.InitAsEqual(ObjP::Clone(a, panel, self.get()), ObjP::Clone(current.Right(), panel, self.get()));
				th.Init(equal, ID);
			}
			theorems.Insert(ID, th);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"ET \u200B"));
				items.Append(th);
				items.Append(RegularText(L" \u200B"));
				items.Append(originalA);
				items.Append(RegularText(L" \u200B"));
				items.Append(originalB);
			}
			container.Text(wstring(L"ET ").append(hstring(ID)).append(L" ").append(hstring(idA)).append(L" ").append(hstring(idB)));
			�����().Children().Append(container);
			{
				const TheoremP tth(panel, self.get());
				tth.Self(tth);
				tth.Init2(th);
				panel.Name(tth);
			}
			�����().Children().Append(panel);
			return MakeOperation(OperationCategory::ET, { ID, idA, idB });
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationER(param::hstring CR ID, param::hstring CR id)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		const ExpressionContainerP container;
		const TheoremP original = FetchTheorem(id, container);
		ObjP current = original.Definition();
		ObjectCategory cat;
		while ((cat = current.Category()) == ObjectCategory::Alias)
			current = current.Right();
		if (cat != ObjectCategory::Equal)
		{
			InvalidReason();
			return nullptr;
		}
		const TheoremPanelP panel;
		const TheoremP th(container, self.get());
		th.Self(th);
		{
			const ObjP equal;
			equal.Self(equal);
			equal.InitAsEqual(ObjP::Clone(current.Right(), panel, self.get()), ObjP::Clone(current.Left(), panel, self.get()));
			th.Init(equal, ID);
		}
		theorems.Insert(ID, th);
		{
			const UIElementCollection items = container.Items();
			items.Append(RegularText(L"ER \u200B"));
			items.Append(th);
			items.Append(RegularText(L" \u200B"));
			items.Append(original);
		}
		container.Text(wstring(L"ER ").append(hstring(ID)).append(L" ").append(hstring(id)));
		�����().Children().Append(container);
		{
			const TheoremP tth(panel, self.get());
			tth.Self(tth);
			tth.Init2(th);
			panel.Name(tth);
		}
		�����().Children().Append(panel);
		return MakeOperation(OperationCategory::ER, { ID, id });
	}

	OperationP MainPage::OperationC0(param::hstring CR ID, param::hstring CR id, param::hstring CR a, param::hstring CR b)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		const ExpressionContainerP container;
		if (const ObjP oa = MakeObject(a, container))
			if (const ObjP ob = MakeObject(b, container))
			{
				if (!TypeP::Equal(oa.MyType(), ob.MyType()))
				{
					InvalidReason();
					return nullptr;
				}
				const TheoremP original = FetchTheorem(id, container);
				const TheoremPanelP panel;
				const TheoremP th(container, self.get());
				th.Self(th);
				{
					const ObjP equal(panel, self.get());
					equal.Self(equal);
					{
						const ObjP choose(panel, self.get());
						choose.Self(choose);
						{
							const ObjP options(panel, self.get());
							options.Self(options);
							options.InitAsOptions(ObjP::Clone(oa, panel, self.get()), ObjP::Clone(ob, panel, self.get()));
							choose.InitAsChoose(ObjP::Clone(original.Definition(), panel, self.get()), options);
						}
						equal.InitAsEqual(choose, ObjP::Clone(oa, panel, self.get()));
					}
					th.Init(equal, ID);
				}
				theorems.Insert(ID, th);
				{
					const UIElementCollection items = container.Items();
					items.Append(RegularText(L"C0 \u200B"));
					items.Append(th);
					items.Append(RegularText(L" \u200B"));
					items.Append(original);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(oa))
						items.Append(item);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(ob))
						items.Append(item);
				}
				container.Text(wstring(L"C0 ").append(hstring(ID)).append(L" ").append(hstring(id)).append(L" ").append(hstring(a)).append(L" ").append(hstring(b)));
				�����().Children().Append(container);
				{
					const TheoremP tth(panel, self.get());
					tth.Self(tth);
					tth.Init2(th);
					panel.Name(tth);
				}
				�����().Children().Append(panel);
				return MakeOperation(OperationCategory::C0, { ID, id, a, b });
			}
		return nullptr;
	}

	OperationP MainPage::OperationC1(param::hstring CR ID, param::hstring CR id, param::hstring CR a, param::hstring CR b)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		const ExpressionContainerP container;
		if (const ObjP oa = MakeObject(a, container))
			if (const ObjP ob = MakeObject(b, container))
			{
				if (!TypeP::Equal(oa.MyType(), ob.MyType()))
					goto Error;
				const TheoremP original = FetchTheorem(id, container);
				ObjP current = original.Definition();
				ObjectCategory cat;
				while ((cat = current.Category()) == ObjectCategory::Alias)
					current = current.Right();
				if (cat != ObjectCategory::Equal)
					goto Error;
				const ObjP pp = current.Left();
				current = current.Right();
				while ((cat = current.Category()) == ObjectCategory::Alias)
					current = current.Right();
				if (cat != ObjectCategory::False)
					goto Error;
				const TheoremPanelP panel;
				const TheoremP th(container, self.get());
				th.Self(th);
				{
					const ObjP equal(panel, self.get());
					equal.Self(equal);
					{
						const ObjP choose(panel, self.get());
						choose.Self(choose);
						{
							const ObjP options(panel, self.get());
							options.Self(options);
							options.InitAsOptions(ObjP::Clone(oa, panel, self.get()), ObjP::Clone(ob, panel, self.get()));
							choose.InitAsChoose(ObjP::Clone(pp, panel, self.get()), options);
						}
						equal.InitAsEqual(choose, ObjP::Clone(ob, panel, self.get()));
					}
					th.Init(equal, ID);
				}
				theorems.Insert(ID, th);
				{
					const UIElementCollection items = container.Items();
					items.Append(RegularText(L"C1 \u200B"));
					items.Append(th);
					items.Append(RegularText(L" \u200B"));
					items.Append(original);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(oa))
						items.Append(item);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(ob))
						items.Append(item);
				}
				container.Text(wstring(L"C1 ").append(hstring(ID)).append(L" ").append(hstring(id)).append(L" ").append(hstring(a)).append(L" ").append(hstring(b)));
				�����().Children().Append(container);
				{
					const TheoremP tth(panel, self.get());
					tth.Self(tth);
					tth.Init2(th);
					panel.Name(tth);
				}
				�����().Children().Append(panel);
				return MakeOperation(OperationCategory::C1, { ID, id, a, b });
			}
		return nullptr;
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationC2(param::hstring CR ID, param::hstring CR idA, param::hstring CR idB)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(idA))
		{
			TheoremNotFound(idA);
			return nullptr;
		}
		if (!theorems.Lookup(idB))
		{
			TheoremNotFound(idB);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP originalA = FetchTheorem(idA, container), originalB = FetchTheorem(idB, container);
			ObjP current = originalA.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Choose)
				goto Error;
			const ObjP pp = current.Left(), aa = current.Right().Left();
			current = originalB.Definition();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Choose || !ObjP::Equal(current.Right().Left(), aa))
				goto Error;
			current = current.Left();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Equal || !ObjP::Equal(current.Left(), pp))
				goto Error;
			current = current.Right();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::False)
				goto Error;
			const TheoremPanelP panel;
			const TheoremP th(container, self.get());
			th.Init(ObjP::Clone(aa, panel, self.get()), ID);
			theorems.Insert(ID, th);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"C2 \u200B"));
				items.Append(th);
				items.Append(RegularText(L" \u200B"));
				items.Append(originalA);
				items.Append(RegularText(L" \u200B"));
				items.Append(originalB);
			}
			container.Text(wstring(L"C2 ").append(hstring(ID)).append(L" ").append(hstring(idA)).append(L" ").append(hstring(idB)));
			�����().Children().Append(container);
			{
				const TheoremP tth(panel, self.get());
				tth.Self(tth);
				tth.Init2(th);
				panel.Name(tth);
			}
			�����().Children().Append(panel);
			return MakeOperation(OperationCategory::C2, { ID, idA, idB });
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationC3(param::hstring CR ID, param::hstring CR id)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP original = FetchTheorem(id, container);
			ObjP current = original.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Choose)
				goto Error;
			ObjP now = current.Right().Left();
			while ((cat = now.Category()) == ObjectCategory::Alias)
				now = now.Right();
			if (cat != ObjectCategory::False)
				goto Error;
			current = current.Left();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::Equal)
				goto Error;
			const ObjP p = current.Left();
			current = current.Right();
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::False)
				goto Error;
			const TheoremPanelP panel;
			const TheoremP th(container, self.get());
			th.Self(th);
			th.Init(ObjP::Clone(p, panel, self.get()), ID);
			theorems.Insert(ID, th);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"C3 \u200B"));
				items.Append(th);
				items.Append(RegularText(L" \u200B"));
				items.Append(original);
			}
			container.Text(wstring(L"C3 ").append(hstring(ID)).append(L" ").append(hstring(id)));
			�����().Children().Append(container);
			{
				const TheoremP tth(panel, self.get());
				tth.Self(tth);
				tth.Init2(th);
				panel.Name(tth);
			}
			�����().Children().Append(panel);
			return MakeOperation(OperationCategory::C3, { ID, id });
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationUF(param::hstring CR ID, param::hstring CR id, param::hstring CR a)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP original = FetchTheorem(id, container);
			ObjP current = original.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::ForallF)
				goto Error;
			if (const ObjP obj = MakeObject(a, container))
			{
				const ObjP f = current.Right();
				{
					TypeP cc = f.MyType();
					while (cc.Category() == TypeCategory::Alias)
						cc = cc.Right();
					if (!Type::Equal(cc.Left(), obj.MyType()))
						goto Error;
				}
				const TheoremPanelP panel;
				const TheoremP th(container, self.get());
				th.Self(th);
				{
					const ObjP apply(panel, self.get());
					apply.Self(apply);
					apply.InitAsApplyF(ObjP::Clone(f, panel, self.get()), ObjP::Clone(obj, panel, self.get()));
					th.Init(apply, ID);
				}
				theorems.Insert(ID, th);
				{
					const UIElementCollection items = container.Items();
					items.Append(RegularText(L"UF \u200B"));
					items.Append(th);
					items.Append(RegularText(L" \u200B"));
					items.Append(original);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : ObjP::Generate(obj))
						items.Append(item);
				}
				container.Text(wstring(L"UF ").append(hstring(ID)).append(L" ").append(hstring(id)).append(L" ").append(hstring(a)));
				�����().Children().Append(container);
				{
					const TheoremP tth(panel, self.get());
					tth.Self(tth);
					tth.Init2(th);
					panel.Name(tth);
				}
				�����().Children().Append(panel);
				return MakeOperation(OperationCategory::UF, { ID, id, a });
			}
			return nullptr;
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationUT(param::hstring CR ID, param::hstring CR id, param::hstring CR t)
	{
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		if (!theorems.Lookup(id))
		{
			TheoremNotFound(id);
			return nullptr;
		}
		{
			const ExpressionContainerP container;
			const TheoremP original = FetchTheorem(id, container);
			ObjP current = original.Definition();
			ObjectCategory cat;
			while ((cat = current.Category()) == ObjectCategory::Alias)
				current = current.Right();
			if (cat != ObjectCategory::ForallT)
				goto Error;
			if (const TypeP tp = MakeType(t, container))
			{
				const TheoremPanelP panel;
				const TheoremP th(container, self.get());
				th.Self(th);
				{
					const ObjP apply(panel, self.get());
					apply.Self(apply);
					{
						const ObjP obj(panel, self.get());
						obj.Self(obj);
						obj.InitAsType(TypeP::Clone(tp, panel, self.get()));
						apply.InitAsApplyT(ObjP::Clone(current.Right(), panel, self.get()), obj);
					}
					th.Init(apply, ID);
				}
				theorems.Insert(ID, th);
				{
					const UIElementCollection items = container.Items();
					items.Append(RegularText(L"UT \u200B"));
					items.Append(th);
					items.Append(RegularText(L" \u200B"));
					items.Append(original);
					items.Append(RegularText(L" \u200B"));
					for (UIElement CR item : TypeP::Generate(tp))
						items.Append(item);
				}
				container.Text(wstring(L"UT ").append(hstring(ID)).append(L" ").append(hstring(id)).append(L" ").append(hstring(t)));
				�����().Children().Append(container);
				{
					const TheoremP tth(panel, self.get());
					tth.Self(tth);
					tth.Init2(th);
					panel.Name(tth);
				}
				�����().Children().Append(panel);
				return MakeOperation(OperationCategory::UT, { ID, id, t });
			}
			return nullptr;
		}
	Error:
		InvalidReason();
		return nullptr;
	}

	OperationP MainPage::OperationScope(param::hstring CR NAME)
	{
		if (!CheckScopeName(NAME))
		{
			ScopeNameExist(NAME);
			return nullptr;
		}
		const MainPageP child;
		child.Self(child);
		child.Parent(self.get());
		child.Root(root.get());
		child.Header(NAME);
		const UIElementCollection path = child.Path();
		for (UIElement CR item : ·��().Children())
			path.Append(item.as<BreadcrumbItem>().Clone(child));
		path.Append(BreadcrumbItemP(child, child));
		children.emplace(NAME, child);
		const ExpressionContainerP container;
		{
			const UIElementCollection items = container.Items();
			items.Append(RegularText(L"Scope \u200B"));
			items.Append(NakedButton(box_value(NAME), [child, this](IInspectable CR, RoutedEventArgs CR)
				{
					if (child.Position())
						child.Display();
					else
						GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
				}));
		}
		container.Text(wstring(L"Scope ").append(hstring(NAME)));
		�����().Children().Append(container);
		root.get().Focus(child);
		GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
		return MakeOperation(OperationCategory::Scope, { NAME });
	}

	OperationP MainPage::OperationAssume(param::hstring CR NAME, param::hstring CR ID, param::hstring CR p)
	{
		if (!CheckScopeName(NAME))
		{
			ScopeNameExist(NAME);
			return nullptr;
		}
		if (!CheckTheoremName(ID))
		{
			TheoremNameExist(ID);
			return nullptr;
		}
		const ExpressionContainerP container;
		if (const ObjP obj = MakeObject(p, container))
		{
			{
				auto current = obj.MyType();
				TypeCategory cat;
				while ((cat = current.Category()) == TypeCategory::Alias)
					current = current.Right();
				if (cat != TypeCategory::Bool)
				{
					const Flyout flyout;
					{
						const TextBlock block;
						{
							const Run run;
							run.Text(ID);
							run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-LightItalic.ttf#Cascadia Code"));
							block.Inlines().Append(run);
						}
						{
							const Run run;
							run.Text(ResourceLoader().GetString(L"NotATheorem"));
							block.Inlines().Append(run);
						}
						flyout.Content(block);
					}
					flyout.ShowAt(�������());
					return nullptr;
				}
			}
			const MainPageP child;
			child.Self(child);
			child.Parent(self.get());
			child.Root(root.get());
			child.Header(NAME);
			const UIElementCollection path = child.Path();
			for (UIElement CR item : ·��().Children())
				path.Append(item.as<BreadcrumbItem>().Clone(child));
			path.Append(BreadcrumbItemP(child, child));
			children.emplace(NAME, child);
			const TheoremPanelP panel;
			const TheoremP th(container, self.get());
			th.Self(th);
			th.Init(ObjP::Clone(obj, panel, child), ID);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"Assume \u200B"));
				items.Append(NakedButton(box_value(NAME), [child, this](IInspectable CR, RoutedEventArgs CR)
					{
						if (child.Position())
							child.Display();
						else
							GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
					}));
				items.Append(RegularText(L" \u200B"));
				items.Append(th);
				items.Append(RegularText(L" \u200B"));
				for (UIElement CR item : ObjP::Generate(obj))
					items.Append(item);
			}
			container.Text(wstring(L"Assume ").append(hstring(NAME)).append(L" ").append(hstring(ID)).append(L" ").append(hstring(p)));
			�����().Children().Append(container);
			root.get().Focus(child);
			{
				const TheoremP tth(panel, child);
				tth.Self(tth);
				tth.Init2(th);
				panel.Name(tth);
				child.InitAsAssume(tth, panel);
			}
			GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
			return MakeOperation(OperationCategory::Assume, { NAME, ID, p });
		}
		return nullptr;
	}

	OperationP MainPage::OperationArbitraryObject(param::hstring CR NAME, param::hstring CR name, param::hstring CR t)
	{
		if (!CheckScopeName(NAME))
		{
			ScopeNameExist(NAME);
			return nullptr;
		}
		if (!CheckObjectName(name))
		{
			ObjectNameExist(name);
			return nullptr;
		}
		const ExpressionContainerP container;
		if (const TypeP tp = MakeType(t, container))
		{
			const MainPageP child;
			child.Self(child);
			child.Parent(self.get());
			child.Root(root.get());
			child.Header(NAME);
			const UIElementCollection path = child.Path();
			for (UIElement CR item : ·��().Children())
				path.Append(item.as<BreadcrumbItem>().Clone(child));
			path.Append(BreadcrumbItemP(child, child));
			children.emplace(NAME, child);
			const ObjP param(container, self.get());
			param.Self(param);
			param.InitAsParameter(tp, name);
			child.InitAsArbitraryO(param);
			{
				const UIElementCollection items = container.Items();
				items.Append(RegularText(L"ArbitraryObject \u200B"));
				items.Append(NakedButton(box_value(NAME), [child, this](IInspectable CR, RoutedEventArgs CR)
					{
						if (child.Position())
							child.Display();
						else
							GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
					}));
				items.Append(RegularText(L" \u200B"));
				items.Append(param);
				items.Append(RegularText(L" \u200B"));
				for (UIElement CR item : TypeP::Generate(tp))
					items.Append(item);
			}
			container.Text(wstring(L"ArbitraryObject ").append(hstring(NAME)).append(L" ").append(hstring(name)).append(L" ").append(hstring(t)));
			�����().Children().Append(container);
			root.get().Focus(child);
			GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
			return MakeOperation(OperationCategory::ArbitraryO, { NAME, name, t });
		}
		return nullptr;
	}

	OperationP MainPage::OperationArbitraryType(param::hstring CR NAME, param::hstring CR name)
	{
		if (!CheckScopeName(NAME))
		{
			ScopeNameExist(NAME);
			return nullptr;
		}
		if (!CheckTypeName(name))
		{
			TypeNameExist(name);
			return nullptr;
		}
		const MainPageP child;
		child.Self(child);
		child.Parent(self.get());
		child.Root(root.get());
		child.Header(NAME);
		const UIElementCollection path = child.Path();
		for (UIElement CR item : ·��().Children())
			path.Append(item.as<BreadcrumbItem>().Clone(child));
		path.Append(BreadcrumbItemP(child, child));
		children.emplace(NAME, child);
		const ExpressionContainerP container;
		const TypeP tp(container, self.get());
		tp.Self(tp);
		tp.InitAsParameter(name);
		child.InitAsArbitraryT(tp);
		{
			const UIElementCollection items = container.Items();
			items.Append(RegularText(L"ArbitraryType \u200B"));
			items.Append(NakedButton(box_value(NAME), [child, this](IInspectable CR, RoutedEventArgs CR)
				{
					if (child.Position())
						child.Display();
					else
						GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
				}));
			items.Append(RegularText(L" \u200B"));
			items.Append(tp);
		}
		container.Text(wstring(L"ArbitraryType ").append(hstring(NAME)).append(L" ").append(hstring(name)));
		�����().Children().Append(container);
		root.get().Focus(child);
		GetMainWindow[position.get()].get().ChangePage(position.get(), child, box_value(child.Header()));
		return MakeOperation(OperationCategory::ArbitraryT, { NAME, name });
	}

	OperationP MainPage::OperationExport(param::hstring CR ID)
	{
		if (!theorems.InCurrent(ID))
		{
			const TextBlock block;
			{
				const Run run;
				run.Text(ID);
				run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
				block.Inlines().Append(run);
			}
			{
				const Run run;
				run.Text(ResourceLoader().GetString(L"�����ڵ�ǰ��Χ"));
				block.Inlines().Append(run);
			}
			error_flyout.Content(block);
			return nullptr;
		}
		if (exported.contains(ID))
		{
			const TextBlock block;
			{
				const Run run;
				run.Text(ID);
				run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
				block.Inlines().Append(run);
			}
			{
				const Run run;
				run.Text(ResourceLoader().GetString(L"�ѵ���"));
				block.Inlines().Append(run);
			}
			error_flyout.Content(block);
			return nullptr;
		}
		if (!parent)
		{
			error_flyout.Content(RegularText(ResourceLoader().GetString(L"��ĸ")));
			return nullptr;
		}
		exported.insert(ID);
		const ExpressionContainerP container;
		const TheoremP original = FetchTheorem(ID, container);
		{
			const UIElementCollection items = container.Items();
			items.Append(RegularText(L"Export \u200B"));
			items.Append(original);
		}
		container.Text(wstring(L"Export ").append(hstring(ID)));
		�����().Children().Append(container);
		const TheoremPanelP panel;
		const TheoremP th(panel, parent.get());
		th.Self(th);
		switch (category)
		{
		case ScopeCategory::Normal:
			th.Init(RemoveCurrent(original.Definition(), panel, parent.get(), nullptr, nullptr), ID);
			break;
		case ScopeCategory::Assume:
		{
			const ObjP choose(panel, parent.get());
			choose.Self(choose);
			{
				const ObjP options(panel, parent.get());
				options.Self(options);
				{
					const ObjP tr(panel, parent.get());
					tr.Self(tr);
					tr.InitAsTrue();
					options.InitAsOptions(RemoveCurrent(original.Definition(), panel, parent.get(), nullptr, nullptr), tr);
				}
				choose.InitAsChoose(ObjP::Clone(assumption.Definition(), panel, parent.get()), options);
			}
			th.Init(choose, ID);
		}
		break;
		case ScopeCategory::Object:
		{
			const ObjP faf(panel, parent.get());
			faf.Self(faf);
			{
				const ObjP df(panel, parent.get());
				df.Self(df);
				{
					const ObjP param = ObjP::Clone(aO, panel, parent.get());
					df.InitAsDeclareF(param, RemoveCurrent(original.Definition(), panel, parent.get(), param, nullptr));
				}
				faf.InitAsForallF(df);
			}
			th.Init(faf, ID);
		}
		break;
		case ScopeCategory::Type:
		{
			const ObjP fat(panel, parent.get());
			fat.Self(fat);
			{
				const ObjP dt(panel, parent.get());
				dt.Self(dt);
				{
					const ObjP param(panel, parent.get());
					param.Self(param);
					const TypeP tp = TypeP::Clone(aT, panel, parent.get());
					param.InitAsType(tp);
					dt.InitAsDeclareT(param, RemoveCurrent(original.Definition(), panel, parent.get(), nullptr, tp));
				}
				fat.InitAsForallT(dt);
			}
			th.Init(fat, ID);
		}
		}
		panel.Name(th);
		to_export.emplace_back(th, panel);
		return MakeOperation(OperationCategory::Export, { ID });
	}

	OperationP MainPage::OperationExit()
	{
		if (!parent)
		{
			error_flyout.Content(RegularText(ResourceLoader().GetString(L"��ĸ")));
			return nullptr;
		}
		const MainPageP pa = parent.get();
		for (auto CR[th, panel] : to_export)
			pa.AddTheorem(th, panel);
		root.get().Focus(pa);
		if (pa.Position())
			pa.Display();
		else
			GetMainWindow[position.get()].get().ChangePage(position.get(), pa, box_value(pa.Header()));
		return MakeOperation(OperationCategory::Exit, {});
	}

	ObjP MainPage::MakeObject(hstring CR s, UIElement CR _position)
	{
		enum class Cat : int8_t { LB, TF, TT, PR, DF, DT, AF, AT, FA, EQ, CO };
		constexpr array LeftP{ 114514, 1, 1, 1, 7, 7, 3, 3, 5, 5, 7 };
		const LinkedMapP recoverO = objects, recoverT = types;
		stack<variant<ObjP, hstring, Cat>> st;
		bool parameter{};
		auto calc = [&](size_t CR p, int CR pre = 514)->variant<ObjP, hstring, nullptr_t>
			{
				if (st.empty() || holds_alternative<Cat>(st.top()))
				{
					SimpleError(L"������Ŵ���", s, p);
					return nullptr;
				}
				if (holds_alternative<hstring>(st.top()))
				{
					const auto str = get<hstring>(st.top());
					st.pop();
					if (st.empty())
						return str;
					if (!holds_alternative<Cat>(st.top()))
					{
						SimpleError(L"�������Ӵ���", s, p);
						return nullptr;
					}
					const auto op = get<Cat>(st.top());
					if (LeftP[static_cast<size_t>(op)] > pre)
						return str;
					st.pop();
					const ObjP result(_position, self.get());
					result.Self(result);
					if (op == Cat::FA)
						if (const ObjP now = FetchObject(str, _position))
						{
							TypeP typeR = now.MyType();
							TypeCategory catR;
							while ((catR = typeR.Category()) == TypeCategory::Alias)
								typeR = typeR.Right();
							if (catR == TypeCategory::Function)
							{
								TypeP typeRR = typeR.Right();
								TypeCategory catRR;
								while ((catRR = typeRR.Category()) == TypeCategory::Alias)
									typeRR = typeRR.Right();
								if (catRR != TypeCategory::Bool)
								{
									SimpleError(L"ȫ�����ʴ���", s, p);
									return nullptr;
								}
								result.InitAsForallF(now);
							}
							else if (catR == TypeCategory::Template)
							{
								TypeP typeRR = typeR.Right();
								TypeCategory catRR;
								while ((catRR = typeRR.Category()) == TypeCategory::Alias)
									typeRR = typeRR.Right();
								if (catRR != TypeCategory::Bool)
								{
									SimpleError(L"ȫ�����ʴ���", s, p);
									return nullptr;
								}
								result.InitAsForallT(now);
							}
							else
							{
								SimpleError(L"ȫ�����ʴ���", s, p);
								return nullptr;
							}
						}
						else
							goto NotAnObject;
					else
					{
						if (op == Cat::PR)
							if (const TypeP tp = FetchType(str, _position))
							{
								const auto name = get<hstring>(st.top());
								result.InitAsParameter(tp, name);
								const LinkedMapP n;
								n.Parent(objects);
								(objects = n).Insert(name, result);
								parameter = true;
							}
							else
								goto NotAType;
						else if (const auto objL = get<ObjP>(st.top()); op == Cat::TF)
							if (const TypeP tp = FetchType(str, _position))
							{
								const TypeP ftp(_position, self.get());
								ftp.Self(ftp);
								ftp.InitAsFunction(objL.MyType(), tp);
								result.InitAsType(ftp);
							}
							else
								goto NotAType;
						else if (op == Cat::TT)
							if (const TypeP tp = FetchType(str, _position))
							{
								const TypeP ttp(_position, self.get());
								ttp.Self(ttp);
								ttp.InitAsTemplate(objL.MyType(), tp);
								result.InitAsType(ttp);
								types = types.Parent();
							}
							else
								goto NotAType;
						else if (op == Cat::DF)
							if (const ObjP now = FetchObject(str, _position))
							{
								result.InitAsDeclareF(objL, now);
								objects = objects.Parent();
							}
							else
								goto NotAnObject;
						else if (op == Cat::DT)
							if (const ObjP now = FetchObject(str, _position))
							{
								result.InitAsDeclareT(objL, now);
								types = types.Parent();
							}
							else
								goto NotAnObject;
						else if (op == Cat::AF)
							if (const ObjP now = FetchObject(str, _position))
							{
								TypeP typeL = objL.MyType();
								while (typeL.Category() == TypeCategory::Alias)
									typeL = typeL.Right();
								if (!TypeP::Equal(typeL.Left(), now.MyType()))
								{
									SimpleError(L"��������", s, p);
									return nullptr;
								}
								result.InitAsApplyF(objL, now);
							}
							else
								goto NotAnObject;
						else if (op == Cat::AT)
							if (const TypeP tp = FetchType(str, _position))
							{
								const ObjP now(_position, self.get());
								now.Self(now);
								now.InitAsType(tp);
								result.InitAsApplyT(objL, now);
							}
							else
								goto NotAType;
						else if (op == Cat::EQ)
							if (const ObjP now = FetchObject(str, _position))
							{
								if (!TypeP::Equal(objL.MyType(), now.MyType()))
								{
									SimpleError(L"���ڴ���", s, p);
									return nullptr;
								}
								result.InitAsEqual(objL, now);
							}
							else
								goto NotAnObject;
						else if (const ObjP now = FetchObject(str, _position))
						{
							if (!TypeP::Equal(objL.MyType(), now.MyType()))
							{
								SimpleError(L"ѡ�����", s, p);
								return nullptr;
							}
							result.InitAsOptions(objL, now);
						}
						else
							goto NotAnObject;
						st.pop();
					}
					st.push(result);
					goto MainPart;
				NotAnObject:
					ComplexError(L"����������", str, s, p);
					return nullptr;
				NotAType:
					ComplexError(L"����������", str, s, p);
					return nullptr;
				}
			MainPart:
				auto now = get<ObjP>(st.top());
				st.pop();
				while (st.size())
				{
					if (!holds_alternative<Cat>(st.top()))
					{
						SimpleError(L"�������Ӵ���", s, p);
						return nullptr;
					}
					const auto op = get<Cat>(st.top());
					if (LeftP[static_cast<size_t>(op)] > pre)
						break;
					st.pop();
					if (parameter)
					{
						SimpleError(L"�˴���Ӧ�в���", s, p);
						return nullptr;
					}
					const ObjP result(_position, self.get());
					result.Self(result);
					if (op == Cat::FA)
					{
						if (now.Category() == ObjectCategory::Type)
							goto UnexpectedType;
						if (now.Category() == ObjectCategory::Options)
							goto Ternary;
						TypeP typeR = now.MyType();
						TypeCategory catR;
						while ((catR = typeR.Category()) == TypeCategory::Alias)
							typeR = typeR.Right();
						if (catR == TypeCategory::Function)
						{
							TypeP typeRR = typeR.Right();
							TypeCategory catRR;
							while ((catRR = typeRR.Category()) == TypeCategory::Alias)
								typeRR = typeRR.Right();
							if (catRR != TypeCategory::Bool)
							{
								SimpleError(L"ȫ�����ʴ���", s, p);
								return nullptr;
							}
							result.InitAsForallF(now);
						}
						else if (catR == TypeCategory::Template)
						{
							TypeP typeRR = typeR.Right();
							TypeCategory catRR;
							while ((catRR = typeRR.Category()) == TypeCategory::Alias)
								typeRR = typeRR.Right();
							if (catRR != TypeCategory::Bool)
							{
								SimpleError(L"ȫ�����ʴ���", s, p);
								return nullptr;
							}
							result.InitAsForallT(now);
						}
						else
						{
							SimpleError(L"ȫ�����ʴ���", s, p);
							return nullptr;
						}
					}
					else
					{
						if (op == Cat::PR)
						{
							if (now.Category() != ObjectCategory::Type)
								goto UnexpectedObject;
							const auto name = get<hstring>(st.top());
							result.InitAsParameter(now.MyType(), name);
							const LinkedMapP n;
							n.Parent(objects);
							(objects = n).Insert(name, result);
							parameter = true;
						}
						else if (const auto objL = get<ObjP>(st.top()); op == Cat::TF)
						{
							if (now.Category() != ObjectCategory::Type)
								goto UnexpectedObject;
							const TypeP tp(_position, self.get());
							tp.Self(tp);
							tp.InitAsFunction(objL.MyType(), now.MyType());
							result.InitAsType(tp);
						}
						else if (op == Cat::TT)
						{
							if (now.Category() != ObjectCategory::Type)
								goto UnexpectedObject;
							const TypeP tp(_position, self.get());
							tp.Self(tp);
							tp.InitAsTemplate(objL.MyType(), now.MyType());
							result.InitAsType(tp);
							types = types.Parent();
						}
						else if (op == Cat::DF)
						{
							if (now.Category() == ObjectCategory::Type)
								goto UnexpectedType;
							if (now.Category() == ObjectCategory::Options)
								goto Ternary;
							result.InitAsDeclareF(objL, now);
							objects = objects.Parent();
						}
						else if (op == Cat::DT)
						{
							if (now.Category() == ObjectCategory::Type)
								goto UnexpectedType;
							if (now.Category() == ObjectCategory::Options)
								goto Ternary;
							result.InitAsDeclareT(objL, now);
							types = types.Parent();
						}
						else if (op == Cat::AF)
						{
							if (now.Category() == ObjectCategory::Type)
								goto UnexpectedType;
							if (now.Category() == ObjectCategory::Options)
								goto Ternary;
							TypeP typeL = objL.MyType();
							while (typeL.Category() == TypeCategory::Alias)
								typeL = typeL.Right();
							if (!TypeP::Equal(typeL.Left(), now.MyType()))
							{
								SimpleError(L"��������", s, p);
								return nullptr;
							}
							result.InitAsApplyF(objL, now);
						}
						else if (op == Cat::AT)
						{
							if (now.Category() != ObjectCategory::Type)
								goto UnexpectedObject;
							result.InitAsApplyT(objL, now);
						}
						else if (op == Cat::EQ)
						{
							if (now.Category() == ObjectCategory::Type)
								goto UnexpectedType;
							if (now.Category() == ObjectCategory::Options)
								goto Ternary;
							if (!TypeP::Equal(objL.MyType(), now.MyType()))
							{
								SimpleError(L"���ڴ���", s, p);
								return nullptr;
							}
							result.InitAsEqual(objL, now);
						}
						else
						{
							if (now.Category() == ObjectCategory::Type)
								goto UnexpectedType;
							if (now.Category() == ObjectCategory::Options)
							{
								TypeP typeL = objL.MyType();
								TypeCategory catL;
								while ((catL = typeL.Category()) == TypeCategory::Alias)
									typeL = typeL.Right();
								if (catL != TypeCategory::Bool)
								{
									SimpleError(L"ѡ�����", s, p);
									return nullptr;
								}
								result.InitAsChoose(objL, now);
							}
							else
							{
								if (!TypeP::Equal(objL.MyType(), now.MyType()))
								{
									SimpleError(L"ѡ�����", s, p);
									return nullptr;
								}
								result.InitAsOptions(objL, now);
							}
						}
						st.pop();
					}
					now = result;
				}
				return now;
			UnexpectedType:
				SimpleError(L"�˴���Ӧ������", s, p);
				return nullptr;
			UnexpectedObject:
				SimpleError(L"�˴���Ӧ������", s, p);
				return nullptr;
			Ternary:
				SimpleError(L"��Ԫ�������?��Ҫ����Ԫ", s, p);
				return nullptr;
			};
		for (auto i = s.cbegin(); i < s.cend();)
			if (size_t p = i - s.cbegin(); *i == L'(')
				st.push(Cat::LB), ++i;
			else if (*i == L')')
				if (const auto result = calc(p); holds_alternative<nullptr_t>(result))
					goto Error;
				else
				{
					if (st.empty())
					{
						SimpleError(L"ȱ��������", s, p);
						goto Error;
					}
					st.pop();
					if (holds_alternative<ObjP>(result))
						st.push(get<ObjP>(result));
					else
						st.push(get<hstring>(result));
					++i;
				}
			else if (*i == L'~')
				if (const auto result = calc(p, 0); holds_alternative<nullptr_t>(result))
					goto Error;
				else
				{
					if (parameter)
					{
						SimpleError(L"�˴���Ӧ�в���", s, p);
						goto Error;
					}
					if (holds_alternative<hstring>(result))
						if (const auto str = get<hstring>(result); const TypeP tp = FetchType(str, _position))
						{
							const ObjP now(_position, self.get());
							now.Self(now);
							now.InitAsType(tp);
							st.push(now);
							st.push(Cat::TF);
						}
						else
						{
							SimpleError(L"����������", s, p);
							goto Error;
						}
					else if (const auto o = get<ObjP>(result); o.Category() != ObjectCategory::Type)
					{
						SimpleError(L"�˴���Ӧ������", s, p);
						goto Error;
					}
					else
					{
						st.push(o);
						st.push(Cat::TF);
					}
					++i;
				}
			else if (*i == L'`')
				if (const auto result = calc(p, 0); holds_alternative<nullptr_t>(result))
					goto Error;
				else if (holds_alternative<hstring>(result))
				{
					const hstring str = get<hstring>(result);
					const TypeP tp(_position, self.get());
					tp.Self(tp);
					tp.InitAsParameter(str);
					const ObjP now(_position, self.get());
					now.Self(now);
					now.InitAsType(tp);
					st.push(now);
					st.push(Cat::TT);
					const LinkedMapP n;
					n.Parent(types);
					(types = n).Insert(str, tp);
					++i;
				}
				else
				{
					SimpleError(L"�˴�Ӧ�в���", s, p);
					goto Error;
				}
			else if (*i == L':')
				if (const auto result = calc(p, 0); holds_alternative<nullptr_t>(result))
					goto Error;
				else if (holds_alternative<hstring>(result))
				{
					st.push(get<hstring>(result));
					st.push(Cat::PR);
					++i;
				}
				else
				{
					SimpleError(L"��:��ǰ��Ӧ�Ǳ��ʽ", s, p);
					goto Error;
				}
			else if (*i == L'@')
				if (const auto result = calc(p, 2); holds_alternative<nullptr_t>(result))
					goto Error;
				else
				{
					if (holds_alternative<hstring>(result))
					{
						const auto str = get<hstring>(result);
						TypeP tp(_position, self.get());
						tp.Self(tp);
						tp.InitAsParameter(str);
						const ObjP now(_position, self.get());
						now.Self(now);
						now.InitAsType(tp);
						st.push(now);
						st.push(Cat::DT);
						LinkedMapP n;
						n.Parent(types);
						(types = n).Insert(str, tp);
					}
					else if (!parameter)
					{
						SimpleError(L"�˴�Ӧ�в���", s, p);
						goto Error;
					}
					else
					{
						parameter = false;
						st.push(get<ObjP>(result));
						st.push(Cat::DF);
					}
					++i;
				}
			else if (*i == L'#')
				if (const auto result = calc(p, 4); holds_alternative<nullptr_t>(result))
					goto Error;
				else
				{
					if (parameter)
					{
						SimpleError(L"�˴���Ӧ�в���", s, p);
						goto Error;
					}
					ObjP now = nullptr;
					if (holds_alternative<ObjP>(result))
						now = get<ObjP>(result);
					else if (!((now = FetchObject(get<hstring>(result), _position))))
					{
						ComplexError(L"����������", get<hstring>(result), s, p);
						goto Error;
					}
					if (now.Category() == ObjectCategory::Type)
					{
						SimpleError(L"�˴���Ӧ������", s, p);
						goto Error;
					}
					if (now.Category() == ObjectCategory::Options)
					{
						SimpleError(L"��Ԫ�������?��Ҫ����Ԫ", s, p);
						goto Error;
					}
					TypeP typeL = now.MyType();
					TypeCategory catL;
					while ((catL = typeL.Category()) == TypeCategory::Alias)
						typeL = typeL.Right();
					if (catL == TypeCategory::Function)
					{
						st.push(now);
						st.push(Cat::AF);
					}
					else if (catL == TypeCategory::Template)
					{
						st.push(now);
						st.push(Cat::AT);
					}
					else
					{
						SimpleError(L"����ģ�����", s, p);
						goto Error;
					}
					++i;
				}
			else if (*i == L'!')
				st.push(Cat::FA), ++i;
			else if (*i == L'=')
				if (const auto result = calc(p, 6); holds_alternative<nullptr_t>(result))
					goto Error;
				else
				{
					if (parameter)
					{
						SimpleError(L"�˴���Ӧ�в���", s, p);
						goto Error;
					}
					ObjP now = nullptr;
					if (holds_alternative<ObjP>(result))
						now = get<ObjP>(result);
					else if (!((now = FetchObject(get<hstring>(result), _position))))
					{
						ComplexError(L"����������", get<hstring>(result), s, p);
						goto Error;
					}
					if (now.Category() == ObjectCategory::Type)
					{
						SimpleError(L"�˴���Ӧ������", s, p);
						goto Error;
					}
					if (now.Category() == ObjectCategory::Options)
					{
						SimpleError(L"��Ԫ�������?��Ҫ����Ԫ", s, p);
						goto Error;
					}
					st.push(now);
					st.push(Cat::EQ);
					++i;
				}
			else if (*i == L'?')
				if (const auto result = calc(p, 6); holds_alternative<nullptr_t>(result))
					goto Error;
				else
				{
					if (parameter)
					{
						SimpleError(L"�˴���Ӧ�в���", s, p);
						goto Error;
					}
					ObjP now = nullptr;
					if (holds_alternative<ObjP>(result))
						now = get<ObjP>(result);
					else if (!((now = FetchObject(get<hstring>(result), _position))))
					{
						ComplexError(L"����������", get<hstring>(result), s, p);
						goto Error;
					}
					if (now.Category() == ObjectCategory::Type)
					{
						SimpleError(L"�˴���Ӧ������", s, p);
						goto Error;
					}
					if (now.Category() == ObjectCategory::Options)
					{
						SimpleError(L"��Ԫ�������?��Ҫ����Ԫ", s, p);
						goto Error;
					}
					st.push(now);
					st.push(Cat::CO);
					++i;
				}
			else
			{
				auto j = i;
				while (j < s.cend() && IsValidName(*j))
					++j;
				st.push(hstring(wstring(i, j)));
				i = j;
			}
		if (const auto result = calc(s.size()); !holds_alternative<nullptr_t>(result))
		{
			if (st.empty())
			{
				if (parameter)
				{
					SimpleError(L"�˴���Ӧ�в���", s, s.size());
					goto Error;
				}
				ObjP now = nullptr;
				if (holds_alternative<ObjP>(result))
					now = get<ObjP>(result);
				else if (!((now = FetchObject(get<hstring>(result), _position))))
				{
					ComplexError(L"����������", get<hstring>(result), s, s.size());
					goto Error;
				}
				if (now.Category() == ObjectCategory::Type)
				{
					SimpleError(L"�˴���Ӧ������", s, s.size());
					goto Error;
				}
				if (now.Category() == ObjectCategory::Options)
				{
					SimpleError(L"��Ԫ�������?��Ҫ����Ԫ", s, s.size());
					goto Error;
				}
				return now;
			}
			SimpleError(L"ȱ��������", s, s.size());
		}
	Error:
		objects = recoverO, types = recoverT;
		return nullptr;
	}

	TypeP MainPage::MakeType(hstring CR s, UIElement CR _position)
	{
		enum class Cat : int8_t { LB, F, T };
		constexpr array LeftP{ 114514, 1, 1 };
		const LinkedMapP recover = types;
		stack<variant<TypeP, hstring, Cat>> st;
		auto calc = [&](size_t CR p, int CR pre = 514)->variant<TypeP, hstring, nullptr_t>
			{
				if (st.empty() || holds_alternative<Cat>(st.top()))
				{
					SimpleError(L"���ͷ��Ŵ���", s, p);
					return nullptr;
				}
				if (holds_alternative<hstring>(st.top()))
				{
					const auto str = get<hstring>(st.top());
					st.pop();
					if (st.empty())
						return str;
					if (!holds_alternative<Cat>(st.top()))
					{
						SimpleError(L"�������Ӵ���", s, p);
						return nullptr;
					}
					const auto op = get<Cat>(st.top());
					if (LeftP[static_cast<size_t>(op)] > pre)
						return str;
					st.pop();
					if (const TypeP now = FetchType(str, _position))
					{
						const TypeP result(_position, self.get());
						result.Self(result);
						if (op == Cat::F)
							result.InitAsFunction(get<TypeP>(st.top()), now);
						else
						{
							result.InitAsTemplate(get<TypeP>(st.top()), now);
							types = types.Parent();
						}
						st.pop();
						st.push(result);
					}
					else
					{
						ComplexError(L"����������", str, s, p);
						return nullptr;
					}
				}
				auto now = get<TypeP>(st.top());
				st.pop();
				while (st.size())
				{
					if (!holds_alternative<Cat>(st.top()))
					{
						SimpleError(L"�������Ӵ���", s, p);
						return nullptr;
					}
					const auto op = get<Cat>(st.top());
					if (LeftP[static_cast<size_t>(op)] > pre)
						break;
					st.pop();
					const TypeP result(_position, self.get());
					result.Self(result);
					if (op == Cat::F)
						result.InitAsFunction(get<TypeP>(st.top()), now);
					else
					{
						result.InitAsTemplate(get<TypeP>(st.top()), now);
						types = types.Parent();
					}
					st.pop();
					now = result;
				}
				return now;
			};
		for (auto i = s.cbegin(); i < s.cend();)
			if (size_t p = i - s.cbegin(); *i == L'(')
				st.push(Cat::LB), ++i;
			else if (*i == L')')
				if (const auto result = calc(p); holds_alternative<nullptr_t>(result))
					goto Error;
				else
				{
					if (st.empty())
					{
						SimpleError(L"ȱ��������", s, p);
						goto Error;
					}
					st.pop();
					if (holds_alternative<TypeP>(result))
						st.push(get<TypeP>(result));
					else
						st.push(get<hstring>(result));
					++i;
				}
			else if (*i == L'~')
				if (const auto result = calc(p, 0); holds_alternative<nullptr_t>(result))
					goto Error;
				else
				{
					if (holds_alternative<hstring>(result))
						if (const TypeP now = FetchType(get<hstring>(result), _position))
						{
							st.push(now);
							st.push(Cat::F);
						}
						else
						{
							SimpleError(L"�������Ӵ���", s, p);
							return nullptr;
						}
					else
					{
						st.push(get<TypeP>(result));
						st.push(Cat::F);
					}
					++i;
				}
			else if (*i == L'`')
				if (const auto result = calc(p, 0); holds_alternative<nullptr_t>(result))
					goto Error;
				else if (holds_alternative<hstring>(result))
				{
					const auto str = get<hstring>(result);
					const TypeP now(_position, self.get());
					now.Self(now);
					now.InitAsParameter(str);
					st.push(now);
					st.push(Cat::T);
					const LinkedMapP n;
					n.Parent(types);
					(types = n).Insert(str, now);
					++i;
				}
				else
				{
					SimpleError(L"�˴�Ӧ�в���", s, p);
					goto Error;
				}
			else
			{
				auto j = i;
				while (j < s.cend() && IsValidName(*j))
					++j;
				st.push(hstring(wstring(i, j)));
				i = j;
			}
		if (const auto result = calc(s.size()); !std::holds_alternative<nullptr_t>(result))
			if (st.empty())
			{
				if (holds_alternative<TypeP>(result))
					return get<TypeP>(result);
				if (TypeP now = FetchType(get<hstring>(result), _position))
					return now;
				ComplexError(L"����������", get<hstring>(result), s, s.size());
			}
			else
				SimpleError(L"ȱ��������", s, s.size());
	Error:
		types = recover;
		return nullptr;
	}

	ObjP MainPage::RemoveCurrent(ObjP CR _original, UIElement CR _position, MainPageP CR _page_position, ObjP CR replaceO, TypeP CR replaceT) const
	{
		unordered_map<ObjP, ObjP> mapO;
		unordered_map<TypeP, TypeP> mapT;
		return [&mapO, &mapT, &_position, &_page_position, &replaceO, &replaceT, this](this auto&& transform, ObjP CR original)->ObjP
			{
				auto tt = [&mapT, &_position, &_page_position, &replaceT, this](this auto&& tt, TypeP CR original)->TypeP
					{
						TypeP result(_position, _page_position);
						result.Self(result);
						switch (original.Category())
						{
						case TypeCategory::Bool:
							result.InitAsBool();
							break;
						case TypeCategory::Function:
							result.InitAsFunction(tt(original.Left()), tt(original.Right()));
							break;
						case TypeCategory::Template:
						{
							const TypeP sb = tt(original.Left());
							result.InitAsTemplate(sb, tt(original.Right()));
						}
						break;
						case TypeCategory::Alias:
							if (types.InCurrent(original.Label()))
								result = tt(original.Right());
							else
								result.InitAsAlias2(original.Left());
							break;
						case TypeCategory::Parameter:
							if (const TypeP oL = original.Left(); original != oL)
								result.InitAsParameter2(mapT.contains(oL) ? mapT[oL] : types.InCurrent(oL.Label()) ? replaceT : oL);
							else
							{
								result.InitAsParameter(original.Label());
								mapT[original] = result;
							}
						}
						return result;
					};
				ObjP result(_position, _page_position);
				result.Self(result);
				switch (original.Category())
				{
				case ObjectCategory::Type:
					result.InitAsType(tt(original.MyType()));
					break;
				case ObjectCategory::True:
					result.InitAsTrue();
					break;
				case ObjectCategory::False:
					result.InitAsFalse();
					break;
				case ObjectCategory::DeclareF:
				{
					const ObjP sb = transform(original.Left());
					result.InitAsDeclareF(sb, transform(original.Right()));
				}
				break;
				case ObjectCategory::DeclareT:
				{
					const ObjP sb = transform(original.Left());
					result.InitAsDeclareT(sb, transform(original.Right()));
				}
				break;
				case ObjectCategory::ApplyF:
					result.InitAsApplyF(transform(original.Left()), transform(original.Right()));
					break;
				case ObjectCategory::ApplyT:
					result.InitAsApplyT(transform(original.Left()), transform(original.Right()));
					break;
				case ObjectCategory::ForallF:
					result.InitAsForallF(transform(original.Right()));
					break;
				case ObjectCategory::ForallT:
					result.InitAsForallT(transform(original.Right()));
					break;
				case ObjectCategory::Equal:
					result.InitAsEqual(transform(original.Left()), transform(original.Right()));
					break;
				case ObjectCategory::Options:
					result.InitAsOptions(transform(original.Left()), transform(original.Right()));
					break;
				case ObjectCategory::Choose:
					result.InitAsChoose(transform(original.Left()), transform(original.Right()));
					break;
				case ObjectCategory::Alias:
					if (objects.InCurrent(original.Label()))
						result = transform(original.Right());
					else
						result.InitAsAlias2(original.Left());
					break;
				case ObjectCategory::Parameter:
					if (const ObjP oL = original.Left(); original != oL)
						result.InitAsParameter2(mapO.contains(oL) ? mapO[oL] : objects.InCurrent(oL.Label()) ? replaceO : oL);
					else
					{
						result.InitAsParameter(tt(original.MyType()), original.Label());
						mapO[original] = result;
					}
				}
				return result;
			}(_original);
	}

	void MainPage::SimpleError(param::hstring CR _id, param::hstring CR _whole, size_t CR _position) const
	{
		const IVector<Inline> message = single_threaded_vector<Inline>();
		{
			const Run block;
			block.Text(ResourceLoader().GetString(_id));
			message.Append(block);
		}
		error_flyout.Content(ErrorFlyoutP(message.GetView(), _position, _whole));
	}

	void MainPage::ComplexError(param::hstring CR _id, param::hstring CR _name, param::hstring CR _whole, size_t CR _position) const
	{
		const IVector<Inline> message = single_threaded_vector<Inline>();
		{
			const Run run;
			run.Text(_name);
			run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
			message.Append(run);
		}
		{
			const Run run;
			run.Text(ResourceLoader().GetString(_id));
			message.Append(run);
		}
		error_flyout.Content(ErrorFlyoutP(message.GetView(), _position, _whole));
	}

	void MainPage::InvalidReason() const
	{
		error_flyout.Content(RegularText(ResourceLoader().GetString(L"���ݲ���Ҫ��")));
	}

	void MainPage::ObjectNameExist(param::hstring CR _name) const
	{
		const TextBlock block;
		{
			const Run run;
			run.Text(_name);
			run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
			block.Inlines().Append(run);
		}
		{
			const Run run;
			run.Text(ResourceLoader().GetString(L"ObjectNameExist"));
			block.Inlines().Append(run);
		}
		error_flyout.Content(block);
	}

	void MainPage::TypeNameExist(param::hstring CR _name) const
	{
		const TextBlock block;
		{
			const Run run;
			run.Text(_name);
			run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
			block.Inlines().Append(run);
		}
		{
			const Run run;
			run.Text(ResourceLoader().GetString(L"TypeNameExist"));
			block.Inlines().Append(run);
		}
		error_flyout.Content(block);
	}

	void MainPage::TheoremNameExist(param::hstring CR _name) const
	{
		const TextBlock block;
		{
			const Run run;
			run.Text(_name);
			run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
			block.Inlines().Append(run);
		}
		{
			const Run run;
			run.Text(ResourceLoader().GetString(L"TheoremNameExist"));
			block.Inlines().Append(run);
		}
		error_flyout.Content(block);
	}

	void MainPage::ScopeNameExist(param::hstring CR _name) const
	{
		const TextBlock block;
		{
			const Run run;
			run.Text(_name);
			run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
			block.Inlines().Append(run);
		}
		{
			const Run run;
			run.Text(ResourceLoader().GetString(L"ScopeNameExist"));
			block.Inlines().Append(run);
		}
		error_flyout.Content(block);
	}

	void MainPage::TheoremNotFound(param::hstring CR _name) const
	{
		const TextBlock block;
		{
			const Run run;
			run.Text(_name);
			run.FontFamily(Media::FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
			block.Inlines().Append(run);
		}
		{
			const Run run;
			run.Text(ResourceLoader().GetString(L"NotATheoremName"));
			block.Inlines().Append(run);
		}
		error_flyout.Content(block);
	}

	ObjP MainPage::FetchObject(param::hstring CR _key, UIElement CR _position) const
	{
		ObjP result(_position, self.get());
		result.Self(result);
		if (_key == L"true")
			result.InitAsTrue();
		else if (_key == L"false")
			result.InitAsFalse();
		else if (const auto def = objects.Lookup(_key).as<ObjP>())
			if (def.Category() == ObjectCategory::Alias)
				result.InitAsAlias2(def);
			else
				result.InitAsParameter2(def);
		else
			return nullptr;
		return result;
	}

	TypeP MainPage::FetchType(param::hstring CR _key, UIElement CR _position) const
	{
		TypeP result(_position, self.get());
		result.Self(result);
		if (_key == L"bool")
			result.InitAsBool();
		else if (const auto def = types.Lookup(_key).as<TypeP>())
			if (def.Category() == TypeCategory::Alias)
				result.InitAsAlias2(def);
			else
				result.InitAsParameter2(def);
		else
			return nullptr;
		return result;
	}

	TheoremP MainPage::FetchTheorem(param::hstring CR _key, UIElement CR _position) const
	{
		TheoremP result(_position, self.get());
		result.Self(result);
		if (const auto def = theorems.Lookup(_key).as<TheoremP>())
			result.Init2(def);
		else
			return nullptr;
		return result;
	}

	bool MainPage::CheckIllegal(wstring CR s)
	{
		for (auto CR c : s)
			if (c <= L' ')
				return false;
		return true;
	}

	bool MainPage::CheckIllegal(wstring CR s, auto CR check)
	{
		for (auto CR c : s)
			if (!check(c))
				return false;
		return true;
	}
}
