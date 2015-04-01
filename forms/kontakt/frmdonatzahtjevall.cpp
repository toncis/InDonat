//
//  frmdonatzahtjevall.cpp
//
//  Author:
//       Tonči Sviličić <tonci.svilicic@in2.hr>
//
//  Copyright (c) 2012 Tonči Sviličić
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "frmdonatzahtjevall.h"
#include "ui_frmdonatzahtjevall.h"
#include "itos.h"

namespace Kontakt {

/* [Class Contructor] */
FrmDonatZahtjevAll::FrmDonatZahtjevAll(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmDonatZahtjevAll)
{
    ui->setupUi(this);

    ui->fraZahtjevSifarnik->setVisible(false);
    ui->fraListUlogaStranke->setVisible(false);
    ui->fraAtributiImovine->setVisible(false);
    ui->fraStrankaImovina->setVisible(false);

    ui->line_5->setVisible(false);
    ui->btnAktivnostSporazum->setVisible(false);
    ui->btnAktivnostUkloni->setVisible(false);
    ui->line_6->setVisible(false);

    ui->treeUlogaStranke->hideColumn(1);
    ui->treeUlogaStranke->hideColumn(2);
    ui->treeUlogaStranke->hideColumn(3);

    ui->treeStrankaImovina->setColumnWidth(0, 30);
    ui->treeStrankaImovina->hideColumn(1);
    ui->treeStrankaImovina->hideColumn(3);
    ui->treeStrankaImovina->hideColumn(4);
    ui->treeStrankaImovina->hideColumn(5);
    ui->treeStrankaImovina->hideColumn(6);

    ui->treeRaspoloziveUsluge->hideColumn(0);
//    ui->treeRaspoloziveUsluge->hideColumn(1);
    ui->treeRaspoloziveUsluge->hideColumn(2);
}

FrmDonatZahtjevAll::FrmDonatZahtjevAll(
    unsigned int iStrankaId,
    unsigned int iGrupaImovineId,
    QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmDonatZahtjevAll)
{
    ui->setupUi(this);

    ui->fraZahtjevSifarnik->setVisible(false);
    ui->fraListUlogaStranke->setVisible(false);
    ui->fraAtributiImovine->setVisible(false);
    ui->fraStrankaImovina->setVisible(false);

    ui->line_5->setVisible(false);
    ui->btnAktivnostSporazum->setVisible(false);
    ui->btnAktivnostUkloni->setVisible(false);
    ui->line_6->setVisible(false);

    ui->treeUlogaStranke->hideColumn(1);
    ui->treeUlogaStranke->hideColumn(2);
    ui->treeUlogaStranke->hideColumn(3);

    ui->treeStrankaImovina->setColumnWidth(0, 30);
    ui->treeStrankaImovina->hideColumn(1);
    ui->treeStrankaImovina->hideColumn(3);
    ui->treeStrankaImovina->hideColumn(4);
    ui->treeStrankaImovina->hideColumn(5);
    ui->treeStrankaImovina->hideColumn(6);

    ui->treeRaspoloziveUsluge->hideColumn(0);
//    ui->treeRaspoloziveUsluge->hideColumn(1);
    ui->treeRaspoloziveUsluge->hideColumn(2);

    m_iStrankaId = iStrankaId;
    m_iGrupaImovineId = iGrupaImovineId;
    init();
}

/* [Private Member Functions] */
void FrmDonatZahtjevAll::init()
{
    ui->dateDatumZahtjeva->setDateTime(QDateTime::currentDateTime());
    ui->txtJopBroj->setText(tr("0"));
    ui->txtBrojSpisa->setText(tr("0"));
    m_iTipZahtjeva = 1;
    setDatum();
    setDokumentNo();
    popunaStranka();
    popunaTelGim();
    popunaRi();
    popunaMo();
}
void FrmDonatZahtjevAll::setDatum()
{

}
void FrmDonatZahtjevAll::setDokumentNo()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT BROJDOK_ID_SEQ.NEXTVAL ID FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_strBrojDokumenta = rs->getString(1);
            m_strBrojDokumenta.append(" / ");
            m_strBrojDokumenta.append(QDate::currentDate().toString("yy").toStdString());
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT SPORAZUM_ID_SEQ.NEXTVAL ID FROM DUAL ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_iSporazumId = rs->getUInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    m_iTipDokumenta = 1;
    m_iNadSporazumId = 0;
    ui->txtTipZahtjeva->setText(tr("REDOVNI ZAHTJEV"));
    ui->txtBrojDokumenta->setText(QString::fromStdString(m_strBrojDokumenta));
}
void FrmDonatZahtjevAll::popunaStranka()
{
    if(m_iStrankaId == 0)
        return;

    ui->treeUlogaStranke->clear();

    m_iTipStrankeId = 0;
    m_iAdresaIdInstalacijeAktivna = 0;
    m_strKupacUloga1.clear();
    m_strKupacUloga2.clear();
    m_strKupacUloga3.clear();
    m_strKupacUloga4.clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT ULSTRANKE_ID, TULSTRANKE_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, TSTRANKE1_ID, ADRESA_ID ");
    strSqlStatement.append("FROM HIJERARHIJA_STR_ADRESE WHERE ROOT_STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append(" ORDER BY TULSTRANKE_ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listUlogeStranaka;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int iTipUlogeStrankeId = rs->getInt(2);
            switch(iTipUlogeStrankeId)
            {
                case 1:
                {
                    m_iKupacId = rs->getUInt(1);
                    m_strKupacNaziv = rs->getString(3);
                    m_strKupacUloga1 = rs->getString(1);
                    m_iTipStrankeId = rs->getInt(5);
                    QString strKupacTitle;
                    strKupacTitle.append(tr("KUPAC - "));
                    strKupacTitle.append(QString::fromStdString(rs->getString(1)));
                    strKupacTitle.append(tr(" - "));
                    strKupacTitle.append(QString::fromStdString(m_strKupacNaziv));
                    strKupacTitle.append(tr(" ... "));
                    strKupacTitle.append(QString::fromStdString(rs->getString(4)));
                    ui->lblKupacTitle->setText(strKupacTitle);
                    break;
                }
                case 2:
                {
                    m_iKontaktId = rs->getUInt(1);
                    m_strKupacUloga2 = rs->getString(1);
                    break;
                }
                case 3:
                {
                    m_strKupacUloga3 = rs->getString(1);
                    QString strUlogaStranke;
                    strUlogaStranke.append(tr("RAČUN - "));
                    strUlogaStranke.append(QString::fromStdString(rs->getString(1)));
                    strUlogaStranke.append(tr(" ... "));
                    strUlogaStranke.append(QString::fromStdString(rs->getString(4)));
                    QTreeWidgetItem *itemUlogaStrankeRacun = new QTreeWidgetItem();
                    itemUlogaStrankeRacun->setText(0, strUlogaStranke);
                    itemUlogaStrankeRacun->setText(1, QString::fromStdString(rs->getString(3)));
                    itemUlogaStrankeRacun->setText(2, QString::fromStdString(rs->getString(1)));
                    itemUlogaStrankeRacun->setText(3, tr("1"));
                    QTreeWidgetItem *itemUlogaStrankeRacunNaziv = new QTreeWidgetItem();
                    itemUlogaStrankeRacunNaziv->setText(0, QString::fromStdString(rs->getString(3)));
                    itemUlogaStrankeRacunNaziv->setText(1, QString::fromStdString(rs->getString(2)));
                    itemUlogaStrankeRacunNaziv->setText(2, QString::fromStdString(rs->getString(1)));
                    itemUlogaStrankeRacunNaziv->setText(3, tr("1"));
                    itemUlogaStrankeRacun->addChild(itemUlogaStrankeRacunNaziv);
                    listUlogeStranaka.append(itemUlogaStrankeRacun);
                    listUlogeStranaka.append(itemUlogaStrankeRacunNaziv);
                    break;
                }
                case 4:
                {
                    m_strKupacUloga4 = rs->getString(1);
                    m_iAdresaIdInstalacijeAktivna = rs->getUInt(6);
                    QString strUlogaStranke;
                    strUlogaStranke.append(tr("INSTALACIJA - "));
                    strUlogaStranke.append(QString::fromStdString(rs->getString(1)));
                    strUlogaStranke.append(tr(" ... "));
                    strUlogaStranke.append(QString::fromStdString(rs->getString(4)));
                    QTreeWidgetItem *itemUlogaStrankeInstalacija = new QTreeWidgetItem();
                    itemUlogaStrankeInstalacija->setText(0, strUlogaStranke);
                    itemUlogaStrankeInstalacija->setText(1, QString::fromStdString(rs->getString(3)));
                    itemUlogaStrankeInstalacija->setText(2, QString::fromStdString(rs->getString(1)));
                    itemUlogaStrankeInstalacija->setText(3, tr("1"));
                    QTreeWidgetItem *itemUlogaStrankeInstalacijaNaziv = new QTreeWidgetItem();
                    itemUlogaStrankeInstalacijaNaziv->setText(0, QString::fromStdString(rs->getString(3)));
                    itemUlogaStrankeInstalacijaNaziv->setText(1, QString::fromStdString(rs->getString(2)));
                    itemUlogaStrankeInstalacijaNaziv->setText(2, QString::fromStdString(rs->getString(1)));
                    itemUlogaStrankeInstalacijaNaziv->setText(3, tr("1"));
                    itemUlogaStrankeInstalacija->addChild(itemUlogaStrankeInstalacijaNaziv);
                    listUlogeStranaka.append(itemUlogaStrankeInstalacija);
                    listUlogeStranaka.append(itemUlogaStrankeInstalacijaNaziv);
                    break;
                }
                default:
                {
//                    QTreeWidgetItem *itemUlogaStranke = new QTreeWidgetItem();
//                    itemUlogaStranke->setText(0, QString::fromStdString(rs->getString(2)));
//                    itemUlogaStranke->setText(1, QString::fromStdString(rs->getString(1)));
//                    itemUlogaStranke->setText(2, QString::fromStdString(rs->getString(3)));
//                    itemUlogaStranke->setText(3, tr("1"));
//                    listUlogeStranaka.append(itemUlogaStranke);
                    break;
                }
            }
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if(!listUlogeStranaka.empty())
    {
        listUlogeStranaka.first()->setSelected(true);
        ui->treeUlogaStranke->insertTopLevelItems(0, listUlogeStranaka);
//        ui->treeUlogaStranke->setCurrentItem(listUlogeStranaka.first());
        ui->treeUlogaStranke->expandAll();
//      ui->treeUlogaStranke->collapseAll();
    }

}
void FrmDonatZahtjevAll::popunaTelGim()
{
    if(m_iGrupaImovineId == 0)
        return;

    NodeTag22 *nodeTag = new NodeTag22();
    nodeTag->Z1_G = "0";
    nodeTag->Z2_G = "0";
    nodeTag->Z3_G = "0";

    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    ui->btnImovinaPromjena->setEnabled(false);
    string strSqlStatement;
    strSqlStatement.append("SELECT TIP, ASSET, GIMOVINE_ID, NVL(TEL_BROJ,'-') TEL_BROJ, NVL(KLASA,'-') KLASA ");
    strSqlStatement.append(" FROM V_GIM_STRUKTURA_SVE WHERE GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    strSqlStatement.append(" ORDER BY TIP ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            string strTip;
            unsigned int iAsset;
            unsigned int iGrupaImovineId;
            string strTelBroj;
            string strKlasa;

            strTip = rs->getString(1);
            iAsset = rs->getUInt(2);
            iGrupaImovineId = rs->getUInt(3);
            strTelBroj = rs->getString(4);
            strKlasa = rs->getString(5);

            if(strTip == "1")
            {
                if(iAsset > 0)
                {
                    nodeTag->Z1_G = rs->getString(2);
                    nodeTag->Z1_T = strTelBroj;
                    nodeTag->Z1_K = strKlasa;
                    ui->btnImovinaOsnovna->setEnabled(true);
                }
            }
            else if(strTip == "2")
            {
                if(iAsset > 0)
                {
                    unsigned int iTempId;
                    if(cttl::str2int(iTempId, nodeTag->Z1_G) == false)
                    {
                        return;
                    }
                    if(jeLiMax3(iTempId) == 0)
                    {
                        nodeTag->Z2_G = rs->getString(2);
                        nodeTag->Z2_T = strTelBroj;
                        nodeTag->Z2_K = strKlasa;
                        ui->btnImovinaAdsl->setEnabled(true);
                    }
                }
            }
            else if(strTip == "3")
            {
                if(iAsset > 0)
                {
                    nodeTag->Z3_G = rs->getString(2);
                    nodeTag->Z3_T = strTelBroj;
                    nodeTag->Z3_K = strKlasa;
                    ui->btnImovinaSme->setEnabled(true);
                }
            }
        }
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    unsigned int iZ1g, iZ2g, iZ3g;
    if(cttl::str2int(iZ1g, nodeTag->Z1_G) == false)
    {
        return;
    }
    if(cttl::str2int(iZ2g, nodeTag->Z2_G) == false)
    {
        return;
    }
    if(cttl::str2int(iZ3g, nodeTag->Z3_G) == false)
    {
        return;
    }

    if(iZ1g > 0)
    {
        if(iZ2g == 0)
        {
            ui->btnProduktiAdsl->setEnabled(true);
        }
        else
        {
            if(iZ3g == 0)
            {
                ui->btnProduktiSme->setEnabled(true);
            }
        }
    }

    m_lstTree22.push_back(*nodeTag);
    m_iPaketTel = 0;
    m_iPaketAkt = 0;

    QString strItemNaziv;
    strItemNaziv.append(QString::fromStdString(nodeTag->Z1_T));
    strItemNaziv.append(tr("  "));
    strItemNaziv.append(QString::fromStdString(nodeTag->Z1_K));
    treeItem->setText(0, strItemNaziv);
    QVariant treeItemTag;
    treeItemTag.setValue(*nodeTag);
    treeItem->setData(0, Qt::UserRole, treeItemTag);
    ui->treeUlogaStranke->addTopLevelItem(treeItem);
    ui->treeUlogaStranke->expandAll();
}
void FrmDonatZahtjevAll::popunaRi()
{
    // [RIOL_LINIJA]
    QTreeWidgetItem *itemRiolLinija = new QTreeWidgetItem();
    itemRiolLinija->setText(0, tr("ISKLJUČENA IMOVINA NA ADRESI"));
    itemRiolLinija->setText(1, tr("20"));
    itemRiolLinija->setText(2, tr(""));
    itemRiolLinija->setText(3, tr("0"));
    QTreeWidgetItem *itemRiolLinijaStavka = new QTreeWidgetItem();
    itemRiolLinijaStavka->setText(0, tr("NEMA"));
    itemRiolLinijaStavka->setText(1, tr("A20"));
    itemRiolLinijaStavka->setText(2, tr(""));
    itemRiolLinijaStavka->setText(3, tr("0"));
    itemRiolLinija->addChild(itemRiolLinijaStavka);


    string strSqlStatement;
    strSqlStatement.append("SELECT COUNT(*) BROJ FROM RIOL_ASSET WHERE ISPORUKA_ID = ");
    strSqlStatement.append(m_strKupacUloga4);
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(rs->getInt(1) > 0)
            {
                itemRiolLinijaStavka->setText(0, tr("IMA - NIJE IZABRAN"));
                QBrush brushRed = itemRiolLinijaStavka->foreground(0);
                brushRed.setColor(Qt::red);
                itemRiolLinijaStavka->setForeground(0, brushRed);
                itemRiolLinija->setText(3, tr("1"));
                itemRiolLinijaStavka->setText(3, tr("1"));
            }
        }
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    ui->treeUlogaStranke->addTopLevelItem(itemRiolLinija);
    ui->treeUlogaStranke->addTopLevelItem(itemRiolLinijaStavka);
    ui->treeUlogaStranke->expandAll();
}
void FrmDonatZahtjevAll::popunaMo()
{
    // [Multiple_Order]
    QTreeWidgetItem *itemMultipleOrder = new QTreeWidgetItem();
    itemMultipleOrder->setText(0, tr("POSTOJEĆI ZAHTJEV"));
    itemMultipleOrder->setText(1, tr("10"));
    itemMultipleOrder->setText(2, tr(""));
    itemMultipleOrder->setText(3, tr("0"));
    QTreeWidgetItem *itemMultipleOrderStavka = new QTreeWidgetItem();
    itemMultipleOrderStavka->setText(0, tr("NEMA"));
    itemMultipleOrderStavka->setText(1, tr("A10"));
    itemMultipleOrderStavka->setText(2, tr(""));
    itemMultipleOrderStavka->setText(3, tr("0"));
    itemMultipleOrder->addChild(itemMultipleOrderStavka);


    string strSqlStatement;
    strSqlStatement.append("SELECT COUNT(*) BROJ FROM TAB_PREGLED_SPORAZUMI S, ULOGE_STRANAKA U ");
    strSqlStatement.append("WHERE S.HEAD_ID = U.ULSTRANKE_NAD_ID AND ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(m_iKupacId));
    strSqlStatement.append(" AND S.STANJE IN ('Ugovaranje','Realizacija','Provjera','Priprema') ");
    strSqlStatement.append(" AND S.TSPORAZUMA_ID IN (1,4) ORDER BY 1 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(rs->getInt(1) > 0)
            {
                itemMultipleOrderStavka->setText(0, tr("IMA - NIJE IZABRAN"));
                QBrush brushRed = itemMultipleOrderStavka->foreground(0);
                brushRed.setColor(Qt::red);
                itemMultipleOrderStavka->setForeground(0, brushRed);
                itemMultipleOrder->setText(3, tr("1"));
                itemMultipleOrderStavka->setText(3, tr("1"));
            }
        }
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    ui->treeUlogaStranke->addTopLevelItem(itemMultipleOrder);
    ui->treeUlogaStranke->addTopLevelItem(itemMultipleOrderStavka);
    ui->treeUlogaStranke->expandAll();
}

int FrmDonatZahtjevAll::jeLiMax3(unsigned int iGrupaImovineId)
{
    int retValue = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT JE_LI_MAX3 (");
    strSqlStatement.append(cttl::itos(iGrupaImovineId));
    strSqlStatement.append(") BROJ FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getInt(1);
        }
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
        retValue = 0;
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    return retValue;
}

void FrmDonatZahtjevAll::popunaKlasa()
{
    ui->treeRaspoloziveUsluge->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT PRODUKT_ID, NAZIV FROM V_DOSTUPNOST_KLASA_NOVI ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listDostupneUsluge;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemDostupnaUsluga = new QTreeWidgetItem();
            itemDostupnaUsluga->setText(0, QString::fromStdString(rs->getString(1)));
            itemDostupnaUsluga->setText(1, QString::fromStdString(rs->getString(2)));
            itemDostupnaUsluga->setText(2, tr("8"));
            listDostupneUsluge.append(itemDostupnaUsluga);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if(!listDostupneUsluge.empty())
    {
        listDostupneUsluge.first()->setSelected(true);
        ui->treeRaspoloziveUsluge->insertTopLevelItems(0, listDostupneUsluge);
//        ui->treeRaspoloziveUsluge->setCurrentItem(listDostupneUsluge.first());
        ui->treeRaspoloziveUsluge->expandAll();
//      ui->treeRaspoloziveUsluge->collapseAll();
    }

    setButtonsForKlasaAdd();
}
void FrmDonatZahtjevAll::popunaKlasaAdsl()
{
    ui->treeRaspoloziveUsluge->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT PRODUKT_ID,NAZIV FROM PRODUKTI WHERE PRODUKT_ID = 10304 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listDostupneUsluge;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemDostupnaUsluga = new QTreeWidgetItem();
            itemDostupnaUsluga->setText(0, QString::fromStdString(rs->getString(1)));
            itemDostupnaUsluga->setText(1, QString::fromStdString(rs->getString(2)));
            itemDostupnaUsluga->setText(2, tr("8"));
            listDostupneUsluge.append(itemDostupnaUsluga);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if(!listDostupneUsluge.empty())
    {
        listDostupneUsluge.first()->setSelected(true);
        ui->treeRaspoloziveUsluge->insertTopLevelItems(0, listDostupneUsluge);
//        ui->treeRaspoloziveUsluge->setCurrentItem(listDostupneUsluge.first());
        ui->treeRaspoloziveUsluge->expandAll();
//      ui->treeRaspoloziveUsluge->collapseAll();
    }

    setButtonsForKlasaAdd();
}
void FrmDonatZahtjevAll::popunaKlasaSme()
{
    ui->treeRaspoloziveUsluge->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT PRODUKT_ID,NAZIV FROM PRODUKTI WHERE PRODUKT_ID = 35365 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listDostupneUsluge;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemDostupnaUsluga = new QTreeWidgetItem();
            itemDostupnaUsluga->setText(0, QString::fromStdString(rs->getString(1)));
            itemDostupnaUsluga->setText(1, QString::fromStdString(rs->getString(2)));
            itemDostupnaUsluga->setText(2, tr("8"));
            listDostupneUsluge.append(itemDostupnaUsluga);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if(!listDostupneUsluge.empty())
    {
        listDostupneUsluge.first()->setSelected(true);
        ui->treeRaspoloziveUsluge->insertTopLevelItems(0, listDostupneUsluge);
//        ui->treeRaspoloziveUsluge->setCurrentItem(listDostupneUsluge.first());
        ui->treeRaspoloziveUsluge->expandAll();
//      ui->treeRaspoloziveUsluge->collapseAll();
    }

    setButtonsForKlasaAdd();
}
void FrmDonatZahtjevAll::setButtonsForKlasaAdd()
{
    ui->btnUslugaIskljuci->setEnabled(false);
    ui->btnUslugaAtributi->setEnabled(false);
    ui->btnUslugaUkloni->setEnabled(false);
    ui->btnImovinaPromjena->setEnabled(false);
    ui->btnImovinaSuspenzija->setEnabled(false);
    ui->btnImovinaResuspenzija->setEnabled(false);
    ui->btnImovinaIskljucenje->setEnabled(false);
//    Status13.Panels(0).Enabled = False  'PROMJENA
//    Status11.Panels(1).Enabled = False  'ISKLJUČENJE USLUGE
//    Status11.Panels(2).Enabled = False  'PROMJENA ATRIBUTA
//    Status11.Panels(3).Enabled = False  'UKLONI
//    Status12.Panels(1).Enabled = False  'SUSPENZIJA
//    Status12.Panels(2).Enabled = False  'RESUSPENZIJA
//    Status12.Panels(3).Enabled = False  'ISKLJUČENJE
//    If ZAH_TIP = 2 Then
//        Status10.Panels(1).Tag = 0          'OSNOVNI
//        Status10.Panels(2).Tag = 0          'ADSL
//        Status10.Panels(3).Tag = 0          'SME
//    End If
//    'P_STAT6.Text = 0
//    'Status6.Panels(1).Enabled = False
//    Status6.Panels(2).Enabled = False
//    Status6.Panels(3).Enabled = False
//    P_STAT5.Text = 0
//    Status5.Panels(1).Enabled = False
//    Status5.Panels(2).Enabled = False
//    Status5.Panels(3).Enabled = False
//    Status5.Panels(4).Enabled = False
}
void FrmDonatZahtjevAll::setButtonsClose()
{
    ui->treeRaspoloziveUsluge->clear();
    ui->btnUslugaIskljuci->setEnabled(false);
    ui->btnUslugaAtributi->setEnabled(false);
    ui->btnUslugaUkloni->setEnabled(false);
    ui->btnImovinaPromjena->setEnabled(false);
    ui->btnImovinaSuspenzija->setEnabled(false);
    ui->btnImovinaResuspenzija->setEnabled(false);
    ui->btnImovinaIskljucenje->setEnabled(false);
//    P_STAT5.Text = 0
//    Status_PPP.Visible = False
//    Status6.Panels(2).Enabled = False
//    Status6.Panels(3).Enabled = False
//    Status5.Panels(1).Enabled = False
//    Status5.Panels(2).Enabled = False
//    Status5.Panels(3).Enabled = False
//    Status5.Panels(4).Enabled = False
//    Status11.Panels(1).Enabled = False
//    Status11.Panels(2).Enabled = False
//    Status11.Panels(3).Enabled = False
//    'POSTOJEĆA IMOVINA-------------------------------------------
//    Status12.Panels(1).Enabled = False     'SUSPENZIJA
//    Status12.Panels(2).Enabled = False     'RESUSPENZIJA
//    Status12.Panels(3).Enabled = False     'ISKLJUČENJE
//    Status14.Panels(1).Enabled = False     'PROMJENA KLASE
//    Status14.Panels(2).Enabled = False     'PROMJENA INSTALACIJE
//    Status14.Panels(3).Enabled = False     'PROMJENA PRETPLATE

}

void FrmDonatZahtjevAll::popuniKupacTel()
{
    if(m_iStrankaId == 0)
    {
        return;
    }
    ui->treeStrankaImovina->clear();

    // [0. Get Uloga Stranke ID]
    unsigned int iUlogaStrankeId = 0;
    unsigned int iUlogaStrankeNadId = 0;
    string strSqlStatement;
    strSqlStatement.append("SELECT ULSTRANKE_ID, ULSTRANKE_NAD_ID FROM ULOGE_STRANAKA WHERE ROOT_STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append("  AND TULSTRANKE_ID = 1 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iUlogaStrankeId = rs->getUInt(1);
            iUlogaStrankeNadId = rs->getUInt(2);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iUlogaStrankeId == 0)
    {
        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
        return;
    }

    // [1. Get Grupe Imovine]
    QList<QTreeWidgetItem *> listGrupaImovine;
    strSqlStatement.clear();
    strSqlStatement.append("SELECT KUPAC_ID, TEL_BROJ, TEL_LIN_ID, IMOVINA_ID, GIMOVINE_ID, SLOG_STATUS, B2 ");
    if(iUlogaStrankeId == iUlogaStrankeNadId)
    {
        strSqlStatement.append("  FROM V_TEL_BROJ WHERE KUPAC_ID = ");
        strSqlStatement.append(cttl::itos(iUlogaStrankeId));
    }
    else
    {
        strSqlStatement.append("  FROM V_TEL_BROJ_HEAD WHERE HEAD_ID = ");
        strSqlStatement.append(cttl::itos(iUlogaStrankeNadId));
    }
    strSqlStatement.append("  AND B1 = 1 AND SLOG_STATUS > 0 ORDER BY SLOG_STATUS, TEL_LIN_ID ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QString strGrupaImovineNaziv;
            strGrupaImovineNaziv.append(QString::fromStdString(rs->getString(2)));
            strGrupaImovineNaziv.append(tr("   "));
            strGrupaImovineNaziv.append(QString::fromStdString(rs->getString(3)));
            string strStatus = rs->getString(6);
            QTreeWidgetItem *itemStrankaImovina = new QTreeWidgetItem();
            itemStrankaImovina->setText(1, QString::fromStdString(rs->getString(4)));
            itemStrankaImovina->setText(2, strGrupaImovineNaziv);
            itemStrankaImovina->setText(3, QString::fromStdString(rs->getString(1)));
            itemStrankaImovina->setText(4, QString::fromStdString(rs->getString(2)));
            itemStrankaImovina->setText(5, QString::fromStdString(rs->getString(5)));
            itemStrankaImovina->setText(6, QString::fromStdString(strStatus));
            int iStatus;
            if(cttl::str2int(iStatus, strStatus) == true)
            {
                if(iStatus == 0)
                {
                    itemStrankaImovina->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                }
                else if(iStatus > 1)
                {
                    itemStrankaImovina->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                }
            }
            listGrupaImovine.append(itemStrankaImovina);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    // [2. Izvuci ADSL]
    int iListSize = listGrupaImovine.size();
    for(int i = 0; i < iListSize; ++i)
    {
        unsigned int iBaseGrupaImovineId;
        string strBaseGrupaImovineId = listGrupaImovine.at(i)->text(5).toStdString();
        if(cttl::str2int(iBaseGrupaImovineId, strBaseGrupaImovineId) == true)
        {
            unsigned int iAdslGrupaImovineId = vratiAdslAsset(iBaseGrupaImovineId);
            if(iAdslGrupaImovineId > 0)
            {
                string strSqlStatement;
                strSqlStatement.append("SELECT IMOVINA_ID, SLOG_STATUS, TEL_BROJ, TEL_LIN_ID FROM B_HIJERARHIJA WHERE GIMOVINE_ID = ");
                strSqlStatement.append(cttl::itos(iAdslGrupaImovineId));
                Statement *sqlStatement = g_DonatConn->createStatement();
                sqlStatement->setSQL(strSqlStatement);

                try
                {
                    ResultSet *rs = sqlStatement->executeQuery();
                    if(rs->next())
                    {
                        QString strAdslGrupaImovineNaziv;
                        strAdslGrupaImovineNaziv.append(QString::fromStdString(rs->getString(3)));
                        strAdslGrupaImovineNaziv.append(tr("   "));
                        strAdslGrupaImovineNaziv.append(QString::fromStdString(rs->getString(4)));
                        string strStatus = rs->getString(2);
                        QTreeWidgetItem *itemStrankaAdslmovina = new QTreeWidgetItem();
                        itemStrankaAdslmovina->setText(1, QString::fromStdString(rs->getString(1)));
                        itemStrankaAdslmovina->setText(2, strAdslGrupaImovineNaziv);
                        itemStrankaAdslmovina->setText(3, listGrupaImovine.at(i)->text(3));
                        itemStrankaAdslmovina->setText(4, listGrupaImovine.at(i)->text(4));
                        itemStrankaAdslmovina->setText(5, listGrupaImovine.at(i)->text(5));
                        itemStrankaAdslmovina->setText(6, listGrupaImovine.at(i)->text(6));
                        int iStatus;
                        if(cttl::str2int(iStatus, strStatus) == true)
                        {
                            if(iStatus == 0)
                            {
                                itemStrankaAdslmovina->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                            }
                            else if(iStatus > 1)
                            {
                                itemStrankaAdslmovina->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                            }
                        }
                        listGrupaImovine.at(i)->addChild(itemStrankaAdslmovina);
                        listGrupaImovine.append(itemStrankaAdslmovina);
                    }
                    sqlStatement->closeResultSet(rs);
                }
                catch(SQLException &ex)
                {
                    QMessageBox::critical(this, tr("DONAT - Database Error"),
                                                   QString::fromStdString(ex.getMessage()),
                                                   QMessageBox::Close);
                }

                g_DonatConn->terminateStatement(sqlStatement);
                strSqlStatement.erase();

            }
        }
    }

    if(!listGrupaImovine.empty())
    {
        listGrupaImovine.first()->setSelected(true);
        ui->treeStrankaImovina->insertTopLevelItems(0, listGrupaImovine);
//        ui->treeStrankaImovina->setCurrentItem(listGrupaImovine.first());
        ui->treeStrankaImovina->expandAll();
//      ui->treeStrankaImovina->collapseAll();
    }
}


unsigned int FrmDonatZahtjevAll::vratiAdslAsset(unsigned int iGrupaImovineId)
{
    unsigned int retValue = 0;
    string strSqlStatement;
    strSqlStatement.append("SELECT VRATI_ADSL_ASSET(");
    strSqlStatement.append(cttl::itos(iGrupaImovineId));
    strSqlStatement.append(") BROJ FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getUInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    return retValue;
}

/* [Event Handlers] */
void FrmDonatZahtjevAll::on_btnOdustani_clicked()
{
    this->close();
}
void FrmDonatZahtjevAll::on_btnPotvrda_clicked()
{

}
void FrmDonatZahtjevAll::on_btnTipZahtjeva_clicked()
{
    if(m_iGrupaImovineId == 0)
        return;

    string strSqlStatement;
    strSqlStatement.append("SELECT SMIJE_LI_REZERVIRANI(");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    strSqlStatement.append(") SMIJE FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    int iSmijeRezervirani;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iSmijeRezervirani = rs->getInt(1);
        }
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if(iSmijeRezervirani == 0)
    {
//        QMessageBox::warning(this, tr("DONAT - Zahtjev"),
//                                   tr("Postoji aktivnost!"),
//                                   QMessageBox::Close);
        return;
    }

    ui->treeZahtjevSifarnik->clear();
    QTreeWidgetItem *itemTipZahtjeva1 = new QTreeWidgetItem();
    itemTipZahtjeva1->setText(0, tr("REDOVNI ZAHTJEV"));
    itemTipZahtjeva1->setText(1, tr("1"));
    QTreeWidgetItem *itemTipZahtjeva2 = new QTreeWidgetItem();
    itemTipZahtjeva2->setText(0, tr("REZERVIRANI ZAHTJEV"));
    itemTipZahtjeva2->setText(1, tr("8"));
    ui->treeZahtjevSifarnik->addTopLevelItem(itemTipZahtjeva1);
    ui->treeZahtjevSifarnik->addTopLevelItem(itemTipZahtjeva2);
    ui->treeZahtjevSifarnik->expandAll();

    ui->fraZahtjevSifarnik->setVisible(true);
    ui->fraZahtjevInfo->setVisible(false);
}
void FrmDonatZahtjevAll::on_pushButton_6_clicked()
{
}
void FrmDonatZahtjevAll::on_pushButton_7_clicked()
{
    ui->dateDatumZahtjeva->calendarPopup();
}
void FrmDonatZahtjevAll::on_pushButton_8_clicked()
{

}
void FrmDonatZahtjevAll::on_btnObvezePodmirene_clicked()
{

}
void FrmDonatZahtjevAll::on_btnObvezeNisuPodmirene_clicked()
{

}
void FrmDonatZahtjevAll::on_btnVaznostNiska_clicked()
{

}
void FrmDonatZahtjevAll::on_btnVaznostSrednja_clicked()
{

}
void FrmDonatZahtjevAll::on_btnVaznostVisoka_clicked()
{

}
void FrmDonatZahtjevAll::on_btnDokumenti_clicked()
{

}
void FrmDonatZahtjevAll::on_btnDatoteke_clicked()
{

}
void FrmDonatZahtjevAll::on_btnKontakt_clicked()
{

}
void FrmDonatZahtjevAll::on_btnPrivole_clicked()
{

}
void FrmDonatZahtjevAll::on_btnAktivnostLista_clicked()
{

}
void FrmDonatZahtjevAll::on_btnAktivnostDodljeli_clicked()
{

}
void FrmDonatZahtjevAll::on_btnAktivnostNova_clicked()
{

}
void FrmDonatZahtjevAll::on_btnAktivnostImfPodaci_clicked()
{

}
void FrmDonatZahtjevAll::on_btnAktivnostNumeracija_clicked()
{

}
void FrmDonatZahtjevAll::on_btnProduktiSveKlase_clicked()
{
    ui->btnUslugaIskljuci->setEnabled(false);
    ui->btnUslugaAtributi->setEnabled(false);
    ui->btnUslugaUkloni->setEnabled(false);
    ui->btnImovinaPromjena->setEnabled(false);
    ui->btnImovinaSuspenzija->setEnabled(false);
    ui->btnImovinaResuspenzija->setEnabled(false);
    ui->btnImovinaIskljucenje->setEnabled(false);
    popunaKlasa();
}
void FrmDonatZahtjevAll::on_btnProduktiAdsl_clicked()
{
    popunaKlasaAdsl();
}
void FrmDonatZahtjevAll::on_btnProduktiSme_clicked()
{
    popunaKlasaSme();
}
void FrmDonatZahtjevAll::on_btnProduktiUsluge_clicked()
{

}
void FrmDonatZahtjevAll::on_btnProduktiOpcije_clicked()
{

}
void FrmDonatZahtjevAll::on_btnProduktiMax23_clicked()
{

}
void FrmDonatZahtjevAll::on_btnUslugaIskljuci_clicked()
{

}
void FrmDonatZahtjevAll::on_btnUslugaAtributi_clicked()
{

}
void FrmDonatZahtjevAll::on_btnUslugaUkloni_clicked()
{

}
void FrmDonatZahtjevAll::on_btnPorez_clicked()
{

}
void FrmDonatZahtjevAll::on_btnPrikaziImovinu_clicked()
{
    if(ui->fraStrankaImovina->isVisible() == true)
    {
        return;
    }
    else
    {
        ui->fraImovinaActions->setVisible(false);
        ui->fraStrankaImovina->setVisible(true);
        popuniKupacTel();
    }
}
void FrmDonatZahtjevAll::on_btnPrikaziAtribute_clicked()
{
    if(ui->fraImovinaActions->isVisible() == true)
    {
        return;
    }
    else
    {
        ui->fraStrankaImovina->setVisible(false);
        ui->fraImovinaActions->setVisible(true);
    }
}
void FrmDonatZahtjevAll::on_treeZahtjevSifarnik_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    m_iTipDokumenta = item->text(1).toInt();
    ui->txtTipZahtjeva->setText(item->text(0));

    ui->fraZahtjevSifarnik->setVisible(true);
    ui->fraZahtjevInfo->setVisible(false);
}
void FrmDonatZahtjevAll::on_treeUlogaStranke_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    QString strTipUlogeStranke = item->text(1);
    QString strAktivan = item->text(3);
    // [Enabled]
    ui->btnAktivnostLista->setEnabled(true);
    ui->btnAktivnostDodljeli->setEnabled(true);
    ui->line->setEnabled(true);
    ui->btnAktivnostNova->setEnabled(true);
    ui->line_2->setEnabled(true);
    ui->btnAktivnostImfPodaci->setEnabled(true);
    ui->btnAktivnostNumeracija->setEnabled(true);
    // [Visible]
    ui->btnAktivnostLista->setVisible(false);
    ui->btnAktivnostDodljeli->setVisible(false);
    ui->line->setVisible(false);
    ui->btnAktivnostNova->setVisible(false);
    ui->line_2->setVisible(false);
    ui->btnAktivnostImfPodaci->setVisible(false);
    ui->btnAktivnostNumeracija->setVisible(false);
    ui->btnAktivnostSporazum->setVisible(false);
    ui->line_5->setVisible(false);
    ui->btnAktivnostUkloni->setVisible(false);
    ui->line_6->setVisible(false);

    if(strTipUlogeStranke == tr("3"))
    {
        // [Visible]
        ui->btnAktivnostLista->setVisible(true);
        ui->btnAktivnostDodljeli->setVisible(true);
        ui->line->setVisible(true);
        ui->btnAktivnostNova->setVisible(true);
        ui->line_2->setVisible(true);
        ui->btnAktivnostImfPodaci->setVisible(true);
        ui->btnAktivnostNumeracija->setVisible(true);
        ui->btnAktivnostSporazum->setVisible(false);
        ui->line_5->setVisible(false);
        ui->btnAktivnostUkloni->setVisible(false);
        ui->line_6->setVisible(false);
        if(strAktivan == tr("0"))
        {
            ui->btnAktivnostLista->setEnabled(false);
            ui->btnAktivnostDodljeli->setEnabled(false);
            ui->line->setEnabled(false);
            ui->btnAktivnostNova->setEnabled(false);
            ui->line_2->setEnabled(false);
            ui->btnAktivnostImfPodaci->setEnabled(false);
            ui->btnAktivnostNumeracija->setEnabled(false);
            ui->btnAktivnostSporazum->setEnabled(false);
        }
    }
    else if(strTipUlogeStranke == tr("4"))
    {
        // [Visible]
        ui->btnAktivnostLista->setVisible(true);
        ui->btnAktivnostDodljeli->setVisible(true);
        ui->line->setVisible(true);
        ui->btnAktivnostNova->setVisible(true);
        ui->line_2->setVisible(true);
        ui->btnAktivnostImfPodaci->setVisible(true);
        ui->btnAktivnostNumeracija->setVisible(true);
        ui->btnAktivnostSporazum->setVisible(false);
        ui->line_5->setVisible(false);
        ui->btnAktivnostUkloni->setVisible(false);
        ui->line_6->setVisible(false);
        if(strAktivan == tr("0"))
        {
            ui->btnAktivnostLista->setEnabled(false);
            ui->btnAktivnostDodljeli->setEnabled(false);
            ui->line->setEnabled(false);
            ui->btnAktivnostNova->setEnabled(false);
            ui->line_2->setEnabled(false);
            ui->btnAktivnostImfPodaci->setEnabled(false);
            ui->btnAktivnostNumeracija->setEnabled(false);
            ui->btnAktivnostSporazum->setEnabled(false);
        }
    }
    else if(strTipUlogeStranke == tr("10"))
    {
        // [Visible]
        ui->btnAktivnostLista->setVisible(true);
        ui->btnAktivnostDodljeli->setVisible(true);
        ui->line->setVisible(true);
        ui->btnAktivnostNova->setVisible(false);
        ui->line_2->setVisible(false);
        ui->btnAktivnostImfPodaci->setVisible(false);
        ui->btnAktivnostNumeracija->setVisible(false);
        ui->btnAktivnostSporazum->setVisible(true);
        ui->line_5->setVisible(false);
        ui->btnAktivnostUkloni->setVisible(true);
        ui->line_6->setVisible(true);
        ui->btnAktivnostUkloni->setEnabled(true);
        ui->btnAktivnostSporazum->setEnabled(true);
        ui->line_6->setEnabled(true);
        if(strAktivan == tr("0"))
        {
            ui->btnAktivnostLista->setEnabled(false);
            ui->btnAktivnostDodljeli->setEnabled(false);
            ui->line->setEnabled(false);
            ui->btnAktivnostUkloni->setEnabled(false);
            ui->btnAktivnostSporazum->setEnabled(false);
            ui->line_6->setEnabled(false);
        }
    }
    else if(strTipUlogeStranke == tr("20"))
    {
        // [Visible]
        ui->btnAktivnostLista->setVisible(true);
        ui->btnAktivnostDodljeli->setVisible(true);
        ui->line->setVisible(true);
        ui->btnAktivnostNova->setVisible(false);
        ui->line_2->setVisible(false);
        ui->btnAktivnostImfPodaci->setVisible(false);
        ui->btnAktivnostNumeracija->setVisible(false);
        ui->btnAktivnostSporazum->setVisible(false);
        ui->line_5->setVisible(false);
        ui->btnAktivnostUkloni->setVisible(true);
        ui->line_6->setVisible(false);
        ui->btnAktivnostUkloni->setEnabled(true);
        if(strAktivan == tr("0"))
        {
            ui->btnAktivnostLista->setEnabled(false);
            ui->btnAktivnostDodljeli->setEnabled(false);
            ui->line->setEnabled(false);
            ui->btnAktivnostUkloni->setEnabled(false);
        }
    }

}
void FrmDonatZahtjevAll::on_treeStrankaImovina_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    setButtonsClose();
    ui->fraImovinaActions->setVisible(true);
    ui->fraStrankaImovina->setVisible(false);
    m_iGrupaImovineId = item->text(5).toUInt();
    popunaTelGim();
}

/* [Class Destrucor]*/
FrmDonatZahtjevAll::~FrmDonatZahtjevAll()
{
    delete ui;
}

}




