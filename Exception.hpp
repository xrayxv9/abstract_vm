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

class NotEnoughPushedValues : public RuntimeError
{
	public:
		NotEnoughPushedValues( const std::string & );
};

class ExitTooSoon : public RuntimeError
{
	public:
		ExitTooSoon( const std::string & );
};

class WrongType : public RuntimeError
{
	public:
		WrongType( const std::string & );
};

class PopOnEmptyStack : public RuntimeError
{
	public:
		PopOnEmptyStack( const std::string & );
};
