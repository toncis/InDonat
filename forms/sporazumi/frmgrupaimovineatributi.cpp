#include "frmgrupaimovineatributi.h"
#include "ui_frmgrupaimovineatributi.h"

#include "itos.h"
#include "ocinumber.h"

namespace Sporazumi {

// [Class Constructors ]
FrmGrupaImovineAtributi::FrmGrupaImovineAtributi(
        unsigned int iGrupaImovineId,
        unsigned int iImovinaId,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmGrupaImovineAtributi)
{
    m_iGrupaImovineId = iGrupaImovineId;
    m_iImovinaId = iImovinaId;

    ui->setupUi(this);

    ui->fraAtributDate->setVisible(false);
    ui->fraImovinaAtributDatumId->setVisible(false);
    ui->lblStatusBarText2->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));

    this->popuniGrupeImovine();

}
FrmGrupaImovineAtributi::FrmGrupaImovineAtributi(
        unsigned int iGrupaImovineId,
        long long iKupacId,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmGrupaImovineAtributi)
{
    m_iGrupaImovineId = iGrupaImovineId;
    m_iKupacId = iKupacId;

    ui->setupUi(this);

    ui->fraAtributDate->setVisible(false);
    ui->fraImovinaAtributDatumId->setVisible(false);
    ui->lblStatusBarText2->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));

    this->popuniGrupeImovine();

}
FrmGrupaImovineAtributi::FrmGrupaImovineAtributi(
        unsigned int iGrupaImovineId,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmGrupaImovineAtributi)
{
    m_iGrupaImovineId = iGrupaImovineId;

    ui->setupUi(this);

    ui->fraAtributDate->setVisible(false);
    ui->fraImovinaAtributDatumId->setVisible(false);
    ui->lblStatusBarText2->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));

    this->popuniGrupeImovine();
}

FrmGrupaImovineAtributi::~FrmGrupaImovineAtributi()
{
    delete ui;
}

