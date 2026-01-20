#include "Factory.hpp"
#include <IOperand.hpp>
#include <Operand.hpp>
#include <absract.h>
#include <cstdint>

IOperand const * Factory::createInt8( std::string const & value ) const
{
	return new Operand<int8_t>(Int8, value);
}

IOperand const * Factory::createInt16( std::string const & value ) const
{
	return new Operand<int16_t>(Int16, value);
}

IOperand const * Factory::createInt32( std::string const & value ) const
{
	return new Operand<int32_t>(Int32, value);
}

IOperand const * Factory::createFloat( std::string const & value ) const
{
	return new Operand<float>(Float, value);
}

IOperand const * Factory::createDouble( std::string const & value ) const
{
	return new Operand<double>(Double, value);
}

IOperand const *Factory::createOperand( eOperandType type, std::string const & value ) const
{
	if (type == Int8)
		return this->createInt8(value);
	else if (type == Int16)
		return this->createInt16(value);
	else if (type == Int32)
		return this->createInt32(value);
	else if (type == Float)
		return this->createFloat(value);
	else
		return this->createDouble(value);
}
