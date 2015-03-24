#ifndef FRMSTRANKAFIZ_H
#define FRMSTRANKAFIZ_H

#include <QDialog>
#include <QDate>
#include <QTreeWidgetItem>
#include "donat.h"

namespace Ui {
    class FrmStrankaFiz;
}

namespace Stranka {

class FrmStrankaFiz : public QDialog
{
    Q_OBJECT

public:
    explicit FrmStrankaFiz(QWidget *parent = 0);
    explicit FrmStrankaFiz(unsigned int iStrankaId, QWidget *parent = 0);
    ~FrmStrankaFiz();

private slots:
    void on_txtTitula_textEdited(const QString &strTitle);

    void on_txtAdresa_textEdited(const QString &strAdresa);

    void on_treeSifarnik_itemPressed(QTreeWidgetItem *item, int column);

    void on_btnTipStranke_clicked();

    void on_btnPorez_clicked();

    void on_btnAtributi_clicked();

    void on_btnNovaAdresa_clicked();

    void on_btnPomjenaAdrese_clicked();

    void on_btnOibPorezna_clicked();

    void on_btnFileNet_clicked();

    void on_btnSkeniranje_clicked();

    void on_btnMdmProvjeraOib_clicked();

private:
    Ui::FrmStrankaFiz *ui;

    // Stranka sifarnik
    enum StrankaSifarnikMode
    {
        SifarnikModeNone   = 0,
        SifarnikModeTitule = 1,
        SifarnikModeAdrese = 2
    };

    StrankaSifarnikMode m_SifranikMode;


    unsigned int m_iStrankaId;
    unsigned int m_iKupacId;
    unsigned int m_iAdresaId;
    string m_strMjesto;
    string m_strUlica;
    string m_strKucniBroj;

    int m_iTitulaId;
    bool m_bSmijePromjena;

    QDate m_dateDatumKreiranja;
    QDate m_DateRodjendan;

    void popuniStranku();
    void popuniKupca();
    void popuniAdresuStranke();
    void popuniSveAdreseStranke();
    void popuniDatumRodjenja();
    void popuniTitulu();
    void popuniTitule(const string strTitle);
    void provjeraPromjene();
    void provjeraPaperCLipDocuments();


};

} // Stranka

#endif // FRMSTRANKAFIZ_H
