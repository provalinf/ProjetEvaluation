#ifndef COURSES_H
#define COURSES_H

#include <QtSql>
#include "model.h"

class courses : public model {
public:
	courses(QSqlDatabase *database);

	~courses();

	QSqlQueryModel *getCoursInscrits();

	QList<QString> verifInfoCours(QHash<QString, QString> hash);

	bool addNewCours(QHash<QString, QString> fields);

	bool addNewCours(QHash<QString, QString> fields, int idUser);
};

#endif // COURSES_H
