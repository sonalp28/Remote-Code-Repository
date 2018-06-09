//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs   : Repository GUI client built using Windows Presentation Foundation 				//
// ver 1.1																								    //
// Platform             : Dell Inspiron 13 - Windows 10, Visual Studio 2017                                 //-|_ 
// Language             : C# & .Net Framework                                                               //-|  <----------Requirement 1---------->
// Application          : Project 4 [Remote Code Repository] Object Oriented Design CSE-687 Spring'18       //
// Author               : Sonal Patil, Syracuse University                                                  //
//                        spatil06@syr.edu (408)-416-6291                                                   // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Package operation:
 * --------------------
 * This package is used to have a graphical user interfcae for the repository test bed where client can access and perform basic functionality on server repository
 * This package also contains a code-pop-up wondow code which helps client to see the file contents by showing it in poped-up window
 * 
 * Public interfcae:
 * --------------------
 * public MainWindow() - Initializes the Components placed in the window and messages of GUI on the command prompt
 * private void Window_Loaded(object sender, RoutedEventArgs e) - start GUI and initialize tabs in the GUI
 * private void demo_otherclient() - function to demonstarte multi client requirement with a demo check-in
 * public void showOnCommandPrompt() - Use of Command prompt to display GUI information and Project Requirement Demo Info
 * private List<string> getFiles(string path) - function that returns cpp & h files present at given location
 * private void demoConnect() - function to demonstarte connect functionality [automated test unit for connect]
 * private void setupServerEndPoint() - for user interaction with GUI this function sets default value of server machine & port address
 * private void addConnectMsg(string msg) - function that displays connect successful message in message textbox
 * private void processMessages() - process incoming messages on child thread
 * private void connect(object sender, RoutedEventArgs e) - Function that Connects client to the server on given machine & Port address
 * private void postConnectMsg() - function that posts a connect to server message to server with details
 * private void loadDispatcher() - load all dispatcher processing
 * private void DispatcherLoadConnect() - loads getConnectMsg processing into dispatcher dictionary
 * private void DispatcherLoadCatBrowse() - loads getCatBrowseMsg processing into dispatcher dictionary
 * private void DispatcherLoadCatFileBrowse() - loads getCatFileBrowseMsg processing into dispatcher dictionary
 * private void DispatcherLoadQueryBrowse() - loads getQueryBrowseMsg processing into dispatcher dictionary
 * private void DispatcherLoadDependent() - loads getDependent processing into dispatcher dictionary
 * private void DispatcherLoadCheckIn() - loads getCheckIn processing into dispatcher dictionary
 * private void DispatcherLoadCheckOut() - loads getCheckOut processing into dispatcher dictionary
 * private void DispatcherLoadViewFile() - loads getViewFileMsg processing into dispatcher dictionary
 * private void DispatcherLoadViewMetadata() - loads getMetadataMsg processing into dispatcher dictionary
 * private void addClientProc(string key, Action<CsMessage> clientProc) - adds client processing for message with key
 * private void demoBrowse() - function to demonstarte browse functionality [automated test unit for browse]
 * private void addCatBrowseMsg(string msg) - function that displays browse successful message in message box
 * private void addCatFileMsg(string msg) - function that displays browse successful message in message box
 * private void addQueryMsg(string msg) - function that displays browse successful message in message box
 * private void fillserverBrowseLB() - function to fill the server repo listbox with files present at server side
 * private void CatbrowseComboBox_Loaded(object sender, RoutedEventArgs e) - function to load the catogries into category combo-box
 * private void CatbrowseComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e) - function to get the selected category in the category combo-box
 * private void ServerfilesLB_MouseDoubleClick(object sender, MouseButtonEventArgs e) - change from categories to files view
 * private void serverbackButton_Click(object sender, RoutedEventArgs e) - back button that again shows the categories/folders in server repository
 * private void showServer_Click(object sender, RoutedEventArgs e) - function that do the functionality of posting a browse msg to server
 * private void showCatg_Click(object sender, RoutedEventArgs e) - function that do the functionality of posting a browse msg to server
 * private void showQuery_Click(object sender, RoutedEventArgs e) - function that do the functionality of posting a browse msg to server
 * private void postCatBrowseMsg() - function that posts a catbrowse message to server with details
 * private void postCatFileMsg(string catgName) - function that posts a catbrowse message to server with details
 * private void postQueryBrowseMsg(string catgName) - function that posts a querybrowse message to server with details
 * private void demoChkInCase1() - function to demonstarte check-in functionality [automated test unit for check-in]
 * private void demoChkInCase2() - function to demonstarte check-in functionality [automated test unit for check-in]
 * private void demoChkInCase3() - function to demonstarte check-in functionality [automated test unit for check-in]
 * private void demoChkInCase4() - function to demonstarte check-in functionality [automated test unit for check-in]
 * private void addCheckinMsg(string msg) - function that displays check-in successful message in status bar
 * private void browseFile_Click(object sender, RoutedEventArgs e) - function to allow user to browse files to check-in
 * private void filldstnDir() - function to fill directories [to select it as the destination path]
 * private void dstn_SelectionChanged(object sender, SelectionChangedEventArgs e) - function that gets a value selected for destination path list box
 * private void ComboBox_Loaded(object sender, RoutedEventArgs e) - function to load the items into combo-box
 * private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e) - function to get the value of item selected in the combo-box which author of check-in
 * private void CatComboBox_Loaded(object sender, RoutedEventArgs e) - function to load the catogries into category combo-box
 * private void CatComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e) - function to get the selected category in the category combo-box
 * public void CreateCheckBoxList() - function that creates checkbox list for dependency children to add for current check-in
 * public void UpdateCheckBoxList(string fileName) - function that updates checkbox list for dependency children to add for current check-in 
 * private void CheckBoxZone_Checked(object sender, RoutedEventArgs e) - function that shows the selected checkbox items from the listbox into a textbox
 * private void ChkInButton_Click(object sender, RoutedEventArgs e) - function that performs the functionality of check-in on button click
 * private void postCheckInMsg() - function that posts a check in message to server with check-in details
 * private void demoChkOutCase1() -  function to demonstarte check-out functionality [automated test unit for check-out]
 * private void demoChkOutCase2() -  function to demonstarte check-out functionality [automated test unit for check-out]
 * private void demoChkOutCase3() -  function to demonstarte check-out functionality [automated test unit for check-out]
 * private void addCheckOutMsg(string msg) - function that displays check-out successful message in message box
 * private void fillCheckoutFilesLB() - This listbox shows the categories/folders currently present in the server repository
 * private void ChkOutFilesListBox_MouseDoubleClick(object sender, MouseButtonEventArgs e) - change from categories to files view
 * private void backButton_Click(object sender, RoutedEventArgs e) - back button that again shows the categories/folders in server repository
 * private void ChkOutButton_Click(object sender, RoutedEventArgs e) - function which performs check out functionality on check out button click
 * private void dependentButton_Click(object sender, RoutedEventArgs e) - function which performs dependency add functionality on dependent button
 * private void showDependent(string files) - function that shows the dependent files in the listbox
 * private void dpendent_SelectionChanged(object sender, SelectionChangedEventArgs e) - function that adds selected dependent file names in the textbox below
 * private void postDependMsg(string ckoutfName) - function that posts a getdependent message to server with details
 * private void postCheckOutMsg() - function that posts a check out message to server with check-out details
 * private void demoViewFile() - function to demonstarte view file content functionality [automated test unit for view file content]
 * private void addViewFileMsg(string contents) - function that displays view file message in message textbox
 * private void fillFoldinRepoLB() - This listbox shows the categories/folders currently present in the server repository
 * private void fold_MouseDoubleClick(object sender, MouseButtonEventArgs e) - Shows content of selected file from ListBox#3 into CodePopUp window 
 * private void fillFilesinRepoLB(string folder) - This listbox shows the files present for given category present in the server repository
 * private void files_MouseDoubleClick(object sender, MouseButtonEventArgs e) - Shows content of selected file from ListBox#3 into CodePopUp window
 * private void postViewFileMsg() - function that posts a view file message to server with details
 * private void demoViewMetadat() - function to demonstarte view metadata functionality [automated test unit for view metadata]
 * private void postgetMetadataMsg() - function that posts view metadata message to server with details
 * private void MDataButton_Click(object sender, RoutedEventArgs e) - function that posts view metadata message to server with details on click of view metadata button
 * private void showMetadata(string data) - Function that puts the meta data into a flow document table 
 * private void connectTabClick (object sender, MouseButtonEventArgs e) - Functions to display message for every tab into it's status bar
 * private void browseTabClick (object sender, MouseButtonEventArgs e) - Functions to display message for every tab into it's status bar
 * private void checkinTabClick (object sender, MouseButtonEventArgs e) - Functions to display message for every tab into it's status bar
 * private void checkoutTabClick (object sender, MouseButtonEventArgs e) - Functions to display message for every tab into it's status bar
 * private void viewfileTabClick (object sender, MouseButtonEventArgs e) - Functions to display message for every tab into it's status bar
 * private void viewMetadataTabClick (object sender, MouseButtonEventArgs e) - Functions to display message for every tab into it's status bar
 * 
 * Required files:
 * --------------------
 * MainWindow.xaml,
 * CodePopUp.xaml, CodePopUp.xaml.cs
 * 
 * Build Command:
 * --------------------
 * devenv repo.sln /rebuild debug
 *
 * Maintance history:
 * --------------------
 * ver 1.1 : 5/01/2018
 * - second release - modified & added some new functionality to fullfill project 4 requirements
 * ver 1.0 : 4/10/2018
 *  - first release
 *
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.IO;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Collections.ObjectModel;
using System.Threading;
using MsgPassingCommunication;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //variavles declared for connect tab
        private Translater translater = new Translater();
        int client_address = 8080;
        int client_number = 1;
        private CsEndPoint endPoint_, server_endpoint;
        private Thread rcvThrd = null;
        private bool connection_status = false;
        private Dictionary<string, Action<CsMessage>> dispatcher_ = new Dictionary<string, Action<CsMessage>>();

        //variables declared for browse tab
        bool serverBrowsingOn = false;
        bool catBrowsingOn = false;
        bool queryBrowsingOn = false;
        bool isdemo = false;
        string qfname = ""; string qcatname = ""; string qdependname = ""; string qversion = "";
        bool catFileBrowsingOn = false;

        //variables declared for check-in tab
        CheckBox chkZone;
        private string CkInfilename, author, dstn_path, childName, descrp, CkInstatus, category;
        private string client_path = @"../../../ClientRepository/Check-in";
        public class BoolStringClass { public string TheText { get; set; } }     //class defined for the check-box items in the list box
        public ObservableCollection<BoolStringClass> TheList { get; set; } = new ObservableCollection<BoolStringClass>();

        //variables declared for check-out tab
        private string server_path = @"../../../ServerRepository";
        private string checkout_file = "";
        private string dependent_file = "";

        //variables declared for view-file tab
        private string category_name = "";
        private string file_toOpen = "";


        /////////////////////////////////////////////////////////////////
        // Initialize Client Repository

        /*<-------------------- Initializes the Components placed in the window and messages of GUI on the command prompt --------------------------->*/
        public MainWindow()
        {
            try
            {
                InitializeComponent();

                /*<---------remove comments of this part if you want to check functionality of GUI with user click & not with window loaded method----------->*/
                //setupServerEndPoint();
                //filldstnDir();
                //fillCheckoutFilesLB();
                //fillFoldinRepoLB();
                //CreateCheckBoxList();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "  |  If you want to try/test the functionality of GUI please comment out view lines in MainWindow() function");
            }
            
        }
        
        /*<--------------------------------------------- start GUI and initialize tabs in the GUI -------------------------------------------------->*/
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            try{
                string[] args = Environment.GetCommandLineArgs();
                client_address = Int32.Parse(args[1]);
                client_number = Int32.Parse(args[2]);                
                showOnCommandPrompt();
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nRequirement 7"); Console.ResetColor();
                Console.WriteLine("Started automated unit test suite that demonstrates requirements & runs without user intervention when application starts.");
                Console.WriteLine("Note : To handle GUI with human interaction Please follow given 2 steps : ");
                Console.WriteLine("          1. Go to Main.Window.xaml.cs & comment out some functions in Window_Loaded function");
                Console.WriteLine("          2. Remove comments of the commented part in MainWindow()");
                /*<---------comment out this part if you want to check functionality of GUI with user click & not with window loaded method----------->*/
                if (client_number == 1)
                {
                    //Connect to Server tab
                    demoConnect();
                    //initializing browse tab with displaying server repository structure
                    fillserverBrowseLB();
                    // Check-In Tab
                    demoChkInCase1();       //initial check-in
                    demoChkInCase2();       //last check-in status close so doing new check-in & appending version number
                    demoChkInCase3();       //dependency open so doing checkin with status as pending
                    demoChkInCase4();       //last checkin status open so doing the checkin in the open version only
                    // Browse Tab - demonstarting displaying of categories & their files with opening file contents on double click
                    demoBrowse();
                    //// CheckOut Tab
                    demoChkOutCase1();      //check-out without dependent files 
                    demoChkOutCase2();      //check-out dependent files present but user doesn't want to checkout dependent files
                    demoChkOutCase3();      //check-out without dependent files 
                    // View-File Tab
                    demoViewFile();
                    // View-Metadata Tab
                    demoViewMetadata();
                }
                if (client_number > 1)
                {
                    Console.WriteLine("                     Demonstrating Multiple Clients ");
                    demoConnect();
                    filldstnDir();
                    fillCheckoutFilesLB();
                    fillFoldinRepoLB();
                    CreateCheckBoxList();
                    demo_otherclient();     //demo for multiple clients requirement 
                }
            }
            catch (Exception ex) {
                MessageBox.Show(ex.Message);  
            }            
        }

        /*<--------------------------------- function to demonstarte multi client requirement with a demo check-in ---------------------------------->*/
        private void demo_otherclient()
        {
            try
            {
                filldstnDir();
                CreateCheckBoxList();
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nCheck-in Test Case #1"); Console.ResetColor();
                Console.WriteLine("\n Check-in demonstartion by another client");
                Console.WriteLine("====================================================================================================================");
                postCheckInMsg("write.cpp", "repo-demo", "Admin", "I/O", "close", server_path + "/write", "");
                CkInfilename = selectedCkInFiles.Text = "write.cpp";
                author = "Admin";
                dstn_path = dstnpath.Text = server_path + "/write";
                childName = child.Text = "";
                descrp = descr.Text = "repo-demo";
                close.IsChecked = true;
                open.IsChecked = false;
                CkInstatus = "close";
                Console.WriteLine("====================================================================================================================");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "  | Please enter all the information");
            }
        }
        
        /*---------------------------< Use of Command prompt to display GUI information and Project Requirement Demo Info >---------------------------*/
        public void showOnCommandPrompt()
        {
            Console.Title = "Client Repository [GUI Console] - " + client_address.ToString();            
            Console.WriteLine("-----------------------------------------------------------------------------------------------------------------------\n");
            Console.WriteLine("                                           Graphical User Interface Using WPF                                          \n"); //<---------Requirement 6
            Console.WriteLine("-----------------------------------------------------------------------------------------------------------------------\n");
            Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("Requirement 1[b]"); Console.ResetColor();
            Console.WriteLine("\nYou may also use C#, the .Net Windows Presentation Foundation framework, & C++/CLI for graphical part of each Client.\n");
            Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("Requirement 3"); Console.ResetColor();
            Console.WriteLine("Shall provide a Client graphical user interface that supports tabs for the views: [Status - Started]\n");
            Console.ForegroundColor = ConsoleColor.DarkBlue; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("GUI Info - \n"); Console.ResetColor();
            Console.WriteLine("* Connection to Servers tab  - Shows funtionality for connection to Server Repository \n");
            Console.WriteLine("* Check-In tab               - Shows funtionality for check-in file/s into Server Repository \n");
            Console.WriteLine("* Check-Out tab              - Shows funtionality for check-out file/s from Server Repository to Client Repository \n");
            Console.WriteLine("* Browse tab                 - Shows funtionality for browsing file/s in Server Repository \n");
            Console.WriteLine("* View-File tab              - Shows funtionality for viewing content of file/s in new popped-up window \n");
            Console.WriteLine("* View-Metadata tab          - Shows funtionality for viewing metadata stored in NoSQLdb for all checkin files \n");
        }

        /*<------------------------------------- function that returns cpp & h files present at given location --------------------------------------->*/
        private List<string> getFiles(string path)
        {
            List<string> files = null;
            try
            {                
                List<string> cpp_files = new List<string>(Directory.GetFiles(path, "*.cpp*"));
                List<string> h_files = new List<string>(Directory.GetFiles(path, "*.h*"));
                var result = cpp_files.Concat(h_files);
                files = result.ToList();                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + " | Files don't Present at given location");
            }
            return files;
        }



        //---------------------------------------------------------------------------------------------------
        //Connect-To-Server tab                                                                             |
        //---------------------------------------------------------------------------------------------------
        /*<------------------------------ function to demonstarte connect functionality [automated test unit for connect] ------------------------------>*/
        private void demoConnect()
        {
            // client side machine & port address initilization
            try
            {
                string client_ma = "localhost";
                int client_pa = client_address;
                endPoint_ = new CsEndPoint();
                endPoint_.machineAddress = Client_Machine_Addr.Text = client_ma;
                endPoint_.port = client_pa;
                Client_Port_Addr.Text = client_pa.ToString();
                //start comm
                translater.listen(endPoint_);
                
                // server side machine & port address initilization
                string server_ma = "localhost";
                int server_pa = 8082;
                server_endpoint = new CsEndPoint();
                server_endpoint.machineAddress = Server_Machine_Addr.Text = server_ma;
                server_endpoint.port = server_pa;
                Server_Port_Addr.Text = server_pa.ToString();
                Server_Machine_Addr.IsEnabled = false;
                Server_Port_Addr.IsEnabled = false;

                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nRequirement 2[a]"); Console.ResetColor();
                Console.WriteLine("<-------------------------- [Asynchronous Message-Passing Communication : Started] -------------------------->");
                Console.WriteLine("\n    Client listening at -> " + client_ma + ":" + client_pa + "  |  " + "Server at -> " + server_ma + ":" + server_pa);

                processMessages();
                loadDispatcher();
                postConnectMsg();

            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        /*<-------------------- for user interaction with GUI this function sets default value of server machine & port address ---------------------->*/
        private void setupServerEndPoint()
        {
            Server_Machine_Addr.Text = "localhost";
            Server_Machine_Addr.IsEnabled = false;
            Server_Port_Addr.Text = "8082";
            Server_Port_Addr.IsEnabled = false;
        }
        
        /*<--------------------------------- function that displays connect successful message in message textbox ------------------------------------>*/
        private void addConnectMsg(string msg)
        {
            connection_status = true;
            Comm_Messages.Text += "Message : " + msg;
        }

        /*<----------------------------------------------- process incoming messages on child thread ------------------------------------------------->*/
        private void processMessages()
        {
            ThreadStart thrdProc = () => {
                while (true)
                {
                    CsMessage msg = translater.getMessage();
                    Console.WriteLine("\n Received message: from " + msg.value("from"));
                    msg.show();
                    string msgId = msg.value("command");
                    if (dispatcher_.ContainsKey(msgId))
                        dispatcher_[msgId].Invoke(msg);
                }
            };
            rcvThrd = new Thread(thrdProc);
            rcvThrd.IsBackground = true;
            rcvThrd.Start();
        }
        
        /*<------------------------------ Function that Connects client to the server on given machine & Port address -------------------------------->*/
        private void connect(object sender, RoutedEventArgs e)
        {
            try
            {
                // client side machine & port address initilization
                endPoint_ = new CsEndPoint();
                endPoint_.machineAddress = Client_Machine_Addr.Text;
                endPoint_.port = client_address = Int32.Parse(Client_Port_Addr.Text);
                Console.Title = "Client Repository [GUI Console] - " + client_address.ToString();
                //start comm
                translater.listen(endPoint_);

                // server side machine & port address initilization
                server_endpoint = new CsEndPoint();
                server_endpoint.machineAddress = Server_Machine_Addr.Text = "localhost";
                server_endpoint.port = Int32.Parse(Server_Port_Addr.Text = "8082");

                processMessages();
                loadDispatcher();
                if (endPoint_.port != 8082 && server_endpoint.port == 8082)
                {
                    Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nRequirement 2[a]"); Console.ResetColor();
                    Console.WriteLine("<-------------------------- [Asynchronous Message-Passing Communication : Started] -------------------------->");
                    Console.WriteLine("\n    Client listening at -> " + Client_Machine_Addr.Text + ":" + Client_Port_Addr.Text + "  |  " + "Server at -> " + Server_Machine_Addr.Text + ":" + Server_Port_Addr.Text);
                    postConnectMsg();
                }
                else
                    MessageBox.Show("Please enter Server Port Address = 8082");
                
            }
            catch (Exception ex)
            {
                MessageBox.Show("Please fill all the information correctly");
                string message = ex.Message;
            }
            
        }

        /*<------------------------------------ function that posts a connect to server message to server with details --------------------------------------->*/
        private void postConnectMsg()
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getConnectMsg");
            msg.add("message", "connect to server " + Server_Port_Addr.Text);
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }



        /*<-------------------------------------------------------- load all dispatcher processing --------------------------------------------------->*/
        private void loadDispatcher()
        {
            try
            {
                DispatcherLoadConnect();
                DispatcherLoadCatBrowse();
                DispatcherLoadCatFileBrowse();
                DispatcherLoadQueryBrowse();
                DispatcherLoadCheckIn();
                DispatcherLoadDependent();
                DispatcherLoadCheckOut();
                DispatcherLoadViewFile();
                DispatcherLoadViewMetadata();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }            
        }
        
        /*<------------------------------------------ loads getConnectMsg processing into dispatcher dictionary --------------------------------------->*/
        private void DispatcherLoadConnect()
        {
            Action<CsMessage> getConnectMsg = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("message"))
                    {
                        Action<string> doConnect = (string msg) =>
                        {
                            addConnectMsg(msg);
                        };
                        Dispatcher.Invoke(doConnect, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getConnectMsg", getConnectMsg);
        }

        /*<------------------------------------------ loads getCatBrowseMsg processing into dispatcher dictionary ------------------------------------------->*/
        private void DispatcherLoadCatBrowse()
        {
            Action<CsMessage> getCatBrowseMsg = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("message"))
                    {
                        Action<string> doBrowse = (string msg) =>
                        {
                            addCatBrowseMsg(msg);
                        };
                        Dispatcher.Invoke(doBrowse, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getCatBrowseMsg", getCatBrowseMsg);
        }

        /*<------------------------------------------ loads getCatFileBrowseMsg processing into dispatcher dictionary ------------------------------------------->*/
        private void DispatcherLoadCatFileBrowse()
        {
            Action<CsMessage> getCatFileMsg = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("message"))
                    {
                        Action<string> doBrowse = (string msg) =>
                        {
                            addCatFileMsg(msg);
                        };
                        Dispatcher.Invoke(doBrowse, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getCatFileMsg", getCatFileMsg);
        }

        /*<------------------------------------------ loads getQueryMsg processing into dispatcher dictionary ------------------------------------------->*/
        private void DispatcherLoadQueryBrowse()
        {
            Action<CsMessage> getQueryMsg = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("message"))
                    {
                        Action<string> doBrowse = (string msg) =>
                        {
                            addQueryMsg(msg);
                        };
                        Dispatcher.Invoke(doBrowse, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getQueryMsg", getQueryMsg);
        }

        /*<------------------------------------------ loads getCheckIn processing into dispatcher dictionary ------------------------------------------->*/
        private void DispatcherLoadCheckIn()
        {
            Action<CsMessage> getCheckinMsg = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("message"))
                    {
                        Action<string> doCheckin = (string msg) =>
                        {
                            addCheckinMsg(msg);
                        };
                        Dispatcher.Invoke(doCheckin, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getCheckinMsg", getCheckinMsg);
        }

        /*<------------------------------------------ loads getDependent processing into dispatcher dictionary ------------------------------------------->*/
        private void DispatcherLoadDependent()
        {
            Action<CsMessage> getDependent = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("dependentFiles"))
                    {
                        Action<string> doCheckout = (string msg) =>
                        {
                            showDependent(msg);
                        };
                        Dispatcher.Invoke(doCheckout, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getDependent", getDependent);
        }

        /*<------------------------------------------ loads getCheckOut processing into dispatcher dictionary ------------------------------------------->*/
        private void DispatcherLoadCheckOut()
        {
            Action<CsMessage> getCheckOutMsg = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("message"))
                    {
                        Action<string> doCheckout = (string msg) =>
                        {
                            addCheckOutMsg(msg);
                        };
                        Dispatcher.Invoke(doCheckout, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getCheckOutMsg", getCheckOutMsg);
        }

        /*<------------------------------------ loads getViewFileMsg processing into dispatcher dictionary ------------------------------------------->*/
        private void DispatcherLoadViewFile()
        {
            Action<CsMessage> getViewFileMsg = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("message"))
                    {
                        Action<string> doViewFile = (string msg) =>
                        {
                            addViewFileMsg(msg);
                        };
                        Dispatcher.Invoke(doViewFile, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getViewFileMsg", getViewFileMsg);
        }

        /*<----------------------------------- loads getMetadataMsg processing into dispatcher dictionary ------------------------------------------->*/
        private void DispatcherLoadViewMetadata()
        {
            Action<CsMessage> getMetadataMsg = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("dbdata"))
                    {
                        Action<string> doViewMetadat = (string msg) =>
                        {
                            showMetadata(msg);
                        };
                        Dispatcher.Invoke(doViewMetadat, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getMetadataMsg", getMetadataMsg);
        }

        /*<---------------------------------------------- adds client processing for message with key ----------------------------------------------->*/
        private void addClientProc(string key, Action<CsMessage> clientProc)
        {
            dispatcher_[key] = clientProc;
        }



        //---------------------------------------------------------------------------------------------------
        //Browse tab                                                                             |
        //---------------------------------------------------------------------------------------------------
        /*<------------------------------ function to demonstarte browse functionality [automated test unit for browse] ------------------------------>*/
        private void demoBrowse()
        {
            try
            {
                serverback.IsEnabled = false;
                postCatBrowseMsg();                 //get all categories
                postCatFileMsg("I/O");              //get files fro I/O category
                postViewFileMsg("read.h.1");        //open selected file in I/O category
                qfname = fname.Text = "display.h";
                qcatname = "Show";
                isdemo = true;
                qdependname = dependfname.Text = "save.h";
                qversion = version.Text = "2";
                postQueryBrowseMsg(qfname, qcatname, qdependname, qversion);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /*<--------------------------------- function that displays browse successful message in message box ----------------------------------------->*/
        private void addCatBrowseMsg(string msg)
        {
            Comm_Messages.Text += "\nMessage : Category names received - " + msg;
            string[] names = msg.Split(' ');
            names = names.Distinct().ToArray();
            serverLB.Items.Clear();
            for (int i = 0; i < names.Length; i++)
                serverLB.Items.Add(names[i]);
        }

        /*<--------------------------------- function that displays browse successful message in message box ----------------------------------------->*/
        private void addCatFileMsg(string msg)
        {
            Comm_Messages.Text += "\nMessage : Files for particular Category - " + msg;            
            string[] names = msg.Split(' ');
            serverLB.Items.Clear();
            for (int i = 0; i < names.Length; i++)
                serverLB.Items.Add(names[i]);
        }

        /*<--------------------------------- function that displays browse successful message in message box ----------------------------------------->*/
        private void addQueryMsg(string msg)
        {
            Comm_Messages.Text += "\nMessage : Files for particular Query - " + msg;
            string[] names = msg.Split(' ');
            serverLB.Items.Clear();
            serverback.IsEnabled = false;
            for (int i = 0; i < names.Length; i++)
                serverLB.Items.Add(names[i]);
        }

        /*<----------------------------------- function to fill the server repo listbox with files present at server side ---------------------------->*/
        private void fillserverBrowseLB()
        {
            serverLB.Items.Clear();
            foreach (string folder in Directory.GetDirectories(server_path))
                serverLB.Items.Add(System.IO.Path.GetFileName(folder));
        }

        /*<----------------------------------------------- function to load the items into combo-box ------------------------------------------------- >*/
        private void CatbrowseComboBox_Loaded(object sender, RoutedEventArgs e)
        {
            List<string> data = new List<string>();
            data.Add("Data");
            data.Add("I/O");
            data.Add("Show");
            data.Add("Out");

            var comboBox = sender as ComboBox;
            comboBox.ItemsSource = data;
            comboBox.SelectedItem = (isdemo) ? "Show" : "";
            
        }

        /*<--------------------------- function to get the value of item selected in the combo-box which author of check-in --------------------------->*/
        private void CatbrowseComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var comboBox = sender as ComboBox;
            qcatname = comboBox.SelectedItem as string;
        }

        /*<---------------------------------------------------- change from categories to files view ------------------------------------------------->*/
        private void ServerfilesLB_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            // double click on category so show its files
            try
            {
                string currentSelection = file_toOpen = (string)serverLB.SelectedItem;
                if(queryBrowsingOn)
                    postViewFileMsg(currentSelection);
                else if (catBrowsingOn)
                {
                    postCatFileMsg(currentSelection);
                    catFileBrowsingOn = true;
                    if (catFileBrowsingOn)
                    {
                        postViewFileMsg(currentSelection);
                    }
                }
                else if (serverBrowsingOn)
                {
                    if(currentSelection.Contains('.'))
                        postViewFileMsg(currentSelection);
                    else
                    {
                        serverLB.Items.Clear();
                        List<string> files = getFiles(server_path + "/" + currentSelection);
                        foreach (string file in files)
                            serverLB.Items.Add(System.IO.Path.GetFileName(file));
                    }
                }
                else
                    MessageBox.Show("Nothing to display!");
                serverback.IsEnabled = true;
            }
            catch(Exception ex)
            {
                MessageBox.Show("Dobule click on Files not allowed");
                string message = ex.Message;
            }
            
        }
        
        /*<-------------------------------- back button that again shows the categories/folders in server repository ---------------------------------->*/
        private void serverbackButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {

                if (catBrowsingOn)
                    postCatBrowseMsg();
                if (serverBrowsingOn)
                    fillserverBrowseLB();
                serverback.IsEnabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /*<---------------------------------- function that do the functionality of posting a browse msg to server ------------------------------------>*/
        private void showServer_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (connection_status)
                {
                    serverback.IsEnabled = false;
                    serverBrowsingOn = true;
                    queryBrowsingOn = false;
                    catBrowsingOn = false;
                    fillserverBrowseLB();
                }
                else
                    MessageBox.Show("Please connect to server first!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
       
        /*<---------------------------------- function that do the functionality of posting a browse msg to server ------------------------------------>*/
        private void showCatg_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (connection_status)
                {
                    serverback.IsEnabled = false;
                    catBrowsingOn = true;
                    serverBrowsingOn = false;
                    queryBrowsingOn = false;
                    statusLabel.Text = "Note : See reply back message in the 'Connect to Server' tab's message text box | or on command prompt";
                    postCatBrowseMsg();
                }
                else
                    MessageBox.Show("Please connect to server first!");
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }            
        }

        /*<---------------------------------- function that do the functionality of posting a browse msg to server ------------------------------------>*/
        private void showQuery_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (connection_status)
                {
                    serverback.IsEnabled = false;
                    queryBrowsingOn = true;
                    catBrowsingOn = false;
                    serverBrowsingOn = false;
                    statusLabel.Text = "Note : See reply back message in the 'Connect to Server' tab's message text box | or on command prompt";
                    qfname = fname.Text;
                    qdependname = dependfname.Text;
                    qversion = version.Text;
                    postQueryBrowseMsg(qfname, qcatname, qdependname, qversion);
                }
                else
                    MessageBox.Show("Please connect to server first!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }


        }

        /*<------------------------------------ function that posts a catbrowse message to server with details ---------------------------------------->*/
        private void postCatBrowseMsg()
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getCatBrowseMsg");
            msg.add("message", "show package categories");
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }

        /*<------------------------------------ function that posts a catbrowse message to server with details ---------------------------------------->*/
        private void postCatFileMsg(string catgName)
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getCatFileMsg");
            msg.add("catgName", catgName);
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }

        /*<------------------------------------ function that posts a querybrowse message to server with details -------------------------------------->*/
        private void postQueryBrowseMsg(string fName, string catgName, string dependName, string version)
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getQueryMsg");
            msg.add("fileName", fName);
            msg.add("category", catgName);
            msg.add("dependency", dependName);
            msg.add("version", version);
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }



        //---------------------------------------------------------------------------------------------------
        //Check-In tab                                                                                      |
        //---------------------------------------------------------------------------------------------------
        /*<------------------------------ function to demonstarte checkin functionality [automated test unit for checkin] ------------------------------>*/
        private void demoChkInCase1()   //initial check-in
        {
            try
            {
                filldstnDir();
                CreateCheckBoxList();
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nCheck-in Test Case #1"); Console.ResetColor();
                Console.WriteLine("\n Initial Check-in & appended initial version number");
                Console.WriteLine("====================================================================================================================");
                postCheckInMsg("save.h",      "repo-demo", "Admin", "Data", "open",   server_path + "/save",    "");
                postCheckInMsg("save.cpp",    "repo-demo", "Admin", "Data", "open",   server_path + "/save",    "");
                postCheckInMsg("display.h",   "repo-demo", "Admin", "Show", "close",  server_path + "/display", "save.h.1");
                postCheckInMsg("display.cpp", "repo-demo", "Admin", "Show", "close",  server_path + "/display", "save.h.1");
                postCheckInMsg("read.h",      "repo-demo", "Admin", "I/O",  "close",  server_path + "/read",    "");
                postCheckInMsg("read.cpp",    "repo-demo", "Admin", "I/O",  "close",  server_path + "/read",    "");
                postCheckInMsg("write.h",     "repo-demo", "Admin", "I/O",  "close",  server_path + "/write",   "");
                postCheckInMsg("write.cpp",   "repo-demo", "Admin", "I/O",  "close",  server_path + "/write",   "");                
                CkInfilename = selectedCkInFiles.Text = "write.cpp";
                author = "Admin";
                dstn_path = dstnpath.Text = server_path + "/write";
                childName = child.Text = "";
                descrp = descr.Text = "repo-demo";
                close.IsChecked = true;
                open.IsChecked = false;
                CkInstatus = "close";
                Console.WriteLine("====================================================================================================================");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "  | Please enter all the information");
            }
            
        }

        /*<------------------------------ function to demonstarte checkin functionality [automated test unit for checkin] ------------------------------>*/
        private void demoChkInCase2()   //last check-in status close so doing new check-in & appending version number 
        {
            try
            {
                filldstnDir();
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nCheck-in Test Case #2"); Console.ResetColor();
                Console.WriteLine("\n New Check-in & appended new version number [because last check-in status close]  ");
                Console.WriteLine("====================================================================================================================");
                postCheckInMsg("read.h", "repo-demo", "Admin", "I/O", "open", server_path + "/read", "");
                postCheckInMsg("read.cpp", "repo-demo", "Admin", "I/O", "open", server_path + "/read", "");
                CkInfilename = selectedCkInFiles.Text = "read.cpp";
                author = "Admin";
                dstn_path = dstnpath.Text = server_path + "/read";
                childName = child.Text = "";
                descrp = descr.Text = "repo-demo";
                close.IsChecked = false;
                open.IsChecked = true;
                CkInstatus = "open";
                Console.WriteLine("====================================================================================================================");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "  | Please enter all the information");
            }

        }

        /*<------------------------------ function to demonstarte checkin functionality [automated test unit for checkin] ------------------------------>*/
        private void demoChkInCase3()     //dependency open so doing checkin with status as pending
        {
            try
            {
                filldstnDir();
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nCheck-in Test Case #3"); Console.ResetColor();
                Console.WriteLine("\n New Check-in, appended new version number & status - Pending [because dependency files check-in status is open]  ");
                Console.WriteLine("====================================================================================================================");
                postCheckInMsg("display.h", "repo-demo", "Admin", "Show", "open", server_path + "/display", "save.h.1");
                postCheckInMsg("display.cpp", "repo-demo", "Admin", "Show", "open", server_path + "/display", "save.h.1");
                CkInfilename = selectedCkInFiles.Text = "display.cpp";
                author = "Admin";
                dstn_path = dstnpath.Text = server_path + "/display";
                childName = child.Text = "save.h.1";
                descrp = descr.Text = "repo-demo";
                close.IsChecked = false;
                open.IsChecked = true;
                CkInstatus = "open";
                Console.WriteLine("====================================================================================================================");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "  | Please enter all the information");
            }

        }

        /*<------------------------------ function to demonstarte checkin functionality [automated test unit for checkin] ------------------------------>*/
        private void demoChkInCase4()     //last checkin status open so doing the checkin in the open version only
        {
            try
            {
                filldstnDir();
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nCheck-in Test Case #4"); Console.ResetColor();
                Console.WriteLine("\n New Check-in but in same file & NOT appended new version number [because last check-in status open]  ");
                Console.WriteLine("====================================================================================================================");
                postCheckInMsg("save.h",   "repo-demo", "Admin", "Data", "open", server_path + "/save", "");
                postCheckInMsg("save.cpp", "repo-demo", "Admin", "Data", "open", server_path + "/save", "");
                CkInfilename = selectedCkInFiles.Text = "save.cpp";
                author = "Admin";
                dstn_path = dstnpath.Text = server_path + "/save";
                childName = child.Text = "";
                descrp = descr.Text = "repo-demo";
                close.IsChecked = false;
                open.IsChecked = true;
                CkInstatus = "open";
                Console.WriteLine("====================================================================================================================");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + "  | Please enter all the information");
            }

        }

        /*<--------------------------------- function that displays check-in successful message in status bar ----------------------------------------->*/
        private void addCheckinMsg(string msg)
        {
            UpdateCheckBoxList(msg);
            Comm_Messages.Text += "\nMessage : " + msg;
        }

        /*<-------------------------------------- function to allow user to browse files to check-in -------------------------------------------------->*/
        private void browseFile_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                selectedCkInFiles.Text = string.Empty;
                System.IO.Stream myStream;
                System.Windows.Forms.OpenFileDialog thisDialog = new System.Windows.Forms.OpenFileDialog();
                thisDialog.InitialDirectory = Path.GetFullPath(client_path);
                thisDialog.Multiselect = true;
                thisDialog.Title = "Please Select Check-in Files for client Repository";

                if (thisDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    foreach (string file in thisDialog.FileNames)
                    {
                        try
                        {
                            if ((myStream = thisDialog.OpenFile()) != null)
                            {
                                using (myStream)
                                {
                                    selectedCkInFiles.Text += Path.GetFileName(file);
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Error: Could not read Path. Original error: " + ex.Message);
                        }
                    }
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show("Please connect to server first!");
                string message = ex.Message;
            }
            
        }
        
        /*<-------------------------------- function to fill directories [to select it as the destination path] -------------------------------------- >*/
        private void filldstnDir()
        {
            selected_dir.Items.Clear();
            foreach (string folder in Directory.GetDirectories(server_path))
                selected_dir.Items.Add(System.IO.Path.GetFileName(folder));
        }

        /*<--------------------------------- function that gets a value selected for destination path list box ----------------------------------------->*/
        private void dstn_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            dstn_path = dstnpath.Text = server_path + "/" + selected_dir.SelectedValue as string;
        }
       
        /*<----------------------------------------------- function to load the items into combo-box ------------------------------------------------- >*/
        private void ComboBox_Loaded(object sender, RoutedEventArgs e)
        {
            List<string> data = new List<string>();
            data.Add("Admin");
            data.Add("Project Manager");
            data.Add("Lead Developer");
            data.Add("Team Manager");
            
            var comboBox = sender as ComboBox;
            comboBox.ItemsSource = data;
            comboBox.SelectedItem = "Admin";
        }
    
        /*<--------------------------- function to get the value of item selected in the combo-box which author of check-in --------------------------->*/
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var comboBox = sender as ComboBox;
            author = comboBox.SelectedItem as string;
        }

        /*<----------------------------------------------- function to load the items into combo-box ------------------------------------------------- >*/
        private void CatComboBox_Loaded(object sender, RoutedEventArgs e)
        {
            List<string> data = new List<string>();
            data.Add("Data");
            data.Add("I/O");
            data.Add("Show");
            data.Add("Out");

            var comboBox = sender as ComboBox;
            comboBox.ItemsSource = data;
            comboBox.SelectedItem = "Data";
        }

        /*<--------------------------- function to get the value of item selected in the combo-box which author of check-in --------------------------->*/
        private void CatComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var comboBox = sender as ComboBox;
            category = comboBox.SelectedItem as string;
        }

        /*<------------------------- function that creates checkbox list for depedency children to add for current check-in --------------------------->*/
        public void CreateCheckBoxList()
        {
            foreach (string folder in Directory.GetDirectories(server_path))
            {
                string dir = System.IO.Path.GetFileName(folder);
                List<string> files = getFiles(server_path + "/" + dir);
                foreach (string file in files)
                {
                    TheList.Add(new BoolStringClass { TheText = System.IO.Path.GetFileName(file) });
                    this.DataContext = this;
                }
            }
        }

        /*<------------------------- function that updates checkbox list for depedency children to add for current check-in --------------------------->*/
        public void UpdateCheckBoxList(string fileName)
        {
            int getIndexFroName = fileName.IndexOf(":");
            TheList.Add(new BoolStringClass { TheText = fileName.Substring(0,getIndexFroName) });
            this.DataContext = this;
        }

        /*<--------------------------- function that shows the selected checkbox items from the listbox into a textbox -------------------------------->*/
        private void CheckBoxZone_Checked(object sender, RoutedEventArgs e)
        {
            childName = "";
            chkZone = (CheckBox)sender;
            childName = child.Text += chkZone.Content.ToString() + ", " ;
        }

        /*<--------------------------- function that performs the functionality of check-in on button click ------------------------------------------->*/
        private void ChkInButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (connection_status)
                {
                    CkInfilename = selectedCkInFiles.Text;
                    descrp = descr.Text;
                    childName = child.Text;
                    CkInstatus = (open.IsChecked.Value) ? "open" : "close";
                    if (selectedCkInFiles.Text != null && dstnpath.Text != null && descr.Text != null && (open.IsChecked.Value || close.IsChecked.Value))
                        ChkInButton.IsEnabled = true;                   
                    postCheckInMsg(CkInfilename, descrp, author, category, CkInstatus, dstn_path, child.Text);
                    if (childName != "")
                        chkZone.IsChecked = false;
                    selectedCkInFiles.Text = descr.Text = dstnpath.Text = child.Text = childName = string.Empty;
                    selected_dir.SelectedIndex = -1;
                    statusLabel.Text = "Note : See reply back message in the 'Connect to Server' tab's message text box | or on command prompt";
                }
                else
                    MessageBox.Show("Please connect to server first!");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Please enter all the information");
                string message = ex.Message;
            }
            
        }

        /*<------------------------------- function that posts a check in message to server with check-in details ------------------------------------->*/
        private void postCheckInMsg(string fname, string desr, string auth, string cat, string status, string path, string children)
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getCheckinMsg");
            msg.add("sendingFile", fname);
            msg.add("descr", desr);
            msg.add("author", auth);
            msg.add("category", cat);
            msg.add("status", status);
            msg.add("path", path);
            msg.add("children", children);
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }



        //---------------------------------------------------------------------------------------------------
        //Check-Out tab                                                                                     |
        //---------------------------------------------------------------------------------------------------
        /*<------------------------------ function to demonstarte checkout functionality [automated test unit for checkin] ------------------------------>*/
        private void demoChkOutCase1()      //check-out without dependent files 
        {
            try
            {
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nCheck-out Test Case #1"); Console.ResetColor();
                Console.WriteLine("\n Basic Check-out with no dependency files present");
                Console.WriteLine("====================================================================================================================");
                postDependMsg("read.h.1");
                postCheckOutMsg("read.h.1","");
                fillCheckoutFilesLB();
                ChkOutButton.IsEnabled = false;
                ChkOutDesc.IsChecked = false;
                back.IsEnabled = false;

            }
            catch (Exception ex)
            {
                MessageBox.Show("Please select a file to check-out [Please see the note in the status bar]");
                string message = ex.Message;
            }
            
        }

        /*<------------------------------ function to demonstarte checkout functionality [automated test unit for checkin] ------------------------------>*/
        private void demoChkOutCase2()      //check-out dependent files present but user doesn't want to checkout dependent files
        {
            try
            {
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nCheck-out Test Case #2"); Console.ResetColor();
                Console.WriteLine("\n Check-out of a file having dependent files present but user doesn't want to checkout dependent files");
                Console.WriteLine("====================================================================================================================");
                ChkOutDesc.IsChecked = false;
                postDependMsg("display.h.1");
                postCheckOutMsg("display.h.1", "save.h.1");
                fillCheckoutFilesLB();
                ChkOutButton.IsEnabled = false;
                back.IsEnabled = false;

            }
            catch (Exception ex)
            {
                MessageBox.Show("Please select a file to check-out [Please see the note in the status bar]");
                string message = ex.Message;
            }

        }

        /*<------------------------------ function to demonstarte checkout functionality [automated test unit for checkin] ------------------------------>*/
        private void demoChkOutCase3()      //check-out without dependent files 
        {
            try
            {
                Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nCheck-out Test Case #3"); Console.ResetColor();
                Console.WriteLine("\n Check-out of a file having dependent files present but user wants to checkout dependent files");
                Console.WriteLine("====================================================================================================================");
                postDependMsg("display.cpp.1");
                ChkOutDesc.IsChecked = true;
                postCheckOutMsg("display.cpp.1", "save.h.1");
                fillCheckoutFilesLB();
                ChkOutButton.IsEnabled = false;
                back.IsEnabled = false;

            }
            catch (Exception ex)
            {
                MessageBox.Show("Please select a file to check-out [Please see the note in the status bar]");
                string message = ex.Message;
            }

        }

        /*<--------------------------------- function that displays check-out successful message in message box -------------------------------------->*/
        private void addCheckOutMsg(string msg)
        {
            Comm_Messages.Text += "\nMessage : " + msg;
        }

        /*<------------------------------ function that shows the dependent files in the listbox ---------------------------------------------------->*/
        private void showDependent(string files)
        {
            depenlist.Items.Clear();
            if (String.IsNullOrEmpty(files))
                statusLabel.Text = "Message : No dependent files for selected check-out file";
            else
            {
                depenlist.Items.Add(files);
                //string[] words = files.Split(',');
                //for (int i = 0; i < words.Length - 1; i++)
                //    depenlist.Items.Add(words[i]);
            }
        }

        /*<---------------------------------This listbox shows the categories/folders currently present in the server repository---------------------->*/
        private void fillCheckoutFilesLB()
        {
            fileslist.Items.Clear();
            foreach (string folder in Directory.GetDirectories(server_path))
                fileslist.Items.Add(System.IO.Path.GetFileName(folder));
        }
        
        /*<---------------------------------------------------- change from categories to files view ------------------------------------------------->*/
        private void ChkOutFilesListBox_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            // double click on category so show its files
            try
            {
                string currentCategory = (string)fileslist.SelectedItem;
                fileslist.Items.Clear();
                List<string> files = getFiles(server_path + "/" + currentCategory);
                foreach (string file in files)
                    fileslist.Items.Add(System.IO.Path.GetFileName(file));
                ChkOutButton.IsEnabled = true;
                back.IsEnabled = true;
            }
            catch(Exception ex)
            {
                MessageBox.Show("Double click on files not allowed");
                string messages = ex.Message;
            }
        }

        /*<-------------------------------back button that again shows the categories/folders in server repository------------------------------------>*/
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                fillCheckoutFilesLB();
                back.IsEnabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Incorrect time to click back button");
                string message = ex.Message;
            }
        }

        /*<----------------------------- function which performs check out functionality on check out button click ----------------------------------->*/
        private void ChkOutButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (connection_status)
                {
                    checkout_file = fileslist.SelectedValue as string;
                    postCheckOutMsg(checkout_file, depend.Text);
                    statusLabel.Text = "Note : See reply back message in the 'Connect to Server' tab's message text box | or on command prompt";
                }
                else
                    MessageBox.Show("Please connect to server first!");
            }
            catch(Exception ex)
            {
                MessageBox.Show("Please select a file to check-out [Please see the note in the status bar]");
                string message = ex.Message;
            }
            
        }

        /*<----------------------------- function which performs dependency add functionality on dependent button click ------------------------------>*/
        private void dependentButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                string select_chkoutFile = fileslist.SelectedValue as string;
                postDependMsg(select_chkoutFile);
            }
            catch(Exception ex)
            {
                MessageBox.Show("Please select file not directory");
                string message = ex.Message;
            }
        }

        /*<------------------------------ function that adds selected dependent file names in the textbox below -------------------------------------->*/
        private void dpendent_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            dependent_file = depend.Text = depenlist.SelectedValue as string + ",";
        }
        
        /*<------------------------------- function that posts a check out message to server with check-out details ---------------------------------->*/
        private void postCheckOutMsg(string ckoutfName, string depndfName)
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getCheckOutMsg");
            if (ChkOutDesc.IsChecked.Value)
                msg.add("dependFileName", depndfName);
            else
                msg.add("dependFileName", "");
            msg.add("FileName", ckoutfName);
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }

        /*<------------------------------------ function that posts a getdependent message to server with details ------------------------------------>*/
        private void postDependMsg(string ckoutfName)
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getDependent");
            msg.add("fileName", ckoutfName);
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }




        //---------------------------------------------------------------------------------------------------
        //View-File tab                                                                                     |
        //---------------------------------------------------------------------------------------------------
        /*<-------------------- function to demonstarte view file content functionality [automated test unit for view file content] ------------------->*/
        private void demoViewFile()
        {
            try
            {
                file_toOpen = "display.h.1";
                fillFoldinRepoLB();
                fillFilesinRepoLB("display");
                postViewFileMsg(file_toOpen);

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        /*<------------------------------------- function that displays view file message in message textbox ---------------------------------------->*/
        private void addViewFileMsg(string contents)
        {
            Comm_Messages.Text += "\nMessage : Poped-up Window for " + Path.GetFileName(contents) + " Successfully!";
            Console.ForegroundColor = ConsoleColor.Black; Console.BackgroundColor = ConsoleColor.Gray; Console.WriteLine("\nRequirement 3"); Console.ResetColor();
            Console.WriteLine("It provide Client program that can upload and download files and view Repository contents");
            Console.WriteLine("Opening a new window displaying text of a Repository file will satisfy this requirement.");
            Console.WriteLine("File Location : " + Path.GetFullPath(contents));
            if (contents.Substring(0, 2) == "..")
            {
                string content = File.ReadAllText(contents);
                CodePopUp popup = new CodePopUp();
                popup.Title = file_toOpen;         //loads content of selected file into codepopup window
                popup.codeView.Text = content;
                popup.Show();
            }
            else
                Comm_Messages.Text += "\n" + contents;
        }

        /*<------------------------------This listbox shows the categories/folders currently present in the server repository ---------------------->*/
        private void fillFoldinRepoLB()
        {
            foldInRepo.Items.Clear();
            foreach (string folder in Directory.GetDirectories(server_path))
                foldInRepo.Items.Add(System.IO.Path.GetFileName(folder));
        }

        /*----------------------------------< Shows content of selected file from ListBox#3 into CodePopUp window >----------------------------------*/
        private void fold_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            // double click on category so show its files
            try
            {
                string currentCategory = (string)foldInRepo.SelectedItem;
                category_name = currentCategory;
                fillFilesinRepoLB(currentCategory);
            }
            catch(Exception ex)
            {
                MessageBox.Show("Double click not available right now");
                string message = ex.Message;
            }
        }

        /*<---------------------------This listbox shows the files present for given category present in the server repository---------------------->*/
        private void fillFilesinRepoLB(string folder)
        {
            filesInRepo.Items.Clear();
            string path = server_path + "/" + folder;
            List<string> files = getFiles(path);
            foreach (string file in files)
                filesInRepo.Items.Add(System.IO.Path.GetFileName(file));
        }

        /*-------------------------------- Shows content of selected file from ListBox#3 into CodePopUp window ------------------------------------->*/
        private void files_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            try
            {
                if (connection_status)
                {
                    file_toOpen = filesInRepo.SelectedValue as string;
                    postViewFileMsg(file_toOpen);
                    statusLabel.Text = "Note : See reply back message in the 'Connect to Server' tab's message text box or on command prompt | See Files copied @ repo -> CopiedFIles directory";
                }
                else
                    MessageBox.Show("Please connect to server first!");
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        /*<------------------------------------ function that posts a view file message to server with details ------------------------------------->*/
        private void postViewFileMsg(string fileName)
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getViewFileMsg");
            msg.add("sendFile", fileName);
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }



        //---------------------------------------------------------------------------------------------------
        //View-Metadata tab                                                                                  |
        //---------------------------------------------------------------------------------------------------
        /*<--------------------- function to demonstarte view metadata functionality [automated test unit for view metadata] ----------------------->*/
        private void demoViewMetadata()
        {
            try
            {
                postgetMetadataMsg();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        /*<------------------------------------ function that posts view metadata message to server with details ----------------------------------->*/
        private void postgetMetadataMsg()
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(server_endpoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getMetadataMsg");
            msg.add("Metadata", "of whole database");
            translater.postMessage(msg);
            Console.WriteLine("\n Posted Message: from " + msg.value("from"));
            msg.show();
        }

        /*<------------------- function that posts view metadata message to server with details on click of view metadata button ------------------->*/
        private void MDataButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (connection_status)
                {
                    postgetMetadataMsg();
                    statusLabel.Text = "Note : See reply back message in the 'Connect to Server' tab's message text box | or on command prompt";
                }
                else
                    MessageBox.Show("Please connect to server first!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message + " Please make sure you have filled all the information while check-in");
            }
            
        }

        /*<---------------------------------- Function that puts the meta data into a flow document table ------------------------------------------>*/
        private void showMetadata(string data)
        {
            try {
                Comm_Messages.Text += "\nMessage : Received Meatadata! [See in 'ViewMetadata' tab]";
                var rowGroup = metadataTB.RowGroups.FirstOrDefault();
                string[] words = data.Split(' ');
                List<string> list = new List<string>(words);
                if (words[4] == string.Empty) {
                    for (int i = 0; i < list.Count; i++) {
                        if (list[i] == string.Empty)
                            list.Remove(list[i]);
                    }
                    words = list.ToArray();
                }
                for (int i = 0; i < words.Length - 1; i=i+11){
                    if (rowGroup != null){
                        TableRow row = new TableRow();
                        TableCell cell = new TableCell();
                        Border myBorder = new Border();
                        myBorder.BorderBrush = Brushes.Black;
                        myBorder.BorderThickness = new Thickness(1, 0, 1, 1);
                        cell.Blocks.Add(new Paragraph(new Run(words[i])));
                        cell.ColumnSpan = 10;                       cell.TextAlignment = TextAlignment.Center;
                        cell.BorderBrush = myBorder.BorderBrush;    cell.BorderThickness = new Thickness(1, 0, 1, 1);
                        row.Cells.Add(cell);
                        cell = new TableCell();
                        cell.ColumnSpan = 6;                       cell.TextAlignment = TextAlignment.Center;
                        cell.BorderBrush = myBorder.BorderBrush;   cell.BorderThickness = new Thickness(0, 0, 1, 1);
                        cell.Blocks.Add(new Paragraph(new Run(words[i + 1])));                  row.Cells.Add(cell);
                        cell = new TableCell();
                        cell.ColumnSpan = 14;                      cell.TextAlignment = TextAlignment.Center;
                        cell.BorderBrush = myBorder.BorderBrush;   cell.BorderThickness = new Thickness(0, 0, 1, 1);
                        cell.Blocks.Add(new Paragraph(new Run(words[i + 2] + " " + words[i + 3] + " " + words[i + 4] + " " + words[i + 5] + " " + words[i + 6])));
                        row.Cells.Add(cell);
                        cell = new TableCell();
                        cell.ColumnSpan = 8;                       cell.TextAlignment = TextAlignment.Center;
                        cell.BorderBrush = myBorder.BorderBrush;   cell.BorderThickness = new Thickness(0, 0, 1, 1);
                        cell.Blocks.Add(new Paragraph(new Run(words[i + 7])));                  row.Cells.Add(cell);
                        cell = new TableCell();
                        cell.ColumnSpan = 30;                      cell.TextAlignment = TextAlignment.Center;
                        cell.BorderBrush = myBorder.BorderBrush;   cell.BorderThickness = new Thickness(0, 0, 1, 1);
                        cell.Blocks.Add(new Paragraph(new Run(words[i + 8] + " " + words[i + 9] + " " + words[i + 10])));
                        row.Cells.Add(cell);
                        rowGroup.Rows.Add(row);
                    }
                }
            }
            catch(Exception ex){
                MessageBox.Show(ex.Message + " Please make sure you have filled all the information while check-in"); 
            }            
        }
        


        /*<-------------------------------- Functions to display message for every tab into it's status bar ---------------------------------------->*/
        private void connectTabClick (object sender, MouseButtonEventArgs e)
        {
            statusLabel.Text = "Note : Message passing communication started on given address | Comm messages received at client side will be shown in last TextBox";
        }

        private void browseTabClick(object sender, MouseButtonEventArgs e)
        {
            statusLabel.Text = "Note : Double Click on directories to see files listed inside it | Back button - to go one level up | Click on Browse messgae button to send browse message to Server";
        }

        private void checkinTabClick(object sender, MouseButtonEventArgs e)
        {
            statusLabel.Text = "Note : Fill out all the information to check-in file/s | Click on Check-in button to send check-in message to Server";
        }

        private void checkoutTabClick(object sender, MouseButtonEventArgs e)
        {
            statusLabel.Text = "Note : Double CLick on directory to see the files listed inside it | Select a File to checkout and then click on CHeck-out button to send check-out message to Server ";
        }

        private void viewfileTabClick(object sender, MouseButtonEventArgs e)
        {
            statusLabel.Text = "Note : Double click on directories to see files residing into 2nd ListBox | Double click on file to see it's full content";
        }

        private void viewMetadataTabClick(object sender, MouseButtonEventArgs e)
        {
            statusLabel.Text = "Note : CLick on View Metadata button to send the message to Server asking for the metadata ";
        }
    }
}
