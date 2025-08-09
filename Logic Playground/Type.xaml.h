#pragma once

#include "Type.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct Type : TypeT<Type>
	{
		Type() = default;
		Type(UIElement CR _position, MainPageP CR _page_position);
		void Self(TypeP CR _self);
		[[nodiscard]] MainPageP PagePosition() const;
		[[nodiscard]] TypeCategory Category() const;
		[[nodiscard]] hstring Label() const;
		[[nodiscard]] TypeP Left() const;
		[[nodiscard]] TypeP Right() const;
		[[nodiscard]] IVector<TypeP> Sames() const;
		void ChainCheck();
		void ChainUncheck();
		void Display() const;
		void InitAsBool();
		void InitAsParameter(param::hstring CR _label);
		void InitAsParameter2(TypeP CR _declaration);
		void InitAsFunction(TypeP CR _left, TypeP CR _right);
		void InitAsTemplate(TypeP CR _left, TypeP CR _right);
		void InitAsAlias(TypeP CR _definition, param::hstring CR _label);
		void InitAsAlias2(TypeP CR _declaration);
		static IVectorView<UIElement> Generate(TypeP CR type);
		static hstring GenerateText(TypeP CR type);
		static bool Equal(TypeP CR x, TypeP CR y);
		static TypeP ApplyTemplate(TypeP temp, TypeP CR arg);
		static TypeP Clone(TypeP CR _original, UIElement CR _position, MainPageP CR _page_position);

		void LoadedEvent(IInspectable CR, RoutedEventArgs CR);

	private:
		weak_ref<TypeP> self;
		weak_ref<UIElement> position;
		weak_ref<MainPageP> page_position;
		hstring label;
		TypeCategory category;
		TypeP left = nullptr, right = nullptr; // For Alias, left is its declaration, right is its definition
		IVector<TypeP> sames;
		bool chain_click{}, loaded{};
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct Type : TypeT<Type, implementation::Type>
	{
	};
}
