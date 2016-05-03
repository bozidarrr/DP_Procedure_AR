#pragma once
#include <fstream>
#include "Parser.h"
#include "Loger.h"
class FajlParser : public Parser
{
public:
    FajlParser(std::string putanja);
    ~FajlParser();
    bool spreman();
    std::set<Clause> parsiraj();
private:
    std::pair<Clause,bool> sledecaKlauza();
    std::fstream _ulazniFajl;
    Loger _dnevnik;
};