#pragma once

#include "controllerqt_global.h"
#include "DBConnector/DBConnector.h"

class User;
class DBConnector;

class CONTROLLERQT_EXPORT ControllerQT
{
	ControllerQT();
	ControllerQT(const ControllerQT&);
	~ControllerQT();

	static ControllerQT* singleton;

	DBConnector connector;

public:
	static ControllerQT& get();

	User checkAuth(const QString& login, const QString& password);
	bool addUser(const QString& name, const QString& surname, const QString& fatherName, const QString& passportNum, const QString& login, const int& userRole);
};
