//
//  wgdonatmenu2.h
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

#ifndef WGDONATMENU2_H
#define WGDONATMENU2_H

#include <QWidget>
#include <QtWidgets>
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
class QListWidget;
QT_END_NAMESPACE

namespace Log {

class WgDonatMenu2 : public QWidget
{
    Q_OBJECT
public:

    // [ Public Members ]
    QComboBox *m_cboDonatSearch;
    QLineEdit *m_txtDonatSearch;
    QPushButton *m_btnDonatTrazi;
    QPushButton *m_btnDonatKon;
    QPushButton *m_btnDonatFiz;
    QPushButton *m_btnDonatFir;

    QLabel *m_lblOsnoveUlogeTitle;
    QListWidget *m_lstUlogeStranaka;

    // [ Class Constructor ]
    explicit WgDonatMenu2(QWidget *parent = 0);
    ~WgDonatMenu2();

signals:

public slots:

private slots:
    void toUpper(const QString &text);

private:

    // [0]
    QHBoxLayout *m_hboxDonatMenu2;
    // [1]
    QFrame *m_fraDonatSearch;
    QFrame *m_fraDonatSearchFlt;
    QVBoxLayout *m_vboxDonatSearch;
    QVBoxLayout *m_vboxDonatSearchFlt;
    QFrame *m_fraDonatUlogeStranke;
    QVBoxLayout *m_vboxDonatUlogeStranke;

    // [10]
    QFrame *m_fraMainMenuImage;
    QLabel *m_imgMainMenuImage;

    // Create Donat search panel
    void creatDonatSearchPanel();
    // [0]
    void createDonatSearchStrankaTitle();
    // [1]
    void createDonatSearchMjestoTitle();
    // [2]
    void createDonatSearchAdresaTitle();
    // [3]
    void createDonatSearchLine();
    // [4]
    void createDonatSearchToolbar();

    // Create Donat Uloge stranaka panel
    void creatDonatUlogeStranke();
};

}   // namespace log

#endif // WGDONATMENU2_H
