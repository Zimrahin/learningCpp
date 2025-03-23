#ifndef DATE_H
#define DATE_H

class date {
  private:
    int year;
    int month;
    int day;

  public:
    date(int day, int month, int year);  // Constructor declaration
    void set_date(int d, int m, int y);  // Setter method to update the date

    // Getters marked as const (good practice)
    int get_day() const;
    int get_month() const;
    int get_year() const;
};

#endif  // DATE_H
