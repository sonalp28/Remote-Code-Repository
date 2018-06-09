#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// DateTime.h		: represents clock time																//
// ver 1.1																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author           : Dr. Jim Fawcett, EECS, SU                                                         // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* The DateTime class represents clock time, and supports:
* - creating default instances and instances from specific time points
* - return times as formatted strings
* - building time points and durations from years, months, days, hours, ...
* - performing addition and subtraction of times
* - comparing times
* - extracting counts of years, months, days, hours, minutes, and seconds
*
* Required Files:
* ---------------
*   DateTime.h
*
*  Build Command:
* ----------------
*  devenv repo.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.1 : 10 Feb 2018
* - added operator==, operator!=, operator<=, and operator>=
* ver 1.0 : 18 Feb 2018
* - first release
*/

#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <unordered_map>

class DateTime
{
public:
	using SysClock = std::chrono::system_clock;
	using TimePoint = std::chrono::system_clock::time_point;
	using Duration = std::chrono::system_clock::duration;

	DateTime();
	DateTime(std::string dtStr);
	DateTime(const TimePoint& tp);
	operator std::string();

	std::string now();
	TimePoint timepoint();
	size_t ticks();
	std::string time();
	static TimePoint makeTime(
		size_t yrs, size_t mon, size_t day,
		size_t hrs = 0, size_t min = 0, size_t sec = 0
	);
	static Duration makeDuration(
		size_t hrs, size_t min, size_t sec = 0, size_t millisec = 0
	);

	DateTime operator+=(const Duration& dt);
	DateTime operator+(const Duration& dt);
	DateTime operator-=(const Duration& dt);
	DateTime operator-(const Duration& dt);
	bool operator<(const DateTime& dt);
	bool operator>(const DateTime& dt);
	bool operator==(const DateTime& dt);
	bool operator!=(const DateTime& dt);
	bool operator<=(const DateTime& dt);
	bool operator>=(const DateTime& dt);

	size_t year();
	size_t month();
	size_t day();
	size_t hour();
	size_t minute();
	size_t second();
private:
	char* ctime(const std::time_t* pTime);
	std::tm* localtime(const time_t* pTime);
	TimePoint tp_;
};

//----< replaces std::ctime using ctime_s >--------------------------

inline char* DateTime::ctime(const std::time_t* pTime)
{
	const rsize_t buffSize = 26;
	static char buffer[buffSize];
	errno_t err = ctime_s(buffer, buffSize, pTime);
	return buffer;
}
//----< replaces std::localtime using localtime_s >------------------

inline std::tm* DateTime::localtime(const std::time_t* pTime)
{
	static std::tm result;
	errno_t err = localtime_s(&result, pTime);
	return &result;
}
//----< construct DateTime instance with current system time >-------

inline DateTime::DateTime()
{
	tp_ = SysClock::now();
}
//----< construct DateTime from formatted time string >--------------
/*
* Helper function that reads each part of the formatted string
*/
inline int readDateTimePart(int& part, std::istringstream& in)
{
	if (in.peek() == ':')
		in.get();
	in >> part;
	//std::cout << "\n  -- part = " << part << " --";
	if (in.good())
		return part;
	return -1;
}
//----< makes a DateTime instance from a formatted string >----------
/*
*  Throws exception if string is an invalid DateTime string
*/
inline DateTime::DateTime(std::string dtStr)
{
	static std::unordered_map<std::string, size_t> months = {
		{ "Jan", 1 },{ "Feb", 2 },{ "Mar", 3 },{ "Apr", 4 },
		{ "May", 5 },{ "Jun", 6 },{ "Jul", 7 },{ "Aug", 8 },
		{ "Sep", 9 },{ "Oct", 10 },{ "Nov", 11 },{ "Dec", 12 }
	};
	std::istringstream in(dtStr);
	std::string day, month;
	in >> day;
	in >> month;
	if (!in.good())
		throw std::exception("invalid DateTime string");
	std::tm date;
	date.tm_mon = months[month] - 1;
	readDateTimePart(date.tm_mday, in);
	readDateTimePart(date.tm_hour, in);
	readDateTimePart(date.tm_min, in);
	readDateTimePart(date.tm_sec, in);
	readDateTimePart(date.tm_year, in);
	date.tm_year -= 1900;
	date.tm_isdst = -1;
	std::time_t time = std::mktime(&date);
	if (time == -1)
	{
		throw "invalid system time";
	}
	tp_ = SysClock::from_time_t(time);
}
//----< cast operator converts to time formatted string >------------

inline DateTime::operator std::string()
{
	return time();
}
//----< construct DateTime instance from time point >----------------

inline DateTime::DateTime(const DateTime::TimePoint& tp) : tp_(tp) {}

//----< make a time from integral parts >----------------------------

