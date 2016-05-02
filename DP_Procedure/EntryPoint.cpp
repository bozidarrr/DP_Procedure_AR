#include<iostream>
#include "Literal.h"
#include "Clause.h"
#include "ClauseList.h"
int main()
{
	//int test;
	//std::cout << "TEST";
	//std::cin >> test;
	Literal tmp("aida", true);
	Literal tmp2 = tmp.getOpposite();
	Clause c1, c2;
	c1.addLiteral(tmp);
	c2.addLiteral(tmp2);
	c2.addLiteral(Literal("x", false));
	c2.addLiteral(Literal("z", true));
	c1.addLiteral(Literal("z", false));
	ClauseList cl;
	cl.addClause(c1);
	cl.addClause(c2);
	std::cout << cl << std::endl;

	int test;
	//std::cout << "TEST";
	//std::cin >> test;
	bool t = cl.resolve();
	std::cout << cl << std::endl;
}