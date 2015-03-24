#include "frmprigovoredit.h"
#include "ui_frmprigovoredit.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

// [Class Constuctor]
FrmPrigovorEdit::FrmPrigovorEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorEdit)
{
    ui->setupUi(this);
}

FrmPrigovorEdit::~FrmPrigovorEdit()
{
    delete ui;
}

// [Event Handlers]

}
