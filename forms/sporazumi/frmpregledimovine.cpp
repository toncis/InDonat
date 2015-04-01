//
//  frmpregledimovine.cpp
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

#include "frmpregledimovine.h"
#include "ui_frmpregledimovine.h"

#include "itos.h"

namespace Sporazumi {

FrmPregledImovine::FrmPregledImovine(unsigned int iGrupaImovineId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPregledImovine)
{
    ui->setupUi(this);
    ui->treeImovina->hideColumn(1);
    ui->treeImovina->hideColumn(2);


    m_iGrupaImovineId = iGrupaImovineId;
    fillImovina(m_iGrupaImovineId);
}

void FrmPregledImovine::fillImovina(unsigned int iGrupaImovineId)
{
    if(iGrupaImovineId == 0)
        return;

	string strSqlStatement;
	strSqlStatement.append("SELECT I.IMOVINA_ID, I.NAD_IMOVINA_ID, P.NAZIV FROM IMOVINA I, PRODUKTI P ");
	strSqlStatement.append("WHERE I.PRODUKT_ID = P.PRODUKT_ID AND GIMOVINE_ID = ");
	strSqlStatement.append(cttl::itos(iGrupaImovineId));
	strSqlStatement.append(" ORDER BY NIVO,IMOVINA_ID ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

	QList<QTreeWidgetItem *> listImovina;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemImovina = new QTreeWidgetItem();
            itemImovina->setText(0, QString::fromStdString(rs->getString(3)));
            itemImovina->setText(1, QString::number(rs->getUInt(1)));
            itemImovina->setText(2, QString::number(rs->getUInt(2)));
            listImovina.append(itemImovina);
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

    if(!listImovina.empty())
    {
        for(int i = 0; i < listImovina.size(); ++i)
        {
             for(int j = 0; j < listImovina.size(); ++j)
             {
                 if(listImovina.at(j)->text(2).toUInt() == listImovina.at(i)->text(1).toUInt() && listImovina.at(j)->text(1).toUInt() != listImovina.at(i)->text(1).toUInt())
                 {
                     listImovina.at(i)->addChild(listImovina.at(j));
                 }
             }
        }

        listImovina.first()->setSelected(true);
        ui->treeImovina->insertTopLevelItems(0, listImovina);
        ui->treeImovina->setCurrentItem(listImovina.first());
        ui->treeImovina->expandAll();
//      ui->treeImovina->collapseAll();
    }

}


FrmPregledImovine::~FrmPregledImovine()
{
    delete ui;
}

} // namespace sporazumi
