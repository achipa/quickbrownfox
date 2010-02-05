#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>

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
private slots:
    void boldify(bool bold);
    void italicize(bool italic);
    void setTextFont(QFont font);
    void setTextSize(QString sizestr);
    void setFontFromFile(QString);
    void about();
    void browseDir();
    void browseSystem();

};

#endif // MAINWINDOW_H
