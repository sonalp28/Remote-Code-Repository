#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// RepoCore.h       : demonstrate Repository core package operations									//
// ver 1.1																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author           : Sonal Patil, Syracuse University                                                  //
//                    spatil06@syr.edu (408)-416-6291                                                   // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This package defines class RepoCore which provides means to check-in, version, browse, and check-out source code packages
*
* Public Interface:
* =================
* inline void identify(std::ostream& out = std::cout) - function to test the existance of TestExecutive package
* bool do_checkin(std::string s, std::string d, int count, std::string description, std::string author, std::string category, std::string status, std::string children) - function for provideing means to checkin package by calling its functions
* bool checkin(std::string s, std::string d, int count, std::string description, std::string author, std::string category, std::string status, std::string children) - function for provideing means to checkin package by calling its functions
* void createMetadata(std::string name, std::string author, std::string status, std::string category, std::string description, std::string path, std::string children) - to initialize metadata in database core
* void createDb() - function to insert a new db element entry for current file in the current database
* void display_db() - function to display database content
* void display_payload() - function to display payload content with name
* bool checkout(std::string s, std::string d) - function for provideing means to checkout package by calling its functions
* std::string version(std::string str, std::string command, int count) - function for provideing means to version package by calling its functions
* bool browsebyCategory(std::string catString) - function for provideing means to browse package by calling its categoryQuery function
* std::string browseFile(std::string fileString) - function for browsing file whose db element contains in the current db
* void openNotepad(std::string str) - function that calls spawnproc package and shows the content of the browsed file
* std::vector<std::string> getFileNames(std::string str) - function that returns the filenames containing in particular package
* std::string getStatus(Key key) - function that returns the check-in status stored in the db for given file
* std::string getLastStatus(std::string fname) - function that returns the last status of a file that matches with the given pattern
* std::string getlastcount(std::string fname) - function that returns the last version number of a file that matches with the given pattern
* std::string getDependentFiles(std::string fileName) - function that returns dependent files for given file 
* std::string getCatgories() - function that returns all categories for a package
* std::string getCatgoryFiles(std::string catgName) - function that returns all files for given category
* std::string getQueryResult(std::string fname, std::string catg, std::string depend, std::string version) - function to get query result as per the data given
* void getBackDb() - function to restore db from XML file
* std::string getDbData() - function that returns whole database as a string
*
* Required Files:
* ===============
* checkin.h, checkin.cpp
* checkout.h checkout.cpp
* version.h, version.cpp
* Browse.h, Browse.cpp
* DbCore.h, DbCore.cpp,
* Payload.h, Persist.h
*
* Build Command:
* ==============
*
*
* Maintenance History:
* ====================
* ver 1.1 : 01 May 2018
* - modified few stuff & added new functions for project 4
* ver 1.0 : 06 March 18
* - first release
*/

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../CheckIn/checkin.h"
#include "../CheckOut/checkout.h"
#include "../Version/version.h"
#include "../Browse/Browse.h"
#include "../DbCore/DbCore.h"
#include "../DbCore/Payload.h"
#include "../DbCore/Persist.h"


using namespace CheckIn;
using namespace CheckOut;
using namespace Version;
using namespace NoSqlDb;
using namespace Browse;

namespace RepositoryCore
{
	/////////////////////
	//RepoCore class
	/////////////////////
	class RepoCore {
	public:
		RepoCore() {}			//default constructor
								//function to test the existance of TestExecutive package
		inline void identify(std::ostream& out = std::cout) { out << "\n     \"" << __FILE__ << "\""; }

		bool do_checkin(std::string s, std::string d, int count, std::string description, std::string author, std::string category, std::string status, std::string children);
		bool checkin(std::string s, std::string d, int count, std::string description, std::string author, std::string category, std::string status, std::string children);

		void createMetadata(std::string author, std::string status, std::string category, std::string description, std::string path, std::string children);
		void createDb();
		void display_db();
		void display_payload();

		bool checkout(std::string s, std::string d);

		std::string version(std::string str, std::string command, int count);

		bool browsebyCategory(std::string catString);
		std::string browseFile(std::string fileString);
		void openNotepad(std::string str);

		std::vector<std::string> getFileNames(std::string str);
		std::string getStatus(Key key);
		std::string getLastStatus(std::string fname);
		std::string getlastcount(std::string fname);
		std::string getDependentFiles(std::string fileName);
		std::string getCatgories();
		std::string getCatgoryFiles(std::string catgName);
		std::string getQueryResult(std::string fname, std::string catg, std::string depend, std::string version);
		std::string getDbData();
		void getBackDb();
	private:
		NoSqlDb::DbCore<NoSqlDb::PayLoad> db_;
		std::string name_;
		std::string status_;
		std::string category_;
		std::string description_;
		std::string path_;
		std::string author_;
		std::vector<std::string> children_;
	};

}
