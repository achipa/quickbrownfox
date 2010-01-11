/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Jan 11 02:03:00 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFontComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout_Qt;
    QAction *actionAbout_Quick_Brown_Fox;
    QAction *actionBrowse_system_fonts;
    QAction *actionBrowse_directory;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFontComboBox *fontComboBox;
    QComboBox *fileComboBox;
    QComboBox *sizeComboBox;
    QPushButton *boldButton;
    QPushButton *italicButton;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFermantle;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        actionAbout_Quick_Brown_Fox = new QAction(MainWindow);
        actionAbout_Quick_Brown_Fox->setObjectName(QString::fromUtf8("actionAbout_Quick_Brown_Fox"));
        actionBrowse_system_fonts = new QAction(MainWindow);
        actionBrowse_system_fonts->setObjectName(QString::fromUtf8("actionBrowse_system_fonts"));
        actionBrowse_system_fonts->setCheckable(true);
        actionBrowse_system_fonts->setChecked(true);
        actionBrowse_directory = new QAction(MainWindow);
        actionBrowse_directory->setObjectName(QString::fromUtf8("actionBrowse_directory"));
        actionBrowse_directory->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        fontComboBox = new QFontComboBox(centralWidget);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));
        fontComboBox->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(fontComboBox);

        fileComboBox = new QComboBox(centralWidget);
        fileComboBox->setObjectName(QString::fromUtf8("fileComboBox"));
        fileComboBox->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(fileComboBox);

        sizeComboBox = new QComboBox(centralWidget);
        sizeComboBox->setObjectName(QString::fromUtf8("sizeComboBox"));
        sizeComboBox->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(sizeComboBox);

        boldButton = new QPushButton(centralWidget);
        boldButton->setObjectName(QString::fromUtf8("boldButton"));
        boldButton->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        boldButton->setFont(font);
        boldButton->setCheckable(true);

        horizontalLayout->addWidget(boldButton);

        italicButton = new QPushButton(centralWidget);
        italicButton->setObjectName(QString::fromUtf8("italicButton"));
        italicButton->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setItalic(true);
        italicButton->setFont(font1);
        italicButton->setCheckable(true);

        horizontalLayout->addWidget(italicButton);


        verticalLayout->addLayout(horizontalLayout);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menuFermantle = new QMenu(menuBar);
        menuFermantle->setObjectName(QString::fromUtf8("menuFermantle"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFermantle->menuAction());
        menuFermantle->addAction(actionBrowse_system_fonts);
        menuFermantle->addAction(actionBrowse_directory);
        menuFermantle->addSeparator();
        menuFermantle->addAction(actionAbout_Qt);
        menuFermantle->addAction(actionAbout_Quick_Brown_Fox);

        retranslateUi(MainWindow);

        sizeComboBox->setCurrentIndex(12);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Quick Brown Fox", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
        actionAbout_Quick_Brown_Fox->setText(QApplication::translate("MainWindow", "About Quick Brown Fox", 0, QApplication::UnicodeUTF8));
        actionBrowse_system_fonts->setText(QApplication::translate("MainWindow", "Browse system fonts", 0, QApplication::UnicodeUTF8));
        actionBrowse_directory->setText(QApplication::translate("MainWindow", "Browse directory", 0, QApplication::UnicodeUTF8));
        sizeComboBox->clear();
        sizeComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "10.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "24", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "28", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "32", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "36", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "40", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "44", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "48", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "54", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "60", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "66", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "72", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "80", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "88", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "96", 0, QApplication::UnicodeUTF8)
        );
        boldButton->setText(QApplication::translate("MainWindow", "B", 0, QApplication::UnicodeUTF8));
        italicButton->setText(QApplication::translate("MainWindow", "I", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt;\">The quick brown fox jumps over the lazy dog</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        menuFermantle->setTitle(QApplication::translate("MainWindow", "fremantle", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
