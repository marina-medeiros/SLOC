#include <array>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <cstdlib> 
#include <cstring>
#include <string>
using std::string;
#include "include/input.h"


namespace sloc {
    /*!
    * Checks if a directory exists.
    *
    * @param target The path of the directory to check.
    *
    * @return True if the directory exists, false otherwise.
    */
    bool directory_exist(const std::string &target) {
        bool exists{ false };
        DIR *p_dir;
        p_dir = opendir(target.c_str());
        exists = (p_dir != nullptr);
        closedir(p_dir);
        return exists;
    }

    /*!
    * Checks if a file exists.
    *
    * @param str The path of the file to check.
    *
    * @return True if the file exists, false otherwise.
    */
    bool file_exists(const string &str) {
        std::ifstream fs{str};
        return fs.is_open();
    }

    /*!
    * Displays the help message for the sloc program.
    */
    void helpmessage(){
        std::cout << "Usage: sloc file/directory [options] " << std::endl;
        std::cout << "Options:"<< std::endl;
        std::cout << "           -h/--help       Display this information." << std::endl;
        std::cout << "           -r              Look for files recursively in the directory provided." << std::endl;
        std::cout << "           -s f/t/c/b/s/a  Sort table in ascending order by (f)ilename, (t) filetype," << std::endl;
        std::cout << "                           (c)omments, (b)lank lines, (s)loc, or (a)ll. Default is to show" << std::endl;
        std::cout << "                           files in ordem of appearance." << std::endl;
        std::cout << "           -S f/t/c/b/s/a  Same as above, but in descending order." << std::endl;
    }

    /*!
    * Verifies the action specified by the argument.
    *
    * @param argumento The argument to be verified.
    *
    * @return The index of the action if it matches one of the options, otherwise -1.
    */
    int verifyAction(char* argumento){
        std::array< std::string, 3 > options {"-r", "-s","-S"};
         for (int i = 0; i < 3; ++i) {
            if (options[i] == argumento) {
                return i; 
            }
        }
        return -1;
    }

    /*!
    * Performs the action specified by the option.
    *
    * @param opt The index of the option.
    * @param argv The command-line arguments.
    * @param argc The number of command-line arguments.
    * @param saida Pointer to the RunningOpt object to update.
    */
    void doAction(int opt, char *argv[], int argc ,RunningOpt* saida){
        std::array< std::string, 6 > subOptions {"f", "t", "c", "b", "s", "a"};
        switch (opt) {
         case 0: // -r  Look for files recursively in the directory provided.
            saida->recursive = true;
            doAction(verifyAction(argv[3]), argv, argc, saida);
            break;
            
         case 1: // -s
            saida->action = 's';{
                bool found = false;
                for (int i = 0; i < 6; ++i) {
                    if (subOptions[i] == argv[argc-1]) {
                        saida->subAction = subOptions[i][0];
                        found = true;
                        break;
                    }
                }
                if (!found) {
                doAction(4, argv, argc, saida);
                }
            }
            break;

         case 2: //-S
            saida->action = 'S';{
                bool found2 = false;
                for (int i = 0; i < 6; ++i) {
                    if (subOptions[i] == argv[argc-1]) {
                        saida->subAction = subOptions[i][0];
                        found2 = true;
                        break;
                    }
                }
                if (!found2) {
                doAction(4, argv, argc, saida);
                }
            }
            break;

         case 3:
            std::cerr << "This file/directory doesn't exist" << std:: endl;
            helpmessage();
            exit (1);
            break;

         case 4:
            std::cerr << "ATTENTION: Wrong indication of sorting field" << std:: endl;
            helpmessage();
            exit (1);
            break;

         case -1:
            std::cerr << "ATTENTION: Wrong indication of sorting order (Ascending or Descending)" << std:: endl;
            helpmessage();
            exit (1);
            break;

         default:
            std::cerr << "ATTENTION: INVALID INPUT, missing arguments" << std:: endl;
            helpmessage();
            exit (1);
            break;
        }
    }

    /*!
    * Parses the command-line arguments and returns the corresponding RunningOpt object.
    *
    * @param argc The number of command-line arguments.
    * @param argv The command-line arguments.
    *
    * @return The RunningOpt object parsed from the command-line arguments.
    */
    RunningOpt parse_cmd_line(int argc, char *argv[]) {
        RunningOpt saida;
        switch (argc) { // /scr nomedoarquivo (recursividade) mainAction subAction
            case 1: helpmessage(); exit (1); break; // /scr

            case 2: // /scr nomedoarquivo or help
            if((strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)){ 
                helpmessage();
                exit(1);
            }else{
                if(file_exists(argv[1]) ||directory_exist(argv[1])){
                    saida.inputName = argv[1];
                }else{
                    doAction(3,argv,argc,&saida);
                }
            }
            break;

            case 4: // /scr nomedoarquivo mainAction subAction
                if(file_exists(argv[1]) || directory_exist(argv[1])){
                    saida.inputName = argv[1];
                    doAction(verifyAction(argv[2]), argv, argc, &saida);
                }else{
                    doAction(3,argv,argc,&saida);
                }
            break;

            case 5: // /scr nomedoarquivo recursividade mainAction subAction
                if(file_exists(argv[1]) || directory_exist(argv[1])){
                    saida.inputName = argv[1];
                    doAction(verifyAction(argv[2]), argv, argc, &saida);
                }else{
                    doAction(3,argv,argc,&saida);
                }
            break;

            default: // <5 inputs
                doAction(-5, argv, argc, &saida);
                break;
            }


        return saida;
    }   
    
}