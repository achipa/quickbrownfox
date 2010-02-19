#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QLabel>

MainWindow::MainWindow(QApplication& a, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    qapp(&a),
    settings("QuickBrownFox","default")
{
    ui->setupUi(this);
    foreach (QAction* action, ui->menuFremantle->actions()){
        ui->menuBar->addAction(action);
        ui->menuFremantle->removeAction(action);
    }
    ui->scrollFonts->setProperty("FingerScrollable", true);
    ui->textEdit->setProperty("FingerScrollable", true);
    ui->scrollFonts->setVisible(false);
    connect(ui->boldButton, SIGNAL(toggled(bool)), this, SLOT(boldify(bool)));
    connect(ui->italicButton, SIGNAL(toggled(bool)), this, SLOT(italicize(bool)));
    connect(ui->fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(setTextFont(QFont)));
    connect(ui->sizeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setTextSize(QString)));
    ui->sizeSlider->setMinimum(0);
    ui->sizeSlider->setMaximum(ui->sizeComboBox->count());
    ui->sizeSlider->setValue(ui->sizeComboBox->currentIndex());
    connect(ui->sizeComboBox, SIGNAL(currentIndexChanged(int)), ui->sizeSlider, SLOT(setValue(int)));
    connect(ui->sizeSlider, SIGNAL(valueChanged(int)), ui->sizeComboBox, SLOT(setCurrentIndex(int)));
    connect(ui->sizeSlider, SIGNAL(valueChanged(int)), this, SLOT(updateScrollFontSizes(int)));
    connect(ui->fileComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setFontFromFile(QString)));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qapp, SLOT(aboutQt()));
    connect(ui->actionAbout_Quick_Brown_Fox, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionBrowse_system_fonts, SIGNAL(triggered(bool)), this, SLOT(browseSystem()));
    connect(ui->actionBrowse_directory, SIGNAL(triggered(bool)), this, SLOT(browseDir()));
    connect(ui->actionSet_Default_Text, SIGNAL(triggered(bool)), this, SLOT(setDefaultText()));
    connect(ui->actionLoad_Text, SIGNAL(triggered(bool)), this, SLOT(setText()));
    connect(ui->actionToggle_edit_view_mode, SIGNAL(triggered()), this, SLOT(toggleEditMode()));
    ui->fontSlider->setValue(0);
    ui->fontSlider->setMinimum(0);
    connect(ui->fontComboBox, SIGNAL(currentIndexChanged(int)), ui->fontSlider, SLOT(setValue(int)));
    connect(ui->fileComboBox, SIGNAL(currentIndexChanged(int)), ui->fontSlider, SLOT(setValue(int)));
    connect(ui->fontSlider, SIGNAL(valueChanged(int)), this, SLOT(setSlider(int)));
    browseSystem();
}

void MainWindow::toggleEditMode()
{
    ui->scrollFonts->setVisible(!ui->scrollFonts->isVisible());
    ui->textEdit->setVisible(!ui->textEdit->isVisible());

    ui->fontComboBox->setEnabled(ui->textEdit->isVisible());
    ui->fileComboBox->setEnabled(ui->textEdit->isVisible());
    ui->fontSlider->setEnabled(ui->textEdit->isVisible());

    if (ui->textEdit->isVisible()) // clean scroller
        for (int i=0 ; i<ui->scrollFontsLayout->count()-1; i++) {
            ui->scrollFontsLayout->removeItem(ui->scrollFontsLayout->takeAt(0));
        }
    else {    // populate scroller
        QObjectList* objlist;
        QLabel* label;
        if (ui->fontComboBox->isVisible()){
        // paraszt... why doesn't itemData give back Qfont Qvariants ?
            int tmpidx = ui->fontComboBox->currentIndex();
            for (int i=0 ; i<ui->fontComboBox->count(); i++) {
                ui->fontComboBox->setCurrentIndex(i);
                label = new QLabel();
                label->setText(tr("The quick brown fox jumps over the lazy dog") + QString(" (%1)").arg(ui->fontComboBox->currentText()));
                label->setFont(ui->fontComboBox->currentFont());
                ui->scrollFontsLayout->insertWidget(0,label);
            }
            ui->fontComboBox->setCurrentIndex(tmpidx);
            updateScrollFontSizes(ui->sizeSlider->value());
        }

    }

}

void MainWindow::updateScrollFontSizes(int val)
{
    for (int i=0 ; i<ui->scrollFontsLayout->count()-1; i++) {
        QWidget* l = ui->scrollFontsLayout->itemAt(i)->widget();
        QLabel* label = (QLabel*)ui->scrollFontsLayout->itemAt(i)->widget();
        QFont tmpfont(label->font());
        tmpfont.setPointSize(val);
        label->setFont(tmpfont);
    }
}

void MainWindow::setSlider(int val)
{
    if (ui->fontComboBox->isVisible())
        ui->fontComboBox->setCurrentIndex(val);
    else
        ui->fileComboBox->setCurrentIndex(val);
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
        if (fileNames.count() > 0){
            qDebug() << fileNames[0];
            QFile f(fileNames[0]);
            if (f.open(QIODevice::ReadOnly|QIODevice::Text)){
                QString s(f.readAll());
                ui->textEdit->setText(s);
            }
        }
    }
}

void MainWindow::setFontFromFile(QString file)
{
    setTextFont(qfd.font(file, "", 10));
}
void MainWindow::browseSystem()
{
/*    if (!ui->actionBrowse_system_fonts->isChecked())
    {
        ui->actionBrowse_system_fonts->setChecked(true);
        return;
    }*/
    ui->fileComboBox->setVisible(false);
    ui->fontComboBox->setVisible(true);
    ui->actionBrowse_directory->setChecked(false);
    ui->actionBrowse_system_fonts->setChecked(true);
    qfd.removeAllApplicationFonts();
    ui->fontSlider->setMaximum(ui->fontComboBox->count()-1);
    ui->fontComboBox->setCurrentIndex(0);
    setTextFont(ui->fontComboBox->currentFont());
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
/*    if (!ui->actionBrowse_directory->isChecked())
    {
        ui->actionBrowse_directory->setChecked(true);
        return;
    }*/
    ui->fileComboBox->setVisible(true);
    ui->fontComboBox->setVisible(false);
    ui->actionBrowse_system_fonts->setChecked(false);
    ui->actionBrowse_directory->setChecked(true);
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
        QStringList dupelist;
        foreach (QString fname, dir.entryList())
        {
            fullpath = dir.canonicalPath() +"/" + fname;
            int fid = qfd.addApplicationFont(fullpath);
            foreach (QString famname, qfd.applicationFontFamilies(fid))
                if (!dupelist.contains(famname)) {
                    ui->fileComboBox->addItem(famname, fname);
                    dupelist << famname;
                }
        }
        if (ui->fileComboBox->count() == 0) {
            notify(tr("No font files found"));
            browseSystem();
            return;
        } else {
            ui->fontSlider->setMaximum(ui->fileComboBox->count()-1);
            ui->fileComboBox->setCurrentIndex(0);
            setFontFromFile(ui->fileComboBox->currentText());
        }
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
