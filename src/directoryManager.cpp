#include <filesystem>
#include <iostream>
#include <vector>

#include "include/classify.h"
#include "include/input.h"

namespace sloc{

    /**
     * @brief Check if a file is source code based on its filename extension.
     * 
     * This function determines if a file is source code by checking its filename extension against a list of known source code extensions.
     * 
     * @param filename The name of the file to be checked.
     * @param fileType A string reference to store the type of the file if it is source code.
     * @return bool True if the file is source code, false otherwise.
     */
    bool is_source_code(const std::string &filename, std::string &fileType) {
        std::array extensions{ ".cpp", ".c", ".h", ".hpp" };

        size_t dot_pos = filename.find_last_of(".");

        if(dot_pos == std::string::npos){
            return false; //Se não encontrar o ponto, não há extensão
        }

        std::string file_extension = filename.substr(dot_pos);

        for (const auto &e : extensions) {
            if(file_extension == e){  //Se a extensão do arquivo válida

            if (file_extension == ".cpp") {fileType="C++  ";}
            if (file_extension == ".hpp") {fileType="C++ header  ";}
            if (file_extension == ".c") {fileType="C  ";}
            if (file_extension == ".h") {fileType="C/C++ header  ";}

            return true;
            }
        }
        return false;
    }
    
    /**
     * @brief Create a list of source files from the given input path.
     * 
     * This function generates a list of source files from the specified input path. If the path points to a single file, only that file is considered.
     * If the path points to a directory, all files within it are considered.
     * 
     * @param input The input path to search for source files.
     * @param recursive Flag indicating whether to search recursively within subdirectories.
     * @return std::vector<SourceFile> A vector containing information about the identified source files.
     */
    std::vector<SourceFile> create_file_list(const std::string& input, bool recursive) {
        std::vector<SourceFile> files;
         std::filesystem::path inputPath (input);

        if(std::filesystem::is_regular_file(inputPath)){
            SourceFile newFile;

            newFile.filePath = inputPath.string();
            newFile.fileName = inputPath.filename().string(); 

            if(is_source_code(newFile.fileName, newFile.fileType)){
                files.push_back(newFile);   
            }else{
                std::cout << "ATTENTION: Unable to read " << newFile.fileName << std:: endl;
                helpmessage();
                exit (1);
            }

        }else{
            if(recursive){
                for (const auto& entry : std::filesystem::recursive_directory_iterator(inputPath)) {
                    if (std::filesystem::is_regular_file(entry)) {
                        SourceFile newFile;

                        newFile.filePath = entry.path().string();
                        newFile.fileName = entry.path().filename().string();

                        if(is_source_code(newFile.fileName, newFile.fileType)){
                            files.push_back(newFile);   
                        }
                    }
                }
            }else{
                for (const auto& entry : std::filesystem::directory_iterator(inputPath)) {
                    if (std::filesystem::is_regular_file(entry)) {
                        SourceFile newFile;

                        newFile.filePath = entry.path().string();
                        newFile.fileName = entry.path().filename().string();

                        if(is_source_code(newFile.fileName, newFile.fileType)){
                            files.push_back(newFile);   
                        }
                    }
                }
            }
        }

        return files;
    }
    
} 
