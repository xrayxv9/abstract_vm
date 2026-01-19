#pragma once

#include "absract.h"
#include <Operand.hpp>
#include <cstdint>
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

		std::stack<Operand<eOperandType>*> getStack() const;
		std::vector<t_command> getCommands() const;
	private:
		void fatalError();

		std::vector<t_command> commands;
		std::stack<Operand<eOperandType> *> s;
};
