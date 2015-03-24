#include "frmprigovorodobrenje.h"
#include "ui_frmprigovorodobrenje.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

// [Class Constuctor]
FrmPrigovorOdobrenje::FrmPrigovorOdobrenje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorOdobrenje)
{
    ui->setupUi(this);
}

FrmPrigovorOdobrenje::~FrmPrigovorOdobrenje()
{
    delete ui;
}

// [Private Member Functions]

// [Event Handlers]

}
