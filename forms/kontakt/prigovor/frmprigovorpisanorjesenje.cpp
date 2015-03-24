#include "frmprigovorpisanorjesenje.h"
#include "ui_frmprigovorpisanorjesenje.h"

namespace Kontakt {

// [Class Constructor]
FrmPrigovorPisanoRjesenje::FrmPrigovorPisanoRjesenje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorPisanoRjesenje)
{
    ui->setupUi(this);
}

FrmPrigovorPisanoRjesenje::~FrmPrigovorPisanoRjesenje()
{
    delete ui;
}

// [Event Handlers]

}
