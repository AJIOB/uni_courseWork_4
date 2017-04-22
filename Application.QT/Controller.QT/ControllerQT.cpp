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

bool ControllerQT::addUser(const QString& name, const QString& surname, const QString& fatherName, const QString& passportNum, const QString& login, const int& userRole)
{
	bool res = true;

	User u;
	u.setLogin(login.toStdString());
	u.resetPassword();
	u.setPrivelege(itoUP(userRole + 1));

	UserPersonalInfo upi;
	upi.setName(name.toStdString());
	upi.setSurname(surname.toStdString());
	upi.setFatherName(fatherName.toStdString());
	upi.setPassportNumber(passportNum.toStdString());

	u.setPersonalInfo(upi);

	QMessageBox mb;
	mb.setWindowTitle("Информация о добавлении пользователя");

	try
	{
		connector.Add(u);
		mb.setText("Пользователь успешно добавлен");
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка добавления пользователя. Текст ошибки:\n" + std::string(e.what())));
		res = false;
	}

	mb.exec();
	return res;
}

std::list<User> ControllerQT::findUsers(const std::multimap<QString, QString> filters)
{
	using namespace bsoncxx::builder::stream;

	std::list<User> users;
	std::set<QString> keys;
	document info{};

	for (auto f : filters)
	{
		keys.insert(f.first);
	}

	//формируме совпадающие элементы по "или"
	for (auto k : keys)
	{
		document d{};
		auto inArray = d << k.toStdString() << open_document << "$in" << open_array;

		for (auto it = filters.find(k); it != filters.end(); ++it)
		{
			inArray = inArray << it->second.toStdString();
		}

		auto i = inArray << close_array << close_document;
		info << concatenate(i << finalize);
	}

	try
	{
		connector.Get(users, document{}.view(), info << finalize);
	}
	catch(std::exception& e)
	{
		QMessageBox mb;
		mb.setWindowTitle("Информация о поиске пользователей");
		mb.setText(QString::fromStdString("Ошибка получения списка пользователей. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
	}

	return users;
}

bool ControllerQT::changePassword(User* u, const QString& oldPassword, const QString& newPassword, const QString& duplicatePassword)
{
	QMessageBox mb;
	mb.setWindowTitle("Смена пароля");
	mb.setIcon(QMessageBox::Information);

	if (newPassword != duplicatePassword)
	{
		mb.setText("Введенные вами новые пароли не совпадают");
		mb.exec();
		return false;
	}

	if (!u->isPasswordCorrect(oldPassword.toStdString()))
	{
		mb.setText("Ввведен некорректный старый пароль");
		mb.exec();
		return false;
	}

	try
	{
		u->setPassword(newPassword.toStdString(), oldPassword.toStdString());
		connector.Update(*u);
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка смены пароля. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();

		u->setPassword(oldPassword.toStdString(), newPassword.toStdString());
		return false;
	}

	return true;
}
