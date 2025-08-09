#pragma once

#include "Theorem.g.h"

namespace winrt::Logic_Playground::implementation
{
    struct Theorem : TheoremT<Theorem>
    {
        Theorem() = default;
        Theorem(UIElement CR _position, MainPageP CR _page_position);
        void Self(TheoremP CR _self);
        [[nodiscard]] MainPageP PagePosition() const;
        [[nodiscard]] hstring Label() const;
        [[nodiscard]] TheoremP Declaration() const;
        [[nodiscard]] ObjP Definition() const;
        [[nodiscard]] IVector<TheoremP> Sames() const;
        void ChainCheck();
        void ChainUncheck();
        void Display() const;
        void Init(ObjP CR _definition, param::hstring CR _label);
        void Init2(TheoremP CR _declaration);

        void LoadedEvent(IInspectable CR, RoutedEventArgs CR);

    private:
        weak_ref<TheoremP> self;
        weak_ref<UIElement> position;
        weak_ref<MainPageP> page_position;
        hstring label;
        weak_ref<TheoremP> declaration;
        ObjP definition = nullptr;
        IVector<TheoremP> sames;
        bool chain_click{}, loaded{};
    };
}

namespace winrt::Logic_Playground::factory_implementation
{
    struct Theorem : TheoremT<Theorem, implementation::Theorem>
    {
    };
}
