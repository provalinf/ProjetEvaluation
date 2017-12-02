#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "model.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_connectButton_clicked();

		void on_resetButton_clicked();

		void on_pushButton_clicked();

		void on_tableView_doubleClicked(const QModelIndex &index);

	private:
		model *model1;
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
