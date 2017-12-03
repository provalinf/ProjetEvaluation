#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "loadmodel.h"
#include "users.h"
#include "courses.h"

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

		void on_reset_clicked();

		void on_addRessource_clicked();

		void on_tableViewCoursInscrits_doubleClicked(const QModelIndex &index);

		void on_toolButtonChooser_clicked();

		void on_actionSe_d_connecter_triggered();

		void on_proposerCours_clicked();

		void on_comboBoxTypeRessource_activated(const QString &arg1);

		void on_deposer_clicked();

	private:
		loadmodel *lmodel;
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
