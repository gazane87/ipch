#include <ctime>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using namespace std ;

int main()
{
    std::fstream destinationFilePath_file ;

    std::string destinationFilePath ;

    destinationFilePath_file.open("project_path.ini" , ios::in ) ;
    
    getline(destinationFilePath_file , destinationFilePath) ;

    std::stringstream ss;

    ss << std::time(nullptr) ;
    std::cout << ("copy " + destinationFilePath + " " + destinationFilePath + "-" + ss.str() + ".bac /y").c_str() ;
    system(("copy " + destinationFilePath + " " + destinationFilePath + "-" + ss.str() + ".bac /y").c_str()) ;
}