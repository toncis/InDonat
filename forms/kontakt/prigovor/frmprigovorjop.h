#ifndef FRMPRIGOVORJOP_H
#define FRMPRIGOVORJOP_H

#include <QDialog>
#include "donat.h"

namespace Ui {
class FrmPrigovorJop;
}

namespace Kontakt {
class FrmPrigovorJop : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorJop(QWidget *parent = 0);
    ~FrmPrigovorJop();

private slots:
    void on_btnPotvrda_clicked();

private:
    Ui::FrmPrigovorJop *ui;
};

}
#endif // FRMPRIGOVORJOP_H
