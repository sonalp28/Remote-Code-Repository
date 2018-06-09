#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse.h				: demonstrate browse package operations												//
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
* This package defines class Browse which provides means to support browsing of one or more packages by displaying package descriptions
*
* Public Interface:
* =================
* browse(NoSqlDb::DbCore<NoSqlDb::PayLoad>& db) : db_(db) - db is passed to browse constructor
* void categoryQuery(std::string category) - function which performs query on db passed by repocore & displays package description of files matching given category
* std::string Browse::browse::fileNameQuery(std::string fileName) - function which performs query on db for file matching with given name
*
* Required Files:
* ===============
* Browse.h, Browse.cpp,
* DbCore.h, DbCore.cpp,
* Payload.h,
* Query.h
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

#include "../DbCore/DbCore.h"
#include "../DbCore/Payload.h"
#include "../DbCore/Query.h"

using namespace NoSqlDb;

namespace Browse
{
	/////////////////////
	//Browse class
	/////////////////////
	class browse
	{
	public:
		browse(NoSqlDb::DbCore<NoSqlDb::PayLoad>& db) : db_(db) {}		//parameterized constructor
		void categoryQuery(std::string catName);						//function implemented in cpp file
		std::string fileDepenQuery(std::string fileName);					//function implemented in cpp file

	private:
		NoSqlDb::DbCore<NoSqlDb::PayLoad>& db_;
	};


}
