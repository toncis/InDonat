//
//  nodetag_cpe_2.cpp
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

