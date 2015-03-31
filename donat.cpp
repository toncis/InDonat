//
//  donat.cpp
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
