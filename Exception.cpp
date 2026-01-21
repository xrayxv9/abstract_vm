#include "Exception.hpp"

RuntimeError::RuntimeError(): msg("") {}
RuntimeError::RuntimeError( const std::string &msg ): msg(msg) {}
RuntimeError::RuntimeError( const RuntimeError &src )
{
	*this = src;
}
RuntimeError &RuntimeError::operator=( const RuntimeError &src )
{
	if (this != &src)
		this->msg = src.getMsg();
	return *this;
}

RuntimeError::~RuntimeError() {}

const std::string &RuntimeError::getMsg() const
{
	return this->msg;
}

const char *RuntimeError::what() const noexcept
{
	return (msg.c_str());
}

ParsingError::ParsingError( const std::string &msg ): RuntimeError("Parsing Error" + msg) {}

LexerError::LexerError( const std::string &msg ): RuntimeError("Lexer Error" + msg) {}

NotEnoughPushedValues::NotEnoughPushedValues( const std::string &msg ): RuntimeError("Not enough values in the stack to do this opperation") {}

ExitTooSoon::ExitTooSoon( const std::string &msg ): RuntimeError("Exit Found before the end of every instructions") {}

WrongType::WrongType( const std::string &msg ): RuntimeError("Wrong type put as input") {}

PopOnEmptyStack::PopOnEmptyStack( const std::string &msg ): RuntimeError("You tried to pop on an empty stack") {}
