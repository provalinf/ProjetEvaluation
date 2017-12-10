#ifndef LOADMODEL_H
#define LOADMODEL_H
#include <QString>
#include <QtSql>
#include <QDebug>
#include <QtWidgets>
#include "model.h"
#include "users.h"
#include "courses.h"

struct dbConfig {
		QString hostname;
		QString username;
		QString password;
		QString nameDatabase;
};

class loadmodel
{
	private:
		const QString databaseSettings = "config.ini";
		dbConfig dbConf;
		QSqlDatabase database;
		users *utilisateur;
		courses *cours;

	public:
		void loadParamsDatabase();
		void testConnexion();
		loadmodel();
		~loadmodel();

        users* getUser();
		courses* getCourses();
};

#endif // LOADMODEL_H
