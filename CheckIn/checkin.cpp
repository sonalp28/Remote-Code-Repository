//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkin.cpp			: demonstrate check-in package operations											//
// ver 1.0																								    //
// Platform             : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language             : C# & .Net Framework                                                               //-|  <----------Requirement 1---------->
// Application          : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author               : Sonal Patil, Syracuse University                                                  //
//                        spatil06@syr.edu (408)-416-6291                                                   // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This package defines class checkin which checks in the files given by user into repository
*
* Public Interface:
* =================
* checkin(std::string s, std::string d) : file1(s), file2(d) {} - parameterized constructor with initilization list to initialize private params of class
* bool checkinFile() - memeber function of check-in class to copy files from source to destination using File class defined in FileSystem.h
*
* Required Files:
* ===============
* checkin.h, checkin.cpp
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
#include "checkin.h"

/*<---------------------------function to copy files from source to destination using File class defined in FileSystem.h-------------------------->*/
bool CheckIn::checkin::checkinFile()
{
	bool t1 = true;
	std::string testFileSpec = file1;
	std::string dst = file2;
	if (File::exists(testFileSpec))
	{
		t1 = File::copy(testFileSpec, dst, false);
	}
	else
		std::cout << "\n  " << testFileSpec << " does not exist";
	return t1;
}

/*<---------------------------------------Test stub-------------------------------------------------->*/
#ifdef TEST_CHECKIN
int main() {
	std::cout << "Check-in Package test stub";
	std::string s = "../ClientRepository/Check-in/display.h";
	std::string d = "../ServerRepository/display/display.h";
	CheckIn::checkin c(s, d);
	bool result = c.checkinFile();
	std::cout << result;
	return 1;
}
#endif


