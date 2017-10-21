 #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QMessageBox>
#include <qgraphicsscene.h>
#include <QRgb>
#include <QFile>
#include <QFileDialog>
#include <QScrollBar>
#include <QCloseEvent>
#include <QFileInfo>
#include <QVector>

#include <algorithm> // std::min_element
#include <iterator>  // std::begin, std::end
#include <iostream>

#include <QtCore>
#include <QtGui>


#define BLACK 1
#define TEST 1

//Height & Width each letter of the text
class LetterSize{
public:
    int letterHeight, letterWidth;
};

//Bounding Bof each line of the text
class LineBbox{
public:
    int rstart, rend, cstart, cend;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_pushButton_clicked();       //FitToPage
    void on_pushButton_2_clicked();     //1:1
    void on_pushButton_3_clicked();     //+
    void on_pushButton_4_clicked();     //-
    void on_pushButton_5_clicked();     //OK: for finding Lines
    void on_pushButton_6_clicked();     //OK: for Binary Threshold
    void on_pushButton_7_clicked();     //OK: for finding Words
    void on_pushButton_8_clicked();     //OK: for Horizontal RLSA
    void on_pushButton_9_clicked();     //OK: for Vertical RLSA
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();

private:

    Ui::MainWindow *ui;            //define the whole user Interface
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QImage *Image1 = NULL;         //define an object in order to manipulate the loading image
    QImage *Image2 = NULL;
    QImage *BinaryImage = NULL;
    QImage *RLSA_Image = NULL;
    QImage *Hor_Image = NULL;
    QImage *Ver_Image = NULL;

    QImage *LetterImage = NULL;    //Save at this image every handprinted character of the text
    QImage *BboxImage = NULL;      //Save at this image every handprinted line of the text

    QSpinBox spinBox;       //Ty
    QSpinBox spinBox_2;     //Vy

    QString photoName;      //Keep the name of the loading photo
    std::string strName;    //Keep the name of the photo on a C/C++ string format

    unsigned char **bitmap = NULL;
    unsigned char **binary_bitmap = NULL;   //It's the bitmap of the Binary Image


    unsigned char **bitmapVerRLSA = NULL;   //It's a bitmap for the vertical RLSA  function
    unsigned char **bitmapHorRLSA = NULL;   //It's a bitmap for the horizontal RLSA  function

//Parameters for the finding lines of a text
    int Ty = -1;     //Threshold for horizontal projections
    int Vy = -1;     //Valley for horizontal projections
    int Tx = -1;     //Threshold for vertical projections
    int Vx = -1;     //Valley for vertical projections
    int Ix = 0;      //width
    int Iy = 0;      //height
    int bpp = 0;
    int Bthr = -1;

    int runParametric = 0;           //0: You can not run the alfgortihm parametric
    int flagAverageCharacter = 0;   //0:We did not use the average character function
    int flagFindLines = 0;          //0: Horizontal Projection's Threshold has not been given by user
    int flagFindWords = 0;          //0: Vertical Projection's Threshold has not been given by user
    int flagBin = 0;                //0: Tell us that the image has not been binarized
    int flagHorizontalRLSA = 0;     //0: Horizontal predefined limit has not been given by user
    int flagVerticalRLSA =  0;      //0: Vertical predefined limit has not been given by user
    int loadImage1 = 0;             //It means that image was loaded at the q_graphics_view
    int loadImage2 = 0;             //It means that image was loaded at the q_graphics_view_2
    int dbFlag = 0;                 //0: It means that we don't use the Images from the database
    int bySum = 1;                  //1: Initial value in order to change after the selection of the appearance method
    double averageHeight = -1.0;    //average character height by sum method
    int another_averageHeight = -1; //average character height by more apearances method


    int horizontal_C = -1;          //predefined limit C of continuous background pixel for horizontal RLSA
    int vertical_C = -1;            //predefined limit C of continuous background pixel for vertical RLSA

//File Tab
    void cleanMemory();
    void openFile();
    void Exit();
    void Load_Result();

//Image Tab
    void Image_Characteristics();   //width, height and bpp odf an image
    void Inverse();                 //inverse the whole image
    void Binarization();            //the i mage has only black and white pxls after the processing
    void Histogram();

//Smoothing Tab
    void Horizontal_RLSA();
    void Vertical_RLSA();
    void RunLengthSmoothingAlgorithm();

//Segmentation Tab
    void Finding_Lines();           //finding the lines of a text
    void Finding_Words();           //finding the words of a text
    void words(int ys, int ye, int& tag);

//Characters Tab
    //Finding the average character height of a text
    void Average_Handprinted_Character_Height();

    //Finding the lines of a text
    void Finding_Lines_for_Average_Height(int *NumberOfLines, QVector<LineBbox> *BBox_Of_Lines);

    //Extract every line from the image and print each one of them to a file-Image
    void extract_Line(int NumberOfLines, QVector<LineBbox> *textLines);

    //Extract every character from the image and print each one of them to a file-Image
    void extract_Character(int NumberOfLines, QVector<LineBbox> *textLines, QVector<LetterSize> *characters, int flagPrint);

    //Return the index of the next column with a black pixel in it
    void following_BLACK_column(int *startcol, int rs, int re);

    //Return the index of the next column with a black pixel in it
    void following_WHITE_column(int *endcol, int rs, int re);

    //Print a Character
    void printCharacterOnFile(int rs, int cs, int re, int ce, int counter);

    //Return the Average height of handprinted character
    double Average_SumOfCharactersHeight(QVector<LetterSize> *characters);

    //Return the Average height, which is the most presentable height
    int Average_HistogramCharactersHeight(QVector<LetterSize> *characters);

    //Printing each word of the handprinted document
    void PrintingLettersOfDocument();

    //Function in order to print the document's lines
    void PrintingLinesOfDocument();


//Convert the result Image each Algorithm to a .dat files in order to be used by evaluator.
    void Create_dot_Dat_Files( QImage *IMAGE, QString Dir );

    void Create_dot_Dat_Files_v_2_0(unsigned char  **bitmapOfTag, QString Dir);

};

#endif // MAINWINDOW_H
