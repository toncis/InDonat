/************************************* Module Header **************************************\
* Module Name:  donat.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of DONAT includes
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

#ifndef DONAT_H
#define DONAT_H

// ORACLE
#include <occi.h>
//#include <oci.h>
//#include <occiObjects.h>

// Qt
#include <QMessageBox>

// Global variables
#include "global.h"



#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

#endif // DONAT_H


// DONAT Global Variables

extern int g_VEL;

// DONAT USER Information
extern string g_KORISNIK_ID;
extern string g_KORISNIK_NAZ;
extern string g_KORISNIK_IME;
extern int g_ORGJED_ID;
extern string g_ORGJED_NAZ;
extern int g_KANAL_ID;
extern string g_KANAL_NAZ;
extern int g_REGIJA_ID;
extern string g_REGIJA_NAZ;
extern int g_ZUPANIJA_ID;
extern string g_ZUPANIJA_NAZ;
extern int g_CROS;


// DONAT USER FILTER Information
extern string g_FILTER_KORISNIK_ID;
extern string g_FILTER_KORISNIK_NAZ;
extern string g_FILTER_KORISNIK_IME;
extern int g_FILTER_ORGJED_ID;
extern string g_FILTER_ORGJED_NAZ;
extern int g_FILTER_KANAL_ID;
extern string g_FILTER_KANAL_NAZ;
extern int g_FILTER_REGIJA_ID;
extern string g_FILTER_REGIJA_NAZ;
extern int g_FILTER_ZUPANIJA_ID;
extern string g_FILTER_ZUPANIJA_NAZ;
extern int g_FILTER_CROS;

// DONAT USER UNIO Information
extern string g_UNIO_KORISNIK_ID;
extern string g_UNIO_KORISNIK_NAZ;
extern string g_UNIO_KORISNIK_IME;
extern int g_UNIO_ORGJED_ID;
extern string g_UNIO_ORGJED_NAZ;
extern int g_UNIO_KANAL_ID;
extern string g_UNIO_KANAL_NAZ;
extern int g_UNIO_REGIJA_ID;
extern string g_UNIO_REGIJA_NAZ;
extern int g_UNIO_ZUPANIJA_ID;
extern string g_UNIO_ZUPANIJA_NAZ;
extern int g_UNIO_CROS;

// MDM Information
extern unsigned int DEF_MDM_ID;
extern unsigned int DEF_STRANKA_VAS;
extern unsigned int DEF_STRANKA_ID;
extern string DEF_STRANKA_NAZ;
extern string DEF_NAZ1;
extern string DEF_NAZ2;
extern int DEF_STRANKA_TIP;
extern string DEF_STRANKA_OIB;
extern unsigned int DEF_KUPAC_ID;

extern string DEF_TEL_BROJ;
extern string DEF_TEL_KLASA;
extern unsigned int DEF_TEL_GIM;
extern int DEF_TEL_STATUS;
extern unsigned int DEF_RAZLOG_ID;
extern string DEF_RAZLOG_NAZ;

extern unsigned int DEF_ADRESA_ID;
extern string DEF_ADRESA_NAZ;
extern unsigned int DEF_DRZAVA_ID;
extern string DEF_DRZAVA_NAZ;
extern unsigned int DEF_ZUPANIJA_ID;
extern string DEF_ZUPANIJA_NAZ;
extern unsigned int DEF_REGIJA_ID;
extern string DEF_REGIJA_NAZ;
extern unsigned int  DEF_MJESTO_ID;
extern string DEF_MJESTO_NAZ;
extern string DEF_MJESTO_PTT;
extern unsigned int DEF_POSTA_ID;
extern string DEF_POSTA_NAZ;
extern unsigned int DEF_ULICA_ID;
extern string DEF_ULICA_NAZ;
extern string DEF_KB;
extern string DEF_KBD;
extern string DEF_SOBA;
extern string DEF_KAT;
extern string DEF_EMAIL;
extern string DEF_TEL_1;
extern string DEF_TEL_2;

// KONTAKTNI CENTAR Information
extern int KON_PODACI_OK;

extern int GRP_TIP;
extern int GRP_NO;
extern string GRP_NAZ;

extern int KONTAKT_AKT;
extern unsigned int K_KON_NO;
extern unsigned int K_STAVKA_NO;
extern unsigned int K_ITEM_NO;
extern string K_STAVKA_PRIKAZ;
extern string K_STAVKA_OPIS;
extern int K_STAVKA_AKT;

extern unsigned int K_KUPAC_NO;
extern string K_KUPAC_NAZ;
extern unsigned int K_HEAD_NO;
extern unsigned int K_STRANKA_NO;

extern unsigned int K_NAPLATA_NO;
extern unsigned int K_INSTALACIJA_NO;
extern unsigned int K_LOYALTY_NO;

extern int K_KUP_TIP_NO;
extern string K_KUP_TIP_NAZ;
extern string K_KUP_MB;
extern string K_KUP_OIB;
extern string K_KUP_EMAIL;


extern unsigned int K_ADRESA_NO;
extern string K_ADRESA;
extern string K_ADRESA_1;
extern string K_ADRESA_2;

extern int K_SEGMENT_NO;
extern string K_SEGMENT_NAZ;
extern string K_ZASTUPNIK_NO;
extern string K_ZASTUPNIK_NAZ;

extern unsigned int K_OSOBA_NO;
extern string K_OSOBA_NAZ;
extern int K_OSOBA_KNT_TIP;
extern string K_OSOBA_KNT_VALUE;
extern string K_OSOBA_KNT_OPIS;

extern string K_TEL_BROJ;
extern string K_TEL_KLASA;
extern unsigned int K_TEL_GIM;
extern int K_TEL_TIP;
extern int K_TEL_STATUS;

extern int K_SMEZAH_TIP;
extern unsigned int K_SMEZAH_ID;
extern string K_SMEZAH_DATUM;

// KONTAKTNI CENTAR AVAYA
extern int AVAYA_KOR_ID;
extern int AVAYA_KON;
extern int AVAYA_AKT;
extern string AVAYA_BROJ;
extern string AVAYA_EDUID;
extern string AVAYA_CALL_TYPE;

// Donat user KON Grupa ID
extern int g_GRP_NO;
// Donat user KON Tip Grupe
extern int g_GRP_TIP;
// Donat user KON Naziv Grupe
extern string g_GRP_NAZ;
