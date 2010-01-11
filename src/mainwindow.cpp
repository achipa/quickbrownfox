#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QApplication& a, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    qapp(&a)
{
    ui->setupUi(this);
    connect(ui->boldButton, SIGNAL(toggled(bool)), this, SLOT(boldify(bool)));
    connect(ui->italicButton, SIGNAL(toggled(bool)), this, SLOT(italicize(bool)));
    connect(ui->fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(setTextFont(QFont)));
    connect(ui->sizeComboBox, SIGNAL(activated(QString)), this, SLOT(setTextSize(QString)));
    connect(ui->fileComboBox, SIGNAL(activated(QString)), this, SLOT(setFontFromFile(QString)));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qapp, SLOT(aboutQt()));
    connect(ui->actionAbout_Quick_Brown_Fox, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionBrowse_system_fonts, SIGNAL(triggered(bool)), this, SLOT(browseSystem()));
    connect(ui->actionBrowse_directory, SIGNAL(triggered(bool)), this, SLOT(browseDir()));
    ui->fileComboBox->setVisible(false);
    ui->fontComboBox->setCurrentIndex(0);
}

void MainWindow::setFontFromFile(QString file)
{
    setTextFont(qfd.font(file, "", 10));
}
void MainWindow::browseSystem()
{
    if (!ui->actionBrowse_system_fonts->isChecked())
    {
        ui->actionBrowse_system_fonts->setChecked(true);
        return;
    }
    ui->fileComboBox->setVisible(false);
    ui->fontComboBox->setVisible(true);
    ui->actionBrowse_directory->setChecked(false);
    ui->fontComboBox->setCurrentIndex(0);
}

void MainWindow::browseDir()
{
    if (!ui->actionBrowse_directory->isChecked())
    {
        ui->actionBrowse_directory->setChecked(true);
        return;
    }
    ui->fileComboBox->setVisible(true);
    ui->fontComboBox->setVisible(false);
    ui->actionBrowse_system_fonts->setChecked(false);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
    if (fileNames.length() == 0) {
        browseSystem();
        return;
    } else {
        QDir dir(fileNames[0]);
        QString fullpath;
        qfd.removeAllApplicationFonts();
        QStringList filterlist;
        filterlist << "*.ttf" << "*.otf" << "*.pfb" << "*.afb" << "*.pfm" << "*.afm";
        dir.setNameFilters(filterlist);
        ui->fileComboBox->clear();
        foreach (QString fname, dir.entryList())
        {
            fullpath = dir.canonicalPath() +"/" + fname;
            qDebug() << fullpath << qfd.addApplicationFont(fullpath);
        }
        foreach (QString fname, qfd.families())
            ui->fileComboBox->addItem(fname, fname);
        ui->fileComboBox->setCurrentIndex(0);
    }
}


void MainWindow::about()
{
    QMessageBox::about(this, "The Quick Brown Fox", "A font viewer tool, Copyright (C) 2010 by Attila Csipa");
}

void MainWindow::setTextSize(QString sizestr)
{
    QTextCursor tc = ui->textEdit->textCursor();
    ui->textEdit->selectAll();
    ui->textEdit->setFontPointSize(sizestr.toFloat());
    ui->textEdit->setTextCursor(tc);
}

void MainWindow::setTextFont(QFont font)
{
    qDebug() << "set" << font;
    QTextCursor tc = ui->textEdit->textCursor();
    ui->textEdit->selectAll();
    ui->textEdit->setCurrentFont(font);
    ui->textEdit->setFontItalic(ui->italicButton->isChecked());
    ui->textEdit->setFontWeight(ui->boldButton->isChecked() ? QFont::Bold : QFont::Normal);
    ui->textEdit->setFontPointSize(ui->sizeComboBox->currentText().toFloat());
    ui->textEdit->setTextCursor(tc);
}

void MainWindow::italicize(bool italic)
{
    QTextCursor tc = ui->textEdit->textCursor();
    ui->textEdit->selectAll();
    ui->textEdit->setFontItalic(italic);
    ui->textEdit->setTextCursor(tc);
}

void MainWindow::boldify(bool bold)
{
    QTextCursor tc = ui->textEdit->textCursor();
    ui->textEdit->selectAll();
    ui->textEdit->setFontWeight(bold ? QFont::Bold : QFont::Normal);
    ui->textEdit->setTextCursor(tc);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
