#include "frmobavijestiposlane.h"
#include "ui_frmobavijestiposlane.h"

namespace Sporazumi {

// [ Class Constructor]
FrmObavijestiPoslane::FrmObavijestiPoslane(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmObavijestiPoslane)
{
    ui->setupUi(this);
}

FrmObavijestiPoslane::~FrmObavijestiPoslane()
{
    delete ui;
}

// [ Class Constructor]
void FrmObavijestiPoslane::initFormView()
{
}

// [ Event Handlers]
void FrmObavijestiPoslane::on_btnKanalProdaje_clicked()
{

}

}

