#include "date.h"


Date::Date() {

    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    day = date_u_short((now->tm_mday));
    month = date_u_short(now->tm_mon + 1);
    year = date_u_short(now->tm_year + 1900);
	hour = date_u_short(now->tm_hour);
    minute = date_u_short(now->tm_min);
}

Date::Date(string date) {
    typedef unsigned short date_u_short;
    vector<string> dateVector;
    dateVector = vectorString(date, "/");
    year = date_u_short(stoi(dateVector.at(0)));
    month = date_u_short(stoi(dateVector.at(1)));
    day = date_u_short(stoi(dateVector.at(2)));
    hour = date_u_short(stoi(dateVector.at(3)));
    minute = date_u_short(stoi(dateVector.at(4)));
}


Date::Date(unsigned year, unsigned short month, unsigned short day, unsigned short hour, unsigned short minute) : month(month), day(day) ,hour(hour),minute(minute){
    if(year<99)
        year+=2000;
    this->year=year;
    isValid();
}
Date::~Date() {

}

/*********************************
 * GET Methods
 ********************************/
unsigned short Date::getDay() const {

    return day;
}


unsigned short Date::getMonth() const {

    return month;
}

unsigned Date::getYear() const {

    return year;
}

unsigned short Date::getHour() const{

    return hour;
}
unsigned short Date::getMinute() const{

    return minute;
}

string Date::getDate() const {

    return to_string(year) + "/" + to_string(month) + "/" + to_string(day)+"/"+to_string(hour)+"/"+to_string(minute);
}

string Date::getDateWHour() const{
    string t="0";
    string tempMinute=to_string(minute);
    if(tempMinute.size()==1)
        t+=to_string(minute);
    else {
        t=to_string(minute);
    }
    return to_string(year) + "/" + to_string(month) + "/" + to_string(day)+",  "+to_string(hour)+":"+t;
}
/*********************************
 * SET Methods
 ********************************/

void Date::setDay(unsigned short day) {

    this->day = day;
}

void Date::setMonth(unsigned short month) {

    this->month = month;
}

void Date::setYear(unsigned year) {

    this->year = year;
}

void Date::setDate(unsigned year, unsigned short month, unsigned short day) {

    this->year = year; this->month = month; this->day = day;
}

/*********************************
 * Other methods
 ********************************/

//function to calculate total amount of days of a given month
unsigned total_days(unsigned year, unsigned short month) {

    if (month == 2) {
        return (year % 400 == 0 || year % 100 != 0) && (year % 4 == 0) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

//check if instance date is valid
bool Date::isValid() {

    if (month > 0 && month <= 12) {
        if (day > 0 && day <= total_days(year, month)) {
            if(hour<=23){
                if(minute<=59)
                    return true;
                else
                    throw DateInvalid("Invalid minutes: "+to_string(minute),year,month,day,hour,minute);
            }
            else
                throw DateInvalid("Invalid Hour: "+to_string(hour),year,month,day,hour,minute);
        }
        else
            throw DateInvalid("Invalid Day: "+to_string(day),year,month,day,hour,minute);
    }
    else
        throw DateInvalid("Invalid Month: "+to_string(month),year,month,day,hour,minute);
}


/*********************************
 * Show Date
 ********************************/

//prints date year/month/day
void Date::show() const {
    cout << to_string(year) + "/" + to_string(month) + "/" + to_string(day) << endl;
}

bool operator < (Date const& date1, Date const& data2) {

    if (date1.getYear() == data2.getYear()) {
        if (date1.getMonth() == data2.getMonth()) {
            if (date1.getDay() == data2.getDay()) {
                if(date1.getHour() == data2.getHour()){
                    return (date1.getMinute() < data2.getMinute());
                }
                else
                    return date1.getHour() < data2.getHour();

            }
            else {
                return date1.getDay() < data2.getDay();
            }
        }
        else
            return date1.getMonth() < data2.getMonth();
    }
    return (date1.getYear() < data2.getYear());
}


const int monthDays[12] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};


int countLeapYears(Date *d)
{
    unsigned years = d->getYear();
    if (d->getMonth() <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}

float operator - (Date  &dt1, Date  &dt2){

    float n1 = dt1.getYear()*365 + dt1.getDay();

    for (int i=0; i<dt1.getMonth() - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(&dt1);

    float n2 = dt2.getYear()*365 + dt2.getDay();
    for (int i=0; i<dt2.getMonth() - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(&dt2);

    float t = ((n1 - n2) * 24 * 60 + (dt1.getHour() - dt2.getHour()) * 60 + (dt1.getMinute() - dt2.getMinute()));
    return  t;
}

void Date::setHour(int hour){
    this->hour=hour;
}

Date operator + (Date date1, int days){
    int dias=(date1.getDay()+days);
    int mes = 0;
    if(dias/monthDays[date1.getMonth()-1]){
        mes=(date1.getMonth()+dias/monthDays[date1.getMonth()-1]);
        date1.setDay(dias%monthDays[date1.getMonth()-1]);
    }
    else{
        date1.setDay(dias);
    }
    if(mes/12){
        date1.setYear(date1.getYear()+mes/12);
        date1.setMonth(mes%12+1);
    }
    else{
        date1.setMonth(mes);
    }
    if(date1.getDay()==0)
        date1.setDay(1);
    if(date1.getMonth()==0)
        date1.setMonth(1);
    cout<<"mes :"<<date1.getMonth()<<endl;
    cout<<"dia :"<<date1.getDay()<<endl;
    return  date1;
}
