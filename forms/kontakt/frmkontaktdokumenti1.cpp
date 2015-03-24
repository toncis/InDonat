#include "frmkontaktdokumenti1.h"
#include "ui_frmkontaktdokumenti1.h"

#include "itos.h"
#include "ocinumber.h"
#include <QDir>

namespace Kontakt {
// [ Class Constructor ]
FrmKontaktDokumenti1::FrmKontaktDokumenti1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKontaktDokumenti1)
{
    ui->setupUi(this);

    initForm();
}

FrmKontaktDokumenti1::FrmKontaktDokumenti1(unsigned int iKontaktId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKontaktDokumenti1)
{
    ui->setupUi(this);

    m_iKonatktId = iKontaktId;

    initForm();

    m_iKupacId = GetKontaktKupacId(m_iKonatktId);
    popuniKupca();
    popuniKontaktDokumente();
}

FrmKontaktDokumenti1::FrmKontaktDokumenti1(
        unsigned int iKupacId,
        unsigned int iKontaktId,
        unsigned int iKontaktStavkaId,
        int iItemId,
        int iTaskId,
        string strAktivniPrikaz,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmKontaktDokumenti1)
{
    ui->setupUi(this);

    m_iKupacId = iKupacId;
    m_iKonatktId = iKontaktId;
    m_iKontaktStavkaId = iKontaktStavkaId;
    m_iItemId = iItemId;
    m_iTaskId = iTaskId;

    ui->lblLink->setText(QString::fromStdString(strAktivniPrikaz));

    initForm();

    popuniKupca();
    popuniKontaktDokumente();
}

FrmKontaktDokumenti1::~FrmKontaktDokumenti1()
{
    delete ui;
}

