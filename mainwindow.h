#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget * mainWidget;

    QHBoxLayout * mainLayout;
        QTreeView * treeView;
        QStackedWidget * mainStackWidget;
            QWidget * stack1Widget;
            QVBoxLayout * stack1Layout;
                QWidget * controlWidget;
                QGridLayout * controlLayout;
                    QPushButton * openButton;
                    QLabel * openFileName;
                // Our custom plot widget
                QCustomPlot * m_CustomPlot;


    // This object will hold the current value as a text
    // that will appear at the extreme right of the plot,
    QCPItemText *m_ValueIndex;

public slots:
    void menuOpen(bool toggle);
    void menuClose(bool toggle);
    void menuData(bool toggle);
    void mouseWheel();
    void mousePress();

    void openFile(bool click);
};

#endif // MAINWINDOW_H
