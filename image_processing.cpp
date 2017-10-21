#include "mainwindow.h"
#include "ui_mainwindow.h"

//--------------------------------------------------------------------------------------------
void MainWindow::Create_dot_Dat_Files_v_2_0(unsigned char **bitmapOfTag, QString Dir){  //int for rlsa

       std::string directory = Dir.toStdString();

       char buffer[128]; //Fixing the new name of the file with the extension .dat
       sprintf(buffer,"%s%s.dat", directory.c_str(), strName.c_str());

       FILE *fp = fopen(buffer,"wb+");  //Copying the Image to filename.dat file
       for(int y=0; y<Iy; ++y)
           for(int x=0; x<Ix; ++x)
               fwrite(&bitmapOfTag[y][x], sizeof(int), 1, fp);

       fclose(fp); //Save the .dat file, in order to be used by a evaluator
}


//-------------------------------------------------------------------------------------------
//------------------------ FUNCTIONS FOR THE IMAGE PROCESSING TAB ---------------------------
//-------------------------------------------------------------------------------------------

void MainWindow::Histogram() //histogram of the Image
{
      if( loadImage1 == 0 ){    //Load an Image first of all
          int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
          if( result3 == QMessageBox::Ok ){ return; }
      }

      int H[256];
      int Hmax=0;
      for (int i=0; i<256; i++) H[i]=0;

      for (int x=0;x<Ix;x++){
          for (int y=0;y<Iy;y++){

             unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
             H[u]++;
             if ( H[u]>Hmax ) Hmax = H[u];
          }
      }

      for (int i=0; i<256; i++) H[i]=(200*H[i])/Hmax;   //We set as maximum value the 200

      QImage *Himage = new QImage(256,201,QImage::Format_RGB16);

      for (int x=0; x<256; x++)
      {
          for (int y=200; y>=200-H[x]; y--)
          {
             QRgb value;
             value = qRgb(255,0,0);
             Himage->setPixel(x,y,value);
          }
          for (int y=200-H[x]-1;y>=0;y--)
          {
             QRgb value;
             value = qRgb(255,255,255);
             Himage->setPixel(x,y,value);
          }
      }


      scene2 = new (std::nothrow) QGraphicsScene;
      scene2->addPixmap(QPixmap::fromImage(*Himage));
      ui->graphicsView_2->setScene(scene2);

      loadImage2 = 1;     //Image has been put at the graphicsView_2


      Himage->save("ImageHistogram.tif");
}

//-------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void MainWindow::Binarization(){

        if( loadImage1 == 0 ){  //Load an Image first of all
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }

        if(Bthr != -1){     //Threshold should been giver by user

            int x, y;
            BinaryImage = new(std::nothrow) QImage(Ix,Iy,QImage::Format_RGB32);

            //Creating the binary bitmap and then Copying the Binary Image to the bitmap
            binary_bitmap = new (std::nothrow) unsigned char* [Iy];
            for (int y=0; y<Iy; y++){ binary_bitmap[y] = new(std::nothrow) unsigned char [Ix]; }

            for (x=0; x<Ix; ++x){

                for (y=0; y<Iy; ++y){

                     unsigned char u = (unsigned char)qGray(Image1->pixel(x,y));

                     QRgb value;

                     if ( u < Bthr ){
                            value = qRgb(0,0,0);                //Black
                            binary_bitmap[y][x] = 1;            //For the binary bitmap it means black pixel
                            BinaryImage->setPixel(x,y,value);   //Fixing the new Binary Image
                     }
                     else{
                            value = qRgb(255,255,255);          //White
                            binary_bitmap[y][x] = 0;            //For the binary bitmap it means white pixel
                            BinaryImage->setPixel(x,y,value);   //Fixing the new Binary Image
                     }
                }
            }

            scene2 = new (std::nothrow) QGraphicsScene;
            scene2->addPixmap(QPixmap::fromImage(*BinaryImage));
            ui->graphicsView_2->setScene(scene2);

            loadImage2 = 1;     //Image has been put at the graphicsView_2
            flagBin = 1;        //Binarization has been done

            BinaryImage->save("BinarizationImage.tif");
        }
        else{  //Bthr == -1, user did not give threshold value

            QMessageBox::information(this, "Binarization Parameter", "You must give Threshold for Binarization process.", QMessageBox::Ok);
        }
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
void MainWindow::Image_Characteristics(){

    if( loadImage1 == 0 ){      //Load an Image first of all
        int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
        if( result3 == QMessageBox::Ok ){ return; }
    }

    QString info = " ";

    if( Image1 != NULL ){

        Ix = Image1->width();   //width
        Iy = Image1->height();  //height
        bpp = Image1->depth();  //bits per pixel

        info = "BPP: " + QString::number(bpp) + ", Width: " + QString::number(Ix)+ ", Height: " + QString::number(Iy);
    }
    else{
        info = "BPP: " + QString::number(bpp) + ", Width: " + QString::number(Ix)+ ", Height: " + QString::number(Iy);
    }

    std::string str = info.toStdString();

    QMessageBox::information(this, "Image Characteristics", str.c_str(), QMessageBox::Ok);
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
void MainWindow::Inverse(){

        if( loadImage1 == 0 ){  //Load an Image first of all
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }

        if( Image1 != NULL ){

                QImage reflection = Image1->mirrored();
                scene2 = new (std::nothrow) QGraphicsScene;

                scene2->addPixmap(QPixmap::fromImage(reflection));
                ui->graphicsView_2->setScene(scene2);
                loadImage2 = 1; //An image loaded to graphicsView_2
        }
}
//------------------------------------------------------------------------------------------------------
//------------------------------- END OF THE CODE ------------------------------------------------------
//------------------------------------------------------------------------------------------------------
