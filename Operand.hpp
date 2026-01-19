#pragma once
#include "IOperand.hpp"
#include <absract.h>
#include <cmath>
#include <cstdint>
#include <string>

template <typename T>
class Operand: public IOperand
{
	public:
		Operand( eOperandType type, std::string str ) : type(type), value(str), number(std::stod(str))
		{
			switch (typeid(T))
				case int8_t:
					this->type = Int8;
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
					res = static_cast<long double>(this->number) + std::stod(rhs.toString());
					break ;
				case minus:
					res = static_cast<long double>(this->number) - std::stod(rhs.toString());
					break; 
				case mul:
					res = static_cast<long double>(this->number) * std::stod(rhs.toString());
					break ;
				case modulus:
					res = std::fmod(static_cast<long double>(this->number), std::stod(rhs.toString()));
					break ;
				case divide:
					if (std::stod(rhs.toString()) != 0)
						res = static_cast<long double>(this->number) / std::stod(rhs.toString());
					else
						;
					// TODO put an error
					break ;
			}
			// std::numeric_limits<type>.max
			if (res >= overflow)
				;
			return new Operand(type, std::to_string(res));
		}
		eOperandType type;
		std::string value;
		long double number;
};
