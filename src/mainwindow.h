#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QApplication& a, QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QApplication* qapp;
    QFontDatabase qfd;
    void notify(QString msg);
    QSettings settings;
private slots:
    void toggleEditMode();
    void updateScrollFontSizes(int val);
    void boldify(bool bold);
    void italicize(bool italic);
    void setSlider(int val);
    void setText();
    void setDefaultText();
    void setTextFont(QFont font);
    void setTextSize(QString sizestr);
    void setFontFromFile(QString);
    void about();
    void browseDir();
    void browseSystem();

};

#endif // MAINWINDOW_H
