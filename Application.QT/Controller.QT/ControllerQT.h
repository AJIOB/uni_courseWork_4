#pragma once

#include <QString>
#include "controllerqt_global.h"
#include "DBConnector/DBConnector.h"

class User;
class FindBlockWidget;

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
	User loginAsGuest() const;

	bool addUser(const QString& name, const QString& surname, const QString& fatherName, const QString& passportNum, const QString& login, const int& userRole);
	bool updateUser(User* oldUser, const QString& name, const QString& surname, const QString& fatherName, const QString& passportNum, const QString& login, const int& userRole);
	std::list<User> findUsers(const std::multimap<QString, QString> filters);
	bool deleteUser(User& u);

	bool changePassword(User* u, const QString& oldPassword, const QString& newPassword, const QString& duplicatePassword);
	bool resetPassword(User* u);

	Author addAuthor(const QString& surname, const QString& name, const QString& fatherName);
	std::list<Author> findAuthors(const std::multimap<QString, QString> filters);

	bool addBook(const QString& ISBN, const std::list<Author>& authors, const QString& name, const long int& year, const unsigned long int& pages, const unsigned long int& copies);
	std::list<Book> findBooks(const std::multimap<QString, QString> filters);
	bool deleteBook(Book& u);
};
