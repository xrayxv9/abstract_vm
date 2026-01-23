#include "Execution.hpp"
#include "Exception.hpp"
#include <Factory.hpp>
#include <IOperand.hpp>
#include <Operand.hpp>
#include <absract.h>
#include <list>
#include <string>

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
	bool toCrash = false;

	if (this->rax != nullptr)
		delete this->rax;

	while (!s.empty())
	{
		toCrash = true;
		const IOperand *tmp = s.front();
		this->s.pop_front();
		delete tmp;
	}
	if (toCrash)
		std::cerr << "[1]    44913 segmentation fault (core dumped)  ./avm" << std::endl;
}

void Execution::pushValue( const IOperand *op )
{
	this->s.push_front(op);
}

void Execution::_push()
{
	this->s.push_front(fact.createOperand(this->commands[this->i].io, this->commands[this->i].value));
}

void Execution::_pop()
{
	if (this->s.empty())
		throw PopOnEmptyStack("");
	if (this->rax != nullptr)
		delete this->rax;
	rax = this->s.front();
	this->s.pop_front();
}

void Execution::_dump()
{
	IOperand *tmp;

	for (auto it : s)
		std::cout << it << " " <<  it->toString() << std::endl;
}

void Execution::_assert()
{
	if (this->rax != nullptr)
		delete this->rax;
	this->_pop();
	if (this->rax->getType() == this->commands[i].io && this->rax->toString() == this->commands[i].value)
		this->_push();
	else
		throw AssertError("");
}

void Execution::_add()
{
	if (s.size() < 2)
		throw NotEnoughPushedValues("");
	_pop();
	const IOperand *tmp = this->rax;
	this->rax = nullptr;
	_pop();
	const IOperand *op = *tmp + *this->rax;
	this->pushValue(op);
	delete tmp;
	delete this->rax;
	this->rax = nullptr;
}

void Execution::_sub()
{
	if (s.size() < 2)
		throw NotEnoughPushedValues("");
	_pop();
	const IOperand *tmp = this->rax;
	this->rax = nullptr;
	_pop();
	const IOperand *op = *tmp - *this->rax;
	this->pushValue(op);
	delete tmp;
	delete this->rax;
	this->rax = nullptr;
}

void Execution::_mul()
{
	if (s.size() < 2)
		throw NotEnoughPushedValues("");
	_pop();
	const IOperand *tmp = this->rax;
	this->rax = nullptr;
	_pop();
	const IOperand *op = *tmp * *this->rax;
	this->pushValue(op);
	delete tmp;
	delete this->rax;
	this->rax = nullptr;
}

void Execution::__div()
{
	if (s.size() < 2)
		throw NotEnoughPushedValues("");
	_pop();
	const IOperand *tmp = this->rax;
	this->rax = nullptr;
	_pop();
	try {
		const IOperand *op = *tmp / *this->rax;
		this->pushValue(op);
		delete tmp;
		delete this->rax;
		this->rax = nullptr;
	}
	catch( RuntimeError &err ){
		delete tmp;
		throw err;
	}
}

void Execution::_mod()
{
	if (s.size() < 2)
		throw NotEnoughPushedValues("");
	_pop();
	const IOperand *tmp = this->rax;
	this->rax = nullptr;
	_pop();
	try{
		const IOperand *op = *tmp % *this->rax;
		this->pushValue(op);
		delete tmp;
		delete this->rax;
		this->rax = nullptr;
	}
	catch ( RuntimeError &err ){
		delete tmp;
		throw err;
	}
}

void Execution::_print()
{
	this->_pop();
	
	if (this->rax->getType() == Int8)
		std::cout << static_cast<char>(std::stoi(this->rax->toString())) << std::endl;
	else
		throw WrongType("");
	pushValue(this->rax);
	this->rax = nullptr;
}


void Execution::mapInit()
{
	this->mapedCommands[push] = &Execution::_push;
	this->mapedCommands[pop] = &Execution::_pop;
	this->mapedCommands[dump] = &Execution::_dump;
	this->mapedCommands[assert] = &Execution::_assert;
	this->mapedCommands[add] = &Execution::_add;
	this->mapedCommands[sub] = &Execution::_sub;
	this->mapedCommands[mul] = &Execution::_mul;
	this->mapedCommands[_div] = &Execution::__div;
	this->mapedCommands[mod] = &Execution::_mod;
	this->mapedCommands[print] = &Execution::_print;
}

void Execution::fullExec()
{
	int len = this->commands.size();

	this->mapInit();
	for (i = 0; i < len; i++)
	{
		e_commands cmd = this->commands[i].command;
		if (cmd == _exit)
			break ;
		auto it = this->mapedCommands.find(cmd);
		if (it != this->mapedCommands.end())
			(this->*(it->second))();
	}
	if (this->i + 1 != commands.size())
		throw ExitTooSoon("");
}
