#pragma once
#include <set>
#include "Literal.h"
#include <iostream>

/**
Klasa koja omogucava predstavljanje klauze kao skupa literala.
Sadrzi metod za primenu binarne rezolucije po odredjenom literalu.
*/

class Clause
{
public:
	Clause();
	Clause(std::set<Literal> literals);
	Clause(const Clause & c);
	~Clause();
	/**
		Operatori poredjenja koji su potrebni da bi se koristila struktura set<Clause>
		*/
	Clause& operator=(const Clause& other);
	bool operator<(const Clause& other) const;
	bool operator<=(const Clause& other) const;
	bool operator>(const Clause& other) const;
	bool operator>=(const Clause& other) const;
	bool operator==(const Clause& other) const;
	std::set<Literal> getPostiveLiterals() const;
	bool addLiteral(const Literal & l);
	bool removeLiteral(const Literal & l);
	/**
		Metod primenjuje binarnu rezoluciju na klauze c1 i c2 po literalu l.
		Pri tom se podrazumeva da klauza c1 sadrzi literal l, a klauza c2 njemu suprtoan literal.
		Metod vraca rezolventu.
		C1 \/ I     C2 \/ !I
		--------------------
		C1 \/ C2
		*/
	static Clause resolve(const Literal & l, const Clause & c1, const Clause & c2);
	/**
		Metod vraca vrednost 'true' ako je u pitanju tautologicna klauza (sadrzi medjusobno suprotne literale), inace vrednost 'false'.
		*/
	bool isTautology() const;
	/**
		Metod vraca vrednost 'true' ako je u pitanju kontradikcija, odnostno prazna klauza, inace vrednost 'false'.
		*/
	bool isContradiction() const;
	bool containsLiteral(const Literal & l) const;
	const std::set<Literal> & getLiterals() const;
	friend std::ostream &operator<<(std::ostream &output, const Clause & c);
private:
	std::set<Literal> literals;
};