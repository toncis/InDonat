//
//  frmcpeoprema.cpp
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


#include "frmcpeoprema.h"
#include "ui_frmcpeoprema.h"
#include "itos.h"

namespace Kontakt {

// [Class Constructors]
FrmCpeOprema::FrmCpeOprema(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmCpeOprema)
{
    ui->setupUi(this);

    ui->treeOprema->setColumnWidth(0, 40);
    ui->treeOprema->setColumnWidth(1, 25);
    //    ui->treeOprema->hideColumn(0);

    ui->treeAtributi->hideColumn(0);

    m_SearchMode = TraziPoBrojTelefona;
    popuniCpeStanja();
}

FrmCpeOprema::FrmCpeOprema(unsigned int iKupacId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmCpeOprema)
{
    ui->setupUi(this);

    ui->txtFltId->setText(QString::number(iKupacId));

    ui->treeOprema->setColumnWidth(0, 40);
    ui->treeOprema->setColumnWidth(1, 25);
    //    ui->treeOprema->hideColumn(0);

    ui->treeAtributi->hideColumn(0);

    m_SearchMode = TraziPoUlogaStrankeId;
    popuniCpeStanja();
    on_btnTrazi_clicked();
}

/* [Private Member Functions] */
void FrmCpeOprema::clearFormData()
{
    ui->treeAtributi->clear();
    ui->treeAtributi->clear();
//    ui->treeStanja->clear();

    ui->txtKupacId->clear();
    ui->txtKupacNaziv->clear();
    ui->txtKupacAdresa->clear();

    ui->txtInstalacijaId->clear();
    ui->txtInstalacijaNaziv->clear();
    ui->txtInstalacijaAdresa->clear();

    ui->txtSerialNumber->clear();
    ui->txtNazivOpreme->clear();
    ui->txtSapId->clear();
    ui->txtJamstvoOd->clear();
    ui->txtJamstvo->clear();
    ui->txtVlasnistvo->clear();
    ui->txtStanjeVlasnistva->clear();
    ui->txtPromjena->clear();
    ui->txtPromjenaStanje->clear();
    ui->txtDatumPromjene->clear();
    ui->txtPromijenio->clear();
    ui->txtKanal->clear();
    ui->txtKanalNaziv->clear();
    ui->txtUgovor->clear();
    ui->txtAssetId->clear();
    ui->txtImovinaId->clear();
    ui->txtTicketId->clear();
    ui->txtProcesId->clear();
}

void FrmCpeOprema::popuniCpeStanja()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT CPE_STANJE_ID, NAZIV FROM CPE_STANJE ORDER BY CPE_STANJE_ID");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listCpeStanja;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemCpeStanje = new QTreeWidgetItem();
            itemCpeStanje->setText(0, QString::fromStdString(rs->getString(2)));
            itemCpeStanje->setText(1, QString::fromStdString(rs->getString(1)));
            listCpeStanja.append(itemCpeStanje);
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

    if(!listCpeStanja.empty())
    {
        listCpeStanja.first()->setSelected(true);
        ui->treeStanja->insertTopLevelItems(0, listCpeStanja);
        ui->treeStanja->setCurrentItem(listCpeStanja.first());
        ui->treeStanja->expandAll();
    }
}

