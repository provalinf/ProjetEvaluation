#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QtSql>
#include <QDebug>
#include <QtWidgets>

class model
{
	protected:
		QSqlDatabase* database;
	public:
		model(QSqlDatabase* database);
		~model();
};

#endif // MODEL_H
