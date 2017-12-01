#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "model.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_connectButton_clicked()
{
	model *model1 = new model();
	QString login = ui->loginTB->text();
	QString password = ui->passwordTB->text();
	model1->checkUser(login, password);

}

void MainWindow::on_resetButton_clicked()
{
	ui->loginTB->clear();
	ui->passwordTB->clear();
}
