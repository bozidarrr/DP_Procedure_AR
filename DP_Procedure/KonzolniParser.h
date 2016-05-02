#pragma once
#include "Parser.h"
class KonzolniParser :
    public Parser
{
public:
    KonzolniParser();
    ~KonzolniParser();
    std::string sledecaLinija();
    bool spreman();
    void parsiraj();
};

