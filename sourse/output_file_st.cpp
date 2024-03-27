#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <filesystem>


using namespace std ;
namespace fs = filesystem;


std::string getIndentation(int indent) {
    std::string result;
    for (int i = 0; i < indent; ++i) {
        result += "    ";  // 4 spaces for each level of indentation
    }
    return result;
}

void traverseFolder(const std::string& folderPath, std::string& xmlContent, int indent) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((folderPath + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        const std::string fileName = findFileData.cFileName;

        if (fileName != "." && fileName != "..") {
            const std::string filePath = folderPath + "\\" + fileName;

            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // If it's a directory, recursively traverse
                xmlContent += getIndentation(indent) + "<group>\n";
                xmlContent += getIndentation(indent + 1) + "<name>" + fileName + "</name>\n";
                traverseFolder(filePath, xmlContent, indent + 1);
                xmlContent += getIndentation(indent) + "</group>\n";
            } else {
                // If it's a file, add a file element
                xmlContent += getIndentation(indent) + "<file>\n";
                xmlContent += getIndentation(indent + 1) + "<name>" +  filePath + "</name>\n";
                xmlContent += getIndentation(indent) + "</file>\n";
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void createXML(const std::string& folderPath, const std::string& outputFilePath) {
    // Recursively traverse the folder and create XML structure
    std::string xmlContent;
    traverseFolder(folderPath, xmlContent, 0);

    // Save the XML to a file
    std::ofstream outputFile(outputFilePath);
    if (outputFile.is_open()) {
        outputFile << xmlContent;
        outputFile.close();
        std::cout << "XML file created successfully.\n";
    } else {
        std::cerr << "Error creating XML file.\n";
    }
}

int main() 
{
    std::fstream folderPath_file ;
    // Specify the folder path and output XML file path
    std::string folderPath ;
    std::string outputFilePath ;

    folderPath_file.open("folder_path.ini" , ios::in) ;

    getline(folderPath_file , folderPath) ;
    outputFilePath = R"(output_file_st.out)" ;
    
    createXML(folderPath, outputFilePath) ;

    return 0;
}
