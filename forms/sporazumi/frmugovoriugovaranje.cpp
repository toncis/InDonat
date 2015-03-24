#include "frmugovoriugovaranje.h"
#include "ui_frmugovoriugovaranje.h"

namespace Sporazumi {

FrmUgovoriUgovaranje::FrmUgovoriUgovaranje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmUgovoriUgovaranje)
{
    ui->setupUi(this);
}

FrmUgovoriUgovaranje::~FrmUgovoriUgovaranje()
{
    delete ui;
}

}
