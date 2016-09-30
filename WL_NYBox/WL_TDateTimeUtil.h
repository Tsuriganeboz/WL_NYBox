#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
time_t WL_ConvertFromTDateTime(double dateTime);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
double WL_ConvertToTDateTime(time_t time);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_YearOf(double dateTime);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_MonthOf(double dateTime);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_DayOf(double dateTime);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_HourOf(double dateTime);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_MinuteOf(double dateTime);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
double WL_DateTimeOfHoursOfToday(double dateTime, int hour, int minute = 0);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
double WL_DateTimeOfHoursOfYesterday(double dateTime, int hour, int minute = 0);
