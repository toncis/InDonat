#include "frmobavijestislanje.h"
#include "ui_frmobavijestislanje.h"

namespace Sporazumi {

FrmObavijestiSlanje::FrmObavijestiSlanje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmObavijestiSlanje)
{
    ui->setupUi(this);
}

FrmObavijestiSlanje::~FrmObavijestiSlanje()
{
    delete ui;
}

}
