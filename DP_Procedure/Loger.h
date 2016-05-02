#pragma once
#include<string>
#include<fstream>
enum TipPoruke{ Info, Upozorenje, Greska};

class Loger
{
public:
    Loger(std::string putanja, std::string aktivnost = "Aktivnost zapoceta");
    ~Loger();
    static std::string vremeSada();
    void operator<<(std::string poruka);

private:
    std::ofstream _pisac;
};