#include "frmprigovorpregled.h"
#include "ui_frmprigovorpregled.h"

#include "itos.h"
#include "ocinumber.h"

#include "forms/kontakt/frmkontaktdokumenti1.h"

#include "forms/kontakt/prigovor/frmprigovoredit.h"
#include "forms/kontakt/prigovor/frmprigovorodabirstatusa.h"
#include "forms/kontakt/prigovor/frmprigovorjop.h"
#include "forms/kontakt/prigovor/frmprigovorstatus.h"
#include "forms/kontakt/prigovor/frmprigovorosporavaniiznos.h"
#include "forms/kontakt/prigovor/frmprigovorpisanorjesenje.h"

namespace Kontakt {

// [Class Constructor]
FrmPrigovorPregled::FrmPrigovorPregled(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPrigovorPregled)
{
    ui->setupUi(this);

    ui->treePrigovori->setColumnWidth(0, 56);
    ui->treePrigovori->setColumnWidth(1, 442);
    ui->treePrigovori->hideColumn(2);
    ui->treePrigovori->hideColumn(3);

    m_iconKupac.addFile(QString::fromUtf8(":/InDonat/Forms/images/ULOGA_ID_16x16.png"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconTelefon.addFile(QString::fromUtf8(":/InDonat/Forms/images/telephone.gif"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconMobitel.addFile(QString::fromUtf8(":/InDonat/Forms/images/mobilephone2.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconInternet.addFile(QString::fromUtf8(":/InDonat/Forms/images/INT_2_16x16.png"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconPrinter.addFile(QString::fromUtf8(":/InDonat/Forms/images/print.gif"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconEmail.addFile(QString::fromUtf8(":/InDonat/Forms/images/email.gif"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    m_iconBundle.addFile(QString::fromUtf8(":/InDonat/Forms/images/SERVICE.GIF"),
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


    initForm();
}

FrmPrigovorPregled::~FrmPrigovorPregled()
{
    delete ui;
}

// [Private Class Members]
void FrmPrigovorPregled::initForm()
{
    ui->dateDo->setDateTime(QDateTime::currentDateTime());
    ui->dateOd->setDateTime(QDateTime::currentDateTime().addDays(-30));
    ui->lblStatusTitle->setText(tr("SVE"));
    m_TipPrigovora = PrikaziPrigovoreSve;
    ui->cboClanGrupe->clear();
    ui->cboVoditeljGrupe->clear();

    m_iPrigovorId = 0;
    m_iStavkaId = 0;

    clearPrigovor();
}

void FrmPrigovorPregled::clearPrigovor()
{

    ui->lblInicijator->clear();
    ui->lblZaprimioUnio->clear();
    ui->lblPreuzeoZaduzen->clear();
    ui->lblTrazenaProvjeras->clear();
    ui->btnGo2_5->setEnabled(false);
    ui->btnGo2_7->setEnabled(false);
    ui->btnGo2_10->setEnabled(false);
    ui->btnGo2_15->setEnabled(false);
    ui->btnGo2_16->setEnabled(false);
    ui->lblDokumentiRijesenje->clear();
    ui->lblPrilog->clear();
    ui->lblKupac->clear();
    ui->lblDatum->clear();
    ui->lblJop->clear();
    ui->lblSpis->clear();
    ui->lblPrigovorTip->clear();
    ui->lblTelefon->clear();
    ui->lblMjesec->clear();
    ui->lblUsluga->clear();
    ui->lblCodeUsl->clear();
    ui->lblCode1->clear();
    ui->lblCode2->clear();
    ui->lblNeto->clear();
    ui->lblPdv->clear();
    ui->lblBruto->clear();
    ui->lblZahSme->clear();
    ui->lblOpis->clear();
    ui->lblRijesenje->clear();
    ui->lblRjesio->clear();
    ui->lblTipRjesenja->clear();
    ui->lblRazlog->clear();
    ui->lblNeto_2->clear();
    ui->lblPdv_2->clear();
    ui->lblBruto_2->clear();
    ui->lblOpis_2->clear();
    ui->lblOdobrenje->clear();
    ui->lblOdobrio->clear();
    ui->lblRazina->clear();
    ui->lblNaplata->clear();
    ui->lblNaplata_2->clear();
    ui->lblPoruka->clear();
    ui->lblPismoOdgovor->clear();
    ui->lblNapisao->clear();
}

void FrmPrigovorPregled::popuniKorisnikGrupe()
{
    ui->treePrigovori->clear();
    ui->cboClanGrupe->clear();
    ui->cboVoditeljGrupe->clear();

    m_iAktivnaKorisnikGrupa = 0;
    m_strAktivnaKorisnikGrupa.clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT COUNT(GRUPA_ID) GRUPA_NAZ FROM KONTAKT_GRUPA_KOR WHERE KOR_ID = '");
    strSqlStatement.append(g_DonatUser);
    strSqlStatement.append("' AND KOR_TIP = ");
    strSqlStatement.append(cttl::itos(m_iTipKorisnika));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    int iGrupeNo = -1;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();

        if(rs->next())
        {
            iGrupeNo = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iGrupeNo == -1)
    {
        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
        return;
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT GRUPA_ID, MIN(GRUPA_NAZ) GRUPA_NAZ FROM KONTAKT_GRUPA_KOR WHERE KOR_ID = '");
    strSqlStatement.append(g_DonatUser);
    strSqlStatement.append("' AND KOR_TIP = ");
    strSqlStatement.append(cttl::itos(m_iTipKorisnika));
    strSqlStatement.append(" GROUP BY GRUPA_ID ORDER BY 2 ");

    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ui->cboClanGrupe->blockSignals(true);
        ResultSet *rs = sqlStatement->executeQuery();

        if(iGrupeNo > 1)
        {
            ui->cboClanGrupe->addItem(tr("SVE GRUPE"), QVariant::fromValue(0));
            m_iAktivnaKorisnikGrupa = 0;
        }

        while(rs->next())
        {
            ui->cboClanGrupe->addItem(QString::fromStdString(rs->getString(2)), QVariant::fromValue(rs->getInt(1)));
            if(m_strAktivnaKorisnikGrupa.length() > 0)
            {
                m_strAktivnaKorisnikGrupa = m_strAktivnaKorisnikGrupa + ", " + rs->getString(1);
            }
            else
            {
                m_strAktivnaKorisnikGrupa = rs->getString(1);
            }
        }
        sqlStatement->closeResultSet(rs);

        m_strSveKorisnikGrupe = m_strAktivnaKorisnikGrupa;
        ui->cboClanGrupe->blockSignals(false);
    }
    catch(SQLException &ex)
    {
        ui->cboClanGrupe->blockSignals(false);
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    g_DonatConn->terminateStatement(sqlStatement);
    strSqlStatement.erase();

    popuniKorisnikAgent();
}
void FrmPrigovorPregled::popuniKorisnikAgent()
{
    ui->cboVoditeljGrupe->clear();
    ui->cboVoditeljGrupe->blockSignals(true);

    if(m_iTipKorisnika == 1)
    {
        ui->cboVoditeljGrupe->addItem(QString::fromStdString(g_DonatUser), QVariant::fromValue(QString::fromStdString(g_DonatUser)));
        m_strAktivniKorisnikId = g_DonatUser;
    }
    else
    {
        ui->cboVoditeljGrupe->addItem(tr("SVI AGENTI"), QVariant::fromValue(tr("SVI AGENTI")));
        m_strAktivniKorisnikId.clear();

        string strSqlStatement;
        strSqlStatement.append("SELECT KOR_ID, MIN(KOR_NAZ) KOR_NAZ FROM KONTAKT_GRUPA_KOR WHERE GRUPA_ID IN (");
        strSqlStatement.append(m_strAktivnaKorisnikGrupa);
        strSqlStatement.append(") AND KOR_TIP = 1 GROUP BY KOR_ID ORDER BY KOR_NAZ ");

        Statement *sqlStatement = g_DonatConn->createStatement();
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();

            while(rs->next())
            {
                ui->cboVoditeljGrupe->addItem(QString::fromStdString(rs->getString(2)), QVariant::fromValue(QString::fromStdString(rs->getString(1))));
            }
            ui->cboVoditeljGrupe->blockSignals(false);
            sqlStatement->closeResultSet(rs);
        }
        catch(SQLException &ex)
        {
            ui->cboVoditeljGrupe->blockSignals(false);
            QMessageBox::critical(this, tr("DONAT - Database Error"),
                                           QString::fromStdString(ex.getMessage()),
                                           QMessageBox::Close);
        }

        g_DonatConn->terminateStatement(sqlStatement);
        strSqlStatement.erase();
    }

}
void FrmPrigovorPregled::popuniPrigovore()
{
    ui->treePrigovori->clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT /*+ RULE */ ID, ST_ID, TO_CHAR(ST_DATUM,'DD.MM.YYYY') ST_DATUM_1, KUP_NAZIV, KUP_ADRESA, ");
    strSqlStatement.append("NVL(TEL_BROJ,'xxxxxxxxx') TEL_BROJ, ST_KOR_NAZ, KOR_GRUPA_NAZ, NVL(ST_PRIKAZ,'xxxxxxxxxxxxxxxxxxxxxxx') ST_PRIKAZ, ");
    strSqlStatement.append("NVL(ST_STATUS,0) ST_STATUS, NVL(ST_NACIN,0) ST_NACIN, NVL(NA_STATUS,0) NA_STATUS, NVL(OD_STATUS,0) OD_STATUS, ");
    strSqlStatement.append("NVL(DOK_STATUS,0) DOK_STATUS, NVL(PROVJERA_ID,0) PROVJERA_ID, NVL(ZAPRIMLJEN_ID,0) ZAPRIMLJEN_ID ");
    strSqlStatement.append(" FROM KONTAKT_ST5_PR WHERE ZA_GRUPA_ID IN (");
    strSqlStatement.append(m_strAktivnaKorisnikGrupa);
    strSqlStatement.append(") AND ST_DATUM BETWEEN TO_DATE('");
    strSqlStatement.append(ui->dateOd->text().toStdString());
    strSqlStatement.append("', 'DD.MM.YYYY') AND TO_DATE('");
    strSqlStatement.append(ui->dateDo->text().toStdString());
    strSqlStatement.append("','DD.MM.YYYY')");

    switch(m_TipPrigovora)
    {
       case PrikaziPrigovoreSve:
       {
           strSqlStatement.append(" AND ST_STATUS IN (-1, 1, 2) ");
           break;
       }
       case PrikaziPrigovoreUtijeku:
       {
           strSqlStatement.append(" AND ST_STATUS = 1 ");
           break;
       }
       case PrikaziPrigovoreZavrsene:
       {
           strSqlStatement.append(" AND ST_STATUS = 2 ");
           break;
       }
       case PrikaziPrigovoreStornirane:
       {
           strSqlStatement.append(" AND ST_STATUS = -1 ");
           break;
       }
       default:
       {
           strSqlStatement.append(" AND ST_STATUS IN (-1, 1, 2) ");
           break;
       }
    }

    /* Pretrazivanje samo za pojedinog djelatnika
    if(m_iPrigovorFileter1 > 1 )
    {
        if(m_strAktivniKorisnikId.length() > 0)
        {
            strSqlStatement.append(" AND ZA_KOR_ID ='");
            strSqlStatement.append(m_strAktivniKorisnikId);
            strSqlStatement.append("' ");
        }
    }
    */

    switch(m_iPrigovorFileter1)
    {
        case 1: // ZADUŽEN
        {
            if(m_iPrigovorFileter2 == 1)
            {
                strSqlStatement.append(" AND ZA_KOR_ID IS NULL ");
            }
            else if(m_iPrigovorFileter2 == 2)
            {
                strSqlStatement.append(" AND ZA_KOR_ID IS NOT NULL ");
            }
            break;
        }
        case 2: // RJEŠENJE
        {
            strSqlStatement.append(" AND RJ_STATUS = ");
            strSqlStatement.append(cttl::itos(m_iPrigovorFileter2));
            strSqlStatement.append(" ");
            break;
        }
        case 3: // ODOBRENJE
        {
            strSqlStatement.append(" AND OD_STATUS = ");
            strSqlStatement.append(cttl::itos(m_iPrigovorFileter2));
            strSqlStatement.append(" ");
            break;
        }
        case 4: // NAPLATA
        {
            strSqlStatement.append(" AND NA_STATUS = ");
            strSqlStatement.append(cttl::itos(m_iPrigovorFileter2));
            strSqlStatement.append(" ");
            break;
        }
        case 5: // PISMO
        {
            strSqlStatement.append(" AND DOK_STATUS = ");
            strSqlStatement.append(cttl::itos(m_iPrigovorFileter2));
            strSqlStatement.append(" ");
            break;
        }
        case 6: // TEHNIČKA PROVJERA
        {
            strSqlStatement.append(" AND TEH_STATUS = ");
            strSqlStatement.append(cttl::itos(m_iPrigovorFileter2));
            strSqlStatement.append(" ");
            break;
        }
        case 7: // RAZINA ODOBRENJA
        {
            strSqlStatement.append(" AND OD_NIVO_ID = ");
            strSqlStatement.append(cttl::itos(m_iPrigovorFileter2));
            strSqlStatement.append(" ");
            break;
        }
        case 8: //
        {
            if(m_iPrigovorFileter2 > -1)
            {
                strSqlStatement.append(" AND ZAH_TIP = ");
                strSqlStatement.append(cttl::itos(m_iPrigovorFileter2));
                strSqlStatement.append(" ");
            }
            break;
        }
    }

    strSqlStatement.append(" ORDER BY ST_DATUM, ID ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listPrigovori;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            bool bNewPrigovor = true;
            for(int iTreeItem = 0; iTreeItem < listPrigovori.size(); ++iTreeItem)
            {
                if(listPrigovori.at(iTreeItem)->text(3).toInt() == rs->getInt(2))
                {
                    bNewPrigovor = false;
                    //break;
                }
            }

            if(bNewPrigovor == true)
            {
                QTreeWidgetItem *itemPrigovor = new QTreeWidgetItem();
                switch(rs->getInt(11))
                {
                    case 0:
                    {
                        itemPrigovor->setIcon(0, m_iconKupac);
                        break;
                    }
                    case 1:
                    {
                        itemPrigovor->setIcon(0, m_iconTelefon);
                        break;
                    }
                    case 2:
                    {
                        itemPrigovor->setIcon(0, m_iconMobitel);
                        break;
                    }
                    case 3:
                    {
                        itemPrigovor->setIcon(0, m_iconInternet);
                        break;
                    }
                    case 4:
                    {
                        itemPrigovor->setIcon(0, m_iconPrinter);
                        break;
                    }
                    case 5:
                    {
                        itemPrigovor->setIcon(0, m_iconEmail);
                        break;
                    }
                    case 6:
                    {
                        itemPrigovor->setIcon(0, m_iconBundle);
                        break;
                    }
                    default:
                    {
                        itemPrigovor->setIcon(0, m_iconTransparent);
                        break;
                    }
                }

                QString strPrigovor = QString();
                strPrigovor.append(QString::fromStdString(rs->getString(3)));
                strPrigovor.append(tr(" ... "));
                strPrigovor.append(QString::fromStdString(rs->getString(6)));
                strPrigovor.append(tr(" ... "));
                strPrigovor.append(QString::fromStdString(rs->getString(4)));
                strPrigovor.append(tr("   ("));
                strPrigovor.append(QString::fromStdString(rs->getString(8)));
                strPrigovor.append(tr(")"));
                itemPrigovor->setText(1, strPrigovor);
                itemPrigovor->setText(2, QString::fromStdString(rs->getString(1)));
                itemPrigovor->setText(3, QString::fromStdString(rs->getString(2)));
                listPrigovori.append(itemPrigovor);
            }

            for(int iTreeItem = 0; iTreeItem < listPrigovori.size(); ++iTreeItem)
            {
                if(listPrigovori.at(iTreeItem)->text(3).toInt() == rs->getInt(2))
                {
                    QTreeWidgetItem *itemPrigovorStavka = new QTreeWidgetItem();
                    switch(rs->getInt(10))
                    {
                        case -1:
                        {
                            itemPrigovorStavka->setIcon(0, m_iconCrveni);
                            break;
                        }
                        case 1:
                        {
                            itemPrigovorStavka->setIcon(0, m_iconZuti);
                            //itemPrigovorStavka->setText(0, tr("XX"));
                            break;
                        }
                        case 2:
                        {
                            itemPrigovorStavka->setIcon(0, m_iconZeleni);
                            break;
                        }
                        default:
                        {
                            itemPrigovorStavka->setIcon(0, m_iconTransparent);
                            break;
                        }
                    }
                    itemPrigovorStavka->setText(1, QString::fromStdString(rs->getString(9)));
                    itemPrigovorStavka->setText(2, QString::fromStdString(rs->getString(1)));
                    itemPrigovorStavka->setText(3, QString::fromStdString(rs->getString(2)));
                    listPrigovori.at(iTreeItem)->addChild(itemPrigovorStavka);
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

    if(!listPrigovori.empty())
    {
        listPrigovori.first()->setSelected(true);
        ui->treePrigovori->insertTopLevelItems(0, listPrigovori);
        ui->treePrigovori->setCurrentItem(listPrigovori.first());
        ui->treePrigovori->collapseAll();
    }

}
void FrmPrigovorPregled::popuniPrigovor()
{
    if(m_iStavkaId == 0)
    {
        return;
    }

    clearPrigovor();

    m_iKontaktId = getKontaktId(m_iStavkaId);

    string strSqlStatement;

    strSqlStatement.append("SELECT ST_GRUPA, ST_STATUS, NVL(TO_CHAR(ST_DATUM,'DD.MM.YYYY'),' ') ST_DATUM, ST_KOR_NAZ, KOR_GRUPA_NAZ, ");
    strSqlStatement.append("NVL(ST_SPIS,' ') ST_SPIS, NVL(ST_JOP,' ') ST_JOP, KUP_ID, KUP_NAZIV, KUP_ADRESA, KUP_TIP_ID, TEL_GIM_ID, TEL_BROJ, ");
    strSqlStatement.append("TEL_KLASA, NVL(ST_OPIS,' ') ST_OPIS, ST_G1_NAZ, ST_G2_NAZ, NVL(ST_G3_NAZ, '-') ST_G3_NAZ, NVL(USL_NAPLATA_ID, 0) USL_NAPLATA_ID, ");
    strSqlStatement.append("NVL(USL_BA_MJESEC, ' ') USL_BA_MJESEC, NVL(USL_POZIV_NB,' ') USL_POZIV_NB, NVL(USL_CODE, ' ') USL_CODE, NVL(USL_NAZIV,'xxxxx') USL_NAZIV, ");
    strSqlStatement.append("NVL(USL_NETO,0) USL_NETO, NVL(USL_PDV,0) USL_PDV, NVL(USL_BRUTO,0) USL_BRUTO, NVL(OSP_NETO,0) OSP_NETO, NVL(OSP_PDV,0) OSP_PDV, ");
    strSqlStatement.append("NVL(OSP_BRUTO,0) OSP_BRUTO, NVL(ZAH_OPIS,' ') ZAH_OPIS, NVL(ZAH_TIP,0) ZAH_TIP, NVL(ZAH_ID,0) ZAH_ID, NVL(RJ_STATUS,0) RJ_STATUS, ");
    strSqlStatement.append("NVL(RJ_TIP,0) RJ_TIP, NVL(RJ_NAZIV,'NIJE RJEŠENO') RJ_NAZIV, NVL(TO_CHAR(RJ_DATUM,'DD.MM.YYYY'),' ') RJ_DATUM, NVL(RJ_KOR_NAZ,' ') RJ_KOR_NAZ, ");
    strSqlStatement.append("NVL(RJ_NETO,0) RJ_NETO, NVL(RJ_PDV,0) RJ_PDV, NVL(RJ_BRUTO,0) RJ_BRUTO, NVL(RJ_OPIS,' ') RJ_OPIS, NVL(RJ_RAZ_ID,0) RJ_RAZ_ID, ");
    strSqlStatement.append("NVL(RJ_RAZ_NAZ,'OSTALO') RJ_RAZ_NAZ, NVL(OD_STATUS,0) OD_STATUS, NVL(TO_CHAR(OD_DATUM,'DD.MM.YYYY'),' ') OD_DATUM, NVL(OD_KOR_NAZ,' ') OD_KOR_NAZ, ");
    strSqlStatement.append("NVL(OD_NIVO_ID,0) OD_NIVO_ID, NVL(OD_NIVO_NAZ,' ') OD_NIVO_NAZ, NVL(NA_STATUS,0) NA_STATUS, NVL(TO_CHAR(NA_DATUM,'DD.MM.YYYY'),' ') NA_DATUM, ");
    strSqlStatement.append("NVL(NA_KOR_NAZ,' ') NA_KOR_NAZ, NVL(NA_OPIS,' ') NA_OPIS, NVL(USL_CODE_T1,' ') USL_CODE_T1, NVL(USL_CODE_T2,' ') USL_CODE_T2, ");
    strSqlStatement.append("NVL(ZA_STATUS,0) ZA_STATUS, NVL(TO_CHAR(ZA_DATUM,'DD.MM.YYYY'),' ') ZA_DATUM, NVL(ZA_KOR_ID,' ') ZA_KOR_ID, NVL(ZA_KOR_NAZ,'X') ZA_KOR_NAZ, ");
    strSqlStatement.append("NVL(ZA_GRUPA_ID,0) ZA_GRUPA_ID, NVL(ZA_GRUPA_NAZ,' ') ZA_GRUPA_NAZ, NVL(DOK_STATUS,0) DOK_STATUS, NVL(TO_CHAR(DOK_DATUM,'DD.MM.YYYY'),' ') DOK_DATUM, ");
    strSqlStatement.append("NVL(DOK_KOR_NAZ,' ') DOK_KOR_NAZ, NVL(DOK_OPIS,' ') DOK_OPIS, NVL(INICIJATOR,' ') INICIJATOR, NVL(TEH_STATUS,0) TEH_STATUS, ");
    strSqlStatement.append("NVL(TO_CHAR(TEH_DATUM_OD,'DD.MM.YYYY'),'xx.xx.xxxx') TEH_DATUM_OD, NVL(TO_CHAR(TEH_DATUM_DO,'DD.MM.YYYY'),'xx.xx.xxxx') TEH_DATUM_DO, ");
    strSqlStatement.append("NVL(TEH_REGIJA,0) TEH_REGIJA, NVL(TEH_TICKET,0) TEH_TICKET ");
    strSqlStatement.append("FROM KONTAKT_ST5_PR WHERE ID = ");
    strSqlStatement.append(cttl::itos(m_iPrigovorId));

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_iKorisnickiKanalId = rs->getInt(1);
            m_iKupacId = rs->getUInt(8);
            m_strKupacNaziv = rs->getString(9);
            m_iKupacTipId = rs->getInt(11);
            m_strTelefonskiBroj = rs->getString(13);
            m_iGrupaImovineId = rs->getUInt(12);
            m_iZaGrupaId = rs->getInt(59);
            m_strZaGrupaNaziv = rs->getString(60);

            ui->lblDatum->setText(QString::fromStdString(rs->getString(3)));
            ui->lblSpis->setText(QString::fromStdString(rs->getString(6)));
            ui->lblJop->setText(QString::fromStdString(rs->getString(7)));

            ui->lblInicijator->setText(QString::fromStdString(rs->getString(65)));

            QString strText = QString();
            strText.append(QString::fromStdString(rs->getString(3)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(5)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(4)));
            ui->lblZaprimioUnio->setText(strText);

            strText.clear();
            strText.append(QString::fromStdString(rs->getString(9)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(10)));
            ui->lblKupac->setText(strText);

            strText.clear();
            strText.append(QString::fromStdString(rs->getString(13)));
            strText.append(tr(" "));
            strText.append(QString::fromStdString(rs->getString(14)));
            ui->lblTelefon->setText(strText);

            strText.clear();
            strText.append(QString::fromStdString(rs->getString(16)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(17)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(18)));
            ui->lblPrigovorTip->setText(strText);

            m_iUslugaNaplataId = cttl::getUIntAsONumber(rs->getNumber(19));
            if(m_iUslugaNaplataId == 0)
            {
                ui->lblMjesec->clear();
                ui->lblUsluga->clear();
                ui->lblCodeUsl->clear();
                ui->lblCode1->clear();
                ui->lblCode2->clear();
            }
            else
            {
                strText.clear();
                strText.append(QString::fromStdString(rs->getString(19)));
                strText.append(tr(" ... "));
                strText.append(QString::fromStdString(rs->getString(20)));
                strText.append(tr(" ... "));
                strText.append(QString::fromStdString(rs->getString(21)));
                ui->lblMjesec->setText(strText);
                ui->lblUsluga->setText(QString::fromStdString(rs->getString(23)));
                ui->lblCodeUsl->setText(QString::fromStdString(rs->getString(22)));
                ui->lblCode1->setText(QString::fromStdString(rs->getString(53)));
                ui->lblCode2->setText(QString::fromStdString(rs->getString(54)));
            }

            ui->lblNeto->setText(QString::fromStdString(rs->getString(27)));
            ui->lblPdv->setText(QString::fromStdString(rs->getString(28)));
            ui->lblBruto->setText(QString::fromStdString(rs->getString(29)));

            m_iStavkaStatusId = rs->getInt(2);
            if(m_iStavkaStatusId == 1)
            {
                ui->btnGo2_10->setEnabled(true);
            }

            ui->lblZahSme->setText(QString::fromStdString(rs->getString(30)));

            m_iZahtjevTipId = rs->getInt(31);
            m_iZahtjevId = rs->getUInt(32);
            m_strST_Opis = rs->getString(15);

            m_iRjesenjeStatusId = rs->getInt(33);
            m_iRjesenjeTipId = rs->getInt(34);
            if(m_iRjesenjeStatusId == 1)
            {
                ui->lblRijesenje->setText(tr("NEMA RJEŠENJE"));
                // To Do Set Red background
                ui->lblRjesio->setText(tr(""));
                ui->lblTipRjesenja->setText(tr(""));
            }
            else if(m_iRjesenjeStatusId == 2)
            {
                ui->lblRijesenje->setText(tr("RJEŠENO"));
                // To Do Set Red background
                strText.clear();
                strText.append(QString::fromStdString(rs->getString(36)));
                strText.append(tr(" ... "));
                strText.append(QString::fromStdString(rs->getString(37)));
                ui->lblRjesio->setText(strText);
                ui->lblTipRjesenja->setText(QString::fromStdString(rs->getString(35)));
            }

            ui->lblTipRjesenja->setText(QString::fromStdString(rs->getString(35)));
            ui->lblRazlog->setText(QString::fromStdString(rs->getString(43)));

            ui->lblNeto_2->setText(QString::fromStdString(rs->getString(38)));
            ui->lblPdv_2->setText(QString::fromStdString(rs->getString(39)));
            ui->lblBruto_2->setText(QString::fromStdString(rs->getString(40)));

            strText.clear();
            strText.append(QString::fromStdString(rs->getString(45)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(46)));
            ui->lblOdobrio->setText(strText);

            m_iOdobrenjeStatusId = rs->getInt(44);
            switch(m_iOdobrenjeStatusId)
            {
                case 0:
                {
                    ui->lblOdobrio->clear();
                    break;
                }
                case 1:
                {
                    ui->lblOdobrenje->setText(tr("NIJE ODOBRENO"));
                    // To Do Set Red background
                    ui->lblOdobrio->clear();
                    ui->btnGo2_15->setEnabled(true);
                    break;
                }
                case 2:
                {
                    ui->lblOdobrenje->setText(tr("ODOBRENO U CJELOSTI"));
                    // To Do Set Gray background
                    break;
                }
                case 3:
                {
                    ui->lblOdobrenje->setText(tr("ODOBRENO DJELOMIČNO"));
                    // To Do Set Gray background
                    break;
                }
                case 4:
                {
                    ui->lblOdobrenje->setText(tr("ODOBRENJE ODBIJENO"));
                    // To Do Set Red background
                    break;
                }
            }

            m_iOdobrenjeNivoId = rs->getInt(47);
            ui->lblRazina->setText(QString::fromStdString(rs->getString(48)));

            // NAPLATA ------------------------------------------------------------------------------
            strText.clear();
            strText.append(QString::fromStdString(rs->getString(50)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(51)));
            ui->lblNaplata_2->setText(strText);
            ui->lblPoruka->setText(QString::fromStdString(rs->getString(52)));

            m_iNaplataStatusId = rs->getInt(49);
            switch(m_iNaplataStatusId)
            {
                case 0:
                {
                    ui->lblNaplata_2->clear();
                    ui->lblPoruka->clear();
                    break;
                }
                case 1:
                {
                    ui->lblNaplata->setText(tr("NIJE PROVEDENO"));
                    // To Do Set Red background
                    ui->lblNaplata_2->clear();
                    ui->lblPoruka->clear();
                    break;
                }
                case 2:
                {
                    ui->lblNaplata->setText(tr("POSLANO"));
                    // To Do Set DarkGoldenrod background
                    break;
                }
                case 3:
                {
                    ui->lblNaplata->setText(tr("NAPLATA OK"));
                    // To Do Set Gray background
                    break;
                }
                case 4:
                {
                    ui->lblNaplata->setText(tr("NAPLATA NOT OK"));
                    // To Do Set Red background
                    break;
                }
            }

            // ZADUŽEN ------------------------------------------------------------------------------
            strText.clear();
            strText.append(QString::fromStdString(rs->getString(56)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(60)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(58)));
            ui->lblPreuzeoZaduzen->setText(strText);

            if(rs->getString(58) == "X")
            {
                m_strAktivniKorisnikId = "";
                ui->lblPreuzeoZaduzen->setText(QString::fromStdString(rs->getString(60)));
                // To Do Set Red background
                // To Do Set White foreground
            }
            else
            {
                m_strAktivniKorisnikId = rs->getString(57);
            }

            // PISMO---------------------------------------------------------------------------
            strText.clear();
            strText.append(QString::fromStdString(rs->getString(62)));
            strText.append(tr(" ... "));
            strText.append(QString::fromStdString(rs->getString(63)));
            ui->lblNapisao->setText(strText);

            m_iDokumentStatusId = rs->getInt(61);
            switch(m_iDokumentStatusId)
            {
                case 0:
                {
                    ui->lblNapisao->clear();
                    break;
                }
                case 1:
                {
                    ui->lblPismoOdgovor->setText(tr("NIJE NAPISANO"));
                    // To Do Set Red background
                    ui->lblNapisao->clear();
                    break;
                }
                case 2:
                {
                    ui->lblPismoOdgovor->setText(tr("NAPISANO"));
                    // To Do Set DarkGoldenrod background
                    break;
                }
                case 3:
                {
                    ui->lblPismoOdgovor->setText(tr("POSLANO"));
                    // To Do Set Gray background
                    break;
                }
                case 4:
                {
                    ui->lblPismoOdgovor->setText(tr("NAPISANO PRIVREMENO"));
                    // To Do Set DarkGoldenrod background
                    break;
                }
                case 5:
                {
                    ui->lblPismoOdgovor->setText(tr("POSLANO PRIVREMENO"));
                    // To Do Set Gray background
                    break;
                }
                case 6:
                {
                    ui->lblPismoOdgovor->setText(tr("DRUGA STAVKA"));
                    // To Do Set Gray background
                    break;
                }
            }

            // TEHNIKA----------------------------------------------------------------
            m_iTehnikaStatusId = rs->getInt(66);
            m_iTehnikaRegijaId = rs->getInt(69);
            if(m_iTehnikaStatusId > 0)
            {
                strText.clear();
                switch(m_iTehnikaRegijaId)
                {
                    case 1:
                    {
                        strText.append(tr("REGIJA ISTOK ... "));
                        break;
                    }
                    case 2:
                    {
                        strText.append(tr("REGIJA JUG ... "));
                        break;
                    }
                    case 3:
                    {
                        strText.append(tr("REGIJA SJEVER ... "));
                        break;
                    }
                    case 4:
                    {
                        strText.append(tr("REGIJA ZAPAD ... "));
                        break;
                    }
                    default:
                    {
                        strText.append(tr("NEMA REGIJE ... "));
                        break;
                    }
                }
                if(m_iTehnikaStatusId == 1)
                {
                    strText.append(QString::fromStdString(rs->getString(67)));
                    ui->lblTrazenaProvjeras->setText(strText);
                    // To Do Set Red background
                    // To Do Set White foreground
                }
                else if(m_iTehnikaStatusId == 2)
                {
                    strText.append(QString::fromStdString(rs->getString(67)));
                    strText.append(tr(" - "));
                    strText.append(QString::fromStdString(rs->getString(68)));
                    ui->lblTrazenaProvjeras->setText(strText);
                    // To Do Set Gray background
                    // To Do Set White foreground
                }

                ui->btnGo2_5->setEnabled(true);
                ui->btnGo2_7->setEnabled(true);
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

    popuniPrilogDatoteke();

}
void FrmPrigovorPregled::popuniPrilogDatoteke()
{
    ui->lblPrilog->clear();

    int iDatotekaNo = 0;
    string strSqlStatement;
    strSqlStatement.append("SELECT COUNT(ID) BROJ FROM KONTAKT_PLAN_FILE ");
    strSqlStatement.append(" WHERE STAVKA_ID = ");
    strSqlStatement.append(cttl::itos(m_iStavkaId));
    strSqlStatement.append(" ORDER BY ID ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iDatotekaNo = rs->getInt(1);
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

    if(iDatotekaNo == 0)
    {
        ui->lblPrilog->setText(tr("NEMA DOKUMENATA"));
    }
    else
    {
        ui->lblPrilog->setText(tr("BROJ DOKUMENATA ... ") + QString::number(iDatotekaNo));
    }
}

int FrmPrigovorPregled::getKontaktId(int iStavkaId)
{
    int retValue = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT KON_ID FROM KONTAKT_ST_N WHERE ST_ID = ");
    strSqlStatement.append(cttl::itos(iStavkaId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getInt(1);
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

    return retValue;
}

// [Event Handlers]
void FrmPrigovorPregled::on_btnClanGrupe_clicked()
{
    initForm();
    m_iTipKorisnika = 1;
    popuniKorisnikGrupe();
}

void FrmPrigovorPregled::on_btnVoditeljGrupe_clicked()
{
    initForm();
    m_iTipKorisnika = 2;
    popuniKorisnikGrupe();
}

void FrmPrigovorPregled::on_btnStatusSvi_clicked()
{
    m_TipPrigovora = PrikaziPrigovoreSve;
    popuniPrigovore();
}

void FrmPrigovorPregled::on_btnStatusUtijeku_clicked()
{
    m_TipPrigovora = PrikaziPrigovoreUtijeku;
    popuniPrigovore();
}

void FrmPrigovorPregled::on_btnStatusZavrseno_clicked()
{
    m_TipPrigovora = PrikaziPrigovoreZavrsene;
    popuniPrigovore();
}

void FrmPrigovorPregled::on_btnStatusStorno_clicked()
{
    m_TipPrigovora = PrikaziPrigovoreStornirane;
    popuniPrigovore();
}

void FrmPrigovorPregled::on_btnOdabirPrigovorTipova_clicked()
{
    // Show Donat prigovor odabir statusa
    Kontakt::FrmPrigovorOdabirStatusa *frmPrigovorStatus = new Kontakt::FrmPrigovorOdabirStatusa(this);
    frmPrigovorStatus->exec();
    m_iPrigovorFileter1 = frmPrigovorStatus->m_iPrigovorFilter1;
    m_iPrigovorFileter2 = frmPrigovorStatus->m_iPrigovorFilter2;
    ui->lblStatusTitle->setText(QString::fromStdString(frmPrigovorStatus->m_strPrigovorStatus));
    delete frmPrigovorStatus;
}

void FrmPrigovorPregled::on_cboClanGrupe_currentIndexChanged(const QString &strGrupa)
{
    if(strGrupa == "SVE GRUPE")
    {
        m_strAktivnaKorisnikGrupa = m_strSveKorisnikGrupe;
    }
    else
    {
        m_strAktivnaKorisnikGrupa = ui->cboClanGrupe->currentData().toString().toStdString();
    }
    popuniKorisnikAgent();
}

void FrmPrigovorPregled::on_btnPrigovorsStatusi_clicked()
{
    // Show Donat prigovor status form
    Kontakt::FrmPrigovorStatus *frmPrigovorStatus = new Kontakt::FrmPrigovorStatus(this);
    frmPrigovorStatus->exec();
    delete frmPrigovorStatus;
}

void FrmPrigovorPregled::on_btnPrigovorEdit_clicked()
{
    // Show Donat prigovor Edit form
    Kontakt::FrmPrigovorEdit *frmPrigovorEdit = new Kontakt::FrmPrigovorEdit(this);
    frmPrigovorEdit->exec();
    delete frmPrigovorEdit;
}

void FrmPrigovorPregled::on_btnGo2_8_clicked()
{
    // Show Donat prigovor JOP form
    Kontakt::FrmPrigovorJop *frmPrigovorJop = new Kontakt::FrmPrigovorJop(this);
    frmPrigovorJop->exec();
    delete frmPrigovorJop;
}

void FrmPrigovorPregled::on_btnGo2_10_clicked()
{
    // Show Donat prigovor Osporavani Iznos Edit form
    Kontakt::FrmPrigovorOsporavaniIznos *frmPrigovorIznos = new Kontakt::FrmPrigovorOsporavaniIznos(this);
    frmPrigovorIznos->exec();
    delete frmPrigovorIznos;
}

void FrmPrigovorPregled::on_btnGo2_11_clicked()
{
//    // Show Donat prigovor JOP form
//    Kontakt::FrmPrigovorJop *frmPrigovorJop = new Kontakt::FrmPrigovorJop(this);
//    frmPrigovorJop->exec();
//    delete frmPrigovorJop;
}

void FrmPrigovorPregled::on_btnGo2_18_clicked()
{
    // Show Donat prigovor Pisano rješenje form
    Kontakt::FrmPrigovorPisanoRjesenje *frmPrigovorPisanoRjesenje = new Kontakt::FrmPrigovorPisanoRjesenje(this);
    frmPrigovorPisanoRjesenje->exec();
    delete frmPrigovorPisanoRjesenje;
}

void FrmPrigovorPregled::on_btnKontaktDokumenti_clicked()
{
    // Show Donat prigovor prilozeni dokumenti form
    Kontakt::FrmKontaktDokumenti1 *frmKontaktDokumenti = new Kontakt::FrmKontaktDokumenti1(m_iKontaktId , this);
    frmKontaktDokumenti->exec();
    delete frmKontaktDokumenti;
}



void FrmPrigovorPregled::on_cboVoditeljGrupe_currentIndexChanged(const QString &strKorisnikId)
{
    if(strKorisnikId == "SVI AGENTI")
    {
        m_strAktivniKorisnikId.clear();
    }
    else
    {
        m_strAktivniKorisnikId = ui->cboVoditeljGrupe->currentData().toString().toStdString();
    }
}

void FrmPrigovorPregled::on_treePrigovori_itemPressed(QTreeWidgetItem *itemPrigovor, int UNUSED(column))
{
    m_iPrigovorId = itemPrigovor->text(2).toInt();
    m_iStavkaId = itemPrigovor->text(3).toInt();

    if(itemPrigovor->parent())
    {
        popuniPrigovor();
    }
    else
    {
        m_iPrigovorId = 0;
        m_iStavkaId = 0;
        clearPrigovor();
    }
}

}