// [Private Member Functions ]
//
void FrmGrupaImovineAtributi::popuniGrupeImovine()
{
    string strSqlStatement;
    strSqlStatement.append("SELECT GIMOVINE_ID, B1, B2, TEL_BROJ, TEL_LIN_ID, IMOVINA_ID, ");
    strSqlStatement.append("SLOG_STATUS, TO_CHAR(DATUM_DO, 'DD.MM.RR') DATUM_DO ");
    strSqlStatement.append("FROM B_HIJERARHIJA WHERE GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
//    if(m_iKupacId != 0)
//    {
//        strSqlStatement.append(" AND KUPAC_ID = ");
//        strSqlStatement.append(cttl::itos(m_iKupacId));
//    }
    //strSqlStatement.append(" AND B1>0 AND B2<>9 ");
    strSqlStatement.append(" ORDER BY B1, TEL_BROJ ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
             ui->lblGrupaImovineNaziv->setText(QString::fromStdString(rs->getString(4) + " ... " + rs->getString(5)));
             ui->lblGrupaImovineId->setText(QString::number(m_iGrupaImovineId));
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

    popuniSveImovine();
}
void FrmGrupaImovineAtributi::popuniSveImovine()
{
    if(m_iGrupaImovineId == 0)
    {
        return;
    }

    string strSqlStatement;

    strSqlStatement.append("SELECT I.IMOVINA_ID, I.NAD_IMOVINA_ID, I.STATUS_ID, I.NIVO, ");
    strSqlStatement.append(" NVL(TO_CHAR(I.DATUM_OD,'DD.MM.YYYY'),'-') DATUM_OD, ");
    strSqlStatement.append(" NVL(TO_CHAR(I.DATUM_DO,'DD.MM.YYYY HH24:MI'),'-') DATUM_DO, P.NAZIV ");
    strSqlStatement.append("FROM IMOVINA I, PRODUKTI P ");
    strSqlStatement.append("WHERE I.PRODUKT_ID = P.PRODUKT_ID ");
    strSqlStatement.append(" AND I.STATUS_ID > 0 ");
    strSqlStatement.append(" AND I.NIVO>0 ");
    strSqlStatement.append(" AND GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(m_iGrupaImovineId));
    strSqlStatement.append(" AND P.GPRODUKATA_ID NOT IN (4) ");
    strSqlStatement.append(" ORDER BY NIVO, IMOVINA_ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listImovina;
    string strDatumDo;
    string strDatumOd;
    string strNaziv;
    string strImovinaNaziv;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            strDatumDo = rs->getString(6);
            strDatumOd = rs->getString(5);
            strNaziv = rs->getString(7);
            if(strDatumDo == "-")
            {
                if(strDatumOd == "-")
                {
                    strImovinaNaziv = strNaziv;
                }
                else
                {
                    strImovinaNaziv = strDatumOd + " ... " + strNaziv;
                }
            }
            else
            {
                strImovinaNaziv = strDatumDo + " ... " + strNaziv;
            }

            QTreeWidgetItem *itemImovina = new QTreeWidgetItem();
            itemImovina->setText(0, QString::fromStdString(strImovinaNaziv));
            itemImovina->setText(1, QString::number(rs->getUInt(1)));
            itemImovina->setText(2, QString::number(rs->getUInt(2)));
            itemImovina->setText(3, QString::number(rs->getInt(3)));
            itemImovina->setText(4, QString::number(rs->getInt(4)));
            itemImovina->setText(5, QString::fromStdString(rs->getString(5)));
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
                 if(listImovina.at(j)->text(2).toUInt() == listImovina.at(i)->text(1).toUInt())
                 {
                     listImovina.at(i)->addChild(listImovina.at(j));
                 }
             }
        }

        for(int ii = 0; ii < listImovina.size(); ++ii)
        {
            if(listImovina.at(ii)->text(3).toInt() == 0)
            {
                listImovina.at(ii)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
            }
            else if (listImovina.at(ii)->text(3).toInt() == 2)
            {
                listImovina.at(ii)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/OLOVKA.GIF")));
            }
            else if (listImovina.at(ii)->text(3).toInt() > 4)
            {
                listImovina.at(ii)->setIcon(0, QPixmap(QString::fromUtf8(":/InDonat/Forms/images/LOKOT1.GIF")));
            }

            popuniImovinaAtribute(listImovina.at(ii));
        }

        listImovina.first()->setSelected(true);
        m_iImovinaId = listImovina.first()->text(1).toUInt();
//        m_iImovinaIdStatus = listImovina.first()->text(3).toInt();
        ui->treeImovina->insertTopLevelItems(0, listImovina);
        ui->treeImovina->setCurrentItem(listImovina.first());
        ui->treeImovina->expandAll();
//        ui->treeImovina->collapseAll();
    }


}
void FrmGrupaImovineAtributi::popuniImovinaAtribute(QTreeWidgetItem *itemImovina)
{
    string strSqlStatement;
    strSqlStatement.append("SELECT /*+ RULE */ ATRIBUT_ID, IMOVATR_ID, SHOWN_VALUE, NAZIV, TVRATR_ID, WWMS_NAZIV ");
    strSqlStatement.append("FROM V_IMOVINA_ATR WHERE IMOVINA_ID = ");
    strSqlStatement.append(itemImovina->text(1).toStdString());
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemImovinaAtributi = new QTreeWidgetItem(itemImovina);
            itemImovinaAtributi->setText(0, QString::fromStdString(rs->getString(4)) + tr(" ... ") + QString::fromStdString(rs->getString(3)));
            itemImovinaAtributi->setText(6, QString::number(rs->getUInt(2)));
            itemImovinaAtributi->setText(7, QString::number(rs->getUInt(1)));
            itemImovinaAtributi->setText(8, QString::fromStdString(rs->getString(3)));
            itemImovinaAtributi->setText(9, QString::fromStdString(rs->getString(4)));
            itemImovinaAtributi->setText(10, QString::number(rs->getInt(5)));
            itemImovinaAtributi->setText(11, QString::fromStdString(rs->getString(6)));
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
void FrmGrupaImovineAtributi::popuniDozvoljeneVrijednostiAtributa()
{
//    ui->treeListaVrijesnostiAtributa->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT STAVKA_ID, NAZIV_STAVKE FROM PRODUKTI_ATRIBUTI WHERE ATRIBUT_ID = ");
    strSqlStatement.append(ui->lblAtributId->text().toStdString());
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listVrijednostiAtributa;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemVrijednostAtributa = new QTreeWidgetItem();
            itemVrijednostAtributa->setText(0, QString::number(rs->getUInt(1)));
            itemVrijednostAtributa->setText(1, QString::fromStdString(rs->getString(2)));
            listVrijednostiAtributa.append(itemVrijednostAtributa);
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

    if(listVrijednostiAtributa.count() != 0)
    {
//        listVrijednostiAtributa.first()->setSelected(true);
        ui->treeListaVrijesnostiAtributa->insertTopLevelItems(0, listVrijednostiAtributa);
//        ui->treeListaVrijesnostiAtributa->setCurrentItem(listVrijednostiAtributa.first());
        ui->treeListaVrijesnostiAtributa->expandAll();
//        ui->treeListaVrijesnostiAtributa->collapseAll();
    }
}

// [ Event Handlers]
void FrmGrupaImovineAtributi::on_treeImovina_itemClicked(
        QTreeWidgetItem *itemImovina,
        int UNUSED(column))
{
    setCursor(Qt::BusyCursor);

    if(!itemImovina->text(1).isEmpty())
    {
        // Imovina klik
        ui->lblImovinaId->setText(itemImovina->text(1));
        ui->lblAtributId->clear();
        ui->lblAtribut->clear();
        ui->txtAtribut->clear();
        ui->treeListaVrijesnostiAtributa->clear();
        m_iTipVrsteAtributaId = 0;
        ui->lblImovAtrID1->clear();
        ui->lblImovAtrID2->clear();
//        ui->lblAtribut->setText(itemImovina->text(1));
//        ui->txtImovinaStatus->clear();
//        ui->txtImovinaAktivnaOd->clear();
//        ui->txtImovinaAktivnaDo->clear();
//        ui->txtImovinaSuspendiranaOd->clear();
//        ui->txtImovinaSuspendiranaDo->clear();

//        m_iImovinaId = itemImovina->text(1).toUInt();
//        ui->txtImovinaId->setText(itemImovina->text(1));
//        popuniImovinaStatus();
    }
    else
    {
        // Imovina atribut klik
        ui->lblImovinaId->setText(itemImovina->parent()->text(1));
        ui->lblAtributId->setText(itemImovina->text(7));
        ui->lblAtribut->setText(itemImovina->text(9));
        ui->lblImovAtrID1->setText(itemImovina->text(6));
        ui->lblImovAtrID2->setText(itemImovina->text(6));
        ui->treeListaVrijesnostiAtributa->clear();
        // Text
        if(itemImovina->text(10) == tr("1"))
        {
            ui->txtAtribut->setText(itemImovina->text(8));
            ui->fraAtributDate->setVisible(false);
            ui->fraImovinaAtributDatumId->setVisible(false);
            ui->fraImovinaAtributId->setVisible(true);
            ui->fraAtributEdit->setVisible(true);
            m_iTipVrsteAtributaId = 1;
        }
        // Broj
        else if(itemImovina->text(10) == tr("2"))
        {
            ui->txtAtribut->setText(itemImovina->text(8));
            ui->fraAtributDate->setVisible(false);
            ui->fraImovinaAtributDatumId->setVisible(false);
            ui->fraImovinaAtributId->setVisible(true);
            ui->fraAtributEdit->setVisible(true);
            m_iTipVrsteAtributaId = 2;

        }
        // Lista
        else if(itemImovina->text(10) == tr("3"))
        {
            ui->txtAtribut->setText(itemImovina->text(8));
            ui->fraAtributDate->setVisible(false);
            ui->fraImovinaAtributDatumId->setVisible(false);
            ui->fraImovinaAtributId->setVisible(true);
            ui->fraAtributEdit->setVisible(true);
            m_iTipVrsteAtributaId = 3;
            popuniDozvoljeneVrijednostiAtributa();
        }
        // Datum
        else if(itemImovina->text(10) == tr("4"))
        {
            ui->txtAtribut->setText(itemImovina->text(8));
            ui->dateAtributDate->setDate(QDate::fromString(itemImovina->text(8), "dd.MM.yyyy"));
            ui->fraAtributDate->setVisible(true);
            ui->fraImovinaAtributDatumId->setVisible(true);
            ui->fraImovinaAtributId->setVisible(false);
            ui->fraAtributEdit->setVisible(false);
            m_iTipVrsteAtributaId = 4;
        }

    }
    setCursor(Qt::ArrowCursor);
}
void FrmGrupaImovineAtributi::on_treeListaVrijesnostiAtributa_itemClicked(
        QTreeWidgetItem *itemVrijednostAtributa,
        int UNUSED(column))
{
    ui->txtAtribut->setText(itemVrijednostAtributa->text(1));
    m_strNazivStavke = itemVrijednostAtributa->text(1).toStdString();
    m_iStavkaId = itemVrijednostAtributa->text(0).toUInt();
}
void FrmGrupaImovineAtributi::on_btnPotvrda_clicked()
{
    if(m_iTipVrsteAtributaId == 0)
    {
        return;
    }

    switch (m_iTipVrsteAtributaId) {
    case 1:
        {
            string strSqlStatement;
            strSqlStatement.append("UPDATE IMOVINA_ATR SET TEXT_VALUE = :x, SHOWN_VALUE = :y WHERE IMOVATR_ID = ");
            strSqlStatement.append(ui->lblImovAtrID1->text().toStdString());
            Statement *sqlStatement = g_DonatConn->createStatement();
            sqlStatement->setSQL(strSqlStatement);

            try
            {
                sqlStatement->setString(1, ui->txtAtribut->text().toStdString());
                sqlStatement->setString(2, ui->txtAtribut->text().toStdString());
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

            break;
        }
    case 2:
        {
            string strSqlStatement;
            strSqlStatement.append("UPDATE IMOVINA_ATR SET INT_VALUE = :x, SHOWN_VALUE = :y WHERE IMOVATR_ID = ");
            strSqlStatement.append(ui->lblImovAtrID1->text().toStdString());
            Statement *sqlStatement = g_DonatConn->createStatement();
            sqlStatement->setSQL(strSqlStatement);

            try
            {
                sqlStatement->setInt(1, ui->txtAtribut->text().toInt());
                sqlStatement->setString(2, ui->txtAtribut->text().toStdString());
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

            break;
        }
    case 3:
        {
            string strSqlStatement;
            strSqlStatement.append("UPDATE IMOVINA_ATR SET VALUE_ID = :x, SHOWN_VALUE = :y WHERE IMOVATR_ID = ");
            strSqlStatement.append(ui->lblImovAtrID1->text().toStdString());
            Statement *sqlStatement = g_DonatConn->createStatement();
            sqlStatement->setSQL(strSqlStatement);

            try
            {
                sqlStatement->setInt(1, m_iStavkaId);
                sqlStatement->setString(2, ui->txtAtribut->text().toStdString());
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

            break;
        }
    case 4:
        {
            string strSqlStatement;
            strSqlStatement.append("UPDATE IMOVINA_ATR SET DATE_VALUE = :x, SHOWN_VALUE = :y WHERE IMOVATR_ID = ");
            strSqlStatement.append(ui->lblImovAtrID1->text().toStdString());
            Statement *sqlStatement = g_DonatConn->createStatement();
            sqlStatement->setSQL(strSqlStatement);

            try
            {
                Date datum = Date(g_DonatEnv,
                                      ui->dateAtributDate->date().year(),
                                      ui->dateAtributDate->date().month(),
                                      ui->dateAtributDate->date().day(),
                                      ui->dateAtributDate->time().hour(),
                                      ui->dateAtributDate->time().minute(),
                                      ui->dateAtributDate->time().second());

                sqlStatement->setDate(1, datum);
                sqlStatement->setString(2, ui->txtAtribut->text().toStdString());
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

            break;
        }
    default:
        break;
    }

    ui->lblImovAtrID1->clear();
    ui->lblImovAtrID2->clear();
    ui->lblAtribut->clear();
    ui->dateAtributDate->clear();
    ui->txtAtribut->clear();
    ui->treeImovina->clear();
    ui->treeListaVrijesnostiAtributa->clear();
    this->popuniGrupeImovine();
}

}



