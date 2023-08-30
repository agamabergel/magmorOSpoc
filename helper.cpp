#include "helper.h"


std::vector<std::string> Helper::split_cmd(std::string cmd)
{
	std::stringstream ss(cmd);
	std::string part;
	std::vector<std::string> ans;

	while (std::getline(ss, part, ' '))
		ans.push_back(part);

	return ans;
}

void Helper::recursive_print(MyFs &myfs, std::string path, std::string prefix)
{
	MyFs::dir_list dlist = myfs.list_dir(path);
	for (size_t i = 0; i < dlist.size(); i++) 
	{
		MyFs::dir_list_entry &curr_entry = dlist[i];
		std::string entry_prefix = prefix;

		if (i == dlist.size() - 1)
			entry_prefix += "└── ";

		else
			entry_prefix += "├── ";

		std::cout << entry_prefix << curr_entry.name << std::endl;

		if (curr_entry.is_dir)
		{
			std::string dir_prefix = prefix;

			if (i == dlist.size() - 1)
				dir_prefix += "    ";

			else
				dir_prefix += "│   ";

			Helper::recursive_print(myfs, path + "/" + curr_entry.name, dir_prefix);
		}
	}
}



