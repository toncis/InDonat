//
//  itos.h
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

#ifndef _CTTL_ITOS_H_INCLUDED_
#define _CTTL_ITOS_H_INCLUDED_

#include <iostream>
#include <string>
#include <sstream>

#include <algorithm>
#include <functional>
#include <locale>


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
static inline std::string itos( int i )
{
    std::stringstream s;
    s << i;
    return s.str();
}

static inline std::string itos( unsigned int i )
{
    std::stringstream s;
    s << i;
    return s.str();
}

static inline std::string itos( long long i )
{
    std::stringstream s;
    s << i;
    return s.str();
}

static inline std::string concatenate(std::string const& name, int i)
{
    std::stringstream s;
    s << name << i;
    return s.str();
}

static inline std::string concatenate(std::string const& name, unsigned int i)
{
    std::stringstream s;
    s << name << i;
    return s.str();
}

static inline std::string concatenate(std::string const& name, long long i)
{
    std::stringstream s;
    s << name << i;
    return s.str();
}

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

//enum STR2INT_ERROR { SUCCESS = 0, OVERFLOW = 1, UNDERFLOW = 2, INCONVERTIBLE = 3 };

//STR2INT_ERROR str2int (int &i, char const *s, int base = 0)
//{
//    char *end;
//    long  l;
//    errno = 0;
//    l = strtol(s, &end, base);
//    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
//        return OVERFLOW;
//    }
//    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
//        return UNDERFLOW;
//    }
//    if (*s == '\0' || *end != '\0') {
//        return INCONVERTIBLE;
//    }
//    i = l;
//    return SUCCESS;
//}

static inline bool str2int (int &i, char const *s)
{
    char c;
    std::stringstream ss(s);
    ss >> i;
    if (ss.fail() || ss.get(c)) {
        // not an integer
        return false;
    }
    return true;
}

static inline bool str2int (unsigned int &i, char const *s)
{
    char c;
    std::stringstream ss(s);
    ss >> i;
    if (ss.fail() || ss.get(c)) {
        // not an integer
        return false;
    }
    return true;
}

static inline bool str2int (int &i, std::string &s)
{
    char c;
    std::stringstream ss(s);
    ss >> i;
    if (ss.fail() || ss.get(c)) {
        // not an integer
        return false;
    }
    return true;
}

static inline bool str2int (unsigned int &i, std::string &s)
{
    char c;
    std::stringstream ss(s);
    ss >> i;
    if (ss.fail() || ss.get(c)) {
        // not an integer
        return false;
    }
    return true;
}

static inline bool strisint (std::string &s)
{
    char c;
    int i;
    std::stringstream ss(s);
    ss >> i;
    if (ss.fail() || ss.get(c)) {
        // not an integer
        return false;
    }
    return true;
}

}   // namespace cttl

#endif // _CTTL_ITOS_H_INCLUDED_