inline DateTime::TimePoint DateTime::makeTime(
	size_t year, size_t mon, size_t day, size_t hour, size_t min, size_t sec
)
{
	struct std::tm t;
	t.tm_sec = sec;
	t.tm_min = min;
	t.tm_hour = hour;
	t.tm_mday = day;
	t.tm_mon = mon - 1;
	t.tm_year = year - 1900;
	t.tm_isdst = -1;
	std::time_t time = std::mktime(&t);
	if (time == -1)
	{
		throw "invalid system time";
	}
	return SysClock::from_time_t(time);
}
//----< make duration from integral parts >--------------------------

inline DateTime::Duration DateTime::makeDuration(
	size_t hour, size_t min, size_t sec, size_t millisec
)
{
	Duration dur =
		std::chrono::milliseconds(millisec) +
		std::chrono::seconds(sec) +
		std::chrono::minutes(min) +
		std::chrono::hours(hour);
	return dur;
}
//----< set time to system time >------------------------------------

inline std::string DateTime::now()
{
	TimePoint tp = SysClock::now();
	std::time_t t = SysClock::to_time_t(tp);
	std::string ts = ctime(&t);
	ts.resize(ts.size() - 1);
	return ts;
}
//----< return internal time point >---------------------------------

inline DateTime::TimePoint DateTime::timepoint()
{
	return tp_;
}
//----< return seconds from Jan 1 1990 at midnight >-----------------

inline size_t DateTime::ticks()
{
	auto int_sec = std::chrono::duration_cast<std::chrono::seconds>(tp_.time_since_epoch());
	return static_cast<size_t>(int_sec.count());
}
//----< return formatted time string >-------------------------------

inline std::string DateTime::time()
{
	std::time_t t = SysClock::to_time_t(tp_);
	std::string ts = ctime(&t);
	ts.resize(ts.size() - 1);
	return ts;
}
//----< compare DateTime instances >---------------------------------

inline bool DateTime::operator<(const DateTime& dt)
{
	return tp_ < dt.tp_;
}
//----< compare DateTime instances >---------------------------------

inline bool DateTime::operator>(const DateTime& dt)
{
	return tp_ > dt.tp_;
}
//----< compare DateTime instances >---------------------------------

inline bool DateTime::operator==(const DateTime& dt)
{
	return tp_ == dt.tp_;
}
//----< compare DateTime instances >---------------------------------

inline bool DateTime::operator!=(const DateTime& dt)
{
	return tp_ != dt.tp_;
}
//----< compare DateTime instances >---------------------------------

inline bool DateTime::operator<=(const DateTime& dt)
{
	return tp_ <= dt.tp_;
}
//----< compare DateTime instances >---------------------------------

inline bool DateTime::operator>=(const DateTime& dt)
{
	return tp_ >= dt.tp_;
}
//----< add a duration to DateTime instance >------------------------

inline DateTime DateTime::operator+=(const DateTime::Duration& dur)
{
	tp_ += dur;
	return *this;
}
//----< make DateTime from instance time plus duration >-------------

inline DateTime DateTime::operator+(const DateTime::Duration& dur)
{

	return DateTime(tp_ + dur);
}
//----< subtract a duration from instance >--------------------------

inline DateTime DateTime::operator-=(const DateTime::Duration& dur)
{
	tp_ -= dur;
	return *this;
}
//---- make DateTime from instance time minus duration >-------------

inline DateTime DateTime::operator-(const DateTime::Duration& dur)
{
	return DateTime(tp_ - dur);
}
//----< return year count >------------------------------------------

inline size_t DateTime::year()
{
	std::time_t t = SysClock::to_time_t(tp_);
	std::tm tm = *localtime(&t);
	return tm.tm_year;
}
//----< return month count >-----------------------------------------

inline size_t DateTime::month()
{
	std::time_t t = SysClock::to_time_t(tp_);
	std::tm tm = *localtime(&t);
	return tm.tm_mon;
}
//----< return day count >-------------------------------------------

inline size_t DateTime::day()
{
	std::time_t t = SysClock::to_time_t(tp_);
	std::tm tm = *localtime(&t);
	return tm.tm_mday;
}
//----< return hour count >------------------------------------------

inline size_t DateTime::hour()
{
	std::time_t t = SysClock::to_time_t(tp_);
	std::tm tm = *localtime(&t);
	return tm.tm_hour;
}
//----< return minutes count >---------------------------------------

inline size_t DateTime::minute()
{
	std::time_t t = SysClock::to_time_t(tp_);
	std::tm tm = *localtime(&t);
	return tm.tm_min;
}
//----< return seconds count >---------------------------------------

inline size_t DateTime::second()
{
	std::time_t t = SysClock::to_time_t(tp_);
	std::tm tm = *localtime(&t);
	return tm.tm_sec;
}
