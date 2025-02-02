#ifndef PRINT_H 
#define PRINT_H  

//funções relacionadas à impressão e ordenação da tabela
#include <string>
#include <vector>

#include "classify.h"
#include "input.h"

namespace sloc{
    void sort_files(std::vector<SourceFile>& files, int SourceFile :: *action);
    void sort_files_string(std::vector<SourceFile>& files, std:: string SourceFile :: *action);
    int sum_all(std::vector<SourceFile>& files, int SourceFile :: *collumnType);
    void verify_subaction(std::vector<SourceFile>& files, RunningOpt runopt);
    int collumn_length(std::vector<SourceFile>& files, std::string SourceFile :: *collumnType, int min);
    void add_percentages(std::vector<SourceFile>& files, int SourceFile :: *intType, std::string SourceFile :: *stringType);
    void print_table (std::vector<SourceFile> files, RunningOpt runopt);
} 

#endif