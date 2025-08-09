#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	void MainWindow::Self(MainWindowP CR _self)
	{
		self = _self;
	}

	void MainWindow::OpenNewTab()
	{
		const TabViewItem item;
		{
			const NewTabP page;
			page.Self(page);
			page.Position(item);
			item.Content(page);
		}
		item.Header(box_value(ResourceLoader().GetString(L"NewTab")));
		GetMainWindow.emplace(item, self);
		tabView().TabItems().Append(item);
		tabView().SelectedItem(item);
	}

	void MainWindow::OpenTab(Page CR _page, IInspectable CR _header)
	{
		const TabViewItem item;
		if (const auto new_tab = _page.try_as<NewTabP>())
			new_tab.Position(item);
		else if (const auto main_page = _page.try_as<MainPageP>())
		{
			main_page.Position(item);
			GetRoot.emplace(item, main_page.Root());
			main_page.Root().Add();
		}
		else if (const auto new_set = _page.try_as<SettingsP>())
			new_set.Position(item);
		item.Content(_page);
		item.Header(_header);
		GetMainWindow.emplace(item, self);
		tabView().TabItems().Append(item);
		tabView().SelectedItem(item);
	}

	bool MainWindow::CloseTab(TabViewItem CR _item)
	{
		if (const auto _main_page = _item.Content().try_as<MainPageP>())
		{
			if (!_main_page.Root().TryRelease(_item, [this, _item, _main_page]
				{
					_main_page.Position(nullptr);
					GetRoot.erase(_item);
					GetMainWindow.erase(_item);
					const IVector items = tabView().TabItems();
					{
						uint32_t index;
						items.IndexOf(_item, index);
						items.RemoveAt(index);
					}
					if (!items.Size())
						Close();
				}))
				return false;
			_main_page.Position(nullptr);
			GetRoot.erase(_item);
		}
		GetMainWindow.erase(_item);
		_item.Content(nullptr);
		const IVector items = tabView().TabItems();
		{
			uint32_t index;
			items.IndexOf(_item, index);
			items.RemoveAt(index);
		}
		if (!items.Size())
			Close();
		return true;
	}

	bool MainWindow::ChangePage(TabViewItem CR _item, Page CR _page, IInspectable CR _header)
	{
		const TabViewItem item;
		if (const auto main_page = _page.try_as<MainPageP>())
		{
			main_page.Root().Add();
			GetRoot.emplace(item, main_page.Root());
		}
		if (const auto _main_page = _item.Content().try_as<MainPageP>())
		{
			if (!_main_page.Root().TryRelease(_item, [this, _item, _main_page, _page, _header]
				{
					_main_page.Position(nullptr);
					GetRoot.erase(_item);
					const TabViewItem item;
					if (const auto new_tab = _page.try_as<NewTabP>())
						new_tab.Position(item);
					else if (const auto main_page = _page.try_as<MainPageP>())
						main_page.Position(item);
					else if (const auto new_set = _page.try_as<SettingsP>())
						new_set.Position(item);
					item.Content(_page);
					item.Header(_header);
					GetMainWindow.erase(_item);
					_item.Content(nullptr);
					GetMainWindow.emplace(item, self);
					{
						uint32_t index;
						const IVector items = tabView().TabItems();
						items.IndexOf(_item, index);
						items.SetAt(index, item);
					}
					tabView().SelectedItem(item);
				}))
			{
				if (const auto main_page = _page.try_as<MainPageP>())
				{
					GetRoot.erase(item);
					main_page.Root().JustRelease();
				}
				return false;
			}
			_main_page.Position(nullptr);
			GetRoot.erase(_item);
		}
		if (const auto new_tab = _page.try_as<NewTabP>())
			new_tab.Position(item);
		else if (const auto main_page = _page.try_as<MainPageP>())
			main_page.Position(item);
		else if (const auto new_set = _page.try_as<SettingsP>())
			new_set.Position(item);
		item.Content(_page);
		item.Header(_header);
		GetMainWindow.erase(_item);
		_item.Content(nullptr);
		GetMainWindow.emplace(item, self);
		{
			uint32_t index;
			const IVector items = tabView().TabItems();
			items.IndexOf(_item, index);
			items.SetAt(index, item);
		}
		tabView().SelectedItem(item);
		return false;
	}

	void MainWindow::AddTabItem(TabViewItem CR _item)
	{
		GetMainWindow.emplace(_item, self);
		tabView().TabItems().Append(_item);
		tabView().SelectedItem(_item);
	}

	void MainWindow::RemoveTabItem(TabViewItem CR _item)
	{
		GetMainWindow.erase(_item);
		const IVector items = tabView().TabItems();
		{
			uint32_t index;
			items.IndexOf(_item, index);
			items.RemoveAt(index);
		}
		if (!items.Size())
			Close();
	}

	void MainWindow::Display(TabViewItem CR _item)
	{
		Activate();
		tabView().SelectedItem(_item);
	}

	void MainWindow::ActivatedEvent(IInspectable CR, WindowActivatedEventArgs CR)
	{
		if (!activated)
		{
			activated = true;
			Title(ResourceLoader().GetString(L"AppTitle"));
			ExtendsContentIntoTitleBar(true);
			SetTitleBar(titleBar());
		}
	}

	void MainWindow::ClosedEvent(IInspectable CR, WindowEventArgs CR args)
	{
		for (const IVector tab_items = tabView().TabItems(); IInspectable CR item : vector(tab_items.begin(), tab_items.end()))
			if (!CloseTab(item.as<TabViewItem>()))
			{
				args.Handled(true);
				return;
			}
	}

	void MainWindow::AddTabButton(TabView CR, IInspectable CR)
	{
		OpenNewTab();
	}

	void MainWindow::TabClose(TabView CR, TabViewTabCloseRequestedEventArgs CR args)
	{
		CloseTab(args.Tab());
	}

	void MainWindow::TearOutWindow(TabView CR, TabViewTabTearOutWindowRequestedEventArgs CR args)
	{
		(new_window = make<MainWindow>()).Self(new_window);
		new_window.Activate();
		args.NewWindowId(new_window.AppWindow().Id());
	}

	void MainWindow::TearOut(TabView CR, TabViewTabTearOutRequestedEventArgs CR args)
	{
		for (UIElement CR item : args.Tabs())
		{
			const auto tab_item = item.as<TabViewItem>();
			RemoveTabItem(tab_item);
			new_window.AddTabItem(tab_item);
		}
		new_window = nullptr;
	}

	void MainWindow::Dropping(TabView CR, TabViewExternalTornOutTabsDroppingEventArgs CR args)
	{
		args.AllowDrop(false); // Runtime error during dropping has not been resolved yet, so it is disabled.
	}

	void MainWindow::Dropped(TabView CR, TabViewExternalTornOutTabsDroppedEventArgs CR args)
	{
		for (UIElement CR item : args.Tabs())
		{
			const auto tab_item = item.as<TabViewItem>();
			GetMainWindow[tab_item].get().RemoveTabItem(tab_item);
			GetMainWindow[tab_item] = self;
			tabView().TabItems().InsertAt(args.DropIndex(), tab_item);
			tabView().SelectedItem(tab_item);
		}
	}
}
