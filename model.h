#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QtSql>
#include <QDebug>
#include <QtWidgets>

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
