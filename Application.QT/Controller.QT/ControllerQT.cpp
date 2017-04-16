#include "stdafx.h"
#include "ControllerQT.h"

ControllerQT* ControllerQT::singleton = nullptr;

ControllerQT::ControllerQT()
{
}

ControllerQT::ControllerQT(const ControllerQT&)
{
}

ControllerQT::~ControllerQT()
{
}

ControllerQT& ControllerQT::get()
{
	if (!singleton)
	{
		singleton = new ControllerQT();
	}

	return *singleton;
}

User ControllerQT::checkAuth(const QString& login, const QString& password)
{
	return connector.Authorize(login.toStdString(), password.toStdString());
}
