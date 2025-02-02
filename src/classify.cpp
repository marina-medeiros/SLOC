#include <string>
#include <fstream>
#include <vector>
#include "include/classify.h"

namespace sloc {

    /**
     * @brief Trim leading whitespace characters from a string.
     * 
     * @param s The input string.
     * @return std::string The string with leading whitespace characters removed.
     */
    inline std::string Classify::ltrim(const std::string &s) {
        const char *t = " \t\n\r\f\v";
        std::string clone{s};
        clone.erase(0, clone.find_first_not_of(t));
        return clone;
    }

    /**
     * @brief Trim trailing whitespace characters from a string.
     * 
     * @param s The input string.
     * @return std::string The string with trailing whitespace characters removed.
     */
    inline std::string Classify::rtrim(const std::string &s) {
        const char *t = " \t\n\r\f\v";
        std::string clone{s};
        clone.erase(clone.find_last_not_of(t) + 1);
        return clone;
    }

    /**
     * @brief Trim leading and trailing whitespace characters from a string.
     * 
     * @param s The input string.
     * @return std::string The string with leading and trailing whitespace characters removed.
     */
    inline std::string Classify::trim(const std::string &s) {
        return rtrim(ltrim(s));
    }

    /**
     * @brief Remove quotes from a string and track whether the string is in quotes.
     * 
     * @param line The input string.
     * @param inQuotes Boolean flag indicating whether the line is in quotes.
     * @return std::string The string with quotes removed.
     */
    std::string Classify::remove_quotes(std::string line, bool &inQuotes) {
        std::string result;
        
        for (int pos = 0; pos < int(line.length()); pos++) {
            if (line[pos] == '"' && (pos == 0 || line[pos - 1] != '\\')) { 
                inQuotes = !inQuotes;
                continue;
            }
            if (!inQuotes) {
                result += line[pos];
            }
        }

        return result;
    }

    /**
     * @brief Remove comments from a string and track whether the string is within a comment block.
     * 
     * @param line The input string.
     * @param inCommentBlock Boolean flag indicating whether the string is within a comment block.
     * @param hasComment Boolean flag indicating whether the line has a comment.
     * @param file Reference to the SourceFile object being analyzed.
     */
    void Classify::remove_comments(std::string& line, bool& inCommentBlock, bool& hasComment, SourceFile& file) {
        size_t posBlockStart = line.find("/*");
        size_t posBlockEnd= line.find("*/");
        size_t posSimpleComment = line.find("//");

        if((posSimpleComment != std::string::npos || posBlockStart != std::string::npos || posBlockEnd != std::string::npos) && !hasComment){
            file.commentLines++;
            hasComment = true;
        }

        if(posBlockStart != std::string::npos){
            inCommentBlock = true;
        }
        if(posBlockEnd != std::string::npos){
            inCommentBlock = false;
        }

        while (posBlockStart != std::string::npos) {
            if (posBlockEnd != std::string::npos) {
                if (posBlockEnd > posBlockStart) {
                    line.erase(posBlockStart, posBlockEnd - posBlockStart + 2); // Erase the block including '/*' and '*/'
            
                    posBlockStart = line.find("/*", posBlockStart); // Find the next occurrence of '/*' after the current position
                    posBlockEnd = line.find("*/", posBlockStart); // Find the next occurrence of '*/' after the current position
                } else {
                    // If '*/' not found after '/*'
                    line.erase(posBlockStart);
            
                    break;
                }
            } else {
                // If '/*' not found
                line.erase(posBlockStart);
        
                break;
            }
        }

        if(posBlockStart == std::string::npos && posBlockEnd != std::string::npos){
            posBlockEnd = line.rfind("*/");
            line.erase(0, posBlockEnd+2);
        }
        posSimpleComment = line.find("//");

        if(posSimpleComment != std::string::npos){
            line.erase(posSimpleComment);   
        }
    }

    /**
     * @brief Analyze files to count lines of code, comment lines, and blank lines.
     * 
     * @param files A vector of SourceFile objects to be analyzed.
     */
    void Classify::analize_files(std::vector<SourceFile> &files){
        for(SourceFile& file : files){
            std::ifstream currentFile(file.filePath);
            bool inQuotes  = false;
            bool inCommentBlock = false;
            bool lineHasComment;
            bool lineHasCode;
            bool lineIsBlank;
            if(currentFile.is_open()){
                std::string line;
                while(std::getline(currentFile, line)){
                    file.totalLines++;
                    lineHasCode = false;
                    lineHasComment = false;
                    lineIsBlank = false;

                    line = Classify::trim(line);
                    if(line.length() == 0 && !inCommentBlock){
                        file.blankLines++;
                        lineIsBlank = true;
                        continue;
                    }
                    line = remove_quotes(line, inQuotes);

                    if(inCommentBlock){
                        size_t posBlockEnd= line.find("*/");
                        if(posBlockEnd != std::string::npos){
                            inCommentBlock = false;
                        }
                        if(!lineHasComment){
                            file.commentLines++;
                        }
                        lineHasComment = true;
                    }

                    if(!inCommentBlock){
                        remove_comments(line, inCommentBlock, lineHasComment, file);

                        line = Classify::trim(line);

                        if(line.length() != 0){
                            file.codeLines++;
                            lineHasCode = true;
                        }
                    }
                    if(!lineHasCode && !lineHasComment && !lineIsBlank && !inCommentBlock){
                        file.codeLines++;
                        lineHasCode = true;
                    }
                }
                currentFile.close();
            }
        }
    }
    
}