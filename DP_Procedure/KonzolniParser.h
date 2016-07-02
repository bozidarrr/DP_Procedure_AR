#pragma once
#include "Parser.h"

/**
Klasa koja omogucava parsiranje klauzi zadatih na standardnom ulazu
Sledece pretpostavke se uzimaju za unos
- svaka klauza je u posebnoj liniji fajla
- literali u okviru jedne klauze su razdvojeni zapetama
- literali koji imaju prefiks '!' smatraju se negacijama literala
- sve beline u fajlu se ignorisu
- da bi korisnik uneo praznu klauzu, potrebno je da unese karakter @
- unos se smatra zavrsenim, kada se unese karakter #
*/
class KonzolniParser : public Parser
{
public:
	KonzolniParser();
	~KonzolniParser();
	bool spreman();
	std::set<Clause> parsiraj();
private:
	std::pair<Clause, bool> sledecaKlauza();
};
