#include "Parsing.hpp"
#include <absract.h>
#include <cctype>
#include <cstdlib>
#include <string>

Parsing::Parsing(){
	this->inputType = ERROR_IN;
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
	this->matchCommand.insert({str[0], push});
	this->matchCommand.insert({str[1], pop});
	this->matchCommand.insert({str[2], dump});
	this->matchCommand.insert({str[3], assert});
	this->matchCommand.insert({str[4], add});
	this->matchCommand.insert({str[5], sub});
	this->matchCommand.insert({str[6], mul});
	this->matchCommand.insert({str[7], _div});
	this->matchCommand.insert({str[8], mod});
	this->matchCommand.insert({str[9], print});
	this->matchCommand.insert({str[10], _exit});

	std::string  val[] = {"int8", "int16", "int32", "float", "double"};
	this->matchValue.insert({val[0], Int8});
	this->matchValue.insert({val[1], Int16});
	this->matchValue.insert({val[2], Int32});
	this->matchValue.insert({val[3], Float});
	this->matchValue.insert({val[4], Double});
}

void Parsing::parseFile()
{
	bool exitFound = false;
	if (this->inputType == ERROR_IN)
		throw InvalidInput();
	this->initMatch();

	this->error = false;
	for (int i = 0; i < this->file.size(); i++)
	{
		this->parseLine(i);
	}
	for (std::vector<t_command>::iterator it = this->commands.begin(); it != this->commands.end(); it++)
	{
		if (it->command == _exit)
		{
			exitFound = true;
			break ;
		}
	}

	if (!exitFound)
	{
		this->error = true;
		std::string error = "No exit point found.";
		this->errors.insert(this->errors.end(), error);
	}
	// for (int i = 0; i < commands.size() ;i++)
	// {
	// 	std::cout << "command enum: " << commands[i].command << " command: " << commands[i].cmd_written << " value enum: " << commands[i].io << " value written : " << commands[i].io_written << " number : " << commands[i].value << std::endl;
	// }
	for (int i = 0; i < errors.size() ;i++)
	{
		std::cout << "error: " << errors[i] << std::endl;
	}
}

int Parsing::checkNumber( std::string &str, t_command *cmd, int l )
{
	size_t i = 0;
	bool point = false;
	int err = 0;
	size_t start = str.find_first_not_of(" \t");
	size_t ending = str.find_last_not_of(" \t");

	str = str.substr(start, ending - start + 1);
	while (str[i])
	{
		if (!std::isdigit(str[i]) && (str[i] != '.' || (str[i] == '.' && point)))
		{
			err = 1;
			break ;
		}
		else if (str[i] == '.')
			point = true;
		i++;
	}
	if (err)
	{
		this->error = true;
		std::cout << "str[i]: " << str[i] << std::endl;
		std::string error = "Invalid format at line: " + std::to_string(l + 1) + ".";
		this->errors.insert(this->errors.end(), error);
		return 1;
	}
	cmd->value = str;
	return 0;
}


std::string Parsing::handleComments( std::string &str )
{
	if (str.find(";;") != std::string::npos)
		return "";
	size_t len = str.find(";");
	if (len != std::string::npos)
	{
		std::string line = str.substr(0, len);
		return line;
	}
	return str;
}

size_t	Parsing::findSplit( std::string &str, size_t &begin )
{
	size_t len = 0;
	bool c = false;
	while (str[len])
	{
		if (c && (str[len] == ' ' || str[len] == '\t'))
			break ;
		if (str[len] > ' ' && str[len] < '~')
		{
			if (!c)
				begin = len;
			c = true;
		}
		len++;
	}
	return len;
}

size_t	Parsing::findSplitValue( std::string &str )
{
	size_t len = 0;
	while (str[len])
	{
		if (!(str[len] == ' ' || str[len] == '\t'))
			break ;
		len++;
	}
	return len;
}

int Parsing::handleFirstHalf( std::string &str, int l, t_command *cmd)
{
	std::map<std::string, e_commands>::iterator it = this->matchCommand.find(str);
	if (it == this->matchCommand.end())
	{
		this->error = true;
		std::string error = "Unknown command: " + str + " at line: " + std::to_string(l + 1) + ".";
		this->errors.insert(this->errors.end(), error);
		cmd->command = nullCommand;
		cmd->cmd_written = "";
		return 1;
	}
	else
	{
		cmd->cmd_written = it->first;
		cmd->command = it->second;
	}
	return 0;
}

int Parsing::handleSecondHalf( std::string &str, int l, t_command *cmd)
{
	bool err = false;
	
	if (str.empty())
	{
		this->error = true;
		std::string error = "No Value after " + cmd->cmd_written + " at line: " + std::to_string(l + 1) + ".";
		this->errors.insert(this->errors.end(), error);
		cmd->command = nullCommand;
		cmd->cmd_written = "";
		return 1;
	}
	size_t openParent = str.find("(");
	size_t closeParent = str.find(")");
	if (openParent == std::string::npos)
	{
		this->error = true;
		err = true;
		std::string error = "No open Parenthesis at line: " + std::to_string(l + 1) + ".";
		this->errors.insert(this->errors.end(), error);
		return 1;
	}
	if (closeParent == str.length())
	{
		this->error = true;
		err = true;
		std::string error = "No closing Parenthesis at line: " + std::to_string(l + 1) + ".";
		this->errors.insert(this->errors.end(), error);
		return 1;
	}

	size_t whitespace = this->findSplitValue(str);
	std::string number = str.substr(openParent + 1, closeParent - openParent - 1);
	std::string val = str.substr(whitespace, openParent - whitespace);
	std::map<std::string, eOperandType>::iterator it = this->matchValue.find(val);
	if (it == this->matchValue.end())
	{
		this->error = true;
		err = true;
		std::string error = "Unknown Value: " + str + " at line: " + std::to_string(l + 1) + ".";
		this->errors.insert(this->errors.end(), error);
		return 1;
	}
	if (str.find(")") + 1 == std::string::npos)
	{
		err = true;
		error = true;
		std::string error = "Invalid Value: " + str + "at line: " + std::to_string(l);
		this->errors.insert(this->errors.end(), error);
		return 1;
	}
	err += this->checkNumber(number, cmd, l);
	if (err)
		return 1;
	cmd->io_written = it->first;
	cmd->io = it->second;
	return 0;
}

// TODO  check this : (23 3      2)
void Parsing::parseLine( int l )
{
	t_command cmd;
	std::string first_half;
	std::string second_half;
	int lineError = 0;

	cmd.value = "";
	std::string line = handleComments(this->file[l]);
	if (line == "")
		return ;

	size_t begin = 0;
	size_t splitPos = this->findSplit(line, begin);
	first_half = line.substr(begin, splitPos - begin);
	if (splitPos == line.length())
		second_half = "";
	else
		second_half = line.substr(splitPos + 1, line.length());
	
	lineError += this->handleFirstHalf(first_half, l, &cmd);
	cmd.io = nullOperand;
	
	if ((cmd.command == push || cmd.command == assert) && !lineError)
		lineError += this->handleSecondHalf(second_half, l, &cmd);
	if (!lineError)
		this->commands.insert(this->commands.end(), cmd);
}

std::vector<t_command> Parsing::getCommand() const
{
	return this->commands;
}
