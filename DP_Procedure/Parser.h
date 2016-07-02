#pragma once
#include<string>
#include"Clause.h"
#include "Loger.h"
class Parser
{
public:
	virtual std::pair<Clause, bool> sledecaKlauza() = 0;
	virtual bool spreman() = 0;
	virtual std::set<Clause> parsiraj() = 0;
	std::string trim(const std::string& str, const std::string& whitespace = " \t");
};
