#include "frmkontaktdokumenti.h"
#include "ui_frmkontaktdokumenti.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {
// [ Class Constructor ]
FrmKontaktDokumenti::FrmKontaktDokumenti(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKontaktDokumenti)
{
    ui->setupUi(this);
}

FrmKontaktDokumenti::~FrmKontaktDokumenti()
{
    delete ui;
}

// [ Private Member Functions ]

// [ Event Handlers ]

}
