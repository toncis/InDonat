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
