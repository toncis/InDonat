#include "frmkontaktnicentarpretraga.h"
#include "ui_frmkontaktnicentarpretraga.h"

namespace Kontakt {

// [Class Constructor]
FrmKontaktniCentarPretraga::FrmKontaktniCentarPretraga(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKontaktniCentarPretraga)
{
    ui->setupUi(this);

    ui->treeStranke->setColumnWidth(0, 240);
    ui->treeStranke->hideColumn(1);
    ui->treeStranke->hideColumn(2);
    ui->treeStranke->hideColumn(3);
    ui->treeStranke->hideColumn(4);
    ui->treeStranke->hideColumn(5);
}

FrmKontaktniCentarPretraga::~FrmKontaktniCentarPretraga()
{
    delete ui;
}

// [Private member Functions]
void FrmKontaktniCentarPretraga::traziDonatKorisnikaPoNazivu()
{
}

// [Event Hnadlers]
void FrmKontaktniCentarPretraga::on_btnSearchByName_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByPhone_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByJmbg_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByOib_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByUlogaStrankeId_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByGrupaImovineId_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnSearchByTicketId_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnFilterByCity_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnFilterByStreet_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnTrazi_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnPreuzmiStranku_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnPreuzmiTelefon_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnFizickaOsoba_clicked()
{

}

void FrmKontaktniCentarPretraga::on_btnPravnaOsoba_clicked()
{

}

}


