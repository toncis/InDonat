#-------------------------------------------------
#
# Project created by QtCreator 2011-07-06T11:23:54
#
#-------------------------------------------------

QT       += core widgets gui network webkitwidgets

TARGET = DONAT
TEMPLATE = app

# The application version
VERSION = 5.5.5005.4125

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=$$VERSION
DEFINES += APP_NAME=$$TARGET


SOURCES += main.cpp\
        mainwindow.cpp \
    forms/log/frmdonatlogin.cpp \
    donat.cpp \
    global.cpp \
    forms/log/frmdonatabout.cpp \
    forms/log/frmdonatuserrole.cpp \
    forms/log/frmdonatpasswordchange.cpp \
    forms/log/frmdonatuserlogin.cpp \
    forms/log/wgdonatmenu4.cpp \
    forms/log/wgdonatmenu1.cpp \
    forms/log/wgdonatmenu2.cpp \
    forms/log/wgdonatmenu3.cpp \
    forms/log/frmdonatmenu2.cpp \
    forms/sporazumi/frmpregledzahtjeva.cpp \
    forms/sporazumi/frmstavkesporazuma.cpp \
    forms/sporazumi/frmpregledprocesa.cpp \
    forms/sporazumi/frmwwmspregled.cpp \
    forms/sporazumi/frmdonatpregled.cpp \
    forms/stranka/frmstrankaocv.cpp \
    forms/sporazumi/frmpregledsporazuma.cpp \
    forms/sporazumi/frmpregledimovine.cpp \
    forms/kontakt/frmcpeoprema.cpp \
    forms/kontakt/frmugovorneobveze.cpp \
    forms/kontakt/frmtipstranke.cpp \
    forms/stranka/frmstrankafiz.cpp \
    forms/stranka/frmstrankaprav.cpp \
    forms/kontakt/frmdonatzahtjevall.cpp \
    forms/kontakt/zahtjev/nodetag22.cpp \
    forms/kontakt/cpe/nodetag_cpe_2.cpp \
    forms/stranka/frmstrankaadresa.cpp \
    forms/log/frmdonatmenu_old.cpp \
    forms/log/frmdonatmenu.cpp \
    forms/sporazumi/frmobavijestislanje.cpp \
    forms/sporazumi/frmobavijestiposlane.cpp \
    forms/sporazumi/frmzahtjevipregled.cpp \
    forms/sporazumi/frmzahtjevinemoguci.cpp \
    forms/sporazumi/frmugovoripregled.cpp \
    forms/sporazumi/frmugovoriugovaranje.cpp \
    forms/kontakt/frmkontaktnicentar.cpp \
    forms/stranka/frmstrankazurnal.cpp \
    forms/sporazumi/frmgrupaimovineatributi.cpp \
    forms/stranka/frmstrankagrupeimovine.cpp \
    forms/kontakt/frmkontaktnicentaruser.cpp \
    forms/kontakt/frmkontaktnicentarpretraga.cpp \
    forms/kontakt/frmkanalprodaje.cpp \
    forms/sporazumi/frmbundleinfo.cpp \
    forms/sporazumi/Bundle/nodetag_bundle.cpp \
    forms/sporazumi/Bundle/bundle.cpp \
    forms/kontakt/prigovor/frmprigovoradd.cpp \
    forms/kontakt/prigovor/frmprigovorpregled.cpp \
    forms/kontakt/prigovor/frmprigovorodabirstatusa.cpp \
    forms/kontakt/prigovor/frmprigovorstatus.cpp \
    forms/kontakt/prigovor/frmprigovorjop.cpp \
    forms/kontakt/prigovor/frmprigovorosporavaniiznos.cpp \
    forms/kontakt/prigovor/frmprigovoredit.cpp \
    forms/kontakt/prigovor/frmprigovorpisanorjesenje.cpp \
    forms/kontakt/frmkontaktdokumenti.cpp \
    forms/kontakt/prigovor/frmprigovorodobrenje.cpp \
    forms/kontakt/prigovor/frmprigovorpismopotvrde.cpp \
    forms/kontakt/frmkontaktdokumenti1.cpp \
    forms/kontakt/kontakt/nodetag_kontakt.cpp \
    forms/kontakt/frmkanalprodajekorisnik.cpp \
    forms/sporazumi/frmsuspenzija.cpp \
    forms/kontakt/zlonamjerni/frmzlonamjerniadd.cpp \
    forms/kontakt/zlonamjerni/frmzlonamjernipregled.cpp \
    forms/kontakt/zlonamjerni/frmzlonamjernimobadd.cpp \
    forms/stranka/frmmdm1.cpp \
    forms/stranka/frmmdm2.cpp \
    forms/stranka/frmmdm3.cpp

