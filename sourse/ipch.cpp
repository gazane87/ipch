#include "ipch.h"
#include "ui_ipch.h"
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <QProcess>
#include <ctime>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QDataStream>
#include <QPixmap>

namespace fs = std::filesystem;
using namespace std;

bool check = 0 ;
void s2b (char& ) ;

bool memory_bool [7] = {1,1,1,1,1,1,1};
std::string memory_string [3] = {"0" ,"0" ,"0"} ;
string getIndentation(int) ;
void traverseFolder(const string& , string& , int) ;
void createXML(const string& , const string&) ;

QString slash_2_back_slash (QString ) ;
QString back_slash_2_slash (QString ) ;

QString project_path_slash = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        "
      , project_path_back_slash = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        " ;

QString file_folder_path_slash = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        "
      , file_folder_path_back_slash = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        " ;

QString include_folder_path_slash = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        "
     , include_folder_path_back_slash = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        " ;

QString home_path = QDir::homePath() ;

ipch::ipch(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ipch)
{
    ui->setupUi(this);

    QPixmap pix(":/ax/ax/c_ipch.png");
    int w = ui->ax->width() ;
    int h = ui->ax->height() ;
    ui ->ax->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

ipch::~ipch()
{
    delete ui;
}

void ipch::on_project_button_clicked()
{
    QString filter = "Project File (*.ewp) ;; All Files (*.*)" ;
    if (memory_string[0].c_str()=="0")
    {
        memory_string [0] = home_path.toStdString() ;
    }
    QString project_path_temp = QFileDialog::getOpenFileName(this , "select project" , memory_string [0].c_str() , filter) ;

    if (project_path_temp.size() != 0)
    {
        QFile project_file_test (project_path_temp) ;

        if (project_file_test.open(QFile::ReadOnly | QFile::Text))
        {
            project_path_slash = project_path_temp ;
            project_path_back_slash = slash_2_back_slash(project_path_slash) ;

            ui->project_line->clear() ;

            ui->project_line->insert(project_path_temp) ;

            memory_string[0] = project_path_temp.toStdString() ;
        }
        else
        {
            ui->project_status->setText("<font color='#ddc422'>Select the project file path .</font>") ;
        }
        project_file_test.close() ;
    }
    ipch::on_project_line_editingFinished() ;
}

QString slash_2_back_slash (QString input)
{
    QString output = input ;

    for (int i = 0 ; i < input.size() ; i++)
    {
        if (input [i] == '/')
        {
            output [i] = '\\' ;
        }
        else
        {
            output [i] = input [i] ;
        }
    }
    return output ;
}

QString back_slash_2_slash (QString input)
{
    QString output = input ;

    for (int i = 0 ; i < input.size() ; i++)
    {
        if (input [i] == '\\')
        {
            output [i] = '/' ;
        }
        else
        {
            output [i] = input [i] ;
        }
    }

    return output ;
}

void ipch::on_project_line_editingFinished()
{
    QFile project_path_file("project_path.ini");

    project_path_file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text) ;


    QString project_path_temp = ui->project_line->text() ;

    QFile project_file_test (project_path_temp) ;
    {
        if (project_path_temp.size() != 0)
        {
            if (project_file_test.open(QFile::ReadOnly | QFile::Text))
            {
                project_path_slash = project_path_temp ;
                project_path_back_slash = slash_2_back_slash(project_path_slash) ;
                ui->project_status->setText("<font color='green'>The Project file opened successfully .</font>") ;
            }
            else
            {
                check = 1 ;
                ui->project_status->setText("<font color='red'>The project file could not be opened !</font>") ;
            }
        }
        else
        {
            check = 1 ;
            ui->project_status->setText("<font color='#ddc422'>Select the project file path .</font>") ;
        }
    }

    QTextStream out(&project_path_file); // ایجاد یک شیء QTextStream برای نوشتن به فایل

    out << project_path_back_slash ;

    project_path_file.close();

    project_file_test.close() ;
}


