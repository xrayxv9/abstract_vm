#include "absract.h"
#include <vector>
#include <exception>
class FileHandle{
	public:
		FileHandle();
		FileHandle(int ac, char **av);
		~FileHandle();

		void readIn();

		class InvalidCreation : public std::exception
		{
			public: 
				virtual const char *what() const throw();
		};
	private:
		int		ac;
		int		fd;
		std::vector<std::string> fullFile;
};
