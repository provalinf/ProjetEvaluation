#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QList>

MainWindow* MainWindow::instance = NULL;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	lmodel = new loadmodel();
	ui->setupUi(this);
    /* Toujours demarrer l'application sur la page de connexion */
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow* MainWindow::getInstance(){
    if(instance == NULL){
        instance = new MainWindow;
    }
    return instance;
}

loadmodel* MainWindow::getLModel(){
    return lmodel;
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_connectButton_clicked() {
	QString login = ui->loginTB->text();
	QString password = ui->passwordTB->text();
    if (lmodel->getUser()->checkAndDefinedUser(login, password)) {
        switch (lmodel->getUser()->getStatus()) {
		case 3:
			qDebug() << "Administrateur";
			ui->helloAdmin->setText("Bonjour "+login+ " !");
			ui->stackedWidget->setCurrentIndex(9);
			break;
		case 1:
			qDebug() << "Professeur";
			ui->helloProf->setText("Bonjour "+login+ " !");
			ui->stackedWidget->setCurrentIndex(8);
            break;
		case 2:
			qDebug() << "Etudiant";
			ui->helloEtudiant->setText("Bonjour "+login+ " !");
			ui->stackedWidget->setCurrentIndex(7);
            break;
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
	ui->nbPlaces->clear();
}

void MainWindow::on_addRessource_clicked() {
	ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_tableViewCoursInscrits_doubleClicked() {
    int id = ui->tableViewCoursInscrits->selectionModel()->selectedRows().value(0).data().toInt();
    QSqlQueryModel* coursQuery = lmodel->getCourses()->getCoursById(id);
    int idAuthor=coursQuery->record(0).value("id_Author").toInt();
    int idDomain=coursQuery->record(0).value("id_Domain").toInt();
    QSqlQueryModel* userQuery = lmodel->getUser()->getUserById(idAuthor);
    QSqlQueryModel* domainQuery = lmodel->getCourses()->getDomainById(idDomain);

    ui->nom->setText(coursQuery->record(0).value("name").toString());
    ui->enseignant->setText(userQuery->record(0).value("login").toString());
    ui->domaine->setText(domainQuery->record(0).value("name").toString());
    ui->dateTimeEdit->setDateTime(QDateTime::fromString(coursQuery->record(0).value("date_fin").toString(),"yyyy-MM-ddTHH:mm:ss"));
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(coursQuery->record(0).value("nb_Place").toInt());
    ui->progressBar->setValue(lmodel->getCourses()->getNbPlacesRestantes(id));
    lmodel->getCourses()->setIdCurrentCours(coursQuery->record(0).value("id_Course").toInt());
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_toolButtonChooser_clicked() {
	QFileDialog file;
	//file.exec();
	QFileInfo name;
	name = file.getOpenFileName();
	lmodel->getCourses()->setRessourceNameChoosing(name.baseName());
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
    stringList.insert("domaine", QString::number(ui->comboBoxDomaine->currentData().toInt()));
	stringList.insert("nbPlaces", ui->nbPlaces->text());

	QList<QString> invalid = lmodel->getCourses()->verifInfoCours(stringList);

	for (QWidget *&q : fields) {
		q->setStyleSheet("background-color: none;");
	}

	if (invalid.isEmpty()) {
		qDebug() << invalid << "valide";

        if (lmodel->getCourses()->addNewCours(stringList, lmodel->getUser()->getIdUser())) {
            ui->stackedWidget->setCurrentIndex(8);
		} else {
            qDebug() << "Pas envoyé à la BDD";
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
    ui->tableViewCoursInscrits->setModel(lmodel->getCourses()->getCoursInscrits(lmodel->getUser()->getIdUser()));
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_coursDispo_clicked()
{
    ui->tableViewCoursDispo->setModel(lmodel->getCourses()->getCoursDispo(lmodel->getUser()->getIdUser()));
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_proposeCours_clicked()
{
    QSqlQueryModel* domainsQuery = lmodel->getCourses()->getAllDomains();
    for(int i = 0; i < domainsQuery->rowCount(); ++i)
    {
        ui->comboBoxDomaine->addItem(domainsQuery->record(i).value(1).toString(),domainsQuery->record(i).value(0));
    }
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_coursAttente_clicked()
{
    ui->tableViewCoursEnAttente->setModel(lmodel->getCourses()->getCoursAttenteValidation());
	ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_listeCours_clicked()
{
	ui->tableViewCoursProf->setModel(lmodel->getCourses()->getCoursProf(lmodel->getUser()->getIdUser()));
	ui->tableViewCoursProf->setColumnHidden(0, true);
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

void MainWindow::on_desinscrire_clicked()
{
    lmodel->getUser()->desinscrireEtudiantCours(lmodel->getUser()->getIdUser(),lmodel->getCourses()->getIdCurrentCours());
    MainWindow::on_coursSuivis_clicked();
}

void MainWindow::on_return_CoursSelectionEtudiant_clicked()
{
    MainWindow::on_coursSuivis_clicked();
}


void MainWindow::on_tableViewCoursEnAttente_doubleClicked()
{
	 QMessageBox msgBox;
	 int id = ui->tableViewCoursEnAttente->selectionModel()->selectedRows().value(0).data().toInt();
	 QSqlQueryModel* nom = lmodel->getCourses()->getCoursById(id);
	 msgBox.setWindowTitle("Cours : "+nom->record(0).value("name").toString());
	 msgBox.setText("Que souhaitez-vous faire ?");
	 QPushButton *acceptButton = msgBox.addButton(tr("Accepter"), QMessageBox::ActionRole);
	 QPushButton *refuseButton = msgBox.addButton(tr("Refuser"), QMessageBox::ActionRole);
	 QPushButton *annuleButton = msgBox.addButton(tr("Annuler"), QMessageBox::ActionRole);

	 msgBox.exec();

	 if (msgBox.clickedButton() == acceptButton) {
		 qDebug() << "cours accepte";
		 lmodel->getCourses()->setAcceptCours(id);
	 }
	 else if (msgBox.clickedButton() == refuseButton) {
		 lmodel->getCourses()->setRefuseCours(id);
	 }
	 else if (msgBox.clickedButton() == annuleButton) {
		 msgBox.close();
	 }

	 ui->tableViewCoursEnAttente->setModel(lmodel->getCourses()->getCoursAttenteValidation()); //maj de la table
}

void MainWindow::on_tableViewCoursProf_doubleClicked(const QModelIndex &index)
{
	int id = ui->tableViewCoursProf->selectionModel()->selectedRows().value(0).data().toInt();
	qDebug() << "clic sur" << id;
	ui->stackedWidget->setCurrentIndex(11);
	ui->tableViewRessourcesProf->setModel(lmodel->getCourses()->getCoursRessources(id));
	qDebug() << "return " << lmodel->getCourses()->getCoursRessources(id);
	ui->tableViewRessourcesProf->setColumnHidden(0, true);
}

void MainWindow::on_buttonAddRessource_clicked()
{
	ui->comboBoxTypeRessource_2->addItem("Fichier");
	ui->comboBoxTypeRessource_2->addItem("Texte");
	ui->comboBoxTypeRessource_2->addItem("Devoir");
	ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::on_buttonReset_clicked()
{
	lmodel->getCourses()->setRessourceNameChoosing("");// permet de reinitialiser l'ancien nom
	ui->nomFichier->clear();
}

void MainWindow::on_pushResetText_clicked()
{
	ui->textRessource->clear();
}

void MainWindow::on_pushButtonAddText_clicked()
{
	int id = ui->tableViewCoursProf->selectionModel()->selectedRows().value(0).data().toInt();
	lmodel->getCourses()->addResource(ui->textRessource->toPlainText(), ui->dateDebut_2->date(),
									  ui->dateFin_2->date(), ui->comboBoxTypeRessource_2->currentText(),
									  ui->lineEditDescriptionRessource->text(), ui->lineEditTitreRessource->text(), id);
	ui->stackedWidget->setCurrentIndex(11); // redirection sur la liste des ressources
	ui->tableViewRessourcesProf->setModel(lmodel->getCourses()->getCoursRessources(id));
}

void MainWindow::on_pushButton_clicked()
{
	ui->lineEditDescriptionRessource->clear();
	ui->lineEditTitreRessource->clear();
	ui->dateDebut_2->clear();
	ui->dateFin_2->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
	if(ui->comboBoxTypeRessource_2->currentText() == "Texte"){
		ui->stackedWidget->setCurrentIndex(13);
	}else if (ui->comboBoxTypeRessource_2->currentText() == "Fichier"){
		ui->stackedWidget->setCurrentIndex(14);
	}else if (ui->comboBoxTypeRessource_2->currentText() == " Devoir"){
		ui->stackedWidget->setCurrentIndex(15);
	}
}

void MainWindow::on_toolButtonChooser_2_clicked()
{
	QFileDialog file;
	//file.exec();
	QFileInfo name;
	name = file.getOpenFileName();
	lmodel->getCourses()->setRessourceNameChoosing(name.baseName());
	ui->nomFichier_2->setText(name.baseName());
	ui->nomFichier_2->setEnabled(true);
	//qDebug() <<file.getOpenFileUrl();
	//QFileDialog.exec();
}

void MainWindow::on_pushButtonValidFile_clicked()
{
	//dépend du choix de stockage
	ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_return_viewRessourceProf_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}
