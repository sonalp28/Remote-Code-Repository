#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Persist.h		: persist DbCore<P> to and from XML file								            //
// ver 1.0																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author           : Dr. Jim Fawcett, EECS, SU                                                         // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package defines a single Persist class that:
*  - accepts a DbCore<P> instance when constructed
*  - persists its database to an XML string
*  - creates an instance of DbCore<P> from a persisted XML string
*
*  Required Files:
*  ---------------
*  Persist.h, Persist.cpp
*  DbCore.h, DbCore.cpp
*  Query.h, Query.cpp
*  PayLoad.h
*  XmlDocument.h, XmlDocument.cpp
*  XmlElement.h, XmlElement.cpp
*
*  Maintenance History:
*  --------------------
*  ver 1.0 : 12 Feb 2018
*  - first release
*/

#include "DbCore.h"
#include "Query.h"
#include "DateTime.h"
#include "../XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement.h"
#include <string>
#include <iostream>

namespace NoSqlDb
{
	using namespace XmlProcessing;
	using Xml = std::string;
	using Sptr = std::shared_ptr<AbstractXmlElement>;

	const bool augment = true;   // do augment
	const bool rebuild = false;  // don't augment

								 /////////////////////////////////////////////////////////////////////
								 // Persist<P> class
								 // - persist DbCore<P> to XML string

	template<typename P>
	class Persist
	{
	public:
		Persist(DbCore<P>& db);
		virtual ~Persist() {}
		static void identify(std::ostream& out = std::cout);
		Persist<P>& shard(const Keys& keys);
		Persist<P>& addShardKey(const Key& key);
		Persist<P>& removeShard();
		Xml toXml();
		bool saveToFile(const std::string& fileSpec);
		NoSqlDb::DbCore<NoSqlDb::PayLoad> restoreFromFile(const std::string& fileSpec);
		bool fromXml(const Xml& xml, bool augment = true);  // will clear and reload db if augment is false !!!
	private:
		DbCore<P>& db_;
		Keys shardKeys_;
		bool containsKey(const Key& key);
		void toXmlRecord(Sptr pDb, const Key& key, DbElement<P>& dbElem);
	};
	//----< constructor >------------------------------------------------

	template<typename P>
	Persist<P>::Persist(DbCore<P>& db) : db_(db) {}


	//----< saves db contents to file, using save >--------------------
	template<typename Data>
	bool Persist<Data>::saveToFile(const std::string& fileSpec)
	{
		std::ofstream out(fileSpec);
		if (!out.good())
			return false;
		Persist<Data> persist(db_);
		Xml xml = persist.toXml();
		out << xml;
		out.close();
		return true;
	}

	//----< restores db contents from file, using restore >------------
	template<typename Data>
	NoSqlDb::DbCore<NoSqlDb::PayLoad> Persist<Data>::restoreFromFile(const std::string& fileSpec)
	{
		std::ifstream in(fileSpec);
		if (!in.good())
		{
			std::cout << "\n  File doesn't exsist or Failed to open file";
			return db_;
		}
		Xml xml;
		// build XML string from file

		while (in.good())
		{
			char ch = in.get();
			// This code removes whitespace from XML contents 
			if (!in.good())
				break;
			xml += ch;
		}
		in.close();
		fromXml(xml);
		return db_;
	}

	//----< show file name >---------------------------------------------

	template<typename P>
	void Persist<P>::identify(std::ostream& out)
	{
		out << "\n  \"" << __FILE__ << "\"";
	}
	//----< add key to shard collection >--------------------------------
	/*
	* - when sharding, a db record is persisted if, and only if, its key
	is contained in the shard collection
	*/
	template<typename P>
	Persist<P>& Persist<P>::addShardKey(const Key& key)
	{
		shardKeys_.push_back(key);
		return *this;
	}
	//----< does the shard key collection contain key? >-----------------

	template<typename P>
	bool Persist<P>::containsKey(const Key& key)
	{
		Keys::iterator start = shardKeys_.begin();
		Keys::iterator end = keys_.end();
		return std::find(start, end, key) != end;
	}
	//----< set the shardKeys collection >-------------------------------

