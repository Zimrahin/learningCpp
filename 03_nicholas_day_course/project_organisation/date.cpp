#include "date.h"

// Constructor
date::date(int day, int month, int year) {
    set_date(day, month, year);
}

// Setter function implementation
void date::set_date(int d, int m, int y) {
    day   = d;
    month = m;
    year  = y;
}

// Getter implementations
int date::get_day() const {
    return day;
}

int date::get_month() const {
    return month;
}

int date::get_year() const {
    return year;
}
