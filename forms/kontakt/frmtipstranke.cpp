#include "frmtipstranke.h"
#include "ui_frmtipstranke.h"

#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

// [ Class Constructors ]
FrmTipStranke::FrmTipStranke(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmTipStranke)
{
    ui->setupUi(this);

    ui->treeSifre->hideColumn(0);

    m_iStrankaId = 0;
    m_SifranikMode = SifarnikModeTipStrankeNone;

    popuniStranku(m_iStrankaId);
}

FrmTipStranke::FrmTipStranke(unsigned int iStrankaId, unsigned int iKupacId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmTipStranke)
{
    ui->setupUi(this);

    ui->treeSifre->hideColumn(0);

    m_iStrankaId = iStrankaId;
    m_iKupacId = iKupacId;
    m_SifranikMode = SifarnikModeTipStrankeNone;

    popuniStranku(m_iStrankaId);
}

FrmTipStranke::FrmTipStranke(unsigned int iStrankaId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmTipStranke)
{
    ui->setupUi(this);

    ui->treeSifre->hideColumn(0);

    m_iStrankaId = iStrankaId;
    m_SifranikMode = SifarnikModeTipStrankeNone;

    popuniStranku(m_iStrankaId);
}


FrmTipStranke::~FrmTipStranke()
{
    delete ui;
}

