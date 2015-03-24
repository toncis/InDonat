#include "frmzlonamjerniadd.h"
#include "ui_frmzlonamjerniadd.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

// [Class Constuctor]
FrmZlonamjerniAdd::FrmZlonamjerniAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmZlonamjerniAdd)
{
    ui->setupUi(this);
}

FrmZlonamjerniAdd::~FrmZlonamjerniAdd()
{
    delete ui;
}

// [Private Member Functions]


// [Event Handlers]

}
