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
	/* Primenjuje rezoluciju po l na celu listu
	    --> Izbacuju se sve klauze koje sadrze l ili njemu suprotan literal. Ubacuju se rezolvente. 
		Napomena: Tatutologije se ne ubacuju.	
	*/
	bool resolve(const Literal & l);
	/* Rezolucija po literalu l na c1 koja sadrzi l i c2 koja sadrzi suprotan literal.
		Vraca false ukoliko je dobijena prazna klauza, inace true.
	*/
	bool resolveClauses(const Literal & l, const Clause & c1, const Clause & c2);
	/* Pomocni metod koji izbacuje sve tautologicne klauze (koje sadrze suprotne literale) pre nego sto pocne sama procedura. 	
	   Vraca false ako naidje na praznu klauzu. */
	bool preprocess();
	/* Mozda i ne treba, eliminise sve ciste literale (koji se javljaju u jednoj polarnosti) 
	bool eliminatePureLiterals();*/
	/* Particionise klauze na dva skupa: 
		C1 su one koje sadrze literal l,
		C2 one koje sadrze suprotan
	  Sve se izbacuju iz tekuceg skupa klauza. */
	bool partition(const Literal & l, std::set<Clause> & C1, std::set<Clause> & C2);
	//void findPositiveLiterals();
	/* Pronalazi sve literale, ali uvek ih cuva kao pozitivne (prakticno pronalazi sve promenljive) */
	void findAllLiterals();

	/* tekuci skup klauza i skup literala (promenljivih) */
	std::set<Clause> clauses;
	//std::set<Literal> positiveLiterals;
	std::set<Literal> literals;
};