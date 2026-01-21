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

SegFault::SegFault( const std::string &msg ): RuntimeError(msg) {}
ParsingError::ParsingError( const std::string &msg ): RuntimeError("Parsing Error" + msg) {}
LexerError::LexerError( const std::string &msg ): RuntimeError("Lexer Error" + msg) {}
// InvalidInput::InvalidInput( const std::string &msg ): RuntimeError(msg) {}
