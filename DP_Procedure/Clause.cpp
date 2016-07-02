#include "Clause.h"

Clause::Clause()
{
}

Clause::Clause(std::set<Literal> literals) : literals(literals)
{
}

Clause::Clause(const Clause & c) : literals(c.literals)
{
}

Clause::~Clause()
{
}

Clause& Clause::operator=(const Clause& other)
{
	if (this != &other)
		literals = other.literals;
	return *this;
}

bool Clause::operator<(const Clause& other) const
{
	return literals < other.literals;


}
bool Clause::operator<=(const Clause& other) const
{
	return literals <= other.literals;
}

bool Clause::operator>(const Clause& other) const
{
	return literals > other.literals;
}

bool Clause::operator>=(const Clause& other) const
{
	return literals >= other.literals;
}

bool Clause::operator==(const Clause& other) const
{
	return literals == other.literals;
}

std::set<Literal> Clause::getPostiveLiterals() const
{
	std::set<Literal> p;
	for (auto l : literals)
		if (l.isPositive())
			p.insert(l);
	return p;
}

bool Clause::addLiteral(const Literal & l)
{
	auto it = literals.find(l);
	if (it != literals.end())
		return false;
	literals.insert(l);
	return true;
}
bool Clause::removeLiteral(const Literal & l)
{
	auto it = literals.find(l);
	if (it == literals.end())
		return false;
	literals.erase(it);
	return true;
}

Clause Clause::resolve(const Literal & l, const Clause & c1, const Clause & c2)
{
	std::set<Literal> literals(c1.literals);
	literals.insert(c2.literals.begin(), c2.literals.end());
	Clause resolvent(literals);
	resolvent.removeLiteral(l);
	resolvent.removeLiteral(l.getOpposite());
	return resolvent;
}

bool Clause::isTautology() const
{
	if (literals.empty())
		return false;
	std::set<Literal> positive = getPostiveLiterals();
	for (auto l : positive)
		if (literals.find(l.getOpposite()) != literals.end())
			return true;
	return false;
}

bool Clause::isContradiction() const
{
	return literals.empty();
}

bool Clause::containsLiteral(const Literal & l) const
{
	return literals.find(l) != literals.end();
}

const std::set<Literal> & Clause::getLiterals() const
{
	return literals;
}

std::ostream &operator<<(std::ostream &output, const Clause & c)
{
	output << "[ ";
	for (auto l : c.literals)
		output << l << " ";
	output << "]";
	return output;
}