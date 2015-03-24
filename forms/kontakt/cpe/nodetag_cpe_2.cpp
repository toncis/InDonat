#include "nodetag_cpe_2.h"

namespace Kontakt {

NodeTag_Cpe_2::NodeTag_Cpe_2()
{
    this->BrojTelefona = "";
    this->CpeModel = "";
    this->CpeSerialNumber = "";
    this->CpeTip = "";
    this->Klasa = "";
    this->Tip = "";
}

NodeTag_Cpe_2::NodeTag_Cpe_2(const NodeTag_Cpe_2 &other)
{
    this->Asset = other.Asset;
    this->BrojTelefona = other.BrojTelefona;
    this->CpeModel = other.CpeModel;
    this->CpeOId = other.CpeOId;
    this->CpePId = other.CpePId;
    this->CpeSerialNumber = other.CpeSerialNumber;
    this->CpeTip = other.CpeTip;
    this->GrupaImovineId = other.GrupaImovineId;
    this->IsporukaId = other.IsporukaId;
    this->Klasa = other.Klasa;
    this->KupacId = other.KupacId;
    this->NadImovinaId = other.NadImovinaId;
    this->NapalataId = other.NapalataId;
    this->status = other.status;
    this->Tip = other.Tip;
}

NodeTag_Cpe_2::~NodeTag_Cpe_2()
{
}

} // Kontakt

