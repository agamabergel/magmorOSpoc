#include "myfs.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include <sstream>

const char *MyFs::MYFS_MAGIC = "magmorOS";

MyFs::MyFs(BlockDeviceSimulator *blkdevsim_):blkdevsim(blkdevsim_) 
{
	struct myfs_header header;
	blkdevsim->read(0, sizeof(header), (char *)&header);

	std::cout << "os booted with 1024^2 bytes." << std::endl;

	if (strncmp(header.magic, MYFS_MAGIC, sizeof(header.magic)) != 0 || (header.version != CURR_VERSION)) 
		format();

	else
		blkdevsim->read(NODES_START, sizeof(header), (char *)&nodes);
}

void MyFs::format() 
{

	// put the header in place
	struct myfs_header header;
	strncpy(header.magic, MYFS_MAGIC, sizeof(header.magic));
	header.version = CURR_VERSION;
	blkdevsim->write(0, sizeof(header), (const char*)&header);
	memset(nodes.inodes, 0, sizeof(nodes.inodes));
	nodes.currEmptyLoc = DATA_START;
	nodes.currNode = 0;
	
}
/*
* This function checks if a file path exists
* @parm path
* @return none
*/
bool MyFs::checkFilePathExists(std::string path)
{
	for (unsigned int i = 0; i < INODES_C; i++)
		if (strcmp(nodes.inodes[i].name, path.c_str()) == 0) //found
			return true;

	return false;
}

void MyFs::create_file(std::string path_str, bool directory) 
{

	if (checkFilePathExists(path_str))
		throw std::runtime_error("\n\t[*] a file with that name is already exists! :(\n");
	
	strncpy(nodes.inodes[nodes.currNode].name, path_str.c_str(), PATH_MAX_LEN);
	nodes.inodes[nodes.currNode].addr = 0;
	nodes.inodes[nodes.currNode].size = 0;
	nodes.inodes[nodes.currNode].isDir = false;
	nodes.currNode++;

	if (directory)
		nodes.inodes[nodes.currNode].isDir = true;

	blkdevsim->write(NODES_START, sizeof(this->nodes), (char *)&nodes);
}

std::string MyFs::get_content(std::string path_str) 
{
	for (unsigned int i = 0; i < INODES_C; i++)
	{
		if (strcmp(nodes.inodes[i].name, path_str.c_str()) == 0) 
		{
			if (nodes.inodes[i].isDir == true)
				return "cat: " + path_str + "is a directory";

			if (nodes.inodes[i].addr != 0 && nodes.inodes[i].size != 0)
			{
				char *data = new char[nodes.inodes[i].size];
				this->blkdevsim->read(nodes.inodes[i].addr, nodes.inodes[i].size, data);
				std::string unallocatedData (data);
				delete data;

				return unallocatedData;
			}
			else
				return "";
		}
	}
}

void MyFs::set_content(std::string path_str, std::string content) 
{
	for (unsigned int i = 0; i < INODES_C; i++)
	{
		if (strcmp(nodes.inodes[i].name, path_str.c_str()) == 0) //found
		{
			nodes.inodes[i].size = content.size() + 1;
			nodes.currEmptyLoc += content.size() + 2;
			nodes.inodes[i].addr = nodes.currEmptyLoc;
			this->blkdevsim->write(nodes.inodes[i].addr, nodes.inodes[i].size, content.c_str());
			blkdevsim->write(NODES_START, sizeof(this->nodes), (char *)&nodes);
		}
	}
}

MyFs::dir_list MyFs::list_dir(std::string path_str) 
{
	dir_list dirList;
	for (unsigned int i = 0; i < INODES_C; i++)
	{
		if (nodes.inodes[i].name != std::string(""))
		{
			dir_list_entry entry;
			entry.name = nodes.inodes[i].name;
			entry.file_size = nodes.inodes[i].size;
			entry.is_dir = 0;
			dirList.push_back(entry);
		}
	}
	return dirList;
}

