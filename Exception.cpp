#include "Exception.hpp"
#include <stdexcept>

RuntimeError::RuntimeError(): std::runtime_error("") {}
RuntimeError::RuntimeError( const std::string &msg ): std::runtime_error(""), msg(msg){}
RuntimeError::RuntimeError( const RuntimeError &src ): std::runtime_error(src.msg), msg(src.msg)
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

DivisionByZero::DivisionByZero( const std::string &msg ): RuntimeError("Error, Division by zero") {}

DivisionByNonInteger::DivisionByNonInteger( const std::string &msg ): RuntimeError("Division by non integer value is not possible on modulus") {}

OverflowUnderflow::OverflowUnderflow( const std::string &msg ): RuntimeError("Overflow or underflow detected") {}

AssertError::AssertError( const std::string &msg ): RuntimeError("Assertion Error") {}
