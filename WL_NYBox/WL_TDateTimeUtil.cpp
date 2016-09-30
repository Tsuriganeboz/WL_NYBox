#include "WL_TDateTimeUtil.h"



//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
time_t WL_ConvertFromTDateTime(double dateTime)
{
	// define structure of type time_t, c++ base date is 01/01/1970 (25569 days after FT start date of 30/12/1899)
	time_t time;
	time = (time_t) ((dateTime - 25569) * 86400);
	return time;
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
double WL_ConvertToTDateTime(time_t time)
{
	double dateTime = (((double) time / 86400) + 25569);
	return dateTime;
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_YearOf(double dateTime)
{
	time_t time = WL_ConvertFromTDateTime(dateTime);

	struct tm* timeinfo = _gmtime64(&time);
	return (1900 + timeinfo->tm_year);
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_MonthOf(double dateTime)
{
	time_t time = WL_ConvertFromTDateTime(dateTime);

	struct tm* timeinfo = _gmtime64(&time);
	return (1 + timeinfo->tm_mon);
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_DayOf(double dateTime)
{
	time_t time = WL_ConvertFromTDateTime(dateTime);

	struct tm* timeinfo = _gmtime64(&time);
	return timeinfo->tm_mday;
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_HourOf(double dateTime)
{
	time_t time = WL_ConvertFromTDateTime(dateTime);

	struct tm* timeinfo = _gmtime64(&time);
	return timeinfo->tm_hour;
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_MinuteOf(double dateTime)
{
	time_t time = WL_ConvertFromTDateTime(dateTime);

	struct tm* timeinfo = _gmtime64(&time);
	return timeinfo->tm_min;
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
double WL_DateTimeOfHoursOfToday(double dateTime, int hour, int minute)
{
	time_t time = WL_ConvertFromTDateTime(dateTime);

	struct tm* timeinfo = _gmtime64(&time);

	timeinfo->tm_hour = hour;
	timeinfo->tm_min = minute;

	int days = 0;
	switch (timeinfo->tm_wday) {
	case 6:
		days = 1;
		break;
	case 0:				//“ú
		days = 2;
		break;
	default:
		days = 0;
		break;
	}

	time_t resultTime = _mkgmtime64(timeinfo) - ((days * 24) * 60 * 60);	// - 24 ŽžŠÔ

	return WL_ConvertToTDateTime(resultTime);
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
double WL_DateTimeOfHoursOfYesterday(double dateTime, int hour, int minute)
{
	time_t time = WL_ConvertFromTDateTime(dateTime);

	struct tm* timeinfo = _gmtime64(&time);

	timeinfo->tm_hour = hour;
	timeinfo->tm_min = minute;

	int days = 1;
	switch (timeinfo->tm_wday) {
	default:
	case 6:
		days = 1;
		break;
	case 0:				//“ú
		days = 2;
		break;
	case 1:
		days = 3;
		break;
	}

	time_t resultTime = _mkgmtime64(timeinfo) - ((days * 24) * 60 * 60);	// - 24 ŽžŠÔ

	return WL_ConvertToTDateTime(resultTime);
}