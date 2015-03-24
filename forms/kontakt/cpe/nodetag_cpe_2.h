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
