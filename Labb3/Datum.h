//Kasper Rosenberg - karo5568
// Labb3, Datum.h – klassdefinition

#ifndef DATUM_H
#define DATUM_H

#include <array>
#include <iostream>
#include <stdexcept>


class Datum
{
	friend std::ostream& operator<<(std::ostream&, const Datum&);

	unsigned int year;
	unsigned int month;
	unsigned int day;

	// Deklaration av statisk privat medlem, "ant_dagar per månad"
	static const std::array< unsigned int, 13 > ANT_DAGAR_PER_MAANAD;
	static const std::array<std::string, 13> MANADER;
	//void step_one_day(); // Öka datum med en dag

public:
	Datum();
	Datum(const Datum& date);
	Datum(int, int, int);
	void set_date(int, int, int); // set year, month, day

	//OBS. funktionen "step_one_day()" bör vara PRIVATE
	void step_one_day(); // Öka datum med en dag
	static bool is_skott_aar(int); // Är det skottår?
	bool end_of_month(int) const; // Är dagen den sista i månaden?

	//Operatorer
	const Datum& operator+=(const int& daysToAdd);
	const Datum operator+(const int& daysToAdd) const;
	const Datum& operator++();
	const Datum operator++(int);

private: 
	friend bool operator<(const Datum& dat1, const Datum& dat2);
};
//Operatorer
bool operator<(const Datum& dat1, const Datum& dat2);
bool operator<=(const Datum& dat1, const Datum& dat2);
bool operator>=(const Datum& dat1, const Datum& dat2);

inline const Datum operator+(const int& daysToAdd, const Datum& date) {
	Datum tmp(date);
	tmp += daysToAdd;
	return tmp;
}

inline bool operator>(const Datum& dat1, const Datum& dat2) {
	return dat2 < dat1;
}

inline bool operator==(const Datum& dat1, const Datum& dat2) {
	return !(dat1 < dat2) && !(dat2 < dat1);
}

inline bool operator!=(const Datum& dat1, const Datum& dat2) {
	return !(dat1 == dat2);
}
#endif

