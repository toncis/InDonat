#ifndef FRMKONTAKTDOKUMENTI_H
#define FRMKONTAKTDOKUMENTI_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"


namespace Ui {
class FrmKontaktDokumenti;
}

namespace Kontakt {
class FrmKontaktDokumenti : public QDialog
{
    Q_OBJECT

public:
    explicit FrmKontaktDokumenti(QWidget *parent = 0);
    ~FrmKontaktDokumenti();

private:
    Ui::FrmKontaktDokumenti *ui;
};

}
#endif // FRMKONTAKTDOKUMENTI_H
