	/*
    * @file
    * @brief Program to convert time Unix Timestamp to human readabe format.
    * @description 
        * Program takes input in seconds
        * Gives output in human readable format(Date/Month/Year Hour:Minute:Second).
        * Example : Input - 1354626750
                    Output - 4/12/2012 13:12:30
*/

#include <iostream>
using namespace std;

/*
    *Function to check if an year is a leap year or not.
*/
bool isLeapYear(int currYear) {
    if (currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0)) {
        return true;
    }else {
        return false;
    }
}

/*
    * Function to convert unix timestamp (in seconds)
    * to required format(Date/Month/Year Hour:Minute:Second).
*/
string unixTimeStampToHumanReadable(long int unixTime) {
    string ans = "";
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long int currYear,
        daysTillNow,
        extraTime,
        extraDays,
        index,
        date,
        month,
        hours,
        minutes,
        seconds,
        flag = 0;

    /*
    * adding 1 because daysTillNow will give days till previous day 
    * and we have to include current day for DATE and MONTH 
    */
    daysTillNow = (unixTime / (24 * 60 * 60)) + 1;

    extraTime = unixTime % (24 * 60 * 60);

    currYear = 1970; // year calculation will start from Epoch's year (1970)

    // calculating currrent year
    while ((daysTillNow > 365 && !isLeapYear(currYear)) || ((daysTillNow > 366 && isLeapYear(currYear)))) {
        if (isLeapYear(currYear)) { // checking if an year is a leap year
            daysTillNow -= 366;
        }else { // otherwise
            daysTillNow -= 365;
        }

        currYear += 1;
    }

    /* 
    * updating extradays
    * because daysTillNow is reduced till remaining days
    */
    extraDays = daysTillNow;

    if (isLeapYear(currYear)) {
        flag = 1;
    }

    // calculating MONTH and DATE
    month = 0, index = 0;
    
    // if it is a leap year
    if(flag == 1) {
        while(true){
            if(index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }else {
                if (extraDays - daysOfMonth[index] < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
                if (extraDays <= 0) {
                    break;
                }
            }
            index += 1;
        }
    }

    // if this is not a leap year
    else {
        while (true) {
            if (extraDays - daysOfMonth[index] < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            if (extraDays <= 0) {
                break;
            }
            index += 1;
        }
    }

    if (extraDays > 0){ // we are in (month + 1)th month.
        month += 1;
        date = extraDays;
    }else {
        if (month == 2 && flag == 1) {
            date = 29;
        }else {
            date = daysOfMonth[month - 1];
        }
    }

    // calculating Hours:Minutes:Seconds

    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    seconds = (extraTime % 3600) % 60;

    // Converting to desired format
    ans += to_string(date);
    ans += "/";
    ans += to_string(month);
    ans += "/";
    ans += to_string(currYear);
    ans += " ";
    ans += to_string(hours);
    ans += ":";
    ans += to_string(minutes);
    ans += ":";
    ans += to_string(seconds);

    // return the human readable point in time.
    return ans;
}

int main()
{
    // sample input
    long int seconds = 1354626750;

    string ans = unixTimeStampToHumanReadable(seconds);

    cout << ans << "\n";

    return 0;
}