// [ Private Member Functions ]
void FrmKontaktDokumenti1::initForm()
{
    ui->treeDokumenti->setColumnWidth(0, 442);
    ui->treeDokumenti->setColumnWidth(1, 5);
    ui->treeDokumenti->setColumnWidth(2, 5);
    ui->treeDokumenti->setColumnWidth(3, 56);
    ui->treeDokumenti->setColumnWidth(4, 56);
    ui->treeDokumenti->hideColumn(1);
    ui->treeDokumenti->hideColumn(2);

    m_iconUser.addFile(QString::fromUtf8(":/InDonat/Forms/images/USER.ico"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);

    m_iconLozinka.addFile(QString::fromUtf8(":/InDonat/Forms/images/userlocked.gif"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);

    m_iconTransparent.addFile(QString::fromUtf8(":/InDonat/Forms/images/transparet_10x10.png"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
}

unsigned int FrmKontaktDokumenti1::GetKontaktKupacId(const unsigned int iKonaktId)
{
    unsigned int iKupacId = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT KUPAC_ID FROM KONTAKT_SP_N WHERE KON_ID = ");
    strSqlStatement.append(cttl::itos(iKonaktId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            iKupacId = rs->getUInt(1);
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

    return iKupacId;
}

unsigned int FrmKontaktDokumenti1::GetKontaktPlanIdSeq()
{
    unsigned int retValue = 0;

    string strSqlStatement;
    strSqlStatement.append("SELECT KONTAKT_PLAN_ID_SEQ.NEXTVAL ID FROM DUAL");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getUInt(1);
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

void FrmKontaktDokumenti1::popuniKupca()
{
    if(m_iKupacId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT STRANKA_ID, FORMATIRANI_NAZIV, FORMATIRANA_ADRESA FROM HIJERARHIJA_STR_ADRESE WHERE ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(m_iKupacId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->lblKupacNaziv->setText(QString::fromStdString(rs->getString(2)));
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

void FrmKontaktDokumenti1::popuniKontaktDokumente()
{
    ui->treeDokumenti->clear();

    if(m_iKonatktId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT ID, FILE_NAZIV, NVL(FILE_OPIS,'-') FILE_OPIS, NVL(LOZINKA,'-') LOZINKA, ");
    strSqlStatement.append("FILE_SIZE, STATUS, NVL(TO_CHAR(DATUM,'DD.MM.YYYY'),'-') DATUM ");
    strSqlStatement.append("FROM KONTAKT_PLAN_FILE WHERE KNTPLAN_ID = ");
    strSqlStatement.append(cttl::itos(m_iKonatktId));
    strSqlStatement.append(" ORDER BY ID ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listDokumenti;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemDokument = new QTreeWidgetItem();

            string strDatum, strLozinka;
            int iStatus;
            strLozinka = rs->getString(4);
            strDatum = rs->getString(7);
            iStatus = rs->getInt(6);

            if(strDatum == "-")
            {
                itemDokument->setText(0, QString::fromStdString(rs->getString(2)));
            }
            else
            {
                itemDokument->setText(0, QString::fromStdString(rs->getString(7)) + tr(" ... ") + QString::fromStdString(rs->getString(2)));
            }
            itemDokument->setText(1, QString::fromStdString(rs->getString(1)));
            itemDokument->setText(2, QString::fromStdString(rs->getString(2)));
//            if(strLozinka != "-")
//            {
//                itemDokument->setIcon(3, m_iconLozinka);
//            }
//            else
//            {
//                itemDokument->setIcon(3, m_iconTransparent);
//            }
//            if(iStatus == 0)
//            {
//                itemDokument->setIcon(4, m_iconUser);
//            }
//            else
//            {
//                itemDokument->setIcon(4, m_iconTransparent);
//            }
            listDokumenti.append(itemDokument);
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

    if(!listDokumenti.empty())
    {
        listDokumenti.first()->setSelected(true);
        ui->treeDokumenti->insertTopLevelItems(0, listDokumenti);
        ui->treeDokumenti->setCurrentItem(listDokumenti.first());
        ui->treeDokumenti->expandAll();
    }

}

void FrmKontaktDokumenti1::popuniKupacDokumente()
{
    ui->treeDokumenti->clear();

    if(m_iKupacId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT ID, FILE_NAZIV, NVL(FILE_OPIS,'-') FILE_OPIS, NVL(LOZINKA,'-') LOZINKA, ");
    strSqlStatement.append("FILE_SIZE, STATUS, NVL(TO_CHAR(DATUM,'DD.MM.YYYY'),'-') DATUM ");
    strSqlStatement.append("FROM KONTAKT_PLAN_FILE WHERE KUPAC_ID = ");
    strSqlStatement.append(cttl::itos(m_iKupacId));
    strSqlStatement.append(" ORDER BY ID ");

    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    QList<QTreeWidgetItem *> listDokumenti;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            QTreeWidgetItem *itemDokument = new QTreeWidgetItem();

            string strDatum, strLozinka;
            int iStatus;
            strLozinka = rs->getString(4);
            strDatum = rs->getString(7);
            iStatus = rs->getInt(6);

            if(strDatum == "-")
            {
                itemDokument->setText(0, QString::fromStdString(rs->getString(2)));
            }
            else
            {
                itemDokument->setText(0, QString::fromStdString(rs->getString(7)) + tr(" ... ") + QString::fromStdString(rs->getString(2)));
            }
            itemDokument->setText(1, QString::fromStdString(rs->getString(1)));
            itemDokument->setText(2, QString::fromStdString(rs->getString(2)));
            if(strLozinka != "-")
            {
                itemDokument->setIcon(3, m_iconLozinka);
            }
            else
            {
                itemDokument->setIcon(3, m_iconTransparent);
            }
            if(iStatus == 0)
            {
                itemDokument->setIcon(4, m_iconUser);
            }
            else
            {
                itemDokument->setIcon(4, m_iconTransparent);
            }
            listDokumenti.append(itemDokument);
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

    if(!listDokumenti.empty())
    {
        listDokumenti.first()->setSelected(true);
        ui->treeDokumenti->insertTopLevelItems(0, listDokumenti);
        ui->treeDokumenti->setCurrentItem(listDokumenti.first());
        ui->treeDokumenti->expandAll();
    }

}

void FrmKontaktDokumenti1::popuniOpisDokumenta()
{
    ui->txtOpisDokumenta->clear();

    if(m_iFileNo == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT KORISNIK_ID, NVL(FILE_OPIS,'-') FILE_OPIS FROM KONTAKT_PLAN_FILE WHERE ID = ");
    strSqlStatement.append(cttl::itos(m_iFileNo));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtOpisDokumenta->setPlainText(QString::fromStdString(rs->getString(2)));
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
void FrmKontaktDokumenti1::on_btnPotvrdaOpisa_clicked()
{
    if(m_iFileNo == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("BEGIN UPDATE KONTAKT_PLAN_FILE SET FILE_OPIS = :P_OPIS WHERE ID = :P_ID; END; ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setString(1, ui->txtOpisDokumenta->toPlainText().toStdString());
        sqlStatement->setUInt(2, m_iFileNo);
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
}

void FrmKontaktDokumenti1::on_btnNoviDokument_clicked()
{
    if(m_iKonatktId == 0)
    {
        return;
    }

    unsigned int iId = GetKontaktPlanIdSeq();

    //1. First insert empty blobs in tables...
    Blob blobFile;
    blobFile.setEmpty(g_DonatConn);

    string strSqlStatement;
    strSqlStatement.append("BEGIN INSERT INTO KONTAKT_PLAN_FILE (ID, KNTPLAN_ID, KUPAC_ID, FILE_NAZIV, FILE_OPIS, FILE_BLOB, ");
    strSqlStatement.append("FILE_SIZE, LOZINKA, KORISNIK_ID, STATUS, DATUM, STAVKA_ID, ITEM_ID, TASK_ID) ");
    strSqlStatement.append("VALUES ( :v0, :v1, :v2, :v3, :v4, :v5, :v6, :v7, :v8, :v9, SYSDATE, :v11, :v12, :v13); ");
    strSqlStatement.append("END; ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        sqlStatement->setUInt(1, iId);
        sqlStatement->setUInt(2, m_iKonatktId);
        sqlStatement->setUInt(3, m_iKupacId);
        sqlStatement->setString(4, m_strFileName);
        sqlStatement->setString(5, m_strFileDescription);
        sqlStatement->setBlob(6, blobFile);
        sqlStatement->setInt(7, m_iFileSize);
        sqlStatement->setNull(8, OCCISTRING);
        sqlStatement->setString(9, g_DonatUser);
        sqlStatement->setInt(10, 1);
        if(m_iKontaktStavkaId == 0)
        {
            sqlStatement->setNull(11, OCCIUNSIGNED_INT);
        }
        else
        {
            sqlStatement->setUInt(11, m_iKontaktStavkaId);
        }
        if(m_iItemId == 0)
        {
            sqlStatement->setNull(12, OCCIINT);
        }
        else
        {
            sqlStatement->setInt(12, m_iItemId);
        }
        if(m_iTaskId == 0)
        {
            sqlStatement->setNull(13, OCCIINT);
        }
        else
        {
            sqlStatement->setInt(13, m_iTaskId);
        }

        sqlStatement->executeUpdate();
    }
    catch(SQLException &ex)
    {
        QMessageBox::critical(this, tr("DONAT - Database Error"),
                                       QString::fromStdString(ex.getMessage()),
                                       QMessageBox::Close);
    }

    //2. Update empty blobs in tables...
    strSqlStatement.clear();
    strSqlStatement.append("SELECT FILE_BLOB FROM KONTAKT_PLAN_FILE WHERE ID = ");
    strSqlStatement.append(cttl::itos(iId));
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            blobFile = rs->getBlob(1);
            // To Do
            //blobFile.write((unsigned int)bytesOut, req_buffer, (unsigned int)bytesOut);

            g_DonatConn->commit();
        }
        else
        {
            g_DonatConn->rollback();
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
    blobFile.close();
    //blobFile.~Blob();
}

void FrmKontaktDokumenti1::on_btnOtvoriDokument_clicked()
{
    if(m_iFileNo == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT FILE_BLOB FROM KONTAKT_PLAN_FILE WHERE ID = ");
    strSqlStatement.append(cttl::itos(m_iFileNo));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            /* Stream BLOB read
            Blob blob=rset->getBlob(1);
            if(blob.isNull())
               cerr <<"Null Blob"<<endl;
            else
            {
               Stream *instream=blob.getStream(1,0);
               //reading from offset 1 to the end of the BLOB

               unsigned int size=blob.getChunkSize();
               char *buffer=new char[size];

               while((unsigned int length=instream->readBuffer(buffer,size))!=-1)
               {
                  //process "length" bytes read into buffer
                  ...
               }
               delete[] buffer;
               blob.closeStream(instream);
            }
            */

            /* BLOB READ  */
            Blob blobFile = rs->getBlob(1);
            if(blobFile.isNull())
            {
                QMessageBox::warning(this, tr("DONAT - Kontakt "),
                                               tr("Datoteka ne psotoji u DONAT sustavu!"),
                                               QMessageBox::Close);
            }
            else
            {
               blobFile.open(OCCI_LOB_READONLY);

               const unsigned int BUFSIZE=blobFile.length();
               char *buffer[BUFSIZE];
               unsigned int readAmt=BUFSIZE;
               unsigned int offset=1;

               //reading readAmt bytes from offset 1
               //blobFile.read(readAmt, buffer, BUFSIZE, offset);

               //process information in buffer
               // Create a new file
               //QFile file(tr("/home/toncis/Desktop/") +  QString::fromStdString(m_strFileName));
               QFile file(QDir::tempPath() + tr("/") + QString::fromStdString(m_strFileName));

               file.open(QIODevice::WriteOnly);
               file.write(reinterpret_cast<const char*>(buffer));
               file.close();
               //QTextStream out(&file);
               //out << buffer;

               // optional, as QFile destructor will already do it:
               //file.close();
            }
            blobFile.close();
        }




//            Blob blobFile = rs->getBlob(1);
//            // To Do
//            //blobFile.write((unsigned int)bytesOut, req_buffer, (unsigned int)bytesOut);

//            unsigned int iOffSet = 1;
//            int iBlobLen = blobFile.length();
//            if(iBlobLen > 0)
//            {
//                Stream *instream = blobFile.getStream(1, 0);
//                char *buffer = new char[iBlobLen];
//                memset(buffer, NULL, iBlobLen);

//                instream->readBuffer (buffer, iBlobLen);
//                cout << "dumping blob: ";
//                for (int i = 0; i < iBlobLen; ++i)
//                  cout << (int) buffer[i];
//                cout << endl;

//                delete (buffer);
//                blobFile.closeStream (instream);

////                unsigned int size=BUFSIZE;
////                unsigned char *buffer= new unsigned char[size];
////                memset (buffer, NULL, size);
//            }

//            blobFile.close();
//        }


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

void FrmKontaktDokumenti1::on_btnUkloniDokument_clicked()
{
    if(m_iFileNo == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("BEGIN DELETE FROM KONTAKT_PLAN_FILE WHERE ID = :P_ID; END; ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);
    sqlStatement->setAutoCommit(TRUE);

    try
    {
        sqlStatement->setUInt(1, m_iFileNo);
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

}

void FrmKontaktDokumenti1::on_btnDokumentZaporka_clicked()
{

}

void FrmKontaktDokumenti1::on_btnKorisnikDokument_clicked()
{

}

void FrmKontaktDokumenti1::on_btnExcell_clicked()
{

}

void FrmKontaktDokumenti1::on_btnWord_clicked()
{

}

void FrmKontaktDokumenti1::on_btnDokumentEmail_clicked()
{

}

void FrmKontaktDokumenti1::on_treeDokumenti_itemPressed(QTreeWidgetItem *item, int UNUSED(column))
{
    m_iFileNo = item->text(1).toUInt();
    m_strFileName = item->text(2).toStdString();
    m_strFileDescription = item->text(2).toStdString();
    popuniOpisDokumenta();
}


}

