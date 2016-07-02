#pragma once
#include <fstream>
#include "Parser.h"
#include "Loger.h"

/**
Klasa koja omogucava parsiranje klauzi iz datog fajla
Sledece pretpostavke se uzimaju za ulazni fajl:
- svaka klauza je u posebnoj liniji fajla
- literali u okviru jedne klauze su razdvojeni zapetama
- literali koji imaju prefiks '!' smatraju se negacijama literala
- sve beline u fajlu se ignorisu
*/
class FajlParser : public Parser
{
public:
	/**
	Kreira parser za fajl na zadatoj putanji
	*/
	FajlParser(std::string putanja);

	/**
	Unistava parser i zatvara fajl
	*/
	~FajlParser();

	/**
	Vraca vrednost 'true' ako je parser spreman za rad; 'false' u suprotnom
	*/
	bool spreman();

	/**
	Metod koji vraca skup klauzi, izvucenih na osnovu datog ulaznog fajla.
	*/
	std::set<Clause> parsiraj();
private:
	/**
	Metod koji vraca sledecu klauzu iz fajla kao prvi clan para.
	Drugi clan ima vrednost 'false', ukoliko u fajlu ne postoji sledeca klauza. U tom slucaju treba ignorisati prvi parametar
	*/
	std::pair<Clause, bool> sledecaKlauza();

	std::fstream _ulazniFajl;

	Loger _dnevnik;
};
