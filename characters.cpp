#include "mainwindow.h"
#include "ui_mainwindow.h"


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//Functions in order to compute the average handprinted character height
void MainWindow::Average_Handprinted_Character_Height(){


        if( loadImage1 == 0 ){      //Load an Image first of all
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }

        if( flagBin == 0 ){         //It means that the image has not been binarized
            int result1 = QMessageBox::information(this,"Error", "First of all Binarization.", QMessageBox::Ok);
            if( result1 == QMessageBox::Ok ){ return; }
        }

        if( bySum == 1 ){         //It means that you did not choose by more appearances method
            int result1 = QMessageBox::information(this,"Error", "First of all you have to choose by more appearances method .", QMessageBox::Ok);
            if( result1 == QMessageBox::Ok ){ return; }
        }

        QVector<LineBbox> BBox_Of_Lines;        //Keep the bounding box of all lines of the text
        QVector<LetterSize> charactersInfo;     //Keep information about the size of each character

//A. Search the file and Find the lines of text and remember where they are
        int NumberOfLines = -1;
        Finding_Lines_for_Average_Height(&NumberOfLines, &BBox_Of_Lines);

//B. Now extract and recognize the characters
        extract_Character(NumberOfLines, &BBox_Of_Lines, &charactersInfo, 0);

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
    printf("Size of the BBox_Of_Lines vector: %d\n", BBox_Of_Lines.size());
    printf("Size of the charactersInfo vector: %d\n", charactersInfo.size());
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

    flagAverageCharacter = 1;   //1:The average character function was used

//C. Return the Average height of handprinted character
        char buffer[256];

        if( !bySum ){   //we use the by more appearances method

            another_averageHeight = Average_HistogramCharactersHeight(&charactersInfo);
            sprintf(buffer, "The average Handprinted-Character height, by more appearances method, of  %s is %d pxls.\n", strName.c_str(), another_averageHeight);
        }

        int result3 = QMessageBox::information(this, "Characters", buffer, QMessageBox::Ok);
        if( result3 == QMessageBox::Ok ){ return; }
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//Locate each line of text, and remember the start and end columns
//and rows. These are saved in the global array LINES.

void MainWindow::Finding_Lines_for_Average_Height(int *NumberOfLines, QVector<LineBbox> *textLines){

        int *hproj, i, j, n, m, counter;
        int lineStart, lineEnd;

//1. Construct a horizontal projection and look for minimum
        hproj = new (std::nothrow)int[ Iy*sizeof(int) ];

        for(i=0; i<Iy; i++){        //"Reading" the whole Image row by row

              counter = 0;          //It counts the black pixels at every line

              for (j=0; j<Ix; j++){ if( binary_bitmap[i][j] == BLACK ) counter++; }  //All the columns of the row

              hproj[i] = counter;
        }

//2. Zeros in Horizontal Projection array means that the row was all white pixels.

        i = 0;  j = 0;
        while(i < Iy){     //Editing every row of the Image

            LineBbox    lBboxTmp;   //A Bounding  box of a line: rstart, rend, cstart, cend;

//2.A. Find the start and end of a line with characters
            while( (i < Iy) && (hproj[i] == 0) ) i++;     //Keep going until you find sth non-zero
            lineStart = i;
            while ( (i < Iy) && (hproj[i]  > 0) ) i++;    //Keep going until you find zero
            lineEnd = i-1;

            lBboxTmp.rstart = lineStart;        //j_th line Bounding box
            lBboxTmp.rend = lineEnd;

//2.B. Look for the start and end columns of the above line
            lBboxTmp.cstart = -1;               //Finding the first column the line
            for (m=0; m < Ix; m++){             //Check every possible column in order to find the start

                for (n = lineStart; n <= lineEnd; n++)
                    if( binary_bitmap[n][m] == BLACK ){
                        lBboxTmp.cstart = m;
                        break;  //Let's go to find the end column
                    }

                if (lBboxTmp.cstart >= 0) break;
            }

            lBboxTmp.cend = -1;                 //Finding the last column of the line
            for(m = (Ix-1); m >= 0; m--){       //Check every possible column in order to find the end

                for (n = lineStart; n<= lineEnd; n++)
                    if ( binary_bitmap[n][m] == BLACK ){
                        lBboxTmp.cend = m;
                        break;
                    }

                if ( lBboxTmp.cend > 0) break;
            }

            textLines->append(lBboxTmp);
            j = j + 1;  //Measuring the number of bounding boxes of the text lines
        }

        j--;    //Now j == textLines.size()
        *NumberOfLines = (textLines->size())-1;

        delete [] hproj;
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//Extract every line from the image and print each one of them to a file-Image
void MainWindow::extract_Line(int NumberOfLines, QVector<LineBbox> *textLines){

        int thisline, rstart, rend, cstart, cend;

        for (thisline = 0; thisline < NumberOfLines; thisline++){  //For every bounding box

            //How wide and tall is every line/bounding box that we check
            rstart = (*textLines)[thisline].rstart;
            rend   = (*textLines)[thisline].rend;
            cstart = (*textLines)[thisline].cstart;
            cend   = (*textLines)[thisline].cend;

            BboxImage = new QImage(Ix, Iy, QImage::Format_RGB16);
            QRgb value;
            value = qRgb(255,255,255);                //White background

            for(int y=0; y<Iy; ++y)
                for(int x=0; x<Ix; ++x)
                 BboxImage->setPixel(x,y,value);      //All the image will be white

            if(thisline%4 == 0){ value = qRgb(255,0,0); }       //red
            else if(thisline%4 == 1){ value = qRgb(0,255,0); }  //green
            else if(thisline%4 == 2){ value = qRgb(0,0,255); }  //blue
            else { value = qRgb(255,102,0); }                   //orange

            //We're painting every bounding box
            for(int i=rstart; i<=rend; i++){            //Running along the height of the current line
                  for (int j=cstart; j<=cend; j++){     //Running along the width of the current line

                      if(binary_bitmap[i][j] == BLACK){ BboxImage->setPixel(j,i,value); }
                  }
            }

            char buffer[128];
            sprintf(buffer,"BoundingBoxes/%d.tif", thisline);

            BboxImage->save(buffer);
    }
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//Extract every character from the image and print each one of them to a file-Image
void MainWindow::extract_Character(int NumberOfLines, QVector<LineBbox> *textLines, QVector<LetterSize> *characters, int flagPrint){

        int col, startcol, endcol;
        int thisline, rstart, rend, cstart;
        int counter = 1;    //It counts the total number of the characters

//For all the lines  of the text, all characters
        for (thisline = 0; thisline < NumberOfLines; thisline++){

            //How wide and tall is every line that we check
            rstart = (*textLines)[thisline].rstart;
            rend =   (*textLines)[thisline].rend;
            cstart = (*textLines)[thisline].cstart;

//Extract individual characters
            col = cstart;

            do{     //We editing each line of the text right here

//Find a column with black pixels in it
//Find the first column where the pixels of a character start
                  startcol = col;
                  following_BLACK_column(&startcol, rstart, rend);
                  if (startcol < 0) continue;   //There isn't any character left at this line

//Find a following column that is all white
//Find the first white column which is at the right of a character, as you observe the text
                  endcol = startcol;
                  following_WHITE_column(&endcol, rstart, rend);
                  if (endcol < 0) continue;

//We now have a character - dump/extract it
                  if(TEST){

                        if(flagPrint){

                            printCharacterOnFile(rstart, startcol, rend, endcol, counter);
                            counter++;
                        }
                        LetterSize CharacterTmp;        //Variable which keeps info for the current character
                        CharacterTmp.letterHeight = (rend-rstart);
                        CharacterTmp.letterWidth = (endcol-startcol);
                        characters->append(CharacterTmp);
                  }

                col = endcol++;   //From the all white column, we go to the next one which is black one

            }while(startcol >= 0 && endcol >= 0);
        }//End of the FOR -- thisline
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//Return the index of the next column with a black pixel in it
void MainWindow::following_BLACK_column(int *startcol, int rs, int re){

    for (int j=(*startcol); j<Ix; j++)
      for (int i=rs; i<=re; i++)
        if (binary_bitmap[i][j] == BLACK){
            (*startcol) = j; return;
        }

    (*startcol) = -1;
    return ;
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
// Return the index of the next column with a black pixel in it
void MainWindow::following_WHITE_column(int *endcol, int rs, int re){

    int flag;

    for (int j=(*endcol); j<Ix; j++){

          flag = 1;
          for (int i=rs; i<=re; i++)
                if (binary_bitmap[i][j] == BLACK){
                      flag = 0;
                      break;
                }

          if(flag){ (*endcol) = j; return; }
    }
    (*endcol) = -1;
    return ;
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// Print a Character as  Image
void MainWindow::printCharacterOnFile(int rs, int cs, int re, int ce, int counter){

    int Lx = Ix;  //Fix width: 100
    int Ly = Iy;  //Fix height: 100

    if (!TEST) return;     //FIXME Maybe we can erase it

    LetterImage = new QImage(Lx, Ly, QImage::Format_RGB16);
    QRgb value;
    value = qRgb(255,255,255);              //white background
    for(int y=0; y<Ly; ++y)
        for(int x=0; x<Lx; ++x)
             LetterImage->setPixel(x,y,value);  //All the image will be white


    if(counter%4 == 0){ value = qRgb(255,0,0); }       //red
    else if(counter%4 == 1){ value = qRgb(0,255,0); }  //green
    else if(counter%4 == 2){ value = qRgb(0,0,255); }  //blue
    else { value = qRgb(255,102,0); }                   //orange


    for (int i=rs; i<=re; i++){         //Running along the height of the current character,row by row
          for (int j=cs; j<=ce; j++){   //Running along the width of the current character

                if(binary_bitmap[i][j] == BLACK){ LetterImage->setPixel(j,i,value); }
          }
    }

    char buffer[128];
    sprintf(buffer,"Characters/%d.tif", counter);

    LetterImage->save(buffer);
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//Return the Average height of handprinted character, which is the most presentable height. Version 2.0
int MainWindow::Average_HistogramCharactersHeight(QVector<LetterSize> *characters){

           int min = 1000000, max = 0, *Heights, maxHeight = 0, height = 0;

           for(int i = 0; i < characters->size() ; i++){

                if( (*characters)[i].letterHeight <= min ){ min = (*characters)[i].letterHeight; }
                if( (*characters)[i].letterHeight >= max ){ max = (*characters)[i].letterHeight; }
           }

           Heights = new(std::nothrow) int[(max+1)];
           for(int i = 0; i <= max; i++){ Heights[i] = 0; }

           for(int i = 0; i < characters->size() ; i++)
                Heights[ (*characters)[i].letterHeight ]++;

           for(int i = 0; i <= max ; i++)       //Which height is presented more times
                if( Heights[i] >= maxHeight){

                    maxHeight = Heights[i];
                    height = i;
                }

           printf("The height: %d presents %d times.\n", height, maxHeight);

           for (int i = 0; i <= max ; i++) Heights[i]=(200*Heights[i])/maxHeight;

           QImage *Himage = new QImage(max+1,201,QImage::Format_RGB16);

           for (int x=0; x<=max; x++){

                for (int y=200; y>=200-Heights[x]; y--){
                    QRgb value;
                    value = qRgb(255,0,0);
                    Himage->setPixel(x,y,value);
                }

                for (int y=200-Heights[x]-1;y>=0;y--){
                   QRgb value;
                   value = qRgb(255,255,255);
                   Himage->setPixel(x,y,value);
                }
           }

           Himage->save("AverageHeightHistogram.tif");

           return height;
}


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//Printing each word of the handprinted document
void MainWindow::PrintingLettersOfDocument(){

        QVector<LineBbox> BBox_Of_Lines;     //Keep the bounding box of all lines of the text
        QVector<LetterSize> charactersInfo;  //Keep information about the size of each character
        int NumberOfLines = -1;

//Finding all the lines of the document
        Finding_Lines_for_Average_Height(&NumberOfLines, &BBox_Of_Lines);

//Now extract and recognize the characters
        extract_Character(NumberOfLines, &BBox_Of_Lines, &charactersInfo, 1);   //1: it means that we want to print each character

        int result1 = QMessageBox::information(this,"Information", "All the characters have been printed as Images in the Characters directory.", QMessageBox::Ok);
        if( result1 == QMessageBox::Ok ){ return; }
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//Function in order to print the document's lines
void MainWindow::PrintingLinesOfDocument(){

        QVector<LineBbox> BBox_Of_Lines;     //Keep the bounding box of all lines of the text
        int NumberOfLines = -1;

//Finding all the lines of the document
        Finding_Lines_for_Average_Height(&NumberOfLines, &BBox_Of_Lines);

//Now extract and recognize every line of the document
        extract_Line(NumberOfLines, &BBox_Of_Lines);

        int result1 = QMessageBox::information(this,"Information", "All the lines have been printed as Images in the BoundingBoxes directory.", QMessageBox::Ok);
        if( result1 == QMessageBox::Ok ){ return; }
}

//------------------------------------------------------------------------------------------------------
//-------------------------------------  END OF THE CODE -----------------------------------------------
//------------------------------------------------------------------------------------------------------
