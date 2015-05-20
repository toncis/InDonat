//
//  frmkanalprodajekorisnik.cpp
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

#include "frmkanalprodajekorisnik.h"
#include "ui_frmkanalprodajekorisnik.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {
// [ Class Constructor ]
FrmKanalProdajeKorisnik::FrmKanalProdajeKorisnik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKanalProdajeKorisnik)
{
    ui->setupUi(this);

    initForm();
}

FrmKanalProdajeKorisnik::~FrmKanalProdajeKorisnik()
{
    delete ui;
}

// [ Private Member Functions]
void FrmKanalProdajeKorisnik::initForm()
{
    ui->lblKanalProdaje->setText(QString::fromStdString(g_UNIO_KANAL_NAZ));
    ui->lblOrganizacijskaJedninica->setText(QString::fromStdString(g_UNIO_ORGJED_NAZ));
    ui->lblDonatKorisnik->setText(QString::fromStdString(g_UNIO_KORISNIK_NAZ));
    ui->lblRegija->setText(QString::fromStdString(g_UNIO_REGIJA_NAZ));
    ui->lblZupanija->setText(QString::fromStdString(g_UNIO_ZUPANIJA_NAZ));
}

void FrmKanalProdajeKorisnik::popunaKorisnik()
{
    ui->treeKorisnik->clear();

    if(ui->txtFltDonatUser->text().length() < 3)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT DISTINCT KORISNIK_ID, NAZIV FROM V_KANALI_PRODAJE ");
    strSqlStatement.append("WHERE NAZIV LIKE ('%");
    strSqlStatement.append(ui->txtFltDonatUser->text().toUpper().toStdString());
    strSqlStatement.append("%') ORDER BY NAZIV ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listKorisnici;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemKorisnik = new QTreeWidgetItem();
            itemKorisnik->setText(0, QString::fromStdString(rs->getString(1)));
            itemKorisnik->setText(1, QString::fromStdString(rs->getString(2)));
            listKorisnici.append(itemKorisnik);
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

    if(!listKorisnici.empty())
    {
        listKorisnici.first()->setSelected(true);
        ui->treeKorisnik->insertTopLevelItems(0, listKorisnici);
        ui->treeKorisnik->setCurrentItem(listKorisnici.first());
        ui->treeKorisnik->expandAll();
    }
}

void FrmKanalProdajeKorisnik::dohvatiKorisnika(const string strKorisnikId)
{
    if(strKorisnikId.empty() == true)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT KORISNIK_ID, NAZIV, ORGJED_ID, ORG_JEDINICA, REGIJA_ID, LOKACIJA_ID, TORGJED_ID, ");
    strSqlStatement.append("TIP_ORGJED, KANAL_ID, KANAL_PRODAJE FROM V_KANALI_PRODAJE ");
    strSqlStatement.append("WHERE KORISNIK_ID ='");
    strSqlStatement.append(strKorisnikId);
    strSqlStatement.append("' ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_strKORISNIK_ID = rs->getString(1);
            m_strKORISNIK_NAZ = rs->getString(2);
            m_iORGJED_ID = rs->getInt(3);
            m_strORGJED_NAZ = rs->getString(4);
            m_iREGIJA_ID = rs->getInt(5);
            m_iZUPANIJA_ID = rs->getInt(6);
            m_iKANAL_ID = rs->getInt(9);
            m_strKANAL_NAZ =rs->getString(10);
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
    strSqlStatement.append("SELECT /*+ RULE*/ NAZIV FROM GEO_STRUKTURE WHERE GEO_ID = ");
    strSqlStatement.append(cttl::itos(m_iREGIJA_ID));

    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_strREGIJA_NAZ = rs->getString(1);
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
    strSqlStatement.append("SELECT /*+ RULE*/ NAZIV FROM GEO_STRUKTURE WHERE GEO_ID = ");
    strSqlStatement.append(cttl::itos(m_iZUPANIJA_ID));

    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_strZUPANIJA_NAZ = rs->getString(1);
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

    ui->lblKanalProdaje->setText(QString::fromStdString(m_strKANAL_NAZ));
    ui->lblOrganizacijskaJedninica->setText(QString::fromStdString(m_strORGJED_NAZ));
    ui->lblDonatKorisnik->setText(QString::fromStdString(m_strKORISNIK_NAZ));
    ui->lblRegija->setText(QString::fromStdString(m_strREGIJA_NAZ));
    ui->lblZupanija->setText(QString::fromStdString(m_strZUPANIJA_NAZ));
}

// [ Event Handlers ]
void FrmKanalProdajeKorisnik::on_txtFltDonatUser_textEdited(const QString &UNUSED(arg1))
{
    popunaKorisnik();
}

void FrmKanalProdajeKorisnik::on_btnSetLoggedInDonatUser_clicked()
{
    ui->treeKorisnik->clear();
    ui->txtFltDonatUser->clear();


    m_strKORISNIK_ID = g_KORISNIK_ID;
    m_strKORISNIK_NAZ = g_KORISNIK_NAZ;
    m_strKORISNIK_IME = g_KORISNIK_IME;
    m_iORGJED_ID = g_ORGJED_ID;
    m_strORGJED_NAZ = g_ORGJED_NAZ;
    m_iKANAL_ID = g_KANAL_ID;
    m_strKANAL_NAZ = g_KANAL_NAZ;
    m_iREGIJA_ID = g_REGIJA_ID;
    m_strREGIJA_NAZ = g_REGIJA_NAZ;
    m_iZUPANIJA_ID = g_ZUPANIJA_ID;
    m_strZUPANIJA_NAZ = g_ZUPANIJA_NAZ;

    ui->lblKanalProdaje->setText(QString::fromStdString(g_KANAL_NAZ));
    ui->lblOrganizacijskaJedninica->setText(QString::fromStdString(g_ORGJED_NAZ));
    ui->lblDonatKorisnik->setText(QString::fromStdString(g_KORISNIK_NAZ));
    ui->lblRegija->setText(QString::fromStdString(g_REGIJA_NAZ));
    ui->lblZupanija->setText(QString::fromStdString(g_ZUPANIJA_NAZ));
}

void FrmKanalProdajeKorisnik::on_treeKorisnik_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    dohvatiKorisnika(item->text(0).toStdString());
}

void FrmKanalProdajeKorisnik::on_btnPotvrda_clicked()
{
    g_UNIO_KORISNIK_ID = m_strKORISNIK_ID;
    g_UNIO_KORISNIK_NAZ = m_strKORISNIK_NAZ;
    g_UNIO_KORISNIK_IME = m_strKORISNIK_IME;
    g_UNIO_ORGJED_ID = m_iORGJED_ID;
    g_UNIO_ORGJED_NAZ = m_strORGJED_NAZ;
    g_UNIO_KANAL_ID = m_iKANAL_ID;
    g_UNIO_KANAL_NAZ = m_strKANAL_NAZ;
    g_UNIO_REGIJA_ID = m_iREGIJA_ID;
    g_UNIO_REGIJA_NAZ = m_strREGIJA_NAZ;
    g_UNIO_ZUPANIJA_ID = m_iZUPANIJA_ID;
    g_UNIO_ZUPANIJA_NAZ = m_strZUPANIJA_NAZ;

    this->close();
}

}






