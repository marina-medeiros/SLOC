#ifndef _SLOC_H_
#define _SLOC_H_

#include <string>
#include <vector>
#include <vector>

namespace sloc {
    struct SourceFile{
        std::string fileName;
        std::string filePath;
        std::string fileType;
        int commentLines = 0;
        int codeLines = 0;
        int blankLines = 0;
        int totalLines = 0;
        std::string stringCommentLines;
        std::string stringCodeLines;
        std::string stringBlankLines;
        std::string stringTotalLines;
    };

    //Deve preencher todos os SourceFiles da lista criada pelo directoryManager
    class Classify {
    public:
        static inline std::string ltrim(const std::string &s);
        static inline std::string rtrim(const std::string &s);
        static inline std::string trim(const std::string &s);
        static std::string remove_quotes(std::string line, bool &quotesFlag);
        static void remove_comments(std::string& line, bool& inCommentBlock, bool& hasComment, SourceFile& file);
        static void analize_files(std::vector<SourceFile> &files);

    };
}
#endif