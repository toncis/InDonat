/************************************* Module Header **************************************\
* Module Name:  frmbundleinfo.cpp
* Project:      InDonat - Donat client
* Copyright (c) IN2 d.o.o.
* http://www.in2.hr
*
* This file contains the implementations of DONAT pregled za bundle usluge form
*
* For more information see the Books Online and documentation.
* *****************************************************************************************
* All rights reserved.
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
* OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
* FITNESS FOR A PARTICULAR PURPOSE.
* * *****************************************************************************************
* Release History :
*
* VERSION	DESCRIPTION
* 	1.0		Created by Tonci Svilicic
\******************************************************************************************/

#include "frmbundleinfo.h"
#include "ui_frmbundleinfo.h"

#include "itos.h"
#include "ocinumber.h"

namespace Sporazumi {

// [ Class Constructors]
FrmBundleInfo::FrmBundleInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmBundleInfo)
{
    ui->setupUi(this);
}

FrmBundleInfo::FrmBundleInfo(unsigned int iKupacId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmBundleInfo)
{
    ui->setupUi(this);

    m_iKupacId = iKupacId;

    ui->treeBundle->hideColumn(1);
    ui->treeBundle->hideColumn(2);
    ui->treeBundle->hideColumn(3);
    ui->treeBundle->hideColumn(4);
    ui->treeBundle->hideColumn(5);
    ui->treeBundle->hideColumn(6);
    ui->treeBundle->hideColumn(7);
    ui->treeBundle->hideColumn(8);

    popuniKupca(m_iKupacId);
    popuniBundleZaKupca();

    popuniBundle();
    popuniBundleAnaliza();
    popuniBundleInfo();
    popuniBUndleSporazumi();
}


FrmBundleInfo::~FrmBundleInfo()
{
    delete ui;
}

