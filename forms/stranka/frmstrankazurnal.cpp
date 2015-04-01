//
//  frmstrankazurnal.cpp
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

#include "frmstrankazurnal.h"
#include "ui_frmstrankazurnal.h"

#include "itos.h"
#include "ocinumber.h"

namespace Stranka {

// [Class Constructors]
FrmStrankaZurnal::FrmStrankaZurnal(
    unsigned int iKupacId,
    unsigned int iGrupaImovineId,
    QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmStrankaZurnal)
{
    ui->setupUi(this);

    ui->treeGrupeImovine->setColumnWidth(0, 300);
    ui->treeGrupeImovine->setColumnWidth(1, 18);
    ui->treeGrupeImovine->setColumnWidth(2, 18);
    ui->treeGrupeImovine->setColumnWidth(3, 18);
    ui->treeGrupeImovine->hideColumn(4);
    ui->treeGrupeImovine->hideColumn(5);
    ui->treeGrupeImovine->hideColumn(6);
    ui->treeGrupeImovine->hideColumn(7);
    ui->treeGrupeImovine->hideColumn(8);
    ui->treeGrupeImovine->hideColumn(9);
    ui->treeGrupeImovine->hideColumn(10);
    ui->treeGrupeImovine->hideColumn(11);
    ui->treeGrupeImovine->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeGrupeImovine->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->treeIzmjene->setColumnWidth(0, 300);
    ui->treeIzmjene->hideColumn(1);
    ui->treeIzmjene->hideColumn(2);
    ui->treeIzmjene->hideColumn(3);
    ui->treeIzmjene->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeIzmjene->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->treePromena->setColumnWidth(0, 320);
    ui->treePromena->setColumnWidth(1, 50);
    ui->treePromena->hideColumn(1);
    ui->treePromena->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treePromena->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_iKupacId = iKupacId;
    m_iGrupaImovineId = iGrupaImovineId;

    if(m_iGrupaImovineId != 0)
    {
        m_iTipPromjene = 1;
    }

    popuniGrupuImovine();
    popuniListePromjena();

//    ui->lblStatusBarText2->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));

}

FrmStrankaZurnal::~FrmStrankaZurnal()
{
    delete ui;
}

// [Private Member Functions]
void FrmStrankaZurnal::clearPromjena()
{
    ui->treePromena->clear();
    ui->lblImovina1->clear();
    ui->lblImovina2->clear();
    ui->lblKlasa->clear();
    ui->lblKlasa2->clear();
    ui->lblPretplata->clear();
    ui->lblPretplata2->clear();
    ui->lblOperater->clear();
}

void FrmStrankaZurnal::popuniPoTelefonskomBroju()
{

    if(m_strTelefonskiBroj.length() == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT  NVL(KUPAC_ID,0) KUPAC_ID, NAZIV_KONTAKTA(KUPAC_ID) KUPAC_NAZ, NVL(GIMOVINE_ID,0) GIMOVINE_ID, ");
    strSqlStatement.append("NVL(SLOG_STATUS,100) SLOG_STATUS FROM V_TEL_BROJ WHERE TEL_BROJ = '");
    strSqlStatement.append(m_strTelefonskiBroj);
    strSqlStatement.append(" ORDER BY SLOG_STATUS DESC, TO_DATE(DATUM_OD,'dd.mm.yyyy hh24:mi:ss') DESC, ROWNUM ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);


    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_iKupacId = rs->getUInt(1);
            m_iGrupaImovineId = rs->getUInt(3);
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

    popuniGrupuImovine();
}
void FrmStrankaZurnal::popuniGrupuImovine()
{
    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    ui->treeGrupeImovine->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT TIP, ASSET, GIMOVINE_ID, NVL(TEL_BROJ,'-') TEL_BROJ, NVL(KLASA,'-') KLASA ");
    strSqlStatement.append("FROM V_GIM_STRUKTURA_SVE WHERE GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    strSqlStatement.append(" ORDER BY TIP ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listGrupaImovine;
    std::list<gim_struktura_sve_t> lstGimStruktura;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            unsigned int iAssetId;
            iAssetId = rs->getUInt(2);
            if(iAssetId > 0)
            {
                gim_struktura_sve_t gim;
                gim.Tip = rs->getString(1);
                gim.Asset = rs->getUInt(2);
                gim.GrupaImovineId = rs->getUInt(3);
                gim.TelefonskiBroj = rs->getString(4);
                gim.Klasa = rs->getString(5);
                lstGimStruktura.push_back(gim);
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

    list<gim_struktura_sve_t >::const_iterator itGim;
    for(itGim=lstGimStruktura.begin(); itGim!=lstGimStruktura.end(); ++itGim)
    {
        strSqlStatement.clear();
        strSqlStatement.append("SELECT GIMOVINE_ID, B1, B2, TEL_BROJ, TEL_LIN_ID, IMOVINA_ID, ");
        strSqlStatement.append("SLOG_STATUS, TO_CHAR(DATUM_DO, 'DD.MM.RR') DATUM_DO ");
        strSqlStatement.append("FROM B_HIJERARHIJA WHERE GIMOVINE_ID = ");
        strSqlStatement.append(cttl::itos(itGim->GrupaImovineId));
        strSqlStatement.append(" AND KUPAC_ID = ");
        strSqlStatement.append(cttl::itos(m_iKupacId));
        strSqlStatement.append(" AND B1>0 AND B2<>9 ");
        strSqlStatement.append(" ORDER BY B1, TEL_BROJ ");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                QTreeWidgetItem *itemGrupaImovine = new QTreeWidgetItem();
                itemGrupaImovine->setText(0, QString::fromStdString(rs->getString(4) + "      " + rs->getString(5)));
                itemGrupaImovine->setText(4, QString::fromStdString(rs->getString(1)));
                itemGrupaImovine->setText(5, QString::fromStdString(rs->getString(2)));
                itemGrupaImovine->setText(6, QString::fromStdString(rs->getString(3)));
                itemGrupaImovine->setText(7, QString::fromStdString(rs->getString(4)));
                itemGrupaImovine->setText(8, QString::fromStdString(rs->getString(5)));
                itemGrupaImovine->setText(9, QString::fromStdString(rs->getString(6)));
                itemGrupaImovine->setText(10, QString::fromStdString(rs->getString(7)));
                itemGrupaImovine->setText(11, QString::fromStdString(rs->getString(8)));
                listGrupaImovine.append(itemGrupaImovine);
            }
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    for(int i = 0; i < listGrupaImovine.size(); ++i)
    {
        if(listGrupaImovine.at(i)->text(5).toInt() == 1)
        {
            if(listGrupaImovine.at(i)->text(10).toInt() == 0)
            {
               listGrupaImovine.at(i)->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
            }
            if(listGrupaImovine.at(i)->text(10).toInt() > 1)
            {
                listGrupaImovine.at(i)->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
            }
        }
        else
        {
            if(listGrupaImovine.at(i)->text(10).toInt() == 0)
            {
               listGrupaImovine.at(i)->setIcon(1, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
            }

            if(i != 0)
            {
                if(listGrupaImovine.at(i)->text(8) != listGrupaImovine.at((i - 1))->text(8))
                {
//                    listGrupaImovine.at(i)->setText(0, listGrupaImovine.at(i)->text(4));
                }
                listGrupaImovine.at((0))->addChild(listGrupaImovine.at(i));
            }
        }
    }

    if(!listGrupaImovine.empty())
    {
        listGrupaImovine.first()->setSelected(true);
        ui->treeGrupeImovine->insertTopLevelItems(0, listGrupaImovine);
        ui->treeGrupeImovine->setCurrentItem(listGrupaImovine.first());
        ui->treeGrupeImovine->expandAll();
//      ui->treeGrupeImovine->collapseAll();

//        ui->txtGrupaImovineId->setText(listGrupaImovine.first()->text(4));
//        ui->txtUloge->setText(listGrupaImovine.first()->text(0));
        m_strTelefonskiBroj = listGrupaImovine.first()->text(7).toStdString();
//        m_strTelefonskiBrojKlasa = listGrupaImovine.first()->text(8).toStdString();
    }

    popuniUlogeGrupeImovine();
}
void FrmStrankaZurnal::popuniUlogeGrupeImovine()
{
    ui->txtBillingAccountId->clear();
    ui->txtInstalacijaId->clear();

    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    string strUlogeStranakaIds;
    string strSqlStatement;
    strSqlStatement.append("SELECT ULOGE_GRUPE_IMOVINE(");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    strSqlStatement.append(") ULOGE FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strUlogeStranakaIds = rs->getString(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    int iTipUlogeStrankeId = 0;
    strSqlStatement.clear();
    strSqlStatement.append("SELECT ULSTRANKE_ID, NAZIV_ULSTR, FORMATIRANI_NAZIV, TULSTRANKE_ID, FORMATIRANA_ADRESA ");
    strSqlStatement.append(" FROM HIJERARHIJA_STR_ADRESE2 WHERE ULSTRANKE_ID IN ");
    strSqlStatement.append(strUlogeStranakaIds);
    strSqlStatement.append(" ORDER BY TULSTRANKE_ID ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            iTipUlogeStrankeId = rs->getInt(4);
            switch(iTipUlogeStrankeId)
            {
                case 3:
                {
                    ui->txtBillingAccountId->setText(QString::fromStdString(rs->getString(1)));
                    break;
                }
                case 4:
                {
                    ui->txtInstalacijaId->setText(QString::fromStdString(rs->getString(1)));
                    break;
                }
                default:
                {
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

    m_iTipPromjene = 1;
}
void FrmStrankaZurnal::popuniListePromjena()
{
    ui->treeIzmjene->clear();
    clearPromjena();

    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT MATPROM_TEL_ID, NVL(TO_CHAR(DATUM_PROMJENE,'DD.MM.YYYY HH24:MI'),' ') DATUM, ");
    strSqlStatement.append(" NVL(KLASA,'.') KLASA,NVL(TELEFON,'.') TELEFON ");
    strSqlStatement.append(" FROM MATICNE_PROMJENE_TEL WHERE GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    if(m_strTelefonskiBroj.length() > 0)
    {
        strSqlStatement.append(" AND TELEFON = '");
        strSqlStatement.append(m_strTelefonskiBroj);
        strSqlStatement.append("' ");
    }
    strSqlStatement.append("  ORDER BY DATUM_PROMJENE DESC ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listPromjene;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemPromjena = new QTreeWidgetItem();
            itemPromjena->setText(0, QString::fromStdString(rs->getString(4) + " ... " + rs->getString(2)));
            itemPromjena->setText(1, QString::fromStdString(rs->getString(1)));
            itemPromjena->setText(2, QString::fromStdString(rs->getString(2)));
            itemPromjena->setText(3, QString::fromStdString(rs->getString(4)));
            listPromjene.append(itemPromjena);

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

    m_iTipPromjene = 1;

    if(!listPromjene.empty())
    {
        listPromjene.first()->setSelected(true);
        ui->treeIzmjene->insertTopLevelItems(0, listPromjene);
        ui->treeIzmjene->setCurrentItem(listPromjene.first());
        ui->treeIzmjene->expandAll();
//      ui->treeIzmjene->collapseAll();


        QTreeWidgetItem *itemBelow = ui->treeIzmjene->itemBelow(listPromjene.first());
        if(itemBelow > 0)
        {
            m_iMaticnePromjenePrijeId = itemBelow->text(1).toUInt();
        }
        else
        {
            m_iMaticnePromjenePrijeId = 0;
        }

        m_iMaticnePromjeneId = listPromjene.first()->text(1).toUInt();
        if(m_iTipPromjene == 1)
        {
            clearPromjena();
            popuniMaticnuPromjenuZaGrupuImovine();
            popuniMaticnuPromjenuPrijeZaGrupuImovine();
        }
        else
        {
            clearPromjena();
            popuniMaticnuPromjenuZaUloguStranke();
        }

    }

}
void FrmStrankaZurnal::popuniListePromjenaUlogaStranke()
{
    ui->treeIzmjene->clear();
    clearPromjena();

    if(m_iKupacId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT MATPROM_ID, NVL(TO_CHAR(DATUM_PROMJENE,'DD.MM.YYYY HH24:MI'),' ') DATUM, ");
    strSqlStatement.append(" ULSTRANKE_ID FROM MATICNE_PROMJENE WHERE ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(m_iKupacId));
    strSqlStatement.append("  ORDER BY DATUM_PROMJENE DESC ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listPromjene;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemPromjena = new QTreeWidgetItem();
            itemPromjena->setText(0, QString::fromStdString(rs->getString(3) + " ... " + rs->getString(2)));
            itemPromjena->setText(1, QString::fromStdString(rs->getString(1)));
            itemPromjena->setText(2, QString::fromStdString(rs->getString(2)));
            itemPromjena->setText(3, QString::fromStdString(rs->getString(3)));
            listPromjene.append(itemPromjena);
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

    m_iTipPromjene = 2;

    if(!listPromjene.empty())
    {
        listPromjene.first()->setSelected(true);
        ui->treeIzmjene->insertTopLevelItems(0, listPromjene);
        ui->treeIzmjene->setCurrentItem(listPromjene.first());
        ui->treeIzmjene->expandAll();
//      ui->treeIzmjene->collapseAll();

        QTreeWidgetItem *itemBelow = ui->treeIzmjene->itemBelow(listPromjene.first());
        if(itemBelow > 0)
        {
            m_iMaticnePromjenePrijeId = itemBelow->text(1).toUInt();
        }
        else
        {
            m_iMaticnePromjenePrijeId = 0;
        }

        m_iMaticnePromjeneId = listPromjene.first()->text(1).toUInt();

        clearPromjena();
        popuniMaticnuPromjenuZaUloguStranke();
        popuniMaticnuPromjenuPrijeZaUloguStranke();
    }

}
void FrmStrankaZurnal::popuniMaticnuPromjenuZaGrupuImovine()
{
    if(m_iMaticnePromjeneId == 0)
    {
        return;
    }

    string strSqlStatement;

//    strSqlStatement.append("SELECT ");
//    strSqlStatement.append("NVL(KLASA,'...') KLASA, ");
//    strSqlStatement.append("NVL(TELEFON,'...') TELEFON, ");
//    strSqlStatement.append("NVL(PRETPLATA,'...') PRETPLATA, ");
//    strSqlStatement.append("NVL(DOD_USLUGE,'...') DOD_USLUGE, ");
//    strSqlStatement.append("NVL(TO_CHAR(DATUM_PROMJENE,'DD.MM.YYYY HH24:MI'),'...') DATUM, ");
//    strSqlStatement.append("NVL(OPERATER,'...') OPERATER, ");
//    strSqlStatement.append("NVL(TO_CHAR(CUST_ID),'...') CUST_ID, ");
//    strSqlStatement.append("NVL(TO_CHAR(KONT_ID),'...') KONT_ID, ");
//    strSqlStatement.append("NVL(TO_CHAR(BILL_ID),'...') BILL_ID, ");
//    strSqlStatement.append("NVL(TO_CHAR(SERV_ID),'...') SERV_ID, ");
//    strSqlStatement.append("NVL(NAZIV_CUST,'...') NAZIV_CUST, ");
//    strSqlStatement.append("NVL(NAZIV_KONT,'...') NAZIV_KONT, ");
//    strSqlStatement.append("NVL(NAZIV_BILL,'...') NAZIV_BILL, ");
//    strSqlStatement.append("NVL(NAZIV_SERV,'...') NAZIV_SERV, ");
//    strSqlStatement.append("NVL(ADRESA_CUST,'...') ADRESA_CUST, ");
//    strSqlStatement.append("NVL(ADRESA_KONT,'...') ADRESA_KONT, ");
//    strSqlStatement.append("NVL(ADRESA_BILL,'...') ADRESA_BILL, ");
//    strSqlStatement.append("NVL(ADRESA_SERV,'...') ADRESA_SERV, ");
//    strSqlStatement.append("NVL(TIP_STRANKE,'...') TIP_STRANKE, ");
//    strSqlStatement.append("NVL(PODTIP_STRANKE,'...') PODTIP_STRANKE, ");
//    strSqlStatement.append("NVL(MARKET_SEGMENT,'...') MARKET_SEGMENT, ");
//    strSqlStatement.append("NVL(TIP_ISPRAVE,'...') TIP_ISPRAVE, ");
//    strSqlStatement.append("NVL(BROJ_ISPRAVE,'...') BROJ_ISPRAVE, ");
//    strSqlStatement.append("NVL(TIP_PORB,'...') TIP_PORB, ");
//    strSqlStatement.append("NVL(MBR,'...') MBR, ");
//    strSqlStatement.append("NVL(VRSTA_RACUNA,'...') VRSTA_RACUNA, ");
//    strSqlStatement.append("NVL(MEDIJ_RACUNA,'...') MEDIJ_RACUNA, ");
//    strSqlStatement.append("NVL(KRED_KLASA,'...') KRED_KLASA, ");
//    strSqlStatement.append("NVL(TIP_OPOMINJANJA,'...') TIP_OPOMINJANJA, ");
//    strSqlStatement.append("NVL(POREZ,'...') POREZ ");
//    strSqlStatement.append(" FROM MATICNE_PROMJENE_TEL WHERE MATPROM_TEL_ID = ");
//    strSqlStatement.append(cttl::itos(m_iMaticnePromjeneId));

    strSqlStatement.append("SELECT MATPROM_TEL_ID, MATPROM_ID, GIMOVINE_ID, KLASA, TELEFON, B1, PRETPLATA, DOD_USLUGE, TITULA, TIP_ISPRAVE, ");
    strSqlStatement.append(" BROJ_ISPRAVE, TIP_PORB, MBR, TIP_STRANKE, PODTIP_STRANKE, MARKET_SEGMENT, VRSTA_RACUNA, MEDIJ_RACUNA, KRED_KLASA, ");
    strSqlStatement.append(" TIP_OPOMINJANJA, POREZ, BILL_ID, CUST_ID, SERV_ID, KONT_ID, NAZIV_BILL, ADRESA_BILL, NAZIV_CUST, ADRESA_CUST, ");
    strSqlStatement.append(" NAZIV_SERV, ADRESA_SERV, NAZIV_KONT, ADRESA_KONT, TO_CHAR(DATUM_PROMJENE, 'DD.MM.YYYY HH24:MI:SS') DATUM_PROMJENE, ");
    strSqlStatement.append(" OPERATER, STATUS ");
    strSqlStatement.append(" FROM MATICNE_PROMJENE_TEL WHERE MATPROM_TEL_ID = ");
    strSqlStatement.append(cttl::itos(m_iMaticnePromjeneId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listPromjene;
//    m_GrupaImovinePromjena = new maticna_promjena_tel_t();

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(!rs->isNull(1))
            {
                m_GrupaImovinePromjena.MATPROM_TEL_ID = cttl::getUIntAsONumber(rs->getNumber(1)); //rs->getUInt(1);
            }
            if(!rs->isNull(2))
            {
                m_GrupaImovinePromjena.MATPROM_ID = cttl::getUIntAsONumber(rs->getNumber(2)); //rs->getUInt(2);
            }
            m_GrupaImovinePromjena.GIMOVINE_ID = rs->getUInt(3);
            m_GrupaImovinePromjena.KLASA = rs->getString(4);
            m_GrupaImovinePromjena.TELEFON = rs->getString(5);
            m_GrupaImovinePromjena.B1 = rs->getInt(6);
            m_GrupaImovinePromjena.PRETPLATA = rs->getString(7);
            m_GrupaImovinePromjena.DOD_USLUGE = rs->getString(8);
            m_GrupaImovinePromjena.TITULA = rs->getString(9);
            m_GrupaImovinePromjena.TIP_ISPRAVE = rs->getString(10);
            m_GrupaImovinePromjena.BROJ_ISPRAVE = rs->getString(11);
            m_GrupaImovinePromjena.TIP_PORB = rs->getString(12);
            m_GrupaImovinePromjena.MBR = rs->getString(13);
            m_GrupaImovinePromjena.TIP_STRANKE = rs->getString(14);
            m_GrupaImovinePromjena.PODTIP_STRANKE = rs->getString(15);
            m_GrupaImovinePromjena.MARKET_SEGMENT = rs->getString(16);
            m_GrupaImovinePromjena.VRSTA_RACUNA = rs->getString(17);
            m_GrupaImovinePromjena.MEDIJ_RACUNA = rs->getString(18);
            m_GrupaImovinePromjena.KRED_KLASA = rs->getString(19);
            m_GrupaImovinePromjena.TIP_OPOMINJANJA = rs->getString(20);
            m_GrupaImovinePromjena.POREZ = rs->getString(21);
            if(!rs->isNull(22))
            {
                m_GrupaImovinePromjena.BILL_ID = cttl::getUIntAsONumber(rs->getNumber(22)); //rs->getUInt(22);
            }
            if(!rs->isNull(23))
            {
                m_GrupaImovinePromjena.CUST_ID = cttl::getUIntAsONumber(rs->getNumber(23)); //rs->getUInt(23);
            }
            if(!rs->isNull(24))
            {
                m_GrupaImovinePromjena.SERV_ID = cttl::getUIntAsONumber(rs->getNumber(24)); //rs->getUInt(24);
            }
            if(!rs->isNull(25))
            {
                m_GrupaImovinePromjena.KONT_ID = cttl::getUIntAsONumber(rs->getNumber(25)); //rs->getUInt(25);
            }
            m_GrupaImovinePromjena.NAZIV_BILL = rs->getString(26);
            m_GrupaImovinePromjena.ADRESA_BILL = rs->getString(27);
            m_GrupaImovinePromjena.NAZIV_CUST = rs->getString(28);
            m_GrupaImovinePromjena.ADRESA_CUST = rs->getString(29);
            m_GrupaImovinePromjena.NAZIV_SERV = rs->getString(30);
            m_GrupaImovinePromjena.ADRESA_SERV = rs->getString(31);
            m_GrupaImovinePromjena.NAZIV_KONT = rs->getString(32);
            m_GrupaImovinePromjena.ADRESA_KONT = rs->getString(33);
            m_GrupaImovinePromjena.DATUM_PROMJENE = rs->getString(34);
            m_GrupaImovinePromjena.OPERATER = rs->getString(35);
            m_GrupaImovinePromjena.STATUS = rs->getString(36);
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

    ui->lblOperater->setText(QString::fromStdString(m_GrupaImovinePromjena.OPERATER));
    ui->lblKlasa->setText(QString::fromStdString(m_GrupaImovinePromjena.TELEFON + " ... " + m_GrupaImovinePromjena.KLASA));
    ui->lblPretplata->setText(QString::fromStdString(m_GrupaImovinePromjena.PRETPLATA));

    QString strImovina = QString::fromStdString(m_GrupaImovinePromjena.DOD_USLUGE).replace(tr(","), tr("\n"));
    ui->lblImovina1->setText(strImovina);

    QTreeWidgetItem *itemKupac = new QTreeWidgetItem();
    itemKupac->setText(1, tr("10"));
    itemKupac->setText(0, tr("KUPAC"));
    QTreeWidgetItem *itemKupac1 = new QTreeWidgetItem();
    itemKupac1->setText(1, tr("11"));
    itemKupac1->setText(0, tr("ID ...") + QString::number(m_GrupaImovinePromjena.CUST_ID));
    itemKupac->addChild(itemKupac1);
    QTreeWidgetItem *itemKupac2 = new QTreeWidgetItem();
    itemKupac2->setText(1, tr("12"));
    itemKupac2->setText(0, QString::fromStdString(m_GrupaImovinePromjena.NAZIV_CUST));
    itemKupac->addChild(itemKupac2);
    QTreeWidgetItem *itemKupac3 = new QTreeWidgetItem();
    itemKupac3->setText(1, tr("13"));
    itemKupac3->setText(0, QString::fromStdString(m_GrupaImovinePromjena.ADRESA_CUST));
    itemKupac->addChild(itemKupac3);
    listPromjene.append(itemKupac);

    QTreeWidgetItem *itemKontakt = new QTreeWidgetItem();
    itemKontakt->setText(1, tr("20"));
    itemKontakt->setText(0, tr("KONTAKT"));
    QTreeWidgetItem *itemKontakt1 = new QTreeWidgetItem();
    itemKontakt1->setText(1, tr("21"));
    itemKontakt1->setText(0, tr("ID ...") + QString::number(m_GrupaImovinePromjena.KONT_ID));
    itemKontakt->addChild(itemKontakt1);
    QTreeWidgetItem *itemKontakt2 = new QTreeWidgetItem();
    itemKontakt2->setText(1, tr("22"));
    itemKontakt2->setText(0, QString::fromStdString(m_GrupaImovinePromjena.NAZIV_KONT));
    itemKontakt->addChild(itemKontakt2);
    QTreeWidgetItem *itemKontakt3 = new QTreeWidgetItem();
    itemKontakt3->setText(1, tr("23"));
    itemKontakt3->setText(0, QString::fromStdString(m_GrupaImovinePromjena.ADRESA_KONT));
    itemKontakt->addChild(itemKontakt3);
    listPromjene.append(itemKontakt);

    QTreeWidgetItem *itemRacun = new QTreeWidgetItem();
    itemRacun->setText(1, tr("30"));
    itemRacun->setText(0, tr("RAČUN"));
    QTreeWidgetItem *itemRacun1 = new QTreeWidgetItem();
    itemRacun1->setText(1, tr("31"));
    itemRacun1->setText(0, tr("ID ...") + QString::number(m_GrupaImovinePromjena.BILL_ID));
    itemRacun->addChild(itemRacun1);
    QTreeWidgetItem *itemRacun2 = new QTreeWidgetItem();
    itemRacun2->setText(1, tr("32"));
    itemRacun2->setText(0, QString::fromStdString(m_GrupaImovinePromjena.NAZIV_BILL));
    itemRacun->addChild(itemRacun2);
    QTreeWidgetItem *itemRacun3 = new QTreeWidgetItem();
    itemRacun3->setText(1, tr("33"));
    itemRacun3->setText(0, QString::fromStdString(m_GrupaImovinePromjena.ADRESA_BILL));
    itemRacun->addChild(itemRacun3);
    listPromjene.append(itemRacun);

    QTreeWidgetItem *itemInstalacija = new QTreeWidgetItem();
    itemInstalacija->setText(1, tr("40"));
    itemInstalacija->setText(0, tr("INSTALACIJA"));
    QTreeWidgetItem *itemInstalacija1 = new QTreeWidgetItem();
    itemInstalacija1->setText(1, tr("41"));
    itemInstalacija1->setText(0, tr("ID ...") + QString::number(m_GrupaImovinePromjena.SERV_ID));
    itemInstalacija->addChild(itemInstalacija1);
    QTreeWidgetItem *itemInstalacija2 = new QTreeWidgetItem();
    itemInstalacija2->setText(1, tr("42"));
    itemInstalacija2->setText(0, QString::fromStdString(m_GrupaImovinePromjena.NAZIV_SERV));
    itemInstalacija->addChild(itemInstalacija2);
    QTreeWidgetItem *itemInstalacija3 = new QTreeWidgetItem();
    itemInstalacija3->setText(1, tr("43"));
    itemInstalacija3->setText(0, QString::fromStdString(m_GrupaImovinePromjena.ADRESA_SERV));
    itemInstalacija->addChild(itemInstalacija3);
    listPromjene.append(itemInstalacija);

    QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
    itemStranka->setText(1, tr("50"));
    itemStranka->setText(0, tr("STRANKA"));
    QTreeWidgetItem *itemStranka1 = new QTreeWidgetItem();
    itemStranka1->setText(1, tr("51"));
    itemStranka1->setText(0, tr("Tip ...") + QString::fromStdString(m_GrupaImovinePromjena.TIP_STRANKE));
    itemStranka->addChild(itemStranka1);
    QTreeWidgetItem *itemStranka2 = new QTreeWidgetItem();
    itemStranka2->setText(1, tr("52"));
    itemStranka2->setText(0, tr("PodTip ...") + QString::fromStdString(m_GrupaImovinePromjena.PODTIP_STRANKE));
    itemStranka->addChild(itemStranka2);
    QTreeWidgetItem *itemStranka3 = new QTreeWidgetItem();
    itemStranka3->setText(1, tr("53"));
    itemStranka3->setText(0, tr("Segment ...") + QString::fromStdString(m_GrupaImovinePromjena.MARKET_SEGMENT));
    itemStranka->addChild(itemStranka3);
    listPromjene.append(itemStranka);

    QTreeWidgetItem *itemIsprave = new QTreeWidgetItem();
    itemIsprave->setText(1, tr("60"));
    itemIsprave->setText(0, tr("ISPRAVE"));
    QTreeWidgetItem *itemIsprave1 = new QTreeWidgetItem();
    itemIsprave1->setText(1, tr("61"));
    itemIsprave1->setText(0, tr("Tip isprave ...") + QString::fromStdString(m_GrupaImovinePromjena.TIP_ISPRAVE));
    itemIsprave->addChild(itemStranka1);
    QTreeWidgetItem *itemIsprave2 = new QTreeWidgetItem();
    itemIsprave2->setText(1, tr("62"));
    itemIsprave2->setText(0, tr("Broj isprave ...") + QString::fromStdString(m_GrupaImovinePromjena.BROJ_ISPRAVE));
    itemIsprave->addChild(itemIsprave2);
    QTreeWidgetItem *itemIsprave3 = new QTreeWidgetItem();
    itemIsprave3->setText(1, tr("63"));
    itemIsprave3->setText(0, tr("Tip poreznog broja ...") + QString::fromStdString(m_GrupaImovinePromjena.TIP_PORB));
    itemIsprave->addChild(itemIsprave3);
    QTreeWidgetItem *itemIsprave4 = new QTreeWidgetItem();
    itemIsprave4->setText(1, tr("64"));
    itemIsprave4->setText(0, tr("Porez ...") + QString::fromStdString(m_GrupaImovinePromjena.POREZ));
    itemIsprave->addChild(itemIsprave4);
    listPromjene.append(itemIsprave);

    if(!listPromjene.empty())
    {
        listPromjene.first()->setSelected(true);
        ui->treePromena->insertTopLevelItems(0, listPromjene);
        ui->treePromena->setCurrentItem(listPromjene.first());
        ui->treePromena->expandAll();
//      ui->treePromena->collapseAll();
    }
}
void FrmStrankaZurnal::popuniMaticnuPromjenuPrijeZaGrupuImovine()
{
    if(m_iMaticnePromjenePrijeId == 0)
    {
        return;
    }

    string strSqlStatement;

//    strSqlStatement.append("SELECT ");
//    strSqlStatement.append("NVL(KLASA,'...') KLASA, ");
//    strSqlStatement.append("NVL(TELEFON,'...') TELEFON, ");
//    strSqlStatement.append("NVL(PRETPLATA,'...') PRETPLATA, ");
//    strSqlStatement.append("NVL(DOD_USLUGE,'...') DOD_USLUGE, ");
//    strSqlStatement.append("NVL(TO_CHAR(DATUM_PROMJENE,'DD.MM.YYYY HH24:MI'),'...') DATUM, ");
//    strSqlStatement.append("NVL(OPERATER,'...') OPERATER, ");
//    strSqlStatement.append("NVL(TO_CHAR(CUST_ID),'...') CUST_ID, ");
//    strSqlStatement.append("NVL(TO_CHAR(KONT_ID),'...') KONT_ID, ");
//    strSqlStatement.append("NVL(TO_CHAR(BILL_ID),'...') BILL_ID, ");
//    strSqlStatement.append("NVL(TO_CHAR(SERV_ID),'...') SERV_ID, ");
//    strSqlStatement.append("NVL(NAZIV_CUST,'...') NAZIV_CUST, ");
//    strSqlStatement.append("NVL(NAZIV_KONT,'...') NAZIV_KONT, ");
//    strSqlStatement.append("NVL(NAZIV_BILL,'...') NAZIV_BILL, ");
//    strSqlStatement.append("NVL(NAZIV_SERV,'...') NAZIV_SERV, ");
//    strSqlStatement.append("NVL(ADRESA_CUST,'...') ADRESA_CUST, ");
//    strSqlStatement.append("NVL(ADRESA_KONT,'...') ADRESA_KONT, ");
//    strSqlStatement.append("NVL(ADRESA_BILL,'...') ADRESA_BILL, ");
//    strSqlStatement.append("NVL(ADRESA_SERV,'...') ADRESA_SERV, ");
//    strSqlStatement.append("NVL(TIP_STRANKE,'...') TIP_STRANKE, ");
//    strSqlStatement.append("NVL(PODTIP_STRANKE,'...') PODTIP_STRANKE, ");
//    strSqlStatement.append("NVL(MARKET_SEGMENT,'...') MARKET_SEGMENT, ");
//    strSqlStatement.append("NVL(TIP_ISPRAVE,'...') TIP_ISPRAVE, ");
//    strSqlStatement.append("NVL(BROJ_ISPRAVE,'...') BROJ_ISPRAVE, ");
//    strSqlStatement.append("NVL(TIP_PORB,'...') TIP_PORB, ");
//    strSqlStatement.append("NVL(MBR,'...') MBR, ");
//    strSqlStatement.append("NVL(VRSTA_RACUNA,'...') VRSTA_RACUNA, ");
//    strSqlStatement.append("NVL(MEDIJ_RACUNA,'...') MEDIJ_RACUNA, ");
//    strSqlStatement.append("NVL(KRED_KLASA,'...') KRED_KLASA, ");
//    strSqlStatement.append("NVL(TIP_OPOMINJANJA,'...') TIP_OPOMINJANJA, ");
//    strSqlStatement.append("NVL(POREZ,'...') POREZ ");
//    strSqlStatement.append(" FROM MATICNE_PROMJENE_TEL WHERE MATPROM_TEL_ID = ");
//    strSqlStatement.append(cttl::itos(m_iMaticnePromjenePrijeId));

    strSqlStatement.append("SELECT MATPROM_TEL_ID, MATPROM_ID, GIMOVINE_ID, KLASA, TELEFON, B1, PRETPLATA, DOD_USLUGE, TITULA, TIP_ISPRAVE, ");
    strSqlStatement.append(" BROJ_ISPRAVE, TIP_PORB, MBR, TIP_STRANKE, PODTIP_STRANKE, MARKET_SEGMENT, VRSTA_RACUNA, MEDIJ_RACUNA, KRED_KLASA, ");
    strSqlStatement.append(" TIP_OPOMINJANJA, POREZ, BILL_ID, CUST_ID, SERV_ID, KONT_ID, NAZIV_BILL, ADRESA_BILL, NAZIV_CUST, ADRESA_CUST, ");
    strSqlStatement.append(" NAZIV_SERV, ADRESA_SERV, NAZIV_KONT, ADRESA_KONT, TO_CHAR(DATUM_PROMJENE, 'DD.MM.YYYY HH24:MI:SS') DATUM_PROMJENE, ");
    strSqlStatement.append(" OPERATER, STATUS ");
    strSqlStatement.append(" FROM MATICNE_PROMJENE_TEL WHERE MATPROM_TEL_ID = ");
    strSqlStatement.append(cttl::itos(m_iMaticnePromjenePrijeId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listPromjene;
//    m_GrupaImovinePromjenaPrije = new maticna_promjena_tel_t();

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(!rs->isNull(1))
            {
                m_GrupaImovinePromjenaPrije.MATPROM_TEL_ID = cttl::getUIntAsONumber(rs->getNumber(1)); //rs->getUInt(1);
            }
            if(!rs->isNull(2))
            {
                m_GrupaImovinePromjenaPrije.MATPROM_ID = cttl::getUIntAsONumber(rs->getNumber(2)); //rs->getUInt(2);
            }
            m_GrupaImovinePromjenaPrije.GIMOVINE_ID = rs->getUInt(3);
            m_GrupaImovinePromjenaPrije.KLASA = rs->getString(4);
            m_GrupaImovinePromjenaPrije.TELEFON = rs->getString(5);
            m_GrupaImovinePromjenaPrije.B1 = rs->getInt(6);
            m_GrupaImovinePromjenaPrije.PRETPLATA = rs->getString(7);
            m_GrupaImovinePromjenaPrije.DOD_USLUGE = rs->getString(8);
            m_GrupaImovinePromjenaPrije.TITULA = rs->getString(9);
            m_GrupaImovinePromjenaPrije.TIP_ISPRAVE = rs->getString(10);
            m_GrupaImovinePromjenaPrije.BROJ_ISPRAVE = rs->getString(11);
            m_GrupaImovinePromjenaPrije.TIP_PORB = rs->getString(12);
            m_GrupaImovinePromjenaPrije.MBR = rs->getString(13);
            m_GrupaImovinePromjenaPrije.TIP_STRANKE = rs->getString(14);
            m_GrupaImovinePromjenaPrije.PODTIP_STRANKE = rs->getString(15);
            m_GrupaImovinePromjenaPrije.MARKET_SEGMENT = rs->getString(16);
            m_GrupaImovinePromjenaPrije.VRSTA_RACUNA = rs->getString(17);
            m_GrupaImovinePromjenaPrije.MEDIJ_RACUNA = rs->getString(18);
            m_GrupaImovinePromjenaPrije.KRED_KLASA = rs->getString(19);
            m_GrupaImovinePromjenaPrije.TIP_OPOMINJANJA = rs->getString(20);
            m_GrupaImovinePromjenaPrije.POREZ = rs->getString(21);
            if(!rs->isNull(22))
            {
                m_GrupaImovinePromjenaPrije.BILL_ID = cttl::getUIntAsONumber(rs->getNumber(22)); //rs->getUInt(22);
            }
            if(!rs->isNull(23))
            {
                m_GrupaImovinePromjenaPrije.CUST_ID = cttl::getUIntAsONumber(rs->getNumber(23)); //rs->getUInt(23);
            }
            if(!rs->isNull(24))
            {
                m_GrupaImovinePromjenaPrije.SERV_ID = cttl::getUIntAsONumber(rs->getNumber(24)); //rs->getUInt(24);
            }
            if(!rs->isNull(25))
            {
                m_GrupaImovinePromjenaPrije.KONT_ID = cttl::getUIntAsONumber(rs->getNumber(25)); //rs->getUInt(25);
            }
            m_GrupaImovinePromjenaPrije.NAZIV_BILL = rs->getString(26);
            m_GrupaImovinePromjenaPrije.ADRESA_BILL = rs->getString(27);
            m_GrupaImovinePromjenaPrije.NAZIV_CUST = rs->getString(28);
            m_GrupaImovinePromjenaPrije.ADRESA_CUST = rs->getString(29);
            m_GrupaImovinePromjenaPrije.NAZIV_SERV = rs->getString(30);
            m_GrupaImovinePromjenaPrije.ADRESA_SERV = rs->getString(31);
            m_GrupaImovinePromjenaPrije.NAZIV_KONT = rs->getString(32);
            m_GrupaImovinePromjenaPrije.ADRESA_KONT = rs->getString(33);
            m_GrupaImovinePromjenaPrije.DATUM_PROMJENE = rs->getString(34);
            m_GrupaImovinePromjenaPrije.OPERATER = rs->getString(35);
            m_GrupaImovinePromjenaPrije.STATUS = rs->getString(36);
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

    ui->lblKlasa2->setText(QString::fromStdString(m_GrupaImovinePromjenaPrije.TELEFON + " ... " + m_GrupaImovinePromjena.KLASA));
    ui->lblPretplata2->setText(QString::fromStdString(m_GrupaImovinePromjenaPrije.PRETPLATA));

    QString strImovina = QString::fromStdString(m_GrupaImovinePromjenaPrije.DOD_USLUGE).replace(tr(","), tr("\n"));
    ui->lblImovina2->setText(strImovina);

    // Provjere
    // [10] Provjera Kupca
    if(m_GrupaImovinePromjena.CUST_ID != m_GrupaImovinePromjenaPrije.CUST_ID)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("11"))
            {
                QTreeWidgetItem *itemKupac1 = new QTreeWidgetItem();
                itemKupac1->setText(1, tr("111"));
                itemKupac1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::number(m_GrupaImovinePromjenaPrije.CUST_ID));
                (*it)->addChild(itemKupac1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.NAZIV_CUST != m_GrupaImovinePromjenaPrije.NAZIV_CUST)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("12"))
            {
                QTreeWidgetItem *itemKupac2 = new QTreeWidgetItem();
                itemKupac2->setText(1, tr("112"));
                itemKupac2->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.NAZIV_CUST));
                (*it)->addChild(itemKupac2);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.ADRESA_CUST != m_GrupaImovinePromjenaPrije.ADRESA_CUST)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("13"))
            {
                QTreeWidgetItem *itemKupac3 = new QTreeWidgetItem();
                itemKupac3->setText(1, tr("113"));
                itemKupac3->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.ADRESA_CUST));
                (*it)->addChild(itemKupac3);
            }
            ++it;
        }
    }
    // [20] Provjera Kontakta
    if(m_GrupaImovinePromjena.KONT_ID != m_GrupaImovinePromjenaPrije.KONT_ID)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("21"))
            {
                QTreeWidgetItem *itemKontakt1 = new QTreeWidgetItem();
                itemKontakt1->setText(1, tr("211"));
                itemKontakt1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::number(m_GrupaImovinePromjenaPrije.KONT_ID));
                (*it)->addChild(itemKontakt1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.NAZIV_KONT != m_GrupaImovinePromjenaPrije.NAZIV_KONT)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("22"))
            {
                QTreeWidgetItem *itemKontakt1 = new QTreeWidgetItem();
                itemKontakt1->setText(1, tr("221"));
                itemKontakt1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.NAZIV_KONT));
                (*it)->addChild(itemKontakt1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.ADRESA_KONT != m_GrupaImovinePromjenaPrije.ADRESA_KONT)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("23"))
            {
                QTreeWidgetItem *itemKontakt1 = new QTreeWidgetItem();
                itemKontakt1->setText(1, tr("231"));
                itemKontakt1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.ADRESA_KONT));
                (*it)->addChild(itemKontakt1);
            }
            ++it;
        }
    }

    // [30] Provjera Racuna
    if(m_GrupaImovinePromjena.BILL_ID != m_GrupaImovinePromjenaPrije.BILL_ID)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("31"))
            {
                QTreeWidgetItem *itemBillingAccount1 = new QTreeWidgetItem();
                itemBillingAccount1->setText(1, tr("311"));
                itemBillingAccount1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::number(m_GrupaImovinePromjenaPrije.BILL_ID));
                (*it)->addChild(itemBillingAccount1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.NAZIV_BILL != m_GrupaImovinePromjenaPrije.NAZIV_BILL)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("32"))
            {
                QTreeWidgetItem *itemBillingAccount1 = new QTreeWidgetItem();
                itemBillingAccount1->setText(1, tr("321"));
                itemBillingAccount1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.NAZIV_BILL));
                (*it)->addChild(itemBillingAccount1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.ADRESA_BILL != m_GrupaImovinePromjenaPrije.ADRESA_BILL)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("33"))
            {
                QTreeWidgetItem *itemBillingAccount1 = new QTreeWidgetItem();
                itemBillingAccount1->setText(1, tr("331"));
                itemBillingAccount1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.ADRESA_BILL));
                (*it)->addChild(itemBillingAccount1);
            }
            ++it;
        }
    }

    // [40] Provjera Instalacije
    if(m_GrupaImovinePromjena.SERV_ID != m_GrupaImovinePromjenaPrije.SERV_ID)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("41"))
            {
                QTreeWidgetItem *itemInstalacija1 = new QTreeWidgetItem();
                itemInstalacija1->setText(1, tr("411"));
                itemInstalacija1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::number(m_GrupaImovinePromjenaPrije.SERV_ID));
                (*it)->addChild(itemInstalacija1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.NAZIV_SERV != m_GrupaImovinePromjenaPrije.NAZIV_SERV)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("42"))
            {
                QTreeWidgetItem *itemInstalacija1 = new QTreeWidgetItem();
                itemInstalacija1->setText(1, tr("421"));
                itemInstalacija1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.NAZIV_SERV));
                (*it)->addChild(itemInstalacija1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.ADRESA_SERV != m_GrupaImovinePromjenaPrije.ADRESA_SERV)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("43"))
            {
                QTreeWidgetItem *itemInstalacija1 = new QTreeWidgetItem();
                itemInstalacija1->setText(1, tr("431"));
                itemInstalacija1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.ADRESA_SERV));
                (*it)->addChild(itemInstalacija1);
            }
            ++it;
        }
    }

    // [50] Stranka
    if(m_GrupaImovinePromjena.TIP_STRANKE != m_GrupaImovinePromjenaPrije.TIP_STRANKE)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("51"))
            {
                QTreeWidgetItem *itemStranka1 = new QTreeWidgetItem();
                itemStranka1->setText(1, tr("511"));
                itemStranka1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.TIP_STRANKE));
                (*it)->addChild(itemStranka1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.PODTIP_STRANKE != m_GrupaImovinePromjenaPrije.PODTIP_STRANKE)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("52"))
            {
                QTreeWidgetItem *itemStranka1 = new QTreeWidgetItem();
                itemStranka1->setText(1, tr("521"));
                itemStranka1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.PODTIP_STRANKE));
                (*it)->addChild(itemStranka1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.MARKET_SEGMENT != m_GrupaImovinePromjenaPrije.MARKET_SEGMENT)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("53"))
            {
                QTreeWidgetItem *itemStranka1 = new QTreeWidgetItem();
                itemStranka1->setText(1, tr("531"));
                itemStranka1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.MARKET_SEGMENT));
                (*it)->addChild(itemStranka1);
            }
            ++it;
        }
    }

    // [60] Isprave
    if(m_GrupaImovinePromjena.TIP_ISPRAVE != m_GrupaImovinePromjenaPrije.TIP_ISPRAVE)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("61"))
            {
                QTreeWidgetItem *itemIsprave1 = new QTreeWidgetItem();
                itemIsprave1->setText(1, tr("611"));
                itemIsprave1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.TIP_ISPRAVE));
                (*it)->addChild(itemIsprave1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.BROJ_ISPRAVE != m_GrupaImovinePromjenaPrije.BROJ_ISPRAVE)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("62"))
            {
                QTreeWidgetItem *itemIsprave1 = new QTreeWidgetItem();
                itemIsprave1->setText(1, tr("621"));
                itemIsprave1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.BROJ_ISPRAVE));
                (*it)->addChild(itemIsprave1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.TIP_PORB != m_GrupaImovinePromjenaPrije.TIP_PORB)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("63"))
            {
                QTreeWidgetItem *itemIsprave1 = new QTreeWidgetItem();
                itemIsprave1->setText(1, tr("631"));
                itemIsprave1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.TIP_PORB));
                (*it)->addChild(itemIsprave1);
            }
            ++it;
        }
    }
    if(m_GrupaImovinePromjena.POREZ != m_GrupaImovinePromjenaPrije.POREZ)
    {
        QTreeWidgetItemIterator it(ui->treePromena);
        while (*it)
        {
            if ((*it)->text(1) == tr("64"))
            {
                QTreeWidgetItem *itemIsprave1 = new QTreeWidgetItem();
                itemIsprave1->setText(1, tr("641"));
                itemIsprave1->setText(0, QString::fromStdString(m_GrupaImovinePromjenaPrije.DATUM_PROMJENE) + tr(" - ") + QString::fromStdString(m_GrupaImovinePromjenaPrije.POREZ));
                (*it)->addChild(itemIsprave1);
            }
            ++it;
        }
    }

    ui->treePromena->expandAll();
}

