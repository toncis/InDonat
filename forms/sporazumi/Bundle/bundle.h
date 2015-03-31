//
//  bundle.h
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

#ifndef BUNDLE_H
#define BUNDLE_H

#include <QMetaType>
#include "donat.h"

namespace Sporazumi {

class BundleInfo
{
public:
    BundleInfo();
    BundleInfo(const BundleInfo &other);
    ~BundleInfo();

    string Bundle_Id;
    unsigned int Bundle_GrupaImovine_id;
    int Bundle_Stat;
    int Bundle_Pretplata_Id;
    string Bundle_Pretplata;
    int Bundle_Pretplata_Stat;
    string Konverzija_Cekanje;
    unsigned int Billing_Bundle_GR_S;
    unsigned int Memeber_Id;
    string Komponenta;
    int Member_Linija;
    string Memeber_Identifikator;
    int Memeber_Pretplata_Id;
    string Memeber_Ppretplata;
    int Memeber_Pretplata_Stat;
    string Referenca;
    string VOIP;
    string AKT_GIM;
    string AKT_IMOV;
    string VOIP_MIG;
    string OPTIKA_MIG;
    string ISP_DIST;
    string LI;
    string GR_WWMS;
    string STORNO_REQ;
    string PRVO_SP;
    string GR_EXP;
    string REZ_ZAHT;
    unsigned int Billing_Memeber_GR_S;
};

class BundleAnaliza
{

public:
    BundleAnaliza();
    BundleAnaliza(const BundleAnaliza &other);
    ~BundleAnaliza();


    unsigned int BH_Kupac_Id;
    unsigned int Bundle_Id;
    string Bundle_Identifikator;
    string Member_Identifikator;
    string Tel_Klasa;
    unsigned int Member_Id;
    string Produkt;
    string Imovina_Id;
    string Kupac_Id;
    string BillingAccount_Id;
    string PartNumber;
    string ProductName;
    string Created;
    string EffectiveDTM;
    string ProductStatus;
    int DonatStatus;
};

class BundleSporazum
{
public:
    BundleSporazum();
    BundleSporazum(const BundleSporazum &other);
    ~BundleSporazum();

    string Akcija;
    unsigned int Bundle_Spor;
    string Bundle_Id;
    unsigned int Ima_Bundle_Akt;
    unsigned int Bundle_Prov_Proc_Id;
    unsigned int Bundle_Prov_Stanje_Id;
    unsigned int BUNDLE_BILL_PROC_ID;
    unsigned int BUNDLE_BILL_STANJE_ID;
    unsigned int MEMBER_SPOR;
    unsigned int MEMBER_ID;
    unsigned int IMA_MEMBER_AKT;
    unsigned int MEMBER_PROV_PROC_ID;
    unsigned int MEMBER_PROV_STANJE_ID;
    unsigned int MEMBER_BILL_PROC_ID;
    unsigned int MEMBER_BILL_STANJE_ID;
};

class BundleMember
{
public:
    BundleMember();
    BundleMember(const BundleMember &other);
    ~BundleMember();

    unsigned int Bundle_Id;
    string Bundle_Identifikator;
    unsigned int Member_Id;
    string Identifikator;
    unsigned int Bundle_Instalacija_Id;
    string Tel_Klasa;
    string Produkt;
    unsigned int Status_Id;
    string Status;
    unsigned int Komponenta_Id;
    unsigned int Member_Linija_Id;

    int Member_Status_Id;
    int Memeber_TAktivnosti_Id;

    BundleSporazum Sporazum;
    BundleInfo Info;
    std::list<BundleAnaliza> Analiza;
};

class Bundle
{
public:
    Bundle();
    Bundle(const Bundle &other);
    ~Bundle();

    unsigned int Kupac_Id;
    unsigned int Bundle_Id;
    string Identifikator;
    unsigned int Imovina_Id;
    string Produkt;
    unsigned int Status_Id;
    string Status;
    //BundleInfo Info;
    std::list<BundleMember> Members;
    std::list<BundleAnaliza> Analiza;
    BundleSporazum Sporazum;
};


} // Sporazumi

Q_DECLARE_METATYPE(Sporazumi::BundleSporazum);

Q_DECLARE_METATYPE(Sporazumi::BundleInfo);

Q_DECLARE_METATYPE(Sporazumi::BundleAnaliza);

Q_DECLARE_METATYPE(Sporazumi::BundleMember);

Q_DECLARE_METATYPE(Sporazumi::Bundle);


#endif // BUNDLE_H
