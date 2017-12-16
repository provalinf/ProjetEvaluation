#ifndef COURSES_H
#define COURSES_H

#include <QtSql>
#include "model.h"

class courses : public model {
int idCurrentCours;
public:
	courses(QSqlDatabase *database);

	~courses();

    QSqlQueryModel *getCoursById(int id);

	QSqlQueryModel *getCoursInscrits(int i);

	void setAcceptCours(int idCours);

	void setRefuseCours(int idCours);

    QSqlQueryModel *getCoursDispo(int i);

    QSqlQueryModel *getCoursProf(int i);

    QSqlQueryModel *getCoursAttenteValidation();

    QSqlQueryModel *getAllDomains();

    QSqlQueryModel *getDomainById(int id);

	QList<QString> verifInfoCours(QHash<QString, QString> hash);

	bool addNewCours(QHash<QString, QString> fields, int idUser);

    int getNbPlacesRestantes(int id);

    void setIdCurrentCours(int id);

    int getIdCurrentCours();

	QAbstractItemModel *getCoursRessources(int i);
};

#endif // COURSES_H
