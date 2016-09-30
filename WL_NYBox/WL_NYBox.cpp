#define	_CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <time.h>
#include "WL_TDateTimeUtil.h"
#include "IndicatorInterfaceUnit.h"
#include "TechnicalFunctions.h"

//--- 外部変数
int g_startHourSystem = 7;
int g_endHourSystem = 14;

//---
int g_barsLimit = 1 * 24 * 60;


// バッファ
TIndexBuffer g_indHighestHigh;
TIndexBuffer g_indLowestLow;
//+------------------------------------------------------------------+


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
int WL_FindIndexForCurrentSymbolAndTimeframe60(double dateTime)
{
	return iBarShift(Symbol(), 60, dateTime, false);
}

//---------------------------------------------------------------------------
// Initialize indicator
//---------------------------------------------------------------------------
EXPORT void __stdcall Init()
{
	IndicatorShortName("NY Box");
	SetOutputWindow(ow_ChartWindow);


	RegOption("Start Hour (System)", ot_Integer, &g_startHourSystem);
	SetOptionRange("Start Hour (System)", 0, 24);
	g_startHourSystem = 7;

	RegOption("End Hour (System)", ot_Integer, &g_endHourSystem);
	SetOptionRange("End Hour (System)", 0, 24);
	g_endHourSystem = 14;

	// 
	g_indHighestHigh = CreateIndexBuffer();
	g_indLowestLow = CreateIndexBuffer();


	IndicatorBuffers(2);
	SetIndexBuffer(0, g_indHighestHigh);
	SetIndexBuffer(1, g_indLowestLow);

	SetIndexStyle(0, ds_Line, psSolid, 1, RGB(0xFF, 0x00, 0x00));
	SetIndexLabel(0, "Highest High");
	SetIndexStyle(1, ds_Line, psSolid, 1, RGB(0x00, 0x00, 0xFF));
	SetIndexLabel(1, "Lowest Low");

}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
EXPORT void __stdcall OnParamsChange()
{
}

//---------------------------------------------------------------------------
// Calculate requested bar
//---------------------------------------------------------------------------
EXPORT void __stdcall Calculate(int index)
{
	// 処理高速化のため。
	if (index >= g_barsLimit)
		return;

	double indexTime = Time(index);

	int endHourSystem0 = g_endHourSystem;
	if (endHourSystem0 == 24)
		endHourSystem0 = 0;

	int endHourSystem24 = g_endHourSystem;
	if (endHourSystem24 == 0)
		endHourSystem24 = 24;

	int indexHour = WL_HourOf(indexTime);

	do
	{
		if (endHourSystem0 <= indexHour && indexHour <= 23)
		{
			double startDateTime = WL_DateTimeOfHoursOfToday(indexTime, g_startHourSystem);
			double endDateTime = WL_DateTimeOfHoursOfToday(indexTime, (endHourSystem24 - 1), 59);

			int startIndex = WL_FindIndexForCurrentSymbolAndTimeframe60(startDateTime);
			if (startIndex == -1)
				break;

			int endIndex = WL_FindIndexForCurrentSymbolAndTimeframe60(endDateTime);
			if (endIndex == -1)
				break;

			double high = iHigh(Symbol(), 60, iHighest(Symbol(), 60, MODE_HIGH, (startIndex - endIndex + 1), endIndex));
			double low = iLow(Symbol(), 60, iLowest(Symbol(), 60, MODE_LOW, (startIndex - endIndex + 1), endIndex));

			g_indHighestHigh[index] = high;
			g_indLowestLow[index] = low;
		}
		else if (0 <= indexHour && (indexHour + 1) <= endHourSystem24)
		{
			double startDateTime = WL_DateTimeOfHoursOfYesterday(indexTime, g_startHourSystem);
			double endDateTime = WL_DateTimeOfHoursOfYesterday(indexTime, (endHourSystem24 - 1), 59);

			int startIndex = WL_FindIndexForCurrentSymbolAndTimeframe60(startDateTime);
			if (startIndex == -1)
				break;

			int endIndex = WL_FindIndexForCurrentSymbolAndTimeframe60(endDateTime);
			if (endIndex == -1)
				break;

			double high = iHigh(Symbol(), 60, iHighest(Symbol(), 60, MODE_HIGH, (startIndex - endIndex + 1), endIndex));
			double low = iLow(Symbol(), 60, iLowest(Symbol(), 60, MODE_LOW, (startIndex - endIndex + 1), endIndex));

			g_indHighestHigh[index] = high;
			g_indLowestLow[index] = low;
		}
		else {}
	} while (false);

}
