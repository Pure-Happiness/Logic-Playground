#pragma once

#include "Obj.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct Obj : ObjT<Obj>
	{
		Obj() = default;
		Obj(UIElement CR _position, MainPageP CR _page_position);
		void Self(ObjP CR _self);
		[[nodiscard]] MainPageP PagePosition() const;
		[[nodiscard]] ObjectCategory Category() const;
		[[nodiscard]] hstring Label() const;
		[[nodiscard]] ObjP Left() const;
		[[nodiscard]] ObjP Right() const;
		[[nodiscard]] TypeP MyType() const;
		[[nodiscard]] IVector<ObjP> Sames() const;
		void ChainCheck();
		void ChainUncheck();
		void Display() const;
		void InitAsTrue();
		void InitAsFalse();
		void InitAsParameter(TypeP CR _type, param::hstring CR _label);
		void InitAsParameter2(ObjP CR _declaration);
		void InitAsType(TypeP CR _type);
		void InitAsDeclareF(ObjP CR _left, ObjP CR _right);
		void InitAsDeclareT(ObjP CR _left, ObjP CR _right);
		void InitAsApplyF(ObjP CR _left, ObjP CR _right);
		void InitAsApplyT(ObjP CR _left, ObjP CR _right);
		void InitAsForallF(ObjP CR _x);
		void InitAsForallT(ObjP CR _x);
		void InitAsEqual(ObjP CR _left, ObjP CR _right);
		void InitAsOptions(ObjP CR _left, ObjP CR _right);
		void InitAsChoose(ObjP CR _left, ObjP CR _right);
		void InitAsAlias(ObjP CR _definition, param::hstring CR _label);
		void InitAsAlias2(ObjP CR _declaration);
		static IVectorView<UIElement> Generate(ObjP CR obj);
		static hstring GenerateText(ObjP CR obj);
		static bool Equal(ObjP CR x, ObjP CR y);
		static ObjP ApplyFunction(ObjP CR func, ObjP CR arg, UIElement CR _position, MainPageP CR _page_position);
		static ObjP ApplyTemplate(ObjP CR temp, TypeP CR arg, UIElement CR _position, MainPageP CR _page_position);
		static ObjP Clone(ObjP CR _original, UIElement CR _position, MainPageP CR _page_position);

		void LoadedEvent(IInspectable CR, RoutedEventArgs CR);

	private:
		weak_ref<ObjP> self;
		weak_ref<UIElement> position;
		weak_ref<MainPageP> page_position;
		hstring label;
		ObjectCategory category;
		ObjP left = nullptr, right = nullptr;
		TypeP type = nullptr;
		IVector<ObjP> sames;
		bool chain_click{}, loaded{};
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct Obj : ObjT<Obj, implementation::Obj>
	{
	};
}
