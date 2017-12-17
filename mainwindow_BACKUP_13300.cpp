#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	model1 = new model();
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
	if(model1->checkUser(login, password)){
		ui->tableViewCoursInscrits->setModel(model1->getCoursInscrits());
        ui->stackedWidget->setCurrentIndex(1);
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
	//ajouter la ressource
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
