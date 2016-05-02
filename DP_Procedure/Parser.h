#pragma once
#include<string>
class Parser
{
public:
    virtual std::string sledecaLinija() = 0;
    virtual bool spreman() = 0;
    virtual void parsiraj() = 0;
};

