#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QSettings>
#include <QLabel>

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
    void populateScroller(bool vis);
    bool editmode;
    QList<QLabel*> labellist;
private slots:
    void toggleEditMode();
    void toggleAutoRotate();
    void updateScrollFontSizes(qreal val);
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
