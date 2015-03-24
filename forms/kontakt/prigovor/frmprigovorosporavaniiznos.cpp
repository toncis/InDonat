#include "frmprigovorosporavaniiznos.h"
#include "ui_frmprigovorosporavaniiznos.h"

namespace Kontakt {

// [Class Constructor]
FrmPrigovorOsporavaniIznos::FrmPrigovorOsporavaniIznos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorOsporavaniIznos)
{
    ui->setupUi(this);
}

FrmPrigovorOsporavaniIznos::~FrmPrigovorOsporavaniIznos()
{
    delete ui;
}

// [Event Handlers]
void FrmPrigovorOsporavaniIznos::on_btnPotvrda_clicked()
{

}

}
