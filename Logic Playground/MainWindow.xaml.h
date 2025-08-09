#pragma once

#include "MainWindow.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        void Self(MainWindowP CR _self);
        void OpenNewTab();
        void OpenTab(Page CR _page, IInspectable CR _header);
        bool CloseTab(TabViewItem CR _item);
        bool ChangePage(TabViewItem CR _item, Page CR _page, IInspectable CR _header);
        void AddTabItem(TabViewItem CR _item);
        void RemoveTabItem(TabViewItem CR _item);
        void Display(TabViewItem CR _item);

        void ActivatedEvent(IInspectable CR, WindowActivatedEventArgs CR);
        void ClosedEvent(IInspectable CR, WindowEventArgs CR args);
        void AddTabButton(TabView CR, IInspectable CR);
        void TabClose(TabView CR, TabViewTabCloseRequestedEventArgs CR args);
        void TearOutWindow(TabView CR, TabViewTabTearOutWindowRequestedEventArgs CR args);
        void TearOut(TabView CR, TabViewTabTearOutRequestedEventArgs CR args);
        static void Dropping(TabView CR, TabViewExternalTornOutTabsDroppingEventArgs CR args);
        void Dropped(TabView CR, TabViewExternalTornOutTabsDroppedEventArgs CR args);

    private:
        weak_ref<MainWindowP> self;
        bool activated;
        MainWindowP new_window = nullptr;
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
