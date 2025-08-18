#pragma once

#include "FileRoot.g.h"

namespace winrt::Logic_Playground::implementation
{
	struct FileRoot : FileRootT<FileRoot>
	{
		void Self(FileRootP CR _self);
		void InitAsNewFile() const;
		[[nodiscard]] IAsyncOperation<hstring> InitAsFile(StorageFile CR _file);
		fire_and_forget ReadContent(hstring CR _content);
		[[nodiscard]] MainPageP PageRoot() const;
		[[nodiscard]] MainPageP Focus() const;
		void Focus(MainPageP CR _focus);
		void AddOperationS(OperationP CR _operation);
		IAsyncAction Save(TabViewItem CR _position);
		fire_and_forget SaveAs(TabViewItem CR _position);
		void Undo();
		void Redo();
		void Add();
		void JustRelease();
		bool TryRelease(TabViewItem CR _position, Func CR op);

	private:
		weak_ref<FileRootP> self;
		MainPageP page_root, focus = page_root;
		StorageFile file = nullptr, temp_file = nullptr;
		hstring edit_time;
		stack<OperationP> operations, recover;
		uint8_t count;
		wstring content;

		IAsyncOperation<bool> FetchFile(TabViewItem CR _position);
		void SaveFile();
		IAsyncAction CreateTempFile();
	};
}

namespace winrt::Logic_Playground::factory_implementation
{
	struct FileRoot : FileRootT<FileRoot, implementation::FileRoot>
	{
	};
}
