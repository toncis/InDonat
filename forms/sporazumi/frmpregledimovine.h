#ifndef FRMPREGLEDIMOVINE_H
#define FRMPREGLEDIMOVINE_H

#include <QDialog>
#include "donat.h"

namespace Ui {
    class FrmPregledImovine;
}

namespace Sporazumi {

class FrmPregledImovine : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPregledImovine(unsigned int iGrupaImovineId, QWidget *parent = 0);
    ~FrmPregledImovine();

private:
    Ui::FrmPregledImovine *ui;

    unsigned int m_iGrupaImovineId;

    void fillImovina(unsigned int iGrupaImovineId);
};


} // namespace sporazumi

#endif // FRMPREGLEDIMOVINE_H
