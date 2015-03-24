#include "frmmdm1.h"
#include "ui_frmmdm1.h"
#include "itos.h"

namespace Stranka {
// [ Class Contructors ]
FrmMdm1::FrmMdm1(const string strOib, const unsigned int iKupacId, const unsigned int iMdmId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmMdm1)
{
    ui->setupUi(this);

    m_strOib = strOib;
    m_iKupacId = iKupacId;
    m_iMdmId = iMdmId;

    initForm();

    if(m_strOib.length() > 0)
    {
        m_MdmMode = TraziOib;
        ui->txtFilter->setText(QString::fromStdString(m_strOib));
        ui->lblFilterTitle->setText(tr("OIB"));
        popuniMdmOib();
    }
    else if(m_iMdmId != 0)
    {
        m_MdmMode = TraziMdmId;
        ui->txtFilter->setText(QString::number(m_iMdmId));
        ui->lblFilterTitle->setText(tr("MDM ID"));
        popuniMdmMdmId();
    }
    else if(m_iKupacId != 0)
    {
        m_MdmMode = TraziKupacId;
        ui->txtFilter->setText(QString::number(m_iKupacId));
        ui->lblFilterTitle->setText(tr("KUPAC ID"));
        popuniMdmKupacId();
    }
}

FrmMdm1::FrmMdm1(const string strOib, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmMdm1)
{
    ui->setupUi(this);

    m_strOib = strOib;
    m_MdmMode = TraziOib;
    ui->txtFilter->setText(QString::fromStdString(m_strOib));
    ui->lblFilterTitle->setText(tr("OIB"));

    initForm();
}

FrmMdm1::FrmMdm1(const unsigned int iKupacId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmMdm1)
{
    ui->setupUi(this);

    m_iKupacId = iKupacId;
    m_MdmMode = TraziKupacId;
    ui->txtFilter->setText(QString::number(m_iKupacId));
    ui->lblFilterTitle->setText(tr("KUPAC ID"));

    initForm();
}

FrmMdm1::~FrmMdm1()
{
    delete ui;
}

// [ Private Member Functions ]
void FrmMdm1::initForm()
{
    m_iconAdressValid.addFile(QString::fromUtf8(":/InDonat/Forms/images/NODE_7_10x10.png"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconZuti.addFile(QString::fromUtf8(":/InDonat/Forms/images/zuti.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconZeleni.addFile(QString::fromUtf8(":/InDonat/Forms/images/zeleni.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconCrveni.addFile(QString::fromUtf8(":/InDonat/Forms/images/crveni.JPG"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconTransparent.addFile(QString::fromUtf8(":/InDonat/Forms/images/transparet_10x10.png"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);

    ui->treeMdmStranke->hideColumn(0);
    ui->treeMdmStranke->hideColumn(3);
    ui->treeMdmStranke->setColumnWidth(1, 450);
}

void FrmMdm1::clearFormData()
{
    ui->treeMdmStranke->clear();
    ui->treeMdmStranke_2->clear();
}

void FrmMdm1::popuniMdmOib()
{
    if(m_strOib.length() == 0)
    {
        return;
    }

    setCursor(Qt::BusyCursor);

    clearFormData();

    // [1. clear temp tables]
    string strSqlStatement;
    strSqlStatement.append("DELETE FROM TMP_MDM_CUSTOMER");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STRANKE");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_ULOGE_STRANAKA");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STR_ADRESE");
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

    // [2. MDM search for customer]
    strSqlStatement.clear();
    strSqlStatement.append("BEGIN PKG_MDM_INTF.SEARCH_CUSTOMER(:P_OIB,:P_RESP_CODE,:P_MESSAGE); END;");
    sqlStatement->setSQL(strSqlStatement);

    string strResponseCode;
    string strResponseMessage;

    try
    {
        sqlStatement->setString(1, m_strOib);
        sqlStatement->registerOutParam(2, OCCISTRING, 2000);
        sqlStatement->registerOutParam(3, OCCISTRING, 2000);
        sqlStatement->executeUpdate();
        strResponseCode = sqlStatement->getString(2);
        strResponseMessage = sqlStatement->getString(3);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    // [3. get MDM customer results]
    strSqlStatement.clear();
    strSqlStatement.append("SELECT MDM_ID, CUSTOMER_NAME, NVL(MDM_STATUS, 'NIJE ODREÐEN'), ADR_ZIP_CODE||' '||ADR_CITY||', '||ADR_STREET_NAME||' '||ADR_STREET_NUMBER ADRESA ");
    strSqlStatement.append("FROM TMP_MDM_CUSTOMER ORDER BY 2, 3 ");
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listMdmCustomer;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemMdmCustomer = new QTreeWidgetItem();
            itemMdmCustomer->setText(0, QString::fromStdString(rs->getString(1)));
            itemMdmCustomer->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(4)));
            if("NIJE ODREÐEN" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconAdressValid);
                itemMdmCustomer->setText(3, tr("0"));
            }
            else if("OK" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconZeleni);
                itemMdmCustomer->setText(3, tr("1"));
            }
            else if("DIRTY" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconZuti);
                itemMdmCustomer->setText(3, tr("2"));
            }
            else if("INVALID" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconCrveni);
                itemMdmCustomer->setText(3, tr("3"));
            }
            listMdmCustomer.append(itemMdmCustomer);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }


    if(!listMdmCustomer.empty())
    {
        ui->treeMdmStranke->insertTopLevelItems(0, listMdmCustomer);
        ui->treeMdmStranke->setCurrentItem(listMdmCustomer.first());
        ui->treeMdmStranke->expandAll();
//        ui->treeMdmStranke->collapseAll();

        popuniMdmUloge(listMdmCustomer.first()->text(0).toUInt());
    }
    else
    {
        QMessageBox::information(this, tr("DONAT - MDM search"),
                                       tr("MDM - Stranka sa traenim OIB_om ne postoji"),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    setCursor(Qt::ArrowCursor);
}
void FrmMdm1::popuniMdmKupacId()
{
    if(m_iKupacId == 0)
    {
        return;
    }

    setCursor(Qt::BusyCursor);

    clearFormData();

    // [1. clear temp tables]
    string strSqlStatement;
    strSqlStatement.append("DELETE FROM TMP_MDM_CUSTOMER");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STRANKE");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_ULOGE_STRANAKA");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STR_ADRESE");
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

    // [2. MDM search for customer]
    strSqlStatement.clear();
    strSqlStatement.append("BEGIN PKG_MDM_INTF.GET_CUSTOMER(:P_CUSTOMER_ID,:P_RESP_CODE,:P_MESSAGE); END;");
    sqlStatement->setSQL(strSqlStatement);

    string strResponseCode;
    string strResponseMessage;

    try
    {
        sqlStatement->setUInt(1, m_iKupacId);
        sqlStatement->registerOutParam(2, OCCISTRING, 2000);
        sqlStatement->registerOutParam(3, OCCISTRING, 2000);
        sqlStatement->executeUpdate();
        strResponseCode = sqlStatement->getString(2);
        strResponseMessage = sqlStatement->getString(3);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    // [3. get MDM customer results]
    strSqlStatement.clear();
    strSqlStatement.append("SELECT ULSTRANKE_ID, FORMATIRANI_NAZIV, NVL(MDM_STATUS, 'NIJE ODREÐEN'), FORMATIRANA_ADRESA ");
    strSqlStatement.append("FROM MDM_STR_ADRESE WHERE TULSTRANKE_ID = 0 ");
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listMdmCustomer;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemMdmCustomer = new QTreeWidgetItem();
            itemMdmCustomer->setText(0, QString::fromStdString(rs->getString(1)));
            itemMdmCustomer->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(4)));
            if("NIJE ODREÐEN" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconAdressValid);
                itemMdmCustomer->setText(3, tr("0"));
            }
            else if("OK" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconZeleni);
                itemMdmCustomer->setText(3, tr("1"));
            }
            else if("DIRTY" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconZuti);
                itemMdmCustomer->setText(3, tr("2"));
            }
            else if("INVALID" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconCrveni);
                itemMdmCustomer->setText(3, tr("3"));
            }
            listMdmCustomer.append(itemMdmCustomer);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(!listMdmCustomer.empty())
    {
        ui->treeMdmStranke->insertTopLevelItems(0, listMdmCustomer);
        ui->treeMdmStranke->setCurrentItem(listMdmCustomer.first());
        ui->treeMdmStranke->expandAll();
//        ui->treeMdmStranke->collapseAll();

        popuniMdmUloge(listMdmCustomer.first()->text(0).toUInt());
    }
    else
    {
        QMessageBox::information(this, tr("DONAT - MDM search"),
                                       tr("MDM - Stranka sa traenim OIB_om ne postoji"),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    setCursor(Qt::ArrowCursor);
}
void FrmMdm1::popuniMdmMdmId()
{
    if(m_iMdmId != 0)
    {
        return;
    }

    setCursor(Qt::BusyCursor);

    clearFormData();

    // [1. clear temp tables]
    string strSqlStatement;
    strSqlStatement.append("DELETE FROM TMP_MDM_CUSTOMER");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STRANKE");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_ULOGE_STRANAKA");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STR_ADRESE");
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

    // [2. MDM search for customer]
    strSqlStatement.clear();
    strSqlStatement.append("BEGIN PKG_MDM_INTF.GET_CUSTOMER_TREE(:P_MDM_ID,:P_RESP_CODE,:P_MESSAGE); END;");
    sqlStatement->setSQL(strSqlStatement);

    string strResponseCode;
    string strResponseMessage;

    try
    {
        sqlStatement->setUInt(1, m_iMdmId);
        sqlStatement->registerOutParam(2, OCCISTRING, 2000);
        sqlStatement->registerOutParam(3, OCCISTRING, 2000);
        sqlStatement->executeUpdate();
        strResponseCode = sqlStatement->getString(2);
        strResponseMessage = sqlStatement->getString(3);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    // [3. get MDM customer results]
    strSqlStatement.clear();
    strSqlStatement.append("SELECT ULSTRANKE_ID, FORMATIRANI_NAZIV, NVL(MDM_STATUS, 'NIJE ODREÐEN'), FORMATIRANA_ADRESA ");
    strSqlStatement.append("FROM MDM_STR_ADRESE WHERE TULSTRANKE_ID = 0 ");
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listMdmCustomer;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemMdmCustomer = new QTreeWidgetItem();
            itemMdmCustomer->setText(0, QString::fromStdString(rs->getString(1)));
            itemMdmCustomer->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(4)));
            if("NIJE ODREÐEN" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconAdressValid);
                itemMdmCustomer->setText(3, tr("0"));
            }
            else if("OK" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconZeleni);
                itemMdmCustomer->setText(3, tr("1"));
            }
            else if("DIRTY" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconZuti);
                itemMdmCustomer->setText(3, tr("2"));
            }
            else if("INVALID" == rs->getString(3))
            {
                itemMdmCustomer->setIcon(2, m_iconCrveni);
                itemMdmCustomer->setText(3, tr("3"));
            }
            listMdmCustomer.append(itemMdmCustomer);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }


    if(!listMdmCustomer.empty())
    {
        ui->treeMdmStranke->insertTopLevelItems(0, listMdmCustomer);
        ui->treeMdmStranke->setCurrentItem(listMdmCustomer.first());
        ui->treeMdmStranke->expandAll();
//        ui->treeMdmStranke->collapseAll();

        popuniMdmUloge(listMdmCustomer.first()->text(0).toUInt());
   }
    else
    {
        QMessageBox::information(this, tr("DONAT - MDM search"),
                                       tr("MDM - Stranka sa traenim OIB_om ne postoji"),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    setCursor(Qt::ArrowCursor);
}
void FrmMdm1::popuniMdmUloge(const unsigned int iMdmId)
{
    setCursor(Qt::BusyCursor);

    ui->treeMdmStranke_2->clear();

    // [1. clear temp tables]
    string strSqlStatement;
    strSqlStatement.append("DELETE FROM TMP_STRANKE");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_ULOGE_STRANAKA");
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

    strSqlStatement.clear();
    strSqlStatement.append("DELETE FROM TMP_STR_ADRESE");
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

    // [2. MDM search for customer]
    strSqlStatement.clear();
    strSqlStatement.append("BEGIN PKG_MDM_INTF.GET_CUSTOMER_TREE(:P_MDM_ID,:P_RESP_CODE,:P_MESSAGE); END;");
    sqlStatement->setSQL(strSqlStatement);

    string strResponseCode;
    string strResponseMessage;

    try
    {
        sqlStatement->setUInt(1, iMdmId);
        sqlStatement->registerOutParam(2, OCCISTRING, 2000);
        sqlStatement->registerOutParam(3, OCCISTRING, 2000);
        sqlStatement->executeUpdate();
        strResponseCode = sqlStatement->getString(2);
        strResponseMessage = sqlStatement->getString(3);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    // [3. get MDM customer results]
    strSqlStatement.clear();
    strSqlStatement.append("SELECT ULSTRANKE_ID, ULSTRANKE_NAD_ID, TULSTRANKE_ID, NAZIV_ULSTR, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, NVL(SOURCE, 'xxx'), ");
    strSqlStatement.append("NVL(MDM_STATUS, 'NIJE ODREÐEN'), NAZIV1, NVL(NAZIV2, '') ");
    strSqlStatement.append("FROM MDM_STR_ADRESE ORDER BY TULSTRANKE_ID,FORMATIRANI_NAZIV ");
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listMdmCustomer;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemMdmCustomer = new QTreeWidgetItem();
            itemMdmCustomer->setText(0, QString::fromStdString(rs->getString(4)) + tr(" - ") + QString::fromStdString(rs->getString(1)) + tr(" - ") + QString::fromStdString(rs->getString(5)) + tr(" - ") + QString::fromStdString(rs->getString(6)) + tr(" (") + QString::fromStdString(rs->getString(7)) + tr(")"));
//            itemMdmCustomer->setText(1, QString::fromStdString(rs->getString(2) + " ... " + rs->getString(4)));
//            if("NIJE ODREÐEN" == rs->getString(8))
//            {
//                itemMdmCustomer->setIcon(2, m_iconAdressValid);
//            }
//            else if("OK" == rs->getString(8))
//            {
//                itemMdmCustomer->setIcon(2, m_iconZeleni);
//            }
//            else if("DIRTY" == rs->getString(8))
//            {
//                itemMdmCustomer->setIcon(2, m_iconZuti);
//            }
//            else if("INVALID" == rs->getString(8))
//            {
//                itemMdmCustomer->setIcon(2, m_iconCrveni);
//            }
            listMdmCustomer.append(itemMdmCustomer);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }


    if(!listMdmCustomer.empty())
    {
        ui->treeMdmStranke_2->insertTopLevelItems(0, listMdmCustomer);
        ui->treeMdmStranke_2->setCurrentItem(listMdmCustomer.first());
        ui->treeMdmStranke_2->expandAll();
//        ui->treeMdmStranke_2->collapseAll();
    }
    else
    {
        QMessageBox::information(this, tr("DONAT - MDM search"),
                                       tr("MDM - Stranka nema uloga!"),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    setCursor(Qt::ArrowCursor);
}

// [ Event Handlers ]
void FrmMdm1::on_btnTrazi_clicked()
{
    switch (m_MdmMode)
    {
        case TraziOib:
            {
                m_strOib = ui->txtFilter->text().toStdString();
                popuniMdmOib();
                break;
            }
        case TraziKupacId:
            {
                m_iKupacId = ui->txtFilter->text().toUInt();
                popuniMdmKupacId();
                break;
            }
        case TraziMdmId:
            {
                m_iMdmId = ui->txtFilter->text().toUInt();
                popuniMdmMdmId();
                break;
            }
        default:
            break;
    }
}

void FrmMdm1::on_btnOib_clicked()
{
    m_MdmMode = TraziOib;
    ui->txtFilter->setText(QString::fromStdString(m_strOib));
    ui->lblFilterTitle->setText(tr("OIB"));
}

void FrmMdm1::on_btnKupacId_clicked()
{
    m_MdmMode = TraziKupacId;
    ui->txtFilter->setText(QString::number(m_iKupacId));
    ui->lblFilterTitle->setText(tr("KUPAC ID"));
}

void FrmMdm1::on_btnMdmId_clicked()
{
    m_MdmMode = TraziMdmId;
    ui->txtFilter->setText(QString::number(m_iMdmId));
    ui->lblFilterTitle->setText(tr("MDM ID"));
}

void FrmMdm1::on_btnValidirajMdm_clicked()
{

}

void FrmMdm1::on_btnBillingAccountPovezivanje_clicked()
{

}

void FrmMdm1::on_treeMdmStranke_itemClicked(QTreeWidgetItem *item, int UNUSED(column))
{
    unsigned int iMdmId = item->text(0).toUInt();
    popuniMdmUloge(iMdmId);
}



}


