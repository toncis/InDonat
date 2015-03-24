/************************************* Module Header **************************************\
* Module Name:  ocinumber.h
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the definitions of OCCI Number conversions
*
* For more information see the Books Online and documentation.
* *****************************************************************************************
* All rights reserved.
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
* OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
* FITNESS FOR A PARTICULAR PURPOSE.
* * *****************************************************************************************
* Release History :
*
* VERSION	DESCRIPTION
* 	1.0		Created by Tonci Svilicic
\******************************************************************************************/

/**@file ocinumber.h
 * @brief OCCI Numbers to string and back conversion functions.
 *
 */

// ocinumber.h

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
