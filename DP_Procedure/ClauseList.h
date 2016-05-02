#pragma once
#include "Clause.h"
#include <set>
#include <iostream>
class ClauseList
{
public:
	ClauseList();
	ClauseList(std::set<Clause> clauses);
	~ClauseList();
	bool addClause(const Clause & c);
	bool removeClause(const Clause & c);
	bool resolve();
	friend std::ostream &operator<<(std::ostream &output, const ClauseList & cl);
private:
	bool resolve(const Literal & l);
	bool resolveClauses(const Literal & l, const Clause & c1, const Clause & c2);
	bool preprocess();
	bool eliminatePureLiterals();
	bool partition(const Literal & l, std::set<Clause> & C1, std::set<Clause> & C2);
	void findPositiveLiterals();
	std::set<Clause> clauses;
	std::set<Literal> positiveLiterals;
};

