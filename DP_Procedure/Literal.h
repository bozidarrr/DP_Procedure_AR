#pragma once
#include <string>
#include <ostream>

/**
Klasa koja omogucava predstavljanje literala.
Literal je predstavljen promenljivom tipa string i poloranoscu tipa bool.
Negacija se predstavlja prefiksom '!'.
*/

class Literal
{
public:
	Literal(const std::string & var, const bool value);
	Literal(const Literal & literal);
	~Literal();
	/**
		Naredni operatori poredjenja su neophodni da bi se koristila struktura set<Literal>. 
	*/
	Literal& operator=(const Literal& other);
	bool operator<(const Literal& other) const;
	bool operator<=(const Literal& other) const;
	bool operator>(const Literal& other) const;
	bool operator>=(const Literal& other) const;
	bool operator==(const Literal& other) const;
	/**
		Metod vraca suprotan literal. 
	*/
	Literal getOpposite() const;
	/**
		Metod vraca vrednost 'true' ako je u pitanju pozitivan literal, a vrednost 'false' ako je negativan.
	*/
	bool isPositive() const;
	/**
	Metod vraca vrednost 'false' ako je u pitanju pozitivan literal, a vrednost 'true' ako je negativan.
	*/
	bool isNegative() const;
	bool isOppositeOf(const Literal & other) const;
	const std::string & getVariable() const;
	friend std::ostream &operator<<(std::ostream &output, const Literal & l);
private:
	std::string var;
	bool value;
};

