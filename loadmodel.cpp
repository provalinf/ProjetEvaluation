#include "loadmodel.h"


loadmodel::loadmodel()
{
	loadParamsDatabase();
	database = QSqlDatabase::addDatabase("QMYSQL");
	database.setHostName(dbConf.hostname);
	database.setUserName(dbConf.username);
	database.setPassword(dbConf.password);
	database.setDatabaseName(dbConf.nameDatabase);

	testConnexion();

	utilisateur = new users(&database);
	cours = new courses(&database);
}

users* loadmodel::getUsers() {
	return utilisateur;
}

courses* loadmodel::getCourses() {
	return cours;
}

void loadmodel::testConnexion() {
	// Test connexion
	if(database.open()) {
		qDebug() << "Connexion à la base de donnée" << database.databaseName()<<"réussie";
		database.close();
	} else {
		qDebug() << "Impossible de se connecter à la base de donnée"<<database.lastError().text();
		// Ajouter un popup ou quitter l'application
	}
}

void loadmodel::loadParamsDatabase() {
	QString path = QDir::currentPath() + "/"+databaseSettings;
	if (QFile(path).exists()) {
		qDebug() << "Chargement de "+databaseSettings;
		QSettings settings(path, QSettings::IniFormat);
		dbConf.hostname = settings.value("Database/hostname","localhost").toString();
		dbConf.username = settings.value("Database/username","root").toString();
		dbConf.password = settings.value("Database/password","").toString();
		dbConf.nameDatabase = settings.value("Database/nameDatabase","").toString();
	} else {
		qDebug() << "Création du fichier de configuration "+databaseSettings;
		QSettings settings(path, QSettings::IniFormat);
		settings.beginGroup("Database");
		settings.setValue("hostname", "localhost");
		settings.setValue("username", "");
		settings.setValue("password", "");
		settings.setValue("nameDatabase", "fst_projetEvaluation");
		settings.endGroup();
		settings.sync();
		//afficher un popup ou un formulaire de remplissage
		exit(0);
	}
}

loadmodel::~loadmodel() {
}
