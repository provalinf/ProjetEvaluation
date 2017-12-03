#include "users.h"


users::users(QSqlDatabase* database):model(database)
{
	users::setDisconnected();
}

bool users::checkAndDefinedUser(QString login, QString password) {
	QSqlQuery query;
	database->open();
	query.prepare("SELECT id FROM users WHERE login=:login AND password=:password");
	query.bindValue(":login", login);
	query.bindValue(":password", password);

	if(query.exec()){
		if (query.size() == 1) {
			//connexion au site
			qDebug() << "Login et mot de passe correct";
			/*qDebug() << "Number of Rows: " << query.size();
			qDebug() << "Number of columns: " << query.record().count();
			query.first();
			qDebug() << "test : " << query.value(1).toString();*/
			defineUserConnect(query.value(0).toInt());
			qDebug() << query.value(0).toInt();
			return true;
		} else {
			qDebug() << "Login et mot de passe incorrect";
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

void users::setConnected() {
	connected = true;
}

void users::setDisconnected() {
	connected = false;
	idUserConnect = -1;
}

users::~users() {
	database->close();
}
