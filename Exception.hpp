#pragma once

#include <exception>
#include <iostream>

class RuntimeError : public std::exception
{
	public:
		RuntimeError();
		RuntimeError( const std::string & );
		RuntimeError( const RuntimeError & );
		RuntimeError &operator=( const RuntimeError & );
		~RuntimeError();

		const char *what() const noexcept;
		const std::string &getMsg() const;
	private:
		std::string msg;
};

class SegFault : public RuntimeError
{
	public:
		SegFault( const std::string & );
};

class ParsingError: public RuntimeError
{
	public:
		ParsingError( const std::string & );
};

class LexerError: public RuntimeError
{
	public:
		LexerError( const std::string & );
};

// class segFault : public RuntimeError
// {
// 	public:
// 		segFault( const std::string & );
// };
