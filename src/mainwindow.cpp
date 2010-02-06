#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDBusConnection>
#include <QDBusMessage>

MainWindow::MainWindow(QApplication& a, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    qapp(&a)
{
    qDebug() << "D";
    ui->setupUi(this);
    qDebug() << "D";
    connect(ui->boldButton, SIGNAL(toggled(bool)), this, SLOT(boldify(bool)));
    connect(ui->italicButton, SIGNAL(toggled(bool)), this, SLOT(italicize(bool)));
    connect(ui->fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(setTextFont(QFont)));
    connect(ui->sizeComboBox, SIGNAL(activated(QString)), this, SLOT(setTextSize(QString)));
    connect(ui->fileComboBox, SIGNAL(activated(QString)), this, SLOT(setFontFromFile(QString)));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qapp, SLOT(aboutQt()));
    connect(ui->actionAbout_Quick_Brown_Fox, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionBrowse_system_fonts, SIGNAL(triggered(bool)), this, SLOT(browseSystem()));
    connect(ui->actionBrowse_directory, SIGNAL(triggered(bool)), this, SLOT(browseDir()));
    connect(ui->actionSet_Default_Text, SIGNAL(triggered(bool)), this, SLOT(setDefaultText()));
    connect(ui->actionLoad_Text, SIGNAL(triggered(bool)), this, SLOT(setText()));
    qDebug() << "D";
    ui->fileComboBox->setVisible(false);
    ui->fontComboBox->setCurrentIndex(0);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(ui->fontComboBox->count());
    connect(ui->fontComboBox, SIGNAL(currentIndexChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->fontComboBox, SLOT(setCurrentIndex(int)));
    qDebug() << "D";
}

void MainWindow::setDefaultText()
{
    ui->textEdit->setText(tr("The quick brown fox jumps over the lazy dog"));
}

void MainWindow::setText()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();

    }
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

void MainWindow::notify(QString text)
{
    QDBusMessage msg = QDBusMessage::createMethodCall("org.freedesktop.Notifications",
                                          "/org/freedesktop/Notifications",
                                           "org.freedesktop.Notifications",
                                           "SystemNoteDialog");

    QList<QVariant> args;
    args.append(text);
    args.append(static_cast<quint32>(0));
    args.append("ok");

    msg.setArguments(args);

    QDBusConnection::systemBus().call(msg);
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
        notify(tr("No font files found"));
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
        if (ui->fileComboBox->count() == 0) {
            notify(tr("No font files found"));
            browseSystem();
            return;
        } else
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
