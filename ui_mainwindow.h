/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionImage_Characteristics;
    QAction *actionInverse_Image;
    QAction *actionBinarization;
    QAction *actionHorizontal_RLSA;
    QAction *actionVertical_RLSA;
    QAction *actionRLSA_2;
    QAction *actionFinding_Lines_2;
    QAction *actionFinding_Words_2;
    QAction *actionLoad_Result_2;
    QAction *actionHistogram;
    QAction *actionAverage_Character_Height;
    QAction *actionPrinting_Lines;
    QAction *actionPrinting_Letters;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_15;
    QCheckBox *checkBox_4;
    QPushButton *pushButton_11;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *spinBox_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSpinBox *spinBox_5;
    QPushButton *pushButton_7;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpinBox *spinBox_2;
    QPushButton *pushButton_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *spinBox_3;
    QPushButton *pushButton_6;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_9;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QSpinBox *spinBox_6;
    QPushButton *pushButton_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QSpinBox *spinBox_7;
    QPushButton *pushButton_9;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_14;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QPushButton *pushButton_10;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_16;
    QCheckBox *checkBox_5;
    QPushButton *pushButton_12;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuProcessing;
    QMenu *menuSmoothing;
    QMenu *menuSegmentation;
    QMenu *menuCharacters;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1035, 686);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionImage_Characteristics = new QAction(MainWindow);
        actionImage_Characteristics->setObjectName(QStringLiteral("actionImage_Characteristics"));
        actionInverse_Image = new QAction(MainWindow);
        actionInverse_Image->setObjectName(QStringLiteral("actionInverse_Image"));
        actionBinarization = new QAction(MainWindow);
        actionBinarization->setObjectName(QStringLiteral("actionBinarization"));
        actionHorizontal_RLSA = new QAction(MainWindow);
        actionHorizontal_RLSA->setObjectName(QStringLiteral("actionHorizontal_RLSA"));
        actionVertical_RLSA = new QAction(MainWindow);
        actionVertical_RLSA->setObjectName(QStringLiteral("actionVertical_RLSA"));
        actionRLSA_2 = new QAction(MainWindow);
        actionRLSA_2->setObjectName(QStringLiteral("actionRLSA_2"));
        actionFinding_Lines_2 = new QAction(MainWindow);
        actionFinding_Lines_2->setObjectName(QStringLiteral("actionFinding_Lines_2"));
        actionFinding_Words_2 = new QAction(MainWindow);
        actionFinding_Words_2->setObjectName(QStringLiteral("actionFinding_Words_2"));
        actionLoad_Result_2 = new QAction(MainWindow);
        actionLoad_Result_2->setObjectName(QStringLiteral("actionLoad_Result_2"));
        actionHistogram = new QAction(MainWindow);
        actionHistogram->setObjectName(QStringLiteral("actionHistogram"));
        actionAverage_Character_Height = new QAction(MainWindow);
        actionAverage_Character_Height->setObjectName(QStringLiteral("actionAverage_Character_Height"));
        actionPrinting_Lines = new QAction(MainWindow);
        actionPrinting_Lines->setObjectName(QStringLiteral("actionPrinting_Lines"));
        actionPrinting_Letters = new QAction(MainWindow);
        actionPrinting_Letters->setObjectName(QStringLiteral("actionPrinting_Letters"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setAutoFillBackground(true);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        verticalLayout_6->addWidget(label_15);

        checkBox_4 = new QCheckBox(centralWidget);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        verticalLayout_6->addWidget(checkBox_4);

        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        verticalLayout_6->addWidget(pushButton_11);


        gridLayout->addLayout(verticalLayout_6, 2, 5, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_3->addWidget(label_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        spinBox_4 = new QSpinBox(centralWidget);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMaximum(999);

        horizontalLayout_6->addWidget(spinBox_4);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        spinBox_5 = new QSpinBox(centralWidget);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMaximum(999);

        horizontalLayout_7->addWidget(spinBox_5);


        verticalLayout_3->addLayout(horizontalLayout_7);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout_3->addWidget(pushButton_7);


        gridLayout->addLayout(verticalLayout_3, 2, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        verticalLayout->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(999);

        horizontalLayout_3->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(999);

        horizontalLayout_4->addWidget(spinBox_2);


        verticalLayout->addLayout(horizontalLayout_4);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_2->addWidget(label_12);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        spinBox_3 = new QSpinBox(centralWidget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(999);

        horizontalLayout_5->addWidget(spinBox_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout_2->addWidget(pushButton_6);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 7);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_4->addWidget(label_9);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_4->addWidget(label_13);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_8->addWidget(label_10);

        spinBox_6 = new QSpinBox(centralWidget);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setMaximum(999);

        horizontalLayout_8->addWidget(spinBox_6);

        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        horizontalLayout_8->addWidget(pushButton_8);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_9->addWidget(label_11);

        spinBox_7 = new QSpinBox(centralWidget);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setMaximum(999);

        horizontalLayout_9->addWidget(spinBox_7);

        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        horizontalLayout_9->addWidget(pushButton_9);


        verticalLayout_4->addLayout(horizontalLayout_9);


        gridLayout->addLayout(verticalLayout_4, 2, 3, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_5->addWidget(label_14);

        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout_5->addWidget(checkBox_2);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_5->addWidget(checkBox);

        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        verticalLayout_5->addWidget(pushButton_10);


        gridLayout->addLayout(verticalLayout_5, 2, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        graphicsView_2 = new QGraphicsView(centralWidget);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));

        horizontalLayout->addWidget(graphicsView_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 7);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout_7->addWidget(label_16);

        checkBox_5 = new QCheckBox(centralWidget);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        verticalLayout_7->addWidget(checkBox_5);

        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        verticalLayout_7->addWidget(pushButton_12);


        gridLayout->addLayout(verticalLayout_7, 2, 6, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1035, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuProcessing = new QMenu(menuBar);
        menuProcessing->setObjectName(QStringLiteral("menuProcessing"));
        menuSmoothing = new QMenu(menuBar);
        menuSmoothing->setObjectName(QStringLiteral("menuSmoothing"));
        menuSegmentation = new QMenu(menuBar);
        menuSegmentation->setObjectName(QStringLiteral("menuSegmentation"));
        menuCharacters = new QMenu(menuBar);
        menuCharacters->setObjectName(QStringLiteral("menuCharacters"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuProcessing->menuAction());
        menuBar->addAction(menuSmoothing->menuAction());
        menuBar->addAction(menuSegmentation->menuAction());
        menuBar->addAction(menuCharacters->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuFile->addSeparator();
        menuFile->addAction(actionLoad_Result_2);
        menuFile->addSeparator();
        menuProcessing->addAction(actionImage_Characteristics);
        menuProcessing->addSeparator();
        menuProcessing->addAction(actionInverse_Image);
        menuProcessing->addSeparator();
        menuProcessing->addAction(actionBinarization);
        menuProcessing->addSeparator();
        menuProcessing->addAction(actionHistogram);
        menuProcessing->addSeparator();
        menuSmoothing->addAction(actionHorizontal_RLSA);
        menuSmoothing->addSeparator();
        menuSmoothing->addAction(actionVertical_RLSA);
        menuSmoothing->addSeparator();
        menuSmoothing->addAction(actionRLSA_2);
        menuSmoothing->addSeparator();
        menuSegmentation->addAction(actionFinding_Lines_2);
        menuSegmentation->addSeparator();
        menuSegmentation->addAction(actionFinding_Words_2);
        menuSegmentation->addSeparator();
        menuCharacters->addAction(actionAverage_Character_Height);
        menuCharacters->addSeparator();
        menuCharacters->addAction(actionPrinting_Lines);
        menuCharacters->addSeparator();
        menuCharacters->addAction(actionPrinting_Letters);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open ", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit ", Q_NULLPTR));
        actionImage_Characteristics->setText(QApplication::translate("MainWindow", "Image Characteristics", Q_NULLPTR));
        actionInverse_Image->setText(QApplication::translate("MainWindow", "Inverse ", Q_NULLPTR));
        actionBinarization->setText(QApplication::translate("MainWindow", "Binarization", Q_NULLPTR));
        actionHorizontal_RLSA->setText(QApplication::translate("MainWindow", "Horizontal RLSA", Q_NULLPTR));
        actionVertical_RLSA->setText(QApplication::translate("MainWindow", "Vertical  RLSA", Q_NULLPTR));
        actionRLSA_2->setText(QApplication::translate("MainWindow", "RLSA_H_V", Q_NULLPTR));
        actionFinding_Lines_2->setText(QApplication::translate("MainWindow", "Finding Lines", Q_NULLPTR));
        actionFinding_Words_2->setText(QApplication::translate("MainWindow", "Finding Words", Q_NULLPTR));
        actionLoad_Result_2->setText(QApplication::translate("MainWindow", "Load Result", Q_NULLPTR));
        actionHistogram->setText(QApplication::translate("MainWindow", "Histogram", Q_NULLPTR));
        actionAverage_Character_Height->setText(QApplication::translate("MainWindow", "Average Character Height", Q_NULLPTR));
        actionPrinting_Lines->setText(QApplication::translate("MainWindow", "Printing Lines", Q_NULLPTR));
        actionPrinting_Letters->setText(QApplication::translate("MainWindow", "Printing Letters", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "         Average Height", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("MainWindow", "   By more Appearances", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "    Finding Words Parameter  ", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "       Tx", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "       Vx", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "   Finding Lines  Parameters  ", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "   Ty", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "   Vy", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "   Binarization Parameter ", Q_NULLPTR));
        label_12->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "   B. Thr.", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "1:1", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Fit_To_Page", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "                   R.L.S.A  Parameters ", Q_NULLPTR));
        label_13->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "  Horizontal_C", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "  Vertical_C", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "    Kind of  Photos  ", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("MainWindow", "      .tif   Photos", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "      .dat    Files", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "       Parametric Run ", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("MainWindow", "              Run", Q_NULLPTR));
        pushButton_12->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuProcessing->setTitle(QApplication::translate("MainWindow", "Image Processing", Q_NULLPTR));
        menuSmoothing->setTitle(QApplication::translate("MainWindow", "Smoothing ", Q_NULLPTR));
        menuSegmentation->setTitle(QApplication::translate("MainWindow", "Segmentation", Q_NULLPTR));
        menuCharacters->setTitle(QApplication::translate("MainWindow", "Characters", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
