#include "mainwindow.h"
#include "ui_mainwindow.h"
/*
#include <QFile>
#include <QFileDialog>  //The QFileDialog class provides a dialog that allow users to select files or directories
#include <QMessageBox>
#include <QRgb>
#include <QSpinBox>
#include <QScrollBar>
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//File Tab
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::Exit);
    connect(ui->actionLoad_Result_2, &QAction::triggered, this, &MainWindow::Load_Result);

//Image Processing Tab
    connect(ui->actionImage_Characteristics, &QAction::triggered, this, &MainWindow::Image_Characteristics);
    connect(ui->actionInverse_Image, &QAction::triggered, this, &MainWindow::Inverse);
    connect(ui->actionBinarization, &QAction::triggered, this, &MainWindow::Binarization);
    connect(ui->actionHistogram, &QAction::triggered, this, &MainWindow::Histogram);

//Smoothing Tab
    connect(ui->actionHorizontal_RLSA, &QAction::triggered, this, &MainWindow::Horizontal_RLSA);
    connect(ui->actionVertical_RLSA, &QAction::triggered, this, &MainWindow::Vertical_RLSA);
    connect(ui->actionRLSA_2, &QAction::triggered, this, &MainWindow::RunLengthSmoothingAlgorithm);

//Segmentation Tab
    connect(ui->actionFinding_Lines_2, &QAction::triggered, this, &MainWindow::Finding_Lines);
    connect(ui->actionFinding_Words_2, &QAction::triggered, this, &MainWindow::Finding_Words);

//Characters Tab
    connect(ui->actionAverage_Character_Height, &QAction::triggered, this, &MainWindow::Average_Handprinted_Character_Height);
    connect(ui->actionPrinting_Lines, &QAction::triggered, this, &MainWindow::PrintingLinesOfDocument);
    connect(ui->actionPrinting_Letters, &QAction::triggered, this, &MainWindow::PrintingLettersOfDocument);

//connect (sender, signal, receiver, slot)
    connect(ui->graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_2->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_2->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView_2->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView_2->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView->horizontalScrollBar(), SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------------------------------------------------------------
//------------------------------- END OF THE CODE ------------------------------------------------------
//------------------------------------------------------------------------------------------------------

