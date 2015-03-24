/************************************* Module Header **************************************\
* Module Name:  global.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the impelemntations of DONAT global members
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


// C++ STL algoritms
#include <algorithm>
#include <cctype>

using namespace std;

// Qt Codec settings
#include <QTextCodec>

// Oracle OCCI support
#include <occi.h>
//#include <oci.h>
//#include <occiObjects.h>

using namespace oracle::occi;


// Declaration of Donat envirorment for connection
Environment *g_DonatEnv = NULL;
// Declaration of Donat connection
Connection *g_DonatConn = NULL;
// Declaration of Donat connection status
bool g_DonatConnected = false;

// Donat user info
string g_DonatUser = "";
// Donat user passwd
string g_DonatUserPasswd = "";
// Donat database
string g_DonatDatebase = "";

void CreateDonatConnection(
    string strUserName,
    string strPasswd,
    string strDatabase)
{
    // Create Oracle OCCI Environment
    // Use global variable NLS_LANG
    g_DonatEnv = Environment::createEnvironment();
    // Use explicit charsets
    // g_DonatEnv = Environment::createEnvironment("EE8MSWIN1250","AL16UTF16");

    // Create Oracle OCCI Connection in the Environment instance
    g_DonatConn = g_DonatEnv->createConnection(strUserName, strPasswd, strDatabase);

    // TO DO
    // Set global conversions based on charsets used in Oracle environment
    string strCharSet = g_DonatConn->getClientCharSet();
    if(strCharSet == "UTF8")
    {
        // Set tr() global conversions based on UTF-8, not required for Qt v5.x
        // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    }
    else if(strCharSet == "EE8MSWIN1250")
    {
        // Set tr() global conversions based on UTF-8, not required for Qt v5.x
        //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));
    }

    g_DonatConnected = true;
    g_DonatUser = strUserName;
    std::transform(g_DonatUser.begin(),
                   g_DonatUser.end(),
                   g_DonatUser.begin(),
                   (int(*)(int)) std::toupper);
    g_DonatUserPasswd = strPasswd;
    g_DonatDatebase = strDatabase;
    std::transform(g_DonatDatebase.begin(),
                   g_DonatDatebase.end(),
                   g_DonatDatebase.begin(),
                   (int(*)(int)) std::toupper);
}

void CloseDonatConnection()
{
    if(g_DonatConn != NULL)
    {
        // Terminate Donat connection from envirorment
        g_DonatEnv->terminateConnection(g_DonatConn);
    }

    if(g_DonatEnv != NULL)
    {
        //terminate Environment by calling static method
        //Environment::terminateEnvironment
        Environment::terminateEnvironment(g_DonatEnv);
    }

    g_DonatConnected = false;
}

