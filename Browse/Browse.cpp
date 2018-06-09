//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse.cpp			: demonstrate browse package operations												//
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

#include <iostream>
#include "Browse.h"

/*<------------function which performs query on db passed by repocore & displays package description of files matching given category----------->*/
void Browse::browse::categoryQuery(std::string catName) {
	Query<PayLoad> q1(db_);

	std::cout << "\n\n  Select on Payload categories for \"" << catName << "\"\n";

	auto hasCategory = [&catName](DbElement<PayLoad>& elem) {
		return (elem.payLoad()).hasCategory(catName);
	};

	q1.select(hasCategory).show();			//shows the query executed database
}

/*<----------------------------------------------function which performs query on db for file matching with given name-------------------------->*/
std::string Browse::browse::fileDepenQuery(std::string fileName) {
	std::string file_names = "";
	Keys files;
	Query<PayLoad> q1(db_);
	Keys saveKeys = q1.keys();
	q1.from(saveKeys);
	Conditions<PayLoad> conds1;
	conds1.name(fileName);
	files = q1.select(conds1).show();
	for (auto key : files) {
		Children c = db_[key].children();
		for (unsigned i = 0; i < c.size(); i++)
			file_names += db_[c.at(i)].name() + ",";
	}
	return file_names;

}

/*<-----------------------------------Test Stub-------------------------------------->*/
#ifdef TEST_BROWSE
void main() {
	std::cout << "Browse package test stub";
	NoSqlDb::DbCore<NoSqlDb::PayLoad> db_;
	std::string path = "";
	Browse::browse b(db_);
	path = b.fileNameQuery("display.h.1");
	std::cout << path;
	return 1;
}
#endif // TEST_BROWSE

