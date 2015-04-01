//
//  frmkontaktnicentar.cpp
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

#include "frmkontaktnicentar.h"
#include "ui_frmkontaktnicentar.h"

#include "forms/kontakt/frmkontaktnicentaruser.h"
#include "forms/kontakt/frmkontaktnicentarpretraga.h"
#include "forms/stranka/frmstrankaocv.h"


#include "itos.h"
#include "ocinumber.h"

namespace Kontakt {

/* [Class Contructor] */
FrmKontaktniCentar::FrmKontaktniCentar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmKontaktniCentar)
{
    ui->setupUi(this);

    //////////////////////////////////////////////////////////
    // Center Main Form on Screen
    //////////////////////////////////////////////////////////

//    window->setGeometry(
//        QStyle::alignedRect(
//            Qt::LeftToRight,
//            Qt::AlignCenter,
//            window->size(),
//            qApp->desktop()->availableGeometry()
//        ));


    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    windowSize = size();
    width = windowSize.width();
    height = windowSize.height();

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;

    move ( x, y );

    //setFixedSize(windowSize.width(), windowSize.height());

    //////////////////////////////////////////////////////////


    ui->lblStatusBarInfo->setText(QString::fromStdString(g_GRP_NAZ) + tr(" ... ") + QString::fromStdString(g_KORISNIK_NAZ));
    ui->lblStatusBarInfo->setToolTip(tr("ROLA : ") + QString::number(g_GRP_NO) + tr(" ROLA_TIP : ") + QString::number(g_GRP_TIP));
    ui->lblStatusBarInfo->setStatusTip(tr("ROLA : ") + QString::number(g_GRP_NO) + tr(" ROLA_TIP : ") + QString::number(g_GRP_TIP));
    // ui->lblStatusBarDatum->setText(QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")));
    ui->lblTime->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));
    ui->lblTime->setToolTip(QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")));
    ui->fraInteraction->setVisible(false);
    ui->fraInteractionActions->setVisible(false);
    ui->fraImovina->setVisible(true);
    ui->fraImovinaStatus->setVisible(true);

    m_iAktivnostNo = 0;
    popunaRole();
    popunaAnonimniKupacVrijednost();
}

FrmKontaktniCentar::FrmKontaktniCentar(QWidget *parent, string strTelefonskiBroj) :
    QMainWindow(parent),
    ui(new Ui::FrmKontaktniCentar)
{
    ui->setupUi(this);

    //////////////////////////////////////////////////////////
    // Center Main Form on Screen
    //////////////////////////////////////////////////////////

//    window->setGeometry(
//        QStyle::alignedRect(
//            Qt::LeftToRight,
//            Qt::AlignCenter,
//            window->size(),
//            qApp->desktop()->availableGeometry()
//        ));


    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    windowSize = size();
    width = windowSize.width();
    height = windowSize.height();

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;

    move ( x, y );

    //setFixedSize(windowSize.width(), windowSize.height());

    //////////////////////////////////////////////////////////

    ui->lblStatusBarInfo->setText(QString::fromStdString(g_GRP_NAZ) + tr(" ... ") + QString::fromStdString(g_KORISNIK_NAZ));
    ui->lblStatusBarInfo->setToolTip(tr("ROLA : ") + QString::number(g_GRP_NO) + tr(" ROLA_TIP : ") + QString::number(g_GRP_TIP));
    ui->lblStatusBarInfo->setStatusTip(tr("ROLA : ") + QString::number(g_GRP_NO) + tr(" ROLA_TIP : ") + QString::number(g_GRP_TIP));
    // ui->lblStatusBarDatum->setText(QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")));
    ui->lblTime->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));
    ui->lblTime->setToolTip(QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")));
    ui->fraInteraction->setVisible(false);
    ui->fraInteractionActions->setVisible(false);
    ui->fraImovina->setVisible(true);
    ui->fraImovinaStatus->setVisible(true);

    if(strTelefonskiBroj == "0")
    {
        m_strTelefonskiBroj = "";
    }
    else
    {
        m_strTelefonskiBroj = strTelefonskiBroj;
        ui->txtFltBrojTelefona->setText(QString::fromStdString(m_strTelefonskiBroj));
    }

    m_iAktivnostNo = 0;
    popunaRole();
    popunaAnonimniKupacVrijednost();

    popunaUpit();
}

/* [Class Destructor] */
FrmKontaktniCentar::~FrmKontaktniCentar()
{
    delete ui;
}

/* [Private Member Functions] */
/*  Popuna forme  */
void FrmKontaktniCentar::initForm()
{
}

