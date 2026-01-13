#include "absract.h"
#include "FileHandle.hpp"
#include "Parsing.hpp"

int main(int ac, char **av)
{
	FileHandle *file = new FileHandle(ac, av);
	Parsing *parser = new Parsing(file->getVec(), file->getType());

	parser->parseFile();

	delete parser;
	delete file;
}
