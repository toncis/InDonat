//
//  notetag22.h
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

#ifndef NODETAG22_H
#define NODETAG22_H

#include <QMetaType>
#include "donat.h"

namespace Kontakt {

class NodeTag22
{

public:
    NodeTag22();
    NodeTag22(const NodeTag22 &other);
    ~NodeTag22();

    string Z1_G;
    string Z2_G;
    string Z3_G;
    string Z1_T;
    string Z2_T;
    string Z3_T;
    string Z1_K;
    string Z2_K;
    string Z3_K;
    string S1;
    string S2;
    string S3;
    string P1;
    string P2;
    string P3;
};


} // Kontakt

Q_DECLARE_METATYPE(Kontakt::NodeTag22);

#endif // NODETAG22_H
