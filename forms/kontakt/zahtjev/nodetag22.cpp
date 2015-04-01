//
//  nodetag22.cpp
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


#include "nodetag22.h"

namespace Kontakt {

NodeTag22::NodeTag22()
{
    string S1 = "0";
    string S2 = "0";
    string S3 = "0";
    string P1 = "0";
    string P2 = "0";
    string P3 = "0";
}

NodeTag22::NodeTag22(const NodeTag22 &other)
{
    this->Z1_G = other.Z1_G;
    this->Z2_G = other.Z1_G;
    this->Z3_G = other.Z1_G;
    this->Z1_T = other.Z1_G;
    this->Z2_T = other.Z1_G;
    this->Z3_T = other.Z1_G;
    this->Z1_K = other.Z1_G;
    this->Z2_K = other.Z1_G;
    this->Z3_K = other.Z1_G;
    this->S1 = other.Z1_G;
    this->S2 = other.Z1_G;
    this->S3 = other.Z1_G;
    this->P1 = other.Z1_G;
    this->P2 = other.Z1_G;
    this->P3 = other.Z1_G;
}

NodeTag22::~NodeTag22()
{
}

} // Kontakt
