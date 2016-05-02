#include "Literal.h"


Literal::Literal(const std::string & var, const bool value) : var(var), value(value)
{
}

Literal::Literal(const Literal & literal) : var(literal.var), value(literal.value)
{
}

Literal::~Literal()
{
}

Literal& Literal::operator=(const Literal& other) 
{
	if (this != &other) 
	{ 
		var = other.var;
		value = other.value;
	}
	return *this;
}

Literal Literal::getOpposite() const
{
	return Literal(var, !value);
}
//verovatno nam i ne treba :) 
bool Literal::isPositive() const
{
	return value == true;
}

bool Literal::isNegative() const
{
	return !isPositive();
}

const std::string & Literal::getVariable() const
{
	return var;
}

bool Literal::isOppositeOf(const Literal & other) const
{
	return (var == other.var) && (value != other.value);
}

bool Literal::operator<(const Literal& other) const
{
	return (var < other.var) || (var == other.var && !value && other.value);
}
bool Literal::operator<=(const Literal& other) const
{
	return *this < other || *this == other;
}
bool Literal::operator>(const Literal& other) const
{
	return (var > other.var) || (var == other.var && value && !other.value);
}
bool Literal::operator>=(const Literal& other) const
{
	{
		return  *this > other || *this == other;
	}
}
bool Literal::operator==(const Literal& other) const
{
	{
		return var == other.var && value == other.value;
	}
}

std::ostream &operator<<(std::ostream &output, const Literal & l)
{
	if (!l.value)
		output << "~";
	output << l.var;
	return output;
}