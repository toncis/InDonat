//
//  frmkanalprodaje.cpp
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

#include "frmkanalprodaje.h"
#include "ui_frmkanalprodaje.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {
// [ Class Constructor ]
FrmKanalProdaje::FrmKanalProdaje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKanalProdaje)
{
    ui->setupUi(this);

    ui->treeSifre->hideColumn(0);

    m_iFormActivity = 0;
    m_SifranikMode = SifarnikModeNone;
    m_KanalProdajeMode = KanalProdajeFilter;
    popuniZaKanalProdaje();
}
FrmKanalProdaje::FrmKanalProdaje(int iFormActivity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKanalProdaje)
{
    ui->setupUi(this);

    ui->treeSifre->hideColumn(0);

    m_iFormActivity = iFormActivity;
    m_SifranikMode = SifarnikModeNone;

    switch (m_iFormActivity)
    {
        case 1:
            {
                this->setWindowTitle(tr("Kanal Prodaje - Pregled Zahtjeva"));
                ui->btnKanalProdaje->setText(tr("PREGLED ZAHTJEVA"));
                m_KanalProdajeMode = KanalProdajeFilter;
                popuniZaPregledzahtjeva();
                break;
            }
        case 2:
            {
                this->setWindowTitle(tr("Kanal Prodaje - Prodajni Kanal"));
                ui->btnKanalProdaje->setText(tr("KANAL PRODAJE"));
                m_KanalProdajeMode = KanalProdajeProdajniKanal;
                popuniZaKanalProdajeProdajniKanal();
                break;
            }
        case 3:
            {
                this->setWindowTitle(tr("Kanal Prodaje - Regija"));
                ui->btnKanalProdaje->setText(tr("REGIJA"));
                m_KanalProdajeMode = KanalProdajeRegija;
                popuniZaKanalProdajeRegija();
                break;
            }
        case 4:
            {
                this->setWindowTitle(tr("Kanal Prodaje - Promjena Na zahtjevu"));
                ui->btnKanalProdaje->setText(tr("PROMJENA NA ZAHTJEVU"));
                m_KanalProdajeMode = KanalProdajeKorisnik;
                popuniZaPromjenuNaZahtjevu();
                break;
            }
        default:
            {
                m_KanalProdajeMode = KanalProdajeFilter;
                break;
            }
    }
}

FrmKanalProdaje::~FrmKanalProdaje()
{
    delete ui;
}

