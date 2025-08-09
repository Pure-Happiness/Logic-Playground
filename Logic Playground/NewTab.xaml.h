#pragma once

#include "NewTab.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct NewTab : NewTabT<NewTab>
    {
        void Self(NewTabP CR _self);
        [[nodiscard]] TabViewItem Position() const;
        void Position(TabViewItem CR _position);
        void RemoveItem(UIElement CR _item);
        fire_and_forget OpenFile(StorageFile CR _file) const;

        void LoadedEvent(IInspectable CR, RoutedEventArgs CR);
        void NewFileClick(IInspectable CR, RoutedEventArgs CR) const;
        fire_and_forget OpenFileClick(IInspectable CR, RoutedEventArgs CR);
        void SettingsClick(IInspectable CR, RoutedEventArgs CR) const;

    private:
        weak_ref<NewTabP> self;
        weak_ref<TabViewItem> position;
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct NewTab : NewTabT<NewTab, implementation::NewTab>
    {
    };
}
