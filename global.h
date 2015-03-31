//
//  global.h
//
//  Author:
//       Tonči Sviličić <tonci.svilicic@in2.hr>
//
//  Copyright (c) 2012 Tonči Sviličić
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
