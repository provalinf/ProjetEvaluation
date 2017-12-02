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
	model1->checkUser(login, password);

}

void MainWindow::on_resetButton_clicked()
{
	ui->loginTB->clear();
	ui->passwordTB->clear();
}