	template<typename P>
	Persist<P>& Persist<P>::shard(const Keys& keys)
	{
		shardKeys_ = keys;
		return *this;
	}
	//----< empty the shardKeys collection >-----------------------------

	template<typename P>
	Persist<P>& Persist<P>::removeShard()
	{
		shardKeys_.clear();
	}
	//----< persist database record to XML string >----------------------

	template<typename P>
	void Persist<P>::toXmlRecord(Sptr pDb, const Key& key, DbElement<P>& dbElem)
	{
		Sptr pRecord = makeTaggedElement("dbRecord");
		pDb->addChild(pRecord);
		Sptr pKey = makeTaggedElement("key", key);
		pRecord->addChild(pKey);

		Sptr pValue = makeTaggedElement("value");
		pRecord->addChild(pValue);
		Sptr pName = makeTaggedElement("name", dbElem.name());
		pValue->addChild(pName);
		Sptr pDescrip = makeTaggedElement("description", dbElem.descrip());
		pValue->addChild(pDescrip);

		Sptr pChildren = makeTaggedElement("children");
		pValue->addChild(pChildren);
		for (auto child : dbElem.children())
		{
			Sptr pChild = makeTaggedElement("child", child);
			pChildren->addChild(pChild);
		}

		Sptr pPayLoad = dbElem.payLoad().toXmlElement();
		pValue->addChild(pPayLoad);
	}
	//----< persist, possibly sharded, database to XML string >----------
	/*
	* - database is sharded if the shardKeys collection is non-empty
	*/
	template<typename P>
	Xml Persist<P>::toXml()
	{
		Sptr pDb = makeTaggedElement("db");
		pDb->addAttrib("type", "fromQuery");
		Sptr pDocElem = makeDocElement(pDb);
		XmlDocument xDoc(pDocElem);

		if (shardKeys_.size() > 0)
		{
			for (auto key : shardKeys_)
			{
				DbElement<P> elem = db_[key];
				toXmlRecord(pDb, key, elem);
			}
		}
		else
		{
			for (auto item : db_)
			{
				toXmlRecord(pDb, item.first, item.second);
			}
		}
		std::string xml = xDoc.toString();
		return xml;
	}
	//----< retrieve database from XML string >--------------------------
	/*
	* - Will clear db and reload if augment is false
	*/
	template<typename P>
	bool Persist<P>::fromXml(const Xml& xml, bool augment)
	{
		XmlProcessing::XmlDocument doc(xml);
		if (!augment)
			db_.dbStore().clear();
		std::vector<Sptr> pRecords = doc.descendents("dbRecord").select();
		for (auto pRecord : pRecords)
		{
			Key key;
			DbElement<P> elem;
			P pl;

			std::vector<Sptr> pChildren = pRecord->children();
			for (auto pChild : pChildren)
			{
				if (pChild->tag() == "key")
				{
					key = pChild->children()[0]->value();
				}
				else
				{
					std::vector<Sptr> pValueChildren = pChild->children();
					std::string valueOfTextNode;
					for (auto pValueChild : pValueChildren)
					{
						std::string tag = pValueChild->tag();
						if (pValueChild->children().size() > 0)
							valueOfTextNode = pValueChild->children()[0]->value();
						else
							valueOfTextNode = "";

						if (tag == "name")
						{
							elem.name(valueOfTextNode);
						}
						else if (tag == "description")
						{
							elem.descrip(valueOfTextNode);
						}
						else if (tag == "dateTime")
						{
							elem.dateTime(valueOfTextNode);
						}
						else if (tag == "children")
						{
							for (auto pChild : pValueChild->children())
							{
								valueOfTextNode = pChild->children()[0]->value();
								elem.children().push_back(valueOfTextNode);
							}
						}
						else if (tag == "payload")
						{
							pl = PayLoad::fromXmlElement(pValueChild);
							elem.payLoad(pl);
						}
					}
				}
				db_[key] = elem;
			}
		}
		return true;
	}
}
