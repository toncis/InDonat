//
//  wgdonatmenu3.h
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

#ifndef WGDONATMENU3_H
#define WGDONATMENU3_H

#include <QWidget>
#include <QtWidgets>
#include <QTableWidget>
#include "donat.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
class QComboBox;
class QLineEdit;
class QLabel;
class QFrame;
class QToolBox;
class QWidget;
class QPushButton;
class QGridLayout;
QT_END_NAMESPACE

namespace Log {


class WgDonatMenu3 : public QWidget
{
    Q_OBJECT
public:
    // [ Public Members ]
    QVBoxLayout *m_vboxDonatSearchResults;
    // [0]
    QFrame *m_fraDonatSearchResultTitle;
    // [1]
    QFrame *m_fraDonatSearchResultStranke;
    QComboBox *m_cboDonatSearchResult;
    QTableWidget *m_grdDonatStranke;
    // [0]
    QFrame *m_fraDonatSearchResultLoyalty;
    QLabel *m_txtStrankaLoyaltyId;
    QLabel *m_txtStrankaLoyaltyValidniBodovi;
    QLabel *m_txtStrankaLoyaltyPotencijalniBodovi;
    QPushButton *m_btnLoyalty;
    // [0]
    QFrame *m_fraDonatSearchResultBrzina;
    QPushButton *m_btnStrankaPromjenaAdslStatusa;
    QLabel *m_txtStrankaAdslStatus;
    QPushButton *m_btnStrankaPromijenaIptvStatusa;
    QLabel *m_txtStrankaMaxtvStatus;
    QPushButton *m_btnStrankaMjerenjeBrzine;
    // [0]
    QFrame *m_fraDonatSearchResultZastupnik;
    QPushButton *m_btnStrankaZatupnik1;
    QLabel *m_txtStrankaZastupnik;
    QPushButton *m_btnStrankaZatupnik2;
    // [0]
    QFrame *m_fraDonatSearchResultToolBar;
    QPushButton *m_btnStrankaPregledZahtjeva;
    QPushButton *m_btnStrankaPregledNemogucnosti;
    QPushButton *m_btnStrankaPregledUgovora;
    QPushButton *m_btnStrankaSklapanjeUgovora;
    QPushButton *m_btnStrankaZahtjevStranke;
    QPushButton *m_btnStrankaInterno;
    QPushButton *m_btnStrankaSlanjeObavijesti;
    QPushButton *m_btnStrankaPoslaneObavijesti;

    // [0]
    QFrame *m_fraDonatSearchResultMessages;
    QLabel *m_lblDonatStrankaMessages;

    // [ Constructor ]
    explicit WgDonatMenu3(QWidget *parent = 0);
    ~WgDonatMenu3();

signals:

public slots:

private:
    // [Private Member Functions]
    void createDonatSearchResultsTitle();
    void createDonatSearchResultsStranke();
    void createDonatSearchResultsLoyalty();
    void createDonatSearchResultsBrzina();
    void createDonatSearchResultsZastupnik();
    void createDonatSearchResultsToolBar();
    void createDonatSearchResultsMessages();

};

}   // namespace log

#endif // WGDONATMENU3_H
