#include "FileHandle.hpp"
#include <absract.h>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>
#include <vector>
#include <exception>

FileHandle::FileHandle()
{
	throw InvalidCreation();	
}

const char *FileHandle::InvalidCreation::what() const throw()
{
	return "I would be thankful if you would give me an argument";
}

FileHandle &FileHandle::operator=( const FileHandle &src )
{
	if (&src != this)
		this->fullFile = src.fullFile;
	return *this;
}

FileHandle::FileHandle( const FileHandle &cpy )
{
	*this = cpy;
}

FileHandle::~FileHandle() {}

FileHandle::FileHandle(int ac, char **av)
{
	if (ac == 1)
	{
		this->readIn();
		this->entryType = STDIN;
	}
	else
	{
		this->entryType = FILE_OUT;
		this->readFile(av[1]);
	}
}

bool FileHandle::checkEmpty( std::string &line )
{
	int i = 0;
	for (char c = line[i]; c != '\0'; i++, c = line[i])
	{
		if (c != '\t' && c != ' ' && c != '\n')
			return false;
	}
	return true;
}

void FileHandle::readIn()
{
	std::string line;
	bool run = true;

	while (run)
	{
		std::getline(std::cin, line);
		if (std::cin.eof())
			return ;
		if (line.find(";;") != std::string::npos)
			run = 0;
		if (!line.empty() && !checkEmpty(line))
			this->fullFile.insert(this->fullFile.end(), line);
	}
}

void FileHandle::readFile(char *fileName)
{
	std::fstream file;
	std::string line;
	int run = 1;

	file.open(fileName);
	if (!file.is_open())
	{
		this->readIn();
		return ;
	}
	while (run)
	{
		if (!std::getline(file, line))
			break ;
		if (line.find("exit") != std::string::npos)
			run = 0;
		if (!line.empty() && !checkEmpty(line))
			this->fullFile.insert(this->fullFile.end(), line);
	}
	file.close();
}

std::vector<std::string> FileHandle::getVec() const
{
	return this->fullFile;
}

int FileHandle::getType() const
{
	return this->entryType;
}
