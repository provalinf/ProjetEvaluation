#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QtSql>
#include <QDebug>

class model
{
	private:
		QString login;
		QString password;
		QSqlDatabase database;
	public:
		model();
		void checkUser(QString login, QString password);
};

#endif // MODEL_H
