#include "frmprigovorstatus.h"
#include "ui_frmprigovorstatus.h"

namespace Kontakt {

// [Class Constuctor]
FrmPrigovorStatus::FrmPrigovorStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorStatus)
{
    ui->setupUi(this);
}

FrmPrigovorStatus::~FrmPrigovorStatus()
{
    delete ui;
}

// [Event Handlers]

}

void Kontakt::FrmPrigovorStatus::on_btnPotvrda_clicked()
{

}
