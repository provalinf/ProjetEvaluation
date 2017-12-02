#include "model.h"


model::model()
{
	loadParamsDatabase();
	database = QSqlDatabase::addDatabase("QMYSQL");
	database.setHostName(dbConf.hostname);
	database.setUserName(dbConf.username);
	database.setPassword(dbConf.password);
	database.setDatabaseName(dbConf.nameDatabase);
	if(database.open())
		qDebug() << "Connexion à la base de donnée" << database.databaseName()<<"réussie";
	else
		qDebug() << "Impossible de se connecter à la base de donnée"<<database.lastError().text();
}

void model::loadParamsDatabase() {
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

bool model::checkUser(QString login, QString password) {
    // Conversion en string pour hachage puis hachage du mot de passe
    std::string hashed_str = sha512(password.toUtf8().constData());
    QString hashed_password = QString::fromStdString(hashed_str);

    //qDebug() << hashed_password;

	QSqlQuery query;
	database.open();
	query.prepare("SELECT * FROM users WHERE login=:login AND password=:password");
	query.bindValue(":login", login);
    query.bindValue(":password", hashed_password);

	if(query.exec()){
		if (query.size() == 1) {
			//connexion au site
			qDebug() << "Login et mot de passe correct";
			return true;
			/*qDebug() << "Number of Rows: " << query.size();
			qDebug() << "Number of columns: " << query.record().count();
			query.first();
			qDebug() << "test : " << query.value(1).toString();*/

		} else {
			qDebug() << "Login et mot de passe incorrect";
		}

	}
	else{
		qDebug() << "Erreur d'execution";
	}
	return false;
}

QSqlQueryModel* model::getCoursInscrits(){
    QSqlQueryModel* res = new QSqlQueryModel();
	database.open();
    QSqlQuery* qry = new QSqlQuery();
	qry->prepare("SELECT * FROM courses");
	qry->exec();
	//database.close();
    res->setQuery(* qry);
    return res;
}

model::~model() {
	database.close();
}
