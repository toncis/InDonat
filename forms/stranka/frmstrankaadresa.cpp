//
//  frmstrankaadresa.cpp
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

#include "frmstrankaadresa.h"
#include "ui_frmstrankaadresa.h"
#include "itos.h"


namespace Stranka {
// [ Class Contructors ]
FrmStrankaAdresa::FrmStrankaAdresa(const unsigned int iAdresaId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmStrankaAdresa)
{
    ui->setupUi(this);

    m_iAdresaId = iAdresaId;
    if(m_iAdresaId != 0)
    {
        ui->lblAdresaTitle->setText(tr("ADRESA - NOVA"));
        popuniAdresu(m_iAdresaId);
    }
}

FrmStrankaAdresa::~FrmStrankaAdresa()
{
    delete ui;
}

// [ Private Member Functions ]
void FrmStrankaAdresa::popuniAdresu(const unsigned int iAdressaId)
{
    if(iAdressaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT ");
    strSqlStatement.append("    AD.ADRESA_ID, ");
    strSqlStatement.append("    AD.STRANKA_ID, ");
    strSqlStatement.append("    AD.TADRESE_ID, ");
    strSqlStatement.append("    UPPER(ta.naziv) TIP_ADRESE, ");
    strSqlStatement.append("    AD.MJESTO_ID, ");
    strSqlStatement.append("    AD.MJESTO, ");
    strSqlStatement.append("    AD.ULICA_ID, ");
    strSqlStatement.append("    AD.ULICA, ");
    strSqlStatement.append("    AD.KUCNI_BROJ, ");
    strSqlStatement.append("    AD.KBR_DODATAK, ");
    strSqlStatement.append("    AD.POSTA_ID, ");
    strSqlStatement.append("    AD.BROJ_POSTE, ");
    strSqlStatement.append("    AD.POSTA, ");
    strSqlStatement.append("    AD.ZUPANIJA_ID, ");
    strSqlStatement.append("    ZU.NAZIV ZUPANIJA_NAZIV, ");
    strSqlStatement.append("    AD.REGIJA_ID, ");
    strSqlStatement.append("    RE.NAZIV REGIJA_NAZIV, ");
    strSqlStatement.append("    AD.DRZAVA, ");
    strSqlStatement.append("    AD.STATUS_ID ");
    strSqlStatement.append("FROM ");
    strSqlStatement.append("    STR_ADRESE AD, ");
    strSqlStatement.append("    GEO_STRUKTURE ZU, ");
    strSqlStatement.append("    GEO_STRUKTURE RE, ");
    strSqlStatement.append("    TIPOVI_ADRESA ta ");
    strSqlStatement.append("WHERE ");
    strSqlStatement.append("    ADRESA_ID      = ");
    strSqlStatement.append(cttl::itos(iAdressaId));
    strSqlStatement.append("AND AD.ZUPANIJA_ID = ZU.GEO_ID(+) ");
    strSqlStatement.append("AND AD.REGIJA_ID   = RE.GEO_ID(+) ");
    strSqlStatement.append("AND AD.TADRESE_ID = TA.TADRESE_ID(+) ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
              m_iStrankaId = rs->getUInt(2);
              m_iTipAdreseId = rs->getInt(3);
              ui->txtTipAdreseId->setText(QString::number(m_iTipAdreseId));
              ui->txtTipAdreseNaziv->setText(QString::fromStdString(rs->getString(4)));
              m_iMjestoId = rs->getUInt(5);
              ui->txtMjestoId->setText(QString::number(m_iMjestoId));
              ui->txtMjestoNaziv->setText(QString::fromStdString(rs->getString(6)));
              m_iUlicaId = rs->getUInt(7);
              ui->txtUlicaId->setText(QString::number(m_iUlicaId));
              ui->txtUlicaNaziv->setText(QString::fromStdString(rs->getString(8)));
              ui->txtKucniBroj->setText(QString::fromStdString(rs->getString(9)));
              ui->txtKucniBrojDodatak->setText(QString::fromStdString(rs->getString(10)));
              m_iPostaId = rs->getUInt(11);
              ui->txtPostaId->setText(QString::number(m_iPostaId));
//              ui->txtPostaNaziv->setText(QString::fromStdString(rs->getString(12) + " " + rs->getString(13)));
              ui->txtPostaNaziv->setText(QString::fromStdString(rs->getString(13)));
              m_iZupanijaId = rs->getUInt(14);
              ui->txtZupanijaNaziv->setText(QString::fromStdString(rs->getString(15)));
              m_iRegijaId = rs->getUInt(16);
              ui->txtRegijaNaziv->setText(QString::fromStdString(rs->getString(17)));
              ui->txtDrzavaNaziv->setText(QString::fromStdString(rs->getString(18)));
              m_iStatusId = rs->getInt(19);
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


// [ Event Handlers ]
void FrmStrankaAdresa::on_btnPotvrda_clicked()
{

}


void FrmStrankaAdresa::on_treeSifre_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{

}

}
