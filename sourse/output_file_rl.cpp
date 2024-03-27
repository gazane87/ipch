#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <filesystem>


using namespace std ;
namespace fs = filesystem;

string project_path ;

string make_relative_path(string ,string) ;
string convertToRelativePath(const string& , const string&) ;
void s2b (char&) ;

string convertToRelativePath(const string& targetPath, const string& filePath) 
{
    fs::path target(targetPath);
    fs::path file(filePath);

    target = fs::absolute(target);
    file = fs::absolute(file);

    auto targetIt = target.begin();
    auto fileIt = file.begin();

    while (targetIt != target.end() && fileIt != file.end() && (*targetIt) == (*fileIt))
    {
        ++targetIt;
        ++fileIt;
    }

    fs::path relativePath = {} ;
    while (fileIt != file.end())
    {
        relativePath /= "..";
        ++fileIt;
    }

    while (targetIt != target.end())
    {
        relativePath /= *targetIt;
        ++targetIt;
    }

    return relativePath.lexically_normal().string();
}

void s2b (char& x) 
{
    if (((static_cast<int>(x))>(96))&&((static_cast<int>(x))<(123)))
    {
        x = static_cast<char>((static_cast<int>(x))-32) ;
    }
}

string make_relative_path(string filePath ,string targetPath)
{
    const char project_dir [] = "$PROJ_DIR$\\" ;

    s2b(targetPath[0]);
    s2b(filePath[0]) ;

    string text = convertToRelativePath(targetPath, filePath);

    std::string relativePath_adr = std::string(project_dir) + text ;

    return relativePath_adr ;
}

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
                xmlContent += getIndentation(indent + 1) + "<name>" + make_relative_path(project_path , filePath) + "</name>\n";
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
    std::fstream project_path_file ;
    std::fstream folderPath_file ;
    // Specify the folder path and output XML file path
    std::string folderPath ;
    std::string outputFilePath ;

    project_path_file.open("project_path.ini" , ios::in) ;
    folderPath_file.open("folder_path.ini" , ios::in) ;

    getline(project_path_file , project_path) ;
    getline(folderPath_file , folderPath) ;
    outputFilePath = R"(output_file_rl.out)" ;
    
    createXML(folderPath, outputFilePath) ;

    return 0;
}