void ipch::on_file_folder_line_editingFinished()
{
    QFile folder_path("folder_path.ini");

    folder_path.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text) ;

    QString file_folder_path_temp = ui->file_folder_line->text() ;
    string file_folder_path_temp_string = file_folder_path_temp.toStdString() ;

    if (file_folder_path_temp.size() != 0)
    {
        if (fs::exists(file_folder_path_temp_string) && fs::is_directory(file_folder_path_temp_string))
        {
            file_folder_path_back_slash = file_folder_path_temp ;
            file_folder_path_slash = back_slash_2_slash(file_folder_path_temp) ;
            ui->file_folder_status->setText("<font color='green'>The files folder opened successfully .</font>") ;
        }
        else
        {
            check = 1 ;
            ui->file_folder_status->setText("<font color='red'>The files folder could not be opened !</font>") ;
        }
    }
    else
    {
        check = 1 ;
        ui->file_folder_status->setText("<font color='#ddc422'>Select the files folder path .</font>") ;
    }

    QTextStream out(&folder_path) ;

    out << file_folder_path_back_slash ;

    if (ui->includes_with_files->isChecked())
    {
        ui->include_folder_line->clear() ;

        ui->include_folder_line->insert(file_folder_path_temp) ;

        ipch::on_include_folder_line_editingFinished() ;
    }

    folder_path.close() ;
}

void ipch::on_file_folder_button_clicked()
{
    if (memory_string[1].c_str()=="0")
    {
        memory_string [1] = home_path.toStdString() ;
    }
    QString file_folder_path_temp = QFileDialog::getExistingDirectory(this , "select files folder" , memory_string [1].c_str() ) ;
    file_folder_path_temp = slash_2_back_slash(file_folder_path_temp) ;
    string file_folder_path_temp_string = file_folder_path_temp.toStdString() ;

    if (file_folder_path_temp.size() != 0)
    {
        if (fs::exists(file_folder_path_temp_string) && fs::is_directory(file_folder_path_temp_string))
        {
            file_folder_path_back_slash = file_folder_path_temp ;
            file_folder_path_slash = back_slash_2_slash(file_folder_path_temp) ;

            ui->file_folder_line->clear() ;

            ui->file_folder_line->insert(file_folder_path_temp) ;

            memory_string[1] = file_folder_path_temp.toStdString() ;
        }
        else
        {
            ui->file_folder_status->setText("<font color='red'>The files folder could not be opened !</font>") ;
        }
    }

    ipch::on_file_folder_line_editingFinished() ;
}

void ipch::on_include_folder_line_editingFinished()
{
    QFile include_folder("include_folder.ini") ;

    include_folder.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text) ;

    QString include_folder_path_temp = ui->include_folder_line->text() ;
    string include_folder_path_temp_string = include_folder_path_temp.toStdString() ;

    if (include_folder_path_temp.size() != 0)
    {
        if (fs::exists(include_folder_path_temp_string) && fs::is_directory(include_folder_path_temp_string))
        {
            include_folder_path_back_slash = include_folder_path_temp ;
            include_folder_path_slash = back_slash_2_slash(include_folder_path_temp) ;
            ui->include_folder_status->setText("<font color='green'>The includes folder opened successfully .</font>") ;
        }
        else
        {
            check = 1 ;
            ui->include_folder_status->setText("<font color='red'>The includes folder could not be opened !</font>") ;
        }
    }
    else
    {
        check = 1 ;
        ui->include_folder_status->setText("<font color='#ddc422'>Select the includes folder path .</font>") ;
    }

    QTextStream out(&include_folder) ;

    out << include_folder_path_back_slash ;

    include_folder.close() ;
}

void ipch::on_include_folder_button_clicked()
{
    if (memory_string[2].c_str()=="0")
    {
        memory_string [2] = home_path.toStdString() ;
    }
    QString include_folder_path_temp = QFileDialog::getExistingDirectory(this , "select files folder" , memory_string [2].c_str() ) ;
    include_folder_path_temp = slash_2_back_slash(include_folder_path_temp) ;
    string include_folder_path_temp_string = include_folder_path_temp.toStdString() ;

    if (include_folder_path_temp.size() != 0)
    {
        if (fs::exists(include_folder_path_temp_string) && fs::is_directory(include_folder_path_temp_string))
        {
            include_folder_path_back_slash = include_folder_path_temp ;
            include_folder_path_slash = back_slash_2_slash(include_folder_path_temp) ;

            ui->include_folder_line->clear() ;

            ui->include_folder_line->insert(include_folder_path_temp) ;
            memory_string[2] = include_folder_path_temp.toStdString() ;
        }
        else
        {
            ui->include_folder_status->setText("<font color='red'>The includes folder could not be opened !</font>") ;
        }
    }

    ipch::on_include_folder_line_editingFinished() ;
}

