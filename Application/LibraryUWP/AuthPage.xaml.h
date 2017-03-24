//
// AuthPage.xaml.h
// Declaration of the AuthPage class.
//

#pragma once

#include "AuthPage.g.h"

namespace LibraryUWP
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class AuthPage sealed
	{
	public:
		AuthPage();

	private:
		void ExitEvent(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
