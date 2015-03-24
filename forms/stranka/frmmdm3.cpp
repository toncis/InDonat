#include "frmmdm3.h"
#include "ui_frmmdm3.h"
#include "itos.h"

namespace Stranka {
// [ Class Contructors ]
FrmMdm3::FrmMdm3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmMdm3)
{
    ui->setupUi(this);
}

FrmMdm3::~FrmMdm3()
{
    delete ui;
}

// [ Private Member Functions ]

// [ Event Handlers ]

}
