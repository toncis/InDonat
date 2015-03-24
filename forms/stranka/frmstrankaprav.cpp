#include "frmstrankaprav.h"
#include "ui_frmstrankaprav.h"

namespace Stranka {

// [Class Constructor]
FrmStrankaPrav::FrmStrankaPrav(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmStrankaPrav)
{
    ui->setupUi(this);
}
FrmStrankaPrav::FrmStrankaPrav(unsigned int iStrankaId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmStrankaPrav)
{
    ui->setupUi(this);

//    m_bSmijePromjena = false;
    m_iStrankaId = iStrankaId;
//    popuniStranku();
}


// [Class Destructor]
FrmStrankaPrav::~FrmStrankaPrav()
{
    delete ui;
}

} //Stranka
