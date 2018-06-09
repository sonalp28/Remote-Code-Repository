#ifndef UTILITIES_H
#define UTILITIES_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities.h		: small, generally usefule, helper classes											//
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
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <functional>

namespace Utilities
{
	///////////////////////////////////////////////////////////////////
	// Utilities for std::string
	// - split accepts comma separated list of items and returns
	//   std::vector containing each item
	// - Title writes src string to console with underline of '=' chars
	// - title writes src string to console with underline of '-' chars

	class StringHelper
	{
	public:
		static std::vector<std::string> split(const std::string& src);
		static void Title(const std::string& src, char underline = '=');
		static void title(const std::string& src);
		static std::string trim(const std::string& src);
		static std::string addHeaderAndFooterLines(const std::string& src);
	};

	///////////////////////////////////////////////////////////////////
	// function writes return to console

	void putline();

	///////////////////////////////////////////////////////////////////
	// DisplayLocation writes start address, ending address and size
	// to console

	std::string ToDecAddressString(size_t address);
	std::string ToHexAddressString(size_t address);

	template<typename T>
	void DisplayLocation(T& t)
	{
		size_t address = reinterpret_cast<size_t>(&t);
		size_t size = sizeof(t);

		std::cout << ToDecAddressString(address)
			<< " : "
			<< ToDecAddressString(address + size)
			<< ", " << size;
	}

	///////////////////////////////////////////////////////////////////
	// Converter converts template type T to and from string

	template <typename T>
	class Converter
	{
	public:
		static std::string toString(const T& t);
		static T toValue(const std::string& src);
	};

	template <typename T>
	std::string Converter<T>::toString(const T& t)
	{
		std::ostringstream out;
		out << t;
		return out.str();
	}

	template<typename T>
	T Converter<T>::toValue(const std::string& src)
	{
		std::istringstream in(src);
		T t;
		in >> t;
		return t;
	}
}
#endif