void FrmCpeOprema::popuniGrupuImovine(unsigned int iGrupaImovineId)
{
    std::list<gim_struktura_t> lstGimStruktura;
    string strSqlStatement;
    strSqlStatement.append("SELECT STATUS_ID, KUPAC_ID, ISPORUKA_ID, TIP, ASSET, GIMOVINE_ID, NVL(TEL_BROJ,'-') TEL_BROJ, NVL(KLASA,'-') KLASA ");
    strSqlStatement.append(" FROM V_GIM_STRUKTURA_SVEX WHERE GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(iGrupaImovineId));
    strSqlStatement.append(" ORDER BY TIP ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            gim_struktura_t gim;
            gim.Status = rs->getInt(1);
            gim.KupacId = rs->getUInt(2);
            gim.IsporukaId = rs->getUInt(3);
            gim.Tip = rs->getString(4);
            gim.Asset = rs->getUInt(5);
            gim.GrupaImovineId = rs->getUInt(6);
            gim.TelefonskiBroj = rs->getString(7);
            gim.Klasa = rs->getString(8);
            lstGimStruktura.push_back(gim);
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

    if(lstGimStruktura.empty())
    {
        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
        return;
    }

    list<gim_struktura_t>::const_iterator itGim;
    for(itGim=lstGimStruktura.begin(); itGim!=lstGimStruktura.end(); ++itGim)
    {
        if(itGim->Asset > 0)
        {
            popuniCpeOpremu(*itGim);
        }
    }
}
void FrmCpeOprema::popuniCpeOpremu(gim_struktura_t gim)
{
    NodeTag_Cpe_2 *nodeTag = new NodeTag_Cpe_2();
    nodeTag->Asset = gim.Asset;
    nodeTag->BrojTelefona = gim.TelefonskiBroj;
    nodeTag->GrupaImovineId = gim.Asset;
    nodeTag->IsporukaId = gim.IsporukaId;
    nodeTag->Klasa = gim.Klasa;
    nodeTag->KupacId = gim.KupacId;
    nodeTag->NapalataId = gim.NapalataId;
    nodeTag->status = gim.Status;
    nodeTag->Tip = gim.Tip;

    QList<QTreeWidgetItem *> listCpeOprema;

    QTreeWidgetItem *treeItemGrupaImovine = new QTreeWidgetItem();
    treeItemGrupaImovine->setText(0, QString::number(nodeTag->GrupaImovineId));
    if(nodeTag->status < 1)
    {
        treeItemGrupaImovine->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
    }
    else if(nodeTag->status == 2)
    {
        treeItemGrupaImovine->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OLOVKA.GIF")));
    }
    else if(nodeTag->status > 2)
    {
        treeItemGrupaImovine->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
    }
    treeItemGrupaImovine->setText(2, QString::fromStdString(nodeTag->BrojTelefona + " " + nodeTag->Klasa));
    QVariant treeItemTag;
    treeItemTag.setValue(*nodeTag);
    treeItemGrupaImovine->setData(0, Qt::UserRole, treeItemTag);

    list<gim_cpe_promjena_struktura_t> lstCpeOpremaPromjene;

    string strSqlStatement;
    strSqlStatement.append("SELECT CPE_PROMJENA_ID,CPE_ID,IMOVINA_ID,AKT_IND, ");
    strSqlStatement.append(" NVL(TO_CHAR(DATE_MODIFIED,'DD.MM.YYYY HH24:MI'),'0') DATUM ");
    strSqlStatement.append(" FROM CPE_OPREMA_PROMJENE WHERE ASSET_ID = ");
    strSqlStatement.append(cttl::itos(nodeTag->Asset));
    strSqlStatement.append(" ORDER BY AKT_IND DESC,CPE_PROMJENA_ID DESC ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {

            gim_cpe_promjena_struktura_t cpePromjena;
            cpePromjena.CpePromjenaId = rs->getUInt(1);
            cpePromjena.CpeId = rs->getUInt(2);
            cpePromjena.ImovinaId = rs->getUInt(3);
            cpePromjena.AktInd = rs->getUInt(4);
            cpePromjena.Datum = rs->getString(5);
            if(cpePromjena.Datum == "0")
            {
                cpePromjena.Datum = "xx.xx.xxxx";
            }
            lstCpeOpremaPromjene.push_back(cpePromjena);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this,
                              tr("DONAT - Database Error"),
                              QString::fromStdString(ex.getMessage()),
                              QMessageBox::Close);
    }

    if(!lstCpeOpremaPromjene.empty())
    {
        listCpeOprema.append(treeItemGrupaImovine);
    }

    list<gim_cpe_promjena_struktura_t>::const_iterator itGimCpe;
    for(itGimCpe=lstCpeOpremaPromjene.begin(); itGimCpe!=lstCpeOpremaPromjene.end(); ++itGimCpe)
    {
        strSqlStatement.erase();
        strSqlStatement.append("SELECT P.NAZIV, I.STATUS_ID, NVL(TO_CHAR(I.DATUM_OD, 'DD.MM.YYYY HH24:MI'), '0') DATUM_OD, ");
        strSqlStatement.append(" NVL(TO_CHAR(I.DATUM_DO, 'DD.MM.YYYY HH24:MI'),'0') DATUM_DO ");
        strSqlStatement.append(" FROM IMOVINA I, PRODUKTI P WHERE I.IMOVINA_ID = ");
        strSqlStatement.append(cttl::itos(itGimCpe->ImovinaId));
        strSqlStatement.append(" AND P.PRODUKT_ID=I.PRODUKT_ID ");
        sqlStatement->setSQL(strSqlStatement);

        QTreeWidgetItem *treeItemImovina = new QTreeWidgetItem();
        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            if(rs->next())
            {
                int iStatusId = rs->getInt(2);
                string strDatumOd = rs->getString(3);
                string strDatumDo = rs->getString(4);
                if(strDatumOd == "0")
                {
                    strDatumOd = "xx.xx.xxxx";
                }
                if(strDatumDo == "0")
                {
                    strDatumDo = "xx.xx.xxxx";
                }
                treeItemImovina->setText(0, QString::number(itGimCpe->ImovinaId));

                if(iStatusId < 1)
                {
                    treeItemImovina->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                }
                else if(iStatusId == 2)
                {
                    treeItemImovina->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OLOVKA.GIF")));
                }
                else if(iStatusId > 2)
                {
                    treeItemImovina->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
                }

                if(iStatusId > 0)
                {
                    treeItemImovina->setText(2, QString::fromStdString(strDatumOd + " ... " + rs->getString(1)));
                }
                else
                {
                    treeItemImovina->setText(2, QString::fromStdString(strDatumDo + " ... " + rs->getString(1)));
                }
                QVariant treeItemTag;
                nodeTag->CpePId = itGimCpe->CpePromjenaId;
                nodeTag->CpeOId = itGimCpe->CpeId;
                nodeTag->NadImovinaId = itGimCpe->ImovinaId;
                treeItemTag.setValue(*nodeTag);
                treeItemImovina->setData(0, Qt::UserRole, treeItemTag);

            }
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this,
                                  tr("DONAT - Database Error"),
                                  QString::fromStdString(ex.getMessage()),
                                  QMessageBox::Close);
        }

        strSqlStatement.erase();
        strSqlStatement.append("SELECT P.SN, R.NAZIV TIP_NAZIV, O.NAZIV MOD_NAZIV ");
        strSqlStatement.append(" FROM CPE_OPREMA P, CPE_TIPOVI_OPREME R, CPE_MODELI_OPREME O ");
        strSqlStatement.append(" WHERE P.CPE_ID = ");
        strSqlStatement.append(cttl::itos(itGimCpe->CpeId));
        strSqlStatement.append(" AND R.CPE_TIP_ID = P.CPE_TIP_ID AND O.CPE_MODEL_ID = P.CPE_MODEL_ID ");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            if(rs->next())
            {
                nodeTag->CpeSerialNumber = rs->getString(1);
                nodeTag->CpeTip = rs->getString(2);
                nodeTag->CpeModel = rs->getString(3);

                QTreeWidgetItem *treeItemCpe = new QTreeWidgetItem();
                treeItemCpe->setText(0, QString::number(itGimCpe->CpeId));
//                    treeItemCpe->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
                treeItemCpe->setText(2, QString::fromStdString(itGimCpe->Datum + " ... " + nodeTag->CpeTip + " ... " + nodeTag->CpeModel + "(" + nodeTag->CpeSerialNumber + ")"));
                QVariant treeItemTag;
                nodeTag->CpePId = itGimCpe->CpePromjenaId;
                nodeTag->CpeOId = itGimCpe->CpeId;
                nodeTag->NadImovinaId = itGimCpe->ImovinaId;
                treeItemTag.setValue(*nodeTag);
                treeItemCpe->setData(0, Qt::UserRole, treeItemTag);
                treeItemImovina->addChild(treeItemCpe);
            }
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this,
                                  tr("DONAT - Database Error"),
                                  QString::fromStdString(ex.getMessage()),
                                  QMessageBox::Close);
        }

        treeItemGrupaImovine->addChild(treeItemImovina);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    if(!listCpeOprema.empty())
    {
        listCpeOprema.first()->setSelected(true);
        ui->treeOprema->insertTopLevelItems(0, listCpeOprema);
//        ui->treeOprema->setCurrentItem(listCpeOprema.first());
        ui->treeOprema->expandAll();
//      ui->treeOprema->collapseAll();
    }

}

