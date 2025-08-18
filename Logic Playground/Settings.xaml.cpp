#include "pch.h"
#include "Settings.xaml.h"
#if __has_include("Settings.g.cpp")
#include "Settings.g.cpp"
#endif

namespace winrt::Logic_Playground::implementation
{
	void Settings::Position(TabViewItem CR _position)
	{
		position = _position;
	}

	void Settings::ThemeChoiceLoaded(IInspectable CR, RoutedEventArgs CR)
	{
		if (const IInspectable theme = ApplicationData::GetDefault().LocalSettings().Values().TryLookup(L"Theme"))
			themeChoice().SelectedIndex(unbox_value<int32_t>(theme));
		else
			themeChoice().SelectedIndex(2);
	}

	void Settings::ThemeSelectionChanged(IInspectable CR, SelectionChangedEventArgs CR)
	{
		ApplicationData::GetDefault().LocalSettings().Values().Insert(L"Theme", box_value(themeChoice().SelectedIndex()));
	}

	void Settings::LanguageChoiceLoaded(IInspectable CR, RoutedEventArgs CR)
	{
		const hstring first = *ApplicationLanguages::Languages().First();
		languageChoice().SelectedIndex(first[0] != L'z' || first[1] != L'h');
	}

	void Settings::LanguageSelectionChanged(IInspectable CR, SelectionChangedEventArgs CR)
	{
		ApplicationData::GetDefault().LocalSettings().Values().Insert(L"Language", box_value(languageChoice().SelectedIndex()));
	}

	void Settings::RecoveryLoaded(IInspectable CR, RoutedEventArgs CR)
	{
		const UIElementCollection items = toRecover().Children();
		items.Clear();
		for (const IPropertySet pairs = ApplicationData::GetDefault().LocalSettings().CreateContainer(L"ToRecover", ApplicationDataCreateDisposition::Always).Values(); auto CR[t, _p] : pairs)
		{
			auto p = unbox_value<hstring>(_p);
			for (auto it = p.cbegin(); it < p.cend(); ++it)
				if (*it == L'?')
				{
					hstring original_path(wstring(p.cbegin(), it)), save_path(wstring(++it, p.cend()));
					const TextBlock text;
					if (original_path.size())
					{
						text.Text(t + L' ' + original_path);
						text.Tapped([this, original_path, save_path, t, pairs](IInspectable CR, TappedRoutedEventArgs CR)->fire_and_forget
							{
								try
								{
									const StorageFile save = co_await ApplicationData::GetDefault().LocalFolder().GetFileAsync(save_path);
									try
									{
										const StorageFile original = co_await StorageFile::GetFileFromPathAsync(original_path);
										try
										{
											const FileRootP root;
											root.Self(root);
											root.InitAsFile(original);
											GetMainWindow[position.get()].get().ChangePage(position.get(), root.PageRoot(), box_value(root.PageRoot().Header()));
											const ContentDialog dialog;
											dialog.XamlRoot(XamlRoot());
											dialog.Title(box_value(ResourceLoader().GetString(L"ÇëÉÔºò¡­¡­")));
											dialog.ShowAsync();
											{
												const apartment_context ui;
												co_await resume_after(114514us);
												co_await ui;
											}
											root.ReadContent(co_await FileIO::ReadTextAsync(save));
											dialog.Hide();
											pairs.Remove(t);
											save.DeleteAsync();
										}
										catch (...)
										{
										}
									}
									catch (...)
									{
									}
								}
								catch (...)
								{
								}
							});
					}
					else
					{
						text.Text(t + L' ' + ResourceLoader().GetString(L"Î´ÃüÃû"));
						text.Tapped([this, save_path, t, pairs](IInspectable CR, TappedRoutedEventArgs CR)->fire_and_forget
							{
								try
								{
									const StorageFile save = co_await ApplicationData::GetDefault().LocalFolder().GetFileAsync(save_path);
									try
									{
										const FileRootP root;
										root.Self(root);
										root.InitAsNewFile();
										GetMainWindow[position.get()].get().ChangePage(position.get(), root.PageRoot(), box_value(root.PageRoot().Header()));
										root.ReadContent(co_await FileIO::ReadTextAsync(save));
										pairs.Remove(t);
										save.DeleteAsync();
									}
									catch (...)
									{
									}
								}
								catch (...)
								{
								}
							});
					}
					text.RightTapped([save_path, t, pairs, w_items = weak_ref(items), w_text = weak_ref(text)](IInspectable CR, RightTappedRoutedEventArgs CR)
						{
							const MenuFlyout menu;
							{
								const MenuFlyoutItem item;
								item.Text(ResourceLoader().GetString(L"RemoveItem"));
								item.Click([save_path, t, pairs, w_items, w_text](IInspectable CR, RoutedEventArgs CR)->fire_and_forget
									{
										try
										{
											uint32_t index;
											w_items.get().IndexOf(w_text.get(), index);
											w_items.get().RemoveAt(index);
											pairs.Remove(t);
											(co_await ApplicationData::GetDefault().LocalFolder().GetFileAsync(save_path)).DeleteAsync();
										}
										catch (...)
										{
										}
									});
								menu.Items().Append(item);
							}
							menu.ShowAt(w_text.get());
						});
					items.Append(text);
					break;
				}
		}
	}
}
