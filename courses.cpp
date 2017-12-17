#include "courses.h"
#include "mainwindow.h"

courses::courses(QSqlDatabase *database) : model(database) {
}

QSqlQueryModel *courses::getCoursById(int id) {
    QSqlQueryModel *res = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    qry->prepare("SELECT * FROM courses WHERE id_Course=:idCourse");
    qry->bindValue(":idCourse", id);
    qry->exec();
    res->setQuery(*qry);
    database->close();
    return res;
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
    qry->prepare("SELECT id_course, c.name as 'Titre', d.name as 'Domaine', nb_place as 'Nb place', date_deb as 'Date de début', date_fin as 'Date de fin', "
						 "CASE valide\n"
						 "      WHEN '0' THEN 'Refusé'\n"
						 "      WHEN '1' THEN 'Accepté'\n"
						 "      ELSE 'Non contrôlé'\n"
						 "   END as 'Validé' FROM courses as c "
						 "JOIN domains as d ON c.id_domain=d.id_domain WHERE id_Author=:idAuthor");
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

QSqlQueryModel *courses::getAllDomains(){
    QSqlQueryModel *res = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    qry->prepare("SELECT * FROM domains");
    qry->exec();
    res->setQuery(*qry);
    database->close();
    return res;
}

QSqlQueryModel *courses::getDomainById(int id){
    QSqlQueryModel *res = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    qry->prepare("SELECT * FROM domains WHERE id_Domain=:idDomain");
    qry->bindValue(":idDomain", id);
    qry->exec();
    res->setQuery(*qry);
    database->close();
    return res;
}

QAbstractItemModel *courses::getCoursRessources(int id_cours) {
	QSqlQueryModel *res = new QSqlQueryModel();
	QSqlQuery *qry = new QSqlQuery();
	database->open();
	/*qry->prepare("SELECT id_resource, title as 'Nom', tr.name as 'Type', descr as 'Description', date_deb as 'Date de début', date_fin as 'Date de fin' FROM resources as c"
						 "JOIN Type_resource as tr ON tr.id_type=c.id_type"
						 "WHERE id_course=:idCours");*/
	qry->prepare("SELECT id_resource, title as 'Nom', tr.name as 'Type', descr as 'Description', date_deb as 'Date de début', date_fin as 'Date de fin' FROM resources as c "
						 "JOIN Type_resource as tr ON tr.id_type=c.id_type "
						 "WHERE id_course=:idCours");
	qry->bindValue(":idCours", id_cours);
	qry->exec();
	res->setQuery(*qry);
	database->close();
	return res;
}


bool courses::addNewCours(QHash<QString, QString> fields, int idUser) {
	QSqlQuery qry;
	database->open();
    qry.prepare("INSERT INTO courses (name, date_deb, date_fin, nb_Place, id_Author, id_Domain) "
                "VALUES (:name, :date_deb, :date_fin, :nb_Place, :id_Author, :id_Domain)");
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

int courses::getNbPlacesRestantes(int id){
    QSqlQueryModel *res = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    qry->prepare("SELECT * FROM courses WHERE id_Course=:idCourse");
    qry->bindValue(":idCourse", id);
    qry->exec();
    res->setQuery(*qry);
    int nb_place = res->record(0).value("nb_Place").toInt();
    QSqlQueryModel *res2 = new QSqlQueryModel();
    QSqlQuery *qry2 = new QSqlQuery();
    qry2->prepare("SELECT COUNT(id_Studies) FROM studies WHERE id_Course=:idCourse");
    qry2->bindValue(":idCourse", id);
    qry2->exec();
    res2->setQuery(*qry);
    int nb_place_prises = res->record(0).value(0).toInt();
    database->close();
    return nb_place - nb_place_prises;
}

void courses::setIdCurrentCours(int id){
    idCurrentCours = id;
}

int courses::getIdType(QString type){
	QSqlQuery *qry = new QSqlQuery();
	QSqlQueryModel *res = new QSqlQueryModel();
	qry->prepare("SELECT * FROM type_resource WHERE name=:name");
	qry->bindValue(":name", type);
	qry->exec();
	res->setQuery(*qry);
	return res->query().first();
}

void courses::addResource(QString text, QDate debut, QDate fin, QString type, QString descr, QString titre){
	QSqlQuery *qry = new QSqlQuery();
	database->open();
	qry->prepare("INSERT INTO resources VALUES (5, :titre, :descr, :deb, :fin, :idCourse, :type)"); //id auto incremente ?
	qry->bindValue(":debut", debut);
	qry->bindValue(":fin", fin);
	qry->bindValue(":type", getIdType(type));
	qry->bindValue(":descr", descr);
	qry->bindValue(":titre", titre);
	qry->bindValue(":idCourse", 3);
	qry->exec();

	QSqlQuery *qry2 = new QSqlQuery();
	qry2->prepare("INSERT INTO resource_text VALUES (:idResource, :text)");
	qry2->bindValue(":text", text);
	qry2->bindValue(":idResource", 5);
	qry2->exec();

	database->close();
}

int courses::getIdCurrentCours(){
    return idCurrentCours;
}

void courses::setRessourceNameChoosing(QString nom) {
	nomCoursChoisi = nom;
}

void courses::setRefuseCours(int idCours){
	QSqlQuery *qry = new QSqlQuery();
	database->open();
	qry->prepare("UPDATE courses SET valide = 0 WHERE id_Course=:idCourse");
	qry->bindValue(":idCourse", idCours);
	qry->exec();
	database->close();
}

void courses::setAcceptCours(int idCours){
	QSqlQuery *qry = new QSqlQuery();
	database->open();
	qry->prepare("UPDATE courses SET valide = 1 WHERE id_Course=:idCourse");
	qry->bindValue(":idCourse", idCours);
	qry->exec();
	database->close();
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
