#include <iostream>
#include <fstream>
#include <string>

using namespace std ;

int main() {
    std::fstream destinationFilePath_file ;
    // Specify the folder path and output XML file path

    std::string destinationFilePath ;

    destinationFilePath_file.open("project_path.ini" , ios::in ) ;
    
    getline(destinationFilePath_file , destinationFilePath) ;

    // مسیر فایل مبدا
    std::string sourceFilePath = "output_file_st.out";


    // خواندن محتوای فایل مبدا
    std::ifstream sourceFile(sourceFilePath);
    if (!sourceFile.is_open()) {
        std::cerr << "Unable to open the source file.\n";
        return 1;
    }

    std::string fileContent((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
    sourceFile.close();

    // خواندن محتوای فایل مقصد
    std::ifstream destinationFile(destinationFilePath);
    if (!destinationFile.is_open()) {
        std::cerr << "Unable to open the destination file.\n";
        return 1;
    }

    std::string destinationContent((std::istreambuf_iterator<char>(destinationFile)), std::istreambuf_iterator<char>());
    destinationFile.close();

    // جستجوی <project> در محتوای فایل مقصد
    size_t projectPos = destinationContent.find("<project>");
    if (projectPos == std::string::npos) {
        std::cerr << "The <project> tag not found in the destination file.\n";
        return 1;
    }

    // اضافه کردن محتوای فایل مبدا به محتوای فایل مقصد
    destinationContent.insert(projectPos + sizeof("<project>") - 1, "\n" + fileContent);

    // نوشتن محتوای نهایی در فایل مقصد
    std::ofstream outputFile(destinationFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the destination file for writing.\n";
        return 1;
    }

    outputFile << destinationContent;
    outputFile.close();

    std::cout << "Content added successfully.\n";

    return 0;
}