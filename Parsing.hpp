#include "absract.h"
#include <cstddef>
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
		std::string handleComments( std::string & );
		int	handleFirstHalf( std::string &, int, t_command * );
		int handleSecondHalf( std::string &, int, t_command *);
		size_t findSplit( std::string &, size_t & );
		size_t findSplitValue( std::string & );

		std::vector<t_command> commands;
		std::vector<std::string> file;
		std::map<std::string, int> matchCommand;
		std::map<std::string, int> matchValue;
		std::vector<std::string> errors;
		int inputType;
		bool error;
};
