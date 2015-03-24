#ifndef WGDONATMENU4_H
#define WGDONATMENU4_H

#include <QWidget>
#include <QtWidgets>
#include <QListWidget>
#include <QTreeWidget>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
class QComboBox;
class QLineEdit;
class QLabel;
class QFrame;
class QToolBox;
class QWidget;
class QPushButton;
class QTreeLayout;
class QListLayout;
QT_END_NAMESPACE

namespace Log {

class WgDonatMenu4 : public QWidget
{
    Q_OBJECT

public:
    // [Classs Members]
    QVBoxLayout *m_vboxDonatStrankaImovina;
    // [0]
    QFrame *m_fraStrankaImovinaKlasaTitle;
    QLabel *m_lblStrankaKlaseTitle;
    QComboBox *m_cboStrankaImovinaKlase;
    // [1]
    QFrame *m_fraStrankaGrupaImovineTitle;
    QLabel *m_txtStrankaGrupaImovineId;
    QPushButton *m_btnStrankaNeaktivneGrupeImovine;
    QPushButton *m_btnStrankaGrupaImovineZurnal;
    QPushButton *m_btnStrankaGrupaImovineColapse;
    // [2]
    QFrame *m_fraStrankaGrupaImovine;
    QTreeWidget *m_treeStrankaGrupaImovine;
    // [3]
    QFrame *m_fraStrankaUgovorneObveze;
    QLabel *m_txtStrankaUgovorneObveze;
    QLabel *m_imgStrankaUgovorneObveze;
    QPushButton *m_btnStrankaUgovorneObveze;
    // [4]
    QFrame *m_fraStrankaImovinaTitle;
    QLabel *m_txtStrankaImovinaId;
    QPushButton *m_btnStrankaImovinaOprema;
    QPushButton *m_btnStrankaNeaktivnaImovina;
    QPushButton *m_btnStrankaImovinaColapse;
    // [5]
    QFrame *m_fraStrankaImovina;
    QTreeWidget *m_treeStrankaImovina;
    // [6]
    QFrame *m_fraStrankaImovinaStatusTitle;
    QLabel *m_txtStrankaImovinaStatus;
    // [7]
    QFrame *m_fraStrankaImovinaStatus;
    QListWidget *m_lstStrankaImovinaStatus;

    // [Class Contructor]
    explicit WgDonatMenu4(QWidget *parent = 0);
    ~WgDonatMenu4();

signals:

public slots:

private slots:
    // [Event Handlers]
    void on_btnStrankaGrupaImovineColapse_clicked();
    void on_btnStrankaImovinaColapse_clicked();

private:
    // [Private Member Functions]
    void createStrankaKlaseTitle();
    void createStrankaGrupaImovineTitle();
    void createStrankaGrupaImovine();
    void createStrankaUgovornaObveza();
    void createStrankaImovinaTitle();
    void createStrankaImovina();
    void createStrankaImovinaStatusTitle();
    void createStrankaImovinaStatus();
};

}   // namespace log

#endif // WGDONATMENU4_H
