#include "absract.h"
#include "FileHandle.hpp"
#include "Parsing.hpp"
#include "Execution.hpp"

//TODO give each errors numbers so that they will be able to throw;

int main(int ac, char **av)
{
	FileHandle *file = new FileHandle(ac, av);
	Parsing *parser = new Parsing(file->getVec(), file->getType());
	try
	{
		parser->parseFile();
		Execution *exec = new Execution( parser->getCommand() );
		exec->fullExec();

		delete exec;
	}
	catch (std::exception &err)
	{
		std::cerr << err.what() << std::endl;
	}
	delete parser;
	delete file;
}
