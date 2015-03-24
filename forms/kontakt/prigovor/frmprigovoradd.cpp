#include "frmprigovoradd.h"
#include "ui_frmprigovoradd.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

// [Class Constuctor]
FrmPrigovorAdd::FrmPrigovorAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorAdd)
{
    ui->setupUi(this);
}

FrmPrigovorAdd::~FrmPrigovorAdd()
{
    delete ui;
}

// [Event Handlers]

}
