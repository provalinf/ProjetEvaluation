#include "model.h"
#include <QtSql>
#include <QDebug>

model::model()
{

}

void model::checkUser(QString login, QString password)
{
	QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
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
