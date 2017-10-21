#include "mainwindow.h"
#include "ui_mainwindow.h"


//----------------------------------------------------------------------------------
//------------------- FUNCTIONS FOR THE SEGMENTATION TAB ---------------------------
//----------------------------------------------------------------------------------

//Finding Words
void MainWindow::Finding_Words(){   //finding the words of a text

        if( loadImage1 == 0 ){      //You have to read an image first
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }

        if( flagBin == 0 ){         //It means that the image has not been binarized
            int result1 = QMessageBox::information(this,"Error", "First of all Binarization.", QMessageBox::Ok);
            if( result1 == QMessageBox::Ok ){ return; }
        }

        if( runParametric != 1 ){   //It means that we do not want parametric run

            if( flagFindLines == 0){    //It means that the user did not give Ty & Vy
                int result2 = QMessageBox::information(this,"Error", "You must provide Ty & Vy.", QMessageBox::Ok);
                if( result2 == QMessageBox::Ok ){ return; }
            }

            if( flagFindWords == 0 ){   //It means that the user did not give the Tx & Vx
                int result3 = QMessageBox::information(this,"Error", "You must provide Tx & Vx.", QMessageBox::Ok);
                if( result3 == QMessageBox::Ok ){ return; }
            }
        }

        int *y_axis_hist = new int[Iy];
        int x, y, Ymax=0;
        long sum = 0, count = 0;

    //Y-AXIS HISTOGRAM
        for(y=0; y<Iy; ++y){            //For every line of the Image

                y_axis_hist[y] = 0;     //Initialize every cell

                for(x=0; x<Ix; ++x){
                    unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                    if( u == 0){ ++y_axis_hist[y]; }    //Count the black pixels, at every line
                }

                if ( y_axis_hist[y] > Ymax ) Ymax = y_axis_hist[y];

                sum += y_axis_hist[y];          //It contains the total number of black pixels on an Image
                if(y_axis_hist[y]){ ++count; }  //How many rows have black pixels
        }

//NORMALIZATION OF THE HISTOGRAM
        for(y=0; y<Iy; ++y)
            y_axis_hist[y] = y_axis_hist[y] >= Ty;  //Hist[i] = { 0 αν Hist[i] < Ty, 1 αν Hist[i] ≥ Ty }.


//FINDING THE VALLEYS
        QVector<int> y_cuts;

        for(int y=0; y<Iy;){
            for(; y<Iy && y_axis_hist[y] != 0; ++y);      //Until to find the first cell with zero(O)
            int Vstart = y;                               //Start of the valley
            for(; y<Iy && y_axis_hist[y] == 0; ++y);      //Keep going till to find cell with one(1)
            int Vend = y;                                 //End of the valley
            int mid = Vstart + (Vend-Vstart)/2;           //Finding the middle of the valley
            if( (Vend-Vstart) >= Vy)                      //The width of the valley should be Vy, at least
                y_cuts.push_back(mid);                    //Keeping safe the middle of the valley
        }

        printf("Number of Middles = %d\n", y_cuts.size());

        delete[] y_axis_hist;

//FINDING THE WORDS OF THE DOCUMENT
        if( y_cuts.size() >= 2 ){   //At least 2 middles, so 2 valleys

            int tag = 1;
            for(int i=0; i<y_cuts.size()-1; ++i)
                    words(y_cuts[i], y_cuts[i+1], tag);     //Finding the words, it also produces the image
        }

        if(runParametric == 1){

            if( !bySum )
                 printf("Average Character Height is: %d.\n", another_averageHeight);

            printf("Ty = %d is two times the Average Height.\n", Ty);
            printf("Vy = %d is divide four times the Average Height.\n", Vy);
            printf("Tx = %d is divide two times the Average Height.\n", Tx);
            printf("Vx = %d is equal the Average Height.\n", Vx);
        }
        else
            printf("Ty = %d, Vy = %d, Tx = %d, Vx = %d \n", Ty, Vy, Tx, Vx);
}

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//WORDS:FOR THE FINDING WORDS
void MainWindow::words(int ys,int ye,int& tag){    //Finding the words of a document

        int *x_axis_hist = new int[Ix];
        int x, y, Xmax=0;
        long sum = 0,count = 0;

//A. X-AXIS HISTOGRAM
        for(x=0; x<Ix; ++x){

            x_axis_hist[x] = 0;

            for(y=ys; y<ye; ++y){       //Inside the valley of 0 (black) pixels

                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                if( u == 0){ ++x_axis_hist[x]; }    //Count the black pixels, at every column on the range[ys, ye]
            }

            if ( x_axis_hist[x] > Xmax ) Xmax = x_axis_hist[x];

            sum += x_axis_hist[x];              //It contains the total number of black pixels on an image
            if( x_axis_hist[x] ){ ++count; }    //How many columns have black pixels
        }

//B. NORMALIZATION OF THE HISTOGRAM
        for(x=0; x<Ix; ++x)
            x_axis_hist[x] = x_axis_hist[x] >= Tx;  //Hist[i] = { 0 αν Hist[i] < Tx, 1 αν Hist[i] ≥ Tx }.


//C & D. FINDING THE VALLEYS AND STORING THE MIDDLES OF THEM
        QVector<int> x_cuts;
        for(int x=0; x<Ix;){

            for(; x<Ix && x_axis_hist[x] != 0; ++x);    //Until to find the first cell with zero(O)
            int Vstart = x;                             //Start of the valley
            for(; x<Ix && x_axis_hist[x] == 0; ++x);    //Keep going till to find cell with one(1)
            int Vend = x;                               //End of the valley
            int mid = Vstart + (Vend - Vstart)/2;       //Finding the middle of the valley
            if( (Vend - Vstart) >= Vx )                 //The width of the valley should be Vx, at least
                    x_cuts.push_back(mid);              //Keeping safe the middle of the valley
        }

        printf("Number of Middles = %d\n ", x_cuts.size());


//e: ASSIGN TAGS AND FINDING THE WORDS OF THE DOCUMENT
     if( x_cuts.size() >= 2){         //At least 2 middles, so 2 valleys

             unsigned char **bitmapOfTag = NULL;
             bitmapOfTag = new (std::nothrow) unsigned char* [Iy];

             for (int y=0; y<Iy; y++){

                 bitmapOfTag[y] = new(std::nothrow) unsigned char[Ix];
                 for(int x=0; x<Ix; x++) bitmapOfTag[y][x] = 0;  //All the bitmap has zero value
             }

            //CREATION OF THE IMAGE WITH WORDS ONLY
            QImage *Himage = new QImage(Ix, Iy, QImage::Format_RGB16);
            QRgb value;
            value = qRgb(255,255,255);              //white background, qRgb(0,0, 0);
            for(int y=0; y<Iy; ++y)
                for(int x=0; x<Ix; ++x)
                    Himage->setPixel(x,y,value);    //All the image will be white

            //Assign tags to each region of black pixels
            for(int i=0; i<x_cuts.size()-1; ++i){
                for(int x=x_cuts[i]; x<x_cuts[i+1]; ++x)  //Crossing into the valley one step at a time
                        for(int y=ys; y<ye; ++y){

                                unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                                if( u == 0) {
                                    QRgb value;

                                    //We use three colours in order to paint the image, red-green-orange
                                    if( tag%3 == 0 ){value = qRgb(255,0,0); }          //red
                                    else if( tag%3 == 1 ){ value = qRgb(0,255,0); }    //green
                                    else{ value = qRgb(0,0,255); }                     //orange

                                    Himage->setPixel(x,y,value);
                                    bitmapOfTag[y][x] = tag;
                                }
                        }
                ++tag;  //Next tag for the next area of useful info
            }


            if( dbFlag == 1 ){ //We'l create .dat files

                Create_dot_Dat_Files_v_2_0(bitmapOfTag, "X_Y_cuts_DB/words/");
            }
            else{  //We'll create .tif files

                Himage->save("X_Y_cuts/findingWordsImage.tif");
            }

            delete[] x_axis_hist;

            if( bitmapOfTag != NULL ){
                for(int y=0;y<Iy;y++){ delete[] bitmapOfTag[y]; }

                delete bitmapOfTag;
                bitmapOfTag = NULL;
            }

            scene2 = new (std::nothrow) QGraphicsScene;
            scene2->addPixmap(QPixmap::fromImage(*Himage));
            ui->graphicsView_2->setScene(scene2);

            loadImage2 = 1;     //Image has been put at the graphicsView_2
     }
}


