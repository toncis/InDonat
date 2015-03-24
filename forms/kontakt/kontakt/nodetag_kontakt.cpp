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
