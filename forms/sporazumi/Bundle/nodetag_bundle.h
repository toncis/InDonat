//
//  nodetag_bundle.h
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

#ifndef NODETAG_BUNDLE
#define NODETAG_BUNDLE

#include <QMetaType>
#include "donat.h"

namespace Sporazumi {

class NodeTag_BundleView
{

public:
    NodeTag_BundleView();
    NodeTag_BundleView(const NodeTag_BundleView &other);
    ~NodeTag_BundleView();

    unsigned int Bundle_Id;
    string Bundle_Identifikator;
    unsigned int Bundle_Instalacija_Id;
    string Tel_Klasa;
    string Identifikator;
    unsigned int Member_Id;
    unsigned int Status_Id;
    unsigned int Komponenta_Id;
    unsigned int Memeber_Linija;

    int Member_Status_Id;
    int Memeber_TAktivnosti_Id;
};

class NodeTag_BundleAnaliza
{

public:
    NodeTag_BundleAnaliza();
    NodeTag_BundleAnaliza(const NodeTag_BundleAnaliza &other);
    ~NodeTag_BundleAnaliza();


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

class NodeTag_BundleInfo
{

public:
    NodeTag_BundleInfo();
    NodeTag_BundleInfo(const NodeTag_BundleInfo &other);
    ~NodeTag_BundleInfo();

    string Bundle_Id;
    unsigned int Bundle_GrupaImovine_id;
    int Bundle_Stat;
    unsigned int Bundle_Pretplata_Id;
    string Bundle_Pretplata;
    int Bundle_Pretplata_Stat;
    string Konverzija_Cekanje;
    unsigned int Billing_Bundle_GR_S;
    unsigned int Memeber_Id;
    string Komponenta;
    int Member_Linija;
    string Memeber_Identifikator;
    unsigned int Memeber_Pretplata_Id;
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


} // Sporazumi

Q_DECLARE_METATYPE(Sporazumi::NodeTag_BundleView);

Q_DECLARE_METATYPE(Sporazumi::NodeTag_BundleAnaliza);

Q_DECLARE_METATYPE(Sporazumi::NodeTag_BundleInfo);

#endif // NodeTag_BundleView
