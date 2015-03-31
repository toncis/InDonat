//
//  nodetag_kontakt.cpp
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

#include "nodetag_kontakt.h"

namespace Kontakt {

NodeTag_Nod11::NodeTag_Nod11()
{
    this->NOD_OSOBA_ID = 0;
    this->NOD_OSOBA_NAZ = "";
    this->NOD_KNT_TIP = 0;
    this->NOD_KNT_VALUE = "";
    this->NOD_KNT_STATUS = 0;
}

NodeTag_Nod11::NodeTag_Nod11(const NodeTag_Nod11 &other)
{
    this->NOD_OSOBA_ID = other.NOD_OSOBA_ID;
    this->NOD_OSOBA_NAZ = other.NOD_OSOBA_NAZ;
    this->NOD_KNT_TIP = other.NOD_KNT_TIP;
    this->NOD_KNT_VALUE = other.NOD_KNT_VALUE;
    this->NOD_KNT_STATUS = other.NOD_KNT_STATUS;
}

NodeTag_Nod11::~NodeTag_Nod11()
{
}

} // Kontakt
