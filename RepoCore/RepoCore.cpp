//////////////////////////////////////////////////////////////////////////////////////////////////////////
// RepoCore.cpp     : demonstrate Repository core package operations									//
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

#include <iostream>
#include "RepoCore.h"

/*--------------------------------------------------------check-in related functionality---------------------------------------------------------*/
/*<-------------------------function that uses checkin package to perform initial checkin a new file into repository---------------------------->*/
bool RepositoryCore::RepoCore::do_checkin(std::string s, std::string d, int count, std::string description, std::string author, std::string category, std::string status, std::string children)
{
	std::cout << "  Request for Check-in [ File Name : " << Path::getName(s) << "]";
	bool result = false;
	std::string status_ = status;
	if (File::exists(d)) {
		std::size_t found = s.find_last_of("/\\");
		std::string str = s.substr(found + 1, s.size());
		status_ = getLastStatus(str);
		std::string v_count = getlastcount(str);
		int version_count = atoi(v_count.c_str());
		if (status_ == "close")
			d = version(d, "in", version_count + 1);
		if (status_ == "open")
			d = version(d, "in", version_count);
	}
	if (!File::exists(d)) {
		d = version(d, "in", count);
	}
	createMetadata(author, status_, category, description, d, children);
	createDb();
	CheckIn::checkin c(s, d);
	result = c.checkinFile();
	std::cout << "\n  Appended version number into file name";
	std::cout << "\n  Checked-in file : " << Path::getName(d) << "    Check-in Process status : " << std::boolalpha << result;
	std::cout << "\n  Checked-in location : " << Path::getPath(d);
	std::cout << "\n-----------------------------------------------------------------------------------------------------------\n";
	return result;
}

/*<--------------------------------function that uses checkin package to checkin a new file into repository------------------------------------->*/
bool RepositoryCore::RepoCore::checkin(std::string s, std::string d, int count, std::string description, std::string author, std::string category, std::string status, std::string children)
{
	std::cout << "  Request for Check-in [File Name : " << Path::getName(s) << "]";
	std::string status_ = status;
	bool result = false, dependency_match = true;
	std::size_t found1 = d.find_last_of("/\\");
	std::size_t found2 = (d.substr(0, found1)).find_last_of("/\\");
	std::size_t size = found1 - found2 - 1;
	std::string key = "::" + d.substr(found2 + 1, size) + "::" + Path::getName(d);
	DbElement<PayLoad> elem = db_[key];
	Children c = elem.children();
	if (c.size() > 0) {
		int count = 0;
		for (unsigned i = 0; i < c.size(); i++) {
			std::cout << "\n  Requested Check-in file has dependency File/s : " << c.at(i) << " with last check-in status = " << getStatus(c.at(i));
			if (getStatus(c.at(i)) == "close") { count++; }
		}
		dependency_match = (count == c.size());
	}
	if (!dependency_match) {
		if (db_[key].payLoad().status() == "close") {
			d = version(d, "in", count);
			status_ = "pending";
			std::cout << "\n  Check-in \"pending\" of file [" << Path::getName(d) << "] as it's dependency file/s are still open!\n";
			std::cout << "\n  Database displayed in the GUI shows the \"pending\" status for this file\n";
		}
	}
	if (c.size() == 0 || (c.size() > 0 && dependency_match)) {
		if ((File::exists(d) && getLastStatus(Path::getName(s)) == "close") || !File::exists(d)) {
			d = version(d, "in", count);
		}
	}
	std::cout << "\n  Appended version number into file name";
	createMetadata(author, status_, category, description, d, children);
	createDb();
	CheckIn::checkin ci(s, d);
	result = ci.checkinFile();
	std::cout << "\n  Checked-in file : " << Path::getName(d) << "    Check-in Process status : " << std::boolalpha << result;
	std::cout << "\n  Checked-in location : " << Path::getPath(d);
	std::cout << "\n-----------------------------------------------------------------------------------------------------------\n";
	return result;
}


/*--------------------------------------------------------database related functionality---------------------------------------------------------*/
/*<---------------------------------------function to initialize metadata in the database core-------------------------------------------------->*/
void RepositoryCore::RepoCore::createMetadata(std::string author, std::string status, std::string category, std::string description, std::string path, std::string children) {
	name_ = Path::getName(path);
	author_ = author;
	status_ = status;
	category_ = category;
	description_ = description;
	path_ = path;
	children_.clear();
	if (children != "") {
		std::stringstream ss(children);
		std::string token;
		while (getline(ss, token, ','))
			children_.push_back(token);
	}	
}

