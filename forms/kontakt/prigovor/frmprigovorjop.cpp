#include "frmprigovorjop.h"
#include "ui_frmprigovorjop.h"

namespace Kontakt {

// [Class Constuctor]
FrmPrigovorJop::FrmPrigovorJop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorJop)
{
    ui->setupUi(this);
}

FrmPrigovorJop::~FrmPrigovorJop()
{
    delete ui;
}

// [Event Handlers]
void FrmPrigovorJop::on_btnPotvrda_clicked()
{

}

}
