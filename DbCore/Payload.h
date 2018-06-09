#ifndef PAYLOAD_H
#define PAYLOAD_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// PayLoad.h		: application defined payload														//
// ver 1.2																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author           : Sonal Patil, Syracuse University                                                  //
//                    spatil06@syr.edu (408)-416-6291                                                   //  
// Source           : Dr. Jim Fawcett, EECS, SU                                                         // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*  Public Interface:
*  -------------------
*  This package provides a single class, PayLoad:
*  - holds a payload string and vector of categories
*  - provides means to set and access those values
*  - provides methods used by Persist<PayLoad>:
*    - Sptr toXmlElement();
*    - static PayLoad fromXmlElement(Sptr elem);
*  - provides a show function to display PayLoad specific information
*  - PayLoad processing is very simple, so this package contains only
*    a header file, making it easy to use in other packages, e.g.,
*    just include the PayLoad.h header.
*
*  Required Files:
*  ---------------
*    PayLoad.h, PayLoad.cpp - application defined package
*    DbCore.h, DbCore.cpp
*
*  Build Command:
* ----------------
*  devenv repo.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.2 : 06 Mar 2018
*  - changed the set width in the show functions of Payload class [as the payload value lengths of this database are large]
*  ver 1.1 : 19 Feb 2018
*  - added inheritance from IPayLoad interface
*  Ver 1.0 : 10 Feb 2018
*  - first release
*
*/

#include <string>
#include <vector>
#include <iostream>
#include "DbCore.h"
#include "IPayLoad.h"
#include "../XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement.h"

///////////////////////////////////////////////////////////////////////
// PayLoad class provides:
// - a std::string value which, in Project #2, will hold a file path
// - a vector of string categories, which for Project #2, will be 
//   Repository categories
// - methods used by Persist<PayLoad>:
//   - Sptr toXmlElement();
//   - static PayLoad fromXmlElement(Sptr elem);


namespace NoSqlDb
{
	using Key = std::string;
	using Keys = std::vector<Key>;
	using Children = std::vector<Key>;
	using Parents = std::vector<Key>;


	class PayLoad : public IPayLoad<PayLoad>
	{
	public:
		PayLoad() = default;
		PayLoad(const std::string& val) : value_(val) {}
		static void identify(std::ostream& out = std::cout);
		PayLoad& operator=(const std::string& val)
		{
			value_ = val;
			return *this;
		}
		operator std::string() { return value_; }

		std::string value() const { return value_; }
		std::string& value() { return value_; }
		void value(const std::string& value) { value_ = value; }

		std::string author() const { return author_; }
		std::string& author() { return author_; }
		void author(const std::string& author) { author_ = author; }

		std::string status() const { return status_; }
		std::string& status() { return status_; }
		void status(const std::string& status) { status_ = status; }

		std::string path() const { return path_; }
		std::string& path() { return path_; }
		void path(const std::string& path) { path_ = path; }

		std::vector<std::string>& categories() { return categories_; }
		std::vector<std::string> categories() const { return categories_; }

		bool hasCategory(const std::string& cat)
		{
			return std::find(categories().begin(), categories().end(), cat) != categories().end();
		}

		Sptr toXmlElement();
		static PayLoad fromXmlElement(Sptr elem);

		static void showPayLoadHeaders(std::ostream& out = std::cout);
		static void showElementPayLoad(NoSqlDb::DbElement<PayLoad>& elem, std::ostream& out = std::cout);
		static void showDb(NoSqlDb::DbCore<PayLoad>& db, std::ostream& out = std::cout);
	private:
		std::string value_;
		std::string author_;
		std::string status_;
		std::string path_;
		std::vector<std::string> categories_;
	};

	//----< show file name >---------------------------------------------

	inline void PayLoad::identify(std::ostream& out)
	{
		out << "\n  \"" << __FILE__ << "\"";
	}
	////----< create XmlElement that represents PayLoad instance >---------
	///*
	//* - Required by Persist<PayLoad>
	//*/
	inline Sptr PayLoad::toXmlElement()
	{
		Sptr sPtr = XmlProcessing::makeTaggedElement("payload");
		XmlProcessing::XmlDocument doc(makeDocElement(sPtr));
		Sptr sPtrAuth = XmlProcessing::makeTaggedElement("author", author_);
		sPtr->addChild(sPtrAuth);
		Sptr sPtrStatus = XmlProcessing::makeTaggedElement("status", status_);
		sPtr->addChild(sPtrStatus);
		Sptr sPtrPath = XmlProcessing::makeTaggedElement("path", path_);
		sPtr->addChild(sPtrPath);
		Sptr sPtrCats = XmlProcessing::makeTaggedElement("categories");
		sPtr->addChild(sPtrCats);
		for (auto cat : categories_)
		{
			Sptr sPtrCat = XmlProcessing::makeTaggedElement("category", cat);
			sPtrCats->addChild(sPtrCat);
		}
		return sPtr;
	}
	////----< create PayLoad instance from XmlElement >--------------------
	///*
	//* - Required by Persist<PayLoad>
	//*/
	inline PayLoad PayLoad::fromXmlElement(Sptr pElem)
	{
		PayLoad pl;
		std::string author = "";
		std::string status = "";
		std::string path = "";
		for (auto pChild : pElem->children())
		{
			std::string tag = pChild->tag();
			std::string val = pChild->children()[0]->value();
			if (tag == "author")
			{
				author = val;
				pl.author(val);
			}
			if (tag == "status")
			{
				status = val;
				pl.status(val);
			}
			if (tag == "path")
			{
				path = val;
				pl.path(val);
			}
			if (tag == "categories")
			{
				std::vector<Sptr> pCategories = pChild->children();
				for (auto pCat : pCategories)
				{
					pl.categories().push_back(pCat->children()[0]->value());
				}
			}
		}
		pl.value(author + " Status:" + status + " " + path);
		return pl;
	}
	/////////////////////////////////////////////////////////////////////
	// PayLoad display functions

	inline void PayLoad::showPayLoadHeaders(std::ostream& out)
	{
		out << "\n  ";
		out << std::setw(15) << std::left << "Name";
		out << std::setw(75) << std::left << "Payload Value";
		out << std::setw(15) << std::left << "Categories";
		out << "\n  ";
		out << std::setw(15) << std::left << "-------------";
		out << std::setw(75) << std::left << "--------------------------------------------------------------------------";
		out << std::setw(15) << std::left << "---------------";
	}


	inline void PayLoad::showElementPayLoad(NoSqlDb::DbElement<PayLoad>& elem, std::ostream& out)
	{
		out << "\n  ";
		out << std::setw(15) << std::left << elem.name().substr(0, 13);
		out << std::setw(75) << std::left << elem.payLoad().value().substr(0, 75);
		for (auto cat : elem.payLoad().categories())
		{
			out << cat << " ";
		}
	}

	inline void PayLoad::showDb(NoSqlDb::DbCore<PayLoad>& db, std::ostream& out)
	{
		showPayLoadHeaders(out);
		for (auto item : db)
		{
			NoSqlDb::DbElement<PayLoad> temp = item.second;
			PayLoad::showElementPayLoad(temp, out);
		}
	}
}
#endif
