#include "stdafx.h"
#include "ControllerQT.h"

ControllerQT* ControllerQT::singleton = nullptr;

ControllerQT::ControllerQT() : config("controller"), connector(config["connectTo"])
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

bool ControllerQT::updateUser(User* oldUser, const QString& name, const QString& surname, const QString& fatherName, const QString& passportNum, const QString& login, const int& userRole)
{
	bool res = true;

	QMessageBox mb;
	mb.setWindowTitle("Информация об обновлении пользователя");

	if (name.isEmpty() || surname.isEmpty() || passportNum.isEmpty() || login.isEmpty())
	{
		mb.setText("Пожалуйста, заполните все поля, обозначенные символом '*'");
		mb.exec();
		return false;
	}

	User u(oldUser->getId(), oldUser->getCryptedPassword());
	u.setLogin(login.toStdString());
	u.setPrivelege(itoUP(userRole + 1));

	UserPersonalInfo upi;
	upi.setName(name.toStdString());
	upi.setSurname(surname.toStdString());
	upi.setFatherName(fatherName.toStdString());
	upi.setPassportNumber(passportNum.toStdString());

	u.setPersonalInfo(upi);

	try
	{
		connector.Update(u);
		mb.setText("Информация о пользователе успешно обновлена");
		*oldUser = u;
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка обновлении информации о пользователя. Текст ошибки:\n" + std::string(e.what())));
		res = false;
	}

	mb.exec();
	return res;
}

