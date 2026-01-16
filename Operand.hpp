#pragma once
#include "IOperand.hpp"
#include <absract.h>
#include <cmath>
#include <string>

template <typename T>
class Operand: public IOperand
{
	public:
		Operand(eOperandType type, std::string str) : type(type), value(str), number(std::stod(str)){}

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
		IOperand const * operator-( IOperand const & rhs ) const; // Difference
		IOperand const * operator*( IOperand const & rhs ) const; // Product
		IOperand const * operator/( IOperand const & rhs ) const; // Quotient
		IOperand const * operator%( IOperand const & rhs ) const; // Modulo
		std::string const & toString( void ) const; // String representation of the instance
		~Operand( void ) {}

	private:
		IOperand const  calcul(char c, IOperand const & rhs) const
		{
			eOperandType type = this->type > rhs.getType()? this->type : rhs.getType();
			long double overflow = std::pow(2, sizeof(type) - 1) - 1;
			long double underflow = std::pow(2, sizeof(type) - 1);
			long double res;

			switch (c) {
				plus:
					res = static_cast<long double>(this->number) + std::stod(rhs.toString());
					break ;
				minus:
					
			
			}
			if (res >= overflow)
				;
			return new Operand(type, std::to_string(res));
		}

		eOperandType type;
		std::string value;
		long double number;
};
