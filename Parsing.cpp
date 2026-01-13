#include "Parsing.hpp"
#include <absract.h>
#include <string>

Parsing::Parsing(){
	this->inputType = null;
}

Parsing::Parsing( std::vector<std::string>commands, int inputType ){
	this->inputType = inputType;
	this->file = commands;
}

Parsing::Parsing( const Parsing &cpy )
{
	*this = cpy;
}

Parsing &Parsing::operator=( const Parsing &src )
{
	if (this != &src)
	{
		this->commands = src.commands;
		this->file = src.file;
		this->inputType = src.inputType;
	}
	return (*this);
}

Parsing::~Parsing() {}

const char *Parsing::InvalidInput::what() const throw()
{
	return "The input given is invalid";
}

void Parsing::initMatch()
{
	std::string str[] = {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};
	for (int i = 0; i <= _exit; i++)
		this->matchCommand.insert({str[i], i});

	std::string  val[] = {"int8", "int16", "int32", "float", "double"};
	for (int i = 0; i <= DOUBLE; i++)
		this->matchValue.insert({str[i], i});

}

void Parsing::parseFile()
{
	if (this->inputType == null)
		throw InvalidInput();
	this->initMatch();

	this->error = false;
	for (int i = 0; i < this->file.size(); i++)
	{
		this->parseLine(i);
	}

	for (int i = 0; i < commands.size() ;i++)
	{
		std::cout << "command: " << commands[i].command << " value : " << std::endl;
	}
	for (int i = 0; i < errors.size() ;i++)
	{
		std::cout << "error: " << errors[i] << std::endl;
	}
}

// TODO I have to handle the comments, (could be anywhere and could male a command invalid)
// The values do not work too, I have a lot of errors, and I have to check for the value INSIDE the parentheses
void Parsing::parseLine( int line )
{
	t_command cmd;
	std::string first_half;
	std::string second_half;

	first_half = this->file[line].substr(0, this->file[line].find(" "));
	second_half = this->file[line].substr(this->file[line].find(" ") + 1, this->file[line].length());

	std::cout << "first half : " << first_half << std::endl;
	std::cout << "second half : " << second_half << std::endl;
	std::map<std::string, int>::iterator it = this->matchCommand.find(first_half);
	if (it == this->matchCommand.end())
	{
		this->error = true;
		std::string error = "Unknown command: " + first_half + " at line: " + std::to_string(line + 1) + ".";
		this->errors.insert(this->errors.end(), error);
	}
	else
		cmd.command = it->second;
	cmd.io = null;
	if (cmd.command == push || cmd.command == assert)
	{
		bool err = false;
		it = this->matchValue.find(second_half);
		if (it == this->matchValue.end())
		{
			this->error = true;
			err = true;
			std::string error = "Unknown Value: " + second_half + " at line: " + std::to_string(line + 1) + ".";
			this->errors.insert(this->errors.end(), error);
		}
		if (second_half.find(")") + 1 == std::string::npos)
		{
			err = true;
			error = true;
			std::string error = "Invalid Value: " + second_half + "at line: " + std::to_string(line);
			this->errors.insert(this->errors.end(), error);
		}
		if (err)
			return ;	
		cmd.io = it->second;
	}
	this->commands.insert(this->commands.end(), cmd);
}