//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//Finding Lines
void MainWindow::Finding_Lines(){   //Finding the lines of a text

        if( loadImage1 == 0 ){      //You have to read an image first
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }

        if( flagBin == 0 ){     //It means that the image has not been binarized
            int result1 = QMessageBox::information(this,"Error", "First of all Binarization.", QMessageBox::Ok);
            if( result1 == QMessageBox::Ok ){ return; }
        }

        if( runParametric != 1 ){   //It means that we do not want parametric run

            if( flagFindLines == 0 ){   //It means that the user does not give the Ty & Vy
                int result2 = QMessageBox::information(this,"Error", "You must provide Ty & Vy.", QMessageBox::Ok);
                if( result2 == QMessageBox::Ok ){ return; }
            }
        }

        int *y_axis_hist = new int[Iy];
        int x, y, Ymax=0;
        long sum = 0, count = 0;

//Y-AXIS HISTOGRAM
        for(y=0; y<Iy; ++y){            //For every line of the Image

                y_axis_hist[y] = 0;     //Initialize every cell

                for(x=0; x<Ix; ++x){

                    unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                    if( u == 0){ ++y_axis_hist[y]; }    //Count the black pixels, at every line
                }

                if ( y_axis_hist[y] > Ymax ) Ymax = y_axis_hist[y];

                sum += y_axis_hist[y];          //It contains the total number of black pixels on an Image
                if(y_axis_hist[y]){ ++count; }  //How many rows have black pixels
        }

//NORMALIZATION OF THE HISTOGRAM
        for(y=0; y<Iy; ++y)
            y_axis_hist[y] = y_axis_hist[y] >= Ty;      //Hist[i] = { 0 αν Hist[i] < Ty, 1 αν Hist[i] ≥ Ty }.


//FINDING THE VALLEYS
        QVector<int> y_cuts;

        for(int y=0; y<Iy;){
            for(; y<Iy && y_axis_hist[y] != 0; ++y);      //Until to find the first cell with zero(O)
            int Vstart = y;                               //Start of the valley
            for(; y<Iy && y_axis_hist[y] == 0; ++y);      //Keep going till to find cell with one(1)
            int Vend = y;                                 //End of the valley
            int mid = Vstart + (Vend-Vstart)/2;           //Finding the middle of the valley
            if( (Vend-Vstart) >= Vy)                      //The width of the valley should be Vy, at least
                y_cuts.push_back(mid);                    //Keeping safe the middle of the valley
        }

        printf("Number of Middles = %d\n ", y_cuts.size());

        delete[] y_axis_hist;

//FINDING THE LINES OF THE DOCUMENT
        if( y_cuts.size() >= 2){     //At least 2 middles, so 2 valleys

                unsigned char **bitmapOfTag = NULL;
                bitmapOfTag = new (std::nothrow) unsigned char* [Iy];

                for (int y=0; y<Iy; y++){

                    bitmapOfTag[y] = new(std::nothrow) unsigned char[Ix];
                    for(int x=0; x<Ix; x++) bitmapOfTag[y][x] = 0;          //All the bitmap has zero value
                }

                //CREATION OF THE IMAGE WITH LINES ONLY
                QImage *Himage = new QImage(Ix, Iy, QImage::Format_RGB16);
                QRgb value;
                value = qRgb(255,255,255);              //White background, qRgb(0,0, 0);
                for(int y=0; y<Iy; ++y)
                    for(int x=0; x<Ix; ++x)
                        Himage->setPixel(x,y,value);    //All the image will be white

                //Assign tags to each region of black pixels
                for(int i=0,tag=1; i<y_cuts.size()-1; ++i,++tag)
                    for(int y=y_cuts[i]; y<y_cuts[i+1]; ++y)        //Crossing into the valley one step at a time
                            for(int x=0; x<Ix; ++x){
                                    unsigned char u = (unsigned char)qGray(BinaryImage->pixel(x,y));
                                    if( u == 0) {
                                        QRgb value;

                                        //We use four colours in order to paint the image, red-green-blue-orange
                                        if( tag%4 == 0 ){value = qRgb(255,0,0); }          //red
                                        else if( tag%4 == 1 ){ value = qRgb(0,255,0); }    //green
                                        else if( tag%4 == 2 ){ value = qRgb(0,0,255); }    //blue
                                        else{ value = qRgb(255,102,0);  }                  //orange

                                        Himage->setPixel(x,y,value);
                                        bitmapOfTag[y][x] = tag;
                                    }
                            }

                if( dbFlag == 1 ){ //We'l create .dat files

                    Create_dot_Dat_Files_v_2_0( bitmapOfTag, "X_Y_cuts_DB/lines/");
                }
                else{ //We'l create .tif files

                    Himage->save("X_Y_cuts/findingLinesImage.tif");  //Lines are mostly appeared on the image
                }


                if( bitmapOfTag != NULL ){
                    for(int y=0;y<Iy;y++){ delete[] bitmapOfTag[y]; }

                    delete bitmapOfTag;
                    bitmapOfTag = NULL;
                }

                scene2 = new (std::nothrow) QGraphicsScene;
                scene2->addPixmap(QPixmap::fromImage(*Himage));
                ui->graphicsView_2->setScene(scene2);

                loadImage2 = 1;     //Image has been put at the graphicsView_2

                if(runParametric == 1){

                    if( !bySum )
                         printf("Average Character Height is: %d.\n", another_averageHeight);

                    printf("Ty = %d is two times the Average Height.\n", Ty);
                    printf("Vy = %d is divide four times the Average Height.\n", Vy);
                }
                else{
                    printf("Ty = %d, Vy = %d\n", Ty, Vy);
                }
        }
}

//------------------------------------------------------------------------------------------------------
//------------------------------- END OF THE CODE ------------------------------------------------------
//------------------------------------------------------------------------------------------------------
