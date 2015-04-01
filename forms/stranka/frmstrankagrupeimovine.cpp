//
//  frmstrankegrupeimovine.cpp
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

#include "frmstrankagrupeimovine.h"
#include "ui_frmstrankagrupeimovine.h"
#include "itos.h"

namespace Stranka {

// [Class Constructors]
FrmStrankaGrupeImovine::FrmStrankaGrupeImovine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmStrankaGrupeImovine)
{
    ui->setupUi(this);


    ui->treeKlase->setColumnWidth(0, 30);
    ui->treeKlase->setColumnWidth(1, 318);
    ui->treeKlase->hideColumn(0);
    ui->treeKlase->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeKlase->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->treeAdrese->setColumnWidth(0, 318);
    ui->treeAdrese->setColumnWidth(1, 30);
    ui->treeAdrese->setColumnWidth(2, 30);
    ui->treeAdrese->setColumnWidth(3, 30);
    ui->treeAdrese->setColumnWidth(4, 30);
    ui->treeAdrese->hideColumn(1);
    ui->treeAdrese->hideColumn(2);
    ui->treeAdrese->hideColumn(3);
    ui->treeAdrese->hideColumn(4);
    ui->treeAdrese->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeAdrese->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->treeGrupeImovine->setColumnWidth(0, 318);
    ui->treeGrupeImovine->setColumnWidth(1, 30);
    ui->treeGrupeImovine->setColumnWidth(2, 30);
    ui->treeGrupeImovine->setColumnWidth(3, 30);
    ui->treeGrupeImovine->setColumnWidth(4, 30);
    ui->treeGrupeImovine->setColumnWidth(5, 30);
    ui->treeGrupeImovine->setColumnWidth(6, 30);
    ui->treeGrupeImovine->hideColumn(1);
    ui->treeGrupeImovine->hideColumn(2);
    ui->treeGrupeImovine->hideColumn(3);
    ui->treeGrupeImovine->hideColumn(4);
    ui->treeGrupeImovine->hideColumn(5);
    ui->treeGrupeImovine->hideColumn(6);
    ui->treeGrupeImovine->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeGrupeImovine->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_strSelectedKlasa = "0";
    m_strSelectedMjestoId = "0";
    m_strSelectedUlicaId = "0";

    m_GrupaImovineStatus = GrupaImovineAktivna;

    popuniKlase();
    popuniAdrese();
    popuniGrupeImovine();
}

FrmStrankaGrupeImovine::~FrmStrankaGrupeImovine()
{
    delete ui;
}

// [Private Member Functions]

