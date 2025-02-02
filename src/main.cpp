/*!
 * @file main.cpp
 * @description
 * This program implements a single line of code count for C/C++ programs.
 * @author	Add your name here
 * @date	September, 9th 2024.
 * @remark On 2022-09-9 changed ...
 */
#include <cstdlib>
#include <dirent.h>
#include <vector>
#include <string>
using std::string;

#include "include/input.h"
#include "include/classify.h"
#include "include/directoryManager.h"
#include "include/printing.h"


int main(int argc, char *argv[]) {
  sloc::RunningOpt runop = sloc::parse_cmd_line(argc, argv);
  std::vector<sloc::SourceFile> src_files = sloc::create_file_list(runop.inputName, runop.recursive);
  sloc::Classify::analize_files(src_files);
  sloc::print_table(src_files, runop);
  return EXIT_SUCCESS;
}