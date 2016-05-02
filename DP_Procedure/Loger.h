#pragma once
#include<string>
#include<fstream>
enum TipPoruke{ Info, Upozorenje, Greska};

class Loger
{
public:
    Loger(std::string putanja = "C:\\Windows\\Temp\\DP_Procedure.log");
    ~Loger();
    static std::string vremeSada();
    void operator<<(std::string poruka);

private:
    std::ofstream _pisac;
};