#include "Loger.h"
#include <ctime>
#include <sstream>
Loger::Loger(std::string putanja, std::string aktivnost) :_pisac(putanja)
{
    _pisac << "[" << Loger::vremeSada() << "]: "<<aktivnost<< std::endl;
}

Loger::~Loger()
{
    _pisac.close();
}

std::string Loger::vremeSada()
{
    time_t rawnow = time(0);
    struct tm now;
    localtime_s(&now, &rawnow);
    std::stringstream ss;
    ss << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << " " << now.tm_mday << "/" << now.tm_mon + 1 << "/" << now.tm_year + 1900;
    return ss.str();
}

void Loger::operator<<(std::string poruka)
{
    _pisac << "[" << Loger::vremeSada() << " - ";
    switch (poruka.at(0))
    {
    case '?':
        poruka = poruka.substr(1);
        _pisac << "Upozorenje";
        break;
    case '!':
        poruka = poruka.substr(1);
        _pisac << "GRESKA";
        break;
    default:
        _pisac << "Informacija";
        break;
    }
    _pisac << "]: ";
    _pisac << poruka << std::endl;
}
