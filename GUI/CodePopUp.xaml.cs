//////////////////////////////////////////////////////////////////////////////////////////////////////////
// CodePopUp.xaml.cs: Displays text file source in response to double-click								//
// ver 1.0																								//
// Platform         : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language         : C# & .Net Framework                                                               //-|  <----------Requirement 1---------->
// Application      : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author           : Sonal Patil, Syracuse University                                                  //
//                    spatil06@syr.edu (408)-416-6291                                                   // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------//
//Prologues - 1. public CodePopUp() - Initializes the Components placed in the window 
//-----------------------------------------------------------------------------------------------//
/* Required Files:
* ---------------
* CodePopUp.xaml
*
* Maintenance History:
* --------------------
* ver 1.0 : 19 Nov 2017
*/
using System;
using System.Windows;

namespace GUI
{
    /// <summary>
    /// Interaction logic for CodePopUp.xaml
    /// </summary>
    public partial class CodePopUp : Window
    {
        /*-------------------------------------------------< Initializes the Components placed in the window >-------------------------------------------------------*/
        public CodePopUp()
        {
            try
            {
                InitializeComponent();
            }
            catch (Exception ex) { string message = ex.Message; }

        }
    }
}