void FrmKontaktniCentar::popunaRole()
{
    /* ROLA CODE ------------------------------------------- */

    m_iAKT_CODE_LOG = 0;
    m_iAKT_CODE = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT COUNT(*) BROJ FROM VEZE_KORISNIKA WHERE KORISNIK_ID='");
    strSqlStatement.append(g_DonatUser);
    strSqlStatement.append("'  AND KORISNIK_ID_2 = 'ROLA_FORMA_LOG' ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    int iBroj = 0;
    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iBroj = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
        iBroj = 0;
    }

    if(iBroj > 0)
    {
        m_iAKT_CODE_LOG = 1;
    }

    strSqlStatement.clear();
    strSqlStatement.append("SELECT COUNT(*) BROJ FROM KONTAKT_STAT_GR G,KONTAKT_GRUPA_KOR K WHERE K.KOR_ID='");
    strSqlStatement.append(g_DonatUser);
    strSqlStatement.append("' AND K.GRUPA_ID = G.GRUPA_ID AND G.NAD_ID = 1 ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iBroj = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iBroj > 0)
    {
        m_iAKT_CODE = 1;
    }

    /* ROLA VELEPRODAJA------------------------------------------- */
    strSqlStatement.clear();
    strSqlStatement.append("SELECT COUNT(*) BROJ FROM VEZE_KORISNIKA WHERE KORISNIK_ID = '");
    strSqlStatement.append(g_DonatUser);
    strSqlStatement.append("' AND KORISNIK_ID_2 IN ('ROLA_NP_TEST', 'ROLA_VELEPRODAJA') ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iBroj = rs->getInt(1);
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iBroj > 0)
    {
        m_iROLA_VEL_NO = 1;
    }


    strSqlStatement.clear();
    strSqlStatement.append("SELECT TREBA_LI_KON_REASON SMIJE FROM DUAL");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_iAKT_CODE_ROLA = rs->getInt(1);
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
void FrmKontaktniCentar::popunaAnonimniKupacVrijednost()
{
    m_strANONIM_VAL = "0";
    string strSqlStatement;
    strSqlStatement.append("SELECT VALUE FROM KONTAKT_OSOBE_ITEMS WHERE ID = 896076 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_strANONIM_VAL = rs->getString(1);
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
    strSqlStatement.erase();}
void FrmKontaktniCentar::popunaAnonimac()
{

    /* KUPAC-------------------------------------------  */
     m_iKUPAC_STRANKA_NO = 0;
     m_strKUPAC_MB = "";
     m_strKUPAC_ADRESA = "NEPOZNATA";
     m_strKUPAC_AD1 = "";
     m_strKUPAC_AD2 = "";
     m_iKUPAC_SEGMENT_NO = 0;
     m_strKUPAC_ZASTUPNIK_NO = "";

     m_iKUPAC_TIP_NO = 1;
     m_strKUPAC_NAZ = "ANONIMNI KUPAC";

     m_iHEAD_NO = 0;

     ui->lblKupacFormatiraniNaziv->setText(tr("ANONIMNI KUPAC"));
     ui->lblOib->clear();
     ui->lblMB->clear();
     ui->lblDatumRodjenja->clear();
     ui->lblAdresa->clear();

     m_iAKT_GIM_NO = 0;
     m_iAKT_TEL_NO = 0;
     m_strAKT_TEL_KLASA = "0";

     popunaAnonimacKontakt();

}
void FrmKontaktniCentar::popunaAnonimacKontakt()
{
//    X1 = 1932061
//    X2 = "ANONIMNA OSOBA"
//    Y1 = 896076
//    Y2 = ANONIM_VAL
//    If CC_KON_VALUE <> ANONIM_VAL Then
//            Y2 = CC_KON_VALUE
//    End If

    ui->treeKontaktOsobe->clear();



    m_iOSOBA_NO = 1932061;
    m_iOSOBA_ITEM_NO = 1932061;
    m_strOSOBA_ITEM_NAZ = "ANONIMNA OSOBA";

}

void FrmKontaktniCentar::popunaUpit()
{
    // [1. Popuni KupacId i Grupa ImovineId]
    popunaKupacTelefon1();
    // [2. Popuni Kontakt osobe]
    popunaKupacTelefon2();

    if (m_lstKupacTelefon1.empty() == true && m_lstKupacTelefon2.empty())
    {
        // Anonimni kupac
        m_iKupacId = 10639110;
        popunaAnonimac();
        return;
    }
    else
    {
        if(m_lstKupacTelefon1.size() == 1)
        {
            gim_struktura_t kupacTelefon = m_lstKupacTelefon1.front();
            m_iKupacId = kupacTelefon.KupacId;
            m_iGrupaImovineId = kupacTelefon.GrupaImovineId;
            if(kupacTelefon.Status > 0)
            {
                m_iAKT_STATUS = 1;
            }
            else
            {
                m_iAKT_STATUS = 0;
            }

            popunaKupac();
            popunaOsobe();
            popunaKontakt_A();

            if(m_iGrupaImovineId != 0)
            {
                popunaUlogaStranke();
            }
            else
            {
                popunaGrupaImovine();
            }

            popuniInfoPanel();
        }
        else if(m_lstKupacTelefon2.empty() == false)
        {
            gim_struktura_t kupacTelefon = m_lstKupacTelefon2.front();
            m_iKupacId = kupacTelefon.KupacId;
            m_iGrupaImovineId = kupacTelefon.GrupaImovineId;

            popunaKupac();
            popunaOsobe();
            popunaKontakt_A();

            if(m_iGrupaImovineId != 0)
            {
                popunaUlogaStranke();
            }
            else
            {
                popunaGrupaImovine();
            }

            popuniInfoPanel();
        }
        else
        {
            popuniKupceNaoDabir();
        }

    }

}
void FrmKontaktniCentar::popunaKupacTelefon1()
{
    if(m_strTelefonskiBroj.length() == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT NVL(KUPAC_ID, 0) KUPAC_ID, NAZIV_KONTAKTA(KUPAC_ID) KUPAC_NAZ, NVL(GIMOVINE_ID, 0) GIMOVINE_ID, ");
    strSqlStatement.append("NVL(SLOG_STATUS, 100) SLOG_STATUS FROM V_TEL_BROJ WHERE TEL_BROJ = '");
    strSqlStatement.append(m_strTelefonskiBroj);
    strSqlStatement.append("' and TEL_LIN_ID != 'WLR' ");
    strSqlStatement.append("ORDER BY SLOG_STATUS DESC, TO_DATE(DATUM_OD,'dd.mm.yyyy hh24:mi:ss') DESC, ROWNUM");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    m_lstKupacTelefon1.clear();

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            gim_struktura_t  gim;
            gim.KupacId = rs->getUInt(1);
            gim.KupacNaziv = rs->getString(2);
            gim.GrupaImovineId = rs->getUInt(3);
            gim.Status = rs->getInt(4);
            m_iKupacId = gim.KupacId;
            m_lstKupacTelefon1.push_back(gim);
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
void FrmKontaktniCentar::popunaKupacTelefon2()
{
    if(m_strTelefonskiBroj.length() == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT KUPAC_ID, NAZIV_KONTAKTA(KUPAC_ID) KUPAC_NAZ, NVL(MAX(LAST_GIM), 0) LAST_GIM ");
    strSqlStatement.append("FROM KONTAKT_OSOBE_ITEMS WHERE VALUE = '");
    strSqlStatement.append(m_strTelefonskiBroj);
    strSqlStatement.append("' ");
    if (m_iKupacId != 0)
    {
        strSqlStatement.append(" AND KUPAC_ID != ");
        strSqlStatement.append(cttl::itos(m_iKupacId));
    }
    strSqlStatement.append(" GROUP BY KUPAC_ID ORDER BY 2 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    m_lstKupacTelefon2.clear();

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            gim_struktura_t  gim;
            gim.KupacId = rs->getUInt(1);
            gim.KupacNaziv = rs->getString(2);
            gim.GrupaImovineId = rs->getUInt(3);
            gim.Status = 100;
            m_lstKupacTelefon2.push_back(gim);
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

void FrmKontaktniCentar::popunaKupac()
{
    if(m_iKupacId == 0)
    {
        return;
    }

    if(popunaKupac_ProvjeriStanje() == false)
    {
        return;
    }




}
bool FrmKontaktniCentar::popunaKupac_ProvjeriStanje()
{
    bool retValue = false;

    string strSqlStatement;
    strSqlStatement.append("BEGIN provjeri_stanje(:p_kupac_id ,:p_gimovine_id, :rezultat); END;");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        Number nProva = cttl::getONumber(m_iKupacId);
        sqlStatement->setNumber(1, nProva);
        sqlStatement->setNull(2, OCCINUMBER);
        sqlStatement->registerOutParam(3, OCCISTRING, 2000);
        sqlStatement->executeUpdate();
        string strMessage = sqlStatement->getString(3);

        if(strMessage == "0")
        {
            retValue = true;
        }
        else
        {
            retValue = false;
            QMessageBox::critical(this, tr("DONAT - Kontaktni Centar"),
                                           QString::fromStdString(strMessage),
                                           QMessageBox::Close);
        }
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

void FrmKontaktniCentar::popuniKupceNaoDabir()
{
}
void FrmKontaktniCentar::popunaOsobe()
{
}
void FrmKontaktniCentar::popunaUlogaStranke()
{
}
void FrmKontaktniCentar::popunaGrupaImovine()
{
}

void FrmKontaktniCentar::popunaKontakt_A()
{
}

void FrmKontaktniCentar::popuniInfoPanel()
{
}



/* [Event Handlers] */
void FrmKontaktniCentar::on_btnChangeUserRole_clicked()
{
    // Show Donat kontact role selection form
    Kontakt::FrmKontaktniCentarUser *frmKontaktniCentarUser = new Kontakt::FrmKontaktniCentarUser(this, 0);
    frmKontaktniCentarUser->exec();
    delete frmKontaktniCentarUser;

    ui->lblStatusBarInfo->setText(QString::fromStdString(g_GRP_NAZ) + tr(" ... ") + QString::fromStdString(g_KORISNIK_NAZ));
    ui->lblStatusBarInfo->setToolTip(tr("ROLA : ") + QString::number(g_GRP_NO) + tr(" ROLA_TIP : ") + QString::number(g_GRP_TIP));
    ui->lblStatusBarInfo->setStatusTip(tr("ROLA : ") + QString::number(g_GRP_NO) + tr(" ROLA_TIP : ") + QString::number(g_GRP_TIP));
    // ui->lblStatusBarDatum->setText(QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")));
    ui->lblTime->setText(QDateTime::currentDateTime().toString(tr("hh:mm")));
    ui->lblTime->setToolTip(QDateTime::currentDateTime().toString(tr("dd.MM.yyyy")));
}

void FrmKontaktniCentar::on_btnContactSearch_clicked()
{
    // Show Donat kontact search form
    Kontakt::FrmKontaktniCentarPretraga *frmContactSearch = new Kontakt::FrmKontaktniCentarPretraga(this);
    frmContactSearch->exec();
    delete frmContactSearch;
}

void FrmKontaktniCentar::on_btnOsf_clicked()
{
    if(ui->lblOib->text().isEmpty())
    {
        return;
    }

    // Show OSF web
    Stranka::FrmStrankaOcv *frmOcv = new Stranka::FrmStrankaOcv(ui->lblOib->text().toStdString());
    frmOcv->exec();
    delete frmOcv;
}

void FrmKontaktniCentar::on_btnList_clicked()
{

}

void FrmKontaktniCentar::on_btnAnonymous_clicked()
{

}

void FrmKontaktniCentar::on_btnIdentification_clicked()
{

}


void FrmKontaktniCentar::on_btnTipStranke_2_clicked()
{

}

void FrmKontaktniCentar::on_btnRacunStranke_clicked()
{

}

void FrmKontaktniCentar::on_btnStrankaBiljeska_clicked()
{

}

void FrmKontaktniCentar::on_btnStrankaIzjave_clicked()
{

}

void FrmKontaktniCentar::on_btnStrankaTipInfo_clicked()
{

}

void FrmKontaktniCentar::on_btnStrankaRacunInfo_clicked()
{

}

void FrmKontaktniCentar::on_btnStrankaBiljeskaInfo_clicked()
{

}

void FrmKontaktniCentar::on_btnStrankaIzjaveInfo_clicked()
{

}

void FrmKontaktniCentar::on_btnMjerenjeBrzine_clicked()
{

}

void FrmKontaktniCentar::on_btnUgovorneObveze_clicked()
{

}

void FrmKontaktniCentar::on_btnStrankaEdit_clicked()
{

}

void FrmKontaktniCentar::on_btnEmailEdit_clicked()
{

}

void FrmKontaktniCentar::on_btnTipKupcaEdit_clicked()
{

}

void FrmKontaktniCentar::on_btnInstalacijaEdit_clicked()
{

}

void FrmKontaktniCentar::on_btnRacunEdit_clicked()
{

}

void FrmKontaktniCentar::on_btnLoyaltyEdit_clicked()
{

}

void FrmKontaktniCentar::on_btnTreeImovinaExpand_clicked()
{
    ui->treeImovina->expandAll();
}

void FrmKontaktniCentar::on_btnTreeImovinaColapse_clicked()
{
    ui->treeImovina->collapseAll();
}

void FrmKontaktniCentar::on_btnKontakOsobeExpand_clicked()
{
    ui->treeKontaktOsobe->expandAll();
}

void FrmKontaktniCentar::on_btnKontakOsobeColapse_clicked()
{
    ui->treeKontaktOsobe->collapseAll();
}

void FrmKontaktniCentar::on_btnKontakiExpand_clicked()
{
    ui->treeKontakti->expandAll();
}

void FrmKontaktniCentar::on_btnKontakiColapse_clicked()
{
    ui->treeKontakti->collapseAll();
}

void FrmKontaktniCentar::on_btnOdustani_clicked()
{
    if(ui->treeStavkeKontakta->topLevelItemCount() > 0)
    {
        QMessageBox::information(this, tr("DONAT - Kontaktni Centar"),
                                 tr("Uklonite unesene stavke kontakta."),
                                 QMessageBox::Close);
    }
    else
    {
        this->close();
    }
}

}








