#include "frmpregledsporazuma.h"
#include "ui_frmpregledsporazuma.h"

#include "itos.h"

namespace Sporazumi {

// [Class constructor]
FrmPregledSporazuma::FrmPregledSporazuma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPregledSporazuma)
{
    ui->setupUi(this);

    ui->m_twStavkeSporazuma->setColumnWidth(0, 480);
    ui->m_twStavkeSporazuma->setColumnWidth(1, 35);
    ui->m_twStavkeSporazuma->setColumnWidth(2, 80);
    ui->m_twStavkeSporazuma->setColumnWidth(3, 80);
    ui->m_twStavkeSporazuma->setColumnWidth(4, 1);
    ui->m_fraStornirao->setVisible(false);
    ui->btnProtvrdaUgovora->setEnabled(false);
    ui->m_btnPotvrdaObavijesti->setEnabled(false);
    ui->m_btnObavijest->setEnabled(false);
    ui->m_btnUgovor->setEnabled(false);
    ui->m_btnUgovorObavijest->setEnabled(false);
}

FrmPregledSporazuma::FrmPregledSporazuma(unsigned int iSporazumId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPregledSporazuma)
{
    ui->setupUi(this);

    ui->m_twStavkeSporazuma->setColumnWidth(0, 480);
    ui->m_twStavkeSporazuma->setColumnWidth(1, 35);
    ui->m_twStavkeSporazuma->setColumnWidth(2, 80);
    ui->m_twStavkeSporazuma->setColumnWidth(3, 80);
    ui->m_twStavkeSporazuma->setColumnWidth(4, 1);
    ui->m_fraStornirao->setVisible(false);
    ui->btnProtvrdaUgovora->setEnabled(false);
    ui->m_btnPotvrdaObavijesti->setEnabled(false);
    ui->m_btnObavijest->setEnabled(false);
    ui->m_btnUgovor->setEnabled(false);
    ui->m_btnUgovorObavijest->setEnabled(false);

    m_iSporazumId = iSporazumId;
    getSporazum(m_iSporazumId);
}

FrmPregledSporazuma::FrmPregledSporazuma(string strBrojDokumenta, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPregledSporazuma)
{
    ui->setupUi(this);

    ui->m_twStavkeSporazuma->setColumnWidth(0, 480);
    ui->m_twStavkeSporazuma->setColumnWidth(1, 35);
    ui->m_twStavkeSporazuma->setColumnWidth(2, 80);
    ui->m_twStavkeSporazuma->setColumnWidth(3, 80);
    ui->m_twStavkeSporazuma->setColumnWidth(4, 1);
    ui->m_fraStornirao->setVisible(false);
    ui->btnProtvrdaUgovora->setEnabled(false);
    ui->m_btnPotvrdaObavijesti->setEnabled(false);
    ui->m_btnObavijest->setEnabled(false);
    ui->m_btnUgovor->setEnabled(false);
    ui->m_btnUgovorObavijest->setEnabled(false);

    m_strBrojDokumenta = strBrojDokumenta;
    getSporazum(m_strBrojDokumenta);
}

// [Private Member Functions]
void FrmPregledSporazuma::clearFormData()
{
    ui->m_twStavkeSporazuma->clearContents();
    ui->m_fraStornirao->setVisible(false);
    ui->btnProtvrdaUgovora->setEnabled(false);
    ui->m_btnPotvrdaObavijesti->setEnabled(false);
    ui->m_btnObavijest->setEnabled(false);
    ui->m_btnUgovor->setEnabled(false);
    ui->m_btnUgovorObavijest->setEnabled(false);
}

