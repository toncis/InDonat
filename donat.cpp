/************************************* Module Header **************************************\
* Module Name:  donat.cpp
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


#include "donat.h"

int g_VEL;

// DONAT USER Information
int g_ORGJED_ID;
string g_ORGJED_NAZ = "";
string g_KORISNIK_ID = "";
string g_KORISNIK_NAZ = "";
string g_KORISNIK_IME = "";

int g_KANAL_ID;
string g_KANAL_NAZ = "";
int g_REGIJA_ID;
string g_REGIJA_NAZ = "";
int g_ZUPANIJA_ID;
string g_ZUPANIJA_NAZ = "";
int g_CROS;

// DONAT USER FILTER Information
string g_FILTER_KORISNIK_ID = "";
string g_FILTER_KORISNIK_NAZ = "";
string g_FILTER_KORISNIK_IME = "";
int g_FILTER_ORGJED_ID;
string g_FILTER_ORGJED_NAZ = "";
int g_FILTER_KANAL_ID;
string g_FILTER_KANAL_NAZ = "";
int g_FILTER_REGIJA_ID;
string g_FILTER_REGIJA_NAZ = "";
int g_FILTER_ZUPANIJA_ID;
string g_FILTER_ZUPANIJA_NAZ = "";
int g_FILTER_CROS;

// DONAT USER UNIO Information
string g_UNIO_KORISNIK_ID = "";
string g_UNIO_KORISNIK_NAZ = "";
string g_UNIO_KORISNIK_IME = "";
int g_UNIO_ORGJED_ID;
string g_UNIO_ORGJED_NAZ = "";
int g_UNIO_KANAL_ID;
string g_UNIO_KANAL_NAZ = "";
int g_UNIO_REGIJA_ID;
string g_UNIO_REGIJA_NAZ = "";
int g_UNIO_ZUPANIJA_ID;
string g_UNIO_ZUPANIJA_NAZ = "";
int g_UNIO_CROS;


// Donat user KON Grupa ID
int g_GRP_NO;
// Donat user KON Tip Grupe
int g_GRP_TIP;
// Donat user KON Naziv Grupe
string g_GRP_NAZ = "";
