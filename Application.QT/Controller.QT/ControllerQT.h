#pragma once

#include "controllerqt_global.h"

class User;

class CONTROLLERQT_EXPORT ControllerQT
{
	ControllerQT();
	ControllerQT(const ControllerQT&);
	~ControllerQT();

	static ControllerQT* singleton;
public:
	static ControllerQT& get();

	User checkAuth(const QString& login, const QString& password);
};
