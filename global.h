/************************************* Module Header **************************************\
* Module Name:  global.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of DONAT global includes
*
* For more information see the Books Online and documentation.
* *****************************************************************************************
* All rights reserved.
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
* OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
* FITNESS FOR A PARTICULAR PURPOSE.
* * *****************************************************************************************
* Release History :
*
* VERSION	DESCRIPTION
* 	1.0		Created by Tonci Svilicic
\******************************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H


// [ STD Support ]
using namespace std;

//extern string inttostring(int i);
//extern string concatenate(std::string const& name, int i);


// [ ORACLE Support ]
#include <occi.h>
//#include <oci.h>
//#include <occiObjects.h>

using namespace oracle::occi;


// extern tells the compiler this variable is declared elsewhere
// Donat envirorment for connection
extern Environment *g_DonatEnv;
// Donat connection
extern Connection *g_DonatConn;
// Donat connection status
extern bool g_DonatConnected;

// Donat user info
extern string g_DonatUser;
// Donat user passwd
extern string g_DonatUserPasswd;
// Donat database
extern string g_DonatDatebase;


// Used to create DONAT connection
extern void CreateDonatConnection(string strUserName, string strPasswd, string strDatabase);
// Used to close DONAT connection
extern void CloseDonatConnection();

#endif // GLOBAL_H
