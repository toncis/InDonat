//
//  frmstrankafiz.cpp
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

#include "frmstrankafiz.h"
#include "ui_frmstrankafiz.h"
#include "forms/kontakt/frmtipstranke.h"
#include "forms/stranka/frmstrankaadresa.h"
#include "itos.h"

namespace Stranka {

// [Class Constructor]
FrmStrankaFiz::FrmStrankaFiz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmStrankaFiz)
{
    ui->setupUi(this);

    ui->fraWeb->setVisible(true);
    ui->fraSifranik->setVisible(false);
    ui->treeSifarnik->hideColumn(0);
    ui->lblStatusBarText2->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));

    m_bSmijePromjena = false;
    m_SifranikMode = SifarnikModeNone;
}
FrmStrankaFiz::FrmStrankaFiz(unsigned int iStrankaId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmStrankaFiz)
{
    ui->setupUi(this);

    ui->fraWeb->setVisible(false);
    ui->treeSifarnik->hideColumn(0);
    ui->lblStatusBarText2->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));

    m_SifranikMode = SifarnikModeNone;
    m_bSmijePromjena = false;
    m_iStrankaId = iStrankaId;
    popuniStranku();
}


// [Class Memebr Functions]
void FrmStrankaFiz::popuniStranku()
{
    if(m_iStrankaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT * FROM STRANKE WHERE STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtPrezime->setText(QString::fromStdString(rs->getString(2)));
            ui->txtIme->setText(QString::fromStdString(rs->getString(3)));
            m_iTitulaId = rs->getInt(12);
            ui->txtJmbg->setText(QString::fromStdString(rs->getString(7)));
            ui->txtOib->setText(QString::fromStdString(rs->getString(33)));
            ui->txtNapomena->setPlainText(QString::fromStdString(rs->getString(35)));
            ui->txtCreatedBy->setText(QString::fromStdString(rs->getString(28)));
            if(!rs->isNull(30))
            {
//                ui->dateDateCreated->setDate(QDate::fromString(
//                                                 QString::fromStdString(
//                                                     rs->getDate(30).toText("DD.MM.YYYY")),
//                                                 "DD.MM.YYYY"));
                m_dateDatumKreiranja = QDate::fromString(QString::fromStdString(
                                                                    rs->getDate(30).toText("DD.MM.YYYY")),
                                                                    "dd.MM.yyyy");
                ui->dateDateCreated->setDate(m_dateDatumKreiranja);
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

    popuniKupca();
    popuniAdresuStranke();
    popuniDatumRodjenja();
    popuniTitulu();
    provjeraPromjene();
}
void FrmStrankaFiz::popuniKupca()
{
    if(m_iStrankaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT ULSTRANKE_ID FROM HIJERARHIJA_STR_ADRESE WHERE ROOT_STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append("  AND TULSTRANKE_ID IN (1, 11)");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_iKupacId = rs->getUInt(1);
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
void FrmStrankaFiz::popuniAdresuStranke()
{
    if(m_iStrankaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT ADRESA_ID FROM ULOGE_STRANAKA WHERE ROOT_STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append(" AND TULSTRANKE_ID IN (1, 11) ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_iAdresaId = rs->getUInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(m_iAdresaId == 0)
    {
        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
        return;
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT ADRESA_ID, TADRESE_ID, STATUS_ID, NVL(MJESTO,'-') A_MJESTO, NVL(ULICA,'-') A_ULICA, ");
    strSqlStatement.append(" NVL(KUCNI_BROJ||KBR_DODATAK, '0') A_KBR, ");
    strSqlStatement.append(" NVL(BROJ_POSTE||' '||MJESTO||', '||ULICA||' '||KUCNI_BROJ||KBR_DODATAK, '-') ADRESA_NAZ ");
    strSqlStatement.append(" FROM STR_ADRESE WHERE ADRESA_ID = ");
    strSqlStatement.append(cttl::itos(m_iAdresaId));
    strSqlStatement.append(" ORDER BY 1 DESC ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtAdresa->setText(QString::fromStdString(rs->getString(7)));
            m_strMjesto = rs->getString(4);
            m_strUlica = rs->getString(5);
            m_strKucniBroj = rs->getString(6);
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
void FrmStrankaFiz::popuniDatumRodjenja()
{
    if(m_iStrankaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT * FROM STR_ATRIBUTI WHERE STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append("  AND ATRIBUT_ID = 2901 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
//            if(!rs->isNull(7))
//            {
//                ui->dateRodjendan->setDate(QDate::fromString(
//                                                 QString::fromStdString(
//                                                     rs->getDate(7).toText("DD.MM.YYYY")),
//                                                 "DD.MM.YYYY"));
//            }
            m_DateRodjendan = QDate::fromString(QString::fromStdString(rs->getString(8)), "dd.MM.yyyy");
            ui->dateRodjendan->setDate(m_DateRodjendan);
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
void FrmStrankaFiz::popuniTitulu()
{
    if(m_iTitulaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT NAZIV FROM TITULE WHERE TITULA_ID = ");
    strSqlStatement.append(cttl::itos(m_iTitulaId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtTitula->setText(QString::fromStdString(rs->getString(1)));
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
void FrmStrankaFiz::popuniTitule(const string strTitle)
{
    ui->treeSifarnik->clear();
    ui->fraSifranik->setVisible(true);
    ui->fraWeb->setVisible(false);

    m_SifranikMode = SifarnikModeTitule;

    string strSqlStatement;
    strSqlStatement.append("SELECT TITULA_ID, UPPER(NAZIV) FROM TITULE WHERE UPPER(NAZIV) LIKE UPPER('%");
    strSqlStatement.append(strTitle);
    strSqlStatement.append("%') ORDER BY NAZIV");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listTitula;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemTitula = new QTreeWidgetItem();
            itemTitula->setText(0, QString::fromStdString(rs->getString(1)));
            itemTitula->setText(1, QString::fromStdString(rs->getString(2)));
            listTitula.append(itemTitula);
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

    if(!listTitula.empty())
    {
        listTitula.first()->setSelected(true);
        ui->treeSifarnik->insertTopLevelItems(0, listTitula);
        ui->treeSifarnik->setCurrentItem(listTitula.first());
        ui->treeSifarnik->expandAll();
    }

}
void FrmStrankaFiz::popuniSveAdreseStranke()
{
    ui->treeSifarnik->clear();
    ui->fraSifranik->setVisible(true);
    ui->fraWeb->setVisible(false);

    if(m_iStrankaId == 0)
    {
        return;
    }

    m_SifranikMode = SifarnikModeAdrese;

    string strSqlStatement;
    strSqlStatement.append("SELECT ADRESA_ID, ZGRADA_ID, STATUS_ID, ");
    strSqlStatement.append(" NVL(BROJ_POSTE||' '||MJESTO||', '||ULICA||' '||KUCNI_BROJ||KBR_DODATAK, '-') ADRESA_NAZ ");
    strSqlStatement.append(" FROM STR_ADRESE WHERE STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append(" ORDER BY 1 DESC ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listAdresa;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemTitula = new QTreeWidgetItem();
            itemTitula->setText(0, QString::fromStdString(rs->getString(1)));
            itemTitula->setText(1, QString::fromStdString(rs->getString(4)));
            listAdresa.append(itemTitula);
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

    if(!listAdresa.empty())
    {
        listAdresa.first()->setSelected(true);
        ui->treeSifarnik->insertTopLevelItems(0, listAdresa);
        ui->treeSifarnik->setCurrentItem(listAdresa.first());
        ui->treeSifarnik->expandAll();
    }
}

void FrmStrankaFiz::provjeraPromjene()
{
    if(m_iStrankaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT SMIJE_LI_MAT_PROMJENA (");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append(") SMIJE FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(rs->getString(1) == "0")
            {
                m_bSmijePromjena = true;
            }
            else
            {
                m_bSmijePromjena = false;
                ui->lblStatusBarText3->setText(QString::fromStdString(rs->getString(1)));
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
void FrmStrankaFiz::provjeraPaperCLipDocuments()
{
    if(m_iStrankaId == 0)
    {
        return;
    }

    int iBroj = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT COUNT(*) AS BROJ FROM STRANKE_DOKUMENTI WHERE STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            if(!rs->isNull(1))
            {
                iBroj = rs->getInt(1);
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

    if(iBroj > 0)
    {
        ui->lblStatusBarText3->setText(ui->lblStatusBarText3->text() + tr("  Stranka ima digitalne dokumente."));
    }
}

// [EVENT HANDLERS]
void FrmStrankaFiz::on_txtTitula_textEdited(const QString &strTitle)
{
    if(strTitle.isEmpty())
    {
        return;
    }

    if(strTitle.count() < 3)
    {
        return;
    }

    popuniTitule(strTitle.toUpper().toStdString());
}
void FrmStrankaFiz::on_txtAdresa_textEdited(const QString &strAdresa)
{
    if(strAdresa.isEmpty())
    {
        return;
    }

    popuniSveAdreseStranke();
}
void FrmStrankaFiz::on_treeSifarnik_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    switch(m_SifranikMode)
    {
        case SifarnikModeNone:
        {
            return;
            break;
        }
        case SifarnikModeTitule:
        {
            ui->txtTitula->setText(item->text(1));
            break;
        }
        case SifarnikModeAdrese:
        {
            ui->txtAdresa->setText(item->text(1));
            break;
        }
        default :
        {
            return;
            break;
        }
    }
}
void FrmStrankaFiz::on_btnTipStranke_clicked()
{
    // Show Donat Tip Stranke form
    Kontakt::FrmTipStranke *frmTipStranke = new Kontakt::FrmTipStranke(m_iStrankaId, m_iKupacId , this);
    frmTipStranke->exec();
    delete frmTipStranke;
}

void FrmStrankaFiz::on_btnPorez_clicked()
{

}

void FrmStrankaFiz::on_btnAtributi_clicked()
{

}

void FrmStrankaFiz::on_btnNovaAdresa_clicked()
{
    Stranka::FrmStrankaAdresa *frmStrankaAdresa = new Stranka::FrmStrankaAdresa(0, this);
    frmStrankaAdresa->exec();
    delete frmStrankaAdresa;
}

void FrmStrankaFiz::on_btnPomjenaAdrese_clicked()
{
    Stranka::FrmStrankaAdresa *frmStrankaAdresa = new Stranka::FrmStrankaAdresa(m_iAdresaId, this);
    frmStrankaAdresa->exec();
    delete frmStrankaAdresa;
}
void FrmStrankaFiz::on_btnOibPorezna_clicked()
{
    ui->fraSifranik->setVisible(false);
    ui->fraWeb->setVisible(true);

//    ui->webView->setUrl(QUrl(tr("http://oib.oib.hr/SaznajOibWeb/fizickaOsoba.html")));
    ui->webView->load(QUrl(tr("http://oib.oib.hr/SaznajOibWeb/fizickaOsoba.html")));
    ui->webView->show();
}
void FrmStrankaFiz::on_btnFileNet_clicked()
{

}
void FrmStrankaFiz::on_btnMdmProvjeraOib_clicked()
{

}
void FrmStrankaFiz::on_btnSkeniranje_clicked()
{

}

// [Class Destructor]
FrmStrankaFiz::~FrmStrankaFiz()
{
    delete ui;
}

} // Stranka


