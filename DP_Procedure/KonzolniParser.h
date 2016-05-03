#pragma once
#include "Parser.h"
class KonzolniParser :
    public Parser
{
public:
    KonzolniParser();
    ~KonzolniParser();
    std::pair<Clause,bool> sledecaKlauza();
    bool spreman();
    std::set<Clause> parsiraj();
};

