#include "Literal.h"
#include<iostream>
#include <algorithm>

unsigned char Literal::s_nextCode = 1;
std::map<std::string, std::pair<unsigned char, unsigned int> > Literal::s_NamesDictionary = std::map<std::string, std::pair<unsigned char, unsigned int> >();
std::map <unsigned char, std::string> Literal::s_variablesDictionary = std::map <unsigned char, std::string>();

Literal::Literal(const std::string & name, const bool value) : _value(value)
{
	if (s_NamesDictionary.find(name) == s_NamesDictionary.end())
	{
		_code = s_nextCode++;
		s_NamesDictionary[name] = std::make_pair(_code,1);
		s_variablesDictionary[_code] = name;
	}
	else
	{
		_code = s_NamesDictionary[name].first;
		s_NamesDictionary[name].second++;
	}
}

Literal::Literal(const Literal & literal) : Literal(literal.getName(), literal.getValue())
{}

Literal::~Literal()
{
	std::string name = getName();
	int count = --s_NamesDictionary[name].second;
	if (0 == count)
	{
		s_NamesDictionary.erase(name);
		s_variablesDictionary.erase(getCode());
	}
}

Literal& Literal::operator=(const Literal& other)
{
	if (this != &other)
	{
		_code = other.getCode();
		_value = other.getValue();
		std::string name = other.getName();
		s_NamesDictionary[name].second++;
	}

	return *this;
}

bool Literal::operator<(const Literal& other) const
{
	return getCode() < other.getCode() ||
		(
		getCode() == other.getCode() &&
		!getValue() && other.getValue()
		);
}

bool Literal::operator<=(const Literal& other) const
{
	return *this < other || *this == other;
}

bool Literal::operator>(const Literal& other) const
{
	return getCode() > other.getCode() ||
		(
		getCode() == other.getCode() &&
		getValue() && !other.getValue()
		);
}

bool Literal::operator>=(const Literal& other) const
{
	return  *this > other || *this == other;
}

bool Literal::operator==(const Literal& other) const
{
	return getCode() == other.getCode() && getValue() == other.getValue();
}

std::string Literal::getName() const
{
	return s_variablesDictionary[getCode()];
}

unsigned char Literal::getCode() const
{
	return _code;
}

bool Literal::getValue() const
{
	return _value;
}

Literal Literal::getOpposite() const
{
	return Literal(getName(), !getValue());
}

bool Literal::isPositive() const
{
	return getValue() == true;
}

bool Literal::isNegative() const
{
	return !isPositive();
}

bool Literal::isOppositeOf(const Literal & other) const
{
	return (getCode() == other.getCode()) && (getValue() != other.getValue());
}

std::ostream &operator<<(std::ostream &output, const Literal & l)
{
	if (!l.getValue())
		output << "!";
	output << l.getName();
	return output;
}