// [ Private Member Functions ]
void FrmKanalProdaje::popuniZaKanalProdaje()
{
    m_iRegijaId = g_FILTER_REGIJA_ID;
    m_iZupanijaId = g_FILTER_ZUPANIJA_ID;
    m_iKanalId = g_FILTER_KANAL_ID;
    m_iOrganizacijskaJedinicaId = g_FILTER_ORGJED_ID;
    m_strKorisdikId = g_FILTER_KORISNIK_ID;
    ui->txtRegija->setText(QString::fromStdString(g_FILTER_REGIJA_NAZ));
    ui->txtZupanija->setText(QString::fromStdString(g_FILTER_ZUPANIJA_NAZ));
    ui->txtKanalProdaje->setText(QString::fromStdString(g_FILTER_KANAL_NAZ));
    ui->txtOrganizacijskaJedinica->setText(QString::fromStdString(g_FILTER_ORGJED_NAZ));
    ui->txtKorisnik->setText(QString::fromStdString(g_FILTER_KORISNIK_NAZ));

//    ui->btnFilter->clicked(true);
}
void FrmKanalProdaje::popuniZaKanalProdajeProdajniKanal()
{
    m_iRegijaId = g_FILTER_REGIJA_ID;
    m_iZupanijaId = g_FILTER_ZUPANIJA_ID;
    m_iKanalId = g_FILTER_KANAL_ID;
    m_iOrganizacijskaJedinicaId = g_FILTER_ORGJED_ID;
    m_strKorisdikId = g_FILTER_KORISNIK_ID;
    ui->txtRegija->setText(QString::fromStdString(g_FILTER_REGIJA_NAZ));
    ui->txtZupanija->setText(QString::fromStdString(g_FILTER_ZUPANIJA_NAZ));
    ui->txtKanalProdaje->setText(QString::fromStdString(g_FILTER_KANAL_NAZ));
    ui->txtOrganizacijskaJedinica->setText(QString::fromStdString(g_FILTER_ORGJED_NAZ));
    ui->txtKorisnik->setText(QString::fromStdString(g_FILTER_KORISNIK_NAZ));
    //set font
    QFont font = ui->lblKanalProdaje->font();
    font.setBold(true);
    ui->lblKanalProdaje->setFont(font);
//    ui->btnFilter->clicked(true);
}
void FrmKanalProdaje::popuniZaKanalProdajeRegija()
{
    m_iRegijaId = g_FILTER_REGIJA_ID;
    m_iZupanijaId = g_FILTER_ZUPANIJA_ID;
    m_iKanalId = g_FILTER_KANAL_ID;
    m_iOrganizacijskaJedinicaId = g_FILTER_ORGJED_ID;
    m_strKorisdikId = g_FILTER_KORISNIK_ID;
    ui->txtRegija->setText(QString::fromStdString(g_FILTER_REGIJA_NAZ));
    ui->txtZupanija->setText(QString::fromStdString(g_FILTER_ZUPANIJA_NAZ));
    ui->txtKanalProdaje->setText(QString::fromStdString(g_FILTER_KANAL_NAZ));
    ui->txtOrganizacijskaJedinica->setText(QString::fromStdString(g_FILTER_ORGJED_NAZ));
    ui->txtKorisnik->setText(QString::fromStdString(g_FILTER_KORISNIK_NAZ));
    //set font
    QFont font = ui->lblRegijaTitle->font();
    font.setBold(true);
    ui->lblRegijaTitle->setFont(font);
//    ui->btnFilter->clicked(true);
}
void FrmKanalProdaje::popuniZaPregledzahtjeva()
{
    m_iRegijaId = g_UNIO_REGIJA_ID;
    m_iZupanijaId = g_UNIO_ZUPANIJA_ID;
    m_iKanalId = g_UNIO_KANAL_ID;
    m_iOrganizacijskaJedinicaId = g_UNIO_ORGJED_ID;
    m_strKorisdikId = g_UNIO_KORISNIK_ID;
    ui->txtRegija->setText(QString::fromStdString(g_UNIO_REGIJA_NAZ));
    ui->txtZupanija->setText(QString::fromStdString(g_UNIO_ZUPANIJA_NAZ));
    ui->txtKanalProdaje->setText(QString::fromStdString(g_UNIO_KANAL_NAZ));
    ui->txtOrganizacijskaJedinica->setText(QString::fromStdString(g_UNIO_ORGJED_NAZ));
    ui->txtKorisnik->setText(QString::fromStdString(g_UNIO_KORISNIK_NAZ));

    //    ui->btnKorisnik->clicked(true);
}
void FrmKanalProdaje::popuniZaPromjenuNaZahtjevu()
{
}

