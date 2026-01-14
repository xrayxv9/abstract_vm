#pragma once

#include "absract.h"
#include <stack>
#include <vector>

class Execution
{
	public:
		Execution();
		Execution( std::vector<t_command> & );
		Execution( const Execution & );
		Execution &operator=( const Execution & );
		~Execution();

		std::stack<long long int> getStack() const;
		std::vector<t_command> getCommands() const;
	private:
		std::vector<t_command> commands;
		std::stack<long long int> s;
};
