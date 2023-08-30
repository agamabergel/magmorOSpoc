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

	if (strncmp(header.magic, MYFS_MAGIC, sizeof(header.magic)) != 0 || (header.version != CURR_VERSION)) 
	{
		format();
		std::cout << "os booted with 1024^2 bytes." << std::endl;
	}
}

void MyFs::format() 
{

	// put the header in place
	struct myfs_header header;
	strncpy(header.magic, MYFS_MAGIC, sizeof(header.magic));
	header.version = CURR_VERSION;
	blkdevsim->write(0, sizeof(header), (const char*)&header);

	
}

void MyFs::create_file(std::string path_str, bool directory) 
{
	throw std::runtime_error("not implemented");
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