void FrmStrankaGrupeImovine::popuniKlase()
{
    ui->treeKlase->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT TEL_LIN_ID, COUNT(TEL_LIN_ID) BROJ FROM TEMP_ASSET_FILTER ");
    strSqlStatement.append("WHERE TEL_LIN_ID NOT IN ('HTnet', 'HT net', 'ISP - davatelj Internet usluga') ");
    strSqlStatement.append("AND TEL_LIN_ID IS NOT NULL ");
    strSqlStatement.append("GROUP BY TEL_LIN_ID ORDER BY TEL_LIN_ID DESC ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listKlase;
    QTreeWidgetItem *itemSveKlase = new QTreeWidgetItem();
    itemSveKlase->setText(0, tr("0"));
    itemSveKlase->setText(1, tr("SVE KLASE"));
    listKlase.append(itemSveKlase);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemKlasa = new QTreeWidgetItem();
            QString strLinijaProdukta = QString::fromStdString(rs->getString(1));
            QString strTelCount = QString::fromStdString(rs->getString(2));
            itemKlasa->setText(0, QString::fromStdString(rs->getString(1)));
            itemKlasa->setText(1, strLinijaProdukta + tr("     ... ") +  strTelCount);
            listKlase.append(itemKlasa);
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

    if(!listKlase.empty())
    {
        listKlase.first()->setSelected(true);
        ui->treeKlase->insertTopLevelItems(0, listKlase);
        ui->treeKlase->setCurrentItem(listKlase.first());
        ui->treeKlase->expandAll();

        ui->lblKlasa->setText(tr("SVE KLASE"));
    }
}

void FrmStrankaGrupeImovine::popuniAdrese()
{
    ui->treeAdrese->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT MJESTO_ID, NVL(MIN(MJESTO), 'XXXXXXXXXX') MJESTO FROM TEMP_ASSET_FILTER ");
    strSqlStatement.append("WHERE MJESTO_ID IS NOT NULL ");
    if(m_strSelectedKlasa != "0")
    {
        strSqlStatement.append("AND TEL_LIN_ID ='");
        strSqlStatement.append(m_strSelectedKlasa);
        strSqlStatement.append("' ");
    }
    strSqlStatement.append(" GROUP BY MJESTO_ID ORDER BY MJESTO ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listAdrese;
    QTreeWidgetItem *itemSveAdrese = new QTreeWidgetItem();
    itemSveAdrese->setText(0, tr("SVE ADRESE"));
    itemSveAdrese->setText(1, tr("0"));
    itemSveAdrese->setText(2, tr(""));
    itemSveAdrese->setText(3, tr("0"));
    itemSveAdrese->setText(4, tr(""));
    listAdrese.append(itemSveAdrese);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemKlasa = new QTreeWidgetItem();
            itemKlasa->setText(0, QString::fromStdString(rs->getString(2)));
            itemKlasa->setText(1, QString::fromStdString(rs->getString(1)));
            itemKlasa->setText(2, QString::fromStdString(rs->getString(2)));
            itemKlasa->setText(3, tr("0"));
            itemKlasa->setText(4, tr(""));
            listAdrese.append(itemKlasa);
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

    strSqlStatement.append("SELECT ULICA_ID, NVL(MIN(ULICA), 'XXXXXXXXXX') ULICA, MIN(MJESTO_ID) MJESTO_ID FROM TEMP_ASSET_FILTER ");
    strSqlStatement.append("WHERE ULICA_ID IS NOT NULL AND MJESTO_ID IS NOT NULL ");
    if(m_strSelectedKlasa != "0")
    {
        strSqlStatement.append("AND TEL_LIN_ID ='");
        strSqlStatement.append(m_strSelectedKlasa);
        strSqlStatement.append("' ");
    }
    strSqlStatement.append(" GROUP BY ULICA_ID ORDER BY ULICA ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemUlica = new QTreeWidgetItem();
            itemUlica->setText(0, QString::fromStdString(rs->getString(2)));
            itemUlica->setText(1, QString::fromStdString(rs->getString(3)));
            itemUlica->setText(2, tr(""));
            itemUlica->setText(3, QString::fromStdString(rs->getString(1)));
            itemUlica->setText(4, QString::fromStdString(rs->getString(2)));
            for(int iTreeItem = 0; iTreeItem < listAdrese.size(); ++iTreeItem)
            {
                if(listAdrese.at(iTreeItem)->text(1) == itemUlica->text(1))
                {
                    itemUlica->setText(2, listAdrese.at(iTreeItem)->text(0));
                    listAdrese.at(iTreeItem)->addChild(itemUlica);
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

    if(!listAdrese.empty())
    {
        listAdrese.first()->setSelected(true);
        ui->treeAdrese->insertTopLevelItems(0, listAdrese);
        ui->treeAdrese->setCurrentItem(listAdrese.first());
        ui->treeAdrese->expandAll();

        ui->lblAdresa->clear();
    }

}

void FrmStrankaGrupeImovine::popuniGrupeImovine()
{
    ui->treeGrupeImovine->clear();

    QList<QTreeWidgetItem *> listGrupeImovine;

    string strSqlStatement;
    strSqlStatement.append("SELECT TEL_LIN_ID, COUNT(TEL_LIN_ID) BROJ FROM TEMP_ASSET_FILTER ");
    switch(m_GrupaImovineStatus)
    {
        case GrupaImovineAktivna:
        {
            strSqlStatement.append(" WHERE STATUS_ID = 1 AND SLOG_STATUS = 1 ");
            break;
        }
        case GrupaImovineSuspendiranNaZahtjevKorisnika:
        {
            strSqlStatement.append("  WHERE STATUS_ID > 2 ");
            break;
        }
        case GrupaImovineNova:
        {
            strSqlStatement.append("  WHERE STATUS_ID = 2 ");
            break;
        }
        case GrupaImovineNeaktivna:
        {
            strSqlStatement.append("  WHERE STATUS_ID < 1 AND SLOG_STATUS < 1 ");
            break;
        }
        default:
        {
            break;
        }
    }
    if(m_strSelectedKlasa != "0")
    {
        strSqlStatement.append("AND TEL_LIN_ID ='");
        strSqlStatement.append(m_strSelectedKlasa);
        strSqlStatement.append("' ");
    }
    else
    {
        strSqlStatement.append(" AND TEL_LIN_ID NOT IN ('HTnet', 'HT net', 'ISP - davatelj Internet usluga') ");
    }
    if(m_strSelectedMjestoId != "0")
    {
        strSqlStatement.append(" AND MJESTO_ID = ");
        strSqlStatement.append(m_strSelectedMjestoId);
    }
    if(m_strSelectedUlicaId != "0")
    {
        strSqlStatement.append(" AND ULICA_ID = ");
        strSqlStatement.append(m_strSelectedUlicaId);
    }
    strSqlStatement.append(" GROUP BY TEL_LIN_ID ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemKlasa = new QTreeWidgetItem();
            itemKlasa->setText(0, QString::fromStdString(rs->getString(1)) + tr("     ... ") + QString::fromStdString(rs->getString(2)));
            itemKlasa->setText(1, QString::fromStdString(rs->getString(1)));
            itemKlasa->setText(2, tr(""));
            itemKlasa->setText(3, tr(""));
            itemKlasa->setText(4, tr(""));
            itemKlasa->setText(5, tr(""));
            itemKlasa->setText(6, tr(""));
            listGrupeImovine.append(itemKlasa);
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

    strSqlStatement.append("SELECT BROJAC, GIMOVINE_ID, TEL_BROJ, TEL_LIN_ID, STATUS_ID, SLOG_STATUS FROM TEMP_ASSET_FILTER ");
    switch(m_GrupaImovineStatus)
    {
        case GrupaImovineAktivna:
        {
            strSqlStatement.append(" WHERE STATUS_ID = 1 AND SLOG_STATUS = 1 ");
            break;
        }
        case GrupaImovineSuspendiranNaZahtjevKorisnika:
        {
            strSqlStatement.append("  WHERE STATUS_ID > 2 ");
            break;
        }
        case GrupaImovineNova:
        {
            strSqlStatement.append("  WHERE STATUS_ID = 2 ");
            break;
        }
        case GrupaImovineNeaktivna:
        {
            strSqlStatement.append("  WHERE STATUS_ID < 1 AND SLOG_STATUS < 1 ");
            break;
        }
        default:
        {
            break;
        }
    }
    if(m_strSelectedKlasa != "0")
    {
        strSqlStatement.append("AND TEL_LIN_ID ='");
        strSqlStatement.append(m_strSelectedKlasa);
        strSqlStatement.append("' ");
    }
    else
    {
        strSqlStatement.append(" AND TEL_LIN_ID NOT IN ('HTnet', 'HT net', 'ISP - davatelj Internet usluga') ");
    }
    if(m_strSelectedMjestoId != "0")
    {
        strSqlStatement.append(" AND MJESTO_ID = ");
        strSqlStatement.append(m_strSelectedMjestoId);
    }
    if(m_strSelectedUlicaId != "0")
    {
        strSqlStatement.append(" AND ULICA_ID = ");
        strSqlStatement.append(m_strSelectedUlicaId);
    }
    strSqlStatement.append(" ORDER BY BROJAC ");

    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemGrupaImovine = new QTreeWidgetItem();
            itemGrupaImovine->setText(0, QString::fromStdString(rs->getString(3)) + tr("  ") + QString::fromStdString(rs->getString(4)));
            itemGrupaImovine->setText(1, QString::fromStdString(rs->getString(4)));
            itemGrupaImovine->setText(2, QString::fromStdString(rs->getString(1)));
            itemGrupaImovine->setText(3, QString::fromStdString(rs->getString(2)));
            itemGrupaImovine->setText(4, QString::fromStdString(rs->getString(3)));
            itemGrupaImovine->setText(5, QString::fromStdString(rs->getString(5)));
            itemGrupaImovine->setText(6, QString::fromStdString(rs->getString(6)));
            for(int iTreeItem = 0; iTreeItem < listGrupeImovine.size(); ++iTreeItem)
            {
                if(listGrupeImovine.at(iTreeItem)->text(1) == itemGrupaImovine->text(1))
                {
                    listGrupeImovine.at(iTreeItem)->addChild(itemGrupaImovine);
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

    if(!listGrupeImovine.empty())
    {
        listGrupeImovine.first()->setSelected(true);
        ui->treeGrupeImovine->insertTopLevelItems(0, listGrupeImovine);
        ui->treeGrupeImovine->setCurrentItem(listGrupeImovine.first());
        ui->treeGrupeImovine->expandAll();
    }
}

// [Event Handlers]
void FrmStrankaGrupeImovine::on_btnPrikazi_clicked()
{
    if(SelectedBrojTelefona.length() > 0)
    {
        this->close();
    }
}

void FrmStrankaGrupeImovine::on_btnAktivni_clicked()
{
    m_GrupaImovineStatus = GrupaImovineAktivna;
    popuniGrupeImovine();
}

void FrmStrankaGrupeImovine::on_btnSuspend_clicked()
{
    m_GrupaImovineStatus = GrupaImovineSuspendiranNaZahtjevKorisnika;
    popuniGrupeImovine();
}

void FrmStrankaGrupeImovine::on_btnNovi_clicked()
{
    m_GrupaImovineStatus = GrupaImovineNova;
    popuniGrupeImovine();
}

void FrmStrankaGrupeImovine::on_btnNeaktivni_clicked()
{
    m_GrupaImovineStatus = GrupaImovineNeaktivna;
    popuniGrupeImovine();
}

void FrmStrankaGrupeImovine::on_treeKlase_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    m_strSelectedKlasa = item->text(0).toStdString();
    if(m_strSelectedKlasa == "0")
    {
        ui->lblKlasa->setText(tr("SVE KLASE"));
    }
    else
    {
        ui->lblKlasa->setText(QString::fromStdString(m_strSelectedKlasa));
    }
    popuniAdrese();
    popuniGrupeImovine();
}

void FrmStrankaGrupeImovine::on_treeAdrese_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    m_strSelectedMjestoId = item->text(1).toStdString();
    m_strSelectedUlicaId = item->text(3).toStdString();
    ui->lblAdresa->setText(item->text(2) + tr(" ") + item->text(0));
    popuniGrupeImovine();
}

void FrmStrankaGrupeImovine::on_treeGrupeImovine_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    ui->lblTelefon->setText(item->text(0));

    try
    {
        SelectedGrupaImovineId = item->text(3).toUInt();
    }
    catch(exception& e)
    {
        SelectedGrupaImovineId = 0;
    }

    SelectedBrojTelefona = item->text(5).toStdString();
}

}
