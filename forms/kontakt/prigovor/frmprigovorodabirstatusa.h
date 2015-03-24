#ifndef FRMPRIGOVORODABIRSTATUSA_H
#define FRMPRIGOVORODABIRSTATUSA_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
class FrmPrigovorOdabirStatusa;
}

namespace Kontakt {
class FrmPrigovorOdabirStatusa : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPrigovorOdabirStatusa(QWidget *parent = 0);
    ~FrmPrigovorOdabirStatusa();

    int m_iPrigovorFilter1;
    int m_iPrigovorFilter2;
    string m_strPrigovorStatus;

private slots:
    void on_treePrigovorStatus_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::FrmPrigovorOdabirStatusa *ui;
};

}
#endif // FRMPRIGOVORODABIRSTATUSA_H
