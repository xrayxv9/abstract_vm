#include "Execution.hpp"
#include <IOperand.hpp>
#include <Operand.hpp>
#include <absract.h>
#include <cstdint>
#include <list>
#include <stack>

Execution::Execution()
{
	return ;
}

Execution::Execution( const std::vector<t_command> &cmds )
{
	this->commands = cmds;
	this->rax = nullptr;
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

Execution::~Execution()
{
	this->fatalError();
}

std::list<const IOperand *> Execution::getStack() const
{
	return this->s;
}

std::vector<t_command> Execution::getCommands() const
{
	return this->commands;
}

void Execution::fatalError()
{
	if (this->rax != nullptr)
		delete this->rax;
	while (!s.empty())
	{
		const IOperand *tmp = s.front();
		this->s.pop_front();
		delete tmp;
	}
}

void Execution::_push()
{
	this->s.push_front(fact.createOperand(this->commands[this->i].io, this->commands[this->i].value));
}

void Execution::_pop()
{
	if (this->s.empty())
	{
		std::cerr << "Segfault" << std::endl;
		return;
	}
	rax = this->s.front();
	this->s.pop_front();
}

void Execution::_dump()
{
	IOperand *tmp;

	for (auto it = s.rbegin(); it != s.rend(); ++it)
		std::cout << *it << " " <<  (*it)->toString() << std::endl;
}

void Execution::_assert()
{
	if (this->rax != nullptr)
		delete this->rax;
	this->_pop();
	if (this->rax->toString() == this->commands[i].cmd_written)
		this->_push();
	else
		std::cerr << "error" << std::endl;
}

void Execution::mapInit()
{
	this->mapedCommands[push] = &Execution::_push;
	this->mapedCommands[pop] = &Execution::_pop;
	this->mapedCommands[dump] = &Execution::_dump;
	this->mapedCommands[assert] = &Execution::_assert;
	// this->mapedCommands[add] = &Execution::_add;
	// this->mapedCommands[sub] = &Execution::_sub;
	// this->mapedCommands[mul] = &Execution::_mul;
	// this->mapedCommands[_div] = &Execution::__div;
	// this->mapedCommands[mod] = &Execution::_mod;
	// this->mapedCommands[print] = &Execution::_print;
	// this->mapedCommands[_exit] = &Execution::__exit;
}

void Execution::fullExec()
{
	int len = this->commands.size();
	std::cout << len << std::endl;

	this->mapInit();
	for (i = 0; i < len; i++)
	{
		e_commands cmd = this->commands[i].command;
		auto it = this->mapedCommands.find(cmd);
		if (it != this->mapedCommands.end())
			(this->*(it->second))();
	}
}
