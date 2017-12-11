#ifndef COURSES_H
#define COURSES_H

#include <QtSql>
#include "model.h"

class courses : public model {
public:
	courses(QSqlDatabase *database);

	~courses();

    QSqlQueryModel *getCoursById(int id);

	QSqlQueryModel *getCoursInscrits();

    QSqlQueryModel *getCoursDispo();

    QSqlQueryModel *getCoursProf();

    QSqlQueryModel *getCoursAttenteValidation();

    QSqlQueryModel *getAllDomains();

    QSqlQueryModel *getDomainById(int id);

	QList<QString> verifInfoCours(QHash<QString, QString> hash);

	bool addNewCours(QHash<QString, QString> fields);

	bool addNewCours(QHash<QString, QString> fields, int idUser);

    int getNbPlacesRestantes(int id);
};

#endif // COURSES_H
