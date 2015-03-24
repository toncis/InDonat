#include "frmugovorneobveze.h"
#include "ui_frmugovorneobveze.h"
#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

// [Class Constructors]
FrmUgovorneObveze::FrmUgovorneObveze(
    unsigned int iKupacId,
    unsigned int iGrupaImovineId,
    QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmUgovorneObveze)
{
    ui->setupUi(this);

    ui->tbUgvorneObveze->setColumnWidth(0,80);
    ui->tbUgvorneObveze->setColumnWidth(1,140);
    ui->tbUgvorneObveze->setColumnWidth(2,340);
    ui->tbUgvorneObveze->setColumnWidth(3,90);
    ui->tbUgvorneObveze->setColumnWidth(4,90);
    ui->tbUgvorneObveze->setColumnWidth(5,50);
    ui->tbUgvorneObveze->setColumnWidth(6,80);
    ui->tbUgvorneObveze->setColumnWidth(7,80);
    ui->tbUgvorneObveze->hideColumn(8);

    m_iKupacId = iKupacId;
    m_iGrupaImovineId = iGrupaImovineId;

    popuniKupca(iKupacId);
    if(iGrupaImovineId == 0)
    {
        prikazUgovorneObvezeZaKupca(iKupacId);
    }
    else
    {
        prikazUgovorneObvezeZaGrupuImovine(iGrupaImovineId);
    }
}

