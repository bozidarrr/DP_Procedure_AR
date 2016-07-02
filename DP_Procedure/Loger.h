#pragma once
#include<string>
#include<fstream>

/**
Nabrojivi tip koji sluzi za oznacavanje razlicitih tipova unosa u log fajl
*/
enum TipPoruke{ Info, Upozorenje, Greska };

/**
 Klasa koja omogucava ugodnije pisanje logova, formatirano tako da postoji informacija o vremenu svake aktivnosti.
 */
class Loger
{
public:
	/**
	Konstruktor klase loger koji je zaduzen za otvaranje log fajla i pisanje njegovog zaglavlja
	'putanja' - putanja do log fajla koji treba da bude kreiran
	'aktivnost' - opcionalni parametar, cija ce vrednost pisati u zaglavlju log fajla
	*/
	Loger(std::string putanja, std::string aktivnost = "Aktivnost zapoceta");

	/**
	Destruktor klase loger, koji je zaduzen za pravilo zatvaranje fajla, po RAII principu
	*/
	~Loger();

	/**
	Sablon metoda za upisivanje podatka u log fajl.
	Svaki podatak, bice upisan u log fajl sa prefiksom koji oznacava vreme unosa i tip zapisa.
	Tip zapisa se odredjuje na osnovu vrednosti privatnog clana podatka _trenTip
	*/
	template<typename T>
	Loger & operator<<(const T &poruka)
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
		_pisac << poruka << std::endl;
		_trenTip = TipPoruke::Info;
		return *this;
	}

	/**
	'Overloading' sablona za upis podataka.
	U slucaju da je tip podatka koji se 'upisuje u log' TipPoruke, menja se privatni clan podatak _tipPoruke, za sledeci unos u log fajl
	*/
	Loger & operator << (TipPoruke tip)
	{
		_trenTip = tip;
		return *this;
	}

	/**
	Vraca putanju do lokacije log fajla.
	*/
	std::string lokacija() const;

private:
	/**
	Metod koji vraca formatiranu nisku sa trenutnim vremenom
	*/
	static std::string vremeSada();

	std::string _lokacija;

	std::ofstream _pisac;

	TipPoruke _trenTip;
};
