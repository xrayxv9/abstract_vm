#pragma once
#include "IOperand.hpp"
#include <Exception.hpp>
#include <absract.h>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string>

template <typename T>
class Operand: public IOperand
{
	public:
		Operand( eOperandType type, std::string str )
		{
			this->type = type;
			this->value = str;
			if (this->type != Int8 || this->type != Int16 || this->type != Int32)
				this->number = static_cast<T>(std::stoi(this->value));
			else if (this->type == Double)
				this->number = static_cast<T>(std::stod(this->value));
			else
				this->number = static_cast<T>(std::stof(this->value));
				
		}
		Operand() {/*throw*/};
		Operand &operator=( const Operand<eOperandType> &src )
		{
				
			if (this != &src)
			{
				this->value = getValue();
				this->number = getNumber();
				this->type = getType();
			}
			return *this;
		}
		
		Operand( const Operand<eOperandType> &src )
		{
			*this = src;
		}
		~Operand() {}

		int getPrecision( void ) const
		{
			return sizeof(T) * 8;

		}
		eOperandType getType( void ) const
		{
			return this->type;
		}
		IOperand const * operator+( IOperand const & rhs ) const
		{
			return (this->calcul(plus, rhs));
		}
		IOperand const * operator-( IOperand const & rhs ) const
		{
			return (this->calcul(minus, rhs));
		}
		IOperand const * operator*( IOperand const & rhs ) const
		{
			return (this->calcul(mul, rhs));
		}
		IOperand const * operator/( IOperand const & rhs ) const
		{
			return (this->calcul(divide, rhs));
		}
		IOperand const * operator%( IOperand const & rhs ) const
		{
			return (this->calcul(modulus, rhs));
		}
		std::string const & toString( void ) const
		{
			return value;
		}

		std::string getValue() const
		{
			return this->value;
		}

		long double getNumber() const
		{
			return this->number;
		}
	private:
		IOperand const  *calcul(char c, IOperand const & rhs) const
		{
			eOperandType type = this->type > rhs.getType()? this->type : rhs.getType();
			long double overflow = std::pow(2, sizeof(type) - 1) - 1;
			long double underflow = std::pow(2, sizeof(type) - 1);
			long double res;

			switch (c) {
				case plus:
					res = std::stod(this->value) + std::stod(rhs.toString());
					break ;
				case minus:
					res = std::stod(this->value) - std::stod(rhs.toString());
					break; 
				case mul:
					res = std::stod(this->value) * std::stod(rhs.toString());
					break ;
				case modulus:
					if (rhs.toString() == "0")
						throw DivisionByZero("");
					if (rhs.getType() == Float || rhs.getType() == Double)
						throw DivisionByNonInteger("");
					res = std::fmod(std::stod(this->value), std::stod(rhs.toString()));
					break ;
				case divide:
					if (rhs.toString() == "0")
						throw DivisionByZero("");
					res = std::stod(this->value) / std::stod(rhs.toString());
			}
			switch (type) {
				case Int8:
					if (std::numeric_limits<int8_t>::min() > res || std::numeric_limits<int8_t>::max() < res)
						throw OverflowUnderflow("");
					return new Operand(type, std::to_string(static_cast<int8_t>(res)));
				case Int16:
					if (std::numeric_limits<int16_t>::min() > res || std::numeric_limits<int16_t>::max() < res)
						throw OverflowUnderflow("");
					return new Operand(type, std::to_string(static_cast<int16_t>(res)));
				case Int32:
					if (std::numeric_limits<int32_t>::min() > res || std::numeric_limits<int32_t>::max() < res)
						throw OverflowUnderflow("");
					return new Operand(type, std::to_string(static_cast<int32_t>(res)));
				case Float:
					if (std::numeric_limits<float>::min() > res || std::numeric_limits<float>::max() < res)
						throw OverflowUnderflow("");
					return new Operand(type, std::to_string(static_cast<float>(res)));
				case Double:
					if (std::numeric_limits<double>::min() > res || std::numeric_limits<double>::max() < res)
						throw OverflowUnderflow("");
					return new Operand(type, std::to_string(static_cast<double>(res)));
				default:
					return nullptr;
			}
		}
		eOperandType type;
		std::string value;
		long double number;
};
