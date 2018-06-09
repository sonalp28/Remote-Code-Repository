//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities.cpp	: small, generally usefule, helper classes											//
// ver 1.0																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author			: Jim Fawcett, CST 4-187, Syracuse University										//
//					  (315) 443-3948, jfawcett@twcny.rr.com												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package defines a single class, Convert<T> that supports convering
* instances of the T type to and from strings.  Also included are a few
* global functions intended to simplify code (slightly).
*
* Public Interface :
* ------------------
* template<typename T> std::string Convert<T>::toString(const T& t) - serialize t to a std::string
* template<typename T> T Convert<T>::fromString(const std::string& str) - create an instance of T from a std::string
* template<typename T> std::string Convert<T>::id(const T& t) - create an id string from an instance of T using RTTI
* template<> inline std::string Convert<std::string>::toString(const std::string& str) - specialization for std::strings
* template<> inline std::string Convert<std::string>::fromString(const std::string& str) - specialization for std::strings
* inline void putLine() - put blank line on command prompt
* inline void putLines(size_t n) - put blank lines of given number on command prompt
* inline void titleCore(const std::string& msg, char underline = '-') - convert title into proper format for command prompt
* inline void Title(const std::string& msg)  -  global function that gets the title
* inline void subTitle(const std::string& msg) - global function that gets the sub-title
* static inline int isspaceHelper(int ch) - string trim function:
* static inline std::string &ltrim(std::string &s) - trim from start
* static inline std::string &rtrim(std::string &s) - trim from end
* inline std::string &trim(std::string &s) - trim from both end
*
* Build Process:
* --------------
*   devenv repo.sln /debug rebuild
*
* Required Files:
* ---------------
*   Utilities.h, Utilities.cpp
*
* Maintenance History:
*---------------------
* ver 1.0 : 06 Feb 2017
* - first release
*/

#include <cctype>
#include <iostream>
#include <sstream>
#include <cctype>
#include <locale>
#include "Utilities.h"

using namespace Utilities;

/////////////////////////////////////////////////////////////////////
// next two functions show how to create alias for function name

std::function<void(const std::string&)> Title =
[](auto src) { StringHelper::Title(src, '='); };

std::function<void(const std::string&)> title =
[](auto src) { StringHelper::Title(src, '-'); };

//----< write major title to console >-------------------------------

void StringHelper::title(const std::string& src)
{
	std::cout << "\n  " << src;
	std::cout << "\n " << std::string(src.size() + 2, '-');
}
//----< write minor title to console >-------------------------------

void StringHelper::Title(const std::string& src, char underline)
{
	std::cout << "\n  " << src;
	std::cout << "\n " << std::string(src.size() + 2, underline);
}
//----< convert comma separated list into vector<std::string> >------
/*
*  - also works for newline separated list
*/
std::vector<std::string> StringHelper::split(const std::string& src)
{
	std::vector<std::string> accum;
	std::string temp;
	size_t index = 0;
	do
	{
		while ((src[index] == ',' || src[index] == '\n') && index < src.length())
		{
			++index;
			if (temp.size() > 0)
			{
				accum.push_back(temp);
				temp.clear();
			}
		}
		if (src[index] != '\0')
			temp += src[index];
	} while (index++ < src.size());
	if (temp.size() > 0)
		accum.push_back(temp);
	return accum;
}
//----< remove leading and trailing whitespace >---------------------

std::string StringHelper::trim(const std::string& src)
{
	std::locale loc;
	std::string trimmed = src;
	size_t first = 0;
	while (true)
	{
		if (std::isspace(trimmed[first], loc))
			++first;
		else
			break;
	}
	size_t last = trimmed.size() - 1;
	while (true)
	{
		if (std::isspace(trimmed[last], loc) && last > 0)
			--last;
		else
			break;

	}
	return trimmed.substr(first, last - first + 1);
}
//----< wrap string in lines >---------------------------------------

std::string StringHelper::addHeaderAndFooterLines(const std::string& src)
{
	std::string line = "------------------------------";
	return line + "\n" + src + "\n" + line + "\n";
}
//----< takes any pointer type and displays as a dec string >--------

std::string Utilities::ToDecAddressString(size_t address)
{
	std::ostringstream oss;
	oss << std::uppercase << std::dec << address;
	return oss.str();
}
//----< takes any pointer type and displays as a hex string >--------

std::string Utilities::ToHexAddressString(size_t address)
{
	std::ostringstream oss;
	oss << std::uppercase << " (0x" << std::hex << address << ")";
	return oss.str();
}
//----< write newline to console >-----------------------------------

void Utilities::putline()
{
	std::cout << "\n";
}
//----< test stub >--------------------------------------------------

#ifdef TEST_UTILITIES

int main()
{
	Title("Testing Utilities Package");
	putline();

	title("test StringHelper::trim");

	std::string test1 = "  12345 ";
	std::cout << "\n  test string = \"" << test1 << "\"";

	test1 = StringHelper::trim(test1);
	std::cout << "\n  test string = \"" << test1 << "\"";
	putline();

	title("test StringHelper::split(std::string)");

	std::string test = "\na:b\naa:bb\naaa:bbb";
	std::cout << "\n  test string = " << test;
	//test = "a, \n, bc, de, efg, i, j k lm nopq rst";
	//std::cout << "\n  test string = " << test;

	std::vector<std::string> result = StringHelper::split(test);

	std::cout << "\n";
	for (auto item : result)
	{
		if (item == "\n")
			std::cout << "\n  " << "newline";
		else
			std::cout << "\n  " << item;
	}
	std::cout << "\n";

	title("test addHeaderAndFooterLines(const std::string&)");
	std::string test4 = "0123456789";
	std::cout << "\n" << StringHelper::addHeaderAndFooterLines(test4);

	title("test std::string Converter<T>::toString(T)");

	std::string conv1 = Converter<double>::toString(3.1415927);
	std::string conv2 = Converter<int>::toString(73);
	std::string conv3 = Converter<std::string>::toString("a_test_string plus more");

	std::cout << "\n  Converting from values to strings: ";
	std::cout << conv1 << ", " << conv2 << ", " << conv3;
	putline();

	title("test T Converter<T>::toValue(std::string)");

	std::cout << "\n  Converting from strings to values: ";
	std::cout << Converter<double>::toValue(conv1) << ", ";
	std::cout << Converter<int>::toValue(conv2) << ", ";
	std::cout << Converter<std::string>::toValue(conv3);

	std::cout << "\n\n";
	return 0;
}
#endif
