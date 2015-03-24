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
