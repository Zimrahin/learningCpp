#include <iostream>
#include "date.h"

int main() {
    date my_date(19, 03, 2025);
    std::cout << "Day: " << my_date.get_day() << std::endl;
    std::cout << "Month: " << my_date.get_month() << std::endl;
    std::cout << "Year: " << my_date.get_year() << std::endl;
    return 0;
}
