//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkout.cpp			: demonstrate check-out package operations											//
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
* This package defines class checkout which checks out the files asked by user into his local repository
*
* Public Interface:
* =================
* checkout(std::string s, std::string d) : file1(s), file2(d) {} - parameterized constructor with initilization list to initialize private params of class
* bool checkoutFile() - memeber function of check-out class to copy files from source to destination using File class defined in FileSystem.h
*
* Required Files:
* ===============
* FileSystem.h, FileSystem.cpp,
* checkout.h, checkout.cpp
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
#include "checkout.h"

/*<---------------------------function to copy files from source to destination using File class defined in FileSystem.h-------------------------->*/
bool CheckOut::checkout::checkoutFile()
{
	bool t1 = true;
	std::string testFileSpec = file1;
	std::string dst = file2;
	if (File::exists(testFileSpec))
	{
		t1 = File::copy(testFileSpec, dst, false);
		std::cout << Path::getFullFileSpec(dst) << "\n";
	}
	else
		std::cout << "\n  " << testFileSpec << " does not exist";
	return t1;
}

/*<---------------------------------------Test stub-------------------------------------------------->*/
#ifdef TEST_CHECKOUT
int main() {
	std::cout << "Check-out package test stub";
	std::string source_path = "../ServerRepository/display/display.h"; 
	std::string dest_path = "../ClientRepository/Check-in/display.h";
	CheckOut::checkout chkout(s, d);
	bool result = chkout.checkoutFile();
	return 1;
}
#endif