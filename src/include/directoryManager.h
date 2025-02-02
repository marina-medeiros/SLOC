#ifndef DIRECTORY_H 
#define DIRECTORY_H 

#include <vector>

#include "classify.h"

/*
A partir da entrada, confira quais arquivos são válidos/existem.
Se existirem, adicione-os a lista:
std::list<SourceFile> files;
*/

namespace sloc{
    std::vector<SourceFile> create_file_list(const std::string& input, bool recursive);
    bool is_source_code(const std::string &filename, std::string &fileType);
} 

#endif