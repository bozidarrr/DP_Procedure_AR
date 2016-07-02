#pragma once
#include <string>
#include <ostream>
#include <set>
#include <map>

/**
Klasa koja omogucava predstavljanje literala.
Literal je predstavljen promenljivom tipa string i poloranoscu tipa bool.
Negacija se predstavlja prefiksom '!'.
*/

class Literal
{
public:
	/**
		Mapa koja omogucava brzu pretragu postojanja koda za literal sa datim imenom
		Ime literala se preslikava u par koji cine njegov kod (koji je sacuvan u samoj instanci)
		i broj pojavljivanja tog literala
	*/
	static std::map<std::string, std::pair<unsigned char, unsigned int> > s_NamesDictionary;

	/**
		Mapa koja omogucava brzo pronalazenje imena literala, na osnovu njegovog koda
	*/
	static std::map <unsigned char, std::string> s_variablesDictionary;

	/**
		Sledeci kod koji ce biti upotrebljen pri kreiranju instance.
	*/
	static unsigned char s_nextCode;

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
		Metod vraca ime literala, na osnovu podataka iz staticke mape.
	*/
	std::string getName() const;
	
	/**
		Metod vraca kod datog literala.
	*/
	unsigned char getCode() const;

	/**
		Metod koji vraca istinitosnu vrednost datog literala
	*/
	bool getValue() const;

	/**
		Metod vraca vrednost 'true' ako je u pitanju pozitivan literal, a vrednost 'false' ako je negativan.
	*/
	bool isPositive() const;
	
	/**
		Metod vraca vrednost 'false' ako je u pitanju pozitivan literal, a vrednost 'true' ako je negativan.
	*/
	bool isNegative() const;
	
	/**
		Metod vraca vrednost 'true' ukoliko je trenutni literal suprotan datom, inace 'false'.
	*/
	bool isOppositeOf(const Literal & other) const;

	/**
	Metod vraca suprotan literal.
	*/
	Literal getOpposite() const;

	/**
		Metod koji sluzi za ispis datog literala.
	*/
	friend std::ostream &operator<<(std::ostream &output, const Literal & l);

private:
	unsigned char _code;
	bool _value;
};
