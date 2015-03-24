#include "frmmdm2.h"
#include "ui_frmmdm2.h"
#include "itos.h"

namespace Stranka {
// [ Class Contructors ]
FrmMdm2::FrmMdm2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmMdm2)
{
    ui->setupUi(this);
}

FrmMdm2::~FrmMdm2()
{
    delete ui;
}

// [ Private Member Functions ]

// [ Event Handlers ]

}