void FrmPregledSporazuma::getSporazumStavke(unsigned int iSporazumId)
{
    if(iSporazumId == 0)
        return;

    std::list<RowStavkaSporazuma> lstStavkaSporazuma;

	string strSqlStatement;
	strSqlStatement.append("SELECT FORMATIRANI_NAZIV_SS(S.SRZSTAVKA_ID) NAZIV_PRODUKTA, S.SRZSTAVKA_ID, S.KOLICINA, S.IZNOS1, S.IZNOS2 ");
	strSqlStatement.append("FROM STAVKE_SPORAZUMA S, PRODUKTI P ");
	strSqlStatement.append("WHERE S.PRODUKT_ID = P.PRODUKT_ID AND ");
	strSqlStatement.append(cttl::itos(m_iSporazumId));
	strSqlStatement.append(" IN (S.SRZ_UGOVOR_ID, S.SPORAZUM_ID) ORDER BY RBR ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            double dKolicina = rs->getDouble(3);
            if(dKolicina != 0)
            {
                RowStavkaSporazuma rowSrzStavka;
                rowSrzStavka.StavkaSporazumaId = rs->getUInt(2);
                rowSrzStavka.Naziv = rs->getString(1);
                rowSrzStavka.Kolicina = dKolicina;
                rowSrzStavka.Iznos1 = rs->getDouble(4);
                rowSrzStavka.Iznos1 = rs->getDouble(5);
                lstStavkaSporazuma.push_back(rowSrzStavka);
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

//    RowStavkaSporazuma rowSrzStavka;
    list<RowStavkaSporazuma>::const_iterator itSrzStavka;
    for(itSrzStavka=lstStavkaSporazuma.begin(); itSrzStavka!=lstStavkaSporazuma.end(); ++itSrzStavka)
    {
        int row = ui->m_twStavkeSporazuma->rowCount();
        ui->m_twStavkeSporazuma->insertRow(row);
        itSrzStavka->Naziv;
        ui->m_twStavkeSporazuma->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(itSrzStavka->Naziv)));
        QString strKolicina;
        strKolicina.setNum(itSrzStavka->Kolicina, 'f', 0);
        if(strKolicina.isEmpty() == false)
        {
            strKolicina.replace(tr("."), tr(","));
        }
        ui->m_twStavkeSporazuma->setItem(row, 1, new QTableWidgetItem(strKolicina));
        QString strJednokratno;
        strJednokratno.setNum(itSrzStavka->Iznos1, 'f', 2);
        if(strJednokratno.isEmpty() == false)
        {
            strJednokratno.replace(tr("."), tr(","));
        }
        ui->m_twStavkeSporazuma->setItem(row, 2, new QTableWidgetItem(strJednokratno));
        QString strPretplata;
        strPretplata.setNum(itSrzStavka->Iznos2, 'f', 2);
        if(strPretplata.isEmpty() == false)
        {
            strPretplata.replace(tr("."), tr(","));
        }
        ui->m_twStavkeSporazuma->setItem(row, 3, new QTableWidgetItem(strPretplata));
        ui->m_twStavkeSporazuma->setItem(row, 4, new QTableWidgetItem(QString::number(itSrzStavka->StavkaSporazumaId)));


        strSqlStatement.clear();
        strSqlStatement.append("SELECT /*+ RULE */ SRZSTAVKA_ID, NAZIV||':     '||NVL(SHOWN_VALUE,'-') ATRIBUT ");
        strSqlStatement.append("FROM V_STSRZ_ATRIBUTI WHERE SRZSTAVKA_ID = ");
        strSqlStatement.append(cttl::itos(itSrzStavka->StavkaSporazumaId));
        sqlStatement->setSQL(strSqlStatement);

        int iAtributNo = 1;
        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                int row = ui->m_twStavkeSporazuma->rowCount();
                ui->m_twStavkeSporazuma->insertRow(row);
                string strAtributRow;
                strAtributRow.append("     ");
                strAtributRow.append(cttl::itos(iAtributNo));
                strAtributRow.append(" - ");
                strAtributRow.append(rs->getString(2));
                ui->m_twStavkeSporazuma->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(strAtributRow)));
                ++iAtributNo;
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

