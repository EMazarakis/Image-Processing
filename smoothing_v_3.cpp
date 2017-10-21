#include "mainwindow.h"
#include "ui_mainwindow.h"

//----------------------------------------------------------------------------------
//----------------------- FUNCTIONS FOR THE SMOOTHING TAB Version 2.0 --------------
//----------------------------------------------------------------------------------


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
        QRgb whitePxl, blackPxl;
        whitePxl = qRgb(255,255,255);
        blackPxl = qRgb(0,0,0);

        for(int y=0; y<Iy; ++y)         //For every line of the image
            for(int x=0; x<Ix; ++x){    //For every column of the image

                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                if( u == 255 ) Himage->setPixel(x,y,whitePxl);
                else Himage->setPixel(x,y,blackPxl);
            }

        //FIXME: should be corrected the bitmap
        //This bitmap is useful for the creation of the .dat files
        unsigned char **bitmapOfTag = NULL;
        bitmapOfTag = new (std::nothrow)  unsigned char* [Iy];

        for (int y=0; y<Iy; y++){
            bitmapOfTag[y] = new(std::nothrow)  unsigned char[Ix];
            for(int x=0; x<Ix; x++){
                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                if( u == 255 ) bitmapOfTag[y][x] = 0;  //All the bitmap has zero value
                else bitmapOfTag[y][x] = 1;
            }
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

                            Himage->setPixel(k,y,blackPxl);
                            bitmapOfTag[y][k] = 1;      //FIXME: should be corrected the bitmap
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

        Hor_Image =  new (std::nothrow) QImage(*Himage);    //In order to be used by the RLSE_H_V

        for(int y=0;y<Iy;y++){ delete[] bitmapOfTag[y]; }
        delete bitmapOfTag;

        scene2 = new (std::nothrow) QGraphicsScene;
        scene2->addPixmap(QPixmap::fromImage(*Himage));
        ui->graphicsView_2->setScene(scene2);

        loadImage2 = 1;     //Image has been put at the graphicsView_2

        if(runParametric == 1){

            if( bySum ) printf("Average Character Height is: %f.\n", averageHeight);
            else printf("Average Character Height is: %d.\n", another_averageHeight);

            printf("Horizontal_c = %d is two times the Average Height.\n", horizontal_C);
        }
        else printf("Horizontal_c = %d.\n", horizontal_C);
}
