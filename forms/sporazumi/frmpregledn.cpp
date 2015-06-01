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

#include "forms/sporazumi/frmdonatpregled.h"
#include "forms/sporazumi/frmpregledsporazuma.h"
#include "forms/sporazumi/frmpregledprocesa.h"
#include "forms/sporazumi/frmwwmspregled.h"

#include "forms/kontakt/frmkontaktdokumenti.h"
#include "forms/kontakt/frmkontaktdokumenti1.h"


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

    ui->treeSporazumLista->setColumnWidth(0, 200);
    ui->treeSporazumLista->setColumnWidth(1, 18);
    ui->treeSporazumLista->setColumnWidth(2, 18);
    ui->treeSporazumLista->hideColumn(3);
    ui->treeSporazumLista->hideColumn(4);
    ui->treeSporazumLista->hideColumn(5);
    ui->treeSporazumLista->hideColumn(6);
    ui->treeSporazumLista->hideColumn(7);
    ui->treeSporazumLista->hideColumn(8);
    ui->treeSporazumLista->hideColumn(9);
    ui->treeSporazumLista->hideColumn(10);
    ui->treeSporazumLista->hideColumn(11);
    ui->treeSporazumLista->hideColumn(12);
    ui->treeSporazumLista->hideColumn(13);
    ui->treeSporazumLista->hideColumn(14);
    ui->treeSporazumLista->hideColumn(15);
    ui->treeSporazumLista->hideColumn(16);
    ui->treeSporazumLista->hideColumn(17);
    ui->treeSporazumLista->hideColumn(18);
    ui->treeSporazumLista->hideColumn(19);
    ui->treeSporazumLista->hideColumn(20);
    ui->treeSporazumLista->hideColumn(21);
    ui->treeSporazumLista->hideColumn(22);
    ui->treeSporazumLista->hideColumn(23);

    ui->treeAktivnosti->setColumnWidth(0, 200);
    ui->treeAktivnosti->hideColumn(1);
    ui->treeAktivnosti->hideColumn(2);
    ui->treeAktivnosti->hideColumn(3);
    ui->treeAktivnosti->hideColumn(4);
    ui->treeAktivnosti->hideColumn(5);
    ui->treeAktivnosti->hideColumn(6);
    ui->treeAktivnosti->hideColumn(7);
    ui->treeAktivnosti->hideColumn(8);
    ui->treeAktivnosti->hideColumn(9);
    ui->treeAktivnosti->hideColumn(10);
    ui->treeAktivnosti->hideColumn(11);
    ui->treeAktivnosti->hideColumn(12);
    ui->treeAktivnosti->hideColumn(13);
    ui->treeAktivnosti->hideColumn(14);
    ui->treeAktivnosti->hideColumn(15);
    ui->treeAktivnosti->hideColumn(16);

    ui->treeStavke->setColumnWidth(0, 300);
    ui->treeStavke->hideColumn(1);
    ui->treeStavke->hideColumn(2);
    ui->treeStavke->hideColumn(3);
    ui->treeStavke->hideColumn(4);
    ui->treeStavke->hideColumn(5);
    ui->treeStavke->hideColumn(6);

    m_iconZuti.addFile(QString::fromUtf8(":/InDonat/Forms/images/zuti.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconZeleni.addFile(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconCrveni.addFile(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconUkljucenje.addFile(QString::fromUtf8(":/InDonat/Forms/images/UG_TEL.GIF"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconPromjena.addFile(QString::fromUtf8(":/InDonat/Forms/images/POP_TEL.GIF"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconIskljucenje.addFile(QString::fromUtf8(":/InDonat/Forms/images/ISK_U.GIF"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);

    m_iconTransparent.addFile(QString::fromUtf8(":/InDonat/Forms/images/transparet_10x10.png"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);

    m_iNoDef = 1001;

    m_iSporazumId = 0;
    m_iListaGrupa = 1;
    m_iTipKorisnika = 1;
    m_iTipKanala = 1;
    m_iTipKupca = 0;
    m_iTipFiltra = 0;
    m_iTipDodatnogFiltra = 0;
    m_iPregledAktivnosti = 0;

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
//    m_iSporazumId = 0;
//    m_iStrankaId = 0;
//    m_iKupacId = 0;

    ui->treeSporazumLista->clear();
    ui->treeAktivnosti->clear();
    ui->treeStavke->clear();

    ui->lblKupacId->clear();
    ui->lblKupacNaziv->clear();

    initSlog();

}
void FrmPregledN::initSlog()
{
    m_iSporazumSlogId = 0;
    m_iGrupaImovineId = 0;
    m_iPoslovniProcesId = 0;
    m_strBrojDokumenta = "";
    m_dateDatumzahtjeva = QDateTime();

    ui->lblTicket->clear();
    ui->lblTelBroj->clear();
    ui->lblGrupaImovineId->clear();
    ui->lblSporazumCreateTitle->clear();
    ui->lblPoslovniProcesId->clear();
    ui->lblSporazumDatumzadnjeIzmjene->clear();
    ui->lblGrupaImovineStatus->clear();
    ui->lblGrupaImovineAktivnost->clear();
    ui->lblOpis->clear();
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

    Date datumOd = Date(g_DonatEnv,
                          ui->dateOd->date().year(),
                          ui->dateOd->date().month(),
                          ui->dateOd->date().day(),
                          ui->dateOd->time().hour(),
                          ui->dateOd->time().minute(),
                          ui->dateOd->time().second());

    Date datumDo = Date(g_DonatEnv,
                          ui->dateDo->date().year(),
                          ui->dateDo->date().month(),
                          ui->dateDo->date().day(),
                          ui->dateDo->time().hour(),
                          ui->dateDo->time().minute(),
                          ui->dateDo->time().second());

    unsigned int iFilterId = ui->txtSearchParam->text().toUInt();

    ui->treeSporazumi->clear();

    QList<QTreeWidgetItem *> listSporazumi;

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
                sqlStatement->setUInt(1, 0); // Sporazum Id
                sqlStatement->setUInt(2, 0); // Kupac Id
                sqlStatement->setString(3, ui->txtSearchParam->text().toStdString()); // Broj_Dokumenta
                sqlStatement->setUInt(4, 0); // GrupaIMovineId
                sqlStatement->setNull(5, OCCISTRING); // Tel Broj
                sqlStatement->setNull(6, OCCISTRING); // Ticket
                sqlStatement->setDate(7, datumOd); // Datum Od
                sqlStatement->setDate(8, datumDo); // Datum Do
                sqlStatement->setInt(9, 1); // Lista Ind Id

//                sqlStatement->setNull(1, OCCINUMBER); // Sporazum_Id
//                sqlStatement->setNull(2, OCCINUMBER); // Kupac_Id
//                sqlStatement->setNull(3, OCCISTRING); // Broj_Dokumenta
//                sqlStatement->setNull(4, OCCINUMBER); // GrupaIMovineId
//                sqlStatement->setNull(5, OCCISTRING); // Tel Broj
//                sqlStatement->setNull(6, OCCISTRING); // Ticket
//                sqlStatement->setNull(7, OCCIDATE); // Datum Od
//                sqlStatement->setNull(8, OCCIDATE); // Datum Do
//                sqlStatement->setNull(9, OCCINUMBER); // Lista Ind Id
                break;
            }
        case 4:
            {
                sqlStatement->setUInt(1, 0); // Sporazum Id
                sqlStatement->setUInt(2, 0); // Kupac Id
                sqlStatement->setNull(3, OCCISTRING); // Broj_Dokumenta
                sqlStatement->setUInt(4, 0); // GrupaIMovineId
                sqlStatement->setString(5, ui->txtSearchParam->text().toStdString()); // Tel Broj
                sqlStatement->setNull(6, OCCISTRING); // Ticket
                sqlStatement->setDate(7, datumOd); // Datum Od
                sqlStatement->setDate(8, datumDo); // Datum Do
                sqlStatement->setInt(9, 1); // Lista Ind Id
                break;
            }
        case 5:
            {
                sqlStatement->setUInt(1, 0); // Sporazum Id
                sqlStatement->setUInt(2, 0); // Kupac Id
                sqlStatement->setNull(3, OCCISTRING); // Broj_Dokumenta
                sqlStatement->setUInt(4, iFilterId); // GrupaIMovineId
                sqlStatement->setNull(5, OCCISTRING); // Tel Broj
                sqlStatement->setNull(6, OCCISTRING); // Ticket
                sqlStatement->setDate(7, datumOd); // Datum Od
                sqlStatement->setDate(8, datumDo); // Datum Do
                sqlStatement->setInt(9, 1); // Lista Ind Id
                break;
            }
        case 6:
            {
                sqlStatement->setUInt(1, iFilterId); // Sporazum Id
                sqlStatement->setUInt(2, 0); // Kupac Id
                sqlStatement->setNull(3, OCCISTRING); // Broj_Dokumenta
                sqlStatement->setUInt(4, 0); // GrupaIMovineId
                sqlStatement->setNull(5, OCCISTRING); // Tel Broj
                sqlStatement->setNull(6, OCCISTRING); // Ticket
                sqlStatement->setDate(7, datumOd); // Datum Od
                sqlStatement->setDate(8, datumDo); // Datum Do
                sqlStatement->setInt(9, 1); // Lista Ind Id
                break;
            }
        case 7:
            {
                sqlStatement->setUInt(1, 0); // Sporazum Id
                sqlStatement->setUInt(2, 0); // Kupac Id
                sqlStatement->setNull(3, OCCISTRING); // Broj_Dokumenta
                sqlStatement->setUInt(4, 0); // GrupaIMovineId
                sqlStatement->setNull(5, OCCISTRING); // Tel Broj
                sqlStatement->setString(6, ui->txtSearchParam->text().toStdString()); // Ticket
                sqlStatement->setDate(7, datumOd); // Datum Od
                sqlStatement->setDate(8, datumDo); // Datum Do
                sqlStatement->setInt(9, 1); // Lista Ind Id
                break;
            }
        case 8:
            {
                sqlStatement->setUInt(1, 0); // Sporazum Id
                sqlStatement->setUInt(2, iFilterId); // Kupac Id
                sqlStatement->setNull(3, OCCISTRING); // Broj_Dokumenta
                sqlStatement->setUInt(4, 0); // GrupaIMovineId
                sqlStatement->setNull(5, OCCISTRING); // Tel Broj
                sqlStatement->setNull(6, OCCISTRING); // Ticket
                sqlStatement->setDate(7, datumOd); // Datum Od
                sqlStatement->setDate(8, datumDo); // Datum Do
                sqlStatement->setInt(9, 1); // Lista Ind Id
                break;
            }
        default:
            break;
        }
        sqlStatement->executeUpdate();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT ROWNUM, SPORAZUM_ID, TO_CHAR(DATUM_OD,'DD.MM.YYYY') DATUM, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA ADRESA, BROJ_DOK, 0 KUPAC_ID, 0 SPORAZUM_ID ");
    strSqlStatement.append("FROM TEMP_PREGLED_ZAHTJEVA_LISTA ");
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
void FrmPregledN::popunaKupca()
{
    if(m_iKupacId == 0)
    {
        return;
    }

    string strSqlStatement;

    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA FROM HIJERARHIJA_STR_ADRESE3 WHERE ULSTRANKE_ID =  ");
    strSqlStatement.append(cttl::itos(m_iKupacId));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        if(rs->next())
        {
            ui->lblKupacId->setText(QString::number(m_iKupacId));
            ui->lblKupacNaziv->setText(QString::fromStdString(rs->getString(2)));
            string strStrankaId;
            strStrankaId = rs->getString(1);
            if(cttl::str2int(m_iStrankaId, strStrankaId) == false)
            {
                m_iStrankaId = 0;
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
}
void FrmPregledN::popuniSporazumListu()
{
    ui->treeSporazumLista->clear();
    ui->treeAktivnosti->clear();

    Date datumOd = Date(g_DonatEnv,
                          ui->dateOd->date().year(),
                          ui->dateOd->date().month(),
                          ui->dateOd->date().day(),
                          ui->dateOd->time().hour(),
                          ui->dateOd->time().minute(),
                          ui->dateOd->time().second());

    Date datumDo = Date(g_DonatEnv,
                          ui->dateDo->date().year(),
                          ui->dateDo->date().month(),
                          ui->dateDo->date().day(),
                          ui->dateDo->time().hour(),
                          ui->dateDo->time().minute(),
                          ui->dateDo->time().second());


    QList<QTreeWidgetItem *> listSporazumLista;
    QList<QTreeWidgetItem *> listSporazumAktivnosti;

    // [2. Popuna sadrzaja sporazuma]
    string strSqlStatement;
    strSqlStatement.append("BEGIN PUNI_PREGLED_ZAHTJEVA_NEW(:SPORAZUM_ID_PAR, :KUPAC_ID_PAR, :BROJ_DOK_PAR, :GIMOVINE_ID_PAR, :TEL_BROJ_PAR, :TICKET_ID_PAR, :DATUM_OD_PAR, :DATUM_DO_PAR, :LISTA_IND_PAR); END;");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setUInt(1, m_iSporazumId); // Sporazum Id
        sqlStatement->setUInt(2, 0); // Kupac Id
        sqlStatement->setNull(3, OCCISTRING); // Broj_Dokumenta
        sqlStatement->setUInt(4, 0); // GrupaIMovineId
        sqlStatement->setNull(5, OCCISTRING); // Tel Broj
        sqlStatement->setNull(6, OCCISTRING); // Ticket
        sqlStatement->setDate(7, datumOd); // Datum Od
        sqlStatement->setDate(8, datumDo); // Datum Do
        sqlStatement->setInt(9, 1); // Lista Ind Id
        sqlStatement->executeUpdate();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT SPORAZUM_ID, BROJ_DOK, KUPAC_ID, GIMOVINE_ID, TEL_BROJ, KLASA, STATUS_PROVISIONING, ");
    strSqlStatement.append(" STATUS_UGOVARANJE, STATUS_BILLING, ORDER_ID, NVL(TICKET_ID, 0) TICKET_ID, TO_CHAR(DATUM_ZAHTJEVA, 'DD.MM.YYYY HH24:MI') DATUM_ZAHTJEVA, ");
    strSqlStatement.append(" TO_CHAR(DATUM_ZADNJE_PROMJENE, 'DD.MM.YYYY HH24:MI') DATUM_ZADNJE_PROMJENE, OPERATER, PRODAVAC, KANAL, NAPOMENA_PROVISIONING, NVL(AKTIVNOST, 200) AKTIVNOST, ");
    strSqlStatement.append(" NVL(ZAVRSENOST, 200) ZAVRSENOST, ID, STATUS_KOMUNIKACIJA_KORISNIKU ");
    strSqlStatement.append(" FROM TEMP_PREGLED_ZAHTJEVA ORDER BY SPORAZUM_ID, ID ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        QString strNaziv1 = QString();
        QString strNaziv2 = QString();
        unsigned int iSporazumId = 0;

        while(rs->next())
        {
            strNaziv1 = QString::fromStdString(rs->getString(12)) +
                        tr(" ... ") +
                        QString::fromStdString(rs->getString(2));
            strNaziv2 = QString::fromStdString(rs->getString(5)) +
                        tr("  ") +
                        QString::fromStdString(rs->getString(6));
            iSporazumId = rs->getUInt(1);

            if(listSporazumLista.count() == 0)
            {
                QTreeWidgetItem *itemSporazum = new QTreeWidgetItem();
                itemSporazum->setText(0, strNaziv1);
                itemSporazum->setIcon(1, m_iconTransparent);
                itemSporazum->setIcon(2, m_iconTransparent);
                itemSporazum->setText(3, QString::number(rs->getUInt(1)));
                itemSporazum->setText(4, QString::fromStdString(rs->getString(2)));
                itemSporazum->setText(5, QString::number(rs->getUInt(3)));
                itemSporazum->setText(6, QString::number(rs->getUInt(4)));
                itemSporazum->setText(7, QString::fromStdString(rs->getString(5)));
                itemSporazum->setText(8, QString::fromStdString(rs->getString(6)));
                itemSporazum->setText(9, QString::fromStdString(rs->getString(7)));
                itemSporazum->setText(10, QString::fromStdString(rs->getString(8)));
                itemSporazum->setText(11, QString::fromStdString(rs->getString(9)));
                itemSporazum->setText(12, QString::number(rs->getUInt(10)));
                itemSporazum->setText(13, QString::number(rs->getUInt(11)));
                itemSporazum->setText(14, QString::fromStdString(rs->getString(12)));
                itemSporazum->setText(15, QString::fromStdString(rs->getString(13)));
                itemSporazum->setText(16, QString::fromStdString(rs->getString(14)));
                itemSporazum->setText(17, QString::fromStdString(rs->getString(15)));
                itemSporazum->setText(18, QString::fromStdString(rs->getString(16)));
                itemSporazum->setText(19, QString::fromStdString(rs->getString(17)));
                itemSporazum->setText(20, QString::number(rs->getInt(18)));
                itemSporazum->setText(21, QString::number(rs->getInt(19)));
                itemSporazum->setText(22, QString::number(rs->getUInt(20)));
                itemSporazum->setText(23, QString::fromStdString(rs->getString(21)));
                listSporazumLista.append(itemSporazum);

                QTreeWidgetItem *itemSporazumstavka = new QTreeWidgetItem();
                itemSporazumstavka->setText(0, strNaziv2);
                if(rs->isNull(19) == false)
                {
                    switch (rs->getInt(19))
                    {
                        case 0:
                        {
                            itemSporazumstavka->setIcon(1, m_iconZuti);
                            break;
                        }
                        case 1:
                        {
                            itemSporazumstavka->setIcon(1, m_iconZeleni);
                            break;
                        }
                        case 2:
                        {
                            itemSporazumstavka->setIcon(1, m_iconCrveni);
                            break;
                        }
                        default:
                        {
                            itemSporazumstavka->setIcon(1, m_iconTransparent);
                            break;
                        }
                    }
                }
                if(rs->isNull(18) == false)
                {
                    switch (rs->getInt(18))
                    {
                        case 0:
                        {
                            itemSporazumstavka->setIcon(2, m_iconPromjena);
                            break;
                        }
                        case 1:
                        {
                            itemSporazumstavka->setIcon(2, m_iconUkljucenje);
                            break;
                        }
                        case 2:
                        {
                            itemSporazumstavka->setIcon(2, m_iconIskljucenje);
                            break;
                        }
                        default:
                        {
                            itemSporazumstavka->setIcon(1, m_iconTransparent);
                            break;
                        }
                    }
                }
                itemSporazumstavka->setText(3, QString::number(rs->getUInt(1)));
                itemSporazumstavka->setText(4, QString::fromStdString(rs->getString(2)));
                itemSporazumstavka->setText(5, QString::number(rs->getUInt(3)));
                itemSporazumstavka->setText(6, QString::number(rs->getUInt(4)));
                itemSporazumstavka->setText(7, QString::fromStdString(rs->getString(5)));
                itemSporazumstavka->setText(8, QString::fromStdString(rs->getString(6)));
                itemSporazumstavka->setText(9, QString::fromStdString(rs->getString(7)));
                itemSporazumstavka->setText(10, QString::fromStdString(rs->getString(8)));
                itemSporazumstavka->setText(11, QString::fromStdString(rs->getString(9)));
                itemSporazumstavka->setText(12, QString::number(rs->getUInt(10)));
                itemSporazumstavka->setText(13, QString::number(rs->getUInt(11)));
                itemSporazumstavka->setText(14, QString::fromStdString(rs->getString(12)));
                itemSporazumstavka->setText(15, QString::fromStdString(rs->getString(13)));
                itemSporazumstavka->setText(16, QString::fromStdString(rs->getString(14)));
                itemSporazumstavka->setText(17, QString::fromStdString(rs->getString(15)));
                itemSporazumstavka->setText(18, QString::fromStdString(rs->getString(16)));
                itemSporazumstavka->setText(19, QString::fromStdString(rs->getString(17)));
                itemSporazumstavka->setText(20, QString::number(rs->getInt(18)));
                itemSporazumstavka->setText(21, QString::number(rs->getInt(19)));
                itemSporazumstavka->setText(22, QString::number(rs->getUInt(20)));
                itemSporazumstavka->setText(23, QString::fromStdString(rs->getString(21)));
                listSporazumLista.append(itemSporazumstavka);
                itemSporazum->addChild(itemSporazumstavka);
            }
            else
            {
                bool bPostoji = false;
                int iListSize = listSporazumLista.size();
                for(int i = 0; i < iListSize; ++i)
                {
                    if(listSporazumLista.at(i)->text(3).toUInt() == iSporazumId && listSporazumLista.at(i)->childCount() > 0)
                    {
                        QTreeWidgetItem *itemSporazum = new QTreeWidgetItem();
                        itemSporazum->setText(0, strNaziv2);
                        if(rs->isNull(19) == false)
                        {
                            switch (rs->getInt(19))
                            {
                                case 0:
                                {
                                    itemSporazum->setIcon(1, m_iconZuti);
                                    break;
                                }
                                case 1:
                                {
                                    itemSporazum->setIcon(1, m_iconZeleni);
                                    break;
                                }
                                case 2:
                                {
                                    itemSporazum->setIcon(1, m_iconCrveni);
                                    break;
                                }
                                default:
                                {
                                    itemSporazum->setIcon(1, m_iconTransparent);
                                    break;
                                }
                            }
                        }
                        if(rs->isNull(18) == false)
                        {
                            switch (rs->getInt(18))
                            {
                                case 0:
                                {
                                    itemSporazum->setIcon(2, m_iconPromjena);
                                    break;
                                }
                                case 1:
                                {
                                    itemSporazum->setIcon(2, m_iconUkljucenje);
                                    break;
                                }
                                case 2:
                                {
                                    itemSporazum->setIcon(2, m_iconIskljucenje);
                                    break;
                                }
                                default:
                                {
                                    itemSporazum->setIcon(1, m_iconTransparent);
                                    break;
                                }
                            }
                        }
                        itemSporazum->setText(3, QString::number(rs->getUInt(1)));
                        itemSporazum->setText(4, QString::fromStdString(rs->getString(2)));
                        itemSporazum->setText(5, QString::number(rs->getUInt(3)));
                        itemSporazum->setText(6, QString::number(rs->getUInt(4)));
                        itemSporazum->setText(7, QString::fromStdString(rs->getString(5)));
                        itemSporazum->setText(8, QString::fromStdString(rs->getString(6)));
                        itemSporazum->setText(9, QString::fromStdString(rs->getString(7)));
                        itemSporazum->setText(10, QString::fromStdString(rs->getString(8)));
                        itemSporazum->setText(11, QString::fromStdString(rs->getString(9)));
                        itemSporazum->setText(12, QString::number(rs->getUInt(10)));
                        itemSporazum->setText(13, QString::number(rs->getUInt(11)));
                        itemSporazum->setText(14, QString::fromStdString(rs->getString(12)));
                        itemSporazum->setText(15, QString::fromStdString(rs->getString(13)));
                        itemSporazum->setText(16, QString::fromStdString(rs->getString(14)));
                        itemSporazum->setText(17, QString::fromStdString(rs->getString(15)));
                        itemSporazum->setText(18, QString::fromStdString(rs->getString(16)));
                        itemSporazum->setText(19, QString::fromStdString(rs->getString(17)));
                        itemSporazum->setText(20, QString::number(rs->getInt(18)));
                        itemSporazum->setText(21, QString::number(rs->getInt(19)));
                        itemSporazum->setText(22, QString::number(rs->getUInt(20)));
                        itemSporazum->setText(23, QString::fromStdString(rs->getString(21)));
                        listSporazumLista.append(itemSporazum);
                        listSporazumLista.at(i)->addChild(itemSporazum);
                        bPostoji = true;
                    }
                }
                if(bPostoji == false)
                {
                    QTreeWidgetItem *itemSporazum = new QTreeWidgetItem();
                    itemSporazum->setText(0, strNaziv1);
                    itemSporazum->setIcon(1, m_iconTransparent);
                    itemSporazum->setIcon(2, m_iconTransparent);
                    itemSporazum->setText(3, QString::number(rs->getUInt(1)));
                    itemSporazum->setText(4, QString::fromStdString(rs->getString(2)));
                    itemSporazum->setText(5, QString::number(rs->getUInt(3)));
                    itemSporazum->setText(6, QString::number(rs->getUInt(4)));
                    itemSporazum->setText(7, QString::fromStdString(rs->getString(5)));
                    itemSporazum->setText(8, QString::fromStdString(rs->getString(6)));
                    itemSporazum->setText(9, QString::fromStdString(rs->getString(7)));
                    itemSporazum->setText(10, QString::fromStdString(rs->getString(8)));
                    itemSporazum->setText(11, QString::fromStdString(rs->getString(9)));
                    itemSporazum->setText(12, QString::number(rs->getUInt(10)));
                    itemSporazum->setText(13, QString::number(rs->getUInt(11)));
                    itemSporazum->setText(14, QString::fromStdString(rs->getString(12)));
                    itemSporazum->setText(15, QString::fromStdString(rs->getString(13)));
                    itemSporazum->setText(16, QString::fromStdString(rs->getString(14)));
                    itemSporazum->setText(17, QString::fromStdString(rs->getString(15)));
                    itemSporazum->setText(18, QString::fromStdString(rs->getString(16)));
                    itemSporazum->setText(19, QString::fromStdString(rs->getString(17)));
                    itemSporazum->setText(20, QString::number(rs->getInt(18)));
                    itemSporazum->setText(21, QString::number(rs->getInt(19)));
                    itemSporazum->setText(22, QString::number(rs->getUInt(20)));
                    itemSporazum->setText(23, QString::fromStdString(rs->getString(21)));
                    listSporazumLista.append(itemSporazum);

                    QTreeWidgetItem *itemSporazumstavka = new QTreeWidgetItem();
                    itemSporazumstavka->setText(0, strNaziv2);
                    if(rs->isNull(19) == false)
                    {
                        switch (rs->getInt(19))
                        {
                            case 0:
                            {
                                itemSporazumstavka->setIcon(1, m_iconZuti);
                                break;
                            }
                            case 1:
                            {
                                itemSporazumstavka->setIcon(1, m_iconZeleni);
                                break;
                            }
                            case 2:
                            {
                                itemSporazumstavka->setIcon(1, m_iconCrveni);
                                break;
                            }
                            default:
                            {
                                itemSporazumstavka->setIcon(1, m_iconTransparent);
                                break;
                            }
                        }
                    }
                    if(rs->isNull(18) == false)
                    {
                        switch (rs->getInt(18))
                        {
                            case 0:
                            {
                                itemSporazumstavka->setIcon(2, m_iconPromjena);
                                break;
                            }
                            case 1:
                            {
                                itemSporazumstavka->setIcon(2, m_iconUkljucenje);
                                break;
                            }
                            case 2:
                            {
                                itemSporazumstavka->setIcon(2, m_iconIskljucenje);
                                break;
                            }
                            default:
                            {
                                itemSporazumstavka->setIcon(1, m_iconTransparent);
                                break;
                            }
                        }
                    }
                    itemSporazumstavka->setText(3, QString::number(rs->getUInt(1)));
                    itemSporazumstavka->setText(4, QString::fromStdString(rs->getString(2)));
                    itemSporazumstavka->setText(5, QString::number(rs->getUInt(3)));
                    itemSporazumstavka->setText(6, QString::number(rs->getUInt(4)));
                    itemSporazumstavka->setText(7, QString::fromStdString(rs->getString(5)));
                    itemSporazumstavka->setText(8, QString::fromStdString(rs->getString(6)));
                    itemSporazumstavka->setText(9, QString::fromStdString(rs->getString(7)));
                    itemSporazumstavka->setText(10, QString::fromStdString(rs->getString(8)));
                    itemSporazumstavka->setText(11, QString::fromStdString(rs->getString(9)));
                    itemSporazumstavka->setText(12, QString::number(rs->getUInt(10)));
                    itemSporazumstavka->setText(13, QString::number(rs->getUInt(11)));
                    itemSporazumstavka->setText(14, QString::fromStdString(rs->getString(12)));
                    itemSporazumstavka->setText(15, QString::fromStdString(rs->getString(13)));
                    itemSporazumstavka->setText(16, QString::fromStdString(rs->getString(14)));
                    itemSporazumstavka->setText(17, QString::fromStdString(rs->getString(15)));
                    itemSporazumstavka->setText(18, QString::fromStdString(rs->getString(16)));
                    itemSporazumstavka->setText(19, QString::fromStdString(rs->getString(17)));
                    itemSporazumstavka->setText(20, QString::number(rs->getInt(18)));
                    itemSporazumstavka->setText(21, QString::number(rs->getInt(19)));
                    itemSporazumstavka->setText(22, QString::number(rs->getUInt(20)));
                    itemSporazumstavka->setText(23, QString::fromStdString(rs->getString(21)));
                    listSporazumLista.append(itemSporazumstavka);
                    itemSporazum->addChild(itemSporazumstavka);
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

    // [3. Popuna sporazum aktivnosti]
    strSqlStatement.clear();
    strSqlStatement.append("SELECT NVL(SPORAZUM_ID, 0) SPORAZUM_ID, GIMOVINE_ID, PROCES_ID, NVL(ID, 0) ID, NVL(NAD_ID, 0) NAD_ID, ");
    strSqlStatement.append(" NVL(NIVO, 0), GRUPA, NAZIV, NVL(STANJE_1, 0) STANJE_1, NVL(STANJE_2, 0) STANJE_2, ");
    strSqlStatement.append(" NVL(CURR_STATE, 0) CURR_STATE, NVL(NEXT_STATE, 0) NEXT_STATE, NVL(MAX_STATE, 0) MAX_STATE, ");
    strSqlStatement.append(" NVL(AKT_TIP, 0) AKT_TIP, NVL(AKT_DATUM, 0) AKT_DATUM, NVL(AKT_RAZLOG, 0) AKT_RAZLOG, NVL(GLAVNI_SRZ_ID, 0) GLAVNI_SRZ_ID ");
    strSqlStatement.append(" FROM KONTAKT_S_AKTST_TEMP ORDER BY GRUPA, ID ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        QString strGrupa = QString();

        while(rs->next())
        {
            strGrupa = QString::fromStdString(rs->getString(7));

            if(listSporazumAktivnosti.count() == 0)
            {
                QTreeWidgetItem *itemSporazumAktivnost = new QTreeWidgetItem();
                itemSporazumAktivnost->setText(0, strGrupa);
                itemSporazumAktivnost->setText(1, tr("0"));
                itemSporazumAktivnost->setText(2, tr("0"));
                itemSporazumAktivnost->setText(3, tr("0"));
                itemSporazumAktivnost->setText(4, tr("0"));
                itemSporazumAktivnost->setText(5, tr("0"));
                itemSporazumAktivnost->setText(6, tr("0"));
                itemSporazumAktivnost->setText(7, tr(""));
                itemSporazumAktivnost->setText(8, tr("0"));
                itemSporazumAktivnost->setText(9, tr("0"));
                itemSporazumAktivnost->setText(10, tr("0"));
                itemSporazumAktivnost->setText(11, tr("0"));
                itemSporazumAktivnost->setText(12, tr("0"));
                itemSporazumAktivnost->setText(13, tr("0"));
                itemSporazumAktivnost->setText(14, tr("0"));
                itemSporazumAktivnost->setText(15, tr("0"));
                itemSporazumAktivnost->setText(16, tr("0"));
                listSporazumAktivnosti.append(itemSporazumAktivnost);

                QTreeWidgetItem *itemSporazumAktivnostStavka = new QTreeWidgetItem();
                itemSporazumAktivnostStavka->setText(0, QString::fromStdString(rs->getString(8)));
                itemSporazumAktivnostStavka->setText(1, QString::number(rs->getUInt(1)));
                itemSporazumAktivnostStavka->setText(2, QString::number(rs->getUInt(2)));
                itemSporazumAktivnostStavka->setText(3, QString::number(rs->getUInt(3)));
                itemSporazumAktivnostStavka->setText(4, QString::number(rs->getInt(4)));
                itemSporazumAktivnostStavka->setText(5, QString::number(rs->getInt(5)));
                itemSporazumAktivnostStavka->setText(6, QString::number(rs->getInt(6)));
                itemSporazumAktivnostStavka->setText(7, QString::fromStdString(rs->getString(7)));
                itemSporazumAktivnostStavka->setText(8, QString::number(rs->getInt(9)));
                itemSporazumAktivnostStavka->setText(9, QString::number(rs->getInt(10)));
                itemSporazumAktivnostStavka->setText(10, QString::number(rs->getInt(11)));
                itemSporazumAktivnostStavka->setText(11, QString::number(rs->getInt(12)));
                itemSporazumAktivnostStavka->setText(12, QString::number(rs->getInt(13)));
                itemSporazumAktivnostStavka->setText(13, QString::number(rs->getInt(14)));
                itemSporazumAktivnostStavka->setText(14, QString::number(rs->getInt(15)));
                itemSporazumAktivnostStavka->setText(15, QString::number(rs->getInt(16)));
                itemSporazumAktivnostStavka->setText(16, QString::number(rs->getUInt(17)));
                listSporazumAktivnosti.append(itemSporazumAktivnostStavka);
                itemSporazumAktivnost->addChild(itemSporazumAktivnostStavka);
            }
            else
            {
                bool bPostoji = false;
                int iListSize = listSporazumAktivnosti.size();
                for(int i = 0; i < iListSize; ++i)
                {
                    if(listSporazumAktivnosti.at(i)->text(0) == strGrupa)
                    {
                        QTreeWidgetItem *itemSporazumAktivnost = new QTreeWidgetItem();
                        itemSporazumAktivnost->setText(0, QString::fromStdString(rs->getString(8)));
                        itemSporazumAktivnost->setText(1, QString::number(rs->getUInt(1)));
                        itemSporazumAktivnost->setText(2, QString::number(rs->getUInt(2)));
                        itemSporazumAktivnost->setText(3, QString::number(rs->getUInt(3)));
                        itemSporazumAktivnost->setText(4, QString::number(rs->getInt(4)));
                        itemSporazumAktivnost->setText(5, QString::number(rs->getInt(5)));
                        itemSporazumAktivnost->setText(6, QString::number(rs->getInt(6)));
                        itemSporazumAktivnost->setText(7, QString::fromStdString(rs->getString(7)));
                        itemSporazumAktivnost->setText(8, QString::number(rs->getInt(9)));
                        itemSporazumAktivnost->setText(9, QString::number(rs->getInt(10)));
                        itemSporazumAktivnost->setText(10, QString::number(rs->getInt(11)));
                        itemSporazumAktivnost->setText(11, QString::number(rs->getInt(12)));
                        itemSporazumAktivnost->setText(12, QString::number(rs->getInt(13)));
                        itemSporazumAktivnost->setText(13, QString::number(rs->getInt(14)));
                        itemSporazumAktivnost->setText(14, QString::number(rs->getInt(15)));
                        itemSporazumAktivnost->setText(15, QString::number(rs->getInt(16)));
                        itemSporazumAktivnost->setText(16, QString::number(rs->getUInt(17)));
                        listSporazumAktivnosti.append(itemSporazumAktivnost);
                        listSporazumAktivnosti.at(i)->addChild(itemSporazumAktivnost);
                        bPostoji = true;
                    }
                }
                if(bPostoji == false)
                {
                    QTreeWidgetItem *itemSporazumAktivnost = new QTreeWidgetItem();
                    itemSporazumAktivnost->setText(0, strGrupa);
                    itemSporazumAktivnost->setText(1, tr("0"));
                    itemSporazumAktivnost->setText(2, tr("0"));
                    itemSporazumAktivnost->setText(3, tr("0"));
                    itemSporazumAktivnost->setText(4, tr("0"));
                    itemSporazumAktivnost->setText(5, tr("0"));
                    itemSporazumAktivnost->setText(6, tr("0"));
                    itemSporazumAktivnost->setText(7, tr(""));
                    itemSporazumAktivnost->setText(8, tr("0"));
                    itemSporazumAktivnost->setText(9, tr("0"));
                    itemSporazumAktivnost->setText(10, tr("0"));
                    itemSporazumAktivnost->setText(11, tr("0"));
                    itemSporazumAktivnost->setText(12, tr("0"));
                    itemSporazumAktivnost->setText(13, tr("0"));
                    itemSporazumAktivnost->setText(14, tr("0"));
                    itemSporazumAktivnost->setText(15, tr("0"));
                    itemSporazumAktivnost->setText(16, tr("0"));
                    listSporazumAktivnosti.append(itemSporazumAktivnost);

                    QTreeWidgetItem *itemSporazumAktivnostStavka = new QTreeWidgetItem();
                    itemSporazumAktivnostStavka->setText(0, QString::fromStdString(rs->getString(8)));
                    itemSporazumAktivnostStavka->setText(1, QString::number(rs->getUInt(1)));
                    itemSporazumAktivnostStavka->setText(2, QString::number(rs->getUInt(2)));
                    itemSporazumAktivnostStavka->setText(3, QString::number(rs->getUInt(3)));
                    itemSporazumAktivnostStavka->setText(4, QString::number(rs->getInt(4)));
                    itemSporazumAktivnostStavka->setText(5, QString::number(rs->getInt(5)));
                    itemSporazumAktivnostStavka->setText(6, QString::number(rs->getInt(6)));
                    itemSporazumAktivnostStavka->setText(7, QString::fromStdString(rs->getString(7)));
                    itemSporazumAktivnostStavka->setText(8, QString::number(rs->getInt(9)));
                    itemSporazumAktivnostStavka->setText(9, QString::number(rs->getInt(10)));
                    itemSporazumAktivnostStavka->setText(10, QString::number(rs->getInt(11)));
                    itemSporazumAktivnostStavka->setText(11, QString::number(rs->getInt(12)));
                    itemSporazumAktivnostStavka->setText(12, QString::number(rs->getInt(13)));
                    itemSporazumAktivnostStavka->setText(13, QString::number(rs->getInt(14)));
                    itemSporazumAktivnostStavka->setText(14, QString::number(rs->getInt(15)));
                    itemSporazumAktivnostStavka->setText(15, QString::number(rs->getInt(16)));
                    itemSporazumAktivnostStavka->setText(16, QString::number(rs->getUInt(17)));
                    listSporazumAktivnosti.append(itemSporazumAktivnostStavka);
                    itemSporazumAktivnost->addChild(itemSporazumAktivnostStavka);
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

    if(!listSporazumLista.empty())
    {
        listSporazumLista.first()->setSelected(true);
        ui->treeSporazumLista->insertTopLevelItems(0, listSporazumLista);
        ui->treeSporazumLista->expandAll();
//        ui->treeSporazumi->collapseAll();
//        ui->treeSporazumi->expandItem(listSporazumLista.first());
//        ui->treeSporazumi->setCurrentItem(listSporazumLista.first());
    }

    if(!listSporazumAktivnosti.empty())
    {
        listSporazumAktivnosti.first()->setSelected(true);
        ui->treeAktivnosti->insertTopLevelItems(0, listSporazumAktivnosti);
        ui->treeAktivnosti->expandAll();
//        ui->treeAktivnosti->collapseAll();
//        ui->treeAktivnosti->expandItem(listSporazumAktivnosti.first());
//        ui->treeAktivnosti->setCurrentItem(listSporazumAktivnosti.first());
    }

    initSlog();
    ui->lblSporazumId->setText(QString::number(m_iSporazumId));
    m_iSporazumSlogId = listSporazumLista.first()->text(4).toUInt();
    popunaSporazumSlog();
    popunaSporazumStavki();
    popunaKupca();
}
void FrmPregledN::popunaSporazumSlog()
{
    if(m_iSporazumSlogId == 0)
    {
        return;
    }

    string strSqlStatement;

    strSqlStatement.append("SELECT SPORAZUM_ID, BROJ_DOK, KUPAC_ID, GIMOVINE_ID, TEL_BROJ, KLASA, STATUS_PROVISIONING, ");
    strSqlStatement.append(" STATUS_UGOVARANJE, STATUS_BILLING, ORDER_ID, TICKET_ID, TO_CHAR(DATUM_ZAHTJEVA, 'DD.MM.YYYY HH24:MI') DATUM_ZAHTJEVA, ");
    strSqlStatement.append(" TO_CHAR(DATUM_ZADNJE_PROMJENE, 'DD.MM.YYYY HH24:MI') DATUM_ZADNJE_PROMJENE, OPERATER, PRODAVAC, KANAL, NAPOMENA_PROVISIONING, NVL(AKTIVNOST, 200) AKTIVNOST, ");
    strSqlStatement.append(" NVL(ZAVRSENOST, 200) ZAVRSENOST, ID, STATUS_KOMUNIKACIJA_KORISNIKU ");
    strSqlStatement.append(" FROM TEMP_PREGLED_ZAHTJEVA WHERE ID = ");
    strSqlStatement.append(cttl::itos(m_iSporazumSlogId));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        if(rs->next())
        {
            ui->lblSporazumId->setText(QString::number(rs->getUInt(1)));
            if(rs->isNull(2) == false)
            {
                ui->lblTicket->setText(QString::number(rs->getUInt(11)));
            }
            ui->lblTelBroj->setText(QString::fromStdString(rs->getString(5)));

            if(rs->isNull(10) == true)
            {
                m_iPoslovniProcesId = 0;
            }
            else
            {
                m_iPoslovniProcesId = rs->getUInt(10);
                ui->lblPoslovniProcesId->setText(QString::number(rs->getUInt(10)));
            }

            if(rs->isNull(4) == true)
            {
                m_iGrupaImovineId = 0;
            }
            else
            {
                ui->lblGrupaImovineId->setText(QString::number(rs->getUInt(4)));
                m_iGrupaImovineId = rs->getUInt(4);
            }

            ui->lblSporazumCreateTitle->setText(QString::fromStdString(rs->getString(16)) +
                                                tr(" ... ") +
                                                QString::fromStdString(rs->getString(14)) +
                                                tr(" ... ") +
                                                QString::fromStdString(rs->getString(15))
                                                );

            m_strBrojDokumenta = rs->getString(2);
            m_dateDatumzahtjeva = QDateTime::fromString(QString::fromStdString(rs->getString(12)), tr("dd.MM.yyyy hh:mm"));
            ui->lblSporazumDatumzadnjeIzmjene->setText(QString::fromStdString(rs->getString(13)));
            ui->lblUgovorStatus->setText(QString::fromStdString(rs->getString(8)));
            ui->lblUgovorBillingStatus->setText(QString::fromStdString(rs->getString(9)));

            switch (rs->getInt(18)) {
            case 0:
            {
                ui->lblGrupaImovineAktivnost->setText(tr("PROMJENA"));
                break;
            }
            case 1:
            {
                ui->lblGrupaImovineAktivnost->setText(tr("UKLJUČENJE"));
                break;
            }
            case 2:
            {
                ui->lblGrupaImovineAktivnost->setText(tr("ISKLJUČENJE"));
                break;
            }
            default:
                break;
            }

            switch (rs->getInt(19)) {
            case 0:
            {
                ui->lblGrupaImovineStatus->setText(tr("U TIJEKU"));
                break;
            }
            case 1:
            {
                ui->lblGrupaImovineStatus->setText(tr("ZATVORENO"));
                break;
            }
            case 2:
            {
                ui->lblGrupaImovineStatus->setText(tr("STORNIRANO"));
                break;
            }
            default:
                break;
            }
        }

        ui->lblOpis->setText(ui->lblOpis->text() +
                             tr("\n") +
                             QString::fromStdString(rs->getString(7)) +
                             tr("\n") +
                             QString::fromStdString(rs->getString(17)));

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

    switch (m_iListaSub)
    {
        case 1:
        {
            popunaWwmsGreska();
            break;
        }
        case 2:
        {
            popunaWwmsRazlog();
            break;
        }
        case 3:
        {
            popunaWwmsStorno();
            break;
        }
        default:
            break;
    }
}
void FrmPregledN::popunaWwmsGreska()
{
    if(m_iPoslovniProcesId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT ERROR_RECEIVING (");
    strSqlStatement.append(cttl::itos(m_iPoslovniProcesId));
    strSqlStatement.append(") GRESKA FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        if(rs->next())
        {
            ui->lblOpis->setText(ui->lblOpis->text() +
                                 tr("\n") +
                                 QString::fromStdString(rs->getString(1)) +
                                 tr("\nStornirati Zahtjev"));
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
void FrmPregledN::popunaWwmsRazlog()
{
    if(m_iPoslovniProcesId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT ORDER_ID, REPLACE(STATUS_REASON,CHR(10),' ') STATUS_REASON, NVL(SOLUTIONPROPOSAL,' ') PRIJEDLOG ");
    strSqlStatement.append(" , CASE WHEN UPPER(SOLUTIONPROPOSAL) LIKE '%FGSM%' THEN 1 ELSE 0 END FGSM ");
    strSqlStatement.append(" FROM WWMS_RESPONSE1 W1 WHERE ORDER_ID = '");
    strSqlStatement.append(cttl::itos(m_iPoslovniProcesId));
    strSqlStatement.append("' AND RESP_NUM=(SELECT MAX(RESP_NUM) FROM WWMS_RESPONSE1 W2 WHERE W1.ORDER_ID=W2.ORDER_ID) ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        if(rs->next())
        {
            ui->lblOpis->setText(ui->lblOpis->text() +
                                 tr("\n") +
                                 QString::fromStdString(rs->getString(2)) +
                                 tr("\n") +
                                 QString::fromStdString(rs->getString(3)));
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
void FrmPregledN::popunaWwmsStorno()
{
    if(m_iPoslovniProcesId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT NVL(STATUS_REASON,'NIJE DEFINIRANO') STATUS_REASON, NVL(SOLUTIONPROPOSAL,'NIJE DEFINIRANO') SOLUTIONPROPOSAL ");
    strSqlStatement.append(" FROM WWMS_RESPONSE1 WHERE ORDER_ID = '");
    strSqlStatement.append(cttl::itos(m_iPoslovniProcesId));
    strSqlStatement.append("' AND STATUS LIKE 'WWMS_CANCEL_REQUEST%' ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        if(rs->next())
        {
            ui->lblOpis->setText(ui->lblOpis->text() +
                                 tr("\n") +
                                 QString::fromStdString(rs->getString(2)) +
                                 tr("\n") +
                                 QString::fromStdString(rs->getString(3)));
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
void FrmPregledN::popunaSporazumAktivnosti()
{
}
void FrmPregledN::popunaOstalo()
{
}
void FrmPregledN::popunaSporazumStavki()
{
    if (m_iSporazumId == 0)
    {
        return;
    }

    ui->treeStavke->clear();

    QList<QTreeWidgetItem *> listSporazumStavke;

    string strSqlStatement;
    strSqlStatement.append("BEGIN SPORAZUM_U_TEMPLATE(:SPORAZUM_ID_PAR, :REZULTAT); END;");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setUInt(1, m_iSporazumId); // Sporazum Id
        sqlStatement->registerOutParam(2, OCCISTRING, 2000); // Rezultat
        sqlStatement->executeUpdate();
        if(sqlStatement->isNull(2) == false)
        {
            if(sqlStatement->getString(2) != "0")
            {
                ui->lblOpis->setText(ui->lblOpis->text() +
                                     tr("\n") +
                                     QString::fromStdString(sqlStatement->getString(2)));
            }
        }
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT ID, NVL(NAD_ID, 1500) NAD_ID, NVL(NIVO, 1500) NIVO, IMOVINA_ID, NAD_IMOVINA_ID, GIMOVINE_ID, OVISNA_GIMOVINE_ID, OVISNA_IMOVINA_ID, ");
    strSqlStatement.append(" NVL(PRODUKT_ID, 0) PRODUKT_ID, NAZIV_PRODUKTA, LPRODUKATA_ID, GPRODUKATA_ID, NOVA_GRUPA, TAKTIVNOSTI_ID, NAPLATA_ID,  ");
    strSqlStatement.append(" ISPORUKA_ID, TIP, PRODUKT_ID_SPOR, NAZIV_PRODUKTA_SPOR  ");
    strSqlStatement.append("FROM TEMP_IMOVINA_TEMPLATE ORDER BY ID, NAD_ID ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        while(rs->next())
        {
            //int iId = rs->getInt(1);
            int iNadId = rs->getInt(2);
            int iGrupaProduktaId = rs->getInt(12);


            if(listSporazumStavke.count() == 0)
            {
                QTreeWidgetItem *itemSporazumStavka = new QTreeWidgetItem();
                itemSporazumStavka->setText(0, QString::fromStdString(rs->getString(10)));
                if(iGrupaProduktaId == 4)
                {
                    QBrush brushRed = itemSporazumStavka->foreground(0);
                    brushRed.setColor(Qt::red);
                    itemSporazumStavka->setForeground(0, brushRed);
                }
                itemSporazumStavka->setText(1, QString::number(rs->getInt(1)));
                itemSporazumStavka->setText(2, QString::number(rs->getUInt(2)));
                itemSporazumStavka->setText(3, QString::number(rs->getUInt(9)));
                itemSporazumStavka->setText(4, QString::number(rs->getInt(12)));
                itemSporazumStavka->setText(5, QString::number(rs->getInt(3)));
                listSporazumStavke.append(itemSporazumStavka);
            }
            else
            {
                int iListSize = listSporazumStavke.size();
                bool bNovaStavka = true;
                for(int i = 0; i < iListSize; ++i)
                {
                    if(listSporazumStavke.at(i)->text(1).toInt() == iNadId)
                    {
                        QTreeWidgetItem *itemSporazumStavka = new QTreeWidgetItem();
                        itemSporazumStavka->setText(0, QString::fromStdString(rs->getString(10)));
                        if(iGrupaProduktaId == 4)
                        {
                            QBrush brushRed = itemSporazumStavka->foreground(0);
                            brushRed.setColor(Qt::red);
                            itemSporazumStavka->setForeground(0, brushRed);
                        }
                        itemSporazumStavka->setText(1, QString::number(rs->getInt(1)));
                        itemSporazumStavka->setText(2, QString::number(rs->getUInt(2)));
                        itemSporazumStavka->setText(3, QString::number(rs->getUInt(9)));
                        itemSporazumStavka->setText(4, QString::number(rs->getInt(12)));
                        itemSporazumStavka->setText(5, QString::number(rs->getInt(3)));
                        listSporazumStavke.append(itemSporazumStavka);
                        listSporazumStavke.at(i)->addChild(itemSporazumStavka);
                        bNovaStavka = false;
                    }
                }
                if(bNovaStavka == true)
                {
                    QTreeWidgetItem *itemSporazumStavka = new QTreeWidgetItem();
                    itemSporazumStavka->setText(0, QString::fromStdString(rs->getString(10)));
                    if(iGrupaProduktaId == 4)
                    {
                        QBrush brushRed = itemSporazumStavka->foreground(0);
                        brushRed.setColor(Qt::red);
                        itemSporazumStavka->setForeground(0, brushRed);
                    }
                    itemSporazumStavka->setText(1, QString::number(rs->getInt(1)));
                    itemSporazumStavka->setText(2, QString::number(rs->getUInt(2)));
                    itemSporazumStavka->setText(3, QString::number(rs->getUInt(9)));
                    itemSporazumStavka->setText(4, QString::number(rs->getInt(12)));
                    itemSporazumStavka->setText(5, QString::number(rs->getInt(3)));
                    listSporazumStavke.append(itemSporazumStavka);
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

    if(!listSporazumStavke.empty())
    {
        listSporazumStavke.first()->setSelected(true);
        ui->treeStavke->insertTopLevelItems(0, listSporazumStavke);
        ui->treeStavke->expandAll();
//        ui->treeSporazumi->collapseAll();
//        ui->treeSporazumi->expandItem(listSporazumi.first());
//        ui->treeSporazumi->setCurrentItem(listSporazumi.first());
    }
}

// [Event Handlers]
void FrmPregledN::on_btnPregledAktivnosti_clicked()
{
    if(m_iPregledAktivnosti != 0)
    {
        ui->lblAktivnostPregledTitle->setText(tr("AKTIVNOSTI"));
        ui->fraAktivnosti->setVisible(true);
        ui->fraRazlog->setVisible(true);
        ui->fraPotvrdaAktivnosti->setVisible(true);
        ui->fraStavke->setVisible(false);
        m_iPregledAktivnosti = 0;
    }
    else
    {
        ui->lblAktivnostPregledTitle->setText(tr("STAVKE"));
        ui->fraAktivnosti->setVisible(false);
        ui->fraRazlog->setVisible(false);
        ui->fraPotvrdaAktivnosti->setVisible(false);
        ui->fraStavke->setVisible(true);
        m_iPregledAktivnosti = 1;
        popunaSporazumStavki();
    }
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

void FrmPregledN::on_treeSporazumi_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    setCursor(Qt::BusyCursor);

    m_iSporazumId = item->text(2).toUInt();
    m_iKupacId = item->text(7).toUInt();
    m_iStrankaId = item->text(8).toUInt();

    initSporazum();
    popuniSporazumListu();

    setCursor(Qt::ArrowCursor);
}

void FrmPregledN::on_treeSporazumLista_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    initSlog();
    m_iSporazumSlogId = item->text(22).toUInt();
    popunaSporazumSlog();
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

void FrmPregledN::on_btnStatusDonat_clicked()
{
    if(m_iSporazumId == 0)
    {
        return;
    }

    // Show Donat pregled zahtjeva new
    Sporazumi::FrmDonatPregled *frmDonatPregled = new Sporazumi::FrmDonatPregled(m_iSporazumId, this);
    //frmDonatPregled->show();
    frmDonatPregled->exec();
    delete frmDonatPregled;
}

void FrmPregledN::on_btnStatusWwms_clicked()
{
    if(m_iSporazumId == 0)
    {
        return;
    }

    // Show Donat pregled zahtjeva new
    Sporazumi::FrmWwmsPregled *frmWwmsPregled = new Sporazumi::FrmWwmsPregled(m_iSporazumId, 1, this);
    //frmWwmsPregled->show();
    frmWwmsPregled->exec();
    delete frmWwmsPregled;
}

void FrmPregledN::on_btnDonatProcesi_clicked()
{
    if(m_iSporazumId == 0)
    {
        return;
    }

    // Show Donat pregled zahtjeva new
    Sporazumi::FrmPregledProcesa *frmPregledProcesa = new Sporazumi::FrmPregledProcesa(m_iSporazumId, this);
    //frmPregledProcesa->show();
    frmPregledProcesa->exec();
    delete frmPregledProcesa;
}

void FrmPregledN::on_btnDonatDetaljno_clicked()
{
    if(m_iSporazumId == 0)
    {
        return;
    }

    // Show Donat pregled zahtjeva new
    Sporazumi::FrmPregledSporazuma *frmPregledSporazuma = new Sporazumi::FrmPregledSporazuma(m_iSporazumId, this);
    //frmPregledSporazuma->show();
    frmPregledSporazuma->exec();
    delete frmPregledSporazuma;
}

void FrmPregledN::on_btnDonatNapomena_clicked()
{

}

void FrmPregledN::on_btnDonatDatoteke_clicked()
{

}

void FrmPregledN::on_btnDonatSpis_clicked()
{

}

void FrmPregledN::on_btnDonatJop_clicked()
{

}

void FrmPregledN::on_pushDonatDodijeliJop_clicked()
{

}

void FrmPregledN::on_btnDonatDokument_clicked()
{

}

void FrmPregledN::on_btnUlaznePoruke_clicked()
{

}

void FrmPregledN::on_btnKanalProdaje_2_clicked()
{

}

void FrmPregledN::on_btnDatumZahtjeva_clicked()
{

}

} // namespace sporazumi













