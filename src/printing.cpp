//funções relacionadas à impressão e ordenação da tabela
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <iterator>

#include "include/classify.h"
#include "include/printing.h"

namespace sloc{

    /*!
    * Sorts the SourceFile objects in the vector based on the specified integer member.
    *
    * @param files Vector containing the SourceFile objects.
    * @param action Pointer to the integer member of SourceFile used for sorting.
    */
    void sort_files(std::vector<SourceFile>& files, int SourceFile :: *action) {
        std::sort(files.begin(), files.end(), [action](const SourceFile& entry1, const SourceFile& entry2) {
            return entry1.*action < entry2.*action;
        });
    }

    /*!
    * Sorts the SourceFile objects in the vector based on the specified string member.
    *
    * @param files Vector containing the SourceFile objects.
    * @param action Pointer to the string member of SourceFile used for sorting.
    */
    void sort_files_string(std::vector<SourceFile>& files, std:: string SourceFile :: *action) {
        std::sort(files.begin(), files.end(), [action](const SourceFile& entry1, const SourceFile& entry2) {
            return entry1.*action < entry2.*action;
        });
    }

    /*!
    * Calculates the sum of the values in the specified column type of SourceFile objects.
    *
    * @param files Vector containing the SourceFile objects.
    * @param collumnType Pointer to the integer member of SourceFile representing the column.
    * @return The sum of all values in the specified column type.
    */
    int sum_all(std::vector<SourceFile>& files, int SourceFile :: *collumnType) {
        int totalSum = 0;
        for (const SourceFile& file : files) {totalSum += file.*collumnType;} return totalSum;
    }

    /*!
    * Verifies and performs sorting of SourceFile objects based on the specified subaction from the RunningOpt object.
    *
    * @param files Vector containing the SourceFile objects.
    * @param runopt RunningOpt object containing the subaction to determine sorting criteria.
    */
    void verify_subaction(std::vector<SourceFile> &files, RunningOpt runopt){
        switch (runopt.subAction) {
            case 'f': sort_files_string(files, &SourceFile::filePath);break;
            case 't': sort_files_string(files, &SourceFile::fileType);break;
            case 'c': sort_files(files, &SourceFile::commentLines);break;
            case 'b': sort_files(files,  &SourceFile::blankLines);break;
            case 's': sort_files(files, &SourceFile::codeLines);break; 
            case 'a': sort_files(files, &SourceFile::totalLines);break;
        }
    }

    /*!
    * Calculates the length of the longest string in the specified column type of SourceFile objects.
    *
    * @param files Vector containing the SourceFile objects.
    * @param collumnType Pointer to the string member of SourceFile representing the column.
    * @param min Minimum column length to consider.
    * @return The length of the longest string in the specified column type.
    */
    int collumn_length(std::vector<SourceFile>& files, std::string SourceFile :: *collumnType, int min) {
        int BiggestLength = min + 2;
        for (SourceFile& file : files) {
            std::string& columnValue = file.*collumnType;
            if(int(columnValue.length()) > BiggestLength) {
                BiggestLength = columnValue.length();
            }
        }
        return BiggestLength;
    }

    /*!
    * Calculates and adds percentage values to the specified integer type in each SourceFile object,
    * and stores the result in the specified string type.
    *
    * @param files Vector containing the SourceFile objects.
    * @param intType Pointer to the integer member of SourceFile.
    * @param stringType Pointer to the string member of SourceFile where the percentage will be stored.
    */
    void add_percentages(std::vector<SourceFile>& files, int SourceFile :: *intType, std::string SourceFile :: *stringType){
        for (SourceFile& file : files) {
            std::ostringstream oss;
            oss << file.*intType << " (" << std::fixed << std::setprecision(1) << (float(file.*intType)/float(file.totalLines) *100) << "%)  ";
            std::string stringification = oss.str();
            file.*stringType = stringification;
        }
    }

    /*!
    * Prints the table of source file.
    *
    * @param files Vector containing the source files.
    * @param runopt The RunningOpt object specifying the options.
    */
    void print_table (std::vector<SourceFile> files, RunningOpt runopt){
        verify_subaction(files, runopt);

        add_percentages(files,&SourceFile::commentLines, &SourceFile::stringCommentLines);
        add_percentages(files,&SourceFile::blankLines, &SourceFile::stringBlankLines);
        add_percentages(files,&SourceFile::codeLines, &SourceFile::stringCodeLines);

        //new function? print header?

        int collumn1, collumn2, collumn3, collumn4, collumn5, collumn6;
        collumn1 = collumn_length(files, &SourceFile::filePath, 9);
        collumn2 = collumn_length(files, &SourceFile::fileType, 8);
        collumn3 = collumn_length(files, &SourceFile::stringCommentLines, 8);
        collumn4 = collumn_length(files, &SourceFile::stringBlankLines, 5);
        collumn5 = collumn_length(files, &SourceFile::stringCodeLines, 4);
        collumn6 = collumn_length(files, &SourceFile::stringTotalLines, 3);

        std::array<std::string, 6> header {"File Name", "Language", "Comments", "Blank", "Code", "All"};
        std::array<int, 6> collumnsWidth {collumn1, collumn2, collumn3, collumn4, collumn5, collumn6};

        if(size(files)== 0){
            std::cout << "ATTENTION: No files found in this directory, maybe try -r to find files recursively " << std:: endl;
            exit (1);
        }

        std::cout << "Files processed: " << size(files) << std::endl;
        std::cout << std::left;
        for(int i = 0; i < int(size(header)); i++){
            std::cout << std::setw(collumnsWidth[i]) << header[i];
            if(i==0){std::cout << "  ";}
        }
        std::cout << std::endl;
        std::cout << std::setfill('-') << std::setw(collumn1+collumn2+collumn3+collumn4+collumn5+collumn6) << "" << std::setfill(' ') << std::endl;

        // end of print header

        // beggining of print lines
        if(runopt.action == 's'){
            for (const SourceFile& file : files) {
                std::cout << std::left << std::setw(collumn1) << file.filePath << "  " << std::setw(collumn2) << file.fileType << std::setw(collumn3) << file.stringCommentLines  << std::setw(collumn4) << file.stringBlankLines  << std::setw(collumn5) << file.stringCodeLines  << std::setw(collumn6) << file.totalLines << std::endl;
            }
        }else{
            std::reverse(files.begin(), files.end());
            for (const SourceFile& file : files) {
                std::cout << std::left << std::setw(collumn1) << file.filePath << "  " << std::setw(collumn2) << file.fileType  << std::setw(collumn3) << file.stringCommentLines  << std::setw(collumn4) << file.stringBlankLines  << std::setw(collumn5) << file.stringCodeLines  << std::setw(collumn6) << file.totalLines << std::endl;
            }
        }
        //end of print lines

        std::cout << std::setfill('-') << std::setw(collumn1+collumn2+collumn3+collumn4+collumn5+collumn6) << "" << std::setfill(' ') << std::endl;

       if(files.size()>1){
        std::cout << std::left << std::setw(collumn1) << "SUM" << std::setw(collumn2) << "" << "  " << std::setw(collumn3) << sum_all(files, &SourceFile::commentLines) << std::setw(collumn4) << sum_all(files, &SourceFile::blankLines) << std::setw(collumn5) << sum_all(files, &SourceFile::codeLines) << std::setw(collumn6) << sum_all(files, &SourceFile::totalLines) << std::endl;
        std::cout << std::setfill('-') << std::setw(collumn1+collumn2+collumn3+collumn4+collumn5+collumn6) << "" << std::setfill(' ') << std::endl;
       }
    }
} 