void FrmPregledSporazuma::getSporazum(string strBrojDokumenta)
{
    if(strBrojDokumenta.empty() == true)
        return;

	int iStatusId;
	string strInUlogeStanke;
	string strSqlStatement;
	strSqlStatement.append("SELECT /*+ RULE */ T.NAZIV, KP.NAZIV KANAL_PRODAJE, S.SPORAZUM_ID, NVL(TO_CHAR(S.DATUM_OD,'DD.MM.YYYY'),' ') DATUM_OD, ");
	strSqlStatement.append("KUPAC_ID, ISPORUKA_ID, KONTAKT_ID, NAPLATA_ID, NVL(KORISNIKUSL_ID,0) KORISNIKUSL_ID, NVL(ODGOSOBA_ID,0) ODGOSOBA_ID, BROJ_DOK,S.CREATED_BY OPERATER, ");
	strSqlStatement.append("ST.NAZIV STATUS, S.STATUS_ID ,KO.NAZIV PRODAO_KORISNIK, OJ.NAZIV PRODAO_ODJEL, S.NAPOMENA, NVL(TO_CHAR(S.DATE_CREATED,'DD.MM.YYYY'),' ') DATUM_UNOSA, ");
	strSqlStatement.append("KO2.NAZIV UNIO_KORISNIK, OJ2.NAZIV UNIO_ODJEL ");
	strSqlStatement.append("FROM SPORAZUMI S, TIPOVI_DOKUMENATA T, KANALI_PRODAJE KP, KORISNICI KO, ORG_JEDINICE OJ, STATUS ST, KORISNICI KO2, ORG_JEDINICE OJ2 ");
	strSqlStatement.append("WHERE S.TSPORAZUMA_ID = T.TSPORAZUMA_ID ");
	strSqlStatement.append("AND S.PROD_KORI_ID=KO.KORISNIK_ID AND S.PROD_ORGJED_ID = OJ.ORGJED_ID AND S.STATUS_ID = ST.STATUS_ID AND S.CREATED_BY = KO2.KORISNIK_ID AND KO2.ODJEL_ID = OJ2.ORGJED_ID ");
	strSqlStatement.append("AND S.KANAL_ID=KP.KANAL_ID(+) AND ST.TABLICA='SPORAZUMI' ");
	strSqlStatement.append("AND S.BROJ_DOK='");
	strSqlStatement.append(strBrojDokumenta);
	strSqlStatement.append("' ");
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            // [0] Zahtjev
            ui->m_lblZahtjev->setText(QString::fromStdString(rs->getString(1)));
            ui->m_lblBrojUgovora->setText(QString::fromStdString(rs->getString(11)));
            ui->m_lblDatumZahtjeva->setText(QString::fromStdString(rs->getString(4)));
            ui->m_lblStatusZahtjeva->setText(QString::fromStdString(rs->getString(13)));
            ui->m_lblNapomena->setText(QString::fromStdString(rs->getString(17)));
            // [2] Prodao
            ui->m_lblProdaoOrgJed->setText(QString::fromStdString(rs->getString(16)));
            ui->m_lblProdaoOsoba->setText(QString::fromStdString(rs->getString(15)));
            ui->m_lblProdaoKanal->setText(QString::fromStdString(rs->getString(2)));
            ui->m_lblProdaoDatum->setText(QString::fromStdString(rs->getString(4)));
            // [2] Unio
            ui->m_lblUnioOrgJed->setText(QString::fromStdString(rs->getString(20)));
            ui->m_lblUnioOsoba->setText(QString::fromStdString(rs->getString(19)));
            ui->m_lblUnioDatum->setText(QString::fromStdString(rs->getString(18)));

            m_iSporazumId = rs->getUInt(3);
            iStatusId = rs->getInt(14);
//            strInUlogeStanke.append("(");
//            strInUlogeStanke.append(cttl::itos(rs->getUInt(5)));
//            strInUlogeStanke.append(",");
//            strInUlogeStanke.append(cttl::itos(rs->getUInt(7)));
//            strInUlogeStanke.append(",");
//            strInUlogeStanke.append(cttl::itos(rs->getUInt(6)));
//            strInUlogeStanke.append(",");
//            strInUlogeStanke.append(cttl::itos(rs->getUInt(8)));
//            strInUlogeStanke.append(",");
//            strInUlogeStanke.append(cttl::itos(rs->getUInt(9)));
//            strInUlogeStanke.append(",");
//            strInUlogeStanke.append(cttl::itos(rs->getUInt(10)));
//            strInUlogeStanke.append(")");
            strInUlogeStanke.append("(");
            strInUlogeStanke.append(rs->getString(5));
            strInUlogeStanke.append(",");
            strInUlogeStanke.append(rs->getString(7));
            strInUlogeStanke.append(",");
            strInUlogeStanke.append(rs->getString(6));
            strInUlogeStanke.append(",");
            strInUlogeStanke.append(rs->getString(8));
            strInUlogeStanke.append(",");
            strInUlogeStanke.append(rs->getString(9));
            strInUlogeStanke.append(",");
            strInUlogeStanke.append(rs->getString(10));
            strInUlogeStanke.append(")");
        }
        sqlStatement->closeResultSet(rs);
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    if(iStatusId == 5)
    {
        // [3] Stornirao
        ui->m_fraStornirao->setVisible(true);
        strSqlStatement.clear();
        strSqlStatement.append("SELECT KO.NAZIV STORNIRAO_KORISNIK, OJ.NAZIV STORNIRAO_ODJEL, NVL(TO_CHAR(PP.DATE_MODIFIED, 'DD.MM.YYYY HH24:MI:SS'), ' ') DATUM_STORNIRANJA ");
        strSqlStatement.append("FROM DNEVNIK_PROCESA DP, POSLOVNI_PROCESI PP, KORISNICI KO, ORG_JEDINICE OJ ");
        strSqlStatement.append("WHERE DP.PROCES_ID=PP.PROCES_ID AND KO.KORISNIK_ID = DP.KORISNIK_ID And KO.ODJEL_ID = OJ.ORGJED_ID And ID2 = ");
        strSqlStatement.append(cttl::itos(m_iSporazumId));
        strSqlStatement.append(" AND NVL(DP.STANJE_ID, 0) = 2008 AND NVL(TABLICA2, '0') = 'SPORAZUMI' AND ROWNUM = 1 ");
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            if(rs->next())
            {
                ui->m_lblStorniraoOrgJed->setText(QString::fromStdString(rs->getString(2)));
                ui->m_lblStorniraoOsoba->setText(QString::fromStdString(rs->getString(1)));
                ui->m_lblStorniraoDatum->setText(QString::fromStdString(rs->getString(3)));
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
        strSqlStatement.append("SELECT STORNO_NAPOMENA,RS.NAZIV RAZLOG_STORNIRANJA ");
        strSqlStatement.append("FROM SPORAZUMI S,RAZLOZI_STORNO RS ");
        strSqlStatement.append("WHERE(S.RAZLOGSTORNO_ID = RS.RAZLOGSTORNO_ID) ");
        strSqlStatement.append("AND SPORAZUM_ID = ");
        strSqlStatement.append(cttl::itos(m_iSporazumId));
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            if(rs->next())
            {
                ui->m_lblStorniraoRazlog->setText(QString::fromStdString(rs->getString(1)));
                ui->m_lblStorniraoNapomena->setText(QString::fromStdString(rs->getString(2)));
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

    // [4] Uloge stranke
    strSqlStatement.clear();
    strSqlStatement.append("SELECT ULSTRANKE_ID, NAZIV_ULSTR, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA, TULSTRANKE_ID ");
    strSqlStatement.append("FROM HIJERARHIJA_STR_ADRESE2 WHERE ULSTRANKE_ID IN ");
    strSqlStatement.append(strInUlogeStanke);
    strSqlStatement.append("  ORDER BY TULSTRANKE_ID ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            string strId;
            strId.append(rs->getString(2));
            strId.append(" - ");
            strId.append(cttl::itos(rs->getUInt(1)));
            ui->m_lblKupacId->setText(QString::fromStdString(strId));
            string strNaziv;
            strNaziv.append("     ");
            strNaziv.append(rs->getString(3));
            ui->m_lblKupacNaziv->setText(QString::fromStdString(strNaziv));
            string strAdresa;
            strAdresa.append("     ");
            strAdresa.append(rs->getString(4));
            ui->m_lblKupacAdresa->setText(QString::fromStdString(strAdresa));
        }
        if(rs->next())
        {
            string strId;
            strId.append(rs->getString(2));
            strId.append(" - ");
            strId.append(cttl::itos(rs->getUInt(1)));
            ui->m_lblKontaktId->setText(QString::fromStdString(strId));
            string strNaziv;
            strNaziv.append("     ");
            strNaziv.append(rs->getString(3));
            ui->m_lblKontaktNaziv->setText(QString::fromStdString(strNaziv));
            string strAdresa;
            strAdresa.append("     ");
            strAdresa.append(rs->getString(4));
            ui->m_lblKontaktAdresa->setText(QString::fromStdString(strAdresa));
        }
        if(rs->next())
        {
            string strId;
            strId.append(rs->getString(2));
            strId.append(" - ");
//            strId.append(cttl::itos(rs->getUInt(1)));
            strId.append(rs->getString(1));
            ui->m_lblRacunId->setText(QString::fromStdString(strId));
            string strNaziv;
            strNaziv.append("     ");
            strNaziv.append(rs->getString(3));
            ui->m_lblRacunNaziv->setText(QString::fromStdString(strNaziv));
            string strAdresa;
            strAdresa.append("     ");
            strAdresa.append(rs->getString(4));
            ui->m_lblRacunAdresa->setText(QString::fromStdString(strAdresa));
        }
        if(rs->next())
        {
            string strId;
            strId.append(rs->getString(2));
            strId.append(" - ");
            strId.append(cttl::itos(rs->getUInt(1)));
            ui->m_lblInstalacijaId->setText(QString::fromStdString(strId));
            string strNaziv;
            strNaziv.append("     ");
            strNaziv.append(rs->getString(3));
            ui->m_lblInstalacijaNaziv->setText(QString::fromStdString(strNaziv));
            string strAdresa;
            strAdresa.append("     ");
            strAdresa.append(rs->getString(4));
            ui->InstalacijaAdresa->setText(QString::fromStdString(strAdresa));
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

    getSporazumStavke(m_iSporazumId);
    getStanjeUgovora(m_iSporazumId);
    getStanjeObavijesti(m_iSporazumId);
}

void FrmPregledSporazuma::getSporazum(unsigned int iSporazumId)
{
    if(iSporazumId == 0)
        return;

	string strSqlStatement;
	strSqlStatement.append("SELECT BROJ_DOK FROM SPORAZUMI WHERE SPORAZUM_ID = ");
	strSqlStatement.append(cttl::itos(m_iSporazumId));
	Statement *sqlStatement = g_DonatConn->createStatement();
	sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            m_strBrojDokumenta = rs->getString(1);
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

    getSporazum(m_strBrojDokumenta);
}

void FrmPregledSporazuma::getStanjeUgovora(unsigned int iSporazumId)
{
    string strSqlStatement;

    strSqlStatement.append("SELECT /*+ RULE */ P.PROCES_ID, P.STANJE_ID STANJE_P, NVL(TO_CHAR(P.DATE_MODIFIED, 'DD.MM.YYYY HH24:MI:SS'), '-') DATUM_ST, ");
    strSqlStatement.append("S.BROJ_DOK UGOVOR_ID FROM POSLOVNI_PROCESI P, SPORAZUMI S ");
    strSqlStatement.append("WHERE P.ID2 = S.SPORAZUM_ID AND nvl(P.STANJE_ID_PP, 0) = 2050 AND nvl(P.TABLICA2, '0') = 'SPORAZUMI' AND ");
    strSqlStatement.append(cttl::itos(iSporazumId));
    strSqlStatement.append(" IN (SPORAZUM_ID, GLAVNI_SRZ_ID) AND S.VSPORAZUMA_ID > 0 ");
    strSqlStatement.append("ORDER BY 2 ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            int iStanjeUgovora = rs->getInt(2);
            string strDatum = rs->getString(3);

            switch (iStanjeUgovora)
            {
                case 2051: // REZERVACIJA
                {
                    ui->m_lblUgovorText->setText(QString::fromStdString(strDatum) + tr("   Rezervacija ugovora"));
                    ui->m_btnUgovor->setEnabled(true);
                    ui->btnProtvrdaUgovora->setEnabled(true);
                    break;
                }
                case 2058: // REZERVIRAN
                {
                    ui->m_lblUgovorText->setText(QString::fromStdString(strDatum) + tr("   Rezerviran ugovor"));
                    ui->m_btnUgovor->setEnabled(true);
                    ui->btnProtvrdaUgovora->setEnabled(true);
                    break;
                }
                case 2059: // ODOBREN
                {
                    ui->m_lblUgovorText->setText(QString::fromStdString(strDatum) + tr("   Rezervirani ugovor odobren"));
                    ui->m_btnUgovor->setEnabled(true);
                    ui->btnProtvrdaUgovora->setEnabled(true);
                    break;
                }
                case 2056: // UGOVORENO
                {
                    ui->m_lblUgovorText->setText(QString::fromStdString(strDatum) + tr("   Potpisan ugovor"));
                    ui->m_btnUgovor->setEnabled(true);
                    ui->btnProtvrdaUgovora->setEnabled(false); break;
                }
                case 2052: // STRANKA PRISUTNA
                {
                    ui->m_lblUgovorText->setText(QString::fromStdString(strDatum) + tr("   Čekanje na potpis ugovora"));
                    ui->m_btnUgovor->setEnabled(true);
                    ui->m_btnUgovorObavijest->setEnabled(true);
                    ui->btnProtvrdaUgovora->setEnabled(true);
                    break;
                }
                case 2054: // POSLANA OBAVIJEST
                {
                    ui->m_lblUgovorText->setText(QString::fromStdString(strDatum) + tr("   Poslana obavijest"));
                    ui->m_btnUgovor->setEnabled(true);
                    ui->btnProtvrdaUgovora->setEnabled(true);
                    break;
                }
                case 2062: //
                {
                    ui->m_lblUgovorText->setText(QString::fromStdString(strDatum) + tr("   Slanje pisma o mogućnosti"));
                    ui->m_btnUgovor->setEnabled(true);
                    ui->btnProtvrdaUgovora->setEnabled(true);
                    break;
                }
                case 2063: //
                {
                    ui->m_lblUgovorText->setText(QString::fromStdString(strDatum) + tr("   Poslano pismo o mogućnosti"));
                    ui->m_btnUgovor->setEnabled(true);
                    ui->btnProtvrdaUgovora->setEnabled(false);
                    break;
                }
                default:
                {
                    break;
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

    QString strSlanjeNaMail = QString();
    strSqlStatement.clear();
    strSqlStatement.append("SELECT TO_CHAR(SPM.DATUM, 'DD.MM.YYYY HH24:MI:SS') DATUM, spm.MAIL_TO FROM SLANJE_PISMENA sp, SLANJE_PISMENA_MAIL spm ");
    strSqlStatement.append("WHERE sp.slanje_id = spm.slanje_id(+) AND sp.sporazum_id = ");
    strSqlStatement.append(cttl::itos(iSporazumId));
    strSqlStatement.append(" AND sp.TIP_PISMENA_ID = 3 AND sp.VRSTA_SLANJA_ID = 2 AND sp.STATUS_ID = 2 ORDER BY spm.slanje_id DESC ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strSlanjeNaMail.append(tr(" - Poslano na mail "));
            strSlanjeNaMail.append(QString::fromStdString(rs->getString(2)));
            strSlanjeNaMail.append(tr(" u "));
            strSlanjeNaMail.append(QString::fromStdString(rs->getString(1)));
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

    if(strSlanjeNaMail.length() > 0)
    {
        ui->m_lblUgovorText->setText(ui->m_lblUgovorText->text() + strSlanjeNaMail);
        ui->m_lblUgovorText->setToolTip(strSlanjeNaMail);
    }
}

void FrmPregledSporazuma::getStanjeObavijesti(unsigned int iSporazumId)
{
    string strSqlStatement;

    //STANJE OBAVIJESTI. AKO NEMA OBAVIJESTI VRAĆA 0
    strSqlStatement.append("SELECT /*+ RULE */ 1 IND, MIN(P.PROCES_ID) PROCES_ID, NVL(MIN(P.STANJE_ID), 0) STANJE_P, MAX(JE_LI_TRAJNO_ISK(S.SPORAZUM_ID)) TRAJNO_IND, ");
    strSqlStatement.append("NVL(TO_CHAR(MAX(P.DATE_MODIFIED), 'DD.MM.YYYY HH24:MI:SS'), '-') DATUM_ST, ");
    strSqlStatement.append("MAX(S.TSPORAZUMA_ID) TSPORAZUMA_ID FROM POSLOVNI_PROCESI P, SPORAZUMI S WHERE P.ID2 = S.SPORAZUM_ID ");
    strSqlStatement.append("AND nvl(P.STANJE_ID_PP, 0) = 2650 AND ");
    strSqlStatement.append(cttl::itos(iSporazumId));
    strSqlStatement.append(" IN (SPORAZUM_ID, GLAVNI_SRZ_ID) AND VRATI_KTKU_RN(S.SPORAZUM_ID) > -1 ");
    strSqlStatement.append(" UNION ALL ");
    strSqlStatement.append("SELECT 2 IND, MIN(P.PROCES_ID) PROCES_ID, NVL(MIN(P.STANJE_ID), 0) STANJE_P, MAX(JE_LI_TRAJNO_ISK(S.SPORAZUM_ID)) TRAJNO_IND, ");
    strSqlStatement.append("NVL(TO_CHAR(MAX(P.DATE_MODIFIED), 'DD.MM.YYYY HH24:MI:SS'), '-') DATUM_ST, ");
    strSqlStatement.append("MAX(S.TSPORAZUMA_ID) TSPORAZUMA_ID FROM POSLOVNI_PROCESI P, SPORAZUMI S ");
    strSqlStatement.append("WHERE P.ID2 = S.SPORAZUM_ID AND nvl(P.STANJE_ID,0) IN (2021,2023,2031,2033,2017,2018,2660,2665,2047,2057) ");
    strSqlStatement.append("AND nvl(P.TABLICA2, '0') = 'SPORAZUMI' AND ");
    strSqlStatement.append(cttl::itos(iSporazumId));
    strSqlStatement.append(" IN (SPORAZUM_ID, GLAVNI_SRZ_ID) ORDER BY 1 ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            int iStanjeObavjesti = rs->getInt(3);
            string strTrajnoIskljucenje = rs->getString(4);
            string strDatum = rs->getString(5);

            switch (iStanjeObavjesti)
            {
                // SLANJE OBAVIJESTI-----XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
                case 2021: // NEDOSTAJE DOKUMENTACIJA
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   SLANJE OBAVIJESTI - Nedostaje dokumentacija"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                case 2031: // NEPODMIRENE OBVEZE
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   SLANJE OBAVIJESTI - Nepodmirene obveze"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                case 2017: // REALIZACIJA U N DANA
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   SLANJE OBAVIJESTI - Realizacija u X dana"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                case 2660: // FGSM
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   SLANJE OBAVIJESTI - FGSM"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(false); break;
                }
                case 2650: // REALIZACIJA I RASKID PRETPLATNIČKOG ODNOSA
                {
                    if(strTrajnoIskljucenje == "Y")
                    {
                        ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   SLANJE OBAVIJESTI - Raskid pretplatničkog odnosa"));
                    }
                    else
                    {
                        ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   SLANJE OBAVIJESTI - Realizacija usluge"));
                    }
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                case 2047: // STORNO ZAHTJEVA - UGOVORA
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   SLANJE OBAVIJESTI - Dokument storniran"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                case 2023: // NEDOSTAJE DOKUMENTACIJA
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   POSLANA OBAVIJEST - Nedostaje dokumentacija"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(false);
                    break;
                }
                case 2033: // NEPODMIRENE OBVEZE
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   POSLANA OBAVIJEST - Nepodmirene obveze"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                case 2018: // REALIZACIJA U N DANA
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   POSLANA OBAVIJEST - Realizacija u X dana"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                case 2665: // FGSM
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   POSLANA OBAVIJEST - FGSM"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                case 2655: // REALIZACIJA I RASKID PRETPLATNIČKOG ODNOSA
                {
                    if(strTrajnoIskljucenje == "Y")
                    {
                        ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   POSLANA OBAVIJEST - Raskid pretplatničkog odnosa"));
                    }
                    else
                    {
                        ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   POSLANA OBAVIJEST - Realizacija usluge"));
                    }
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(false);
                    break;
                }
                case 2057: // STORNO UGOVORA
                {
                    ui->m_lblObavijestText->setText(QString::fromStdString(strDatum) + tr("   POSLANA OBAVIJEST - Ugovor storniran"));
                    ui->m_btnObavijest->setEnabled(true);
                    ui->m_btnPotvrdaObavijesti->setEnabled(true);
                    break;
                }
                default:
                {
                    break;
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

    QString strSlanjeNaMail = QString();
    strSqlStatement.clear();
    strSqlStatement.append("SELECT TO_CHAR(SPM.DATUM, 'DD.MM.YYYY HH24:MI:SS') DATUM, spm.MAIL_TO FROM SLANJE_PISMENA sp, SLANJE_PISMENA_MAIL spm ");
    strSqlStatement.append("WHERE sp.slanje_id = spm.slanje_id(+) AND sp.sporazum_id = ");
    strSqlStatement.append(cttl::itos(iSporazumId));
    strSqlStatement.append(" AND sp.TIP_PISMENA_ID = 4 AND sp.VRSTA_SLANJA_ID = 2 AND sp.STATUS_ID = 2 ORDER BY spm.slanje_id DESC ");
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            strSlanjeNaMail.append(tr(" - Poslano na mail "));
            strSlanjeNaMail.append(QString::fromStdString(rs->getString(2)));
            strSlanjeNaMail.append(tr(" u "));
            strSlanjeNaMail.append(QString::fromStdString(rs->getString(1)));
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

    if(strSlanjeNaMail.length() > 0)
    {
        ui->m_lblObavijestText->setText(ui->m_lblObavijestText->text() + strSlanjeNaMail);
        ui->m_lblObavijestText->setToolTip(strSlanjeNaMail);
    }
}

// [Event Handlers]
void FrmPregledSporazuma::on_m_btnZatvori_clicked()
{

}

void FrmPregledSporazuma::on_m_btnTrazi_clicked()
{
    clearFormData();
    if(ui->m_txtFltUpit->text().isEmpty() == true)
        return;
    getSporazum(ui->m_txtFltUpit->text().toStdString());
}

FrmPregledSporazuma::~FrmPregledSporazuma()
{
    delete ui;
}

}   // namespace sporazumi


