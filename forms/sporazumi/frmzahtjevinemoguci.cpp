#include "frmzahtjevinemoguci.h"
#include "ui_frmzahtjevinemoguci.h"

namespace Sporazumi {

FrmZahtjeviNemoguci::FrmZahtjeviNemoguci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmZahtjeviNemoguci)
{
    ui->setupUi(this);
}

FrmZahtjeviNemoguci::~FrmZahtjeviNemoguci()
{
    delete ui;
}

}
