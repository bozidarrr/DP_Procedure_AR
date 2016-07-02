#include "ClauseList.h"

ClauseList::ClauseList()
{}

ClauseList::ClauseList(std::set<Clause> clauses) : clauses(clauses)
{
}

void ClauseList::findAllLiterals()
{
	for (Clause c : clauses)
	{
		for (Literal l : c.getLiterals())
			literals.insert((l.isNegative()) ? l.getOpposite() : l);
	}
}

ClauseList::~ClauseList()
{
}

bool ClauseList::resolve()
{
	if (!preprocess())
		return  false;
	findAllLiterals();

	for (Literal l : literals)
	{
		if (clauses.empty())
			return true;

		if (!resolve(l))
			return false;
	}
	return clauses.empty();
}

bool ClauseList::resolve(const Literal & l)
{
	std::set<Clause> C1, C2;
	if (!partition(l, C1, C2))
		return true;

	for (auto c1 : C1)
		for (auto c2 : C2)
			if (!resolveClauses(l, c1, c2))
				return false;
	return true;
}

bool ClauseList::resolveClauses(const Literal & l, const Clause & c1, const Clause & c2)
{
	Clause resolvent = Clause::resolve(l, c1, c2);
	if (resolvent.isContradiction())
	{
		return false;
	}
	if (!resolvent.isTautology())
		clauses.insert(resolvent);
	return true;
}

bool ClauseList::addClause(const Clause & c)
{
	auto it = clauses.find(c);
	if (it != clauses.end())
		return false;
	clauses.insert(c);
	return true;
}

bool ClauseList::removeClause(const Clause & c)
{
	auto it = clauses.find(c);
	if (it == clauses.end())
		return false;
	clauses.erase(it);
	return true;
}

bool ClauseList::preprocess()
{
	for (auto c : clauses)
	{
		if (c.isTautology())
			removeClause(c);
		if (c.isContradiction())
			return false;
	}
	return true;
}

bool ClauseList::partition(const Literal & l, std::set<Clause> & C1, std::set<Clause> & C2)
{
	std::set<Clause> tmp(clauses);
	for (auto c : clauses)
	{
		if (c.containsLiteral(l))
		{
			C1.insert(c);
			tmp.erase(tmp.find(c));
		}
		if (c.containsLiteral(l.getOpposite()))
		{
			C2.insert(c);
			tmp.erase(tmp.find(c));
		}
	}
	clauses = tmp;
	if (!C1.empty() && !C2.empty())
		return true;
	return false;
}

std::ostream &operator<<(std::ostream &output, const ClauseList & cl)
{
	output << "[ ";
	for (auto c : cl.clauses)
		output << c << " ";
	output << "]";
	return output;
}