bool ControllerQT::deleteBook(Book& u)
{
	try
	{
		connector.Delete(u);
	}
	catch (std::exception& e)
	{
		QMessageBox mb;
		mb.setWindowTitle("Информация об удалении издания");
		mb.setText(QString::fromStdString("Ошибка удаления издания. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
		return false;
	}

	return true;
}

std::map<Transfer, Book> ControllerQT::getAllNonClosedTransfers(const User* u)
{
	using namespace bsoncxx::builder::stream;

	std::map<Transfer, Book> res;
	document filter{};

	filter <<
		"user_id" << u->getId().getObjectID() <<
		"return_date" << open_document <<
		"$exists" << false <<
		close_document;

	std::list<Transfer> transfers;
	try
	{
		connector.Get(transfers, filter << finalize);
	}
	catch (std::exception& e)
	{
		QMessageBox mb;
		mb.setWindowTitle("Информация о получении списка выдач");
		mb.setText(QString::fromStdString("Ошибка получения списка выдач. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
		return res;
	}

	for (auto t : transfers)
	{
		std::list<Book> books;

		document info{};

		info <<
			"copies" << open_document <<
				"$elemMatch" << open_document <<
					"_id" << open_document <<
						"$in" << open_array <<
							t.getCopyId().getObjectID() <<
						close_array <<
					close_document <<
				close_document <<
			close_document;

		try
		{
			connector.Get(books, info << finalize);
		}
		catch (std::exception& e)
		{
			QMessageBox mb;
			mb.setWindowTitle("Информация о поиске изданий");
			mb.setText(QString::fromStdString("Ошибка получения списка изданий. Текст ошибки:\n" + std::string(e.what())));
			mb.exec();
			return std::map<Transfer, Book>();
		}
		
		if (books.size() != 1)
		{
			QMessageBox mb;
			mb.setWindowTitle("Информация о получении списка выдач");
			mb.setText("Ошибка получения списка изданий. Возможно, нарушена уникальность идентификаторов копий");
			mb.exec();
			return std::map<Transfer, Book>();
		}

		res.emplace(t, books.front());
	}

	return res;
}

std::list<Transfer> ControllerQT::getAllNonClosedTransfers(const Book* b)
{
	using namespace bsoncxx::builder::stream;

	std::list<Transfer> res;
	for (auto bc : b->getCopies())
	{
		document filter{};

		filter <<
			"copy_id" << bc.getId().getObjectID() <<
			"return_date" << open_document <<
			"$exists" << false <<
			close_document;

		std::list<Transfer> transfers;
		try
		{
			connector.Get(transfers, filter << finalize);
			if (transfers.size() > 1)
			{
				throw std::exception("Экземпляр был выдан сразу нескольким людям");
			}
			res.insert(res.end(), transfers.begin(), transfers.end());
		}
		catch (std::exception& e)
		{
			QMessageBox mb;
			mb.setWindowTitle("Информация о получении списка выдач");
			mb.setText(QString::fromStdString("Ошибка получения списка выдач. Текст ошибки:\n" + std::string(e.what())));
			mb.exec();
			return std::list<Transfer>();
		}
	}
	return res;
}

bool ControllerQT::getOutBook(User* u, const QString& bookID)
{
	QMessageBox mb;
	mb.setIcon(QMessageBox::Information);
	mb.setWindowTitle("Информация о выдаче издания");

	bool res = true;

	try
	{
		if (connector.GiveOutBook(BookCopy(DB_ID(bookID.toStdString())), *u) == DB_ID())
		{
			mb.setText("Ошибка выдачи издания");
			res = false;
		}
		else
		{
			mb.setText("Выдача прошла успешно");
		}
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка выдачи издания. Текст ошибки:\n" + std::string(e.what())));
		res = false;
	}

	mb.exec();
	return res;
}

bool ControllerQT::renewBook(const Transfer& transfer)
{
	QMessageBox mb;
	mb.setIcon(QMessageBox::Information);
	mb.setWindowTitle("Информация о продлении издания");
	mb.setText("Продление прошло успешно");

	bool res = true;

	try
	{
		connector.RenewBookTime(BookCopy(transfer.getCopyId()));
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка продления издания. Текст ошибки:\n" + std::string(e.what())));
		res = false;
	}

	mb.exec();
	return res;
}

bool ControllerQT::returnBook(const Transfer& transfer, Book* book)
{
	QMessageBox mb;
	mb.setIcon(QMessageBox::Information);
	mb.setWindowTitle("Информация о возврате издания");
	mb.setText("Возврат прошел успешно");

	bool res = true;

	using namespace bsoncxx::builder::stream;

	try
	{
		connector.ReturnBookCopy(BookCopy(transfer.getCopyId()));
		if (book)
		{
			std::list<Book> books;
			connector.Get(books, document{} << "_id" << book->getId().getObjectID() << finalize);
			*book = books.front();
		}
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка возврата издания. Текст ошибки:\n" + std::string(e.what())));
		res = false;
	}

	mb.exec();
	return res;
}

bool ControllerQT::archieveBook(BookCopy* copy, Book* book)
{
	QMessageBox mb;
	mb.setIcon(QMessageBox::Information);
	mb.setWindowTitle("Информация об архивации издания");
	mb.setText("Архивация прошла успешно");

	bool res = true;

	using namespace bsoncxx::builder::stream;

	try
	{
		connector.ArchieveBookCopy(*copy);
		if (book)
		{
			std::list<Book> books;
			connector.Get(books, document{} << "_id" << book->getId().getObjectID() << finalize);
			*book = books.front();
		}
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка архивации издания. Текст ошибки:\n" + std::string(e.what())));
		res = false;
	}

	mb.exec();
	return res;
}

Author ControllerQT::addAuthor(const QString& surname, const QString& name, const QString& fatherName)
{
	using namespace bsoncxx::builder::stream;
	Author res;

	QMessageBox mb;
	mb.setWindowTitle("Информация о добавлении автора");
	mb.setIcon(QMessageBox::Information);

	if (surname.isEmpty() || name.isEmpty())
	{
		mb.setText("Пожалуйста, заполните все поля, отмеченные символом '*'");
		mb.exec();
		return res;
	}

	Author author;
	author.setName(name.toStdString());
	author.setSurname(surname.toStdString());
	author.setFatherName(fatherName.toStdString());

	try
	{
		connector.Add(author);
		mb.setText("Автор успешно добавлен");
	}
	catch (NonUniqueException&)
	{
		mb.setText("Автор успешно найден");
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка добавления автора. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
		return res;
	}

	std::list<Author> authors;
	try
	{
		connector.Get(authors, document{} <<
		              "name" << name.toStdString() <<
		              "surname" << surname.toStdString() <<
		              "father_name" << fatherName.toStdString() <<
		              finalize);
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка добавления автора. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
		return res;
	}

	if (authors.size() != 1)
	{
		mb.setText("Ошибка уникальности полей в базе данных. Пожалуйста, обратитесь к системному администратору");
	}
	else
	{
		res = authors.front();
	}

	mb.exec();
	return res;
}

std::list<Book> ControllerQT::findBooks(const std::multimap<QString, QString> filters)
{
	using namespace bsoncxx::builder::stream;

	std::set<QString> keys;
	document info{};

	for (auto f : filters)
	{
		keys.insert(f.first);
	}

	//формируме совпадающие элементы по "или"
	for (auto k : keys)
	{
		if (k == AJIOB_Const::authorSurname)
		{
			continue;
		}

		document d{};
		auto inArray = d << k.toStdString() << open_document << "$in" << open_array;

		for (auto it = filters.find(k); it != filters.end(); ++it)
		{
			inArray = inArray << it->second.toStdString();
		}

		auto i = inArray << close_array << close_document;

		info << concatenate(i << finalize);
	}

	std::list<Book> books;

	if (filters.find(AJIOB_Const::authorSurname) != filters.end())
	{
		std::multimap<QString, QString> authorsMap;

		for (auto it = filters.find(AJIOB_Const::authorSurname); it != filters.end(); ++it)
		{
			authorsMap.emplace("surname", it->second);
		}

		std::list<Author> authors = findAuthors(authorsMap);
		/*if (authors.empty())
		{
			return books;
		}*/

		document d{};
		auto inArray = d << "authors" << open_document << "$in" << open_array;

		for (auto a : authors)
		{
			inArray = inArray << a.getId().getObjectID();
		}

		auto i = inArray << close_array << close_document;

		info << concatenate(i << finalize);
	}

	try
	{
		connector.Get(books, info << finalize);
	}
	catch (std::exception& e)
	{
		QMessageBox mb;
		mb.setWindowTitle("Информация о поиске изданий");
		mb.setText(QString::fromStdString("Ошибка получения списка изданий. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
	}

	return books;
}

std::list<Author> ControllerQT::findAuthors(const std::multimap<QString, QString> filters)
{
	using namespace bsoncxx::builder::stream;

	std::list<Author> authors;
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
		connector.Get(authors, info << finalize);
	}
	catch (std::exception& e)
	{
		QMessageBox mb;
		mb.setWindowTitle("Информация о поиске авторов");
		mb.setText(QString::fromStdString("Ошибка получения списка авторов. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
	}

	return authors;
}

bool ControllerQT::resetPassword(User* u)
{
	QMessageBox mb;
	mb.setWindowTitle("Смена пароля");
	mb.setIcon(QMessageBox::Information);

	User tmp = *u;

	try
	{
		tmp.resetPassword();
		connector.Update(tmp);
		mb.setText("Пароль сброшен успешно");
		mb.exec();
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка сброса пароля. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
		return false;
	}

	*u = tmp;
	return true;
}

bool ControllerQT::addBook(const QString& ISBN, const std::list<Author>& authors, const QString& name, const long int& year, const unsigned long int& pages, const unsigned long int& copies)
{
	bool res = true;

	Book book(DB_ID(), copies);
	book.setName(name.toStdString());
	book.setYear(year);
	book.setPageCount(pages);
	book.setAuthors(authors);


	QMessageBox mb;
	mb.setWindowTitle("Информация о добавлении издания");

	ISBNClass isbn;
	if (!isbn.ParseString(ISBN.toStdString()))
	{
		mb.setText("Некорректный ISBN номер");
		mb.exec();
		return res;
	}
	book.setISBN(isbn);

	try
	{
		connector.Add(book);
		mb.setText("Издание успешно добавлено");
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка добавления издания. Текст ошибки:\n" + std::string(e.what())));
		res = false;
	}

	mb.exec();
	return res;
}

bool ControllerQT::updateBook(Book* oldBook, const QString& ISBN, const std::list<Author>& authors, const QString& name, const int& year, const int& pages, const int& copies)
{
	bool res = true;

	QMessageBox mb;
	mb.setWindowTitle("Информация об обновлении издания");

	if (ISBN.isEmpty() || name.isEmpty())
	{
		mb.setText("Пожалуйста, заполните все поля, обозначенные символом '*'");
		mb.exec();
		return false;
	}

	if (copies < oldBook->getCopies().size())
	{
		mb.setText("Количество копий издания не может быть уменьшено");
		mb.exec();
		return false;
	}

	try
	{
		Book book(oldBook->getId());
		book.setISBN(ISBNClass(ISBN.toStdString()));
		book.setAuthors(authors);
		book.setName(name.toStdString());
		book.setYear(year);
		book.setPageCount(pages);
		
		for (auto copy : oldBook->getCopies())
		{
			book.addCopy(copy);
		}

		while (book.getCopies().size() < copies)
		{
			book.addCopy(BookCopy(DB_ID(false)));
		}

		connector.Update(book);
		mb.setText("Информация об издании успешно обновлена");
		*oldBook = book;
	}
	catch (std::exception& e)
	{
		mb.setText(QString::fromStdString("Ошибка обновлении информации об издании. Текст ошибки:\n" + std::string(e.what())));
		res = false;
	}

	mb.exec();
	return res;
}

bool ControllerQT::deleteUser(User& u)
{
	try
	{
		connector.Delete(u);
	}
	catch (std::exception& e)
	{
		QMessageBox mb;
		mb.setWindowTitle("Информация об удалении пользователя");
		mb.setText(QString::fromStdString("Ошибка удаления пользователя. Текст ошибки:\n" + std::string(e.what())));
		mb.exec();
		return false;
	}

	return true;
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
	catch (std::exception& e)
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
		mb.setText("Пароль изменен успешно");
		mb.exec();
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

User ControllerQT::loginAsGuest()
{
	return connector.LoginAsGuest();
}
