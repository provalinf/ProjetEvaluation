/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *resetButton;
    QLineEdit *loginTB;
    QLabel *label_2;
    QLineEdit *passwordTB;
    QPushButton *connectButton;
    QLabel *label;
    QWidget *page_2;
    QLabel *label_3;
    QTableView *tableViewCoursInscrits;
    QWidget *page_3;
    QLabel *label_4;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLineEdit *nomCours;
    QLabel *label_6;
    QDateTimeEdit *dateDebut;
    QLabel *label_7;
    QDateTimeEdit *dateFin;
    QLabel *label_8;
    QComboBox *comboBoxDomaine;
    QLabel *label_9;
    QLineEdit *nbPlaces;
    QLabel *label_10;
    QToolButton *addRessource;
    QPushButton *pushButton;
    QPushButton *reset;
    QWidget *page_4;
    QLabel *label_11;
    QTableView *tableViewCoursDispo;
    QWidget *page_5;
    QLabel *label_12;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_13;
    QComboBox *comboBoxTypeRessource;
    QToolButton *toolButtonChooser;
    QLabel *label_14;
    QWidget *page_6;
    QTableView *tableViewCoursEnAttente;
    QLabel *label_15;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(590, 364);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(30, 10, 621, 391));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        resetButton = new QPushButton(page);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(370, 210, 75, 23));
        loginTB = new QLineEdit(page);
        loginTB->setObjectName(QStringLiteral("loginTB"));
        loginTB->setGeometry(QRect(220, 100, 181, 20));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 100, 47, 13));
        passwordTB = new QLineEdit(page);
        passwordTB->setObjectName(QStringLiteral("passwordTB"));
        passwordTB->setGeometry(QRect(220, 150, 181, 20));
        connectButton = new QPushButton(page);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(170, 210, 75, 23));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 150, 81, 20));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(220, 10, 121, 16));
        tableViewCoursInscrits = new QTableView(page_2);
        tableViewCoursInscrits->setObjectName(QStringLiteral("tableViewCoursInscrits"));
        tableViewCoursInscrits->setGeometry(QRect(0, 50, 521, 261));
        tableViewCoursInscrits->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewCoursInscrits->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        label_4 = new QLabel(page_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(220, 10, 111, 16));
        formLayoutWidget = new QWidget(page_3);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(150, 70, 251, 171));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        nomCours = new QLineEdit(formLayoutWidget);
        nomCours->setObjectName(QStringLiteral("nomCours"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nomCours);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        dateDebut = new QDateTimeEdit(formLayoutWidget);
        dateDebut->setObjectName(QStringLiteral("dateDebut"));

        formLayout->setWidget(1, QFormLayout::FieldRole, dateDebut);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        dateFin = new QDateTimeEdit(formLayoutWidget);
        dateFin->setObjectName(QStringLiteral("dateFin"));

        formLayout->setWidget(2, QFormLayout::FieldRole, dateFin);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        comboBoxDomaine = new QComboBox(formLayoutWidget);
        comboBoxDomaine->setObjectName(QStringLiteral("comboBoxDomaine"));

        formLayout->setWidget(3, QFormLayout::FieldRole, comboBoxDomaine);

        label_9 = new QLabel(formLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_9);

        nbPlaces = new QLineEdit(formLayoutWidget);
        nbPlaces->setObjectName(QStringLiteral("nbPlaces"));

        formLayout->setWidget(4, QFormLayout::FieldRole, nbPlaces);

        label_10 = new QLabel(formLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_10);

        addRessource = new QToolButton(formLayoutWidget);
        addRessource->setObjectName(QStringLiteral("addRessource"));

        formLayout->setWidget(5, QFormLayout::FieldRole, addRessource);

        pushButton = new QPushButton(page_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 290, 75, 23));
        reset = new QPushButton(page_3);
        reset->setObjectName(QStringLiteral("reset"));
        reset->setGeometry(QRect(370, 290, 75, 23));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        label_11 = new QLabel(page_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(200, 10, 131, 16));
        tableViewCoursDispo = new QTableView(page_4);
        tableViewCoursDispo->setObjectName(QStringLiteral("tableViewCoursDispo"));
        tableViewCoursDispo->setGeometry(QRect(0, 50, 551, 251));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        label_12 = new QLabel(page_5);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(220, 10, 121, 16));
        formLayoutWidget_2 = new QWidget(page_5);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(140, 100, 261, 171));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(formLayoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_13);

        comboBoxTypeRessource = new QComboBox(formLayoutWidget_2);
        comboBoxTypeRessource->setObjectName(QStringLiteral("comboBoxTypeRessource"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBoxTypeRessource);

        toolButtonChooser = new QToolButton(formLayoutWidget_2);
        toolButtonChooser->setObjectName(QStringLiteral("toolButtonChooser"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, toolButtonChooser);

        label_14 = new QLabel(formLayoutWidget_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_14);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        tableViewCoursEnAttente = new QTableView(page_6);
        tableViewCoursEnAttente->setObjectName(QStringLiteral("tableViewCoursEnAttente"));
        tableViewCoursEnAttente->setGeometry(QRect(30, 70, 471, 251));
        label_15 = new QLabel(page_6);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(180, 30, 191, 16));
        stackedWidget->addWidget(page_6);
        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(loginTB, passwordTB);
        QWidget::setTabOrder(passwordTB, connectButton);
        QWidget::setTabOrder(connectButton, resetButton);
        QWidget::setTabOrder(resetButton, tableViewCoursInscrits);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Page de connexion", Q_NULLPTR));
        resetButton->setText(QApplication::translate("MainWindow", "R\303\251initialiser", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Login : ", Q_NULLPTR));
        connectButton->setText(QApplication::translate("MainWindow", "Connexion", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Mot de passe : ", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Liste des cours inscrits", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Proposer un cours", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Nom du cours :", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Date d\303\251but :", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Date fin :", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Domaine :", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Nombre de places :", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Ajouter une ressource", Q_NULLPTR));
        addRessource->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Valider", Q_NULLPTR));
        reset->setText(QApplication::translate("MainWindow", "R\303\251initialiser", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Liste des cours disponibles", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Ajouter une ressource", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Type de ressource : ", Q_NULLPTR));
        toolButtonChooser->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Choisir fichier : ", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "Liste des cours en attente de validation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