HEADERS  += mainwindow.h \
    forms/log/frmdonatlogin.h \
    donat.h \
    global.h \
    forms/log/frmdonatabout.h \
    forms/log/frmdonatuserrole.h \
    forms/log/frmdonatpasswordchange.h \
    forms/log/frmdonatuserlogin.h \
    forms/log/wgdonatmenu4.h \
    forms/log/wgdonatmenu1.h \
    forms/log/wgdonatmenu2.h \
    forms/log/wgdonatmenu3.h \
    forms/log/frmdonatmenu2.h \
    itos.h \
    ocinumber.h \
    forms/sporazumi/frmpregledzahtjeva.h \
    forms/sporazumi/frmstavkesporazuma.h \
    forms/sporazumi/frmpregledprocesa.h \
    forms/sporazumi/frmwwmspregled.h \
    forms/sporazumi/frmdonatpregled.h \
    forms/stranka/frmstrankaocv.h \
    forms/sporazumi/frmpregledsporazuma.h \
    forms/sporazumi/frmpregledimovine.h \
    forms/kontakt/frmcpeoprema.h \
    forms/kontakt/frmugovorneobveze.h \
    forms/kontakt/frmtipstranke.h \
    forms/stranka/frmstrankafiz.h \
    forms/stranka/frmstrankaprav.h \
    forms/kontakt/frmdonatzahtjevall.h \
    forms/kontakt/zahtjev/nodetag22.h \
    forms/kontakt/cpe/nodetag_cpe_2.h \
    forms/stranka/frmstrankaadresa.h \
    forms/log/frmdonatmenu_old.h \
    forms/log/frmdonatmenu.h \
    forms/sporazumi/frmobavijestislanje.h \
    forms/sporazumi/frmobavijestiposlane.h \
    forms/sporazumi/frmzahtjevipregled.h \
    forms/sporazumi/frmzahtjevinemoguci.h \
    forms/sporazumi/frmugovoripregled.h \
    forms/sporazumi/frmugovoriugovaranje.h \
    forms/kontakt/frmkontaktnicentar.h \
    forms/stranka/frmstrankazurnal.h \
    forms/sporazumi/frmgrupaimovineatributi.h \
    forms/stranka/frmstrankagrupeimovine.h \
    forms/kontakt/frmkontaktnicentaruser.h \
    forms/kontakt/frmkontaktnicentarpretraga.h \
    forms/kontakt/frmkanalprodaje.h \
    forms/sporazumi/frmbundleinfo.h \
    forms/sporazumi/Bundle/nodetag_bundle.h \
    forms/sporazumi/Bundle/bundle.h \
    forms/kontakt/prigovor/frmprigovoradd.h \
    forms/kontakt/prigovor/frmprigovorpregled.h \
    forms/kontakt/prigovor/frmprigovorodabirstatusa.h \
    forms/kontakt/prigovor/frmprigovorstatus.h \
    forms/kontakt/prigovor/frmprigovorjop.h \
    forms/kontakt/prigovor/frmprigovorosporavaniiznos.h \
    forms/kontakt/prigovor/frmprigovoredit.h \
    forms/kontakt/prigovor/frmprigovorpisanorjesenje.h \
    forms/kontakt/frmkontaktdokumenti.h \
    forms/kontakt/prigovor/frmprigovorodobrenje.h \
    forms/kontakt/prigovor/frmprigovorpismopotvrde.h \
    forms/kontakt/frmkontaktdokumenti1.h \
    forms/kontakt/kontakt/nodetag_kontakt.h \
    forms/kontakt/frmkanalprodajekorisnik.h \
    forms/sporazumi/frmsuspenzija.h \
    forms/kontakt/zlonamjerni/frmzlonamjerniadd.h \
    forms/kontakt/zlonamjerni/frmzlonamjernipregled.h \
    forms/kontakt/zlonamjerni/frmzlonamjernimobadd.h \
    forms/stranka/frmmdm1.h \
    forms/stranka/frmmdm2.h \
    forms/stranka/frmmdm3.h

