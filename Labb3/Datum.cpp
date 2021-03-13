//Kasper Rosenberg - karo5568
// Labb3, Datum.cpp – definitioner av icke-triviala medlemsfunktioner

#include <iostream>
#include <string>
#include "Datum.h"
#include <stdexcept>

// Initialisera statisk medlem
// (första elementet används inte i denna lösning!)
const std::array< unsigned int, 13 > Datum::ANT_DAGAR_PER_MAANAD = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
const std::array<std::string, 13> MANADER = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };


// Konstruktor
Datum::Datum(): year(2000), month(1), day(1) {

}

Datum::Datum(const Datum& date) : year(date.year), month(date.month), day(date.day)
{
}

Datum::Datum(int year, int month, int day)
{
    set_date(year, month, day);
}

void Datum::set_date(int yy, int mm, int dd)
{
    // Glöm inte att kontrollera inmatade värden, annars "exception"
    try {
        if (yy < 2000 || yy > 2100) {
            throw std::invalid_argument("Året måste vara mellan >= 2000 och <= 2100");
        }
        if (mm < 1 || mm > 12) {
            throw std::invalid_argument("Månaden måste vara >= 1 och <= 12");
        }
        if (dd > ANT_DAGAR_PER_MAANAD[mm] || dd < 1) {
            if (is_skott_aar(yy) && mm == 2 && dd == 29) {
                year = yy;
                month = mm;
                day = dd;
                return;
            }
           else {
               throw std::invalid_argument("Dagen stämmer inte med år och månad");
            }
        }
        year = yy;
        month = mm;
        day = dd;
    }
        catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
}
// Denna medlemsfunktion är tänkt att lägga till 1 dag till befintligt datum.
// Om sista dagen i månaden, så byt månad.
//     Om skottår, så ta hänsyn till att februari(månad 2) har 29 dagar.
// Om sista dagen på året, så byt år.
void Datum::step_one_day()
{
    // Dagen är inte sista dagen i månaden!
    if (!end_of_month(day))
        ++day;
    else
        if (month < 12)
        {
            ++month;
            day = 1;
        }
        else
        {
            ++year;
            month = 1;
            day = 1;
        }
}

// Returnera true om yy(year) är skottår!
bool Datum::is_skott_aar(int yy)
{
    if (yy % 400 == 0 ||
        (yy % 100 != 0 && yy % 4 == 0))
        return true;
    else
        return false;
}

// Är det sista dagen (dd) i månaden?
bool Datum::end_of_month(int dd) const
{
    if (month == 2 && is_skott_aar(year))
        return dd == 29;
    else
        return dd == ANT_DAGAR_PER_MAANAD[month];
}

//Operatoröverlagringar
const Datum& Datum:: operator+=(const int& daysToAdd) {
    for (int i = 0; i < daysToAdd; i++) {
        step_one_day();
    }
    return *this;
}

const Datum Datum::operator+(const int& daysToAdd) const
{
    Datum tmp(*this);
    tmp += daysToAdd;
    return tmp;
}

//Prefix
const Datum& Datum::operator++()
{
    step_one_day();
    return *this;
}
//Postfix
const Datum Datum::operator++(int)
{
    Datum tmp(*this);
    step_one_day();
    return tmp;
}

bool operator<(const Datum& dat1, const Datum& dat2)
{
    if (dat1.year < dat2.year) {
        return true;
    }
    else if (dat1.year > dat2.year) {
        return false;
    }
    else {
        if (dat1.month < dat2.month) {
            return true;
        }
        else if (dat1.month > dat2.month) {
            return false;
        }
        else {
            if (dat1.day < dat2.day) {
                return true;
            }
            else if (dat1.day > dat2.day) {
                return false;
            }
            return false;
        }
    }
}

bool operator<=(const Datum& dat1, const Datum& dat2)
{
    return (dat1 < dat2) || (dat1 == dat2);
}

bool operator>=(const Datum& dat1, const Datum& dat2)
{
    return (dat1 > dat2) || (dat1 == dat2);
}

// operator<<
std::ostream& operator<<(std::ostream& output, const Datum& d)
{
    // OBS. Glöm inte att modifiera vad som skrivs ut!
    output << d.day << ' ' << MANADER[d.month] << ' ' << d.year;
    return output;

}



