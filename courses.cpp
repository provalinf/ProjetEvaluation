#include "courses.h"
#include "mainwindow.h"

courses::courses(QSqlDatabase *database) : model(database) {

}

QSqlQueryModel *courses::getCoursInscrits() {
	QSqlQueryModel *res = new QSqlQueryModel();
	QSqlQuery *qry = new QSqlQuery();
	database->open();
    MainWindow* m =MainWindow::getInstance();
    loadmodel* lmodel= m->getLModel();
    users* user = lmodel->getUser();
    int id = user->getIdUser();
    qry->prepare("SELECT * FROM courses WHERE id_Course=(SELECT id_Course FROM studies WHERE id_Student=:idStudent)");
    qry->bindValue(":idStudent", id);
	qry->exec();
	res->setQuery(*qry);
	database->close();
	return res;
}

QSqlQueryModel *courses::getCoursDispo() {
    QSqlQueryModel *res = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    MainWindow* m =MainWindow::getInstance();
    loadmodel* lmodel= m->getLModel();
    users* user = lmodel->getUser();
    int id = user->getIdUser();
    qry->prepare("SELECT * FROM courses WHERE valide = 1 AND "
                 "id_Course=(SELECT id_Course FROM registrations WHERE date_deb<NOW() AND "
                 "date_fin>NOW() AND "
                 "(id_Registration!=(SELECT id_Registration FROM register_students WHERE id_Student=?) OR "
                 "NOT EXISTS (SELECT id_Registration FROM register_students WHERE id_Student=?)))");
    qry->bindValue(0, id);
    qry->bindValue(1, id);
    qry->exec();
    res->setQuery(*qry);
    database->close();
    return res;
}

QSqlQueryModel *courses::getCoursProf() {
    QSqlQueryModel *res = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    MainWindow* m =MainWindow::getInstance();
    loadmodel* lmodel= m->getLModel();
    users* user = lmodel->getUser();
    int id = user->getIdUser();
    qry->prepare("SELECT * FROM courses WHERE id_Author=:idAuthor");
    qry->bindValue(":idAuthor", id);
    qry->exec();
    res->setQuery(*qry);
    database->close();
    return res;
}

QSqlQueryModel *courses::getCoursAttenteValidation() {
    QSqlQueryModel *res = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    qry->prepare("SELECT * FROM courses WHERE valide IS NULL");
    qry->exec();
    res->setQuery(*qry);
    database->close();
    return res;
}

bool courses::addNewCours(QHash<QString, QString> fields, int idUser) {
	QSqlQuery qry;
	database->open();
	qry.prepare("INSERT INTO (name, date_deb, date_fin, nb_Place, id_Author, id_Domain)"
						"VALUES (:name, :date_deb, :date_fin, :nb_Place, :id_Author, :id_Domain)\"");
	qry.bindValue(":name", fields.value("name"));
	qry.bindValue(":date_deb", fields.value("debDate"));
	qry.bindValue(":date_fin", fields.value("finDate"));
	qry.bindValue(":nb_Place", fields.value("nbPlaces"));
	qry.bindValue(":id_Author", idUser);
	qry.bindValue(":id_Domain", fields.value("domaine"));
	bool ret = qry.exec();
	database->close();
	return ret;
}

courses::~courses() = default;

QList<QString> courses::verifInfoCours(QHash<QString, QString> fields) {
	QList<QString> erreurs;
	for (int j = 0; j < fields.keys().size(); ++j) {
		QString key = fields.keys().value(j);
		if (fields.value(key).isEmpty()) erreurs.append(key);
	}

	if (!erreurs.contains("finDate")) {
		QDateTime datefin = QDateTime::fromString(fields.value("finDate"), "yyyy-MM-dd hh:mm");
		QDateTime datedeb = QDateTime::fromString(fields.value("debDate"), "yyyy-MM-dd hh:mm");
		if (datefin.toTime_t() <= datedeb.toTime_t()) erreurs.append("finDate");
	}

	// Ajouter vérification domaine

	if (fields.find("nbPlaces")->toInt() <= 0) erreurs.append("nbPlaces");

	return erreurs;
}

