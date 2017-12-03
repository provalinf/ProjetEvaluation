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
		ui->tableViewCoursInscrits->setModel(lmodel->getCourses()->getCoursInscrits());
        ui->stackedWidget->setCurrentIndex(1);
	} else {
		// Popup mot de passe incorrect
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
