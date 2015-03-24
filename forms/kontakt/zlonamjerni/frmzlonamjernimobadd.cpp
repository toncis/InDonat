#include "frmzlonamjernimobadd.h"
#include "ui_frmzlonamjernimobadd.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

// [Class Constuctor]
FrmZlonamjerniMobAdd::FrmZlonamjerniMobAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmZlonamjerniMobAdd)
{
    ui->setupUi(this);
}

FrmZlonamjerniMobAdd::~FrmZlonamjerniMobAdd()
{
    delete ui;
}

// [Private Member Functions]


// [Event Handlers]

}
