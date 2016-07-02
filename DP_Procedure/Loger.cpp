#include "Loger.h"
#include <ctime>
#include <sstream>
Loger::Loger(std::string putanja, std::string aktivnost) :_lokacija(putanja), _pisac(putanja), _trenTip(TipPoruke::Info)
{
	_pisac << "[" << Loger::vremeSada() << "]: " << aktivnost << std::endl;
}

Loger::~Loger()
{
	_pisac.close();
}

std::string Loger::lokacija() const
{
	return _lokacija;
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
