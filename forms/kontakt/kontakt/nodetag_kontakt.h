#ifndef NODETAG_KONTAKT_H
#define NODETAG_KONTAKT_H

#include <QMetaType>
#include "donat.h"

namespace Kontakt {

class NodeTag_Nod11
{

public:
    NodeTag_Nod11();
    NodeTag_Nod11(const NodeTag_Nod11 &other);
    ~NodeTag_Nod11();

    unsigned int NOD_OSOBA_ID;
    string NOD_OSOBA_NAZ;
    int NOD_KNT_TIP;
    string NOD_KNT_VALUE;
    int NOD_KNT_STATUS;
};


} // Kontakt

Q_DECLARE_METATYPE(Kontakt::NodeTag_Nod11);

#endif // NODETAG_KONTAKT_H
