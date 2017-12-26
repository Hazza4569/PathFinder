#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initialiseUI();

private slots:
    void on_geometryBox_currentIndexChanged(int index);
    void on_gridButton_clicked();
    void on_resetButton_clicked();
    void on_checkRandLayout_stateChanged(int state);
    void on_checkRandFinish_stateChanged(int state);
    void on_widthBox_editingFinished();
    void on_heightBox_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
