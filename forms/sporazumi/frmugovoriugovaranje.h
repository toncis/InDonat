#ifndef FRMUGOVORIUGOVARANJE_H
#define FRMUGOVORIUGOVARANJE_H

#include <QDialog>

namespace Ui {
class FrmUgovoriUgovaranje;
}

namespace Sporazumi {

class FrmUgovoriUgovaranje : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmUgovoriUgovaranje(QWidget *parent = 0);
    ~FrmUgovoriUgovaranje();
    
private:
    Ui::FrmUgovoriUgovaranje *ui;
};

}
#endif // FRMUGOVORIUGOVARANJE_H
