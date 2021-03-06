#include "users.h"


users::users(QSqlDatabase* database):model(database)
{
	users::setDisconnected();
}

bool users::checkAndDefinedUser(QString login, QString password) {
	QSqlQuery query;
	database->open();

	// Conversion en string pour hachage puis hachage du mot de passe
	std::string hashed_str = sha512(password.toUtf8().constData());
	QString hashed_password = QString::fromStdString(hashed_str);

	query.prepare("SELECT * FROM users WHERE login=:login AND password=:password");
	query.bindValue(":login", login);
	query.bindValue(":password", hashed_password);

	if(query.exec()){
		if (query.size() == 1) {
			//connexion au site
			//qDebug() << "Login et mot de passe correct";
			//qDebug() << "Number of Rows: " << query.size();
			//qDebug() << "Number of columns: " << query.record().count();
			query.first();
			//qDebug() << "test : " << query.value(1).toString();*/
			defineUserConnect(query.value(0).toInt());
			status = query.value(3).toInt();
			return true;
		} else {
			qDebug() << "Login et mot de passe incorrect";
			qDebug() << "hashed_password"<< hashed_password;
		}

	}
	else{
		qDebug() << "Erreur d'execution";
	}
	return false;
}

void users::defineUserConnect(int idUser) {
	idUserConnect = idUser;
	setConnected();
}

int users::getStatus(){
	return status;
}

void users::setConnected() {
	connected = true;
}

void users::setDisconnected() {
	connected = false;
	idUserConnect = -1;
}

int users::getIdUser(){
	return idUserConnect;
}

QSqlQueryModel *users::getUserById(int id){
    QSqlQueryModel *res = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    qry->prepare("SELECT * FROM users WHERE id_User=:idUser");
    qry->bindValue(":idUser", id);
    qry->exec();
    res->setQuery(*qry);
    database->close();
    return res;
}

bool users::desinscrireEtudiantCours(int idEtudiant, int idCours){
    QSqlQuery *qry = new QSqlQuery();
    database->open();
    qry->prepare("DELETE FROM studies WHERE id_Student=:idStudent AND id_Course=:idCourse");
    qry->bindValue(":idStudent", idEtudiant);
    qry->bindValue(":idCourse", idCours);
    bool ret = qry->exec();
    database->close();
    return ret;
}

users::~users() {
	database->close();
}
