#include "nodetag_bundle.h"

namespace Sporazumi {

NodeTag_BundleView::NodeTag_BundleView()
{
    this->Bundle_Identifikator = "";
    this->Tel_Klasa = "";
    this->Identifikator = "";
}

NodeTag_BundleView::NodeTag_BundleView(const NodeTag_BundleView &other)
{
    this->Bundle_Id = other.Bundle_Id;
    this->Bundle_Identifikator = other.Bundle_Identifikator;
    this->Bundle_Instalacija_Id = other.Bundle_Instalacija_Id;
    this->Tel_Klasa = other.Tel_Klasa;
    this->Identifikator = other.Identifikator;
    this->Member_Id = other.Member_Id;
    this->Status_Id = other.Status_Id;
    this->Komponenta_Id = other.Komponenta_Id;
    this->Memeber_Linija = other.Memeber_Linija;
    this->Member_Status_Id = other.Member_Status_Id;
    this->Memeber_TAktivnosti_Id = other.Memeber_TAktivnosti_Id;
}

NodeTag_BundleView::~NodeTag_BundleView()
{
}

NodeTag_BundleAnaliza::NodeTag_BundleAnaliza()
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

NodeTag_BundleAnaliza::NodeTag_BundleAnaliza(const NodeTag_BundleAnaliza &other)
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

NodeTag_BundleAnaliza::~NodeTag_BundleAnaliza()
{
}



NodeTag_BundleInfo::NodeTag_BundleInfo()
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

NodeTag_BundleInfo::NodeTag_BundleInfo(const NodeTag_BundleInfo &other)
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

NodeTag_BundleInfo::~NodeTag_BundleInfo()
{
}



} // Sporazumi

