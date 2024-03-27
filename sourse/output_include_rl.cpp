#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std ;
namespace fs = std::filesystem;

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


int main()
{
    std::fstream project_path_file ;
    // Specify the folder path and output XML file path


    project_path_file.open("project_path.ini" , ios::in) ;

    getline(project_path_file , project_path) ;

    std::fstream folderPath_file ;
    // Specify the folder path and output XML file path
    std::string folderPath_string ;

    folderPath_file.open("include_folder.ini" , ios::in ) ;
    
    getline(folderPath_file , folderPath_string) ;
    
    // Define the folder path
    fs::path folderPath = folderPath_string ;

    // Create an XML file to store the folder coordinates
    std::ofstream outputFile("output_include_rl.out");

    // Traverse the folder recursively and read the coordinates of subfolders
    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (entry.is_directory()) {
            outputFile << "\t<state>" << make_relative_path(project_path , entry.path().string())  << "</state>\n";
        }
    }

    outputFile.close();

    std::cout << "Coordinates of subfolders have been successfully saved." << std::endl;

    return 0;
}