/* [Private Member Functions] */
void FrmUgovorneObveze::popuniKupca(unsigned int iKupacId)
{
    if(iKupacId == 0)
        return;

    string strSqlStatement;
    strSqlStatement.append("SELECT FORMATIRANI_NAZIV, FORMATIRANA_ADRESA FROM HIJERARHIJA_STR_ADRESE2 WHERE ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(iKupacId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            QString strKupacNaziv;
            strKupacNaziv.append(QString::fromStdString(rs->getString(1)));
            strKupacNaziv.append(tr(" , "));
            strKupacNaziv.append(QString::fromStdString(rs->getString(2)));
            ui->lblKupacNaziv->setText(strKupacNaziv);
            ui->lblKupacId->setText(QString::number(iKupacId));
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
void FrmUgovorneObveze::prikazUgovorneObvezeZaKupca(unsigned int iKupacId)
{
    if(iKupacId == 0)
        return;

    ui->tbUgvorneObveze->clearContents();
    ui->tbUgvorneObveze->setRowCount(0);

    std::list<RowB_HIJERARHIJA> lstGrupaImovine;

    string strSqlStatement;
    strSqlStatement.append("SELECT TEL_BROJ, TEL_LIN_ID, GIMOVINE_ID FROM B_HIJERARHIJA ");
    strSqlStatement.append("WHERE KUPAC_ID = ");
    strSqlStatement.append(cttl::itos(iKupacId));
    strSqlStatement.append(" AND B1 = 1 AND SLOG_STATUS = 1 ");
    strSqlStatement.append("ORDER BY TEL_BROJ, TEL_LIN_ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            RowB_HIJERARHIJA grupaImovine;;
            grupaImovine.TelBroj = rs->getString(1);
            grupaImovine.TelLinId = rs->getString(2);
            grupaImovine.GrupaImovineId = rs->getUInt(3);
            lstGrupaImovine.push_back(grupaImovine);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    list<RowB_HIJERARHIJA>::const_iterator itGrupaImovine;
    for(itGrupaImovine=lstGrupaImovine.begin(); itGrupaImovine!=lstGrupaImovine.end(); ++itGrupaImovine)
    {
        strSqlStatement.clear();
        strSqlStatement.append("SELECT NVL(NAZIV,'xxxxxxx') NAZIV, NVL(DATUM_POCETKA,'-') DATUM_1, ");
        strSqlStatement.append("NVL(TO_CHAR(DATUM_ISTEKA,'DD.MM.YYYY'),'-') DATUM_2, ");
        strSqlStatement.append("NVL(IND,0) IND,NVL(PENAL,0) IZNOS,NVL(PENAL2,0) IZNOS2 ");
        strSqlStatement.append("FROM PRIKAZ_UG_OBVEZE_NOVI2 WHERE GIMOVINE_ID = ");
        strSqlStatement.append(cttl::itos(itGrupaImovine->GrupaImovineId));
        strSqlStatement.append(" ORDER BY IND DESC");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                int row = ui->tbUgvorneObveze->rowCount();
                ui->tbUgvorneObveze->insertRow(row);
                ui->tbUgvorneObveze->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(itGrupaImovine->TelBroj)));
                ui->tbUgvorneObveze->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(itGrupaImovine->TelLinId)));
                ui->tbUgvorneObveze->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(1))));
                ui->tbUgvorneObveze->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
                ui->tbUgvorneObveze->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
                ui->tbUgvorneObveze->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(rs->getString(4))));
                ui->tbUgvorneObveze->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
                ui->tbUgvorneObveze->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(rs->getString(6))));
                ui->tbUgvorneObveze->setItem(row, 8, new QTableWidgetItem(QString::number(itGrupaImovine->GrupaImovineId)));
            }
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

}
void FrmUgovorneObveze::prikazUgovorneObvezeZaGrupuImovine(unsigned int iGrupaImovineId)
{
    if(iGrupaImovineId == 0)
        return;

    ui->tbUgvorneObveze->clearContents();
    ui->tbUgvorneObveze->setRowCount(0);

    std::list<RowV_GIM_STRUKTURA_SVE> lstGrupaImovine;

    string strSqlStatement;
    strSqlStatement.append("SELECT TIP, ASSET, GIMOVINE_ID, NVL(TEL_BROJ,'-') TEL_BROJ, NVL(KLASA,'-') KLASA ");
    strSqlStatement.append("FROM V_GIM_STRUKTURA_SVE WHERE GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(iGrupaImovineId));
    strSqlStatement.append(" AND ASSET <> 0 ");
    strSqlStatement.append("ORDER BY TIP ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            RowV_GIM_STRUKTURA_SVE grupaImovine;;
            grupaImovine.Tip = rs->getString(1);
            grupaImovine.Asset = rs->getUInt(2);
            grupaImovine.GimovineId = rs->getUInt(3);
            grupaImovine.TelBroj = rs->getString(4);
            grupaImovine.Klasa = rs->getString(5);
            lstGrupaImovine.push_back(grupaImovine);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    list<RowV_GIM_STRUKTURA_SVE>::const_iterator itGrupaImovine;
    for(itGrupaImovine=lstGrupaImovine.begin(); itGrupaImovine!=lstGrupaImovine.end(); ++itGrupaImovine)
    {
        strSqlStatement.clear();
        strSqlStatement.append("SELECT NVL(NAZIV,'xxxxxxx') NAZIV, NVL(DATUM_POCETKA,'-') DATUM_1, ");
        strSqlStatement.append("NVL(TO_CHAR(DATUM_ISTEKA,'DD.MM.YYYY'),'-') DATUM_2, ");
        strSqlStatement.append("NVL(IND,0) IND,NVL(PENAL,0) IZNOS,NVL(PENAL2,0) IZNOS2 ");
        strSqlStatement.append("FROM PRIKAZ_UG_OBVEZE_NOVI2 WHERE GIMOVINE_ID = ");
        strSqlStatement.append(cttl::itos(itGrupaImovine->GimovineId));
        strSqlStatement.append(" ORDER BY IND DESC");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                int row = ui->tbUgvorneObveze->rowCount();
                ui->tbUgvorneObveze->insertRow(row);
                ui->tbUgvorneObveze->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(itGrupaImovine->TelBroj)));
                ui->tbUgvorneObveze->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(itGrupaImovine->Klasa)));
                ui->tbUgvorneObveze->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rs->getString(1))));
                ui->tbUgvorneObveze->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(rs->getString(2))));
                ui->tbUgvorneObveze->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(rs->getString(3))));
                ui->tbUgvorneObveze->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(rs->getString(4))));
                ui->tbUgvorneObveze->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(rs->getString(5))));
                ui->tbUgvorneObveze->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(rs->getString(6))));
                ui->tbUgvorneObveze->setItem(row, 8, new QTableWidgetItem(QString::number(itGrupaImovine->GimovineId)));
            }
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();
}

/* [Event Handlers] */
void FrmUgovorneObveze::on_btnZatvori_clicked()
{
    this->close();
}
void FrmUgovorneObveze::on_btnSveUgovorneObvezeKupca_clicked()
{
    if(ui->lblKupacId->text().isEmpty())
        return;

    prikazUgovorneObvezeZaKupca(m_iKupacId);
}
void FrmUgovorneObveze::on_btnTelefon_clicked()
{
    if(ui->tbUgvorneObveze->selectedItems().isEmpty())
        return;

    QTableWidgetItem *selectedItem = ui->tbUgvorneObveze->selectedItems().first();
    unsigned int iGrupaImovineId = ui->tbUgvorneObveze->item(selectedItem->row(), 8)->text().toUInt();

    prikazUgovorneObvezeZaGrupuImovine(iGrupaImovineId);
}
void FrmUgovorneObveze::on_btnIspis_clicked()
{

}

FrmUgovorneObveze::~FrmUgovorneObveze()
{
    delete ui;
}

}