/*<---------------------------------------function to create a new entry for current file in the database--------------------------------------->*/
void RepositoryCore::RepoCore::createDb() {
	std::cout << "\n  Database entry created for file!";
	std::size_t found1 = path_.find_last_of("/\\");
	std::size_t found2 = (path_.substr(0, found1)).find_last_of("/\\");
	std::size_t size = found1 - found2 - 1;
	std::string key = "::" + path_.substr(found2 + 1, size) + "::" + name_;
	DbElement<PayLoad> elem;
	elem.name(name_);
	elem.descrip(description_);
	elem.dateTime(DateTime().now());
	for (size_t i = 0; i < children_.size(); i++) {
		std::size_t found1 = children_.at(i).find_first_of(".");
		std::string child_key = "::" + children_.at(i).substr(0, found1) + "::" + children_.at(i);
		elem.children().push_back(child_key);
	}
	PayLoad pl;
	pl.author() = author_;
	pl.status() = status_;
	pl.path() = path_;
	pl.value() = pl.author() + " Status:" + pl.status() + " " + path_;
	pl.categories().push_back(category_);
	elem.payLoad(pl);
	db_[key] = elem;
	static int loop = 0;
	if (loop == 14) 
		std::cout << "\n  Parsed the database and saved in ServerRepoDb.xml file located at : ../ServerRepository/ServerRepoDb.xml";
	else
		loop++;
	Persist<PayLoad> persist(db_);
	persist.saveToFile("../ServerRepository/ServerRepoDb.xml");
}

/*<------------------------- function to get dependent files for given file name -------------------------------------------->*/
std::string RepositoryCore::RepoCore::getDependentFiles(std::string fileName) {
	Browse::browse b(db_);
	std::string depend_files = b.fileDepenQuery(fileName);
	return depend_files;
}

/*<-------------------------- function that returns whole db as a string-------------------------------------------------------->*/
std::string RepositoryCore::RepoCore::getDbData() {
	std::string data = "";
	for (auto item : db_)
	{
		const Key& key = item.first;
		const DbElement<PayLoad>& el = item.second;
		data += key.substr(0, 24) + " " + el.name().substr(0, 13) + " " + std::string(el.dateTime()) + " " + el.descrip().substr(0, 18) + " " + std::string(el.payLoad()).substr(0, 75) + " ";
	}
	return data;
}

/*<------------------------------------------------function to display database content--------------------------------------------------------->*/
void RepositoryCore::RepoCore::display_db() {
	showDb(db_);
	std::cout << "\n";
}

/*<------------------------------------function that displays current payload of the database--------------------------------------------------->*/
void RepositoryCore::RepoCore::display_payload() {
	std::cout << "\n  Current database with Name, Payload & Categories \n";
	PayLoad::showDb(db_);
}

/*--------------------------------------------------------check-out related functionality--------------------------------------------------------*/
/*<-----------------function that uses checkout package to checkout a file asked by into his local repository----------------------------------->*/
bool RepositoryCore::RepoCore::checkout(std::string s, std::string d)
{
	std::cout << "  Request for Check-out [File Name : " << Path::getName(s) << "]";
	bool result = false;
	if (isdigit(d.back()))
		d = version(d, "out", 0);
	CheckOut::checkout chkout(s, d);
	std::cout << "\n  Retrieved files copied to specified directory :";
	result = chkout.checkoutFile();
	std::cout << "  Sending file : " << Path::getName(d);
	std::cout << "\n  Checked-out file : " << Path::getName(d) << "    Check-out Process status : " << std::boolalpha << result;
	std::cout << "\n------------------------------------------------------------------------------------------------------------\n";
	return result;
}


/*--------------------------------------------------------version related functionality----------------------------------------------------------*/
/*<-----------------function that uses version package to give/remove version of a file depending upon the checkin status----------------------->*/
std::string RepositoryCore::RepoCore::version(std::string str, std::string command, int count)
{
	Version::version v(str);
	std::string return_str = "";
	if (command == "in" && count != 0) {
		char c = str.back();
		if (isdigit(c))
			str = str.substr(0, str.size() - 2);
		return_str = v.giveVersion(str, count);
	}
	if (command == "out")
		return_str = v.removeVersion();
	return return_str;
}


/*---------------------------------------------------------browse related functionality----------------------------------------------------------*/
/*<-------------------------------function that uses browse package to browse files by category from repository--------------------------------->*/
bool RepositoryCore::RepoCore::browsebyCategory(std::string catstring)
{
	std::cout << "\n  Current database with Name, Payload & Categories \n";
	PayLoad::showDb(db_);
	Browse::browse b(db_);
	b.categoryQuery(catstring);
	return false;
}

/*<--------------------------------------function that uses browse package to browse a file from repository------------------------------------->*/
std::string RepositoryCore::RepoCore::browseFile(std::string fileString) {
	std::string path = "";/*
	Browse::browse b(db_);
	path = b.fileNameQuery(fileString);*/
	return path;
}

/*<-------------------------function used to open new process notepad to show the detail description of a package file-------------------------->*/
void RepositoryCore::RepoCore::openNotepad(std::string str) {
	//not needed for project 4 but good stuff so commented out and not deleted
	/*Process p;
	p.title("test application");;
	p.application("c:/windows/system32/notepad.exe");
	p.commandLine(str);
	p.create();*/
}


/*---------------------------------------------getting data from database related functionality--------------------------------------------------*/
/*<--------------------------------------------function used to change the check-in status in the db-------------------------------------------->*/
std::string RepositoryCore::RepoCore::getStatus(Key key) {
	return db_[key].payLoad().status();
}

