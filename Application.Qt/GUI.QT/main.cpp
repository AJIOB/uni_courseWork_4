#include "stdafx.h"
#include "GUI_MainWindow.h"
#include "GUI_AuthClass.h"

int main(int argc, char* argv[])
{
	DB_START

	QApplication a(argc, argv);

	GUI_AuthClass auth;
	auto res = auth.exec();
	if (res == UPtoi(UserPriveleges::none))
	{
		return 0;
	}

	User user = auth.getUser();
	if (res == UPtoi(UserPriveleges::guest))
	{
		user.setPrivelege(UserPriveleges::guest);
	}

	GUI_MainWindow w(user);
	w.show();
	return a.exec();
}
