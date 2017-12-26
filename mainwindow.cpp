#include <QDebug>
#include <algorithm> //std::min

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "squaregrid.h"
#include "hexgrid.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(QSize(1207, 819));
    initialiseUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialiseUI()
{
    ui->denseBox->setEnabled(false);
    ui->finishBox->setEnabled(false);
    ui->geometryBox->setCurrentIndex(0);
    ui->checkRandLayout->setChecked(false);
    ui->checkRandFinish->setChecked(false);
    ui->checkRandStart->setChecked(false);
    ui->widthBox->setValue(40);
    ui->heightBox->setValue(25);
    ui->denseBox->setValue(30);
    ui->finishBox->setValue(1);

    ui->pathButton->setEnabled(false);
}

void MainWindow::on_geometryBox_currentIndexChanged(int index)
{
    if (index == 2)
    {
        ui->widthBox->setEnabled(false);
        ui->heightBox->setEnabled(false);
        ui->checkRandLayout->setEnabled(false);
        ui->checkRandStart->setEnabled(false);
        ui->checkRandFinish->setEnabled(false);
    }
    else
    {
        ui->widthBox->setEnabled(true);
        ui->heightBox->setEnabled(true);
        ui->checkRandLayout->setEnabled(true);
        ui->checkRandStart->setEnabled(true);
        ui->checkRandFinish->setEnabled(true);
    }
}

void MainWindow::on_gridButton_clicked()
{
    int geometry = ui->geometryBox->currentIndex();

        Grid* theGrid;

        if (geometry == 0)
            theGrid = new SquareGrid(ui->gridView,ui->widthBox->value(),ui->heightBox->value());
        else if (geometry == 1)
            theGrid = new HexGrid(ui->gridView,ui->widthBox->value(),ui->heightBox->value());
        else return;

        theGrid->Randomise(ui->checkRandLayout->isChecked(),ui->checkRandFinish->isChecked(),
                           ui->checkRandStart->isChecked(),ui->finishBox->value(),
                           ui->denseBox->value());

        ui->gridView->SetGrid(theGrid);

        ui->gridView->update();
}

void MainWindow::on_resetButton_clicked()
{
    ui->gridView->SetReset(true);
    ui->gridView->update();

    initialiseUI();
}

void MainWindow::on_checkRandLayout_stateChanged(int state)
{
    ui->denseBox->setEnabled(!!state);
}

void MainWindow::on_checkRandFinish_stateChanged(int state)
{
    ui->finishBox->setEnabled(!!state);
}

void MainWindow::on_widthBox_editingFinished()
{
    ui->finishBox->setMaximum(std::min(
        ui->widthBox->value()*ui->heightBox->value()-1,10));
}

void MainWindow::on_heightBox_editingFinished()
{
    ui->finishBox->setMaximum(std::min(
        ui->widthBox->value()*ui->heightBox->value()-1,10));
}
