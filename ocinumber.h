//
//  ocinumber.h
//
// This file contains the definitions of OCCI Number conversions
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

#ifndef OCINUMBER_H
#define OCINUMBER_H

//#include <occi.h>
#include "donat.h"
#include "itos.h"

//using namespace oracle::occi;

namespace cttl {

/**Converts integer to string.
*
* From Bjarne Stroustrup's C++ Style and Technique FAQ:
* http://www.research.att.com/~bs/bs_faq2.html
*
* How do I convert an integer to a string?
* The simplest way is to use a stringstream:
*
@code
        int i = 127;
        std::string ss = itos( i );
@endcode
*
* For a description of string streams, see 21.5.3
* of The C++ Programming Language.
*
*/

static inline oracle::occi::Number getONumber(const std::string strNumber)
{
    oracle::occi::Number retValue = 0;
    retValue.fromText(
                g_DonatEnv,
                strNumber,
                "9999999999999");
    return retValue;
}

static inline oracle::occi::Number getONumber(const long long iNumber)
{
    return getONumber(cttl::itos(iNumber));
}

static inline std::string getStrAsONumber(const oracle::occi::Number nNumber)
{
    std::string retValue;
    retValue = nNumber.toText(
                g_DonatEnv,
                "9999999999999");
    retValue = cttl::trim(retValue);
    return retValue;
}

static inline long long getLongLongAsONumber(const oracle::occi::Number nNumber)
{
    return atoi(getStrAsONumber(nNumber).c_str());
}

static inline unsigned int getUIntAsONumber(const oracle::occi::Number nNumber)
{
    return atoll(getStrAsONumber(nNumber).c_str());
}


}   // namespace cttl

#endif // OCINUMBER_H
