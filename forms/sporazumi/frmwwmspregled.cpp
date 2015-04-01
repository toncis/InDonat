//
//  frmwwmspregled.cpp
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


#include "frmwwmspregled.h"

#include "itos.h"

namespace Sporazumi {

FrmWwmsPregled::FrmWwmsPregled(unsigned int iSporazumId, int iTipSporazumaId, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // [0]
    createTicketFrame();
    mainLayout->addWidget(m_fraTicket);
    // [1]
    createGridFrame();
    mainLayout->addWidget(m_grdTicket);
    setLayout(mainLayout);

    // Set Form icon
    QIcon frmIcon;
    frmIcon.addFile(QString::fromUtf8(":/InDonat/Forms/images/App.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    setWindowIcon(frmIcon);
    // Set Form Title
    setWindowTitle(tr("DONAT - WWMS - Pregled statusa"));
    setMinimumWidth(886);
    setMinimumHeight(556);

    m_iSporazumId = iSporazumId;
    m_iTipSporazumaId = iTipSporazumaId;
    const bool bSortingEnabled = m_grdTicket->isSortingEnabled();
    m_grdTicket->setSortingEnabled(false);
    popuniWwmsPregled();
    m_grdTicket->setSortingEnabled(bSortingEnabled);

    if(m_grdTicket->rowCount() > 0)
    {
        on_grdTicket_itemPressed(m_grdTicket->item(0, 0));
    }
}

// [ Create Form ]
void FrmWwmsPregled::createTicketFrame()
{
    m_fraTicket = new QFrame();
    m_fraTicket->setContentsMargins(0, 0, 0, 0);
    m_fraTicket->setFrameShape(QFrame::StyledPanel);

    QVBoxLayout *vboxTicketFrameLayout = new QVBoxLayout();
    vboxTicketFrameLayout->setContentsMargins(0, 0, 0, 0);
    vboxTicketFrameLayout->setSpacing(0);
//    vboxTicketFrameLayout->setAlignment(Qt::AlignTop);
    // [0]
    QFrame *fraTicketTitle = new QFrame();
    fraTicketTitle->setContentsMargins(0, 0, 0, 0);
    fraTicketTitle->setFrameStyle(QFrame::Panel | QFrame::Raised);
    QSizePolicy fraTicketTitleSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraTicketTitleSizePolicy.setHorizontalStretch(0);
    fraTicketTitleSizePolicy.setVerticalStretch(0);
    fraTicketTitle->setSizePolicy(fraTicketTitleSizePolicy);
    QHBoxLayout *hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(2, 2, 0, 2);
    hboxLayout1->setSpacing(1);
    QLabel *lblTicketTitle = new QLabel(tr("Ticket"));
    hboxLayout1->addWidget(lblTicketTitle);
    QPushButton *btnExpandFrame1 = new QPushButton();
    btnExpandFrame1->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/ig_menuGreenUp.gif")));
    btnExpandFrame1->setCursor(Qt::PointingHandCursor);
    btnExpandFrame1->setFlat(true);
    QSizePolicy btnExpandFrame1SizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    btnExpandFrame1SizePolicy.setHorizontalStretch(0);
    btnExpandFrame1SizePolicy.setVerticalStretch(0);
    btnExpandFrame1->setSizePolicy(btnExpandFrame1SizePolicy);
    hboxLayout1->addWidget(btnExpandFrame1);
    fraTicketTitle->setLayout(hboxLayout1);
    vboxTicketFrameLayout->addWidget(fraTicketTitle);
    // [1]
    QFrame *fraTicketDate = new QFrame();
    fraTicketDate->setContentsMargins(0, 0, 0, 0);
//    fraTicketDate->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraTicketDateSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraTicketDateSizePolicy.setHorizontalStretch(0);
    fraTicketDateSizePolicy.setVerticalStretch(0);
    fraTicketDate->setSizePolicy(fraTicketDateSizePolicy);
    QHBoxLayout *hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setContentsMargins(8, 4, 8, 4);
    hboxLayout2->setSpacing(1);
    QLabel *lblTicketDatumOdTitle = new QLabel(tr("Datum od :"));
    hboxLayout2->addWidget(lblTicketDatumOdTitle);
    m_txtDatumOd = new QLineEdit();
    m_txtDatumOd->setMaxLength(152);
    m_txtDatumOd->setReadOnly(true);
    hboxLayout2->addWidget(m_txtDatumOd);
    QLabel *lblTicketDatumDoTitle = new QLabel(tr("Datum do :"));
    hboxLayout2->addWidget(lblTicketDatumDoTitle);
    m_txtDatumDo = new QLineEdit();
    m_txtDatumDo->setMaxLength(152);
    m_txtDatumDo->setReadOnly(true);
    hboxLayout2->addWidget(m_txtDatumDo);
    QLabel *lblTicketIdTitle = new QLabel(tr("Id :"));
    hboxLayout2->addWidget(lblTicketIdTitle);
    m_txtTicketId = new QLineEdit();
    m_txtTicketId->setMaxLength(128);
    m_txtTicketId->setReadOnly(true);
    hboxLayout2->addWidget(m_txtTicketId);
    fraTicketDate->setLayout(hboxLayout2);
    vboxTicketFrameLayout->addWidget(fraTicketDate);
    // [2]
    QFrame *fraLine1 = new QFrame();
    fraLine1->setContentsMargins(8, 4, 8, 4);
    fraLine1->setFrameShape(QFrame::StyledPanel);
    fraLine1->setFrameShadow(QFrame::Sunken);
    fraLine1->setMinimumHeight(8);
    QSizePolicy fraLine1SizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    fraLine1SizePolicy.setHorizontalStretch(0);
    fraLine1SizePolicy.setVerticalStretch(0);
    fraLine1->setSizePolicy(fraLine1SizePolicy);
    vboxTicketFrameLayout->addWidget(fraLine1);
    // [3]
    QFrame *fraTicketData = new QFrame();
    fraTicketData->setContentsMargins(0, 0, 0, 0);
//    fraTicketData->setFrameShape(QFrame::StyledPanel);
    QSizePolicy fraTicketDataSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fraTicketDataSizePolicy.setHorizontalStretch(0);
    fraTicketDataSizePolicy.setVerticalStretch(0);
    fraTicketData->setSizePolicy(fraTicketDataSizePolicy);
    QFormLayout *formLayout = new QFormLayout;
    m_txtZadatak = new QLineEdit();
    m_txtStatus = new QLineEdit();
    m_txtPodrucje = new QLineEdit();
    m_txtIzvrsitelj = new QLineEdit();
    m_txtZadatak->setReadOnly(true);
    m_txtStatus->setReadOnly(true);
    m_txtPodrucje->setReadOnly(true);
    m_txtIzvrsitelj->setReadOnly(true);
    formLayout->addRow(tr("&Zadatak :"), m_txtZadatak);
    formLayout->addRow(tr("&Status :"), m_txtStatus);
    formLayout->addRow(tr("&Područje :"), m_txtPodrucje);
    formLayout->addRow(tr("&Izvršitelj :"), m_txtIzvrsitelj);
    fraTicketData->setLayout(formLayout);
    vboxTicketFrameLayout->addWidget(fraTicketData);
    m_fraTicket->setLayout(vboxTicketFrameLayout);
}
void FrmWwmsPregled::createGridFrame()
{
    m_grdTicket = new QTableWidget();
    m_grdTicket->setContentsMargins(4, 4, 0, 0);
    m_grdTicket->setFrameShape(QFrame::StyledPanel);

    // Create headers
    QStringList labels;
    labels << "ZADATAK" << "STATUS" << "DATUM OD" << "DATUM DO" << "PODRUČJE"
           << "WWMS_SIFRA_IZVRSITELJA" << "IZVRŠITELJ" << "TICKET_ID";
    m_grdTicket->setColumnCount(8);
    m_grdTicket->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_grdTicket->setHorizontalHeaderLabels(labels);
    m_grdTicket->horizontalHeader()->setStretchLastSection(false);
    m_grdTicket->setColumnWidth(0, 270);
    m_grdTicket->setColumnWidth(1, 80);
    m_grdTicket->setColumnWidth(2, 120);
    m_grdTicket->setColumnWidth(3, 120);
    m_grdTicket->setColumnWidth(4, 140);
    m_grdTicket->setColumnWidth(6, 155);
    m_grdTicket->hideColumn(5);
    m_grdTicket->hideColumn(7);
    m_grdTicket->verticalHeader()->hide();
//    m_grdTicket->horizontalHeader()->hide();
    m_grdTicket->setAlternatingRowColors(TRUE);
    m_grdTicket->setShowGrid(true);
    m_grdTicket->setSelectionMode(QAbstractItemView::SingleSelection);
    m_grdTicket->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(m_grdTicket,
            SIGNAL(itemPressed(QTableWidgetItem*)),
            this,
            SLOT(on_grdTicket_itemPressed(QTableWidgetItem*)));

}

// [ Private Member Functions ]
void FrmWwmsPregled::popuniWwmsPregled()
{

    string strGrupaImovineIdInSql;
    string strStavkaSporazumaIdInSql;

    string strSqlStatement;
    strSqlStatement.append("SELECT ");
    strSqlStatement.append("  /*+ RULE */ ");
    strSqlStatement.append("  DISTINCT I.GIMOVINE_ID, ");
//    strSqlStatement.append("  VRATI_OZNAKU_I_NAZIV_KLASE(I.GIMOVINE_ID) OZNAKA, ");
//    strSqlStatement.append("  S.SPORAZUM_ID, ");
    strSqlStatement.append("  NVL(S.SRZ_UGOVOR_ID, 0) SRZ_UGOVOR_ID ");
    strSqlStatement.append("FROM ");
    strSqlStatement.append("  STAVKE_SPORAZUMA S, ");
    strSqlStatement.append("  IMOVINA I ");
    strSqlStatement.append("where ");
    strSqlStatement.append(cttl::itos(m_iSporazumId));
    strSqlStatement.append(" IN (S.SPORAZUM_ID, S.SRZ_UGOVOR_ID) AND I.IMOVINA_ID = S.OSN_IMOVINA_ID");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            if(strGrupaImovineIdInSql.empty() == true)
            {
                strGrupaImovineIdInSql.append(cttl::itos(rs->getUInt(1)));
            }
            else
            {
                strGrupaImovineIdInSql.append(", ");
                strGrupaImovineIdInSql.append(cttl::itos(rs->getUInt(1)));
            }

            unsigned int iStavkaSporazumaId = rs->getUInt(2);
            if(iStavkaSporazumaId != 0)
            {
                if(strStavkaSporazumaIdInSql.empty() == true)
                {
                    strStavkaSporazumaIdInSql.append(cttl::itos(iStavkaSporazumaId));
                }
                else
                {
                    strStavkaSporazumaIdInSql.append(", ");
                    strStavkaSporazumaIdInSql.append(cttl::itos(iStavkaSporazumaId));
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

    std::list<string> lstTicketId;
    strSqlStatement.erase();
    if(m_iTipSporazumaId == 1)
    {
        // Zahtjev
      strSqlStatement.append("SELECT ");
      strSqlStatement.append("  /*+ RULE */ ");
//      strSqlStatement.append("  PP2.ID2, ");
//      strSqlStatement.append("  SP.NAZIV STANJE, ");
//      strSqlStatement.append("  PP2.PROCES_ID, ");
//      strSqlStatement.append("  NVL(PP2.PROCES_ID_NAD, 0) PROCES_ID_NAD, ");
      strSqlStatement.append("  NVL(O2.TICKET_ID, 0) TICKET_ID ");
//      strSqlStatement.append("  NVL(O2.PROCES_ID, 0) ORDER_ID, ");
//      strSqlStatement.append("  NVL(O2.WWMS_STATUS, 0)||' '||APPOINTMENT_DATE(O2.TICKET_ID) WWMS_STATUS ");
      strSqlStatement.append("FROM ");
      strSqlStatement.append("  STANJA_PROCESA SP, ");
      strSqlStatement.append("  POSLOVNI_PROCESI PP2, ");
      strSqlStatement.append("  ( ");
      strSqlStatement.append("    SELECT ");
      strSqlStatement.append("      PP.PROCES_ID, ");
      strSqlStatement.append("      PP.ID, ");
      strSqlStatement.append("      PP.ID2, ");
      strSqlStatement.append("      O2.\"TicketId\" TICKET_ID, ");
      strSqlStatement.append("      O2.\"Status\" WWMS_STATUS, ");
      strSqlStatement.append("      \"OrderNumber\" ORDERNUMBER ");
      strSqlStatement.append("    FROM ");
      strSqlStatement.append("      ORDER_2 O2, ");
      strSqlStatement.append("      POSLOVNI_PROCESI PP ");
      strSqlStatement.append("    WHERE ");
      strSqlStatement.append("      PP.PROCES_ID = O2.\"Id\" ");
      strSqlStatement.append("  ) ");
      strSqlStatement.append("  O2, ");
      strSqlStatement.append("  ( ");
      strSqlStatement.append("    SELECT ");
      strSqlStatement.append("      MAX(PROCES_ID) PROCES_ID ");
      strSqlStatement.append("    FROM ");
      strSqlStatement.append("      (POSLOVNI_PROCESI) ");
      strSqlStatement.append("    WHERE ");
      strSqlStatement.append("      TABLICA2 = 'SPORAZUMI' AND ID2 IN (");
      if(strStavkaSporazumaIdInSql.empty() == false)
      {
          strSqlStatement.append(strStavkaSporazumaIdInSql);
          strSqlStatement.append(", ");
      }
      strSqlStatement.append(cttl::itos(m_iSporazumId));
      strSqlStatement.append(") AND ((TABLICA = 'GRUPE_IMOVINE' AND id IN (");
      strSqlStatement.append(strGrupaImovineIdInSql);
      strSqlStatement.append(")) OR TABLICA = 'SPORAZUMI') ");
      strSqlStatement.append("  ) ");
      strSqlStatement.append("  PP ");
      strSqlStatement.append("WHERE ");
      strSqlStatement.append("  PP.PROCES_ID = PP2.PROCES_ID AND SP.STANJE_ID = PP2.STANJE_ID AND O2.ID(+) = PP2.ID ");
      strSqlStatement.append("  AND O2.ORDERNUMBER(+) = TO_CHAR(");
      strSqlStatement.append(cttl::itos(m_iSporazumId));
      strSqlStatement.append(")");

    }
    else
    {
        // Ugovor
        strSqlStatement.append("SELECT ");
        strSqlStatement.append("  /*+ RULE */ ");
//        strSqlStatement.append("  PP2.ID2, ");
//        strSqlStatement.append("  SP.NAZIV STANJE, ");
//        strSqlStatement.append("  PP2.PROCES_ID, ");
//        strSqlStatement.append("  NVL(PP2.PROCES_ID_NAD, 0) PROCES_ID_NAD, ");
        strSqlStatement.append("  NVL(O2.TICKET_ID, 0) TICKET_ID ");
//        strSqlStatement.append("  NVL(O2.PROCES_ID, 0) ORDER_ID, ");
//        strSqlStatement.append("  NVL(O2.WWMS_STATUS, 0)||' '||APPOINTMENT_DATE(O2.TICKET_ID) WWMS_STATUS ");
        strSqlStatement.append("FROM ");
        strSqlStatement.append("  STANJA_PROCESA SP, ");
        strSqlStatement.append("  POSLOVNI_PROCESI PP2, ");
        strSqlStatement.append("  ( ");
        strSqlStatement.append("    SELECT ");
        strSqlStatement.append("      PP.PROCES_ID, ");
        strSqlStatement.append("      PP.ID, ");
        strSqlStatement.append("      PP.ID2, ");
        strSqlStatement.append("      O2.\"TicketId\" TICKET_ID, ");
        strSqlStatement.append("      O2.\"Status\" WWMS_STATUS, ");
        strSqlStatement.append("      \"OrderNumber\" ORDERNUMBER ");
        strSqlStatement.append("    FROM ");
        strSqlStatement.append("      ORDER_2 O2, ");
        strSqlStatement.append("      POSLOVNI_PROCESI PP ");
        strSqlStatement.append("    WHERE ");
        strSqlStatement.append("      PP.PROCES_ID = O2.\"Id\" ");
        strSqlStatement.append("  ) ");
        strSqlStatement.append("  O2, ");
        strSqlStatement.append("  ( ");
        strSqlStatement.append("    SELECT ");
        strSqlStatement.append("      MAX(PROCES_ID) PROCES_ID ");
        strSqlStatement.append("    FROM ");
        strSqlStatement.append("      (POSLOVNI_PROCESI) ");
        strSqlStatement.append("    WHERE ");
        strSqlStatement.append("      TABLICA2 = 'SPORAZUMI' AND ID2 IN (");
        if(strStavkaSporazumaIdInSql.empty() == false)
        {
            strSqlStatement.append(strStavkaSporazumaIdInSql);
            strSqlStatement.append(", ");
        }
        strSqlStatement.append(cttl::itos(m_iSporazumId));
        strSqlStatement.append(") AND ((TABLICA = 'GRUPE_IMOVINE' AND id IN (");
        strSqlStatement.append(strGrupaImovineIdInSql);
        strSqlStatement.append(")) OR TABLICA = 'SPORAZUMI') ");
        strSqlStatement.append("  ) ");
        strSqlStatement.append("  PP ");
        strSqlStatement.append("WHERE ");
        strSqlStatement.append("  PP.PROCES_ID = PP2.PROCES_ID AND SP.STANJE_ID = PP2.STANJE_ID ");
        strSqlStatement.append("  AND O2.ID(+) = PP2.ID AND O2.ID2(+) = TO_CHAR(");
        strSqlStatement.append(cttl::itos(m_iSporazumId));
        strSqlStatement.append(")");
    }
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            string strTicketId = rs->getString(1);
            if(strTicketId != "0")
            {
                lstTicketId.push_back(strTicketId);
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

    list<string>::const_iterator itTicketId;

    for(itTicketId=lstTicketId.begin(); itTicketId!=lstTicketId.end(); ++itTicketId)
    {
        popuniWwmsTicket(*itTicketId);
    }
}
void FrmWwmsPregled::popuniWwmsTicket(string strTicketId)
{
    unsigned int iTicketId;
    if(cttl::str2int(iTicketId, strTicketId) == false)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("BEGIN PUNI_WWMS_STATUS_TEMP(:nTicket_id); END;");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setUInt(1, iTicketId);
        sqlStatement->executeUpdate();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    strSqlStatement.erase();
    strSqlStatement.append("SELECT ");
    strSqlStatement.append("  ZADATAK, ");
    strSqlStatement.append("  STATUS, ");
    strSqlStatement.append("  VRIJEME_STVARANJA, ");
    strSqlStatement.append("  VRIJEME_ZAVRSETKA, ");
    strSqlStatement.append("  TEHNICKO_PODRUCJE, ");
    strSqlStatement.append("  WWMS_SIFRA_IZVRSITELJA, ");
    strSqlStatement.append("  IZVRSITELJ ");
    strSqlStatement.append("FROM ");
    strSqlStatement.append("  WWMS_STATUS_TEMP ");
    strSqlStatement.append("WHERE(TT_VALID_TO > SYSDATE) AND NVL(E_VALID_TO, SYSDATE + 1) > SYSDATE AND TF_VALID_TO > sysdate ");
    strSqlStatement.append("ORDER BY ");
    strSqlStatement.append("  TASK_NUMBER DESC");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int row = m_grdTicket->rowCount();
            m_grdTicket->insertRow(row);
            m_grdTicket->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(rs->getString(1))));
            m_grdTicket->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
            m_grdTicket->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
            m_grdTicket->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(rs->getString(4))));
            m_grdTicket->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
            m_grdTicket->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(rs->getString(6))));
            m_grdTicket->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(rs->getString(7))));
            m_grdTicket->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(strTicketId)));
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
void FrmWwmsPregled::on_grdTicket_itemPressed(QTableWidgetItem* itemTicket)
{
    m_txtZadatak->setText(m_grdTicket->item(itemTicket->row(), 0)->text());
    m_txtStatus->setText(m_grdTicket->item(itemTicket->row(), 1)->text());
    m_txtDatumOd->setText(m_grdTicket->item(itemTicket->row(), 2)->text());
    m_txtDatumDo->setText(m_grdTicket->item(itemTicket->row(), 3)->text());
    m_txtPodrucje->setText(m_grdTicket->item(itemTicket->row(), 4)->text());
    m_txtIzvrsitelj->setText(m_grdTicket->item(itemTicket->row(), 6)->text());
    m_txtTicketId->setText(m_grdTicket->item(itemTicket->row(), 7)->text());
}

FrmWwmsPregled::~FrmWwmsPregled()
{
    m_grdTicket->clear();
}

}   // namespace sporazumi
