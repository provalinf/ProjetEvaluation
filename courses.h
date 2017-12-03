#ifndef COURSES_H
#define COURSES_H
#include <QtSql>
#include "model.h"

class courses : public model
{
	public:
		courses(QSqlDatabase* database);
		~courses();
        QSqlQueryModel* getCoursInscrits();
};

#endif // COURSES_H
