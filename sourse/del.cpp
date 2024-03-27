#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <filesystem>

    int lines [1000] = {0} ;
    int somnum = 0 ;


    std::string filename  ;
    std::string filename_3 = filename ;

bool if_c (int list [] , int z , int n) {
    bool r = 0 ;
    for ( int i = 0 ; i < z ; i++)
    {
        if (list [i] == n)
        r = 1 ; 
    }
    return r ;
}
void writeNumbersBetweenArrays(int array1[], size_t size1, int array2[], size_t size2) {

    // اعتبارسنجی ورودی
    if (size1 == 0 || size2 == 0) {
        std::cerr << "Error: Arrays should not be empty." << std::endl;
        return;
    }

    // محاسبه اعداد بین هر جفت از عناصر آرایه‌ها
    for (size_t i = 0; i < std::min(size1, size2); ++i) {
        for (int j = array1[i]; j <= array2[i]; ++j) {
            lines [somnum] = j ;
            somnum++ ;
        }
    }

    std::cout << std::endl;
}

void removeLineFromFile( int ) ;

int main() {
    std::fstream folderPath_file ;
// Specify the folder path and output XML file path
    std::string folderPath_string ;

    folderPath_file.open("project_path.ini" , std::ios::in ) ;

    getline(folderPath_file , folderPath_string) ;
    filename_3 = folderPath_string ;
    filename = folderPath_string ;

    std::string temp_filename_1 = filename ;
    std::string temp_filename_2 = filename ;
    std::ifstream file_1(temp_filename_1) ;
    std::ifstream file_2(temp_filename_2) ;

    if (!file_1.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return 1;
    }
    if (!file_2.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return 1;
    }

    std::vector<int> lineNumbers_1;
    std::vector<int> lineNumbers_2;

    std::string line_1;
    std::string line_2;

    int lineNumber_1 = 1;
    int lineNumber_2 = 1;

    while (std::getline(file_1, line_1)) {
        size_t found_1 = line_1.find("<group>");
        if (found_1 != std::string::npos) {
            // عبارت "group" در این خط وجود دارد
            lineNumbers_1.push_back(lineNumber_1);
        }

        lineNumber_1++;
    }
        while (std::getline(file_2, line_2)) {
        size_t found_2 = line_2.find("</group>");
        if (found_2 != std::string::npos) {
            // عبارت "group" در این خط وجود دارد
            lineNumbers_2.push_back(lineNumber_2);
        }

        lineNumber_2++;
    }


    // تبدیل std::vector به int[]
    int* lineNumberArray_1 = new int[lineNumbers_1.size()];
    int* lineNumberArray_2 = new int[lineNumbers_2.size()];
    std::copy(lineNumbers_1.begin(), lineNumbers_1.end(), lineNumberArray_1);
    std::copy(lineNumbers_2.begin(), lineNumbers_2.end(), lineNumberArray_2);

    int array1[lineNumbers_1.size()] ;
    int array2[lineNumbers_2.size()] ;

    // نمایش شماره خطوط حاوی "group"
    if (!lineNumbers_1.empty()) {
        std::cout << "Lines containing '<group>': ";
        for (int i = 0; i < lineNumbers_1.size(); ++i) {
            std::cout << lineNumberArray_1[i] << " ";
            array1 [i] = lineNumberArray_1[i] ;
        }
        std::cout << std::endl;
    } else {
        std::cout << "No lines containing '<group>' found." << std::endl;
    }
        if (!lineNumbers_2.empty()) {
        std::cout << "Lines containing '</group>': ";
        for (int i = 0; i < lineNumbers_2.size(); ++i) {
            std::cout << lineNumberArray_2[i] << " ";
            array2 [i] = lineNumberArray_2[i] ;
        }
        std::cout << std::endl;
    } else {
        std::cout << "No lines containing '</group>' found." << std::endl;
    }

    // حذف آرایه تخصیص یافته به صورت دستی

    int x = 0 ;
    // مثال: نوشتن اعداد بین دو آرایه

        delete[] lineNumberArray_1;
    delete[] lineNumberArray_2;

    size_t size1 = sizeof(array1) / sizeof(array1[0]);
    size_t size2 = sizeof(array2) / sizeof(array2[0]);

    writeNumbersBetweenArrays(array1, size1, array2, size2);

    for ( int i = 0 ; i < 1000 ; i++)
    {
    x++ ;
    if (lines [i+1] == 0)
    i = 1000 ;
    }
    int lines_2 [x] ;
    for ( int i = 0 ; i < x ; i++)
    {
        lines_2 [i] = lines [i] ;
    }
    int y = 0 ;
    
    for ( int i = 0 ; i < x ; i++ )
    {
        
    for ( int j = 0 ; j < x ; j++ )
    {
        
        if ( lines_2 [i] > lines_2 [j] )
        {
        y = lines_2 [i] ;
        lines_2 [i] = lines_2 [j] ;
        lines_2 [j] = y ;
        }
    }
    }
    int lines_3 [x] = {0};
    int z = 0 ;
    for (int i = 0 ; i < x ; i++ )
    {
        if ( lines_2 [i] != lines_3 [z-1] )
        {
        lines_3 [z] = lines_2 [i] ;
        z++ ;
        }
    }
    int lines_4 [z] ;
    for ( int i = 0 ; i < z ; i++ )
    lines_4 [i] = lines_3 [i] ;
    for ( int i = 0 ; i < z ; i++)
    {
    std::cout << lines_4 [i] << " ";
    }
    // فراخوانی تابع برای حذف خط مورد نظر از فایل
        // باز کردن فایل برای خواندن و نوشتن
    std::ifstream inFile_2(filename_3);
    std::ofstream outFile_2(filename_3 + ".tmp");

    if (!inFile_2 || !outFile_2) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 0 ;
    }

    // خواندن خطوط فایل و نوشتن خطوط غیرمورد نظر به فایل جدید
    std::string line_4;
    int currentLine = 1 ;

    while (std::getline(inFile_2, line_4)) {
        if (!(if_c (lines_4 , z , currentLine ))) {
            outFile_2 << line_4 << std::endl;
        }

        ++currentLine;
    }

    // بستن فایل‌ها
    inFile_2.close();
    outFile_2.close();
    file_1.close() ;
    file_2.close() ;

    // حذف فایل اصلی و تغییر نام فایل جدید به نام فایل اصلی
    std::remove(filename_3.c_str());
    std::rename((filename_3 + ".tmp").c_str(), filename_3.c_str());

}