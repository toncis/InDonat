//
//  bundle.cpp
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

#include "bundle.h"

namespace Sporazumi {

// [BUNDLE SPORAZUM]

BundleSporazum::BundleSporazum()
{
    this->Akcija = "";
    this->Bundle_Id = "";
}

BundleSporazum::BundleSporazum(const BundleSporazum &other)
{
    this->Akcija = other.Akcija;
    this->Bundle_Spor = other.Bundle_Spor;
    this->Bundle_Id = other.Bundle_Id;
    this->Ima_Bundle_Akt = other.Ima_Bundle_Akt;
    this->Bundle_Prov_Proc_Id = other.Bundle_Prov_Proc_Id;
    this->Bundle_Prov_Stanje_Id = other.Bundle_Prov_Stanje_Id;
    this->BUNDLE_BILL_PROC_ID = other.BUNDLE_BILL_PROC_ID;
    this->BUNDLE_BILL_STANJE_ID = other.BUNDLE_BILL_STANJE_ID;
    this->MEMBER_SPOR = other.MEMBER_SPOR;
    this->MEMBER_ID = other.MEMBER_ID;
    this->IMA_MEMBER_AKT = other.IMA_MEMBER_AKT;
    this->MEMBER_PROV_PROC_ID = other.MEMBER_PROV_PROC_ID;
    this->MEMBER_PROV_STANJE_ID = other.MEMBER_PROV_STANJE_ID;
    this->MEMBER_BILL_PROC_ID = other.MEMBER_BILL_PROC_ID;
    this->MEMBER_BILL_STANJE_ID = other.MEMBER_BILL_STANJE_ID;
}

BundleSporazum::~BundleSporazum()
{
}

// [BUNDLE INFO]

BundleInfo::BundleInfo()
{
    this->Bundle_Id = "";
    this->Bundle_Pretplata = "";
    this->Konverzija_Cekanje = "";
    this->Komponenta = "";
    this->Memeber_Identifikator = "";
    this->Memeber_Ppretplata = "";
    this->Referenca = "";
    this->VOIP = "";
    this->AKT_GIM = "";
    this->AKT_IMOV = "";
    this->VOIP_MIG = "";
    this->OPTIKA_MIG = "";
    this->ISP_DIST = "";
    this->LI = "";
    this->GR_WWMS = "";
    this->STORNO_REQ = "";
    this->PRVO_SP = "";
    this->GR_EXP = "";
    this->REZ_ZAHT = "";
}

BundleInfo::BundleInfo(const BundleInfo &other)
{
    this->Bundle_Id = other.Bundle_Id;
    this->Bundle_GrupaImovine_id = other.Bundle_GrupaImovine_id;
    this->Bundle_Pretplata_Id = other.Bundle_Pretplata_Id;
    this->Bundle_Pretplata = other.Bundle_Pretplata;
    this->Bundle_Pretplata_Stat = other.Bundle_Pretplata_Stat;
    this->Konverzija_Cekanje = other.Konverzija_Cekanje;
    this->Billing_Bundle_GR_S = other.Billing_Bundle_GR_S;
    this->Memeber_Id = other.Memeber_Id;
    this->Komponenta = other.Komponenta;
    this->Member_Linija = other.Member_Linija;
    this->Memeber_Identifikator = other.Memeber_Identifikator;
    this->Memeber_Ppretplata = other.Memeber_Ppretplata;
    this->Memeber_Pretplata_Stat = other.Memeber_Pretplata_Stat;
    this->Referenca = other.Referenca;
    this->VOIP = other.VOIP;
    this->AKT_GIM = other.AKT_GIM;
    this->AKT_IMOV = other.AKT_IMOV;
    this->VOIP_MIG = other.VOIP_MIG;
    this->OPTIKA_MIG = other.OPTIKA_MIG;
    this->ISP_DIST = other.ISP_DIST;
    this->LI = other.LI;
    this->GR_WWMS = other.GR_WWMS;
    this->STORNO_REQ = other.STORNO_REQ;
    this->PRVO_SP = other.PRVO_SP;
    this->GR_EXP = other.GR_EXP;
    this->REZ_ZAHT = other.REZ_ZAHT;
    this->Billing_Memeber_GR_S = other.Billing_Memeber_GR_S;
}

BundleInfo::~BundleInfo()
{
}

// [BUNDLE ANALIZA]

BundleAnaliza::BundleAnaliza()
{
    this->Bundle_Identifikator = "";
    this->Member_Identifikator = "";
    this->Tel_Klasa = "";
    this->Produkt = "";
    this->Imovina_Id = "";
    this->Kupac_Id = "";
    this->BillingAccount_Id = "";
    this->PartNumber = "";
    this->ProductName = "";
    this->ProductStatus = "";
    this->Created = "";
    this->EffectiveDTM = "";
}

BundleAnaliza::BundleAnaliza(const BundleAnaliza &other)
{
    this->BH_Kupac_Id = other.BH_Kupac_Id;
    this->Bundle_Id = other.Bundle_Id;
    this->Bundle_Identifikator = other.Bundle_Identifikator;
    this->Member_Identifikator = other.Member_Identifikator;
    this->Tel_Klasa = other.Tel_Klasa;
    this->Member_Id = other.Member_Id;
    this->Produkt = other.Produkt;
    this->Imovina_Id = other.Imovina_Id;
    this->Kupac_Id = other.Kupac_Id;
    this->BillingAccount_Id = other.BillingAccount_Id;
    this->PartNumber = other.PartNumber;
    this->ProductName = other.ProductName;
    this->Created = other.Created;
    this->EffectiveDTM = other.EffectiveDTM;
    this->ProductStatus = other.ProductStatus;
    this->DonatStatus = other.DonatStatus;
}

BundleAnaliza::~BundleAnaliza()
{
}

// [BUNDLE MEMBER]

BundleMember::BundleMember()
{
    this->Bundle_Identifikator = "";
    this->Identifikator = "";
    this->Tel_Klasa = "";
    this->Produkt = "";
    this->Status = "";
}

BundleMember::BundleMember(const BundleMember &other)
{
    this->Bundle_Id = other.Bundle_Id;
    this->Bundle_Identifikator = other.Bundle_Identifikator;
    this->Identifikator = other.Identifikator;
    this->Bundle_Instalacija_Id = other.Bundle_Instalacija_Id;
    this->Tel_Klasa = other.Tel_Klasa;
    this->Produkt = other.Produkt;
    this->Status_Id = other.Status_Id;
    this->Komponenta_Id = other.Komponenta_Id;
    this->Member_Linija_Id = other.Member_Linija_Id;
    this->Member_Status_Id = other.Member_Status_Id;
    this->Memeber_TAktivnosti_Id = other.Memeber_TAktivnosti_Id;

    this->Info = other.Info;
    this->Analiza = other.Analiza;
    this->Sporazum = other.Sporazum;
}

BundleMember::~BundleMember()
{
}

// [BUNDLE]

Bundle::Bundle()
{
    this->Identifikator = "";
    this->Produkt = "";
    this->Status = "";

    this->Sporazum = BundleSporazum();
}

Bundle::Bundle(const Bundle &other)
{
    this->Kupac_Id = other.Kupac_Id;
    this->Bundle_Id = other.Bundle_Id;
    this->Identifikator = other.Identifikator;
    this->Imovina_Id = other.Imovina_Id;
    this->Produkt = other.Produkt;
    this->Status_Id = other.Status_Id;
    this->Status = other.Status;
    //this->Info = other.Info;
    this->Analiza = other.Analiza;
    this->Members = other.Members;
    this->Sporazum = other.Sporazum;
}

Bundle::~Bundle()
{
}


} // Sporazumi
