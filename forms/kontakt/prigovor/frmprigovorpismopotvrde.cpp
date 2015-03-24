#include "frmprigovorpismopotvrde.h"
#include "ui_frmprigovorpismopotvrde.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

// [Class Constuctor]
FrmPrigovorPismoPotvrde::FrmPrigovorPismoPotvrde(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorPismoPotvrde)
{
    ui->setupUi(this);
}

FrmPrigovorPismoPotvrde::~FrmPrigovorPismoPotvrde()
{
    delete ui;
}

// [Private Member Functions]

// [Event Handlers]

}
