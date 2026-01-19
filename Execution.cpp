#include "Execution.hpp"
#include <Operand.hpp>
#include <absract.h>
#include <cstdint>
#include <stack>

Execution::Execution()
{
	return ;
}

Execution::Execution( const std::vector<t_command> &cmds )
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

std::stack<Operand<eOperandType>*> Execution::getStack() const
{
	return this->s;
}

std::vector<t_command> Execution::getCommands() const
{
	return this->commands;
}

void Execution::fatalError()
{
	Operand<int8_t> *op = new Operand<int8_t>(Int8, "coucou");
	s.push(op);
	for (Operand<eOperandType> *op = this->s.top(); !this->s.empty(); op = this->s.top())
	{
		delete op;


		this->s.pop();
	}
}
