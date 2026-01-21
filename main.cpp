#include "absract.h"
#include "FileHandle.hpp"
#include "Parsing.hpp"
#include "Execution.hpp"
#include <exception>

//TODO give each errors numbers so that they will be able to throw;

int main(int ac, char **av)
{
	FileHandle *file = new FileHandle(ac, av);
	Parsing *parser = new Parsing(file->getVec(), file->getType());
	try {
		parser->parseFile();
	}catch ( std::exception &err )
	{
		std::cerr << err.what() << std::endl;
		delete parser;
		delete file;
		return 1;
	}
	Execution *exec = new Execution( parser->getCommand() );
	try
	{
		exec->fullExec();
	}
	catch (std::exception &err)
	{
		std::cerr << err.what() << std::endl;
	}
	delete exec;
	delete parser;
	delete file;
}
