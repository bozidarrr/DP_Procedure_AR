#pragma once
#include "Clause.h"
#include <set>
#include <iostream>

/**
Klasa koja omogucava predstavljanje formule u KNF kao skupa klauza.
Glavna funkcionalnost je ispitivanje zadovoljivosti date formule, iscrpnom primenom rezolucije po svim promenljivim i na sve klauze.
*/

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
	/**
		Primenjuje rezoluciju po l na celu listu
		--> Izbacuju se sve klauze koje sadrze l ili njemu suprotan literal. Ubacuju se rezolvente.
		Napomena: Tatutologicne klauze se ne ubacuju.
		*/
	bool resolve(const Literal & l);

	/**
		Rezolucija po literalu l na klauze c1 i c2.
		Pretpostavka je da klauza c1 sadrzi l i klauza c2 sadrzi njemu suprotan literal.
		Metod vraca vrednost 'false' ukoliko je dobijena prazna klauza, inace vrednost 'true'.
		*/
	bool resolveClauses(const Literal & l, const Clause & c1, const Clause & c2);

	/**
		Metod izbacuje sve tautologicne klauze iz liste klauza (one koje sadrze medjusobno suprotne literale).
		Metod vraca vrednost 'false' ukoliko naidje na praznu klauzu, a inace vrednost 'true'.
		*/
	bool preprocess();

	/**
		Particionise listu klauza na sledeci nacin:
		- C1 sadrzi sve klauze koje sadrze literal l;
		- C2 sadrzi sve klauze koje sadrze literal suprotan l;
		Pri tome u tekucem skupu klauza ostaju samo one klauze koje ne sadrze ni l ni !l.
		*/
	bool partition(const Literal & l, std::set<Clause> & C1, std::set<Clause> & C2);

	/**
		Pronalazi sve promenljive koje se javljaju u formuli.
		Tacnije pronalaze se svi literali, ali uvek se cuvaju kao pozitivni radi dalje upotrebe.
		*/
	void findAllLiterals();

	/* Tekuci skup klauza i skup svih promenljivih */
	std::set<Clause> clauses;
	std::set<Literal> literals;
};
