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
	throw std::runtime_error("not implemented");
	return "";
}

void MyFs::set_content(std::string path_str, std::string content) 
{
	throw std::runtime_error("not implemented");
}

MyFs::dir_list MyFs::list_dir(std::string path_str) 
{
	dir_list ans;
	throw std::runtime_error("not implemented");
	return ans;
}

