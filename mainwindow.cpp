#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	lmodel = new loadmodel();
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_connectButton_clicked()
{
	QString login = ui->loginTB->text();
	QString password = ui->passwordTB->text();
	if(lmodel->getUsers()->checkAndDefinedUser(login, password)){
		if(lmodel->getUsers()->getStatus() == "Administrateur"){
			//ui->tableViewCoursInscrits->setModel(model1->getCoursInscrits());
			ui->stackedWidget->setCurrentIndex(5);
		}
		else if(lmodel->getUsers()->getStatus() == "Etudiant"){
			ui->tableViewCoursInscrits->setModel(lmodel->getCourses()->getCoursInscrits());
			ui->stackedWidget->setCurrentIndex(1);
		}
		else if(lmodel->getUsers()->getStatus() == "Professeur"){
			//ui->tableViewCoursInscrits->setModel(model1->getCoursInscrits());
			ui->stackedWidget->setCurrentIndex(2);
		}
		else qDebug()<<"Aucun statut";
	}
}

void MainWindow::on_resetButton_clicked()
{
	ui->loginTB->clear();
	ui->passwordTB->clear();
}

void MainWindow::on_reset_clicked()
{
	ui->nomCours->clear();
	ui->dateDebut->clear();
	ui->dateFin->clear();
	ui->comboBoxDomaine->clear();
	ui->nbPlaces->clear();
}

void MainWindow::on_addRessource_clicked()
{
	ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_tableViewCoursInscrits_doubleClicked(const QModelIndex &index)
{
	//QModelIndex val = ui->tableViewCoursInscrits;
	qDebug()<< index.data().toString();
}

void MainWindow::on_toolButtonChooser_clicked()
{
	//QFileDialog.exec();
}
