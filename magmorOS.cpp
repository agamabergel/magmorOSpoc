#include "blkdev.h"
#include "helper.h"
#include "myfs.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

class Modifier 
{
	private:
		Code code;

	public:
		Modifier(Code pCode) : code(pCode) {}
		friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) { return os << "\033[" << mod.code << "m"; }
};

int main(int argc, char **argv)
{

	if (argc != 4) 
	{
		std::cerr << "Usage: ./magmorOS <BlockDeviceFile> <username> <password>" << std::endl;
		return -1;
	}

	Modifier red(FG_RED);
	Modifier cyan(FG_CYAN);
	Modifier green(BG_GREEN);
	Modifier def(FG_DEFAULT);
	Modifier pink(FD_PINK);

	BlockDeviceSimulator *blkdevptr = new BlockDeviceSimulator(argv[1]);
	std::string username = argv[2];
	std::string password = argv[3];

	MyFs myfs(blkdevptr);
	bool exit = false;
	std::string currentDir = "/";

	std::cout << "Welcome to magmorOS" << std::endl;
	std::cout << "enter 'help' for supported commands";
	std::cout << std::endl;

	while (!exit) 
	{
		try 
		{
			std::string cmdline;
			std::cout << cyan << username << "@" << "host" << def << ":" << pink << currentDir << def << "$ ";
			std::getline(std::cin, cmdline, '\n');

			if (cmdline == std::string(""))
				continue;

			std::vector<std::string> cmd = Helper::split_cmd(cmdline);

			if (cmd[0] == LIST_CMD) 
			{
				MyFs::dir_list dlist;
				if (cmd.size() == 1)
					dlist = myfs.list_dir("/");

				else if (cmd.size() == 2)
					dlist = myfs.list_dir(cmd[1]);

				else
					std::cout << LIST_CMD << ": one or zero arguments requested" << std::endl;

				for (size_t i = 0; i < dlist.size(); i++) 
				{
					std::cout << std::setw(15) << std::left
						<< dlist[i].name + (dlist[i].is_dir ? "/":"")
						<< std::setw(10) << std::right
						<< dlist[i].file_size << std::endl;
				}
			} 
			else if (cmd[0] == "quit")
				std::cout	<< "exit out from os via `exit` command." << std::endl;

			else if (cmd[0] == EXIT_CMD) 
				exit = true;

			else if (cmd[0] == HELP_CMD) 
				std::cout << HELP_STRING;

			else if (cmd[0] == CREATE_FILE_CMD) 
			{
				if (cmd.size() == 2)
					myfs.create_file(cmd[1], false);

				else
					std::cout << CREATE_FILE_CMD << ": file path requested" << std::endl;
			} 
			else if (cmd[0] == CONTENT_CMD) 
			{
				if (cmd.size() == 2)
					std::cout << myfs.get_content(cmd[1]) << std::endl;

				else
					std::cout << CONTENT_CMD << ": file path requested" << std::endl;
			} 
			else if (cmd[0] == TREE_CMD)
				Helper::recursive_print(myfs, "", "");

			else if (cmd[0] == EDIT_CMD) 
			{
				if (cmd.size() == 2) 
				{
					std::cout << "Enter new file content" << std::endl;
					std::string content;
					std::string curr_line;
					std::getline(std::cin, curr_line);
					while (curr_line != "") 
					{
						content += curr_line + "\n";
						std::getline(std::cin, curr_line);
					}
					myfs.set_content(cmd[1], content);
				} 
				else 
					std::cout << EDIT_CMD << ": file path requested" << std::endl;
			} 
			else if (cmd[0] == CREATE_DIR_CMD)
			{
				if (cmd.size() == 2)
					myfs.create_file(cmd[1], true);

				else
					std::cout << CREATE_DIR_CMD << ": one argument requested" << std::endl;
			}
			else if (cmd[0] == "^[[A")
				std::cout	<< "banana";
			
			else
				std::cout << cmd[0] << ": command not found" << std::endl;
			

		} 
		catch (std::runtime_error &e) 
		{
			std::cout << e.what() << std::endl;
		}
	}
}
