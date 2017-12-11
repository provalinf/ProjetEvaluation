#ifndef USERS_H
#define USERS_H
#include <QtSql>
#include "model.h"
#include <iostream>
#include "sha512.h"

using std::string;
using std::cout;
using std::endl;

class users : public model
{
	int idUserConnect;
	bool connected;
	int status;
	public:
		void setDisconnected();
		users(QSqlDatabase* database);
		~users();

		bool checkAndDefinedUser(QString login, QString password);
		void defineUserConnect(int idUser);
		void setConnected();
		int getStatus();
        int getIdUser();
        QSqlQueryModel *getUserById(int id);
};

#endif // USERS_H