void ipch::on_change_clicked()
{
    ui->change->setEnabled(0) ;


    if(!ui->file_relative->isChecked() && !ui->file_standard->isChecked())
        ui->file_relative->setChecked(Qt::Checked);
    if(!ui->includes_relative->isChecked() && !ui->includes_standard->isChecked())
        ui->includes_relative->setChecked(Qt::Checked);

    check = 0 ;
    ipch::on_project_line_editingFinished();
    ipch::on_include_folder_line_editingFinished();
    ipch::on_file_folder_line_editingFinished() ;


    if (!check)
    {
        std::ofstream memory_file ("config.ini") ;
        memory_file << ui->includes_with_files->isChecked() << ' ' ;
        memory_file << ui->file_relative->isChecked() << ' ' ;
        memory_file << ui->includes_relative->isChecked() << ' ' ;
        memory_file << ui->import_groups_files->isChecked() << ' ' ;
        memory_file << ui->import_includes->isChecked() << ' ' ;
        memory_file << ui->delete_olds->isChecked() << ' ' ;
        memory_file << ui->backup_file->isChecked() << ' ' ;

        for (int i = 0; i < 3; ++i)
        {
            memory_file << memory_string[i] << '\n';
        }


        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, "warning", "Possibility of data loss!!\nIt is suggested that if you have disabled the backup option, enable it.\nDo you want to continue?",
                                     QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            ui->wait->setText("<font color='#7f7f7f'>This takes about 30 seconds .") ;
            QMessageBox::about(this, "wait" , "Don`t close the app !!\nPlease wait a few seconds ...    ") ;
            if (ui->backup_file->isChecked())
            {
                QProcess *myProcess_0 = new QProcess() ;
                myProcess_0->setProgram("backup.exe") ;
                myProcess_0->start() ;
                ui->wait->setText("<font color='#7f7f7f'>Macking a backup ...") ;
                Sleep (5000);
            }

            QProcess *myProcess_1 = new QProcess();
            QProcess *myProcess_2 = new QProcess();
            QProcess *myProcess_3 = new QProcess();
            QProcess *myProcess_4 = new QProcess();
            QProcess *myProcess_5 = new QProcess();
            QProcess *myProcess_6 = new QProcess();
            QProcess *myProcess_7 = new QProcess();
            QProcess *myProcess_8 = new QProcess();
            QProcess *myProcess_9 = new QProcess();
            QProcess *myProcess_10 = new QProcess();
            QProcess *myProcess_11 = new QProcess();
            QProcess *myProcess_12 = new QProcess();

            if (ui->delete_olds->isChecked())
            {
                myProcess_9->setProgram("del.exe");
                myProcess_9->start();
                ui->wait->setText("<font color='#7f7f7f'>Deleting old files ...") ;
                Sleep (5000);
            }

            // تنظیم مسیر فایل exe برای QProcess
            if (ui->import_groups_files->isChecked())
            {
            if (ui->file_relative->isChecked())
            {
                myProcess_1->setProgram("output_file_rl.exe");
                myProcess_1->start();
            }
            else
            {
                myProcess_2->setProgram("output_file_st.exe");
                myProcess_2->start();
            }
            }
            if (ui->import_includes->isChecked())
            {
            if (ui->includes_relative->isChecked())
            {
                myProcess_3->setProgram("output_include_rl.exe");
                myProcess_3->start();
            }
            else
            {
                myProcess_4->setProgram("output_include_st.exe");
                myProcess_4->start();
            }
            }
            if (ui->import_groups_files->isChecked() | ui->import_includes->isChecked())
            {
            ui->wait->setText("<font color='#7f7f7f'>Macking list from files ...") ;
            Sleep(10000);
            }
            if (ui->import_groups_files->isChecked())
            {
                if (ui->file_relative->isChecked())
                {
                    myProcess_5->setProgram("set_file_rl.exe");
                    myProcess_5->start();
                }
                else
                {
                    myProcess_6->setProgram("set_file_st.exe");
                    myProcess_6->start();
                }
            }
            if (ui->import_includes->isChecked())
            {
                if (ui->includes_relative->isChecked())
                {
                    myProcess_7->setProgram("set_include_rl.exe");
                    myProcess_7->start();
                }
                else
                {
                    myProcess_8->setProgram("set_include_st.exe");
                    myProcess_8->start();
                }
            }
            if (ui->import_groups_files->isChecked() | ui->import_includes->isChecked())
            {
                ui->wait->setText("<font color='#7f7f7f'>Importing files ...") ;
                Sleep(5000);
            }

            // اجرای فرایند


            ui->wait->setText("<font color='#7f7f7f'>finished !!") ;
            QMessageBox::information(this,"status" ,"Finished!");
            ui->wait->setText("") ;



        }

    }
    else
    {
        QMessageBox::warning(this,"warning" ,"One or more of inputs are wrong !");
    }




    ui->change->setEnabled(1) ;
}


