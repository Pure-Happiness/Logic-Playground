#include "pch.h"
#include "App.xaml.h"

namespace winrt::Logic_Playground::implementation
{
	/// <summary>
	/// Initializes the singleton application object.  This is the first line of authored code
	/// executed, and as such is the logical equivalent of main() or WinMain().
	/// </summary>
	App::App()
	{
#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
		UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
			{
				if (IsDebuggerPresent())
				{
					auto errorMessage = e.Message();
					__debugbreak();
				}
			});
#endif
		const ApplicationDataContainer local_settings = ApplicationData::GetDefault().LocalSettings();
		const IPropertySet settings = local_settings.Values();
		if (const IInspectable theme = settings.TryLookup(L"Theme"))
			if (const auto value = unbox_value<int32_t>(theme); value < 2)
				Application::Current().RequestedTheme(static_cast<ApplicationTheme>(value));
		if (const IInspectable language = settings.TryLookup(L"Language"))
			ApplicationLanguages::PrimaryLanguageOverride(unbox_value<int32_t>(language) ? L"en-US" : L"zh-CN");
		const IPropertySet to_recover = local_settings.CreateContainer(L"ToRecover", ApplicationDataCreateDisposition::Always).Values(),
			protective_save = local_settings.CreateContainer(L"ProtectiveSave", ApplicationDataCreateDisposition::Always).Values();
		for (auto CR[k, v] : protective_save)
			to_recover.Insert(k, v);
		protective_save.Clear();
	}

	/// <summary>
	/// Invoked when the application is launched.
	/// </summary>
	/// <param name="e">Details about the launch request and process.</param>
	void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs CR e)
	{
		const MainWindow window;
		window.Self(window);
		window.OpenNewTab();
		window.Activate();
		(HiddenBool = TypeP()).InitAsBool();
	}
}
