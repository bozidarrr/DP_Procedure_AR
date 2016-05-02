#pragma once
#include<fstream>
#include "Parser.h"
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
};

