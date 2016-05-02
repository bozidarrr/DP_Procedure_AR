#pragma once
#include <fstream>
#include "Parser.h"
#include "Loger.h"
class FajlParser : public Parser
{
public:
    FajlParser(std::string putanja);
    ~FajlParser();
    std::string sledecaLinija();
    bool spreman();
    void parsiraj();
private:
    std::fstream _ulazniFajl;
    Loger _dnevnik;
};