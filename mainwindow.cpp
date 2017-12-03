#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QList>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	lmodel = new loadmodel();
	ui->setupUi(this);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_connectButton_clicked() {
	QString login = ui->loginTB->text();
	QString password = ui->passwordTB->text();
	if (lmodel->getUsers()->checkAndDefinedUser(login, password)) {
		if (lmodel->getUsers()->getStatus() == "Administrateur") {
			//ui->tableViewCoursInscrits->setModel(model1->getCoursInscrits());
			ui->stackedWidget->setCurrentIndex(5);
		} else if (lmodel->getUsers()->getStatus() == "Etudiant") {
			ui->tableViewCoursInscrits->setModel(lmodel->getCourses()->getCoursInscrits());
			ui->stackedWidget->setCurrentIndex(1);
		} else if (lmodel->getUsers()->getStatus() == "Professeur") {
			//ui->tableViewCoursInscrits->setModel(model1->getCoursInscrits());
			ui->stackedWidget->setCurrentIndex(2);
		} else
			qDebug() << "Aucun statut";
	}
}

void MainWindow::on_resetButton_clicked() {
	ui->loginTB->clear();
	ui->passwordTB->clear();
}

void MainWindow::on_reset_clicked() {
	ui->nomCours->clear();
	ui->dateDebut->clear();
	ui->dateFin->clear();
	ui->comboBoxDomaine->clear();
	ui->nbPlaces->clear();
}

void MainWindow::on_addRessource_clicked() {
	ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_tableViewCoursInscrits_doubleClicked(const QModelIndex &index) {
	//QModelIndex val = ui->tableViewCoursInscrits;
	qDebug() << index.data().toString();
}

void MainWindow::on_toolButtonChooser_clicked() {
	//QFileDialog.exec();
}

void MainWindow::on_actionSe_d_connecter_triggered() {
	ui->stackedWidget->setCurrentIndex(0);
	ui->loginTB->clear();
	ui->passwordTB->clear();
}

void MainWindow::on_proposerCours_clicked() {
	QHash<QString, QWidget *> fields;
	fields.insert("name", ui->nomCours);
	fields.insert("debDate", ui->dateDebut);
	fields.insert("finDate", ui->dateFin);
	fields.insert("domaine", ui->comboBoxDomaine);
	fields.insert("nbPlace", ui->nbPlaces);

	QHash<QString, QString> stringList;
	stringList.insert("name", ui->nomCours->text());
	stringList.insert("debDate", ui->dateDebut->dateTime().toString("yyyy-MM-dd hh:mm"));
	stringList.insert("finDate", ui->dateFin->dateTime().toString("yyyy-MM-dd hh:mm"));
	stringList.insert("domaine", QString::number(ui->comboBoxDomaine->currentIndex()));
	stringList.insert("nbPlaces", ui->nbPlaces->text());

	QList<QString> invalid = lmodel->getCourses()->verifInfoCours(stringList);
	if (invalid.isEmpty()) {
		qDebug() << invalid << "valide";
		for (QWidget *&q : fields) {
			q->setStyleSheet("background-color: none;");
		}

		if (lmodel->getCourses()->addNewCours(stringList, lmodel->getUsers()->getIdUser())) {
			ui->stackedWidget->setCurrentIndex(1);
		} else {
			// Popup erreur insertion
		}
	} else {
		qDebug() << invalid << "invalide";
		/*for (int i = 0; i < invalid.size(); ++i) {
			QWidget *const q = fields.value(invalid.value(i));
			q->setStyleSheet("background-color: rgb(255, 198, 198);");
		 // A voir
		}*/

		/*for (QWidget *&q : fields) {

			q->setStyleSheet("background-color: none;");
		}*/
	}
}
