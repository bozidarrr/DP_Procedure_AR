#pragma once
#include <string>
#include <ostream>
class Literal
{
public:
	Literal(const std::string & var, const bool value);
	Literal(const Literal & literal);
	~Literal();
	/* Operatori poredjenja su neophodni da bi se koristio skup. */
	Literal& operator=(const Literal& other);
	bool operator<(const Literal& other) const;
	bool operator<=(const Literal& other) const;
	bool operator>(const Literal& other) const;
	bool operator>=(const Literal& other) const;
	bool operator==(const Literal& other) const;
	/* Funkcije za suprotan literal, ispitivanje polarnosti. */
	Literal getOpposite() const;
	bool isPositive() const;
	bool isNegative() const;
	bool isOppositeOf(const Literal & other) const;
	const std::string & getVariable() const;
	friend std::ostream &operator<<(std::ostream &output, const Literal & l);
private:
	std::string var;
	bool value;
};

