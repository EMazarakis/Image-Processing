#include "mainwindow.h"
#include "ui_mainwindow.h"

//----------------------------------------------------------------------------------
//----------------------- FUNCTIONS FOR THE SMOOTHING TAB --------------------------
//----------------------------------------------------------------------------------

//RLSA_H_V
/*
void MainWindow::RunLengthSmoothingAlgorithm(){


    if( loadImage1 == 0 ){      //You have to read an image first
        int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
        if( result3 == QMessageBox::Ok ){ return; } //Exit();
    }

    if( flagBin == 0 ){         //It means that the image has not been binarized
        int result1 = QMessageBox::information(this,"Error", "First of all Binarization.", QMessageBox::Ok);
        if( result1 == QMessageBox::Ok ){ return; }
    }

    if( runParametric != 1 ){   //It means that we do not want parametric run

        if(  flagHorizontalRLSA == 0 ){   //It means that the user did not give the Horizontal_C
            int result3 = QMessageBox::information(this, "Error", "You must provide Horizontal_C.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }    //Exit();
        }

        if( flagVerticalRLSA == 0 ){   //It means that the user did not give the Vertical_C
            int result3 = QMessageBox::information(this, "Error", "You must provide Vertical_C.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }
    }


    //1st step : Run the Horizontal RLSA
    Horizontal_RLSA();

    //2nd step : Run the Vertical RLSA
    Vertical_RLSA();

    //3rd step : Logic AND on the above 2 producing Images
    if( Ver_Image != NULL && Hor_Image != NULL ){   //both Horizontal & Vertical run properly

            RLSA_Image =  new (std::nothrow) QImage(*Hor_Image);

            QRgb white;
            QRgb  black;
            //QRgb  red = qRgb(255,0,0);
            white = qRgb(255,255,255);
            black = qRgb(0,0,0);

            for(int y=0; y<Iy; ++y)
                for(int x=0; x<Ix; ++x)
                    RLSA_Image->setPixel(x,y,white);


            unsigned char **bitmapOfTag = NULL;
            bitmapOfTag = new (std::nothrow) unsigned char* [Iy];

            for (int y=0; y<Iy; y++){
                bitmapOfTag[y] = new(std::nothrow) unsigned char[Ix];
                for(int x=0; x<Ix; x++) bitmapOfTag[y][x] = 0;  //All the bitmap has zero value
            }


            int x, y;

            for(x=0; x<Ix; ++x){

                for(y=0; y<Iy; ++y){

                        unsigned char u1 = (unsigned char)qGray(Hor_Image->pixel(x,y));
                        unsigned char u2 = (unsigned char)qGray(Ver_Image->pixel(x,y));

                        if( (u1 == 255) && (u2 == 255) ){

                            RLSA_Image->setPixel(x,y,white);
                            //bitmapOfTag[y][x] = 1;
                        }
                        else{
                            RLSA_Image->setPixel(x,y,black);
                            bitmapOfTag[y][x] = 1;
                        }
                }
            }

            if( dbFlag == 1 ){  //We use DB photos
                //Create_dot_Dat_Files( RLSA_Image, "RLSA_DB/words/" );
                Create_dot_Dat_Files_v_2_0( bitmapOfTag, "RLSA_DB/words/");
            }
            else{               //We use No DB photos
                RLSA_Image->save("RLSA/RLSA.tif");
            }


            for(int y=0;y<Iy;y++){ delete[] bitmapOfTag[y]; }
            delete bitmapOfTag;

            scene2 = new (std::nothrow) QGraphicsScene;
            scene2->addPixmap(QPixmap::fromImage(*RLSA_Image));
            ui->graphicsView_2->setScene(scene2);

            loadImage2 = 1;     //Image has been put at the graphicsView_2


            if(runParametric == 1){

                if( bySum ){
                     printf("Average Character Height is: %f.\n", averageHeight);
                }
                else{
                     printf("Average Character Height is: %d.\n", another_averageHeight);
                }

                printf("Horizontal_c = %d is two times the Average Height.\n", horizontal_C);
                printf("vertical_C = %d is divide two times the Average Height.\n", vertical_C);
            }
            else{
                printf("Horizontal_c = %d.\n", horizontal_C);
                printf("vertical_C = %d.\n", vertical_C);
            }
    }
}


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Horizontal_RLSA
void MainWindow::Horizontal_RLSA(){

        if( loadImage1 == 0 ){      //You have to read an image first
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; } //Exit();
        }

        if( flagBin == 0 ){         //It means that the image has not been binarized
            int result1 = QMessageBox::information(this,"Error", "First of all Binarization.", QMessageBox::Ok);
            if( result1 == QMessageBox::Ok ){ return; }
        }

        if( runParametric != 1 ){   //It means that we do not want parametric run

            if(  flagHorizontalRLSA == 0 ){   //It means that the user did not give the Horizontal_C
                int result3 = QMessageBox::information(this, "Error", "You must provide Horizontal_C.", QMessageBox::Ok);
                if( result3 == QMessageBox::Ok ){ return; }
            }
        }

        //CREATION OF THE IMAGE AFTER HORIZONTAL RLSA
        QImage *Himage = new QImage(Ix, Iy, QImage::Format_RGB16);
        QRgb value;
        value = qRgb(255,255,255);              //white background, qRgb(0,0, 0);
        for(int y=0; y<Iy; ++y)
            for(int x=0; x<Ix; ++x)
                Himage->setPixel(x,y,value);    //Oli i eikona tha ginei aspri


        unsigned char **bitmapOfTag = NULL;
        bitmapOfTag = new (std::nothrow)  unsigned char* [Iy];

        for (int y=0; y<Iy; y++){
            bitmapOfTag[y] = new(std::nothrow)  unsigned char[Ix];
            for(int x=0; x<Ix; x++) bitmapOfTag[y][x] = 0;  //All the bitmap has zero value
        }


        int x, y, k;

        for(y=0; y<Iy; ++y){        //for every line

            int count = 0;          //Counter for white pixel
            int flag = 0;           //0: It means that we find black pixel

            for(x=0; x<Ix; ++x){    //for every column

                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                if( u == 255 ){   //We find a white pixel
                    flag = 255;
                    count++;
                    //bitmapOfTag[y][x] = 255;
                }
                else{            //We find a black pixel

                    if ( flag == 255 && count <= horizontal_C ){

                        for( k=(x-count); k<x; ++k ){     //Converting count pixels from white to black
                            QRgb value;
                            value = qRgb(0,0,0);         //Black pixel
                            Himage->setPixel(k,y,value);
                            bitmapOfTag[y][k] = 1;
                        }
                    }

                    flag = 0;   //Reseting the flag
                    count = 0;  //Reseting the counter
                }
            }
        }

        if( dbFlag == 1 ){  //We use DB photos
            //Create_dot_Dat_Files( Himage, "RLSA_DB/lines/" );
            Create_dot_Dat_Files_v_2_0( bitmapOfTag, "RLSA_DB/lines/");
        }
        else{               //We use No DB photos
            Himage->save("RLSA/HorizontalRLSA.tif");
        }

        Hor_Image =  new (std::nothrow) QImage(*Himage);    //In order to be used bu the RLSE_H_V

        for(int y=0;y<Iy;y++){ delete[] bitmapOfTag[y]; }
        delete bitmapOfTag;

        scene2 = new (std::nothrow) QGraphicsScene;
        scene2->addPixmap(QPixmap::fromImage(*Himage));
        ui->graphicsView_2->setScene(scene2);

        loadImage2 = 1;     //Image has been put at the graphicsView_2

        if(runParametric == 1){

            if( bySum ){
                 printf("Average Character Height is: %f.\n", averageHeight);
            }
            else{
                 printf("Average Character Height is: %d.\n", another_averageHeight);
            }

            printf("Horizontal_c = %d is two times the Average Height.\n", horizontal_C);
        }
        else{
            printf("Horizontal_c = %d.\n", horizontal_C);
        }
}


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Vertical_RLSA
void MainWindow::Vertical_RLSA(){

    if( loadImage1 == 0 ){      //You have to read an image first
        int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
        if( result3 == QMessageBox::Ok ){ return; } //Exit();
    }

    if( flagBin == 0 ){         //It means that the image has not been binarized
        int result1 = QMessageBox::information(this,"Error", "First of all Binarization.", QMessageBox::Ok);
        if( result1 == QMessageBox::Ok ){ return; }
    }

    if( runParametric != 1 ){   //It means that we do not want parametric run

        if( flagVerticalRLSA == 0 ){   //It means that the user did not give the Vertical_C
            int result3 = QMessageBox::information(this, "Error", "You must provide Vertical_C.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }
    }


    //CREATION OF THE IMAGE AFTER VERTICAL RLSA
    QImage *Himage = new QImage(Ix, Iy, QImage::Format_RGB16);
    QRgb value;
    value = qRgb(255,255,255);              //white background, qRgb(0,0, 0);
    for(int y=0; y<Iy; ++y)
        for(int x=0; x<Ix; ++x)
            Himage->setPixel(x,y,value);    //Oli i eikona tha ginei aspri

    int x, y, k;

    for(x=0; x<Ix; ++x){        //for every column

        int count = 0;          //Counter for white pixel
        int flag = 0;           //0: It means that we find black pixel

        for(y=0; y<Iy; ++y){    //for every line

            unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
            if( u == 255 ){   //We find a white pixel
                flag = 255;    //255: It means that we find white pixel
                count++;
            }
            else{            //We find a black pixel

                if ( flag == 255 && count <= vertical_C ){

                    for( k=(y-count); k<y; ++k ){     //Converting count pixels from white to black
                        QRgb value;
                        value = qRgb(0,0,0);    //Black pixel
                        Himage->setPixel(x,k,value);
                    }
                }

                flag = 0;   //Reseting the flag
                count = 0;  //Reseting the counter
            }
        }
    }

    Himage->save("RLSA/VerticalRLSA.tif");
    Ver_Image =  new (std::nothrow) QImage(*Himage);
}
*/
