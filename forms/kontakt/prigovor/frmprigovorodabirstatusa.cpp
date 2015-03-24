#include "frmprigovorodabirstatusa.h"
#include "ui_frmprigovorodabirstatusa.h"

namespace Kontakt {

// [Class Constuctor]
FrmPrigovorOdabirStatusa::FrmPrigovorOdabirStatusa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorOdabirStatusa)
{
    ui->setupUi(this);

    ui->treePrigovorStatus->hideColumn(1);
    ui->treePrigovorStatus->hideColumn(2);
    ui->treePrigovorStatus->expandAll();

}

FrmPrigovorOdabirStatusa::~FrmPrigovorOdabirStatusa()
{
    delete ui;
}

// [Event Handlers]
void FrmPrigovorOdabirStatusa::on_treePrigovorStatus_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    m_iPrigovorFilter1 = item->text(1).toInt();
    m_iPrigovorFilter2 = item->text(2).toInt();
    m_strPrigovorStatus = item->text(0).toStdString();
}

}
