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
		switch (lmodel->getUsers()->getStatus()) {
		case 0:
			qDebug() << "Administrateur";
			ui->helloAdmin->setText("Bonjour "+login+ " !");
			ui->stackedWidget->setCurrentIndex(9);
			break;
		case 1:
			qDebug() << "Professeur";
			ui->helloProf->setText("Bonjour "+login+ " !");
			ui->stackedWidget->setCurrentIndex(8);
		case 2:
			qDebug() << "Etudiant";
			ui->tableViewCoursInscrits->setModel(lmodel->getCourses()->getCoursInscrits());
			ui->helloEtudiant->setText("Bonjour "+login+ " !");
			ui->stackedWidget->setCurrentIndex(7);
		default:
			qDebug() << "Aucun statut";
			break;
		}
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
	QFileDialog file;
	//file.exec();
	QFileInfo name;
	name = file.getOpenFileName();
	ui->nomFichier->setText(name.baseName());
	ui->nomFichier->setEnabled(true);
	//qDebug() <<file.getOpenFileUrl();
	//QFileDialog.exec();
}

void MainWindow::on_actionSe_d_connecter_triggered() {
	ui->stackedWidget->setCurrentIndex(0);
	ui->loginTB->clear();
	ui->passwordTB->clear();
}

void MainWindow::on_comboBoxTypeRessource_activated(const QString &arg1) {

}

void MainWindow::on_deposer_clicked() {
//	QDrag *drag =new QDrag(this);
//	QMimeData *mimeData = new QMimeData;
//	mimeData->setData();
//	drag->exec();
}

void MainWindow::on_proposerCours_clicked() {
	QHash<QString, QWidget *> fields;
	fields.insert("name", ui->nomCours);
	fields.insert("debDate", ui->dateDebut);
	fields.insert("finDate", ui->dateFin);
	fields.insert("domaine", ui->comboBoxDomaine);
	fields.insert("nbPlaces", ui->nbPlaces);

	QHash<QString, QString> stringList;
	stringList.insert("name", ui->nomCours->text());
	stringList.insert("debDate", ui->dateDebut->dateTime().toString("yyyy-MM-dd hh:mm"));
	stringList.insert("finDate", ui->dateFin->dateTime().toString("yyyy-MM-dd hh:mm"));
	stringList.insert("domaine", QString::number(ui->comboBoxDomaine->currentIndex()));
	stringList.insert("nbPlaces", ui->nbPlaces->text());

	QList<QString> invalid = lmodel->getCourses()->verifInfoCours(stringList);

	for (QWidget *&q : fields) {
		q->setStyleSheet("background-color: none;");
	}

	if (invalid.isEmpty()) {
		qDebug() << invalid << "valide";

		if (lmodel->getCourses()->addNewCours(stringList, lmodel->getUsers()->getIdUser())) {
			ui->stackedWidget->setCurrentIndex(1);
		} else {
			// Popup erreur insertion
		}
	} else {
		qDebug() << invalid << "invalide";
		for (int i = 0; i < invalid.size(); ++i) {
			QWidget *&q = fields[invalid.value(i)];
			q->setStyleSheet("background-color: rgb(255, 198, 198);");
		}
	}
}

void MainWindow::on_coursSuivis_clicked()
{
	 ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_coursDispo_clicked()
{
	 ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_proposeCours_clicked()
{
	ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_coursAttente_clicked()
{
	ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_listeCours_clicked()
{
	ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_return_proposerCours_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_return_coursDisponibles_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_return_coursAttenteDeValidation_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_return_coursProf_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_return_coursInscrits_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}
