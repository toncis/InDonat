//
//  nodetag_cpe_2.h
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

#ifndef NODETAG_CPE_2_H
#define NODETAG_CPE_2_H

#include <QMetaType>
#include "donat.h"

namespace Kontakt {

class NodeTag_Cpe_2
{

public:
    NodeTag_Cpe_2();
    NodeTag_Cpe_2(const NodeTag_Cpe_2 &other);
    ~NodeTag_Cpe_2();

    unsigned int KupacId;
    unsigned int IsporukaId;
    unsigned int NapalataId;
    string BrojTelefona;
    string Klasa;
    unsigned int Asset;
    unsigned int GrupaImovineId;
    int status;
    string Tip;

    unsigned int NadImovinaId;
    unsigned int CpeOId;
    unsigned int CpePId;
    string CpeSerialNumber;
    string CpeTip;
    string CpeModel;

};


} // Kontakt

Q_DECLARE_METATYPE(Kontakt::NodeTag_Cpe_2);

#endif // NODETAG_CPE_2_H
