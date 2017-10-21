#include "mainwindow.h"
#include "ui_mainwindow.h"

//-------------------------------------------------------------------------------------------
//------------------------ FUNCTIONS FOR THE FILE TAB ---------------------------------------
//-------------------------------------------------------------------------------------------

void MainWindow::cleanMemory()
{

    if(bitmap!=NULL){

        for(int y=0;y<Iy;y++){ delete[] bitmap[y]; }

        delete bitmap;
        bitmap = NULL;
    }

    if(binary_bitmap!=NULL){

        for(int y=0; y<Iy; y++){ delete[] binary_bitmap[y]; }

        delete binary_bitmap;
        binary_bitmap = NULL;
    }

    if(bitmapVerRLSA!=NULL){

        for(int y=0; y<Iy; y++){ delete[] bitmapVerRLSA[y]; }

        delete bitmapVerRLSA;
        bitmapVerRLSA = NULL;
    }

    if(bitmapHorRLSA!=NULL){

        for(int y=0; y<Iy; y++){ delete[] bitmapHorRLSA[y]; }

        delete bitmapHorRLSA;
        bitmapHorRLSA = NULL;
    }

    Ix = 0;
    Iy = 0;
    bpp = 0;
}

void MainWindow::Exit()
{
    cleanMemory();
    QCoreApplication::exit(0);  //Tells the application to exit with a return code.
}


void MainWindow::openFile()
{
    QFile *f = new (std::nothrow) QFile(QFileDialog::getOpenFileName(this, tr("Open File"),QCoreApplication::applicationDirPath(),tr("Images (*.png *.tif *.jpg *.bmp)")));

    if(f->exists()){

        Image1 =  new (std::nothrow) QImage(f->fileName());
        scene = new (std::nothrow) QGraphicsScene;          //Trying to allocate memory for scene object

        if( (Image1 != NULL) && (scene != NULL) ){

            scene->addPixmap(QPixmap::fromImage(*Image1));
            ui->graphicsView->setScene(scene);

            Ix = Image1->width();   //width
            Iy = Image1->height();  //height
            bpp = Image1->depth();  //bits per pixel

            loadImage1 = 1;
        }

        printf("Ix = %d\n", Ix);
        printf("Iy = %d\n", Iy);
        printf("bpp = %d\n", bpp);

        QFileInfo fi(*f);
        photoName = fi.fileName();
        strName= photoName.toStdString();
        printf("The name of the photo is: %s\n", strName.c_str());
    }
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
void MainWindow::Load_Result(){    //loading to the graphics_view_2 the result of an algorithm

    QFile *f = new (std::nothrow) QFile(QFileDialog::getOpenFileName(this, tr("Open File"),QCoreApplication::applicationDirPath(),tr("Images (*.png *.tif *.jpg *.bmp)")));

    if( f->exists() ){

        Image2 =  new (std::nothrow) QImage(f->fileName());
        scene2 = new (std::nothrow) QGraphicsScene;          //Trying to allocate memory for scene object

        if( (Image2 != NULL) && (scene2 != NULL) ){

            scene2->addPixmap(QPixmap::fromImage(*Image2));
            ui->graphicsView_2->setScene(scene2);

            Ix = Image2->width();   //width
            Iy = Image2->height();  //height
            bpp = Image2->depth();  //bits per pixel

            loadImage2 = 1;
        }

        printf("Info for the Load Result Image.");
        printf("Ix_2 = %d\n", Ix);
        printf("Iy_2 = %d\n", Iy);
        printf("bpp_2 = %d\n", bpp);
    }

}
//------------------------------------------------------------------------------------------------------
//------------------------------- END OF THE CODE ------------------------------------------------------
//------------------------------------------------------------------------------------------------------
