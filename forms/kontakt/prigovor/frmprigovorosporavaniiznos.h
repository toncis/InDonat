#ifndef FRMPRIGOVOROSPORAVANIIZNOS_H
#define FRMPRIGOVOROSPORAVANIIZNOS_H

#include <QDialog>
#include "donat.h"

namespace Ui {
class FrmPrigovorOsporavaniIznos;
}

namespace Kontakt {

class FrmPrigovorOsporavaniIznos : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorOsporavaniIznos(QWidget *parent = 0);
    ~FrmPrigovorOsporavaniIznos();

private slots:
    void on_btnPotvrda_clicked();

private:
    Ui::FrmPrigovorOsporavaniIznos *ui;
};

}
#endif // FRMPRIGOVOROSPORAVANIIZNOS_H
