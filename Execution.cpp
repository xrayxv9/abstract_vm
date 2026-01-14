#include "Execution.hpp"
#include <absract.h>
#include <stack>

Execution::Execution()
{
	return ;
}

Execution::Execution( std::vector<t_command> &cmds )
{
	this->commands = cmds;
}

Execution::Execution( const Execution &src )
{
	*this = src;
}

Execution &Execution::operator=( const Execution &src )
{
	if (this != &src)
	{
		this->s = src.getStack();
		this->commands = src.getCommands(); 
	}
	return *this;
}

std::stack<long long int> Execution::getStack() const
{
	return this->s;
}

std::vector<t_command> Execution::getCommands() const
{
	return this->commands;
}
