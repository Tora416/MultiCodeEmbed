


#include <stdio.h>
#include <string.h>
#include "date_time.h"

#if defined(_WIN32)
   #include <time.h>
#endif


static const char days[8][10] =
{
   "",
   "Monday",
   "Tuesday",
   "Wednesday",
   "Thursday",
   "Friday",
   "Saturday",
   "Sunday"
};


static const char months[13][10] =
{
   "",
   "January",
   "February",
   "March",
   "April",
   "May",
   "June",
   "July",
   "August",
   "September",
   "October",
   "November",
   "December"
};




const char_t *formatSystemTime(systime_t time, char_t *str)
{
   uint16_t hours;
   uint8_t minutes;
   uint8_t seconds;
   uint16_t milliseconds;
   static char_t buffer[24];

   
   milliseconds = time % 1000;
   time /= 1000;
   
   seconds = time % 60;
   time /= 60;
   
   minutes = time % 60;
   time /= 60;
   
   hours = time;

   
   if(!str)
      str = buffer;

   
   if(hours > 0)
   {
      osSprintf(str, "%" PRIu16 "h %02" PRIu8 "min %02" PRIu8 "s %03" PRIu16 "ms",
         hours, minutes, seconds, milliseconds);
   }
   else if(minutes > 0)
   {
      osSprintf(str, "%" PRIu8 "min %02" PRIu8 "s %03" PRIu16 "ms",
         minutes, seconds, milliseconds);
   }
   else if(seconds > 0)
   {
      osSprintf(str, "%" PRIu8 "s %03" PRIu16 "ms", seconds, milliseconds);
   }
   else
   {
      osSprintf(str, "%" PRIu16 "ms", milliseconds);
   }

   
   return str;
}




const char_t *formatDate(const DateTime *date, char_t *str)
{
   static char_t buffer[40];

   
   if(!str)
      str = buffer;

   
   if(date->dayOfWeek)
   {
      osSprintf(str, "%s, %s %" PRIu8 ", %" PRIu16 " %02" PRIu8 ":%02" PRIu8 ":%02" PRIu8,
         days[MIN(date->dayOfWeek, 7)], months[MIN(date->month, 12)], date->day,
         date->year, date->hours, date->minutes, date->seconds);
   }
   else
   {
      osSprintf(str, "%s %" PRIu8 ", %" PRIu16 " %02" PRIu8 ":%02" PRIu8 ":%02" PRIu8,
         months[MIN(date->month, 12)], date->day, date->year,
         date->hours, date->minutes, date->seconds);
   }

   
   return str;
}




void getCurrentDate(DateTime *date)
{
   
   time_t time = getCurrentUnixTime();

   
   convertUnixTimeToDate(time, date);
}




__weak time_t getCurrentUnixTime(void)
{
#if defined(_WIN32)
   
   return time(NULL);
#else
   
   return 0;
#endif
}




void convertUnixTimeToDate(time_t t, DateTime *date)
{
   uint32_t a;
   uint32_t b;
   uint32_t c;
   uint32_t d;
   uint32_t e;
   uint32_t f;

   
   if(t < 1)
      t = 0;

   
   date->milliseconds = 0;

   
   date->seconds = t % 60;
   t /= 60;
   date->minutes = t % 60;
   t /= 60;
   date->hours = t % 24;
   t /= 24;

   
   a = (uint32_t) ((4 * t + 102032) / 146097 + 15);
   b = (uint32_t) (t + 2442113 + a - (a / 4));
   c = (20 * b - 2442) / 7305;
   d = b - 365 * c - (c / 4);
   e = d * 1000 / 30601;
   f = d - e * 30 - e * 601 / 1000;

   
   if(e <= 13)
   {
      c -= 4716;
      e -= 1;
   }
   else
   {
      c -= 4715;
      e -= 13;
   }

   
   date->year = c;
   date->month = e;
   date->day = f;

   
   date->dayOfWeek = computeDayOfWeek(c, e, f);
}




time_t convertDateToUnixTime(const DateTime *date)
{
   uint_t y;
   uint_t m;
   uint_t d;
   uint32_t t;

   
   y = date->year;
   
   m = date->month;
   
   d = date->day;

   
   if(m <= 2)
   {
      m += 12;
      y -= 1;
   }

   
   t = (365 * y) + (y / 4) - (y / 100) + (y / 400);
   
   t += (30 * m) + (3 * (m + 1) / 5) + d;
   
   t -= 719561;
   
   t *= 86400;
   
   t += (3600 * date->hours) + (60 * date->minutes) + date->seconds;

   
   return t;
}




int_t compareDateTime(const DateTime *date1, const DateTime *date2)
{
   int_t res;

   
   if(date1->year < date2->year)
      res = -1;
   else if(date1->year > date2->year)
      res = 1;
   else if(date1->month < date2->month)
      res = -1;
   else if(date1->month > date2->month)
      res = 1;
   else if(date1->day < date2->day)
      res = -1;
   else if(date1->day > date2->day)
      res = 1;
   else if(date1->hours < date2->hours)
      res = -1;
   else if(date1->hours > date2->hours)
      res = 1;
   else if(date1->minutes < date2->minutes)
      res = -1;
   else if(date1->minutes > date2->minutes)
      res = 1;
   else if(date1->seconds < date2->seconds)
      res = -1;
   else if(date1->seconds > date2->seconds)
      res = 1;
   else if(date1->milliseconds < date2->milliseconds)
      res = -1;
   else if(date1->milliseconds > date2->milliseconds)
      res = 1;
   else
      res = 0;

   
   return res;
}




uint8_t computeDayOfWeek(uint16_t y, uint8_t m, uint8_t d)
{
   uint_t h;
   uint_t j;
   uint_t k;

   
   if(m <= 2)
   {
      m += 12;
      y -= 1;
   }

   
   j = y / 100;
   
   k = y % 100;

   
   h = d + (26 * (m + 1) / 10) + k + (k / 4) + (5 * j) + (j / 4);

   
   return ((h + 5) % 7) + 1;
}
