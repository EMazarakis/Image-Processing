#include "mainwindow.h"
#include "ui_mainwindow.h"


//----------------------------------------------------------------------------------
//----------------------- FUNCTIONS FOR THE SMOOTHING TAB Version 2.0 --------------
//----------------------------------------------------------------------------------


//RLSA_H_V
void MainWindow::RunLengthSmoothingAlgorithm(){


        if( loadImage1 == 0 ){      //You have to read an image first
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
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
        if( Ver_Image != NULL && Hor_Image != NULL ){       //Both Horizontal & Vertical RLSA run properly

                RLSA_Image = new QImage(Ix, Iy, QImage::Format_RGB16);

                QRgb whitePxl, blackPxl, lightskybluePxl;
                whitePxl = qRgb(255,255,255);
                blackPxl = qRgb(0,0,0);
                lightskybluePxl = qRgb(135,206,250);

                for(int y=0; y<Iy; ++y)         //For every line of the image
                    for(int x=0; x<Ix; ++x){    //For every column of the image

                        unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));

                        if( u == 255 ){ RLSA_Image->setPixel(x,y,whitePxl); } //We find a white pixel
                        else{ RLSA_Image->setPixel(x,y,blackPxl); } //We find a black pixel
                    }


                //FIXME: should be corrected
                unsigned char **bitmapOfTag = NULL;
                bitmapOfTag = new (std::nothrow) unsigned char* [Iy];

                for (int y=0; y<Iy; y++){

                    bitmapOfTag[y] = new(std::nothrow) unsigned char[Ix];
                    for(int x=0; x<Ix; x++){

                        unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));

                        if( u == 255 ) bitmapOfTag[y][x] = 0;   //background-white
                        else bitmapOfTag[y][x] = 1;             //foreground-black
                    }
                }

//LOGIC AND BETWEEN TWO BITMAPS
                for(int y=0; y<Iy; ++y){        //For every row of the Image

                    for(int x=0; x<Ix; ++x){    //For every column of the Image

                        if( (bitmapHorRLSA[y][x] == 1) && (bitmapVerRLSA[y][x] == 0) ){ //We find a black pixel

                            RLSA_Image->setPixel(x,y,lightskybluePxl);  //lightskybluePxl
                            bitmapOfTag[y][x] = 1;
                        }
                        else if( (bitmapOfTag[y][x] == 0) && (bitmapHorRLSA[y][x] == 1)){

                            RLSA_Image->setPixel(x,y,whitePxl);
                            bitmapOfTag[y][x] = 0;
                        }
                    }
                }

                if( dbFlag == 1 ){  //We'll create .dat files

                    Create_dot_Dat_Files_v_2_0( bitmapOfTag, "RLSA_DB/words/");
                }
                else{              //We'll create .tif files
                    RLSA_Image->save("RLSA/RLSA.tif");
                }


                for(int y=0;y<Iy;y++){ delete[] bitmapOfTag[y]; }
                delete bitmapOfTag;

                scene2 = new (std::nothrow) QGraphicsScene;
                scene2->addPixmap(QPixmap::fromImage(*RLSA_Image));
                ui->graphicsView_2->setScene(scene2);

                loadImage2 = 1;     //Image has been put at the graphicsView_2

                if(runParametric == 1){ //Parametric run  of the algorithm based on the average character height

                    if( !bySum ){ printf("Average Character Height is: %d.\n", another_averageHeight); }

                    printf("Horizontal_c = %d is two times the Average Height.\n", horizontal_C);
                    printf("vertical_C = %d is divide two times the Average Height.\n", vertical_C);
                }
                else
                    printf("Horizontal_c = %d, Vertical_C = %d\n", horizontal_C, vertical_C);
        }
}


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Horizontal_RLSA
void MainWindow::Horizontal_RLSA(){

        if( loadImage1 == 0 ){      //You have to read an image first
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
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
        QRgb whitePxl, blackPxl, lightskybluePxl;
        whitePxl = qRgb(255,255,255);
        blackPxl = qRgb(0,0,0);
        lightskybluePxl = qRgb(135,206,250);


        //This bitmap is useful for the logic and operation of the RLSA
        bitmapHorRLSA = new (std::nothrow)  unsigned char* [Iy];   //It's a bitmap for the horizontal RLSA  function
        for (int y=0; y<Iy; y++) bitmapHorRLSA[y] = new(std::nothrow)  unsigned char[Ix];

        for(int y=0; y<Iy; ++y)         //For every line of the image
            for(int x=0; x<Ix; ++x){    //For every column of the image

                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));

                if( u == 255 ){  //We find a white pixel

                    Himage->setPixel(x,y,whitePxl);
                    bitmapHorRLSA[y][x] = 0;        //background-white
                }
                else{   //We find a black pixel

                    Himage->setPixel(x,y,blackPxl);
                    bitmapHorRLSA[y][x] = 1;        //foreground-black
                }
            }


        //This bitmap is useful for the creation of the .dat files
        unsigned char **bitmapOfTag = NULL;
        bitmapOfTag = new (std::nothrow) unsigned char* [Iy];

        for (int y=0; y<Iy; y++){

            bitmapOfTag[y] = new(std::nothrow)  unsigned char[Ix];

            for(int x=0; x<Ix; x++){

                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));

                if( u == 255 ) bitmapOfTag[y][x] = 0;  //background-white
                else bitmapOfTag[y][x] = 1;            //foreground-black
            }
        }

        for(int y=0; y<Iy; ++y){        //For every line

            int count = 0;          //Counter for white pixel
            int flag = 0;           //0: It means that we find black pixel

            for(int x=0; x<Ix; ++x){    //For every column

                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                if( u == 255 ){   //We find a white pixel
                    flag = 255;
                    count++;
                }
                else{               //We find a black pixel

                    if ( flag == 255 && count <= horizontal_C ){

                        for(int k=(x-count); k<x; ++k ){     //Converting count pixels from white to black

                            Himage->setPixel(k,y,lightskybluePxl);

                            bitmapOfTag[y][k] = 1;      //Foreground-black
                            bitmapHorRLSA[y][k] = 1;    //Foreground-black
                        }
                    }

                    flag = 0;   //Reseting the flag
                    count = 0;  //Reseting the counter
                }
            }
        }

        if( dbFlag == 1 ){  //We'll create .dat files

            Create_dot_Dat_Files_v_2_0( bitmapOfTag, "RLSA_DB/lines/");
        }
        else{               //We'll create .tif files
            Himage->save("RLSA/HorizontalRLSA.tif");
        }

        Hor_Image =  new (std::nothrow) QImage(*Himage);    //In order to be used by the RLSE_H_V

        for(int y=0;y<Iy;y++){ delete[] bitmapOfTag[y]; }
        delete bitmapOfTag;

        scene2 = new (std::nothrow) QGraphicsScene;
        scene2->addPixmap(QPixmap::fromImage(*Himage));
        ui->graphicsView_2->setScene(scene2);

        loadImage2 = 1;     //Image has been put at the graphicsView_2

        if(runParametric == 1){

            if( !bySum ) printf("Average Character Height is: %d.\n", another_averageHeight);

            printf("Horizontal_c = %d is two times the Average Height.\n", horizontal_C);
        }
        else printf("Horizontal_c = %d.\n", horizontal_C);
}


