#include "KonzolniParser.h"
#include <sstream>
KonzolniParser::KonzolniParser(){}

KonzolniParser::~KonzolniParser(){}

std::pair<Clause, bool> KonzolniParser::sledecaKlauza()
{
	std::string linija = "";
	while (!std::cin.eof() && trim(linija).compare("") == 0)
	{
		std::cout << ">> ";
		std::getline(std::cin, linija);
	}

	linija = trim(linija);
	if (linija.compare("#") == 0)
	{
		return std::make_pair(Clause(), false);
	}
	else if (linija.compare("@") == 0)
	{
		std::cout << "Prepoznata prazna klauza" << std::endl;
		return std::make_pair(Clause(std::set<Literal>()), true);
	}

	std::stringstream ss(linija);
	std::string item;
	std::set<Literal> klauza;
	while (std::getline(ss, item, ',')) {
		item = trim(item);
		if (item[0] == '!')
		{
			item = item.substr(1);
			klauza.insert(Literal(item, false));
		}
		else
		{
			klauza.insert(Literal(item, true));
		}
	}
	std::cout << "Prepoznata klauza: " << klauza << std::endl;
	return std::make_pair(Clause(klauza), true);
}

bool KonzolniParser::spreman()
{
	return true;
}

std::set<Clause> KonzolniParser::parsiraj()
{
	std::cout << "Odabrali ste rad u interaktivnom modu." << std::endl;
	std::cout << "U svakoj liniji treba da se nalazi po jedna klauza" << std::endl;
	std::cout << "Elementi svake klauze treba da budu razdvojeni zarezima." << std::endl;
	std::cout << "Negacija se navodi kao '!' ispred date klauze" << std::endl;
	std::cout << "Ukoliko linija ne sadrzi nijedan literal, bice ignorisana" << std::endl;
	std::cout << "Da biste uneli praznu klauzu, unesite '@' i pritisnite taster ENTER" << std::endl;
	std::cout << "Za kraj unosa, unesite '#' i pritisnite taster enter" << std::endl;
	std::getline(std::cin, std::string());
	std::set<Clause> skupKlauza;

	std::pair<Clause, bool> parsedItem = sledecaKlauza();
	while (parsedItem.second)
	{
		skupKlauza.insert(parsedItem.first);
		parsedItem = sledecaKlauza();
	}
	return skupKlauza;
}