void FrmStrankaZurnal::popuniMaticnuPromjenuZaUloguStranke()
{
    if(m_iMaticnePromjeneId == 0)
    {
        return;
    }

    string strKupacNaziv;
    string strSqlStatement;

    //    SELECT MATPROM_ID, ULSTRANKE_ID, FORMATIRANI_NAZIV, NAZIV3, TITULA, TIP_ISPRAVE, BROJ_ISPRAVE, TIP_PORB, MBR,
    //      TIP_STRANKE, PODTIP_STRANKE, MARKET_SEGMENT, VRSTA_RACUNA, MEDIJ_RACUNA, KRED_KLASA, TIP_OPOMINJANJA,
    //      POREZ, NAZIV_KONTAKTA, ADRESA_KONTAKTA, TO_CHAR(DATUM_PROMJENE, 'DD.MM.YYYY HH24:MI:SS') DATUM_PROMJENE, OPERATER
    //    FROM MATICNE_PROMJENE ;

    strSqlStatement.append("SELECT MATPROM_ID, ULSTRANKE_ID, FORMATIRANI_NAZIV, NAZIV3, TITULA, TIP_ISPRAVE, BROJ_ISPRAVE, TIP_PORB, MBR, ");
    strSqlStatement.append(" TIP_STRANKE, PODTIP_STRANKE, MARKET_SEGMENT, VRSTA_RACUNA, MEDIJ_RACUNA, KRED_KLASA, TIP_OPOMINJANJA, ");
    strSqlStatement.append(" POREZ, NAZIV_KONTAKTA, ADRESA_KONTAKTA, TO_CHAR(DATUM_PROMJENE, 'DD.MM.YYYY HH24:MI:SS') DATUM_PROMJENE, OPERATER ");
    strSqlStatement.append(" FROM MATICNE_PROMJENE WHERE MATPROM_ID = ");
    strSqlStatement.append(cttl::itos(m_iMaticnePromjeneId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listPromjene;
//    m_UlogaStrankePromjena = new maticna_promjena_t();

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(!rs->isNull(1))
            {
                m_UlogaStrankePromjena.MATPROM_ID = cttl::getUIntAsONumber(rs->getNumber(1)); //rs->getUInt(1);
            }
            if(!rs->isNull(2))
            {
                m_UlogaStrankePromjena.ULSTRANKE_ID = cttl::getUIntAsONumber(rs->getNumber(2)); //rs->getUInt(2);
            }
            m_UlogaStrankePromjena.FORMATIRANI_NAZIV = rs->getString(3);
            m_UlogaStrankePromjena.NAZIV3 = rs->getString(4);
            m_UlogaStrankePromjena.TITULA = rs->getString(5);
            m_UlogaStrankePromjena.TIP_ISPRAVE = rs->getString(6);
            m_UlogaStrankePromjena.BROJ_ISPRAVE = rs->getString(7);
            m_UlogaStrankePromjena.TIP_PORB = rs->getString(8);
            m_UlogaStrankePromjena.MBR = rs->getString(9);
            m_UlogaStrankePromjena.TIP_STRANKE = rs->getString(10);
            m_UlogaStrankePromjena.PODTIP_STRANKE = rs->getString(11);
            m_UlogaStrankePromjena.MARKET_SEGMENT = rs->getString(12);
            m_UlogaStrankePromjena.VRSTA_RACUNA = rs->getString(13);
            m_UlogaStrankePromjena.MEDIJ_RACUNA = rs->getString(14);
            m_UlogaStrankePromjena.KRED_KLASA = rs->getString(15);
            m_UlogaStrankePromjena.TIP_OPOMINJANJA = rs->getString(16);
            m_UlogaStrankePromjena.POREZ = rs->getString(17);
            m_UlogaStrankePromjena.NAZIV_KONTAKTA = rs->getString(18);
            m_UlogaStrankePromjena.ADRESA_KONTAKTA = rs->getString(19);
            m_UlogaStrankePromjena.DATUM_PROMJENE = rs->getString(20);
            m_UlogaStrankePromjena.OPERATER = rs->getString(21);
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
    strSqlStatement.append("SELECT R.NAZIV FROM ULOGE_STRANAKA P,TIPOVI_ULSTR R WHERE ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(m_UlogaStrankePromjena.ULSTRANKE_ID));
    strSqlStatement.append(" AND R.TULSTRANKE_ID = P.TULSTRANKE_ID ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strKupacNaziv = rs->getString(1);
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

    ui->lblOperater->clear();
    ui->lblKlasa->clear();
    ui->lblPretplata->clear();
    ui->lblImovina1->clear();

    QTreeWidgetItem *itemKupac = new QTreeWidgetItem();
    itemKupac->setText(1, tr("10"));
    itemKupac->setText(0, QString::fromStdString(strKupacNaziv).toUpper());
    QTreeWidgetItem *itemKupac1 = new QTreeWidgetItem();
    itemKupac1->setText(1, tr("11"));
    itemKupac1->setText(0, tr("ID ...") + QString::number(m_UlogaStrankePromjena.ULSTRANKE_ID));
    itemKupac->addChild(itemKupac1);
    QTreeWidgetItem *itemKupac2 = new QTreeWidgetItem();
    itemKupac2->setText(1, tr("12"));
    itemKupac2->setText(0, QString::fromStdString(m_UlogaStrankePromjena.FORMATIRANI_NAZIV));
    itemKupac->addChild(itemKupac2);
    listPromjene.append(itemKupac);

    QTreeWidgetItem *itemKontakt = new QTreeWidgetItem();
    itemKontakt->setText(1, tr("20"));
    itemKontakt->setText(0, tr("KONTAKT"));
    QTreeWidgetItem *itemKontakt2 = new QTreeWidgetItem();
    itemKontakt2->setText(1, tr("22"));
    itemKontakt2->setText(0, QString::fromStdString(m_UlogaStrankePromjena.NAZIV_KONTAKTA));
    itemKontakt->addChild(itemKontakt2);
    QTreeWidgetItem *itemKontakt3 = new QTreeWidgetItem();
    itemKontakt3->setText(1, tr("23"));
    itemKontakt3->setText(0, QString::fromStdString(m_UlogaStrankePromjena.ADRESA_KONTAKTA));
    itemKontakt->addChild(itemKontakt3);
    listPromjene.append(itemKontakt);

    QTreeWidgetItem *itemRacun = new QTreeWidgetItem();
    itemRacun->setText(1, tr("30"));
    itemRacun->setText(0, tr("STRANKA"));
    QTreeWidgetItem *itemRacun1 = new QTreeWidgetItem();
    itemRacun1->setText(1, tr("31"));
    itemRacun1->setText(0, tr("Tip ...") + QString::fromStdString(m_UlogaStrankePromjena.TIP_STRANKE));
    itemRacun->addChild(itemRacun1);
    QTreeWidgetItem *itemRacun2 = new QTreeWidgetItem();
    itemRacun2->setText(1, tr("32"));
    itemRacun2->setText(0, tr("Podtip ...") + QString::fromStdString(m_UlogaStrankePromjena.PODTIP_STRANKE));
    itemRacun->addChild(itemRacun2);
    QTreeWidgetItem *itemRacun3 = new QTreeWidgetItem();
    itemRacun3->setText(1, tr("33"));
    itemRacun3->setText(0, tr("Segment ...") + QString::fromStdString(m_UlogaStrankePromjena.MARKET_SEGMENT));
    itemRacun->addChild(itemRacun3);
    listPromjene.append(itemRacun);

    QTreeWidgetItem *itemInstalacija = new QTreeWidgetItem();
    itemInstalacija->setText(1, tr("40"));
    itemInstalacija->setText(0, tr("ISPRAVE"));
    QTreeWidgetItem *itemInstalacija1 = new QTreeWidgetItem();
    itemInstalacija1->setText(1, tr("41"));
    itemInstalacija1->setText(0, tr("Tip Isprave ...") + QString::fromStdString(m_UlogaStrankePromjena.TIP_ISPRAVE));
    itemInstalacija->addChild(itemInstalacija1);
    QTreeWidgetItem *itemInstalacija2 = new QTreeWidgetItem();
    itemInstalacija2->setText(1, tr("42"));
    itemInstalacija2->setText(0, tr("Broj Isprave ...") + QString::fromStdString(m_UlogaStrankePromjena.BROJ_ISPRAVE));
    itemInstalacija->addChild(itemInstalacija2);
    QTreeWidgetItem *itemInstalacija3 = new QTreeWidgetItem();
    itemInstalacija3->setText(1, tr("43"));
    itemInstalacija3->setText(0, tr("Tip Poreznog Broja ...") + QString::fromStdString(m_UlogaStrankePromjena.TIP_PORB));
    itemInstalacija->addChild(itemInstalacija3);
    QTreeWidgetItem *itemInstalacija4 = new QTreeWidgetItem();
    itemInstalacija4->setText(1, tr("44"));
    itemInstalacija4->setText(0, tr("Porezni Broj ...") + QString::fromStdString(m_UlogaStrankePromjena.MBR));
    itemInstalacija->addChild(itemInstalacija4);
    listPromjene.append(itemInstalacija);

    QTreeWidgetItem *itemStranka = new QTreeWidgetItem();
    itemStranka->setText(1, tr("50"));
    itemStranka->setText(0, tr("VRSTA RAČUNA"));
    QTreeWidgetItem *itemStranka1 = new QTreeWidgetItem();
    itemStranka1->setText(1, tr("51"));
    itemStranka1->setText(0, tr("Vrsta Računa ...") + QString::fromStdString(m_GrupaImovinePromjena.VRSTA_RACUNA));
    itemStranka->addChild(itemStranka1);
    QTreeWidgetItem *itemStranka2 = new QTreeWidgetItem();
    itemStranka2->setText(1, tr("52"));
    itemStranka2->setText(0, tr("Medij Računa ...") + QString::fromStdString(m_GrupaImovinePromjena.MEDIJ_RACUNA));
    itemStranka->addChild(itemStranka2);
    QTreeWidgetItem *itemStranka3 = new QTreeWidgetItem();
    itemStranka3->setText(1, tr("53"));
    itemStranka3->setText(0, tr("Kreditna Klasa ...") + QString::fromStdString(m_GrupaImovinePromjena.KRED_KLASA));
    itemStranka->addChild(itemStranka3);
    QTreeWidgetItem *itemStranka4 = new QTreeWidgetItem();
    itemStranka4->setText(1, tr("54"));
    itemStranka4->setText(0, tr("Tip Opominjanja ...") + QString::fromStdString(m_GrupaImovinePromjena.TIP_OPOMINJANJA));
    itemStranka->addChild(itemStranka4);
    QTreeWidgetItem *itemStranka5 = new QTreeWidgetItem();
    itemStranka5->setText(1, tr("55"));
    itemStranka5->setText(0, tr("Porez ...") + QString::fromStdString(m_GrupaImovinePromjena.POREZ));
    itemStranka->addChild(itemStranka5);
    listPromjene.append(itemStranka);

    if(!listPromjene.empty())
    {
        listPromjene.first()->setSelected(true);
        ui->treePromena->insertTopLevelItems(0, listPromjene);
        ui->treePromena->setCurrentItem(listPromjene.first());
        ui->treePromena->expandAll();
//      ui->treePromena->collapseAll();
    }

}
void FrmStrankaZurnal::popuniMaticnuPromjenuPrijeZaUloguStranke()
{
}

// [Event Handlers]
void FrmStrankaZurnal::on_btnTrazi_clicked()
{
    if(m_iTipPretrage == 1)
    {
        // Pretraga po broju telefona
        m_strTelefonskiBroj = ui->txtSearch->text().toStdString();
        popuniPoTelefonskomBroju();
    }
    else if(m_iTipPretrage == 2)
    {
        // Pretraga po ulozi stranke id
        try
        {
            m_iKupacId = ui->txtSearch->text().toUInt();
        }
        catch(exception)
        {
            m_iKupacId = 0;
        }
        popuniListePromjenaUlogaStranke();
    }
}

void FrmStrankaZurnal::on_btnSearchPhoneNumber_clicked()
{
    m_iTipPretrage = 1;
}

void FrmStrankaZurnal::on_btnSearchUlogaStranke_clicked()
{
    m_iTipPretrage = 2;
}

void FrmStrankaZurnal::on_treeIzmjene_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    QTreeWidgetItem *itemBelow = ui->treeIzmjene->itemBelow(item);
    if(itemBelow > 0)
    {
        m_iMaticnePromjenePrijeId = itemBelow->text(1).toUInt();
    }
    else
    {
        m_iMaticnePromjenePrijeId = 0;
    }

    m_iMaticnePromjeneId = item->text(1).toUInt();
    if(m_iTipPromjene == 1)
    {
        clearPromjena();
        popuniMaticnuPromjenuZaGrupuImovine();
        popuniMaticnuPromjenuPrijeZaGrupuImovine();
    }
    else
    {
        clearPromjena();
        popuniMaticnuPromjenuZaUloguStranke();
    }
}

void FrmStrankaZurnal::on_treeGrupeImovine_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    m_iGrupaImovineId = item->text(4).toUInt();
    m_strTelefonskiBroj = item->text(7).toStdString();

    popuniListePromjena();
}

}