void FrmCpeOprema::popuniKupca(const unsigned int iKupacId)
{
    if(iKupacId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT FORMATIRANI_NAZIV, FORMATIRANA_ADRESA FROM HIJERARHIJA_STR_ADRESE3 WHERE ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(iKupacId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtKupacId->setText(QString::number(iKupacId));
            ui->txtKupacNaziv->setText(QString::fromStdString(rs->getString(1)));
            ui->txtKupacAdresa->setText(QString::fromStdString(rs->getString(2)));
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
void FrmCpeOprema::popuniInstalaciju(const unsigned int iInstalacijaId)
{
    if(iInstalacijaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT FORMATIRANI_NAZIV, FORMATIRANA_ADRESA FROM HIJERARHIJA_STR_ADRESE3 WHERE ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(iInstalacijaId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtInstalacijaId->setText(QString::number(iInstalacijaId));
            ui->txtInstalacijaNaziv->setText(QString::fromStdString(rs->getString(1)));
            ui->txtInstalacijaAdresa->setText(QString::fromStdString(rs->getString(2)));
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
void FrmCpeOprema::popuniCpe(const unsigned int iCpePromjenaId)
{
    if(iCpePromjenaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT * FROM CPE_SVE WHERE CPE_PROMJENA_ID = ");
    strSqlStatement.append(cttl::itos(iCpePromjenaId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtSerialNumber->setText(QString::fromStdString(rs->getString(2)));
            ui->txtNazivOpreme->setText(QString::fromStdString(rs->getString(3) + " ... " + rs->getString(4)));

            ui->txtSapId->setText(QString::fromStdString(rs->getString(5)));
            ui->txtJamstvoOd->setText(QString::fromStdString(rs->getString(6)));
            ui->txtJamstvo->setText(QString::fromStdString(rs->getString(7)));

            ui->txtVlasnistvo->setText(QString::fromStdString(rs->getString(10)));
            ui->txtStanjeVlasnistva->setText(QString::fromStdString(rs->getString(11)));

            ui->txtPromjena->setText(QString::fromStdString(rs->getString(12)));
            ui->txtPromjenaStanje->setText(QString::fromStdString(rs->getString(21)));

            ui->txtPromijenio->setText(QString::fromStdString(rs->getString(9)));
            ui->txtDatumPromjene->setText(QString::fromStdString(rs->getString(8)));

            ui->txtKanal->setText(QString::fromStdString(rs->getString(17)));
            ui->txtKanalNaziv->setText(QString::fromStdString(rs->getString(18)));

            if(rs->isNull(19) == true)
            {
                ui->txtUgovor->setText(tr("xx.xx.xxxx"));
            }
            else
            {
                ui->txtUgovor->setText(QString::fromStdString(rs->getString(19)));
            }

            ui->txtAssetId->setText(QString::fromStdString(rs->getString(13)));
            ui->txtImovinaId->setText(QString::fromStdString(rs->getString(14)));

            ui->txtTicketId->setText(QString::fromStdString(rs->getString(15)));
            ui->txtProcesId->setText(QString::fromStdString(rs->getString(16)));
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
void FrmCpeOprema::popuniImovinu(const unsigned int iImovinaId)
{
    if(iImovinaId == 0)
    {
        return;
    }

    ui->treeAtributi->clear();
    string strSqlStatement;
    strSqlStatement.append("SELECT /*+ RULE */ * FROM V_IMOVINA_ATR WHERE IMOVINA_ID = ");
    strSqlStatement.append(cttl::itos(iImovinaId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listAtributi;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            string strAtribut;
            strAtribut = rs->getString(5) + " ... " + rs->getString(4);;
            QTreeWidgetItem *treeAtributi = new QTreeWidgetItem();
            treeAtributi->setText(0, QString::number(rs->getUInt(2)));
            treeAtributi->setText(1, QString::fromStdString(strAtribut));
            listAtributi.append(treeAtributi);
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

    if(!listAtributi.empty())
    {
        listAtributi.first()->setSelected(true);
        ui->treeAtributi->insertTopLevelItems(0, listAtributi);
//        ui->treeAtributi->setCurrentItem(listAtributi.first());
        ui->treeAtributi->expandAll();
//      ui->treeAtributi->collapseAll();
    }

}

void FrmCpeOprema::traziPoBrojTelefona()
{
    std::list<unsigned int> lstGupaImovineId;
    ui->treeOprema->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT  NVL(KUPAC_ID,0) KUPAC_ID, NVL(GIMOVINE_ID,0) GIMOVINE_ID, ");
    strSqlStatement.append(" NVL(SLOG_STATUS,100) SLOG_STATUS FROM V_TEL_BROJ WHERE TEL_BROJ = '");
    strSqlStatement.append(ui->txtFltId->text().toStdString());
    strSqlStatement.append("' ORDER BY SLOG_STATUS DESC, TO_DATE(DATUM_OD, 'dd.mm.yyyy hh24:mi:ss') DESC, ROWNUM ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            unsigned int iGrupaImovineId = rs->getUInt(2);
            lstGupaImovineId.push_back(iGrupaImovineId);
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

    if(lstGupaImovineId.empty())
    {
        QMessageBox::information(this, tr("DONAT - CPE Oprema"),
                                    tr("Ne postoji Telefonski broj!"),
                                    QMessageBox::Close);
        return;
    }

    list<unsigned int>::const_iterator itGrupaImovineId;
    for(itGrupaImovineId=lstGupaImovineId.begin(); itGrupaImovineId!=lstGupaImovineId.end(); ++itGrupaImovineId)
    {
        popuniGrupuImovine(*itGrupaImovineId);
    }
}
void FrmCpeOprema::traziPoKupcu()
{
    bool bFltIdIsNumber;
//    unsigned int iKupacId = ui->txtFltId->text().toUInt(&bFltIdIsNumber);

    if(ui->txtFltId->text().toUInt(&bFltIdIsNumber) == false)
    {
        QMessageBox::information(this,
                                 tr("DONAT - CPE Oprema"),
                                 tr("Molimo unesite Kupac ID!"),
                                 QMessageBox::Close);
        ui->txtFltId->setFocus();
        return;
    }

    std::list<unsigned int> lstGupaImovineId;
    ui->treeOprema->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT ASSET_ID FROM CPE_OPREMA_PROMJENE WHERE KUPAC_ID = ");
    strSqlStatement.append(ui->txtFltId->text().toStdString());
    strSqlStatement.append(" GROUP BY ASSET_ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            unsigned int iGrupaImovineId = rs->getUInt(1);
            lstGupaImovineId.push_back(iGrupaImovineId);
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

    if(lstGupaImovineId.empty())
    {
        QMessageBox::information(this, tr("DONAT - CPE Oprema"),
                                    tr("Ne postoji Kupac ID!"),
                                    QMessageBox::Close);
        return;
    }

    list<unsigned int>::const_iterator itGrupaImovineId;
    for(itGrupaImovineId=lstGupaImovineId.begin(); itGrupaImovineId!=lstGupaImovineId.end(); ++itGrupaImovineId)
    {
        popuniGrupuImovine(*itGrupaImovineId);
    }
}
void FrmCpeOprema::traziPoAssetId()
{
    bool bFltIdIsNumber;
    unsigned int iAssetId = ui->txtFltId->text().toUInt(&bFltIdIsNumber);

    if(bFltIdIsNumber == false)
    {
        QMessageBox::information(this,
                                 tr("DONAT - CPE Oprema"),
                                 tr("Molimo unesite Asset ID!"),
                                 QMessageBox::Close);
        ui->txtFltId->setFocus();
        return;
    }

    ui->treeOprema->clear();
    popuniGrupuImovine(iAssetId);
}
void FrmCpeOprema::traziPoTicketId()
{
    bool bFltIdIsNumber;

    if(ui->txtFltId->text().toUInt(&bFltIdIsNumber) == false)
    {
        QMessageBox::information(this,
                                 tr("DONAT - CPE Oprema"),
                                 tr("Molimo unesite Ticket ID!"),
                                 QMessageBox::Close);
        ui->txtFltId->setFocus();
        return;
    }

    std::list<unsigned int> lstGupaImovineId;
    ui->treeOprema->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT ASSET_ID FROM CPE_OPREMA_PROMJENE WHERE TICKET_ID = ");
    strSqlStatement.append(ui->txtFltId->text().toStdString());
    strSqlStatement.append(" GROUP BY ASSET_ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            unsigned int iGrupaImovineId = rs->getUInt(1);
            lstGupaImovineId.push_back(iGrupaImovineId);
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

    if(lstGupaImovineId.empty())
    {
        QMessageBox::information(this, tr("DONAT - CPE Oprema"),
                                    tr("Ne postoji Ticket ID!"),
                                    QMessageBox::Close);
        return;
    }

    list<unsigned int>::const_iterator itGrupaImovineId;
    for(itGrupaImovineId=lstGupaImovineId.begin(); itGrupaImovineId!=lstGupaImovineId.end(); ++itGrupaImovineId)
    {
        popuniGrupuImovine(*itGrupaImovineId);
    }
}
void FrmCpeOprema::traziPoSerijskiBroj()
{
    unsigned int iCpeId = 0;
    std::list<unsigned int> lstGupaImovineId;
    ui->treeOprema->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT CPE_ID FROM CPE_OPREMA WHERE SN = '");
    strSqlStatement.append(ui->txtFltId->text().toStdString());
    strSqlStatement.append("' ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iCpeId = rs->getUInt(1);
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
    strSqlStatement.append("SELECT ASSET_ID FROM CPE_OPREMA_PROMJENE WHERE CPE_ID = ");
    strSqlStatement.append(cttl::itos(iCpeId));
    strSqlStatement.append(" GROUP BY ASSET_ID ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            unsigned int iGrupaImovineId = rs->getUInt(1);
            lstGupaImovineId.push_back(iGrupaImovineId);
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

    if(lstGupaImovineId.empty())
    {
        QMessageBox::information(this,
                                 tr("DONAT - CPE Oprema"),
                                 tr("Ne postoji Serijski Broj!"),
                                 QMessageBox::Close);
        return;
    }

    list<unsigned int>::const_iterator itGrupaImovineId;
    for(itGrupaImovineId=lstGupaImovineId.begin(); itGrupaImovineId!=lstGupaImovineId.end(); ++itGrupaImovineId)
    {
        popuniGrupuImovine(*itGrupaImovineId);
    }
}

/* [Event Handlers] */
void FrmCpeOprema::on_btnTrazi_clicked()
{
    if(ui->txtFltId->text().isEmpty())
        return;

    clearFormData();

    switch(m_SearchMode)
    {
        case TraziPoBrojTelefona:
        {
            traziPoBrojTelefona();
            break;
        }
        case TraziPoUlogaStrankeId:
        {
            traziPoKupcu();
            break;
        }
        case TraziPoAssetId:
        {
            traziPoAssetId();
            break;
        }
        case TraziPoTicketId:
        {
            traziPoTicketId();
            break;
        }
        case TraziPoSerijskiBroj:
        {
            traziPoSerijskiBroj();
            break;
        }
        default:
        {
            break;
        }
    }
}

void FrmCpeOprema::on_btnTelefon_clicked()
{
    m_SearchMode = TraziPoBrojTelefona;
    if(ui->txtFltId->text().isEmpty())
    {
        ui->txtFltId->setFocus();
    }
    else
    {
        traziPoBrojTelefona();
    }
}
void FrmCpeOprema::on_btnKupacId_clicked()
{
    m_SearchMode = TraziPoUlogaStrankeId;
    if(ui->txtFltId->text().isEmpty())
    {
        ui->txtFltId->setFocus();
    }
    else
    {
        traziPoKupcu();
    }
}
void FrmCpeOprema::on_btnAsset_clicked()
{
    m_SearchMode = TraziPoAssetId;
    if(ui->txtFltId->text().isEmpty())
    {
        ui->txtFltId->setFocus();
    }
    else
    {
        traziPoAssetId();
    }
}
void FrmCpeOprema::on_btnTicket_clicked()
{
    m_SearchMode = TraziPoTicketId;
    if(ui->txtFltId->text().isEmpty())
    {
        ui->txtFltId->setFocus();
    }
    else
    {
        traziPoTicketId();
    }
}
void FrmCpeOprema::on_btnSerijskiBroj_clicked()
{
    m_SearchMode = TraziPoSerijskiBroj;
    if(ui->txtFltId->text().isEmpty())
    {
        ui->txtFltId->setFocus();
    }
    else
    {
        traziPoSerijskiBroj();
    }
}
void FrmCpeOprema::on_btnPotvrdaNovogStanja_clicked()
{

}

void FrmCpeOprema::on_btnZatvori_clicked()
{

}

void FrmCpeOprema::on_treeOprema_itemPressed(QTreeWidgetItem *item, const int UNUSED(column))
{
    setCursor(Qt::BusyCursor);
    ui->treeAtributi->clear();
    QVariant varTag = item->data(0, Qt::UserRole);
    NodeTag_Cpe_2 nodeTag = varTag.value<NodeTag_Cpe_2>();
    popuniKupca(nodeTag.KupacId);
    popuniInstalaciju(nodeTag.IsporukaId);
    popuniCpe(nodeTag.CpePId);
    popuniImovinu(nodeTag.NadImovinaId);
    setCursor(Qt::ArrowCursor);
}

FrmCpeOprema::~FrmCpeOprema()
{
    delete ui;
}

}


