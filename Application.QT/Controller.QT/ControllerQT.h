#pragma once

#include <QString>
#include "controllerqt_global.h"
#include "DBConnector/DBConnector.h"

class User;
class FindBlockWidget;
class Transfer;

class CONTROLLERQT_EXPORT ControllerQT
{
	ControllerQT();
	ControllerQT(const ControllerQT&);
	~ControllerQT();

	static ControllerQT* singleton;

	AJIOB::ConfigClass config;
	DBConnector connector;

public:
	static ControllerQT& get();

	User checkAuth(const QString& login, const QString& password);
	User loginAsGuest();

	bool addUser(const QString& name, const QString& surname, const QString& fatherName, const QString& passportNum, const QString& login, const int& userRole);
	bool updateUser(User* oldUser, const QString& name, const QString& surname, const QString& fatherName, const QString& passportNum, const QString& login, const int& userRole);
	std::list<User> findUsers(const std::multimap<QString, QString> filters);
	bool deleteUser(User& u);

	bool changePassword(User* u, const QString& oldPassword, const QString& newPassword, const QString& duplicatePassword);
	bool resetPassword(User* u);

	Author addAuthor(const QString& surname, const QString& name, const QString& fatherName);
	std::list<Author> findAuthors(const std::multimap<QString, QString> filters);

	bool addBook(const QString& ISBN, const std::list<Author>& authors, const QString& name, const long int& year, const unsigned long int& pages, const unsigned long int& copies);
	bool updateBook(Book* oldBook, const QString& ISBN, const std::list<Author>& authors, const QString& name, const int& year, const int& pages, const int& copies);
	std::list<Book> findBooks(const std::multimap<QString, QString> filters);
	bool deleteBook(Book& u);

	std::map<Transfer, Book> getAllNonClosedTransfers(const User* u);
	std::list<Transfer> getAllNonClosedTransfers(const Book* b);

	bool getOutBook(User* u, const QString& bookID);
	bool renewBook(const Transfer& transfer);
	bool returnBook(const Transfer& transfer, Book* book = nullptr);
	bool archieveBook(BookCopy* copy, Book* book);
};
