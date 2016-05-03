#pragma once
#include <set>
//#include <algorithm>
#include "Literal.h"
#include <iostream>
class Clause
	//:	public std::set<std::string>
{
public:
	Clause();
	Clause(std::set<Literal> literals);
	Clause(const Clause & c);
	~Clause();
	/*Operatori poredjenja, potrebni su da bi se koristili skupovi*/
	Clause& operator=(const Clause& other);
	bool operator<(const Clause& other) const;
	bool operator<=(const Clause& other) const;
	bool operator>(const Clause& other) const;
	bool operator>=(const Clause& other) const;
	bool operator==(const Clause& other) const;
	std::set<Literal> getPostiveLiterals() const;
	bool addLiteral(const Literal & l);
	bool removeLiteral(const Literal & l);
	/* Primenjuje binarnu rezoluciju na klauze c1 i c2 po literalu l, podrazumeva se da c1 sadrzi l, a c2 !l */
	static Clause resolve(const Literal & l, const Clause & c1, const Clause & c2);
	bool isTautology() const;
	bool isContradiction() const;
	bool containsLiteral(const Literal & l) const;
	const std::set<Literal> & getLiterals() const;
	friend std::ostream &operator<<(std::ostream &output, const Clause & c);
private:
	std::set<Literal> literals;
};