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
		QSqlQueryModel* pointeur = model1->getCoursInscrits();
		ui->tableViewCoursInscrits->setModel(pointeur);
	}
}

void MainWindow::on_resetButton_clicked()
{
	ui->loginTB->clear();
	ui->passwordTB->clear();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

}
