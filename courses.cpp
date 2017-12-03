#include "courses.h"

courses::courses(QSqlDatabase* database):model(database)
{

}

QSqlQueryModel* courses::getCoursInscrits(){
	QSqlQueryModel* res = new QSqlQueryModel();
	QSqlQuery* qry = new QSqlQuery();
	database->open();
	qry->prepare("SELECT * FROM courses");
	qry->exec();
	//database.close();
	res->setQuery(* qry);
	database->close();
	return res;
}

courses::~courses() {
}
