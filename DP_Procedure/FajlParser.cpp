#include "FajlParser.h"

FajlParser::FajlParser(std::string putanja) :_ulazniFajl(putanja), _dnevnik("..\\FajlParser.log", "FajlParser kreiran")
{}

FajlParser::~FajlParser()
{
    _dnevnik << "Fajl parser unisten";
}

std::string FajlParser::sledecaLinija()
{
    _dnevnik << "Sledeca linija trazena";
    return "ja sam fajl";
}

bool FajlParser::spreman()
{
    _dnevnik << "Parser je spreman";
    return true;
}

void FajlParser::parsiraj()
{
    _dnevnik << "Parsiranje zapoceto";
    _dnevnik << "Parsiranje zavrseno";
}