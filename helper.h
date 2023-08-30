#ifndef __HELPER_H__
#define __HELPER_H__

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "myfs.h"

using std::cout;

const std::string FS_NAME = "magmorOS";
const std::string LIST_CMD = "ls";
const std::string CONTENT_CMD = "cat";
const std::string CREATE_FILE_CMD = "touch";
const std::string CREATE_DIR_CMD = "mkdir";
const std::string EDIT_CMD = "fvim";
const std::string TREE_CMD = "tree";
const std::string HELP_CMD = "help";
const std::string EXIT_CMD = "exit";
const std::string HELP_STRING = "The following commands are supported: \n"
	+ LIST_CMD + " [<directory>] - list directory content. \n"
	+ CONTENT_CMD + " <path> - show file content. \n"
	+ CREATE_FILE_CMD + " <path> - create empty file. \n"
	+ CREATE_DIR_CMD + " <path> - create empty directory. \n"
	+ EDIT_CMD + " <path> - re-set file content. \n"
	+ HELP_CMD + " - show this help messege. \n"
	+ EXIT_CMD + " - gracefully exit. \n";


enum Code 
{
	FG_RED      = 31,
	FG_GREEN    = 32,
	FG_BLUE     = 34,
	FG_CYAN     = 36,
	FG_DEFAULT  = 39,
	BG_RED      = 41,
	BG_GREEN    = 42,
	BG_BLUE     = 44,
	FD_PINK     = 91,
	BG_DEFAULT  = 49
};

class Helper
{
public:
    static std::vector<std::string> split_cmd(std::string cmd);
    static void recursive_print(MyFs &myfs, std::string path, std::string prefix);
};


#endif 