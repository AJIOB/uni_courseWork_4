//
// AuthPage.xaml.cpp
// Implementation of the AuthPage class.
//

#include "pch.h"
#include "AuthPage.xaml.h"

using namespace LibraryUWP;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

AuthPage::AuthPage()
{
	InitializeComponent();
}


void LibraryUWP::AuthPage::ExitEvent(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Application::Current->Exit();
}
