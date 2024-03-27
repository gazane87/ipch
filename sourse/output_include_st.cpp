#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std ;
namespace fs = std::filesystem;

int main() {
    std::fstream folderPath_file ;
    // Specify the folder path and output XML file path
    std::string folderPath_string ;

    folderPath_file.open("include_folder.ini" , ios::in ) ;
    
    getline(folderPath_file , folderPath_string) ;
    
    // Define the folder path
    fs::path folderPath = folderPath_string ;

    // Create an XML file to store the folder coordinates
    std::ofstream outputFile("output_include_st.out");

    // Traverse the folder recursively and read the coordinates of subfolders
    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (entry.is_directory()) {
            outputFile << "\t<state>" << entry.path().string() << "</state>\n";
        }
    }

    outputFile.close();

    std::cout << "Coordinates of subfolders have been successfully saved." << std::endl;

    return 0;
}
