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

    m_iSporazumId = 0;
    m_iListaGrupa = 1;
    m_iTipKorisnika = 1;
    m_iTipKanala = 1;
    m_iTipKupca = 0;
    m_iTipFiltra = 0;

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

    ui->btnKorisnikKanal->setText(QString::fromStdString(g_UNIO_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_KORISNIK_NAZ));

    popunaKlasa();
    popunaListaGrupa();
}

void FrmPregledN::setKorisnik()
{
    if(m_iTipKanala == 1)
    {
        ui->btnKorisnikKanal->setText(QString::fromStdString(g_UNIO_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_KORISNIK_NAZ));
        if(m_iTipKorisnika == 0)
        {
            m_iTipKorisnika = 1;
            ui->btnZahtjevUnio->setChecked(true);
            ui->btnZahtjevProdao->setChecked(false);
        }

        if(g_UNIO_KORISNIK_ID == "0")
        {
            m_iTipKorisnika = 0;
            ui->btnZahtjevUnio->setChecked(false);
            ui->btnZahtjevProdao->setChecked(false);
        }
    }
    else if(m_iTipKanala == 2)
    {
        ui->btnKorisnikKanal->setText(QString::fromStdString(g_UNIO_REGIJA_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_ZUPANIJA_NAZ));
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
        ui->treeListeGrupa->setCurrentItem(listListaGrupa.first());
        ui->treeListeGrupa->expandAll();
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

// [Event Handlers]
void FrmPregledN::on_btnPregledAktivnosti_clicked()
{

}

void FrmPregledN::on_btnZahtjevUnio_clicked()
{
    if(g_UNIO_KORISNIK_ID == "0")
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
    if(g_UNIO_KORISNIK_ID == "0")
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

//    ui->btnKorisnikKanal->setText(QString::fromStdString(g_UNIO_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_KORISNIK_NAZ));
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

//    ui->btnKorisnikKanal->setText(QString::fromStdString(g_UNIO_KANAL_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_ORGJED_NAZ) + tr(" ... ") + QString::fromStdString(g_UNIO_KORISNIK_NAZ));

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

}

void FrmPregledN::on_btnPretragaKljucni_clicked()
{

}

void FrmPregledN::on_btnPretragatSme_clicked()
{

}

void FrmPregledN::on_btnPretragaVeleprodaja_clicked()
{

}

void FrmPregledN::on_treeListeGrupa_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{

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


} // namespace sporazumi








