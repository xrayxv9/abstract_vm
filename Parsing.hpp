#include "absract.h"
#include <map>
#include <string>

class Parsing
{
	public:
		Parsing();
		Parsing( std::vector<std::string>, int );
		Parsing( const Parsing & );
		Parsing &operator=( const Parsing & );
		~Parsing();

		void parseFile();

	private:
		class InvalidInput: public std::exception
		{
			public: 
				virtual const char *what() const throw();
		};

		void parseLine( int );
		void initMatch();

		std::vector<t_command> commands;
		std::vector<std::string> file;
		std::map<std::string, int> matchCommand;
		std::map<std::string, int> matchValue;
		std::vector<std::string> errors;
		int inputType;
		bool error;
};
