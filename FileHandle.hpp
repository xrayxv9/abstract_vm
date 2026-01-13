#include "absract.h"

class FileHandle{
	public:
		FileHandle();
		FileHandle( int, char ** );
		FileHandle( const FileHandle & );
		~FileHandle();
		FileHandle &operator=( const FileHandle & );
		void readIn();
		void readFile( char * );

		class InvalidCreation : public std::exception
		{
			public: 
				virtual const char *what() const throw();
		};

		std::vector<std::string>getVec() const;
		int getType() const;
	private:
		int entryType;
		std::vector<std::string> fullFile;
};