//-------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//Vertical_RLSA
void MainWindow::Vertical_RLSA(){

        if( loadImage1 == 0 ){      //You have to read an image first
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
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
        QRgb whitePxl, blackPxl, lightskybluePxl;
        whitePxl = qRgb(255,255,255);              //white background, qRgb(0,0, 0);
        blackPxl = qRgb(0,0,0);
        lightskybluePxl = qRgb(135,206,250);


        //This bitmap is useful for the logic and operation of the RLSA
        bitmapVerRLSA = new (std::nothrow)  unsigned char* [Iy];   //It's a bitmap for the horizontal RLSA  function
        for (int y=0; y<Iy; y++){
            bitmapVerRLSA[y] = new(std::nothrow)  unsigned char[Ix];
        }

        for(int y=0; y<Iy; ++y)                 //For every line of the image
            for(int x=0; x<Ix; ++x){            //For every column of the image

                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));

                if( u == 255 ){  //We find a white pixel

                    Himage->setPixel(x,y,whitePxl);
                    bitmapVerRLSA[y][x] = 0;    //background-white
                }
                else{           //We find a black pixel

                    Himage->setPixel(x,y,blackPxl);
                    bitmapVerRLSA[y][x] = 1;    //foreground-black
                }
            }

        for(int x=0; x<Ix; ++x){        //for every column

            int count = 0;          //Counter for white pixel
            int flag = 0;           //0: It means that we find black pixel

            for(int y=0; y<Iy; ++y){    //for every line

                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                if( u == 255 ){   //We find a white pixel
                    flag = 255;    //255: It means that we find white pixel
                    count++;
                }
                else{            //We find a black pixel

                    if ( flag == 255 && count <= vertical_C ){

                        for(int k=(y-count); k<y; ++k ){     //Converting count pixels from white to black

                            Himage->setPixel(x,k,lightskybluePxl );
                            bitmapVerRLSA[k][x] = 1;    //foreground-black
                        }
                    }

                    flag = 0;   //Reseting the flag
                    count = 0;  //Reseting the counter
                }
            }
        }

        Himage->save("RLSA/VerticalRLSA.tif");
        Ver_Image =  new (std::nothrow) QImage(*Himage);

        scene2 = new (std::nothrow) QGraphicsScene;
        scene2->addPixmap(QPixmap::fromImage(*Himage));
        ui->graphicsView_2->setScene(scene2);

        loadImage2 = 1;     //Image has been put at the graphicsView_2
}

//------------------------------------------------------------------------------------------------------
//------------------------------- END OF THE CODE ------------------------------------------------------
//------------------------------------------------------------------------------------------------------