FORMS    += mainwindow.ui \
    forms/log/frmdonatlogin.ui \
    forms/sporazumi/frmpregledzahtjeva.ui \
    forms/sporazumi/frmstavkesporazuma.ui \
    forms/sporazumi/frmpregledsporazuma.ui \
    forms/sporazumi/frmpregledimovine.ui \
    forms/kontakt/frmcpeoprema.ui \
    forms/kontakt/frmugovorneobveze.ui \
    forms/kontakt/frmtipstranke.ui \
    forms/stranka/frmstrankafiz.ui \
    forms/stranka/frmstrankaprav.ui \
    forms/kontakt/frmdonatzahtjevall.ui \
    forms/stranka/frmstrankaadresa.ui \
    forms/log/frmdonatmenu_old.ui \
    forms/log/frmdonatmenu.ui \
    forms/sporazumi/frmobavijestislanje.ui \
    forms/sporazumi/frmobavijestiposlane.ui \
    forms/sporazumi/frmzahtjevipregled.ui \
    forms/sporazumi/frmzahtjevinemoguci.ui \
    forms/sporazumi/frmugovoripregled.ui \
    forms/sporazumi/frmugovoriugovaranje.ui \
    forms/kontakt/frmkontaktnicentar.ui \
    forms/stranka/frmstrankazurnal.ui \
    forms/sporazumi/frmgrupaimovineatributi.ui \
    forms/stranka/frmstrankagrupeimovine.ui \
    forms/kontakt/frmkontaktnicentaruser.ui \
    forms/kontakt/frmkontaktnicentarpretraga.ui \
    forms/kontakt/frmkanalprodaje.ui \
    forms/sporazumi/frmbundleinfo.ui \
    forms/kontakt/prigovor/frmprigovoradd.ui \
    forms/kontakt/prigovor/frmprigovorpregled.ui \
    forms/kontakt/prigovor/frmprigovorodabirstatusa.ui \
    forms/kontakt/prigovor/frmprigovorstatus.ui \
    forms/kontakt/prigovor/frmprigovorjop.ui \
    forms/kontakt/prigovor/frmprigovorosporavaniiznos.ui \
    forms/kontakt/prigovor/frmprigovoredit.ui \
    forms/kontakt/prigovor/frmprigovorpisanorjesenje.ui \
    forms/kontakt/frmkontaktdokumenti.ui \
    forms/kontakt/prigovor/frmprigovorodobrenje.ui \
    forms/kontakt/prigovor/frmprigovorpismopotvrde.ui \
    forms/kontakt/frmkontaktdokumenti1.ui \
    forms/kontakt/frmkanalprodajekorisnik.ui \
    forms/sporazumi/frmsuspenzija.ui \
    forms/kontakt/zlonamjerni/frmzlonamjerniadd.ui \
    forms/kontakt/zlonamjerni/frmzlonamjernipregled.ui \
    forms/kontakt/zlonamjerni/frmzlonamjernimobadd.ui \
    forms/stranka/frmmdm1.ui \
    forms/stranka/frmmdm2.ui \
    forms/stranka/frmmdm3.ui

RESOURCES += \
    resources/DonatForm.qrc

unix:
# The ORACLE OCI library
LIBS += -L/$$(ORACLE_HOME)/lib -locci
LIBS += -L/usr/local/lib -lclntsh

INCLUDEPATH += $$quote($$(ORACLE_HOME)/include)
