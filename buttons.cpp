#include "mainwindow.h"
#include "ui_mainwindow.h"

//-----------------------------------------------------------------------------------------
//---------------------------------  BUTTONS ----------------------------------------------
//-----------------------------------------------------------------------------------------

//on_ObjectName_SignalName
void MainWindow::on_pushButton_clicked(){    //FitToPage

        if( loadImage2 == 1 &&  loadImage1 == 1){   //Both of the graphicsView has an image on it.
            ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
            ui->graphicsView_2->fitInView(scene2->sceneRect(), Qt::KeepAspectRatio);
        }
}

void MainWindow::on_pushButton_2_clicked(){  //1:1

        ui->graphicsView->resetMatrix();
        ui->graphicsView_2->resetMatrix();
}

void MainWindow::on_pushButton_3_clicked(){  //+

        ui->graphicsView->scale(1.1, 1.1);
        ui->graphicsView_2->scale(1.1, 1.1);
}

void MainWindow::on_pushButton_4_clicked(){  //-

        ui->graphicsView->scale(0.9, 0.9);
        ui->graphicsView_2->scale(0.9, 0.9);
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void MainWindow::on_pushButton_5_clicked(){  //OK: for finding Lines

        QString spinTy = ui->spinBox->text();   //take value as string
        QString spinVy = ui->spinBox_2->text(); //take value as string

         Ty = spinTy.toInt();
         Vy = spinVy.toInt();

        char buffer[256];
        sprintf(buffer,"Are you sure: Ty = %d & Vy = %d ?", Ty,Vy);

        int result = QMessageBox::question(this, "Finding Lines", buffer, QMessageBox::Ok | QMessageBox::Cancel);

        flagFindLines = 1;  //Declare that Ty & Vy has been given by user

        if( result == QMessageBox::Cancel){
            Ty = -1;
            Vy = -1;
            flagFindLines = 0;
        }

        runParametric = 0;  //No parametric run
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void MainWindow::on_pushButton_6_clicked(){  //OK: for Binary Threshold

        QString spinB_Threshold = ui->spinBox_3->text();

        Bthr = spinB_Threshold.toInt();

        char buffer[256];
        sprintf(buffer,"Are you sure: Bin. Thr. = %d ?", Bthr);

        int result = QMessageBox::question(this, "Binarization", buffer, QMessageBox::Ok | QMessageBox::Cancel);

        if( result == QMessageBox::Cancel){ Bthr = -1; }    //Set an initial value of binary threshold
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void MainWindow::on_pushButton_7_clicked(){ //OK: for finding Words

        QString spinTx = ui->spinBox_4->text();   //take value as string
        QString spinVx = ui->spinBox_5->text();   //take value as string

         Tx = spinTx.toInt();
         Vx = spinVx.toInt();

         char buffer[256];
         sprintf(buffer,"Are you sure: Tx = %d & Vx = %d ?", Tx,Vx);

         int result = QMessageBox::question(this, "Finding Words", buffer, QMessageBox::Ok | QMessageBox::Cancel);

         flagFindWords = 1;  //Declare that Tx & Vx has been given by user

         if( result == QMessageBox::Cancel){
             Tx = -1;
             Vx = -1;
             flagFindWords = 0;
         }

         runParametric = 0;    //No parametric run
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void MainWindow::on_pushButton_8_clicked(){  //OK: for Horizontal_C

        QString spinH_C = ui->spinBox_6->text();    //take value as string

        horizontal_C = spinH_C.toInt();

        char buffer[256];
        sprintf(buffer,"Are you sure: Horizontal_C = %d ?", horizontal_C);

        int result = QMessageBox::question(this, "Horizontal RLSA", buffer, QMessageBox::Ok | QMessageBox::Cancel);

        flagHorizontalRLSA = 1;  //Declare that horizontal_C has been given by user

        runParametric = 0;    //No parametric run

        if( result == QMessageBox::Cancel ){
            horizontal_C = -1;
            flagHorizontalRLSA = 0;
            runParametric = 1;    //Still remaining on parametric running
        }
}


//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void MainWindow::on_pushButton_9_clicked(){ //OK: for Vertical_C

        QString spinV_C = ui->spinBox_7->text();    //take value as string

        vertical_C = spinV_C.toInt();

        char buffer[256];
        sprintf(buffer,"Are you sure: Vertical_C = %d ?", vertical_C);

        int result = QMessageBox::question(this, "Vertical RLSA", buffer, QMessageBox::Ok | QMessageBox::Cancel);

        flagVerticalRLSA = 1;  //Declare that vertical_C has been given by user

        runParametric = 0;    //No parametric run

        if( result == QMessageBox::Cancel ){
            vertical_C = -1;
            flagVerticalRLSA = 0;
            runParametric = 1;    //Still remaining on parametric running
        }
}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButton_10_clicked() //OK: for kind of produced photos/files
{
        if( (ui->checkBox->isChecked() == true) && (ui->checkBox_2->isChecked() == true) ){

            int result3 = QMessageBox::information(this, "Error", ".tif OR .dat  files?", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }
        else if( (ui->checkBox->isChecked() == true) ){  //.dat files

            int result3 = QMessageBox::information(this, "Produced Files", "You choose to create .dat  files.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ dbFlag = 1; }     //1: It means that we'll  create .dat  files.
        }
        else if( (ui->checkBox_2->isChecked() == true) ){ //.tif photos

            int result3 = QMessageBox::information(this, "Produced Files", "You choose to create .tif  files.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ dbFlag = 0; }     //0: It means that we'll  create .tif  files.
        }
        else{
            int result3 = QMessageBox::information(this, "Error", "You must choose one of them.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }
}

//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButton_11_clicked()     //OK: for average height
{
        if( (ui->checkBox_4->isChecked() == true) ){    //By appearances method

            int result3 = QMessageBox::information(this, "Average height", "You choose the by appearances method.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ bySum = 0;   }  //0: It means that we choose the by appearances method
        }
        else{
            int result3 = QMessageBox::information(this, "Error", "You must choose a method.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void MainWindow::on_pushButton_12_clicked()         //It's for parametric run of the algorithm
{
    if( (ui->checkBox_5->isChecked() == true) ){    //You want parametric running

        if( flagAverageCharacter != 1 ){    //It means that the average character function has not sun

            int result3 = QMessageBox::information(this, "Error", "You must use the Average Character Height First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; } //Exit();
        }

        int result3 = QMessageBox::information(this, "Parametric Run", "Do you want parametric run?", QMessageBox::Ok);
        if( result3 == QMessageBox::Ok ){

            runParametric = 1;  //we run the algorithms RLSA & X-Y cut parametric

            if( bySum ){  //We used the sum method for the average height

                Tx = (int)(averageHeight/2.0);
                Vx = (int)(averageHeight);

                Ty = (int)(2.0*averageHeight);
                Vy =(int)(averageHeight/4.0);

                horizontal_C = (int)(2.0*averageHeight);          //predefined limit C of continuous background pixel for horizontal RLSA
                vertical_C = (int)(averageHeight/2.0);
            }
            else{       //We used the more appearances method for the average height

                Tx = (int)(another_averageHeight /2.0);
                Vx = (int)(another_averageHeight );

                Ty = (int)(2.0*another_averageHeight );
                Vy =(int)(another_averageHeight /4.0);

                horizontal_C = (int)(2.0*another_averageHeight );          //predefined limit C of continuous background pixel for horizontal RLSA
                vertical_C = (int)(another_averageHeight/2.0);
            }

            return;
        }
    }
}

//------------------------------------------------------------------------------------------------------
//------------------------------- END OF THE CODE ------------------------------------------------------
//------------------------------------------------------------------------------------------------------
