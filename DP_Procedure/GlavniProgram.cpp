#include<algorithm>
#include<iostream>
#include<sstream>
#include<string>
#include "Fajlparser.h"
#include "KonzolniParser.h"
#include "Loger.h"
#include "ClauseList.h"

/**
 Funkcija koja sluzi za ispitivanje da li korisnik zeli da nastavi sa radom
 Vraca tacno, ukoliko je odgovor 'da', netacno ukoliko je 'ne', beskonacno ponavljajuci petlju dok ne dobije jedan od ova dva odgovora
 */
bool daLiSteSigurni(const std::string & akcija)
{
	std::string odgovor;
	do
	{
		std::cout << "Da li zelite da " << akcija << "? da/ne?";
		std::cin >> odgovor;
		std::transform(odgovor.begin(), odgovor.end(), odgovor.begin(), ::tolower);
	} while (odgovor.compare("da") != 0 && odgovor.compare("ne") != 0);

	return odgovor.compare("da") == 0;
}

/**
 Funkcija koja ispituje da li fajl postoji na zadatoj putanji ili ne.
 */
bool fajlJeDostupan(const std::string & putanja)
{
	std::ifstream f(putanja.c_str());
	return f.good();
}

/**
 Glavna funkcija programa za demonstraciju DP procedure.
 U okviru nje, treba da bude odabran fajl sa ulaznim podacima,
 kao i inicirana procedura za njegovo parsiranje, rezoluciju klauzi
 i ispis i logovanje rezultata
 */
int main(int argc, char *argv[])
{
	Loger dnevnik("..\\DP_proc.log", "DP procedura zapoceta");
	std::cout << "Dobrodosli u program za demonstraciju DP procedure" << std::endl;
	Parser * parser;
	bool interaktivniMod = false;
	bool prosledjeniArgumenti = false;
	if (argc >= 2)
	{
		prosledjeniArgumenti = true;
	}

	if (!prosledjeniArgumenti)
	{
		dnevnik << TipPoruke::Upozorenje << "Nisu dati ulazni argumenti\n";
		if (daLiSteSigurni("navedete putanju do fajla u kojem se nalaze ulazni podaci"))
		{
			std::string putanja;
			std::cout << "Navedite putanju:" << std::endl;
			std::cin >> putanja;
			dnevnik << "Prosledjena putanja: " + putanja;
			if (!fajlJeDostupan(putanja))
			{
				dnevnik << TipPoruke::Greska << "Nije moguce pronaci ulazni fajl na datoj lokaciji";
				std::cout << "GRESKA: Nije moguce pronaci ulazni fajl na datoj lokaciji" << std::endl;
				system("Pause");
				exit(2);
			}
			parser = new FajlParser(putanja);
			dnevnik << "Kreiran fajl parser";
		}
		else // pretpostavljamo da korisnik zeli interaktivni mod
		{
			interaktivniMod = true;
			dnevnik << "Korisnik zeli interaktivni mod";
			parser = new KonzolniParser();
			dnevnik << "Kreiran konzolni parser";
		}
	}
	else
	{
		std::stringstream ss;
		ss << "Broj prosledjenih argumenata: ";
		ss << argc;
		ss << " , prvi argument: ";
		ss << argv[1];
		dnevnik << ss.str();
		if (!fajlJeDostupan(std::string(argv[1])))
		{
			dnevnik << TipPoruke::Greska << "Nije moguce pronaci ulazni fajl na datoj lokaciji";
			std::cout << "GRESKA: Nije moguce pronaci ulazni fajl na datoj lokaciji" << std::endl;
			exit(2);
		}
		parser = new FajlParser(argv[1]);
		dnevnik << "Kreiran parser za fajl";
	}

	ClauseList listaKlauza;
	if (parser->spreman())
	{
		dnevnik << "Parser je spreman, zapoceto parsiranje";
		listaKlauza = ClauseList(parser->parsiraj());
		delete parser;
		dnevnik << "Parsiranje zavrseno";
	}
	else
	{
		delete parser;
		dnevnik << TipPoruke::Greska << "Parser nije bio spreman. Program ce biti ugasen";
		exit(1);
	}

	dnevnik << "Ispis rezultata";

	if (interaktivniMod)
	{
		std::cout << "Prepoznata je lista klauza:" << std::endl << listaKlauza << std::endl;
	}

	bool zadovoljiva = listaKlauza.resolve();

	if (zadovoljiva)
	{
		std::cout << "Formula je ZADOVOLJIVA" << std::endl;
		dnevnik << "Formula je ZADOVOLJIVA";
	}
	else
	{
		std::cout << "Formula NIJE ZADOVOLJIVA" << std::endl;
		dnevnik << "Formula NIJE ZADOVOLJIVA";
	}

	std::cout << "Rad zavrsen" << std::endl;
	std::cout << "Log fajl sa medjukoracima i rezultatom, moguce je pronaci na lokaciji" << std::endl << dnevnik.lokacija() << std::endl;
	//system("Pause");
	dnevnik << "Rad zavrsen";
}
