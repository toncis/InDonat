//
//  frmpregledimovine.cpp
//
//  Author:
//       Tonči Sviličić <tonci.svilicic@in2.hr>
//
//  Copyright (c) 2015 Tonči Sviličić
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

#include "frmpregledn.h"
#include "ui_frmpregledn.h"

#include "itos.h"

#include "forms/kontakt/frmkanalprodaje.h"
#include "forms/kontakt/frmkanalprodajekorisnik.h"


namespace Sporazumi {

// [Class Constructor]
FrmPregledN::FrmPregledN(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPregledN)
{
    ui->setupUi(this);

    initForm();
}

FrmPregledN::~FrmPregledN()
{
    delete ui;
}

// [Private Member Functions]
void FrmPregledN::initForm()
{
    ui->fraStavke->setVisible(false);

    ui->dateOd->setDateTime(QDateTime::currentDateTime().addDays(-7));
    ui->dateDo->setDateTime(QDateTime::currentDateTime());
    ui->dateAktivnosti->setDateTime(QDateTime::currentDateTime());

    ui->treeListeGrupa->setColumnWidth(0, 200);
    ui->treeListeGrupa->hideColumn(1);
    ui->treeListeGrupa->hideColumn(2);
    ui->treeListeGrupa->hideColumn(3);
    ui->treeListeGrupa->hideColumn(4);
    ui->treeListeGrupa->hideColumn(5);
    ui->treeListeGrupa->hideColumn(6);
    ui->treeListeGrupa->hideColumn(7);
    ui->treeListeGrupa->hideColumn(8);

    ui->treeSporazumi->setColumnWidth(0, 800);
    ui->treeSporazumi->hideColumn(1);
    ui->treeSporazumi->hideColumn(2);
    ui->treeSporazumi->hideColumn(3);
    ui->treeSporazumi->hideColumn(4);
    ui->treeSporazumi->hideColumn(5);
    ui->treeSporazumi->hideColumn(6);

    m_iNoDef = 1001;

    m_iSporazumId = 0;
    m_iListaGrupa = 1;
    m_iTipKorisnika = 1;
    m_iTipKanala = 1;
    m_iTipKupca = 0;
    m_iTipFiltra = 0;
    m_iTipDodatnogFiltra = 0;

    ui->btnKanalProdaje->setChecked(true);
    ui->btnRegija->setChecked(false);

    ui->btnZahtjevUnio->setChecked(true);
    ui->btnZahtjevProdao->setChecked(false);

    ui->btnZahtjev->setChecked(true);
    ui->btnUgovor->setChecked(false);
    ui->btnObavijest->setChecked(false);
    ui->btnSme->setChecked(false);

    ui->btnPretragaPrivatni->setChecked(true);
    ui->btnPretragaKljucni->setChecked(false);
    ui->btnPretragatSme->setChecked(false);
    ui->btnPretragaVeleprodaja->setChecked(false);

    ui->btnKorisnikKanal->setText(QString::fromStdString(g_FILTER_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_KORISNIK_NAZ));

    popunaKlasa();
    popunaListaGrupa();
}
void FrmPregledN::initSporazum()
{
    m_iSporazumId = 0;
    m_iStrankaId = 0;
    m_iKupacId = 0;

    ui->treeSporazumStavke->clear();
    ui->treeAktivnosti->clear();
    ui->treeStavke->clear();

    ui->lblZahtjevFullTitle->clear();
    ui->lblKupacId->clear();
    ui->lblKupacNaziv->clear();

}
void FrmPregledN::initSlog()
{
}

void FrmPregledN::setKorisnik()
{
    if(m_iTipKanala == 1)
    {
        ui->btnKorisnikKanal->setText(QString::fromStdString(g_FILTER_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_KORISNIK_NAZ));
        if(m_iTipKorisnika == 0)
        {
            m_iTipKorisnika = 1;
            ui->btnZahtjevUnio->setChecked(true);
            ui->btnZahtjevProdao->setChecked(false);
        }

        if(g_FILTER_KORISNIK_ID == "0")
        {
            m_iTipKorisnika = 0;
            ui->btnZahtjevUnio->setChecked(false);
            ui->btnZahtjevProdao->setChecked(false);
        }
    }
    else if(m_iTipKanala == 2)
    {
        ui->btnKorisnikKanal->setText(QString::fromStdString(g_FILTER_REGIJA_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_ZUPANIJA_NAZ));
        m_iTipKorisnika = 0;
        ui->btnZahtjevUnio->setChecked(false);
        ui->btnZahtjevProdao->setChecked(false);
    }
}

void FrmPregledN::popunaKlasa()
{
    ui->cboPretragaKlase->clear();

    ui->cboPretragaKlase->addItem(tr("SVE GRUPE"), QVariant::fromValue(0));
    m_iFltLinijaProdukataId = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT LPRODUKATA_ID, NAZIV FROM LINIJE_PRODUKATA WHERE VIDLJIVOST = 1 ORDER BY NAZIV");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ui->cboPretragaKlase->blockSignals(true);
        ResultSet *rs = sqlStatement->executeQuery();

        while(rs->next())
        {
            ui->cboPretragaKlase->addItem(QString::fromStdString(rs->getString(2)), QVariant::fromValue(rs->getInt(1)));
        }

        sqlStatement->closeResultSet(rs);
        ui->cboPretragaKlase->blockSignals(false);
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
void FrmPregledN::popunaListaGrupa()
{
    ui->treeListeGrupa->clear();

    QList<QTreeWidgetItem *> listListaGrupa;

    string strSqlStatement;
    strSqlStatement.append("SELECT P.ID, P.NAD_ID, P.NIVO, P.NAZIV, P.TIP, P.VALUE, P.GRUPA, P.AKT_SUB, P.AKT_SEL ");
    strSqlStatement.append("FROM KONTAKT_S_PREGLED P ");
    strSqlStatement.append("WHERE GRUPA = ");
    strSqlStatement.append(cttl::itos(m_iListaGrupa));
    strSqlStatement.append(" ORDER BY P.NIVO, P.ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        while(rs->next())
        {
            QTreeWidgetItem *itemGrupa = new QTreeWidgetItem();
            itemGrupa->setText(0, QString::fromStdString(rs->getString(4)));
            itemGrupa->setText(1, QString::number(rs->getInt(1)));
            itemGrupa->setText(2, QString::number(rs->getInt(2)));
            itemGrupa->setText(3, QString::number(rs->getInt(3)));
            itemGrupa->setText(4, QString::number(rs->getInt(5)));
            itemGrupa->setText(5, QString::fromStdString(rs->getString(6)));
            itemGrupa->setText(6, QString::number(rs->getInt(7)));
            itemGrupa->setText(7, QString::number(rs->getInt(8)));
            itemGrupa->setText(8, QString::number(rs->getInt(9)));
            //listListaGrupa.append(itemGrupa);
            //addNewGrupaToListGrupe(listListaGrupa, itemGrupa);

            if(listListaGrupa.count() == 0)
            {
                listListaGrupa.append(itemGrupa);
            }
            else if((itemGrupa->text(3).toInt() == 0) && (itemGrupa->text(2).toInt() == 0))
            {
                listListaGrupa.append(itemGrupa);
            }
            else
            {
                int iListSize = listListaGrupa.size();
                for(int i = 0; i < iListSize; ++i)
                {
                    if(listListaGrupa.at(i)->text(1).toInt() == itemGrupa->text(2).toInt())
                    {
                        listListaGrupa.at(i)->addChild(itemGrupa);
                    }
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

    if(!listListaGrupa.empty())
    {
        listListaGrupa.first()->setSelected(true);
        ui->treeListeGrupa->insertTopLevelItems(0, listListaGrupa);
        //ui->treeListeGrupa->expandAll();
        ui->treeListeGrupa->collapseAll();
        ui->treeListeGrupa->expandItem(listListaGrupa.first());
        ui->treeListeGrupa->setCurrentItem(listListaGrupa.first());
    }
}
void FrmPregledN::addNewGrupaToListGrupe(QList<QTreeWidgetItem *> listListaGrupa, QTreeWidgetItem *itemGrupa)
{
    if(listListaGrupa.count() == 0)
    {
        listListaGrupa.append(itemGrupa);
        return;
    }

    if((itemGrupa->text(2).toInt() == 0) && (itemGrupa->text(1).toInt() == 0))
    {
        listListaGrupa.append(itemGrupa);
        return;
    }

    int iListSize = listListaGrupa.size();
    for(int i = 0; i < iListSize; ++i)
    {
        if(listListaGrupa.at(i)->text(0) == itemGrupa->text(1))
        {
            listListaGrupa.at(i)->addChild(itemGrupa);
            listListaGrupa.append(itemGrupa);
        }
    }
}

void FrmPregledN::pokreniPretrazivanje()
{
    setCursor(Qt::BusyCursor);

    ui->treeSporazumi->clear();
    ui->lblFilterTtile->setText(tr("FILTER ... UPIT"));
    initSporazum();

    switch (m_iListaGrupa)
    {
        case 1:
        {
            switch (m_iListaTipId)
            {
                case 1:
                    popunaZahtjevaL1();
                    break;
                case 2:
                    popunaZahtjevaL2();
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;
        }
        case 2:
        {
            switch (m_iListaTipId)
            {
                case 1:
                    popunaUgovoraL1();
                    break;
                case 2:
                    popunaUgovoraL2();
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;
        }
        case 3:
        {
            switch (m_iListaTipId)
            {
                case 1:
                    popunaObavijestL1();
                    break;
                case 2:
                    //popunaObavijestL2();
                    break;
                case 3:
                    //popunaObavijestL3();
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }

    setCursor(Qt::ArrowCursor);
}
void FrmPregledN::popunaZahtjevaL1()
{
    ui->treeSporazumi->clear();

    QList<QTreeWidgetItem *> listSporazumi;

    string strSqlStatement;

    strSqlStatement.append("SELECT /*+ TAB_SP_IDX_1 */ ");
    strSqlStatement.append(" ROWNUM, SPORAZUM_ID, TO_CHAR(DATUM_OD, 'DD.MM.YYYY') DATUM, FORMATIRANI_NAZIV, ADRESA, BROJ_DOK, KUPAC_ID, STRANKA_ID ");
    strSqlStatement.append(" FROM TAB_PREGLED_SPORAZUMI WHERE ");
    strSqlStatement.append(" DATUM_OD BETWEEN TO_DATE('");
    strSqlStatement.append(ui->dateOd->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TO_DATE('");
    strSqlStatement.append(ui->dateDo->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TSPORAZUMA_ID IN (1, 4, 7, 8, 11, 12) ");
    strSqlStatement.append(" AND KLJUCNI_IND = ");
    strSqlStatement.append(cttl::itos(m_iTipKupca));

    if (m_strListaValue == "0")
    {
        strSqlStatement.append(" AND STATUS_ID != 0 ");
    }
    else
    {
        strSqlStatement.append(" AND STATUS_ID IN (");
        strSqlStatement.append(m_strListaValue);
        strSqlStatement.append(")");
    }

    if (m_iTipKanala == 1)
    {

        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
        if(g_FILTER_KANAL_ID != 0)
        {
           strSqlStatement.append(" AND KANAL_ID = ");
           strSqlStatement.append(cttl::itos(g_FILTER_KANAL_ID));
        }
        else
        {
           strSqlStatement.append(" AND KANAL_ID != 0 ");
        }

//        if (g_FILTER_ORGJED_ID > 0)
//        {
//            strSqlStatement.append(" AND ORGJED_ID = ");
//            strSqlStatement.append(cttl::itos(g_FILTER_ORGJED_ID));
//        }

        if (g_FILTER_KORISNIK_ID != "0")
        {
            if(m_iTipKorisnika == 1)
            {
                strSqlStatement.append(" AND OPERATER = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
            else
            {
                strSqlStatement.append(" AND KORISNIK_ID = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
        }
    }
    else
    {
        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
    }

    if (m_iFltLinijaProdukataId != 0)
    {
        strSqlStatement.append(" AND KLASA ='");
        strSqlStatement.append(cttl::itos(m_iFltLinijaProdukataId));
        strSqlStatement.append("' ");
    }

    if(m_iTipDodatnogFiltra == 1)
    {
        strSqlStatement.append(" AND FORMATIRANI_NAZIV LIKE '");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");

    }
    else if(m_iTipDodatnogFiltra == 2)
    {
        strSqlStatement.append(" AND ADRESA LIKE '%");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");
    }

    strSqlStatement.append(" AND ROWNUM < ");
    strSqlStatement.append(cttl::itos(m_iNoDef));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        while(rs->next())
        {
            QTreeWidgetItem *itemSporazum = new QTreeWidgetItem();
            itemSporazum->setText(0, QString::fromStdString(rs->getString(3)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(6)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(4)) +
                                     tr(" ,  ") +
                                     QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(1, QString::number(rs->getInt(1)));
            itemSporazum->setText(2, QString::number(rs->getUInt(2)));
            itemSporazum->setText(3, QString::fromStdString(rs->getString(3)));
            itemSporazum->setText(4, QString::fromStdString(rs->getString(4)));
            itemSporazum->setText(5, QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(6, QString::fromStdString(rs->getString(6)));
            itemSporazum->setText(7, QString::number(rs->getUInt(7)));
            itemSporazum->setText(8, QString::number(rs->getUInt(8)));
            listSporazumi.append(itemSporazum);
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

    ui->btnSporazumiUkupno->setText(tr("UK ...") + QString::number(listSporazumi.count()));
    ui->btnSporazumiRange->setText(tr("1 ...") + QString::number(listSporazumi.count()));

    if(!listSporazumi.empty())
    {
        listSporazumi.first()->setSelected(true);
        ui->treeSporazumi->insertTopLevelItems(0, listSporazumi);
        ui->treeSporazumi->expandAll();
//        ui->treeSporazumi->collapseAll();
//        ui->treeSporazumi->expandItem(listSporazumi.first());
//        ui->treeSporazumi->setCurrentItem(listSporazumi.first());
    }
}
void FrmPregledN::popunaZahtjevaL2()
{
    ui->treeSporazumi->clear();

    QList<QTreeWidgetItem *> listSporazumi;

    string strSqlStatement;

    strSqlStatement.append("SELECT /*+ TAB_SP_IDX_1 */ ");
    strSqlStatement.append(" ROWNUM, SPORAZUM_ID, TO_CHAR(DATUM_OD, 'DD.MM.YYYY') DATUM, FORMATIRANI_NAZIV, ADRESA, BROJ_DOK, KUPAC_ID, STRANKA_ID ");
    strSqlStatement.append(" FROM TAB_PREGLED_SPORAZUMI WHERE ");
    strSqlStatement.append(" DATUM_OD BETWEEN TO_DATE('");
    strSqlStatement.append(ui->dateOd->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TO_DATE('");
    strSqlStatement.append(ui->dateDo->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TSPORAZUMA_ID IN (1, 4, 7, 8, 11, 12) ");
    strSqlStatement.append(" AND KLJUCNI_IND = ");
    strSqlStatement.append(cttl::itos(m_iTipKupca));
    strSqlStatement.append(" AND STATUS_ID != 0 ");

    if (m_iTipKanala == 1)
    {

        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
        if(g_FILTER_KANAL_ID != 0)
        {
           strSqlStatement.append(" AND KANAL_ID = ");
           strSqlStatement.append(cttl::itos(g_FILTER_KANAL_ID));
        }
        else
        {
           strSqlStatement.append(" AND KANAL_ID != 0 ");
        }

//        if (g_FILTER_ORGJED_ID > 0)
//        {
//            strSqlStatement.append(" AND ORGJED_ID = ");
//            strSqlStatement.append(cttl::itos(g_FILTER_ORGJED_ID));
//        }

        if (g_FILTER_KORISNIK_ID != "0")
        {
            if(m_iTipKorisnika == 1)
            {
                strSqlStatement.append(" AND OPERATER = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
            else
            {
                strSqlStatement.append(" AND KORISNIK_ID = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
        }
    }
    else
    {
        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
    }

    if (m_iFltLinijaProdukataId != 0)
    {
        strSqlStatement.append(" AND KLASA ='");
        strSqlStatement.append(cttl::itos(m_iFltLinijaProdukataId));
        strSqlStatement.append("' ");
    }

    strSqlStatement.append(" AND SPORAZUM_ID IN (");
    strSqlStatement.append("SELECT /*+ index(PP_5) */ ID2 FROM POSLOVNI_PROCESI WHERE STANJE_ID IN (");
    strSqlStatement.append(m_strListaValue);
    strSqlStatement.append("))");

    if(m_iTipDodatnogFiltra == 1)
    {
        strSqlStatement.append(" AND FORMATIRANI_NAZIV LIKE '");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");

    }
    else if(m_iTipDodatnogFiltra == 2)
    {
        strSqlStatement.append(" AND ADRESA LIKE '%");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");
    }

    strSqlStatement.append(" AND ROWNUM < ");
    strSqlStatement.append(cttl::itos(m_iNoDef));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        while(rs->next())
        {
            QTreeWidgetItem *itemSporazum = new QTreeWidgetItem();
            itemSporazum->setText(0, QString::fromStdString(rs->getString(3)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(6)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(4)) +
                                     tr(" ,  ") +
                                     QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(1, QString::number(rs->getInt(1)));
            itemSporazum->setText(2, QString::number(rs->getUInt(2)));
            itemSporazum->setText(3, QString::fromStdString(rs->getString(3)));
            itemSporazum->setText(4, QString::fromStdString(rs->getString(4)));
            itemSporazum->setText(5, QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(6, QString::fromStdString(rs->getString(6)));
            itemSporazum->setText(7, QString::number(rs->getUInt(7)));
            itemSporazum->setText(8, QString::number(rs->getUInt(8)));
            listSporazumi.append(itemSporazum);
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

    ui->btnSporazumiUkupno->setText(tr("UK ...") + QString::number(listSporazumi.count()));
    ui->btnSporazumiRange->setText(tr("1 ...") + QString::number(listSporazumi.count()));

    if(!listSporazumi.empty())
    {
        listSporazumi.first()->setSelected(true);
        ui->treeSporazumi->insertTopLevelItems(0, listSporazumi);
        ui->treeSporazumi->expandAll();
//        ui->treeSporazumi->collapseAll();
//        ui->treeSporazumi->expandItem(listSporazumi.first());
//        ui->treeSporazumi->setCurrentItem(listSporazumi.first());
    }
}
void FrmPregledN::popunaUgovoraL1()
{
    ui->treeSporazumi->clear();

    QList<QTreeWidgetItem *> listSporazumi;

    string strSqlStatement;

    strSqlStatement.append("SELECT /*+ TAB_SP_IDX_1 */ ");
    strSqlStatement.append(" ROWNUM, SPORAZUM_ID, TO_CHAR(DATUM_OD, 'DD.MM.YYYY') DATUM, FORMATIRANI_NAZIV, ADRESA, BROJ_DOK, KUPAC_ID, STRANKA_ID ");
    strSqlStatement.append(" FROM TAB_PREGLED_SPORAZUMI WHERE ");
    strSqlStatement.append(" DATUM_OD BETWEEN TO_DATE('");
    strSqlStatement.append(ui->dateOd->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TO_DATE('");
    strSqlStatement.append(ui->dateDo->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TSPORAZUMA_ID IN (3) ");
    strSqlStatement.append(" AND KLJUCNI_IND = ");
    strSqlStatement.append(cttl::itos(m_iTipKupca));

    if (m_strListaValue == "0")
    {
        strSqlStatement.append(" AND STATUS_ID != 0 ");
    }
    else
    {
        strSqlStatement.append(" AND STATUS_ID IN (");
        strSqlStatement.append(m_strListaValue);
        strSqlStatement.append(")");
    }

    if (m_iTipKanala == 1)
    {

        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
        if(g_FILTER_KANAL_ID != 0)
        {
           strSqlStatement.append(" AND KANAL_ID = ");
           strSqlStatement.append(cttl::itos(g_FILTER_KANAL_ID));
        }
        else
        {
           strSqlStatement.append(" AND KANAL_ID != 0 ");
        }

//        if (g_FILTER_ORGJED_ID > 0)
//        {
//            strSqlStatement.append(" AND ORGJED_ID = ");
//            strSqlStatement.append(cttl::itos(g_FILTER_ORGJED_ID));
//        }

        if (g_FILTER_KORISNIK_ID != "0")
        {
            if(m_iTipKorisnika == 1)
            {
                strSqlStatement.append(" AND OPERATER = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
            else
            {
                strSqlStatement.append(" AND KORISNIK_ID = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
        }
    }
    else
    {
        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
    }

    if (m_iFltLinijaProdukataId != 0)
    {
        strSqlStatement.append(" AND KLASA ='");
        strSqlStatement.append(cttl::itos(m_iFltLinijaProdukataId));
        strSqlStatement.append("' ");
    }

    if(m_iTipDodatnogFiltra == 1)
    {
        strSqlStatement.append(" AND FORMATIRANI_NAZIV LIKE '");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");

    }
    else if(m_iTipDodatnogFiltra == 2)
    {
        strSqlStatement.append(" AND ADRESA LIKE '%");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");
    }

    strSqlStatement.append(" AND ROWNUM < ");
    strSqlStatement.append(cttl::itos(m_iNoDef));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        while(rs->next())
        {
            QTreeWidgetItem *itemSporazum = new QTreeWidgetItem();
            itemSporazum->setText(0, QString::fromStdString(rs->getString(3)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(6)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(4)) +
                                     tr(" ,  ") +
                                     QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(1, QString::number(rs->getInt(1)));
            itemSporazum->setText(2, QString::number(rs->getUInt(2)));
            itemSporazum->setText(3, QString::fromStdString(rs->getString(3)));
            itemSporazum->setText(4, QString::fromStdString(rs->getString(4)));
            itemSporazum->setText(5, QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(6, QString::fromStdString(rs->getString(6)));
            itemSporazum->setText(7, QString::number(rs->getUInt(7)));
            itemSporazum->setText(8, QString::number(rs->getUInt(8)));
            listSporazumi.append(itemSporazum);
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

    ui->btnSporazumiUkupno->setText(tr("UK ...") + QString::number(listSporazumi.count()));
    ui->btnSporazumiRange->setText(tr("1 ...") + QString::number(listSporazumi.count()));

    if(!listSporazumi.empty())
    {
        listSporazumi.first()->setSelected(true);
        ui->treeSporazumi->insertTopLevelItems(0, listSporazumi);
        ui->treeSporazumi->expandAll();
//        ui->treeSporazumi->collapseAll();
//        ui->treeSporazumi->expandItem(listSporazumi.first());
//        ui->treeSporazumi->setCurrentItem(listSporazumi.first());
    }
}
void FrmPregledN::popunaUgovoraL2()
{
    ui->treeSporazumi->clear();

    QList<QTreeWidgetItem *> listSporazumi;

    string strSqlStatement;

    strSqlStatement.append("SELECT /*+ TAB_SP_IDX_1 */ ");
    strSqlStatement.append(" ROWNUM, SPORAZUM_ID, TO_CHAR(DATUM_OD, 'DD.MM.YYYY') DATUM, FORMATIRANI_NAZIV, ADRESA, BROJ_DOK, KUPAC_ID, STRANKA_ID ");
    strSqlStatement.append(" FROM TAB_PREGLED_SPORAZUMI WHERE ");
    strSqlStatement.append(" DATUM_OD BETWEEN TO_DATE('");
    strSqlStatement.append(ui->dateOd->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TO_DATE('");
    strSqlStatement.append(ui->dateDo->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TSPORAZUMA_ID IN (3) ");
    strSqlStatement.append(" AND KLJUCNI_IND = ");
    strSqlStatement.append(cttl::itos(m_iTipKupca));
    strSqlStatement.append(" AND STATUS_ID != 0 ");

    if (m_iTipKanala == 1)
    {

        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
        if(g_FILTER_KANAL_ID != 0)
        {
           strSqlStatement.append(" AND KANAL_ID = ");
           strSqlStatement.append(cttl::itos(g_FILTER_KANAL_ID));
        }
        else
        {
           strSqlStatement.append(" AND KANAL_ID != 0 ");
        }

//        if (g_FILTER_ORGJED_ID > 0)
//        {
//            strSqlStatement.append(" AND ORGJED_ID = ");
//            strSqlStatement.append(cttl::itos(g_FILTER_ORGJED_ID));
//        }

        if (g_FILTER_KORISNIK_ID != "0")
        {
            if(m_iTipKorisnika == 1)
            {
                strSqlStatement.append(" AND OPERATER = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
            else
            {
                strSqlStatement.append(" AND KORISNIK_ID = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
        }
    }
    else
    {
        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
    }

    if (m_iFltLinijaProdukataId != 0)
    {
        strSqlStatement.append(" AND KLASA ='");
        strSqlStatement.append(cttl::itos(m_iFltLinijaProdukataId));
        strSqlStatement.append("' ");
    }

    strSqlStatement.append(" AND SPORAZUM_ID IN (");
    strSqlStatement.append("SELECT /*+ index(PP_5) */ ID2 FROM POSLOVNI_PROCESI WHERE STANJE_ID IN (");
    strSqlStatement.append(m_strListaValue);
    strSqlStatement.append("))");

    if(m_iTipDodatnogFiltra == 1)
    {
        strSqlStatement.append(" AND FORMATIRANI_NAZIV LIKE '");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");

    }
    else if(m_iTipDodatnogFiltra == 2)
    {
        strSqlStatement.append(" AND ADRESA LIKE '%");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");
    }

    strSqlStatement.append(" AND ROWNUM < ");
    strSqlStatement.append(cttl::itos(m_iNoDef));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        while(rs->next())
        {
            QTreeWidgetItem *itemSporazum = new QTreeWidgetItem();
            itemSporazum->setText(0, QString::fromStdString(rs->getString(3)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(6)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(4)) +
                                     tr(" ,  ") +
                                     QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(1, QString::number(rs->getInt(1)));
            itemSporazum->setText(2, QString::number(rs->getUInt(2)));
            itemSporazum->setText(3, QString::fromStdString(rs->getString(3)));
            itemSporazum->setText(4, QString::fromStdString(rs->getString(4)));
            itemSporazum->setText(5, QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(6, QString::fromStdString(rs->getString(6)));
            itemSporazum->setText(7, QString::number(rs->getUInt(7)));
            itemSporazum->setText(8, QString::number(rs->getUInt(8)));
            listSporazumi.append(itemSporazum);
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

    ui->btnSporazumiUkupno->setText(tr("UK ...") + QString::number(listSporazumi.count()));
    ui->btnSporazumiRange->setText(tr("1 ...") + QString::number(listSporazumi.count()));

    if(!listSporazumi.empty())
    {
        listSporazumi.first()->setSelected(true);
        ui->treeSporazumi->insertTopLevelItems(0, listSporazumi);
        ui->treeSporazumi->expandAll();
//        ui->treeSporazumi->collapseAll();
//        ui->treeSporazumi->expandItem(listSporazumi.first());
//        ui->treeSporazumi->setCurrentItem(listSporazumi.first());
    }
}
void FrmPregledN::popunaObavijestL1()
{
    ui->treeSporazumi->clear();

    QList<QTreeWidgetItem *> listSporazumi;

    string strSqlStatement;

    strSqlStatement.append("SELECT /*+ RULE */ ");
    strSqlStatement.append(" ROWNUM, SPORAZUM_ID, TO_CHAR(DATUM_OD, 'DD.MM.YYYY') DATUM, FORMATIRANI_NAZIV, ADRESA, BROJ_DOK, KUPAC_ID, STRANKA_ID ");
    strSqlStatement.append(" FROM TAB_SLANJE_OBAVIJESTI WHERE ");
    strSqlStatement.append(" DATUM_STANJA BETWEEN TO_DATE('");
    strSqlStatement.append(ui->dateOd->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND TO_DATE('");
    strSqlStatement.append(ui->dateDo->date().toString("dd.MM.yyyy").toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') ");
    strSqlStatement.append(" AND VSPORAZUMA_ID != 0 ");
    strSqlStatement.append(" AND KLJUCNI_IND = ");
    strSqlStatement.append(cttl::itos(m_iTipKupca));

    if (m_strListaValue == "0")
    {
        strSqlStatement.append(" AND STANJE_ID != 0 ");
    }
    else
    {
        strSqlStatement.append(" AND STANJE_ID IN (");
        strSqlStatement.append(m_strListaValue);
        strSqlStatement.append(")");
    }

    switch (m_iListaSel) {
        case 15:
            {
                strSqlStatement.append(" AND NVL(KTKU_RN, 4) > -1 AND NVL(KTKU_RN, 4) NOT IN (1, 3) ");
                strSqlStatement.append(" AND TRAJNO_IND = 'N' ");
                break;
            }
        case 16:
            {
                strSqlStatement.append("  AND TSPORAZUMA_ID IN (1, 4) ");
                break;
            }
        case 17:
            {
                strSqlStatement.append(" AND TSPORAZUMA_ID IN (3, 3) ");
                break;
            }
        case 18:
            {
                strSqlStatement.append(" AND KTKU_RN IN (5, 6) AND TRAJNO_IND= 'Y' ");
                break;
            }
        case 20:
            {
                strSqlStatement.append(" AND NVL(KTKU_RN, 4) > -1 AND NVL(KTKU_RN, 4) IN (1, 3) ");
                strSqlStatement.append(" AND TRAJNO_IND = 'N' ");
                break;
            }
        case 41:
            {
                strSqlStatement.append(" AND KTKU_RN = 25 ");
                break;
            }
        default:
            break;
    }

    if (m_iTipKanala == 1)
    {

        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
        if(g_FILTER_KANAL_ID != 0)
        {
           strSqlStatement.append(" AND KANAL_ID = ");
           strSqlStatement.append(cttl::itos(g_FILTER_KANAL_ID));
        }
        else
        {
           strSqlStatement.append(" AND KANAL_ID != 0 ");
        }

//        if (g_FILTER_ORGJED_ID > 0)
//        {
//            strSqlStatement.append(" AND ORGJED_ID = ");
//            strSqlStatement.append(cttl::itos(g_FILTER_ORGJED_ID));
//        }

        if (g_FILTER_KORISNIK_ID != "0")
        {
            if(m_iTipKorisnika == 1)
            {
                strSqlStatement.append(" AND OPERATER = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
            else
            {
                strSqlStatement.append(" AND KORISNIK_ID = '");
                strSqlStatement.append(g_FILTER_KORISNIK_ID);
                strSqlStatement.append("' ");
            }
        }
    }
    else
    {
        if(g_FILTER_REGIJA_ID != 0)
        {
            strSqlStatement.append(" AND REGIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND REGIJA_ID IN (145839, 145840, 145841, 145842) ");
        }
        if(g_FILTER_ZUPANIJA_ID != 0)
        {
            strSqlStatement.append(" AND ZUPANIJA_ID = ");
            strSqlStatement.append(cttl::itos(g_FILTER_REGIJA_ID));
        }
        else
        {
            strSqlStatement.append(" AND ZUPANIJA_ID !=0 ");
        }
    }

    if (m_iFltLinijaProdukataId != 0)
    {
        strSqlStatement.append(" AND KLASA ='");
        strSqlStatement.append(cttl::itos(m_iFltLinijaProdukataId));
        strSqlStatement.append("' ");
    }

    if(m_iTipDodatnogFiltra == 1)
    {
        strSqlStatement.append(" AND FORMATIRANI_NAZIV LIKE '");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");

    }
    else if(m_iTipDodatnogFiltra == 2)
    {
        strSqlStatement.append(" AND ADRESA LIKE '%");
        strSqlStatement.append(ui->txtSearchParam->text().toStdString());
        strSqlStatement.append("%' ");
    }

    strSqlStatement.append(" AND ROWNUM < ");
    strSqlStatement.append(cttl::itos(m_iNoDef));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        while(rs->next())
        {
            QTreeWidgetItem *itemSporazum = new QTreeWidgetItem();
            itemSporazum->setText(0, QString::fromStdString(rs->getString(3)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(6)) +
                                     tr(" ... ") +
                                     QString::fromStdString(rs->getString(4)) +
                                     tr(" ,  ") +
                                     QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(1, QString::number(rs->getInt(1)));
            itemSporazum->setText(2, QString::number(rs->getUInt(2)));
            itemSporazum->setText(3, QString::fromStdString(rs->getString(3)));
            itemSporazum->setText(4, QString::fromStdString(rs->getString(4)));
            itemSporazum->setText(5, QString::fromStdString(rs->getString(5)));
            itemSporazum->setText(6, QString::fromStdString(rs->getString(6)));
            itemSporazum->setText(7, QString::number(rs->getUInt(7)));
            itemSporazum->setText(8, QString::number(rs->getUInt(8)));
            listSporazumi.append(itemSporazum);
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

    ui->btnSporazumiUkupno->setText(tr("UK ...") + QString::number(listSporazumi.count()));
    ui->btnSporazumiRange->setText(tr("1 ...") + QString::number(listSporazumi.count()));

    if(!listSporazumi.empty())
    {
        listSporazumi.first()->setSelected(true);
        ui->treeSporazumi->insertTopLevelItems(0, listSporazumi);
        ui->treeSporazumi->expandAll();
//        ui->treeSporazumi->collapseAll();
//        ui->treeSporazumi->expandItem(listSporazumi.first());
//        ui->treeSporazumi->setCurrentItem(listSporazumi.first());
    }
}
void FrmPregledN::popunaPregledaZahtjevaNew()
{
    if(ui->txtSearchParam->text().isEmpty() == true)
    {
        return;
    }

    if(m_iTipDodatnogFiltra < 3)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("BEGIN PUNI_PREGLED_ZAHTJEVA_NEW(:SPORAZUM_ID_PAR, :KUPAC_ID_PAR, :BROJ_DOK_PAR, :GIMOVINE_ID_PAR, :TEL_BROJ_PAR, :TICKET_ID_PAR, :DATUM_OD_PAR, :DATUM_DO_PAR, :LISTA_IND_PAR); END;");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        switch (m_iTipDodatnogFiltra) {
        case 3:
            {
                sqlStatement->setNull(1, OCCINUMBER);
                sqlStatement->setNull(2, OCCINUMBER);
                sqlStatement->setString(3, ui->txtSearchParam->text().toStdString());
                sqlStatement->setNull(4, OCCISTRING);
                sqlStatement->setNull(5, OCCISTRING);

                break;
            }
        case 4:
            {
                break;
            }
        case 5:
            {
                break;
            }
        case 6:
            {
                break;
            }
        case 7:
            {
                break;
            }
        case 8:
            {
                break;
            }
        default:
            break;
        }
        sqlStatement->executeUpdate();
        int iBrojac = sqlStatement->getInt(7);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }


}

// [Event Handlers]
void FrmPregledN::on_btnPregledAktivnosti_clicked()
{

}

void FrmPregledN::on_btnZahtjevUnio_clicked()
{
    if(g_FILTER_KORISNIK_ID == "0")
    {
        m_iTipKorisnika = 0;
        ui->btnZahtjevUnio->setChecked(false);
        ui->btnZahtjevProdao->setChecked(false);
        QMessageBox::warning(this, tr("DONAT - Pregled Sporazuma"),
                                   tr("Izaberite KORISNIKA"),
                                   QMessageBox::Close);
        return;
    }

    m_iTipKorisnika = 1; // Operator
    ui->btnZahtjevUnio->setChecked(true);
    ui->btnZahtjevProdao->setChecked(false);
}

void FrmPregledN::on_btnZahtjevProdao_clicked()
{
    if(g_FILTER_KORISNIK_ID == "0")
    {
        m_iTipKorisnika = 0;
        ui->btnZahtjevUnio->setChecked(false);
        ui->btnZahtjevProdao->setChecked(false);
        QMessageBox::warning(this, tr("DONAT - Pregled Sporazuma"),
                                   tr("Izaberite KORISNIKA"),
                                   QMessageBox::Close);
        return;
    }

    m_iTipKorisnika = 2; // Prodao
    ui->btnZahtjevUnio->setChecked(false);
    ui->btnZahtjevProdao->setChecked(true);
}

void FrmPregledN::on_btnPromjenaKanalaProdaje_clicked()
{
    ui->treeSporazumi->clear();

    // Show Donat form for sales channel viewr
    Kontakt::FrmKanalProdaje *frmKanalProdaje = new Kontakt::FrmKanalProdaje(m_iTipKanala + 1, this);
    frmKanalProdaje->exec();
    delete frmKanalProdaje;

    if(m_iTipKanala == 1)
    {
        ui->btnKanalProdaje->setChecked(true);
        ui->btnRegija->setChecked(false);
    }
    else if(m_iTipKanala == 2)
    {
        ui->btnKanalProdaje->setChecked(false);
        ui->btnRegija->setChecked(true);
    }

    setKorisnik();

//    // Show Donat form for user sales channel change
//    Kontakt::FrmKanalProdajeKorisnik *frmKanalProdajeKorisnik = new Kontakt::FrmKanalProdajeKorisnik(this);
//    frmKanalProdajeKorisnik->exec();
//    delete frmKanalProdajeKorisnik;

//    ui->btnKorisnikKanal->setText(QString::fromStdString(g_FILTER_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_KORISNIK_NAZ));
}

void FrmPregledN::on_btnKanalProdaje_clicked()
{
    ui->treeSporazumi->clear();
    m_iTipKanala = 1;
    setKorisnik();
}

void FrmPregledN::on_btnRegija_clicked()
{
    ui->treeSporazumi->clear();
    m_iTipKanala = 2;
    setKorisnik();
}

void FrmPregledN::on_btnDonatUser_clicked()
{
    ui->treeSporazumi->clear();

    // Show Donat form for user sales channel change
    Kontakt::FrmKanalProdajeKorisnik *frmKanalProdajeKorisnik = new Kontakt::FrmKanalProdajeKorisnik(this);
    frmKanalProdajeKorisnik->exec();
    delete frmKanalProdajeKorisnik;

//    ui->btnKorisnikKanal->setText(QString::fromStdString(g_FILTER_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_FILTER_KORISNIK_NAZ));

    setKorisnik();
}

void FrmPregledN::on_btnZahtjev_clicked()
{
    m_iListaGrupa = 1;
    popunaListaGrupa();
}

void FrmPregledN::on_btnUgovor_clicked()
{
    m_iListaGrupa = 2;
    popunaListaGrupa();
}

void FrmPregledN::on_btnObavijest_clicked()
{
    m_iListaGrupa = 3;
    popunaListaGrupa();
}

void FrmPregledN::on_btnSme_clicked()
{
    m_iListaGrupa = 4;
    popunaListaGrupa();
}

void FrmPregledN::on_btnPretragaPrivatni_clicked()
{
    m_iTipKupca = 0;
    m_iTipDodatnogFiltra = 0;
    pokreniPretrazivanje();
}

void FrmPregledN::on_btnPretragaKljucni_clicked()
{
    m_iTipKupca = 1;
    m_iTipDodatnogFiltra = 0;
    pokreniPretrazivanje();
}

void FrmPregledN::on_btnPretragatSme_clicked()
{
    m_iTipKupca = 2;
    m_iTipDodatnogFiltra = 0;
    pokreniPretrazivanje();
}

void FrmPregledN::on_btnPretragaVeleprodaja_clicked()
{
    m_iTipKupca = 3;
    m_iTipDodatnogFiltra = 0;
    pokreniPretrazivanje();
}

void FrmPregledN::on_treeListeGrupa_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    if(item->childCount() > 0)
    {
        //ui->treeListeGrupa->expandAll();
        ui->treeListeGrupa->collapseAll();
        ui->treeListeGrupa->expandItem(item);
    }
    else
    {
        m_iListaTipId = item->text(4).toInt();
        m_strListaValue = item->text(5).toStdString();
        m_iListaSub = item->text(7).toInt();
        m_iListaSel = item->text(8).toInt();
        m_iTipDodatnogFiltra = 0;
        pokreniPretrazivanje();
    }
}

void FrmPregledN::on_cboPretragaKlase_currentIndexChanged(int index)
{
    if(index == 0)
    {
        m_iFltLinijaProdukataId = 0;
        return;
    }
    m_iFltLinijaProdukataId = ui->cboPretragaKlase->itemData(index).toInt();
}

void FrmPregledN::on_btnFilterFormatiraniNaziv_clicked()
{
    ui->lblFilterTtile->setText(tr("FILTER - NAZIV"));
    ui->txtSearchParam->setFocus();
    m_iTipDodatnogFiltra = 1;
}

void FrmPregledN::on_btnFilterAdresa_clicked()
{
    ui->lblFilterTtile->setText(tr("FILTER - ADRESA"));
    ui->txtSearchParam->setFocus();
    m_iTipDodatnogFiltra = 2;
}

void FrmPregledN::on_btnFiletrBrojDokumenta_clicked()
{
    ui->lblFilterTtile->setText(tr("FILTER - BROJ DOK"));
    ui->txtSearchParam->setFocus();
    m_iTipDodatnogFiltra = 3;
}

void FrmPregledN::on_btnFilterBrojTelefona_clicked()
{
    ui->lblFilterTtile->setText(tr("FILTER - TELEFON"));
    ui->txtSearchParam->setFocus();
    m_iTipDodatnogFiltra = 4;
}

void FrmPregledN::on_btnFilterAsset_clicked()
{
    ui->lblFilterTtile->setText(tr("FILTER - ASSET"));
    ui->txtSearchParam->setFocus();
    m_iTipDodatnogFiltra = 5;

}

void FrmPregledN::on_btnFilterBrojSporazuma_clicked()
{
    ui->lblFilterTtile->setText(tr("FILTER - SPORAZUM"));
    ui->txtSearchParam->setFocus();
    m_iTipDodatnogFiltra = 6;

}

void FrmPregledN::on_btnFilterTicket_clicked()
{
    ui->lblFilterTtile->setText(tr("FILTER - TICKET"));
    ui->txtSearchParam->setFocus();
    m_iTipDodatnogFiltra = 7;

}

void FrmPregledN::on_btnFilterKupacId_clicked()
{
    ui->lblFilterTtile->setText(tr("FILTER - KUPAC"));
    ui->txtSearchParam->setFocus();
    m_iTipDodatnogFiltra = 8;

}

void FrmPregledN::on_btnTrazi_clicked()
{
    if(m_iTipDodatnogFiltra == 1 || m_iTipDodatnogFiltra == 2)
    {
        pokreniPretrazivanje();
    }
    else if(m_iTipDodatnogFiltra > 2)
    {
        popunaPregledaZahtjevaNew();
    }
}


} // namespace sporazumi










