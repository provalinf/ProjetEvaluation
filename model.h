#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QtSql>
#include <QDebug>
#include <QtWidgets>
#include <iostream>
#include "sha512.h"

using std::string;
using std::cout;
using std::endl;

struct dbConfig {
		QString hostname;
		QString username;
		QString password;
		QString nameDatabase;
};

class model
{
	private:
		const QString databaseSettings = "config.ini";

		QString login;
		dbConfig dbConf;

		QSqlDatabase database;
	public:
		void loadParamsDatabase();
		model();
		~model();
		bool checkUser(QString login, QString password);
        QSqlQueryModel* getCoursInscrits();
};

#endif // MODEL_H
