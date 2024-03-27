#ifndef IPCH_H
#define IPCH_H

#include <QMainWindow>
#include <QThread>
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
QT_BEGIN_NAMESPACE
namespace Ui { class ipch; }
QT_END_NAMESPACE

class ipch : public QMainWindow
{
    Q_OBJECT

public:
    ipch(QWidget *parent = nullptr);
    ~ipch();


private slots:
    void on_project_button_clicked();

    void on_project_line_editingFinished();

    void on_file_folder_line_editingFinished();

    void on_file_folder_button_clicked();

    void on_include_folder_button_clicked();

    void on_include_folder_line_editingFinished();

    void on_change_clicked();

    void on_includes_with_files_clicked();

    void on_load_clicked();

    void on_actionAbout_triggered();

private:

    Ui::ipch *ui;
};



#endif // IPCH_H