// [ Private Member Functions ]
string FrmBundleInfo::jeLiBundle(const unsigned int iGrupaImovineId)
{
    string retValue;

    if(iGrupaImovineId == 0)
    {
        return retValue;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT DNT_BUNDLE.JE_LI_BUNDLE (");
    strSqlStatement.append(cttl::itos(iGrupaImovineId));
    strSqlStatement.append(") BUNDLE FROM DUAL ");
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            retValue = rs->getString(1);
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

unsigned int FrmBundleInfo::vratiBundleAsset(const unsigned int iGrupaImovineId)
{
    unsigned int retValue = 0;

    if(iGrupaImovineId == 0)
    {
        return retValue;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT DNT_BUNDLE.VRATI_BUNDLE_ASSET (");
    strSqlStatement.append(cttl::itos(iGrupaImovineId));
    strSqlStatement.append(") BUNDLE_ID FROM DUAL ");
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

unsigned int FrmBundleInfo::vratiBundleAsset(const string strIdentifikator)
{
    unsigned int retValue = 0;

    if(strIdentifikator.length() == 0)
    {
        return retValue;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT DNT_BUNDLE.VRATI_BUNDLE_ASSET ('");
    strSqlStatement.append(strIdentifikator);
    strSqlStatement.append("'') BUNDLE_ID FROM DUAL ");
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



void FrmBundleInfo::popuniKupca(const unsigned int iKupacId)
{
    if(iKupacId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT FORMATIRANI_NAZIV, FORMATIRANA_ADRESA FROM HIJERARHIJA_STR_ADRESE3 WHERE ULSTRANKE_ID = ");
    strSqlStatement.append(cttl::itos(iKupacId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        if(rs->next())
        {
            ui->txtKupacId->setText(QString::number(iKupacId));
            ui->txtKupacNaziv->setText(QString::fromStdString(rs->getString(1)));
            ui->txtKupacAdresa->setText(QString::fromStdString(rs->getString(2)));
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


// [ 1. Version]
void FrmBundleInfo::popuniBundleZaKupca()
{
    if(m_iKupacId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT BUNDLE_ID, BUNDLE_IDENTIFIKATOR, BUNDLE_INSTALACIJA_ID, TEL_KLASA, IDENTIFIKATOR, MEMBER_ID, STATUS_ID, ");
    strSqlStatement.append(" KOMPONENTA_ID, MEMBER_LINIJA, KUPAC FROM V_BUNDLE_STRUCTURE_2 WHERE KUPAC = ");
    strSqlStatement.append(cttl::itos(m_iKupacId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    m_lstBundleView.clear();
    list<NodeTag_BundleView> lstBundleView;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            NodeTag_BundleView bundleViewData;
            bundleViewData.Bundle_Id = rs->getUInt(1);
            bundleViewData.Bundle_Identifikator = rs->getString(2);
            bundleViewData.Bundle_Instalacija_Id = rs->getUInt(3);
            bundleViewData.Tel_Klasa = rs->getString(4);
            bundleViewData.Identifikator = rs->getString(5);
            bundleViewData.Member_Id = rs->getUInt(6);
            bundleViewData.Status_Id = rs->getInt(7);
            bundleViewData.Komponenta_Id = rs->getUInt(8);
            bundleViewData.Memeber_Linija = rs->getUInt(9);
//            if(bundleViewData.Bundle_Instalacija_Id > 0)
//            {
//                lstBundleView.push_back(bundleViewData);
//            }
            lstBundleView.push_back(bundleViewData);

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

    ui->treeBundle->clear();
    if(lstBundleView.empty())
    {
       return;
    }

    QList<QTreeWidgetItem *> listDonatBundleView;

    list<NodeTag_BundleView>::const_iterator itBundleViewItem1;
    for(itBundleViewItem1=lstBundleView.begin(); itBundleViewItem1!=lstBundleView.end(); ++itBundleViewItem1)
    {
        if(listDonatBundleView.isEmpty())
        {
            QTreeWidgetItem *itemBundleViewMember = new QTreeWidgetItem();
            itemBundleViewMember->setText(0, tr("BUNDLE   ") + QString::fromStdString(itBundleViewItem1->Bundle_Identifikator).toUpper());
            itemBundleViewMember->setText(1, QString::number(itBundleViewItem1->Bundle_Id));
            itemBundleViewMember->setText(2, QString::fromStdString(itBundleViewItem1->Identifikator));
            QVariant treeItemTag;
            treeItemTag.setValue(*itBundleViewItem1);
            itemBundleViewMember->setData(0, Qt::UserRole, treeItemTag);
            listDonatBundleView.append(itemBundleViewMember);
        }
        else
        {
            bool bNewBundle = true;
            for(int iTreeItem = 0; iTreeItem < listDonatBundleView.size(); ++iTreeItem)
            {
                if(listDonatBundleView.at(iTreeItem)->text(1).toUInt() == itBundleViewItem1->Bundle_Id)
                {
                    bNewBundle = false;
                }
            }
            if(bNewBundle == true)
            {
                QTreeWidgetItem *itemBundleViewMember = new QTreeWidgetItem();
                itemBundleViewMember->setText(0, tr("BUNDLE   ") + QString::fromStdString(itBundleViewItem1->Bundle_Identifikator).toUpper());
                itemBundleViewMember->setText(1, QString::number(itBundleViewItem1->Bundle_Id));
                itemBundleViewMember->setText(2, QString::fromStdString(itBundleViewItem1->Identifikator));
                QVariant treeItemTag;
                treeItemTag.setValue(*itBundleViewItem1);
                itemBundleViewMember->setData(0, Qt::UserRole, treeItemTag);
                listDonatBundleView.append(itemBundleViewMember);
            }
        }
    }

    for(int iTreeItem = 0; iTreeItem < listDonatBundleView.size(); ++iTreeItem)
    {
        unsigned int iGrupaImovineId;
        iGrupaImovineId = listDonatBundleView.at(iTreeItem)->text(1).toUInt();
        popuniBundleAnaliza(iGrupaImovineId);

        // Add products
        list<NodeTag_BundleAnaliza>::const_iterator itBundleAnalizaItem1;
        for(itBundleAnalizaItem1=m_lstBundleAnaliza.begin(); itBundleAnalizaItem1!=m_lstBundleAnaliza.end(); ++itBundleAnalizaItem1)
        {
            if(itBundleAnalizaItem1->Member_Id == iGrupaImovineId)
            {
                QTreeWidgetItem *itemBundleProductMember1 = new QTreeWidgetItem();
                itemBundleProductMember1->setText(0, QString::fromStdString(itBundleAnalizaItem1->Produkt));
                QVariant treeItem3Tag;
                treeItem3Tag.setValue(*itBundleAnalizaItem1);
                itemBundleProductMember1->setData(1, Qt::UserRole, treeItem3Tag);
//                itemBundleViewMember->setData(0, Qt::UserRole, treeItemTag);
                listDonatBundleView.at(iTreeItem)->addChild(itemBundleProductMember1);
            }
        }

        for(itBundleViewItem1=lstBundleView.begin(); itBundleViewItem1!=lstBundleView.end(); ++itBundleViewItem1)
        {
            if(listDonatBundleView.at(iTreeItem)->text(1).toUInt() == itBundleViewItem1->Bundle_Id)
            {
                QTreeWidgetItem *itemBundleViewMember = new QTreeWidgetItem();
                itemBundleViewMember->setText(0, QString::fromStdString(itBundleViewItem1->Identifikator) + tr("   ") + QString::fromStdString(itBundleViewItem1->Tel_Klasa));
                QVariant treeItemTag;
                treeItemTag.setValue(*itBundleViewItem1);
                itemBundleViewMember->setData(0, Qt::UserRole, treeItemTag);

                // Add products
                list<NodeTag_BundleAnaliza>::const_iterator itBundleAnalizaItem;
                for(itBundleAnalizaItem=m_lstBundleAnaliza.begin(); itBundleAnalizaItem!=m_lstBundleAnaliza.end(); ++itBundleAnalizaItem)
                {
                    if(itBundleAnalizaItem->Member_Id == itBundleViewItem1->Member_Id)
                    {
                        QTreeWidgetItem *itemBundleProductMember = new QTreeWidgetItem();
                        itemBundleProductMember->setText(0, QString::fromStdString(itBundleAnalizaItem->Produkt));
                        QVariant treeItem2Tag;
                        treeItem2Tag.setValue(*itBundleAnalizaItem);
                        itemBundleProductMember->setData(1, Qt::UserRole, treeItem2Tag);
                        itemBundleViewMember->setData(0, Qt::UserRole, treeItemTag);
                        itemBundleViewMember->setData(2, Qt::UserRole, treeItem2Tag);
                        itemBundleViewMember->addChild(itemBundleProductMember);
                    }
                }

                listDonatBundleView.at(iTreeItem)->addChild(itemBundleViewMember);
            }
        }


    }





    if(!listDonatBundleView.empty())
    {
        listDonatBundleView.first()->setSelected(true);
        ui->treeBundle->insertTopLevelItems(0, listDonatBundleView);
//        ui->treeBundle->setCurrentItem(listDonatBundleView.first());
        ui->treeBundle->expandAll();
//      ui->treeBundle->collapseAll();
    }


//    QTreeWidgetItem *itemBundleView = new QTreeWidgetItem();
//    itemBundleView->setText(0, tr("BUNDLE   ") + QString::fromStdString(strBundleIdentifikator).toUpper());
//    itemBundleView->setText(1, QString::number(iBundleId));

//    list<NodeTag_BundleView>::const_iterator itBundleViewItem;
//    for(itBundleViewItem=lstBundleView.begin(); itBundleViewItem!=lstBundleView.end(); ++itBundleViewItem)
//    {
//        QTreeWidgetItem *itemBundleViewMember = new QTreeWidgetItem();
//        itemBundleViewMember->setText(0, QString::fromStdString(itBundleViewItem->Identifikator) + tr("   ") + QString::fromStdString(itBundleViewItem->Tel_Klasa));
//        QVariant treeItemTag;
//        treeItemTag.setValue(*itBundleViewItem);
//        itemBundleViewMember->setData(0, Qt::UserRole, treeItemTag);
//        itemBundleView->addChild(itemBundleViewMember);
//    }

//    itemBundleView->setSelected(true);
//    ui->treeBundle->insertTopLevelItem(0, itemBundleView);
//    ui->treeBundle->setCurrentItem(itemBundleView);
//    ui->treeBundle->expandAll();

}

void FrmBundleInfo::popuniBundleAnaliza(const unsigned int iGrupaImovineId)
{
    if(iGrupaImovineId == 0)
    {
        return;
    }

    string strSqlStatement;
    strSqlStatement.append("SELECT BH_KUPAC, GIMOVINE_ID, BUNDLE_IDENT, MEMBER_IDENT, KLASA, MEMBER_GIM, PRODUKT, IMOVINA_ID, KUPAC_ID,  ");
    strSqlStatement.append("BILLINGACCOUNT_ID, PARTNUMBER, PRODUCT_NAME, TO_CHAR(CREATED, 'DD.MM.YYYY HH24:MI:SS') CREATED, ");
    strSqlStatement.append("TO_CHAR(EFFECTIVE_DTM, 'DD.MM.YYYY HH24:MI:SS') EFFECTIVE_DTM, PRODUCT_STATUS, DON_STAT ");
    strSqlStatement.append("FROM DONAT.V_BUNDLE_ANALIZA WHERE GIMOVINE_ID = ");
    strSqlStatement.append(cttl::itos(iGrupaImovineId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    m_lstBundleAnaliza.clear();
//    list<NodeTag_BundleAnaliza> lstBundleAnaliza;

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            NodeTag_BundleAnaliza bundleAnalizaData;
            bundleAnalizaData.BH_Kupac_Id = rs->getUInt(1);
            bundleAnalizaData.Bundle_Id = rs->getUInt(2);
            bundleAnalizaData.Bundle_Identifikator = rs->getString(3);
            bundleAnalizaData.Tel_Klasa = rs->getString(4);
            bundleAnalizaData.Member_Identifikator = rs->getString(5);
            bundleAnalizaData.Member_Id = rs->getUInt(6);
            bundleAnalizaData.Produkt = rs->getString(7);
            bundleAnalizaData.Imovina_Id = rs->getString(8);
            bundleAnalizaData.Kupac_Id = rs->getString(9);
            bundleAnalizaData.BillingAccount_Id = rs->getString(10);
            bundleAnalizaData.PartNumber = rs->getString(11);
            bundleAnalizaData.ProductName = rs->getString(12);
            bundleAnalizaData.Created = rs->getString(13);
            bundleAnalizaData.EffectiveDTM = rs->getString(14);
            bundleAnalizaData.ProductStatus = rs->getString(15);
            bundleAnalizaData.DonatStatus = rs->getInt(16);
            m_lstBundleAnaliza.push_back(bundleAnalizaData);
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

// [2. Version]

void FrmBundleInfo::popuniBundle()
{
    if(m_iKupacId == 0)
    {
        return;
    }

    m_Bundle = Bundle();
    m_lstBundle.clear();
    m_Bundle.Kupac_Id = m_iKupacId;
    m_lstBundleView.clear();

    string strSqlStatement;
    strSqlStatement.append("SELECT BUNDLE_ID, BUNDLE_IDENTIFIKATOR, BUNDLE_INSTALACIJA_ID, TEL_KLASA, IDENTIFIKATOR, MEMBER_ID, STATUS_ID, ");
    strSqlStatement.append(" KOMPONENTA_ID, MEMBER_LINIJA, KUPAC FROM V_BUNDLE_STRUCTURE_2 WHERE KUPAC = ");
    strSqlStatement.append(cttl::itos(m_iKupacId));
    Statement *sqlStatement = g_DonatConn->createStatement();
    sqlStatement->setSQL(strSqlStatement);

    try
    {
        ResultSet *rs = sqlStatement->executeQuery();
        while(rs->next())
        {
            NodeTag_BundleView bundleViewData;
            bundleViewData.Bundle_Id = rs->getUInt(1);
            bundleViewData.Bundle_Identifikator = rs->getString(2);
            bundleViewData.Bundle_Instalacija_Id = rs->getUInt(3);
            bundleViewData.Tel_Klasa = rs->getString(4);
            bundleViewData.Identifikator = rs->getString(5);
            bundleViewData.Member_Id = rs->getUInt(6);
            bundleViewData.Status_Id = rs->getInt(7);
            bundleViewData.Komponenta_Id = rs->getUInt(8);
            bundleViewData.Memeber_Linija = rs->getUInt(9);
//            if(bundleViewData.Bundle_Instalacija_Id > 0)
//            {
//                lstBundleView.push_back(bundleViewData);
//            }
            m_lstBundleView.push_back(bundleViewData);

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

    list<NodeTag_BundleView>::const_iterator itBundleViewItem;
    for(itBundleViewItem=m_lstBundleView.begin(); itBundleViewItem!=m_lstBundleView.end(); ++itBundleViewItem)
    {
        if(m_lstBundle.isEmpty())
        {
            Bundle newBundle = Bundle();
            newBundle.Kupac_Id = m_iKupacId;
            newBundle.Bundle_Id = itBundleViewItem->Bundle_Id;
            newBundle.Identifikator = itBundleViewItem->Bundle_Identifikator;
            newBundle.Imovina_Id = itBundleViewItem->Bundle_Instalacija_Id;
            m_lstBundle.append(newBundle);
        }
        else
        {
            bool bNewBundleToAdd = true;
            for (int i = 0; i < m_lstBundle.size(); ++i)
            {
                if(m_lstBundle.at(i).Bundle_Id == itBundleViewItem->Bundle_Id)
                {
                    bNewBundleToAdd = false;
                }
            }

            if(bNewBundleToAdd == true)
            {
                Bundle newBundle = Bundle();
                newBundle.Kupac_Id = m_iKupacId;
                newBundle.Bundle_Id = itBundleViewItem->Bundle_Id;
                newBundle.Identifikator = itBundleViewItem->Bundle_Identifikator;
                newBundle.Imovina_Id = itBundleViewItem->Bundle_Instalacija_Id;
                m_lstBundle.append(newBundle);
            }
        }
    }

    list<NodeTag_BundleView>::const_iterator itBundleViewItem1;
    for(itBundleViewItem1=m_lstBundleView.begin(); itBundleViewItem1!=m_lstBundleView.end(); ++itBundleViewItem1)
    {
        for (int i = 0; i < m_lstBundle.size(); ++i)
        {
            Bundle bundle = m_lstBundle.at(i);
            if(bundle.Bundle_Id == itBundleViewItem1->Bundle_Id)
            {
                BundleMember newBundleMember = BundleMember();
                newBundleMember.Bundle_Id = itBundleViewItem1->Bundle_Id;
                newBundleMember.Bundle_Identifikator = itBundleViewItem1->Bundle_Identifikator;
                newBundleMember.Bundle_Instalacija_Id = itBundleViewItem1->Bundle_Instalacija_Id;
                newBundleMember.Tel_Klasa = itBundleViewItem1->Tel_Klasa;
                newBundleMember.Identifikator = itBundleViewItem1->Identifikator;
                newBundleMember.Member_Id = itBundleViewItem1->Member_Id;
                newBundleMember.Status_Id = itBundleViewItem1->Status_Id;
                newBundleMember.Komponenta_Id = itBundleViewItem1->Komponenta_Id;
                newBundleMember.Member_Linija_Id = itBundleViewItem1->Memeber_Linija;
                bundle.Members.push_back(newBundleMember);
            }
        }

    }

//    list<NodeTag_BundleView>::const_iterator itBundleViewItem2;
//    for(itBundleViewItem2=m_lstBundleView.begin(); itBundleViewItem2!=m_lstBundleView.end(); ++itBundleViewItem2)
//    {
//        for (int i = 0; i < m_lstBundle.size(); ++i)
//        {
//            Bundle bundle = m_lstBundle.at(i);

//        }

//    }

}

void FrmBundleInfo::popuniBundleAnaliza()
{
    for (int i = 0; i < m_lstBundle.size(); ++i)
    {
        Bundle bundle = m_lstBundle.at(i);

        m_lstBundleAnaliza.clear();

        string strSqlStatement;
        strSqlStatement.append("SELECT BH_KUPAC, GIMOVINE_ID, BUNDLE_IDENT, MEMBER_IDENT, KLASA, MEMBER_GIM, PRODUKT, IMOVINA_ID, KUPAC_ID,  ");
        strSqlStatement.append("BILLINGACCOUNT_ID, PARTNUMBER, PRODUCT_NAME, TO_CHAR(CREATED, 'DD.MM.YYYY HH24:MI:SS') CREATED, ");
        strSqlStatement.append("TO_CHAR(EFFECTIVE_DTM, 'DD.MM.YYYY HH24:MI:SS') EFFECTIVE_DTM, PRODUCT_STATUS, DON_STAT ");
        strSqlStatement.append("FROM DONAT.V_BUNDLE_ANALIZA WHERE GIMOVINE_ID = ");
        strSqlStatement.append(cttl::itos(bundle.Bundle_Id));
        Statement *sqlStatement = g_DonatConn->createStatement();
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                NodeTag_BundleAnaliza bundleAnalizaData;
                bundleAnalizaData.BH_Kupac_Id = rs->getUInt(1);
                bundleAnalizaData.Bundle_Id = rs->getUInt(2);
                bundleAnalizaData.Bundle_Identifikator = rs->getString(3);
                bundleAnalizaData.Member_Identifikator = rs->getString(4);
                bundleAnalizaData.Tel_Klasa = rs->getString(5);
                bundleAnalizaData.Member_Id = rs->getUInt(6);
                bundleAnalizaData.Produkt = rs->getString(7);
                bundleAnalizaData.Imovina_Id = rs->getString(8);
                bundleAnalizaData.Kupac_Id = rs->getString(9);
                bundleAnalizaData.BillingAccount_Id = rs->getString(10);
                bundleAnalizaData.PartNumber = rs->getString(11);
                bundleAnalizaData.ProductName = rs->getString(12);
                bundleAnalizaData.Created = rs->getString(13);
                bundleAnalizaData.EffectiveDTM = rs->getString(14);
                bundleAnalizaData.ProductStatus = rs->getString(15);
                bundleAnalizaData.DonatStatus = rs->getInt(16);
                m_lstBundleAnaliza.push_back(bundleAnalizaData);
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

        // Add products
        list<NodeTag_BundleAnaliza>::const_iterator itBundleAnalizaItem1;
        for(itBundleAnalizaItem1=m_lstBundleAnaliza.begin(); itBundleAnalizaItem1!=m_lstBundleAnaliza.end(); ++itBundleAnalizaItem1)
        {
            if(itBundleAnalizaItem1->Member_Id == bundle.Bundle_Id)
            {
                BundleAnaliza newBundleAnaliza = BundleAnaliza();
                newBundleAnaliza.BH_Kupac_Id = itBundleAnalizaItem1->BH_Kupac_Id;
                newBundleAnaliza.Bundle_Id = itBundleAnalizaItem1->Bundle_Id;
                newBundleAnaliza.Bundle_Identifikator = itBundleAnalizaItem1->Bundle_Identifikator;
                newBundleAnaliza.Tel_Klasa = itBundleAnalizaItem1->Tel_Klasa;
                newBundleAnaliza.Member_Identifikator = itBundleAnalizaItem1->Member_Identifikator;
                newBundleAnaliza.Member_Id = itBundleAnalizaItem1->Member_Id;
                newBundleAnaliza.Produkt = itBundleAnalizaItem1->Produkt;
                newBundleAnaliza.Imovina_Id = itBundleAnalizaItem1->Imovina_Id;
                newBundleAnaliza.Kupac_Id = itBundleAnalizaItem1->Kupac_Id;
                newBundleAnaliza.BillingAccount_Id = itBundleAnalizaItem1->BillingAccount_Id;
                newBundleAnaliza.PartNumber = itBundleAnalizaItem1->PartNumber;
                newBundleAnaliza.ProductName = itBundleAnalizaItem1->ProductName;
                newBundleAnaliza.Created = itBundleAnalizaItem1->Created;
                newBundleAnaliza.EffectiveDTM = itBundleAnalizaItem1->EffectiveDTM;
                newBundleAnaliza.ProductStatus = itBundleAnalizaItem1->ProductStatus;
                newBundleAnaliza.DonatStatus = itBundleAnalizaItem1->DonatStatus;
                bundle.Analiza.push_back(newBundleAnaliza);
            }
        }

        // Add member analiza
        list<BundleMember>::iterator itBundleMemberItem;
        for(itBundleMemberItem=bundle.Members.begin(); itBundleMemberItem!=bundle.Members.end(); ++itBundleMemberItem)
        {
            list<NodeTag_BundleAnaliza>::const_iterator itBundleAnalizaItem2;
            for(itBundleAnalizaItem2=m_lstBundleAnaliza.begin(); itBundleAnalizaItem2!=m_lstBundleAnaliza.end(); ++itBundleAnalizaItem2)
            {
                if(itBundleAnalizaItem2->Member_Id == itBundleMemberItem->Member_Id)
                {
                    BundleAnaliza newBundleAnaliza = BundleAnaliza();
                    newBundleAnaliza.BH_Kupac_Id = itBundleAnalizaItem2->BH_Kupac_Id;
                    newBundleAnaliza.Bundle_Id = itBundleAnalizaItem2->Bundle_Id;
                    newBundleAnaliza.Bundle_Identifikator = itBundleAnalizaItem2->Bundle_Identifikator;
                    newBundleAnaliza.Tel_Klasa = itBundleAnalizaItem2->Tel_Klasa;
                    newBundleAnaliza.Member_Identifikator = itBundleAnalizaItem2->Member_Identifikator;
                    newBundleAnaliza.Member_Id = itBundleAnalizaItem2->Member_Id;
                    newBundleAnaliza.Produkt = itBundleAnalizaItem2->Produkt;
                    newBundleAnaliza.Imovina_Id = itBundleAnalizaItem2->Imovina_Id;
                    newBundleAnaliza.Kupac_Id = itBundleAnalizaItem2->Kupac_Id;
                    newBundleAnaliza.BillingAccount_Id = itBundleAnalizaItem2->BillingAccount_Id;
                    newBundleAnaliza.PartNumber = itBundleAnalizaItem2->PartNumber;
                    newBundleAnaliza.ProductName = itBundleAnalizaItem2->ProductName;
                    newBundleAnaliza.Created = itBundleAnalizaItem2->Created;
                    newBundleAnaliza.EffectiveDTM = itBundleAnalizaItem2->EffectiveDTM;
                    newBundleAnaliza.ProductStatus = itBundleAnalizaItem2->ProductStatus;
                    newBundleAnaliza.DonatStatus = itBundleAnalizaItem2->DonatStatus;
                    itBundleMemberItem->Analiza.push_back(newBundleAnaliza);
                }
            }

        }
    }
}

void FrmBundleInfo::popuniBundleInfo()
{
    for (int i = 0; i < m_lstBundle.size(); ++i)
    {
        Bundle bundle = m_lstBundle.at(i);

        m_lstBundleInfo.clear();

        string strSqlStatement;
        strSqlStatement.append("SELECT BUN_ID, BUN_GIM, BUN_STAT, BUN_PRET_ID, BUN_PRET, BUN_PRET_STAT, KONV_CEKANJE, ");
        strSqlStatement.append("BILL_BUN_GR_S, MEMB_ID, KOMPONENTA, MEMBER_LINIJA, IDENT_MEMB, MEMB_PRET_ID, MEMB_PRET, ");
        strSqlStatement.append("MEMB_PRET_STAT, REFERENCA, VOIP, AKT_GIM, AKT_IMOV, VOIP_MIG, OPTIKA_MIG, ISP_DIST, LI, ");
        strSqlStatement.append("GR_WWMS, STORNO_REQ, PRVO_SP, GR_EXP, REZ_ZAHT, BILL_MEMB_GR_S ");
        strSqlStatement.append("FROM TABLE(BUNDLE_HELP.VRATI_BUNDLE_INFO(");
        strSqlStatement.append(cttl::itos(bundle.Bundle_Id));
        strSqlStatement.append(")) ");
        Statement *sqlStatement = g_DonatConn->createStatement();
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                NodeTag_BundleInfo bundleInfoData;
                bundleInfoData.Bundle_Id = rs->getString(1);
                bundleInfoData.Bundle_GrupaImovine_id = rs->getUInt(2);
                bundleInfoData.Bundle_Stat = rs->getInt(3);
                bundleInfoData.Bundle_Pretplata_Id = rs->getUInt(4);
                bundleInfoData.Bundle_Pretplata = rs->getString(5);
                bundleInfoData.Bundle_Pretplata_Stat = rs->getInt(6);
                bundleInfoData.Konverzija_Cekanje = rs->getString(7);
                bundleInfoData.Billing_Bundle_GR_S = rs->getUInt(8);
                bundleInfoData.Memeber_Id = rs->getUInt(9);
                bundleInfoData.Komponenta = rs->getString(10);
                bundleInfoData.Member_Linija = rs->getInt(11);
                bundleInfoData.Memeber_Identifikator = rs->getString(12);
                bundleInfoData.Memeber_Pretplata_Id = rs->getUInt(13);
                bundleInfoData.Memeber_Ppretplata = rs->getString(14);
                bundleInfoData.Memeber_Pretplata_Stat = rs->getInt(15);
                bundleInfoData.Referenca = rs->getString(16);
                bundleInfoData.VOIP = rs->getString(17);
                bundleInfoData.AKT_GIM = rs->getString(18);
                bundleInfoData.AKT_IMOV = rs->getString(19);
                bundleInfoData.VOIP_MIG = rs->getString(20);
                bundleInfoData.OPTIKA_MIG = rs->getString(21);
                bundleInfoData.ISP_DIST = rs->getString(22);
                bundleInfoData.LI = rs->getString(23);
                bundleInfoData.GR_WWMS = rs->getString(24);
                bundleInfoData.STORNO_REQ = rs->getString(25);
                bundleInfoData.PRVO_SP = rs->getString(26);
                bundleInfoData.GR_EXP = rs->getString(27);
                bundleInfoData.REZ_ZAHT = rs->getString(28);
                bundleInfoData.Billing_Memeber_GR_S = rs->getUInt(29);
                m_lstBundleInfo.push_back(bundleInfoData);
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

        // Add member info
        list<BundleMember>::iterator itBundleMemberItem;
        for(itBundleMemberItem=bundle.Members.begin(); itBundleMemberItem!=bundle.Members.end(); ++itBundleMemberItem)
        {
            list<NodeTag_BundleInfo>::const_iterator itBundleInfoItem;
            for(itBundleInfoItem=m_lstBundleInfo.begin(); itBundleInfoItem!=m_lstBundleInfo.end(); ++itBundleInfoItem)
            {
                if(itBundleMemberItem->Member_Id == itBundleInfoItem->Memeber_Id)
                {
                    BundleInfo newBundleInfo = BundleInfo();
                    newBundleInfo.Bundle_Id = itBundleInfoItem->Bundle_Id;
                    newBundleInfo.Bundle_GrupaImovine_id = itBundleInfoItem->Bundle_GrupaImovine_id;
                    newBundleInfo.Bundle_Stat = itBundleInfoItem->Bundle_Stat;
                    newBundleInfo.Bundle_Pretplata_Id = itBundleInfoItem->Bundle_Pretplata_Id;
                    newBundleInfo.Bundle_Pretplata = itBundleInfoItem->Bundle_Pretplata;
                    newBundleInfo.Bundle_Pretplata_Stat = itBundleInfoItem->Bundle_Pretplata_Stat;
                    newBundleInfo.Konverzija_Cekanje = itBundleInfoItem->Konverzija_Cekanje;
                    newBundleInfo.Billing_Bundle_GR_S = itBundleInfoItem->Billing_Bundle_GR_S;
                    newBundleInfo.Memeber_Id = itBundleInfoItem->Memeber_Id;
                    newBundleInfo.Komponenta = itBundleInfoItem->Komponenta;
                    newBundleInfo.Member_Linija = itBundleInfoItem->Member_Linija;
                    newBundleInfo.Memeber_Identifikator = itBundleInfoItem->Memeber_Identifikator;
                    newBundleInfo.Memeber_Pretplata_Id = itBundleInfoItem->Memeber_Pretplata_Id;
                    newBundleInfo.Memeber_Ppretplata = itBundleInfoItem->Memeber_Ppretplata;
                    newBundleInfo.Memeber_Pretplata_Stat = itBundleInfoItem->Memeber_Pretplata_Stat;
                    newBundleInfo.Referenca = itBundleInfoItem->Referenca;
                    newBundleInfo.VOIP = itBundleInfoItem->VOIP;
                    newBundleInfo.AKT_GIM = itBundleInfoItem->AKT_GIM;
                    newBundleInfo.AKT_IMOV = itBundleInfoItem->AKT_IMOV;
                    newBundleInfo.VOIP_MIG = itBundleInfoItem->VOIP_MIG;
                    newBundleInfo.OPTIKA_MIG = itBundleInfoItem->OPTIKA_MIG;
                    newBundleInfo.ISP_DIST = itBundleInfoItem->ISP_DIST;
                    newBundleInfo.LI = itBundleInfoItem->LI;
                    newBundleInfo.GR_WWMS = itBundleInfoItem->GR_WWMS;
                    newBundleInfo.STORNO_REQ = itBundleInfoItem->STORNO_REQ;
                    newBundleInfo.PRVO_SP = itBundleInfoItem->PRVO_SP;
                    newBundleInfo.GR_EXP = itBundleInfoItem->GR_EXP;
                    newBundleInfo.REZ_ZAHT = itBundleInfoItem->REZ_ZAHT;
                    newBundleInfo.Billing_Memeber_GR_S = itBundleInfoItem->Billing_Memeber_GR_S;
                    itBundleMemberItem->Info = newBundleInfo;
                }
            }
        }
    }
}

void FrmBundleInfo::popuniBUndleSporazumi()
{
    for (int i = 0; i < m_lstBundle.size(); ++i)
    {
        Bundle bundle = m_lstBundle.at(i);

        m_lstBundleSporazumi.clear();

        string strSqlStatement;
        strSqlStatement.append("SELECT AKCIJA, BUNDLE_SPOR, BUNDLE_ID, IMA_BUNDLE_AKT, BUNDLE_PROV_PROC_ID, BUNDLE_PROV_STANJE_ID, ");
        strSqlStatement.append("BUNDLE_BILL_PROC_ID, BUNDLE_BILL_STANJE_ID, MEMBER_SPOR, MEMBER_ID, IMA_MEMBER_AKT, MEMBER_PROV_PROC_ID,");
        strSqlStatement.append("MEMBER_PROV_STANJE_ID, MEMBER_BILL_PROC_ID, MEMBER_BILL_STANJE_ID ");
        strSqlStatement.append("FROM V_BUNDLE_SPORAZUMI_ALL WHERE BUNDLE_ID = '");
        strSqlStatement.append(cttl::itos(bundle.Bundle_Id));
        strSqlStatement.append("'");
        Statement *sqlStatement = g_DonatConn->createStatement();
        sqlStatement->setSQL(strSqlStatement);

        try
        {
            ResultSet *rs = sqlStatement->executeQuery();
            while(rs->next())
            {
                BundleSporazum bundleSporazumData;
                bundleSporazumData.Akcija = rs->getString(1);
                bundleSporazumData.Bundle_Spor = rs->getUInt(2);
                bundleSporazumData.Bundle_Id = rs->getString(3);
                bundleSporazumData.Ima_Bundle_Akt = rs->getUInt(4);
                bundleSporazumData.Bundle_Prov_Proc_Id = rs->getUInt(5);
                bundleSporazumData.Bundle_Prov_Stanje_Id = rs->getUInt(6);
                bundleSporazumData.BUNDLE_BILL_PROC_ID = rs->getUInt(7);
                bundleSporazumData.BUNDLE_BILL_STANJE_ID = rs->getUInt(8);
                bundleSporazumData.MEMBER_SPOR = rs->getUInt(9);
                bundleSporazumData.MEMBER_ID = rs->getUInt(10);
                bundleSporazumData.IMA_MEMBER_AKT = rs->getUInt(11);
                bundleSporazumData.MEMBER_PROV_PROC_ID = rs->getUInt(12);
                bundleSporazumData.MEMBER_PROV_STANJE_ID = rs->getUInt(13);
                bundleSporazumData.MEMBER_BILL_PROC_ID = rs->getUInt(14);
                bundleSporazumData.MEMBER_BILL_STANJE_ID = rs->getUInt(15);
                m_lstBundleSporazumi.push_back(bundleSporazumData);
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

        // Add member sporazum
        list<BundleMember>::iterator itBundleMemberItem;
        for(itBundleMemberItem=bundle.Members.begin(); itBundleMemberItem!=bundle.Members.end(); ++itBundleMemberItem)
        {
            list<BundleSporazum>::const_iterator itBundleSporazumItem;
            for(itBundleSporazumItem=m_lstBundleSporazumi.begin(); itBundleSporazumItem!=m_lstBundleSporazumi.end(); ++itBundleSporazumItem)
            {
                if(itBundleMemberItem->Member_Id == itBundleSporazumItem->MEMBER_ID)
                {
                    BundleSporazum newSporazum = BundleSporazum();
                    newSporazum.Akcija = itBundleSporazumItem->Akcija;
                    newSporazum.Bundle_Spor = itBundleSporazumItem->Bundle_Spor;
                    newSporazum.Bundle_Id = itBundleSporazumItem->Bundle_Id;
                    newSporazum.Ima_Bundle_Akt = itBundleSporazumItem->Ima_Bundle_Akt;
                    newSporazum.Bundle_Prov_Proc_Id = itBundleSporazumItem->Bundle_Prov_Proc_Id;
                    newSporazum.Bundle_Prov_Stanje_Id = itBundleSporazumItem->Bundle_Prov_Stanje_Id;
                    newSporazum.BUNDLE_BILL_PROC_ID = itBundleSporazumItem->BUNDLE_BILL_PROC_ID;
                    newSporazum.BUNDLE_BILL_STANJE_ID = itBundleSporazumItem->BUNDLE_BILL_STANJE_ID;
                    newSporazum.MEMBER_SPOR = itBundleSporazumItem->MEMBER_SPOR;
                    newSporazum.MEMBER_ID = itBundleSporazumItem->MEMBER_ID;
                    newSporazum.IMA_MEMBER_AKT = itBundleSporazumItem->IMA_MEMBER_AKT;
                    newSporazum.MEMBER_PROV_PROC_ID = itBundleSporazumItem->MEMBER_PROV_PROC_ID;
                    newSporazum.MEMBER_PROV_STANJE_ID = itBundleSporazumItem->MEMBER_PROV_STANJE_ID;
                    newSporazum.MEMBER_BILL_PROC_ID = itBundleSporazumItem->MEMBER_BILL_PROC_ID;
                    newSporazum.MEMBER_BILL_STANJE_ID = itBundleSporazumItem->MEMBER_BILL_STANJE_ID;
                    itBundleMemberItem->Sporazum = newSporazum;
                }
            }
        }
    }
}

// [ Event Handlers ]


}   // namespace sporazumi
