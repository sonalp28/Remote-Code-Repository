#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkout.h       : demonstrate check-out package operations											//
// ver 1.0																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 2 [Software Repository Testbed] Object Oriented Design CSE-687 Spring'18  //
// Author           : Sonal Patil, Syracuse University                                                  //
//                    spatil06@syr.edu (408)-416-6291                                                   //  
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This package defines class checkout which checks out the files asked by user into his local repository
*
* Public Interface:
* =================
* checkout(std::string s, std::string d) : file1(s), file2(d) {} - parameterized constructor with initilization list to initialize private params of class
* bool checkoutFile() - memeber function of check-out class to copy files from source to destination using File class defined in FileSystem.h
*
* Required Files:
* ===============
* checkout.h, checkout.cpp,
* FileSystem.h, FileSystem.cpp
*
* Build Command:
* ==============
*
*
* Maintenance History:
* ====================
* ver 1.0 : 06 March 18
* - first release
*/

#include <iostream>
#include "../FileSystem/FileSystem.h"
#include "../DbCore/DbCore.h"
#include "../DbCore/Payload.h"

using namespace FileSystem;
using namespace NoSqlDb;

namespace CheckOut
{
	/////////////////////
	//Check-out class
	/////////////////////
	class checkout {
	public:
		checkout(std::string s, std::string d) : file1(s), file2(d) {}		//parameterized constructor
		bool checkoutFile();												//function implemented in cpp file

	private:
		std::string file1;
		std::string file2;
	};

}
