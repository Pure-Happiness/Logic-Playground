#pragma once
#include <chrono>
#include <random>
#include <ranges>
#include <stack>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include <windows.h>
#include <unknwn.h>
#include <restrictederrorinfo.h>
#include <hstring.h>

// Undefine GetCurrentTime macro to prevent
// conflict with Storyboard::GetCurrentTime
#undef GetCurrentTime

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.AccessCache.h>
#include <winrt/Windows.System.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Documents.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Input.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.Windows.AppNotifications.h>
#include <winrt/Microsoft.Windows.AppNotifications.Builder.h>
#include <winrt/Microsoft.Windows.ApplicationModel.Resources.h>
#include <winrt/Microsoft.Windows.Globalization.h>
#include <winrt/Microsoft.Windows.Storage.h>
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include <winrt/Logic_Playground.h>
#include <wil/cppwinrt_helpers.h>

#define CR const&
#define ThemeRedPurple (Application::Current().RequestedTheme() == ApplicationTheme::Light ? SolidColorBrush({ 0xFF, 0xFF, 0, 0 }) : SolidColorBrush({ 0xFF, 0xFF, 0, 0xFF }))
#define ThemeGreenYellow (Application::Current().RequestedTheme() == ApplicationTheme::Light ? SolidColorBrush({ 0xFF, 0, 0xFF, 0 }) : SolidColorBrush({ 0xFF, 0xFF, 0xFF, 0 }))
#define ThemeBlueAqua (Application::Current().RequestedTheme() == ApplicationTheme::Light ? SolidColorBrush({ 0xFF, 0, 0, 0xFF }) : SolidColorBrush({ 0xFF, 0, 0xFF, 0xFF }))

using namespace std;
using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::ApplicationModel::DataTransfer;
using namespace winrt::Windows::Storage::AccessCache;
using namespace winrt::Windows::System;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Controls::Primitives;
using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt::Microsoft::UI::Xaml::Documents;
using namespace winrt::Microsoft::UI::Xaml::Input;
using namespace winrt::Microsoft::Windows::AppNotifications;
using namespace winrt::Microsoft::Windows::AppNotifications::Builder;
using namespace winrt::Microsoft::Windows::ApplicationModel::Resources;
using namespace winrt::Microsoft::Windows::Globalization;
using namespace winrt::Microsoft::Windows::Storage;
using namespace winrt::Microsoft::Windows::Storage::Pickers;
using Windows::Globalization::Calendar;
using Windows::Storage::CreationCollisionOption;
using Windows::Storage::FileIO;
using Windows::Storage::StorageFile;

using MainWindowP = Logic_Playground::MainWindow;
using NewTabP = Logic_Playground::NewTab;
using MainPageP = Logic_Playground::MainPage;
using SettingsP = Logic_Playground::Settings;
using RecentListItemP = Logic_Playground::RecentListItem;
using BreadcrumbItemP = Logic_Playground::BreadcrumbItem;
using ExpressionContainerP = Logic_Playground::ExpressionContainer;
using TheoremPanelP = Logic_Playground::TheoremPanel;
using BracketP = Logic_Playground::Bracket;
using ObjP = Logic_Playground::Obj;
using TypeP = Logic_Playground::Type;
using TheoremP = Logic_Playground::Theorem;
using ErrorFlyoutP = Logic_Playground::ErrorFlyout;
using FileRootP = Logic_Playground::FileRoot;
using LinkedMapP = Logic_Playground::LinkedMap;
using OperationP = Logic_Playground::Operation;

inline unordered_map<TabViewItem, weak_ref<MainWindowP>> GetMainWindow;
inline unordered_map<TabViewItem, FileRootP> GetRoot;
inline TypeP HiddenBool = nullptr;
inline mt19937 GetRandom(random_device()() ^ static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));

inline TextBlock RegularText(param::hstring CR text)
{
	const TextBlock result;
	result.Text(text);
	return result;
}

inline TextBlock RegularCode(param::hstring CR text)
{
	const TextBlock result;
	result.Text(text);
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-Regular.ttf#Cascadia Code"));
	return result;
}

inline TextBlock ItalicCode(param::hstring CR text)
{
	const TextBlock result;
	result.Text(text);
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-Italic.ttf#Cascadia Code"));
	return result;
}

inline TextBlock BoldCode(param::hstring CR text)
{
	const TextBlock result;
	result.Text(text);
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-Bold.ttf#Cascadia Code"));
	return result;
}

inline TextBlock BoldItalicCode(param::hstring CR text)
{
	const TextBlock result;
	result.Text(text);
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-BoldItalic.ttf#Cascadia Code"));
	return result;
}

inline TextBlock LightCode(param::hstring CR text)
{
	const TextBlock result;
	result.Text(text);
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-Light.ttf#Cascadia Code"));
	return result;
}

inline TextBlock LightItalicCode(param::hstring CR text)
{
	const TextBlock result;
	result.Text(text);
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-LightItalic.ttf#Cascadia Code"));
	return result;
}

inline TextBlock ObjectDefinition()
{
	const TextBlock result;
	result.Text(L"<==");
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-LightItalic.ttf#Cascadia Code"));
	result.Foreground(ThemeGreenYellow);
	return result;
}

inline TextBlock TypeDefinition()
{
	const TextBlock result;
	result.Text(L"<--");
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-LightItalic.ttf#Cascadia Code"));
	result.Foreground(ThemeGreenYellow);
	return result;
}

inline TextBlock Colon()
{
	const TextBlock result;
	result.Text(L":");
	result.FontFamily(FontFamily(L"ms-appx:///Assets/CascadiaCode-LightItalic.ttf#Cascadia Code"));
	result.Foreground(ThemeGreenYellow);
	return result;
}

inline Button NakedButton(IInspectable CR content, RoutedEventHandler CR handler)
{
	const Button result;
	result.Background(SolidColorBrush());
	result.Padding({});
	result.CornerRadius({});
	result.BorderThickness({});
	result.Content(content);
	result.Click(handler);
	return result;
}

constexpr bool IsValidName(wchar_t CR ch)
{
	return ch > L' ' && ch != L'~' && ch != L'`' && ch != L'!' && ch != L'@' && ch != L'#' && ch != L'=' && ch != L'?' && ch != L':' && ch != L'(' && ch != L')';
}

constexpr bool IsValidTypeExpression(wchar_t CR ch)
{
	return ch > L' ' && ch != L'!' && ch != L'@' && ch != L'#' && ch != L'=' && ch != L'?' && ch != L':';
}
