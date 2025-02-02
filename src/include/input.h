#ifndef INPUT_H 
#define INPUT_H  

#include <string>

namespace sloc {
    /// The running options provided via CLI.
    struct RunningOpt {
        std::string inputName;
        char action;
        char subAction;
        bool recursive = false;
    };

    RunningOpt parse_cmd_line(int argc, char *argv[]);
    bool directory_exist(const std::string &target);
    bool file_exists(const std::string &str);
    void helpmessage();
    int verifyAction(char* argumento);
    void doAction(int opt, char *argv[], int argc ,RunningOpt* saida);
}

#endif 