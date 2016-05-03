#pragma once
#include<string>
#include<fstream>
enum TipPoruke{ Info, Upozorenje, Greska};

class Loger
{
public:
    Loger(std::string putanja, std::string aktivnost = "Aktivnost zapoceta");
    ~Loger();

    template<typename T>
    Loger & operator<<(T &poruka)
    {
        _pisac << "[" << Loger::vremeSada() << " - ";
        switch (_trenTip)
        {
        case TipPoruke::Upozorenje:
            _pisac << "Upozorenje";
            break;
        case TipPoruke::Greska:
            _pisac << "GRESKA";
            break;
        default:
            _pisac << "Informacija";
            break;
        }
        _pisac << "]: ";
        _pisac << poruka<<std::endl;
        _trenTip = TipPoruke::Info;
        return *this;
    }

    Loger & operator << (TipPoruke tip)
    {
        _trenTip = tip;
        return *this;
    }

private:
    static std::string vremeSada();
    std::ofstream _pisac;
    TipPoruke _trenTip;
};