/*<-------------------------------function that returns category names present in current database---------------------------------------------->*/
std::string RepositoryCore::RepoCore::getCatgories() {
	std::string catg_names = "";
	Keys all_keys = db_.keys();
	for (auto key : all_keys) {
		std::vector<std::string> catg = db_[key].payLoad().categories();
		for (size_t i = 0; i < catg.size(); i++)
			catg_names += catg.at(i) + " ";
	}
	return catg_names;
}

/*<-------------------------------function that returns file names for given category in current database--------------------------------------->*/
std::string RepositoryCore::RepoCore::getCatgoryFiles(std::string catgName) {
	std::string catg_Filenames = "";
	Keys all_keys = db_.keys();
	for (auto key : all_keys) {
		std::vector<std::string> catg = db_[key].payLoad().categories();
		for (size_t i = 0; i < catg.size(); i++)
			if (catg.at(i) == catgName)
				catg_Filenames += db_[key].name() + " ";
	}
	return catg_Filenames;
}

/*<-------------------------- function to get query result as per the data given -------------------------------------------->*/
std::string RepositoryCore::RepoCore::getQueryResult(std::string fname, std::string catg, std::string depend, std::string version) {
	Keys q1_result;
	bool catg_found = false;
	bool depend_found = false;
	std::string return_result = "";
	Conditions<PayLoad> conds1;
	std::string file_name = (version.empty()) ? fname : fname + "." + version;
	conds1.name(file_name);
	Query<PayLoad> q1(db_);
	q1_result = q1.select(conds1).show();
	for (auto key : q1_result) {
		std::vector<std::string> catgname = db_[key].payLoad().categories();
		for (size_t i = 0; i < catgname.size(); i++)
			if (catgname.at(i) == catg || catg.empty())
				catg_found = true;
		DbElement<PayLoad> elem = db_[key];
		Children c = elem.children();
		depend_found = (c.size() == 0) ? true : false;
		for (size_t i = 0; i < c.size(); i++) {
			std::size_t found = c.at(i).find_first_of(".");
			std::string name = c.at(i).substr(0, found);
			if (depend.find(name) || depend.empty())
				depend_found = true;
		}	
		if (catg_found && depend_found)
			return_result += db_[key].name() + " ";
	}
	return return_result;
}

/*<------------------------------function that returns the file names matching with the given string-------------------------------------------->*/
std::vector<std::string> RepositoryCore::RepoCore::getFileNames(std::string str) {
	std::vector<std::string> fileNames;
	Keys files;
	Query<PayLoad> q1(db_);
	Keys saveKeys = q1.keys();
	q1.from(saveKeys);
	Conditions<PayLoad> conds1;
	conds1.name(str);
	files = q1.select(conds1).show();
	for (auto key : files) {
		fileNames.push_back(key);
		DbElement<PayLoad> elem = db_[key];
		Children c = elem.children();
		if (c.size() > 0) {
			for (unsigned i = 0; i < c.size(); i++)
				fileNames.push_back(c.at(i));
		}
	}
	std::cout << "\n\n";
	return fileNames;
}

/*<--------------------------------------------------- function to restore db from XML file ---------------------------------------------------->*/
void RepositoryCore::RepoCore::getBackDb() {
	std::cout << "\n  Reterived the previous entries of database from ServerRepoDb.xml file located at : ../ServerRepository/ServerRepoDb.xml\n";
	Persist<PayLoad> persist(db_);
	db_ = persist.restoreFromFile("../ServerRepository/ServerRepoDb.xml");
}

/*<------------------------------------function to get current check in of a file residing in repository---------------------------------------->*/
std::string RepositoryCore::RepoCore::getLastStatus(std::string fname) {
	std::string status = "";
	Keys files;
	Query<PayLoad> q1(db_);
	Keys saveKeys = q1.keys();
	q1.from(saveKeys);
	Conditions<PayLoad> conds1;
	conds1.name(fname);
	files = q1.select(conds1).keys();
	for (auto key : files)
		status = db_[key].payLoad().status();
	return status;
}

/*<----------------------------------function to get last version number of a file residing in repository--------------------------------------->*/
std::string RepositoryCore::RepoCore::getlastcount(std::string fname) {
	std::string count = "";
	Keys files;
	Query<PayLoad> q1(db_);
	Keys saveKeys = q1.keys();
	q1.from(saveKeys);
	Conditions<PayLoad> conds1;
	conds1.name(fname);
	files = q1.select(conds1).keys();
	for (auto key : files)
		count = db_[key].name().back();
	return count;
}

/*<-----------------------------------Test Stub-------------------------------------->*/
#ifdef TEST_REPOCORE
int main() {
	std::cout << "RepoCore package test stub";
	RepositoryCore::RepoCore repo;
	std::string source_path = "../ServerRepository/display/display.h"
	std::string dest_path = "../ClientRepository/Check-in/display.h"
	bool checkout_result = repo.checkout(source_path, dest_path);
	return 1;
}
#endif 


