#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// IPayLoad.h		: declare language for serializing a PayLoad instance								//
// ver 1.1																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C++ using the facilities of the standard C++ Libraries                            //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author           : Sonal Patil, Syracuse University                                                  //
//                    spatil06@syr.edu (408)-416-6291                                                   //  
// Source           : Dr. Jim Fawcett, EECS, SU                                                         // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*  Note:
*  - It is common practice to define C++ interfaces as structs with
*    pure virtual methods, including a virtual destructor.
*  - If a class derives from IPayLoad and fails to implement the
*    pure virtual method toXmlElement, the class will be abstract
*    and compilation will fail for statements that declare the PayLoad.
*  - static methods cannot be virtual, and we need fromXmlElement to
*    be static, because we may not have a PayLoad instance to invoke
*    it when deserializing.
*  - IPayLoad defers implementation to the PayLoad class.  If that
*    class fails to implement the method, builds will fail to link.
*
*  Build Command:
* ----------------
*  devenv repo.sln /rebuild debug
*
*  Maintenance History :
*  --------------------
*  ver 1.1 : 06 Mar 2018
*  - commented out few things as persiting db is not part of this project
*  ver 1.0 : 19 Feb 2018
*  - Professor Fawcett version
*/

#include "../XmlDocument/XmlElement.h"
#include <memory>
namespace NoSqlDb
{
	//commented out few things as persiting db is not part of this project but I'll need them in next project so kept here
	using Xml = std::string;
	using Sptr = std::shared_ptr<XmlProcessing::AbstractXmlElement>;

	template<typename P>
	struct IPayLoad
	{
		virtual Sptr toXmlElement() = 0;
		static P fromXmlElement(Sptr elem);
		virtual ~IPayLoad() {};
	};
}