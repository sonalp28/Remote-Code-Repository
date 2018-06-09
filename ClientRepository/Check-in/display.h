//////////////////////////////////////////////////////////////////////////////////////////////////////////
// display.h        : demonstrate display package operations											//
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
* This package defines class display which provides means show functionality
*
* Public Interface:
* =================
* void displayFiles() - function to display files
*
* Required Files:
* ===============
* save.h
*
* Build Command:
* ==============
*
* Maintenance History:
* ====================
* ver 1.0 : 06 March 18
* - first release
*/

#include "Save.h"

namespace display{
	class display{
	public:
		void displayFiles();
	};
}