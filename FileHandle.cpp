#include "FileHandle.hpp"
#include <string>

FileHandle::FileHandle()
{
	throw InvalidCreation();	
}

const char *FileHandle::InvalidCreation::what() const throw()
{
	return "I would be thankful if you would give me an argument";
}

FileHandle::FileHandle(int ac, char **av)
{
	if (ac == 1)
		this->readIn();
}

void FileHandle::readIn()
{
	std::string line;
	bool run = true;

	while (run)
	{

	}
}
