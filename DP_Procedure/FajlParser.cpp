#include "FajlParser.h"
#include<sstream>

FajlParser::FajlParser(std::string putanja) :_ulazniFajl(putanja), _dnevnik("..\\FajlParser.log", "FajlParser kreiran")
{}

FajlParser::~FajlParser()
{
	_dnevnik << "Fajl parser unisten";
}

std::pair<Clause, bool> FajlParser::sledecaKlauza()
{
	std::string linija;
	while (!_ulazniFajl.eof())
	{
		std::getline(_ulazniFajl, linija);
		if (_ulazniFajl.eof() || linija[0] != ';')
			break;
	}
	if (_ulazniFajl.eof())
	{
		_dnevnik << TipPoruke::Upozorenje << "Kraj fajla dostignut";
		return std::make_pair(Clause(), false);
	}
	_dnevnik << "Procitana linija: " + linija;
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

	_dnevnik << "Parsiranje linije zavrseno";
	return std::make_pair(Clause(klauza), true);
}

bool FajlParser::spreman()
{
	if (_ulazniFajl.good())
	{
		_dnevnik << "Parser je spreman";
		return true;
	}

	_dnevnik << TipPoruke::Greska << "Parser nije spreman";
	return false;
}

std::set<Clause> FajlParser::parsiraj()
{
	_dnevnik << "Parsiranje zapoceto";
	std::set<Clause> skupKlauza;

	std::pair<Clause, bool> parsedItem = sledecaKlauza();
	while (parsedItem.second)
	{
		_dnevnik << "Klauza procitana:" << parsedItem.first;
		skupKlauza.insert(parsedItem.first);
		parsedItem = sledecaKlauza();
	}
	_dnevnik << "Parsiranje zavrseno";
	return skupKlauza;
}
