#pragma once

#include "absract.h"
#include <Factory.hpp>
#include <IOperand.hpp>
#include <Operand.hpp>
#include <cstdint>
#include <list>
#include <stack>
#include <vector>

class Execution
{
	public:
		Execution();
		Execution( const std::vector<t_command> & );
		Execution( const Execution & );
		Execution &operator=( const Execution & );
		~Execution();

		std::list<const IOperand *> getStack() const;
		std::vector<t_command> getCommands() const;
		void mapInit();
		void fullExec();
	private:
		void fatalError();

		void pushValue( const IOperand *op );

		void _push();
		void _pop();
		void _dump();
		void _assert();
		void _add();
		void _sub();
		// void _mul();
		// void __div();
		// void _mod();
		// void _print();
		// void __exit();

		Factory fact;
		std::vector<t_command> commands;
		std::list<const IOperand *> s;
		std::map<e_commands, void (Execution::*)(void)> mapedCommands;
		int i;
		const IOperand *rax;
};