void FrmKanalProdaje::popuniRegiju()
{
    ui->treeSifre->clear();
//    ui->txtRegija->clear();
    ui->txtZupanija->clear();
    ui->txtKanalProdaje->clear();
    ui->txtOrganizacijskaJedinica->clear();
    ui->txtKorisnik->clear();
    ui->lblOpis->clear();
//    m_iRegijaId = 0;
    m_iZupanijaId = 0;
    m_iKanalId = 0;
    m_iOrganizacijskaJedinicaId = 0;
    m_strKorisdikId = "";

    m_SifranikMode = SifarnikModeRegija;
    ui->lblSifarnik->setText(tr("REGIJA"));

    string strSqlStatement;
    strSqlStatement.append("SELECT GEO_ID, NAZIV FROM GEO_STRUKTURE WHERE TGEOSTRUKT_ID = 2 ORDER BY NAZIV ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listSifre;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemSifra = new QTreeWidgetItem();
            itemSifra->setText(0, QString::fromStdString(rs->getString(1)));
            itemSifra->setText(1, QString::fromStdString(rs->getString(2)));
            listSifre.append(itemSifra);
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

    if(!listSifre.empty())
    {
        listSifre.first()->setSelected(true);
        ui->treeSifre->insertTopLevelItems(0, listSifre);
        ui->treeSifre->setCurrentItem(listSifre.first());
        ui->treeSifre->expandAll();
    }
}
void FrmKanalProdaje::popuniZupaniju()
{
    ui->treeSifre->clear();
//    ui->txtRegija->clear();
//    ui->txtZupanija->clear();
    ui->txtKanalProdaje->clear();
    ui->txtOrganizacijskaJedinica->clear();
    ui->txtKorisnik->clear();
    ui->lblOpis->clear();
//    m_iRegijaId = 0;
    m_iZupanijaId = 0;
    m_iKanalId = 0;
    m_iOrganizacijskaJedinicaId = 0;
    m_strKorisdikId = "";

    m_SifranikMode = SifarnikModeZupanija;
    ui->lblSifarnik->setText(tr("ŽUPANIJA"));

    string strSqlStatement;
    strSqlStatement.append("SELECT GEO_ID,NAZIV FROM GEO_STRUKTURE G,VEZE_GEO VG ");
    strSqlStatement.append("WHERE G.GEO_ID = VG.GEO2_ID And TGEOSTRUKT_ID = 3 And VG.GEO1_ID = ");
    strSqlStatement.append(cttl::itos(m_iRegijaId));
    strSqlStatement.append(" ORDER BY NAZIV ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listSifre;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemSifra = new QTreeWidgetItem();
            itemSifra->setText(0, QString::fromStdString(rs->getString(1)));
            itemSifra->setText(1, QString::fromStdString(rs->getString(2)));
            listSifre.append(itemSifra);
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

    if(!listSifre.empty())
    {
        listSifre.first()->setSelected(true);
        ui->treeSifre->insertTopLevelItems(0, listSifre);
        ui->treeSifre->setCurrentItem(listSifre.first());
        ui->treeSifre->expandAll();
    }
}
void FrmKanalProdaje::popuniKanalProdaje()
{
    ui->treeSifre->clear();
//    ui->txtRegija->clear();
//    ui->txtZupanija->clear();
//    ui->txtKanalProdaje->clear();
    ui->txtOrganizacijskaJedinica->clear();
    ui->txtKorisnik->clear();
    ui->lblOpis->clear();
//    m_iRegijaId = 0;
//    m_iZupanijaId = 0;
    m_iKanalId = 0;
    m_iOrganizacijskaJedinicaId = 0;
    m_strKorisdikId = "";

    m_SifranikMode = SifarnikModeKanalProdaje;
    ui->lblSifarnik->setText(tr("KANAL"));

    string strSqlStatement;
    strSqlStatement.append("SELECT KANAL_ID, NAZIV FROM KANALI_PRODAJE_VIEW ORDER BY RBK ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listSifre;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemSifra = new QTreeWidgetItem();
            itemSifra->setText(0, QString::fromStdString(rs->getString(1)));
            itemSifra->setText(1, QString::fromStdString(rs->getString(2)));
            listSifre.append(itemSifra);
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

    if(!listSifre.empty())
    {
        listSifre.first()->setSelected(true);
        ui->treeSifre->insertTopLevelItems(0, listSifre);
        ui->treeSifre->setCurrentItem(listSifre.first());
        ui->treeSifre->expandAll();
    }
}
void FrmKanalProdaje::popuniOrganizacijskuJedinicu()
{
    ui->treeSifre->clear();
//    ui->txtRegija->clear();
//    ui->txtZupanija->clear();
//    ui->txtKanalProdaje->clear();
    ui->txtOrganizacijskaJedinica->clear();
    ui->txtKorisnik->clear();
    ui->lblOpis->clear();
//    m_iRegijaId = 0;
//    m_iZupanijaId = 0;
//    m_iKanalId = 0;
    m_iOrganizacijskaJedinicaId = 0;
    m_strKorisdikId = "";

    m_SifranikMode = SifarnikModeOrganizacijskaJedinica;
    ui->lblSifarnik->setText(tr("ORG JED"));

    string strSqlStatement;
    strSqlStatement.append("SELECT DISTINCT ORGJED_ID, ORG_JEDINICA FROM V_KANALI_PRODAJE WHERE KANAL_ID = ");
    strSqlStatement.append(cttl::itos(m_iKanalId));
    if(m_iRegijaId > 0)
    {
        strSqlStatement.append(" AND REGIJA_ID = ");
        strSqlStatement.append(cttl::itos(m_iRegijaId));
    }
    if(m_iZupanijaId > 0)
    {
        strSqlStatement.append(" AND LOKACIJA_ID = ");
        strSqlStatement.append(cttl::itos(m_iZupanijaId));
    }
    strSqlStatement.append(" ORDER BY ORG_JEDINICA ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listSifre;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemSifra = new QTreeWidgetItem();
            itemSifra->setText(0, QString::fromStdString(rs->getString(1)));
            itemSifra->setText(1, QString::fromStdString(rs->getString(2)));
            listSifre.append(itemSifra);
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

    if(!listSifre.empty())
    {
        listSifre.first()->setSelected(true);
        ui->treeSifre->insertTopLevelItems(0, listSifre);
        ui->treeSifre->setCurrentItem(listSifre.first());
        ui->treeSifre->expandAll();
    }
}
void FrmKanalProdaje::popuniKorisnika()
{
    ui->treeSifre->clear();
//    ui->txtRegija->clear();
//    ui->txtZupanija->clear();
//    ui->txtKanalProdaje->clear();
//    ui->txtOrganizacijskaJedinica->clear();
    ui->txtKorisnik->clear();
    ui->lblOpis->clear();
//    m_iRegijaId = 0;
//    m_iZupanijaId = 0;
//    m_iKanalId = 0;
//    m_iOrganizacijskaJedinicaId = 0;
    m_strKorisdikId = "";

    m_SifranikMode = SifarnikModeKorisnik;
    ui->lblSifarnik->setText(tr("KORISNIK"));

    string strSqlStatement;
    strSqlStatement.append("SELECT DISTINCT KORISNIK_ID,NAZIV FROM V_KANALI_PRODAJE WHERE ORGJED_ID = ");
    strSqlStatement.append(cttl::itos(m_iKanalId));
    if(ui->lineEdit->text().length() > 0)
    {
        strSqlStatement.append("  AND NAZIV LIKE ('%");
        strSqlStatement.append(ui->lineEdit->text().toUpper().toStdString());
        strSqlStatement.append("%') ");
    }
    strSqlStatement.append(" ORDER BY NAZIV ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listSifre;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemSifra = new QTreeWidgetItem();
            itemSifra->setText(0, QString::fromStdString(rs->getString(1)));
            itemSifra->setText(1, QString::fromStdString(rs->getString(2)));
            listSifre.append(itemSifra);
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

    if(!listSifre.empty())
    {
        listSifre.first()->setSelected(true);
        ui->treeSifre->insertTopLevelItems(0, listSifre);
        ui->treeSifre->setCurrentItem(listSifre.first());
        ui->treeSifre->expandAll();
    }
}
void FrmKanalProdaje::popuniKorisnika(string strKorisnikId)
{
    string strSqlStatement;
    strSqlStatement.append("SELECT REGIJA_ID, LOKACIJA_ID, KANAL_ID, KANAL_PRODAJE, ORGJED_ID, ORG_JEDINICA, KORISNIK_ID, NAZIV ");
    strSqlStatement.append("FROM V_KANALI_PRODAJE WHERE KORISNIK_ID = '");
    strSqlStatement.append(strKorisnikId);
    strSqlStatement.append("' ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_iRegijaId = rs->getInt(1);
            m_iZupanijaId = rs->getInt(2);
            m_iKanalId = rs->getInt(3);
            ui->txtKanalProdaje->setText(QString::fromStdString(rs->getString(4)));
            m_iOrganizacijskaJedinicaId = rs->getInt(5);
            ui->txtOrganizacijskaJedinica->setText(QString::fromStdString(rs->getString(6)));
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
    strSqlStatement.append("SELECT NAZIV FROM GEO_STRUKTURE WHERE GEO_ID = ");
    strSqlStatement.append(cttl::itos(m_iRegijaId));
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtRegija->setText(QString::fromStdString(rs->getString(1)));
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
    strSqlStatement.append("SELECT NAZIV FROM GEO_STRUKTURE WHERE GEO_ID = ");
    strSqlStatement.append(cttl::itos(m_iZupanijaId));
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtZupanija->setText(QString::fromStdString(rs->getString(1)));
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
void FrmKanalProdaje::popuniSveKorisnike()
{
    ui->treeSifre->clear();
//    ui->txtRegija->clear();
//    ui->txtZupanija->clear();
//    ui->txtKanalProdaje->clear();
//    ui->txtOrganizacijskaJedinica->clear();
    ui->txtKorisnik->clear();
    ui->lblOpis->clear();
//    m_iRegijaId = 0;
//    m_iZupanijaId = 0;
//    m_iKanalId = 0;
//    m_iOrganizacijskaJedinicaId = 0;
    m_strKorisdikId = "";

    m_SifranikMode = SifarnikModeSviKorisnici;
    ui->lblSifarnik->setText(tr("KORISNIK"));

    string strSqlStatement;
    strSqlStatement.append("SELECT DISTINCT KORISNIK_ID,NAZIV FROM V_KANALI_PRODAJE WHERE NAZIV LIKE ('%");
    strSqlStatement.append(ui->lineEdit->text().toUpper().toStdString());
    strSqlStatement.append("%') ");
    strSqlStatement.append(" ORDER BY NAZIV ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listSifre;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemSifra = new QTreeWidgetItem();
            itemSifra->setText(0, QString::fromStdString(rs->getString(1)));
            itemSifra->setText(1, QString::fromStdString(rs->getString(2)));
            listSifre.append(itemSifra);
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

    if(!listSifre.empty())
    {
        listSifre.first()->setSelected(true);
        ui->treeSifre->insertTopLevelItems(0, listSifre);
        ui->treeSifre->setCurrentItem(listSifre.first());
        ui->treeSifre->expandAll();
    }
}

// [ Event Handlers ]
void FrmKanalProdaje::on_btnPotvrda_clicked()
{
    if(m_strKorisdikId.length() == 0 && (m_KanalProdajeMode == KanalProdajeKorisnik || m_KanalProdajeMode == KanalProdajeFilter))
    {
        QMessageBox::information(this, tr("DONAT - Kanal Prodaje"), tr("Popunite sve podatke za Korisnika."), QMessageBox::Close);
        return;
    }

    if(m_iRegijaId == 0 && m_KanalProdajeMode == KanalProdajeRegija)
    {
        QMessageBox::information(this, tr("DONAT - Kanal Prodaje"), tr("Popunite sve podatke za odabir Regije."), QMessageBox::Close);
        return;
    }

    if(m_iKanalId == 0 && m_KanalProdajeMode == KanalProdajeProdajniKanal)
    {
        QMessageBox::information(this, tr("DONAT - Kanal Prodaje"), tr("Popunite sve podatke za odabir Prodajnog Kanala."), QMessageBox::Close);
        return;
    }

    if(m_KanalProdajeMode == KanalProdajeKorisnik)
    {
        g_UNIO_REGIJA_ID = m_iRegijaId;
        g_UNIO_REGIJA_NAZ = ui->txtRegija->text().toStdString();
        g_UNIO_ZUPANIJA_ID = m_iZupanijaId;
        g_UNIO_ZUPANIJA_NAZ = ui->txtZupanija->text().toStdString();
        g_UNIO_KANAL_ID = m_iKanalId;
        g_UNIO_KANAL_NAZ = ui->txtKanalProdaje->text().toStdString();
        g_UNIO_ORGJED_ID = m_iOrganizacijskaJedinicaId;
        g_UNIO_ORGJED_NAZ = ui->txtOrganizacijskaJedinica->text().toStdString();
        g_UNIO_KORISNIK_ID = m_strKorisdikId;
        g_UNIO_KORISNIK_NAZ = ui->txtKorisnik->text().toStdString();

        string strSqlStatement;
        strSqlStatement.append("DELETE FROM TEMP_KORISNIK");

        Statement *sqlStatement = g_DonatConn->createStatement();
        sqlStatement->setSQL(strSqlStatement);
        sqlStatement->setAutoCommit(TRUE);

        try
        {
            sqlStatement->executeUpdate();
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }

        strSqlStatement.erase();
        strSqlStatement.append("INSERT INTO TEMP_KORISNIK (KORISNIK_ID) VALUES ('");
        strSqlStatement.append(m_strKorisdikId);
        strSqlStatement.append("') ");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            sqlStatement->executeUpdate();
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }

        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();

        this->close();
    }
    else if(m_KanalProdajeMode == KanalProdajeFilter)
    {
        g_FILTER_REGIJA_ID = m_iRegijaId;
        g_FILTER_REGIJA_NAZ = ui->txtRegija->text().toStdString();
        g_FILTER_ZUPANIJA_ID = m_iZupanijaId;
        g_FILTER_ZUPANIJA_NAZ = ui->txtZupanija->text().toStdString();
        g_FILTER_KANAL_ID = m_iKanalId;
        g_FILTER_KANAL_NAZ = ui->txtKanalProdaje->text().toStdString();
        g_FILTER_ORGJED_ID = m_iOrganizacijskaJedinicaId;
        g_FILTER_ORGJED_NAZ = ui->txtOrganizacijskaJedinica->text().toStdString();
        g_FILTER_KORISNIK_ID = m_strKorisdikId;
        g_FILTER_KORISNIK_NAZ = ui->txtKorisnik->text().toStdString();

        this->close();
    }
    else if (m_KanalProdajeMode == KanalProdajeRegija)
    {
        g_FILTER_REGIJA_ID = m_iRegijaId;
        g_FILTER_REGIJA_NAZ = ui->txtRegija->text().toStdString();
        g_FILTER_ZUPANIJA_ID = m_iZupanijaId;
        g_FILTER_ZUPANIJA_NAZ = ui->txtZupanija->text().toStdString();
        g_FILTER_KANAL_ID = 0;
        g_FILTER_KANAL_NAZ = "";
        g_FILTER_ORGJED_ID = 0;
        g_FILTER_ORGJED_NAZ = "";
        g_FILTER_KORISNIK_ID = "0";
        g_FILTER_KORISNIK_NAZ = "";

        this->close();
    }
    else if (m_KanalProdajeMode == KanalProdajeProdajniKanal)
    {
        g_FILTER_REGIJA_ID = 0;
        g_FILTER_REGIJA_NAZ = "";
        g_FILTER_ZUPANIJA_ID = 0;
        g_FILTER_ZUPANIJA_NAZ = "";
        g_FILTER_KANAL_ID = m_iKanalId;
        g_FILTER_KANAL_NAZ = ui->txtKanalProdaje->text().toStdString();
        g_FILTER_ORGJED_ID = m_iOrganizacijskaJedinicaId;
        g_FILTER_ORGJED_NAZ = ui->txtOrganizacijskaJedinica->text().toStdString();
        g_FILTER_KORISNIK_ID = "0";
        g_FILTER_KORISNIK_NAZ = "";

        this->close();
    }
}

void FrmKanalProdaje::on_btnKanalProdaje_clicked()
{

}

void FrmKanalProdaje::on_btnFilter_clicked()
{
    m_KanalProdajeMode = KanalProdajeFilter;
    popuniZaPregledzahtjeva();
}

void FrmKanalProdaje::on_btnKorisnik_clicked()
{
    m_KanalProdajeMode = KanalProdajeKorisnik;
    popuniZaKanalProdaje();
}

void FrmKanalProdaje::on_btnSviKorisnici_clicked()
{
    m_SifranikMode = SifarnikModeSviKorisnici;
    popuniSveKorisnike();
}

void FrmKanalProdaje::on_txtRegija_textEdited(const QString &UNUSED(arg1))
{
    popuniRegiju();
}

void FrmKanalProdaje::on_txtZupanija_textEdited(const QString &UNUSED(arg1))
{
    popuniZupaniju();
}

void FrmKanalProdaje::on_txtKanalProdaje_textEdited(const QString &UNUSED(arg1))
{
    popuniKanalProdaje();
}

void FrmKanalProdaje::on_txtOrganizacijskaJedinica_textEdited(const QString &UNUSED(arg1))
{
    popuniOrganizacijskuJedinicu();
}

void FrmKanalProdaje::on_lineEdit_textEdited(const QString &UNUSED(arg1))
{

}

void FrmKanalProdaje::on_treeSifre_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    switch(m_SifranikMode)
    {
        case SifarnikModeNone:
        {
            return;
            break;
        }
        case SifarnikModeRegija:
        {
            m_iRegijaId = item->text(0).toInt();
            ui->txtRegija->setText(item->text(1));
            ui->txtZupanija->setFocus();
            popuniZupaniju();
            break;
        }
        case SifarnikModeZupanija:
        {
            m_iZupanijaId = item->text(0).toInt();
            ui->txtZupanija->setText(item->text(1));
            ui->txtKanalProdaje->setFocus();
            popuniKanalProdaje();
            break;
        }
        case SifarnikModeKanalProdaje:
        {
            m_iKanalId = item->text(0).toInt();
            ui->txtKanalProdaje->setText(item->text(1));
            ui->txtOrganizacijskaJedinica->setFocus();
            popuniOrganizacijskuJedinicu();
            break;
        }
        case SifarnikModeOrganizacijskaJedinica:
        {
            m_iOrganizacijskaJedinicaId = item->text(0).toInt();
            ui->txtOrganizacijskaJedinica->setText(item->text(1));
            ui->txtKorisnik->setFocus();
            popuniKorisnika();
            break;
        }
        case SifarnikModeKorisnik:
        {
            m_strKorisdikId = item->text(0).toStdString();
            ui->txtKorisnik->setText(item->text(1));
            ui->lblOpis->setFocus();
            break;
        }
        case SifarnikModeSviKorisnici:
    {
        m_strKorisdikId = item->text(0).toStdString();
        ui->txtKorisnik->setText(item->text(1));
        ui->lblOpis->setFocus();
        popuniKorisnika(m_strKorisdikId);
        break;
    }
        default :
        {
            return;
            break;
        }
    }

}

}



