#include "model.h"

model::model()
{
	database = QSqlDatabase::addDatabase("QMYSQL");
	database.setHostName("localhost");
	database.setUserName("root");
	database.setPassword("");
	database.setDatabaseName("fst_projetEvaluation");
	if(database.open())
	{
		qDebug() << "Vous êtes maintenant connecté à " << database.hostName();
		database.close();
	}
	else
	{
		qDebug() << "La connexion a échouée, désolé"<<database.lastError().text();
	}

}

void model::checkUser(QString login, QString password)
{
	QSqlQuery query;
	database.open();
	query.prepare("SELECT login FROM utilisateur WHERE login = :login AND password = :password");
	query.bindValue(":login", login);
	query.bindValue(":password", password);

	if(query.exec()){
		//connexion au site
		qDebug() << "Login et mot de passe correct";
	}
	else{
		qDebug() << "Login ou mot de passe incorrect";
	}

}