void ipch::on_includes_with_files_clicked()
{
    if (ui->includes_with_files->isChecked())
    {
        ui->include_folder_button->setEnabled(0) ;
        ui->include_folder_line->setEnabled(0) ;
    }
    else
    {
        ui->include_folder_button->setEnabled(1) ;
        ui->include_folder_line->setEnabled(1) ;
    }
    ipch::on_include_folder_line_editingFinished();
    ipch::on_file_folder_line_editingFinished() ;

}


void ipch::on_load_clicked()
{

    QFile file("config.ini") ;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream  memory_file(&file);
    bool temp_bool [7] = {1,1,1,1,1,1,1};
    std::string temp_string [3] = {"0" ,"0" ,"0"} ;

    QString fileContent = memory_file.readAll();



    file.close() ;

    char temp_char [3] [10000] ;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 10000; ++j)
        {
            temp_char[i][j] = '\0' ;
        }
    }
    int c = 0;
    for (int i = 0; i <= 12; i+=2)
    {
        if(fileContent[i] == '1')
            temp_bool[c] = true ;
        else
            temp_bool[c] = false ;

        c++ ;
    }
    c = 14 ;
    for (int j = 0; j < 3; ++j)
    {
        for (int l = 0; l < 10000 ; ++l)
        {
            if (fileContent[c] != '\n')
                temp_char [j][l] = fileContent[c].toLatin1() ;
            else
                    l = 10000 ;
            c++ ;
        }

    }

    for (int i = 0; i < 3; ++i) {
        temp_string[i] = temp_char[i];
    }

    if (temp_string[0].c_str() == home_path.toStdString())
        temp_string[0] = "0" ;

    if (temp_string[1].c_str() == home_path.toStdString())
        temp_string[1] = "0" ;

    if (temp_string[2].c_str() == home_path.toStdString())
        temp_string[2] = "0" ;

    for (int i = 0; i < 7; ++i)
    {
        memory_bool[i] = temp_bool[i] ;
    }
    for (int i = 0; i < 3; ++i)
    {
        memory_string[i] = temp_string[i] ;
    }

    if (memory_bool[0])
        ui->includes_with_files->setCheckState(Qt::Checked);
    else
        ui->includes_with_files->setCheckState(Qt::Unchecked);

    if (memory_bool[1])
        ui->file_relative->setChecked(Qt::Checked);
    else
        ui->file_standard->setChecked(Qt::Checked);

    if (memory_bool[2])
        ui->includes_relative->setChecked(Qt::Checked);
    else
        ui->includes_standard->setChecked(Qt::Checked);

    if (memory_bool[3])
        ui->import_groups_files->setCheckState(Qt::Checked);
    else
        ui->import_groups_files->setCheckState(Qt::Unchecked);

    if (memory_bool[4])
        ui->import_includes->setCheckState(Qt::Checked);
    else
        ui->import_includes->setCheckState(Qt::Unchecked);

    if (memory_bool[5])
        ui->delete_olds->setCheckState(Qt::Checked);
    else
        ui->delete_olds->setCheckState(Qt::Unchecked);

    if (memory_bool[6])
        ui->backup_file->setCheckState(Qt::Checked);
    else
        ui->backup_file->setCheckState(Qt::Unchecked);

}

void s2b (char& x)
{
    if (((static_cast<int>(x))>(96))&&((static_cast<int>(x))<(123)))
    {
        x = static_cast<char>((static_cast<int>(x))-32) ;
    }
}



void ipch::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About" , "This program is used to manage iar projects .\nver : 1.0                               created by : gazane") ;
}