// [ Member Functions ]
void FrmTipStranke::popuniStranku(const unsigned int iStrankaId)
{
    if (iStrankaId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("    SELECT ");
    strSqlStatement.append("        STRANKA_ID, ");
    strSqlStatement.append("        FORMATIRANI_NAZIV, ");
    strSqlStatement.append("        MBR, ");
    strSqlStatement.append("        T1.TSTRANKE1_ID, ");
    strSqlStatement.append("        UPPER(T1.NAZIV) NAZIV1, ");
    strSqlStatement.append("        T2.TSTRANKE2_ID, ");
    strSqlStatement.append("        UPPER(T2.NAZIV) NAZIV2, ");
    strSqlStatement.append("        T3.TSTRANKE3_ID, ");
    strSqlStatement.append("        UPPER(T3.NAZIV) NAZIV3, ");
    strSqlStatement.append("        MS.MARKETSEGMENT_ID, ");
    strSqlStatement.append("        UPPER(MS.NAZIV) MARKET_NAZIV, ");
    strSqlStatement.append("        OP.TOPOMINJANJA_ID, ");
    strSqlStatement.append("        UPPER(OP.NAZIV) NAZIV_OPOMINJANJA, ");
    strSqlStatement.append("        KP.KREDPROFIL_ID, ");
    strSqlStatement.append("        UPPER(KP.NAZIV) NAZIV_KRED_PROFILA, ");
    strSqlStatement.append("        NAPOMENA ");
    strSqlStatement.append("    FROM ");
    strSqlStatement.append("        STRANKE S, ");
    strSqlStatement.append("        TIPOVI_STRANAKA1 T1, ");
    strSqlStatement.append("        TIPOVI_STRANAKA2 T2, ");
    strSqlStatement.append("        TIPOVI_STRANAKA3 T3, ");
    strSqlStatement.append("        MARKET_SEGMENTI MS, ");
    strSqlStatement.append("        TIPOVI_OPOMINJANJA OP, ");
    strSqlStatement.append("        KREDITNI_PROFILI_STRANKE KP ");
    strSqlStatement.append("    WHERE ");
    strSqlStatement.append("        STRANKA_ID = ");
    strSqlStatement.append(cttl::itos(iStrankaId));
    strSqlStatement.append("        AND S.MARKETSEGMENT_ID = MS.MARKETSEGMENT_ID(+) ");
    strSqlStatement.append("        AND S.TSTRANKE1_ID = T1.TSTRANKE1_ID(+) ");
    strSqlStatement.append("        AND S.TSTRANKE2_ID = T2.TSTRANKE2_ID(+) ");
    strSqlStatement.append("        AND S.TSTRANKE3_ID = T3.TSTRANKE3_ID(+) ");
    strSqlStatement.append("        AND S.TOPOMINJANJA_ID = OP.TOPOMINJANJA_ID(+) ");
    strSqlStatement.append("        AND S.KREDPROFIL_ID = KP.KREDPROFIL_ID(+) ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->lblStrankaId->setText(QString::fromStdString(rs->getString(1)));
            ui->lblStrankaNaziv->setText(QString::fromStdString(rs->getString(2)));
            m_iTipStranke1Id = rs->getInt(4);
            ui->txtTip1->setText(QString::fromStdString(rs->getString(5)));
            m_iTipStranke2Id = rs->getInt(6);
            ui->txtTip2->setText(QString::fromStdString(rs->getString(7)));
            m_iTipStranke3Id = rs->getInt(8);
            ui->txtTip3->setText(QString::fromStdString(rs->getString(9)));
            m_iMarketinskiSegmentId = rs->getInt(10);
            ui->txtSegment->setText(QString::fromStdString(rs->getString(11)));
            m_iTipOpominjanjaId = rs->getInt(12);
            ui->txtOpomena->setText(QString::fromStdString(rs->getString(13)));
            m_iKreditniProfilId = rs->getInt(14);
            ui->txtProfil->setText(QString::fromStdString(rs->getString(15)));
            ui->txtNapomena->setPlainText(QString::fromStdString(rs->getString(16)));
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
bool FrmTipStranke::provjeriSmijeLiMatPromjena(const unsigned int iKupacId)
{
    bool retValue = false;

    if (iKupacId == 0)
    {
        return retValue;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT SMIJE_LI_MAT_PROMJENA (");
    strSqlStatement.append(cttl::itos(iKupacId));
    strSqlStatement.append(") SMIJE FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    string strSmije;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strSmije = rs->getString(1);
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

    if (strSmije == "0")
    {
        retValue = true;
    }
    else
    {
        retValue = false;
    }

    return retValue;
}

void FrmTipStranke::popuniTipStranke1()
{
    ui->treeSifre->clear();
    ui->txtTip1->clear();
    ui->txtTip2->clear();
    ui->txtTip3->clear();
    ui->txtSegment->clear();
    ui->txtOpomena->clear();
    m_iTipStranke1Id = 0;
    m_iTipStranke2Id = 0;
    m_iTipStranke3Id = 0;
    m_iMarketinskiSegmentId = 0;
    m_iTipOpominjanjaId = 0;

    m_SifranikMode = SifarnikModeTipStranke1;

    string strSqlStatement;
    strSqlStatement.append("SELECT TSTRANKE1_ID, UPPER(NAZIV) FROM TIPOVI_STRANAKA1 ORDER BY RBK ");
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
void FrmTipStranke::popuniTipStranke2()
{
    ui->treeSifre->clear();

    ui->txtTip2->clear();
    ui->txtTip3->clear();
    ui->txtSegment->clear();
    ui->txtOpomena->clear();
    m_iTipStranke2Id = 0;
    m_iTipStranke3Id = 0;
    m_iMarketinskiSegmentId = 0;
    m_iTipOpominjanjaId = 0;

    if(m_iTipStranke1Id == 0)
    {
        return;
    }

    m_SifranikMode = SifarnikModeTipStranke2;

    string strSqlStatement;
    strSqlStatement.append("SELECT TSTRANKE2_ID, UPPER(NAZIV) FROM TIPOVI_STRANAKA2 WHERE TSTRANKE1_ID = ");
    strSqlStatement.append(cttl::itos(m_iTipStranke1Id));
    strSqlStatement.append(" ORDER BY RBK ");
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
void FrmTipStranke::popuniTipStranke3()
{
    ui->treeSifre->clear();

    ui->txtTip3->clear();
    ui->txtSegment->clear();
    ui->txtOpomena->clear();
    m_iTipStranke3Id = 0;
    m_iMarketinskiSegmentId = 0;
    m_iTipOpominjanjaId = 0;

    if(m_iTipStranke2Id == 0)
    {
        return;
    }

    m_SifranikMode = SifarnikModeTipStranke3;

    string strSqlStatement;
    strSqlStatement.append("SELECT TSTRANKE3_ID, UPPER(NAZIV) FROM TIPOVI_STRANAKA3 WHERE TSTRANKE2_ID = ");
    strSqlStatement.append(cttl::itos(m_iTipStranke2Id));
    strSqlStatement.append(" ORDER BY RBK ");
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
void FrmTipStranke::popuniMarketSegmente()
{
    ui->treeSifre->clear();

    ui->txtSegment->clear();
    ui->txtOpomena->clear();
    m_iMarketinskiSegmentId = 0;
    m_iTipOpominjanjaId = 0;

    if(m_iStrankaId == 0)
    {
        return;
    }

    m_SifranikMode = SifarnikModeMarketinskiSegment;

    string strSqlStatement;
    strSqlStatement.append("SELECT MS.MARKETSEGMENT_ID, UPPER(MS.NAZIV) ");
    strSqlStatement.append("FROM MARKET_SEGMENTI MS, VEZE_TIP2_MSEGMENT V, ");
    strSqlStatement.append(" (SELECT COUNT(*) BROJ FROM VEZE_TIP2_MSEGMENT WHERE TSTRANKE3_ID = ");
    strSqlStatement.append(cttl::itos(m_iTipStranke3Id));
    strSqlStatement.append(" ) V2 ");
    strSqlStatement.append(" WHERE V.MARKETSEGMENT_ID = MS.MARKETSEGMENT_ID AND V.TSTRANKE2_ID = ");
    strSqlStatement.append(cttl::itos(m_iTipStranke2Id));
    strSqlStatement.append(" AND DECODE(V2.BROJ, 0, NVL(V.TSTRANKE3_ID," + cttl::itos(m_iTipStranke3Id) + "), V.TSTRANKE3_ID) = ");
    strSqlStatement.append(cttl::itos(m_iTipStranke3Id));
    strSqlStatement.append(" ORDER BY RBK ");
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
void FrmTipStranke::popuniTipoveOpomena()
{
    ui->treeSifre->clear();

    m_SifranikMode = SifarnikModeTipoviOpominjanja;

    string strSqlStatement;
    strSqlStatement.append("SELECT TOPOMINJANJA_ID, UPPER(NAZIV) FROM TIPOVI_OPOMINJANJA ");
    if (
            m_iMarketinskiSegmentId == 15 || m_iMarketinskiSegmentId == 17 || m_iMarketinskiSegmentId == 18 ||
            m_iMarketinskiSegmentId == 19 || m_iMarketinskiSegmentId == 20 || m_iMarketinskiSegmentId == 21
       )
    {
        strSqlStatement.append(" WHERE TOPOMINJANJA_ID IN (3, 4, 5, 8, 10, 11) ");
    }
    strSqlStatement.append(" ORDER BY RBK ");
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
void FrmTipStranke::popuniKreditneProfile()
{
    ui->treeSifre->clear();

    m_SifranikMode = SifarnikModeKreditniProfili;

    string strSqlStatement;
    strSqlStatement.append("SELECT KREDPROFIL_ID, UPPER(NAZIV) FROM KREDITNI_PROFILI_STRANKE ORDER BY RBK ");
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

void FrmTipStranke::promjeniTipStranke()
{
    if(
            m_iTipStranke1Id == 0 || m_iTipStranke2Id == 0 || m_iTipStranke3Id == 0 || m_iMarketinskiSegmentId == 0 ||
            m_iTipOpominjanjaId == 0 || m_iKreditniProfilId == 0 || m_iStrankaId == 0
      )
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT SUBSTR(DNT_PROMTIPA.POSTOJI_LI_AKTIVNOST(");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append(",");
    strSqlStatement.append(cttl::itos(m_iTipStranke3Id));
    strSqlStatement.append(",");
    strSqlStatement.append(cttl::itos(m_iMarketinskiSegmentId));
    strSqlStatement.append("), 1, 1) STATUS, SUBSTR(DNT_PROMTIPA.POSTOJI_LI_AKTIVNOST(");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append(",");
    strSqlStatement.append(cttl::itos(m_iTipStranke3Id));
    strSqlStatement.append(",");
    strSqlStatement.append(cttl::itos(m_iMarketinskiSegmentId));
    strSqlStatement.append("), 2) PORUKA FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    string strStatus;
    string strPoruka;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strStatus = rs->getString(1);
            strPoruka = rs->getString(2);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(strStatus != "1")
    {
        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
        QMessageBox::warning(this, tr("DONAT - Stranka - Promjena Tipova"),
                             QString::fromStdString(strPoruka),
                             QMessageBox::Close);
        return;
    }

    setCursor(Qt::BusyCursor);

    strSqlStatement.clear();
    strSqlStatement.append("BEGIN DNT_PROMTIPA.PROMIJENI_TIPOVE(:STRANKA_ID_PAR, :TSTRANKE3_ID_N, :P_MARKET, :P_OPOMENA, :P_PROFIL); END; ");
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setUInt(1, m_iStrankaId);
        sqlStatement->setInt(2, m_iTipStranke3Id);
        sqlStatement->setInt(3, m_iMarketinskiSegmentId);
        sqlStatement->setInt(4, m_iTipOpominjanjaId);
        sqlStatement->setInt(5, m_iKreditniProfilId);
        sqlStatement->executeUpdate();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    setCursor(Qt::ArrowCursor);

    strSqlStatement.clear();
    strSqlStatement.append("SELECT PROVJERA_PROMJENE_PODTIPA (");
    strSqlStatement.append(cttl::itos(m_iStrankaId));
    strSqlStatement.append(") SMIJE FROM DUAL ");
    sqlStatement->setSQL(strSqlStatement);

    string strSmije;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strSmije = rs->getString(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(strSmije != "0")
    {
        QMessageBox::warning(this, tr("DONAT - Stranka - Promjena Tipova"),
                             tr("Pokreni formu za promjenu poreza!"),
                             QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    this->close();
}

// [ Event Handlers ]
void FrmTipStranke::on_btnPotvrda_clicked()
{
    promjeniTipStranke();
}

void FrmTipStranke::on_txtTip1_textEdited(const QString &UNUSED(arg1))
{
    popuniTipStranke1();
}
void FrmTipStranke::on_txtTip2_textEdited(const QString &UNUSED(arg1))
{
    popuniTipStranke2();
}
void FrmTipStranke::on_txtTip3_textEdited(const QString &UNUSED(arg1))
{
    popuniTipStranke3();
}
void FrmTipStranke::on_txtSegment_textEdited(const QString &UNUSED(arg1))
{
    popuniMarketSegmente();
}
void FrmTipStranke::on_txtOpomena_textEdited(const QString &UNUSED(arg1))
{
    popuniTipoveOpomena();
}
void FrmTipStranke::on_txtProfil_textEdited(const QString &UNUSED(arg1))
{
    popuniKreditneProfile();
}

void FrmTipStranke::on_treeSifre_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    switch(m_SifranikMode)
    {
        case SifarnikModeTipStrankeNone:
        {
            return;
            break;
        }
        case SifarnikModeTipStranke1:
        {
            m_iTipStranke1Id = item->text(0).toInt();
            ui->txtTip1->setText(item->text(1));
            ui->txtTip2->setFocus();
            popuniTipStranke2();
            break;
        }
        case SifarnikModeTipStranke2:
        {
            m_iTipStranke2Id = item->text(0).toInt();
            ui->txtTip2->setText(item->text(1));
            ui->txtTip3->setFocus();
            popuniTipStranke3();
            break;
        }
        case SifarnikModeTipStranke3:
        {
            m_iTipStranke3Id = item->text(0).toInt();
            ui->txtTip3->setText(item->text(1));
            ui->txtSegment->setFocus();
            popuniMarketSegmente();
            break;
        }
        case SifarnikModeMarketinskiSegment:
        {
            m_iMarketinskiSegmentId = item->text(0).toInt();
            ui->txtSegment->setText(item->text(1));
            ui->txtOpomena->setFocus();
            popuniTipoveOpomena();
            break;
        }
        case SifarnikModeTipoviOpominjanja:
        {
            m_iTipOpominjanjaId = item->text(0).toInt();
            ui->txtOpomena->setText(item->text(1));
            ui->txtProfil->setFocus();
            popuniKreditneProfile();
            break;
        }
        case SifarnikModeKreditniProfili:
        {
            m_iKreditniProfilId = item->text(0).toInt();
            ui->txtProfil->setText(item->text(1));
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


