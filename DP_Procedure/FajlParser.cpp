#include "FajlParser.h"

FajlParser::FajlParser(std::string putanja) :_ulazniFajl(putanja)
{}

FajlParser::~FajlParser()
{
}

std::string FajlParser::sledecaLinija()
{
    return "ja sam fajl";
}

bool FajlParser::spreman()
{
    return true;
}

void FajlParser::parsiraj()
{

}