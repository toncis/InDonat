#include "wgdonatmenu4.h"

namespace Log {

WgDonatMenu4::WgDonatMenu4(QWidget *parent) :
    QWidget(parent)
{
    m_vboxDonatStrankaImovina = new QVBoxLayout();
    m_vboxDonatStrankaImovina->setContentsMargins(2, 2, 2, 2);
    m_vboxDonatStrankaImovina->setSpacing(1);
    // [0]
    createStrankaKlaseTitle();
    m_vboxDonatStrankaImovina->addWidget(m_fraStrankaImovinaKlasaTitle);
    // [1]
    createStrankaGrupaImovineTitle();
    m_vboxDonatStrankaImovina->addWidget(m_fraStrankaGrupaImovineTitle);
    // [2]
    createStrankaGrupaImovine();
    m_vboxDonatStrankaImovina->addWidget(m_fraStrankaGrupaImovine);
    // [3]
    createStrankaUgovornaObveza();
    m_vboxDonatStrankaImovina->addWidget(m_fraStrankaUgovorneObveze);
    // [4]
    createStrankaImovinaTitle();
    m_vboxDonatStrankaImovina->addWidget(m_fraStrankaImovinaTitle);
    // [5]
    createStrankaImovina();
    m_vboxDonatStrankaImovina->addWidget(m_fraStrankaImovina);
    // [6]
    createStrankaImovinaStatusTitle();
    m_vboxDonatStrankaImovina->addWidget(m_fraStrankaImovinaStatusTitle);
    // [7]
    createStrankaImovinaStatus();
    m_vboxDonatStrankaImovina->addWidget(m_fraStrankaImovinaStatus);

//    QSizePolicy fraDonatStrankaImovinaSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
//    fraDonatStrankaImovinaSizePolicy.setHorizontalStretch(0);
//    fraDonatStrankaImovinaSizePolicy.setVerticalStretch(0);
//    this->setSizePolicy(fraDonatSearchResultsSizePolicy);

    setLayout(m_vboxDonatStrankaImovina);

    // Actions
    connect(m_btnStrankaGrupaImovineColapse, SIGNAL(clicked()), this, SLOT(on_btnStrankaGrupaImovineColapse_clicked()));
    connect(m_btnStrankaImovinaColapse, SIGNAL(clicked()), this, SLOT(on_btnStrankaImovinaColapse_clicked()));
}

void WgDonatMenu4::createStrankaKlaseTitle()
{
    m_fraStrankaImovinaKlasaTitle = new QFrame();
    m_fraStrankaImovinaKlasaTitle->setContentsMargins(0, 0, 0, 0);
//    m_fraStrankaImovinaKlasaTitle->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 2, 0, 2);
    hboxLayout->setSpacing(1);
    // [0]
    m_lblStrankaKlaseTitle = new QLabel(tr("Klasa"));
    m_lblStrankaKlaseTitle->setFrameShape(QFrame::StyledPanel);
    m_lblStrankaKlaseTitle->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxLayout->addWidget(m_lblStrankaKlaseTitle);
    // [1]
    m_cboStrankaImovinaKlase = new QComboBox();
    m_cboStrankaImovinaKlase->addItem(tr(""));
//    m_cboStrankaImovinaKlase->setEditable(TRUE);
//    m_cboDonatSearchResult->setFrameShape(QFrame::StyledPanel);
    hboxLayout->addWidget(m_cboStrankaImovinaKlase);
    m_fraStrankaImovinaKlasaTitle->setLayout(hboxLayout);
}

void WgDonatMenu4::createStrankaGrupaImovineTitle()
{
    m_fraStrankaGrupaImovineTitle = new QFrame();
    m_fraStrankaGrupaImovineTitle->setContentsMargins(0, 0, 0, 0);
//    m_fraStrankaGrupaImovineTitle->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 2, 0, 2);
    hboxLayout->setSpacing(1);
    // [0]
    QLabel *lblStrankaGrupaImovineTitle = new QLabel(tr("Id"));
    lblStrankaGrupaImovineTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblStrankaGrupaImovineTitleSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    lblStrankaGrupaImovineTitleSizePolicy.setHorizontalStretch(0);
    lblStrankaGrupaImovineTitleSizePolicy.setVerticalStretch(0);
    lblStrankaGrupaImovineTitle->setSizePolicy(lblStrankaGrupaImovineTitleSizePolicy);
    hboxLayout->addWidget(lblStrankaGrupaImovineTitle);
    // [1]
    m_txtStrankaGrupaImovineId = new QLabel(tr(" "));
    m_txtStrankaGrupaImovineId->setFrameShape(QFrame::StyledPanel);
    m_txtStrankaGrupaImovineId->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
//    QSizePolicy txtStrankaGrupaImovineIdSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    txtStrankaGrupaImovineIdSizePolicy.setHorizontalStretch(0);
//    txtStrankaGrupaImovineIdSizePolicy.setVerticalStretch(0);
//    m_txtStrankaGrupaImovineId->setSizePolicy(txtStrankaGrupaImovineIdSizePolicy);
    hboxLayout->addWidget(m_txtStrankaGrupaImovineId);
    //[0]
    m_btnStrankaNeaktivneGrupeImovine = new QPushButton();
    m_btnStrankaNeaktivneGrupeImovine->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
    QSizePolicy btnStrankaNeaktivneGrupeImovineSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaNeaktivneGrupeImovineSizePolicy.setHorizontalStretch(0);
    btnStrankaNeaktivneGrupeImovineSizePolicy.setVerticalStretch(0);
    m_btnStrankaNeaktivneGrupeImovine->setSizePolicy(btnStrankaNeaktivneGrupeImovineSizePolicy);
    hboxLayout->addWidget(m_btnStrankaNeaktivneGrupeImovine);
    //[1]
    m_btnStrankaGrupaImovineZurnal = new QPushButton();
    m_btnStrankaGrupaImovineZurnal->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/POVECALO.png")));
    QSizePolicy btnStrankaGrupaImovineZurnalSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaGrupaImovineZurnalSizePolicy.setHorizontalStretch(0);
    btnStrankaGrupaImovineZurnalSizePolicy.setVerticalStretch(0);
    m_btnStrankaGrupaImovineZurnal->setSizePolicy(btnStrankaGrupaImovineZurnalSizePolicy);
    hboxLayout->addWidget(m_btnStrankaGrupaImovineZurnal);
    //[2]
    m_btnStrankaGrupaImovineColapse = new QPushButton();
    m_btnStrankaGrupaImovineColapse->setObjectName(tr("exp"));
    m_btnStrankaGrupaImovineColapse->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/exp.gif")));
    QSizePolicy btnStrankaGrupaImovineColapseSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaGrupaImovineColapseSizePolicy.setHorizontalStretch(0);
    btnStrankaGrupaImovineColapseSizePolicy.setVerticalStretch(0);
    m_btnStrankaGrupaImovineColapse->setSizePolicy(btnStrankaGrupaImovineColapseSizePolicy);
    hboxLayout->addWidget(m_btnStrankaGrupaImovineColapse);

    m_fraStrankaGrupaImovineTitle->setLayout(hboxLayout);
}

void WgDonatMenu4::createStrankaGrupaImovine()
{
    m_fraStrankaGrupaImovine = new QFrame();
    m_fraStrankaGrupaImovine->setContentsMargins(0, 0, 0, 0);
//    m_fraStrankaGrupaImovine->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    hboxLayout->setSpacing(0);
    //[0]
    m_treeStrankaGrupaImovine = new QTreeWidget();
    m_treeStrankaGrupaImovine->setContentsMargins(4, 4, 0, 0);
    m_treeStrankaGrupaImovine->setFrameShape(QFrame::StyledPanel);
//    m_treeStrankaGrupaImovine->setMinimumWidth(600);
    // Create headers
    QStringList labels;
    labels << "GrupaImovine" << "GrupaImovineID" << "B1" << "B2" << "TEL_BROJ" << "TEL_LIN_ID"
              << "IMOVINA_ID" << "SLOG_STATUS" << "DATUM_OD" << "Zastavica" << "Churn";
    m_treeStrankaGrupaImovine->setColumnCount(11);
    m_treeStrankaGrupaImovine->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    m_treeStrankaGrupaImovine->setColumnWidth(0, 1);
    m_treeStrankaGrupaImovine->hideColumn(1);
    m_treeStrankaGrupaImovine->hideColumn(2);
    m_treeStrankaGrupaImovine->hideColumn(3);
    m_treeStrankaGrupaImovine->hideColumn(4);
    m_treeStrankaGrupaImovine->hideColumn(5);
    m_treeStrankaGrupaImovine->hideColumn(6);
    m_treeStrankaGrupaImovine->hideColumn(7);
    m_treeStrankaGrupaImovine->hideColumn(8);
    m_treeStrankaGrupaImovine->setColumnWidth(0, 280);
    m_treeStrankaGrupaImovine->setHeaderHidden(true);
    m_treeStrankaGrupaImovine->setAlternatingRowColors(false);
    m_treeStrankaGrupaImovine->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeStrankaGrupaImovine->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_treeStrankaGrupaImovine->setItemsExpandable(true); //QTreeWidgetItem::DontShowIndicatorWhenChildless
    m_treeStrankaGrupaImovine->setRootIsDecorated(true);
    hboxLayout->addWidget(m_treeStrankaGrupaImovine);

    m_fraStrankaGrupaImovine->setLayout(hboxLayout);
}

void WgDonatMenu4::createStrankaUgovornaObveza()
{
    m_fraStrankaUgovorneObveze = new QFrame();
    m_fraStrankaUgovorneObveze->setContentsMargins(0, 0, 0, 0);
//    m_fraStrankaUgovorneObveze->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 2, 0, 2);
    hboxLayout->setSpacing(1);
    //[0]
    m_imgStrankaUgovorneObveze = new QLabel();
    m_imgStrankaUgovorneObveze->setFrameShape(QFrame::StyledPanel);
    m_imgStrankaUgovorneObveze->setMaximumWidth(32);
    QSizePolicy imgStrankaUgovorneObvezeSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    imgStrankaUgovorneObvezeSizePolicy.setHorizontalStretch(0);
    imgStrankaUgovorneObvezeSizePolicy.setVerticalStretch(0);
    m_imgStrankaUgovorneObveze->setSizePolicy(imgStrankaUgovorneObvezeSizePolicy);
    hboxLayout->addWidget(m_imgStrankaUgovorneObveze);
    //[1]
    m_txtStrankaUgovorneObveze = new QLabel();
    m_txtStrankaUgovorneObveze->setFrameShape(QFrame::StyledPanel);
    m_txtStrankaUgovorneObveze->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    QSizePolicy txtStrankaUgovorneObvezeSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    txtStrankaUgovorneObvezeSizePolicy.setHorizontalStretch(0);
    txtStrankaUgovorneObvezeSizePolicy.setVerticalStretch(0);
    m_txtStrankaUgovorneObveze->setSizePolicy(txtStrankaUgovorneObvezeSizePolicy);
    hboxLayout->addWidget(m_txtStrankaUgovorneObveze);
    //[2]
    m_btnStrankaUgovorneObveze = new QPushButton();
    m_btnStrankaUgovorneObveze->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/POVECALO.png")));
    QSizePolicy btnStrankaUgovorneObvezeSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaUgovorneObvezeSizePolicy.setHorizontalStretch(0);
    btnStrankaUgovorneObvezeSizePolicy.setVerticalStretch(0);
    m_btnStrankaUgovorneObveze->setSizePolicy(btnStrankaUgovorneObvezeSizePolicy);
    hboxLayout->addWidget(m_btnStrankaUgovorneObveze);

    m_fraStrankaUgovorneObveze->setLayout(hboxLayout);
}

void WgDonatMenu4::createStrankaImovinaTitle()
{
    m_fraStrankaImovinaTitle = new QFrame();
    m_fraStrankaImovinaTitle->setContentsMargins(0, 0, 0, 0);
//    m_fraStrankaImovinaTitle->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 2, 0, 2);
    hboxLayout->setSpacing(1);
    // [0]
    QLabel *lblStrankaImovineIdTitle = new QLabel(tr("Id"));
    lblStrankaImovineIdTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblStrankaImovineIdTitleSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    lblStrankaImovineIdTitleSizePolicy.setHorizontalStretch(0);
    lblStrankaImovineIdTitleSizePolicy.setVerticalStretch(0);
    lblStrankaImovineIdTitle->setSizePolicy(lblStrankaImovineIdTitleSizePolicy);
    hboxLayout->addWidget(lblStrankaImovineIdTitle);
    // [1]
    m_txtStrankaImovinaId = new QLabel(tr(" "));
    m_txtStrankaImovinaId->setFrameShape(QFrame::StyledPanel);
    m_txtStrankaImovinaId->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxLayout->addWidget(m_txtStrankaImovinaId);
    //[0]
    m_btnStrankaImovinaOprema = new QPushButton();
    m_btnStrankaImovinaOprema->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/Registering.gif")));
    m_btnStrankaImovinaOprema->setEnabled(FALSE);
    QSizePolicy btnStrankaImovinaOpremaSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaImovinaOpremaSizePolicy.setHorizontalStretch(0);
    btnStrankaImovinaOpremaSizePolicy.setVerticalStretch(0);
    m_btnStrankaImovinaOprema->setSizePolicy(btnStrankaImovinaOpremaSizePolicy);
    hboxLayout->addWidget(m_btnStrankaImovinaOprema);
    //[1]
    m_btnStrankaNeaktivnaImovina= new QPushButton();
    m_btnStrankaNeaktivnaImovina->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/CLOSE.GIF")));
    QSizePolicy btnStrankaNeaktivnaImovinaSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaNeaktivnaImovinaSizePolicy.setHorizontalStretch(0);
    btnStrankaNeaktivnaImovinaSizePolicy.setVerticalStretch(0);
    m_btnStrankaNeaktivnaImovina->setSizePolicy(btnStrankaNeaktivnaImovinaSizePolicy);
    hboxLayout->addWidget(m_btnStrankaNeaktivnaImovina);
    //[2]
    m_btnStrankaImovinaColapse = new QPushButton();
    m_btnStrankaImovinaColapse->setObjectName(tr("exp"));
    m_btnStrankaImovinaColapse->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/exp.gif")));
    QSizePolicy btnStrankaImovinaColapseSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    btnStrankaImovinaColapseSizePolicy.setHorizontalStretch(0);
    btnStrankaImovinaColapseSizePolicy.setVerticalStretch(0);
    m_btnStrankaImovinaColapse->setSizePolicy(btnStrankaImovinaColapseSizePolicy);
    hboxLayout->addWidget(m_btnStrankaImovinaColapse);

    m_fraStrankaImovinaTitle->setLayout(hboxLayout);
}

void WgDonatMenu4::createStrankaImovina()
{
    m_fraStrankaImovina = new QFrame();
    m_fraStrankaImovina->setContentsMargins(0, 0, 0, 0);
//    m_fraStrankaImovina->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 2, 0, 2);
    hboxLayout->setSpacing(1);
    //[0]
    m_treeStrankaImovina = new QTreeWidget();
    m_treeStrankaImovina->setContentsMargins(4, 4, 0, 0);
    m_treeStrankaImovina->setFrameShape(QFrame::StyledPanel);
//    m_treeStrankaImovina->setMinimumWidth(600);
    // Create headers
    QStringList labels;
    labels << "Naziv" << "ImovinaId" << "NadImovinaId" << "StatusId" << "Nivo" << "Naziv produkta"
           << "ImovinaAtributId" << "AtributId" << "Shown value" << "Naziv" << "Tip vrste atributa" << "WWMS naziv";
    m_treeStrankaImovina->setColumnCount(12);
    m_treeStrankaImovina->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    m_treeStrankaImovina->setColumnWidth(0, 1);
    m_treeStrankaImovina->hideColumn(1);
    m_treeStrankaImovina->hideColumn(2);
    m_treeStrankaImovina->hideColumn(3);
    m_treeStrankaImovina->hideColumn(4);
    m_treeStrankaImovina->hideColumn(5);
    m_treeStrankaImovina->hideColumn(6);
    m_treeStrankaImovina->hideColumn(7);
    m_treeStrankaImovina->hideColumn(8);
    m_treeStrankaImovina->hideColumn(9);
    m_treeStrankaImovina->hideColumn(10);
    m_treeStrankaImovina->hideColumn(11);
    m_treeStrankaImovina->setHeaderHidden(true);
    m_treeStrankaImovina->setAlternatingRowColors(false);
    m_treeStrankaImovina->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeStrankaImovina->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_treeStrankaImovina->setItemsExpandable(true); //QTreeWidgetItem::DontShowIndicatorWhenChildless
    m_treeStrankaImovina->setRootIsDecorated(true);

    QSizePolicy treeStrankaImovinaSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    treeStrankaImovinaSizePolicy.setHorizontalStretch(0);
    treeStrankaImovinaSizePolicy.setVerticalStretch(0);
    m_treeStrankaImovina->setSizePolicy(treeStrankaImovinaSizePolicy);

    hboxLayout->addWidget(m_treeStrankaImovina);

    m_fraStrankaImovina->setLayout(hboxLayout);
}

void WgDonatMenu4::createStrankaImovinaStatusTitle()
{
    m_fraStrankaImovinaStatusTitle = new QFrame();
    m_fraStrankaImovinaStatusTitle->setContentsMargins(0, 0, 0, 0);
//    m_fraStrankaImovinaKlasaTitle->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 2, 0, 2);
    hboxLayout->setSpacing(1);
    //[0]
    QLabel *lblStrankaImovinaStatusIdTitle = new QLabel(tr("Status"));
    lblStrankaImovinaStatusIdTitle->setFrameShape(QFrame::StyledPanel);
    QSizePolicy lblStrankaImovinaStatusIdTitleSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    lblStrankaImovinaStatusIdTitleSizePolicy.setHorizontalStretch(0);
    lblStrankaImovinaStatusIdTitleSizePolicy.setVerticalStretch(0);
    lblStrankaImovinaStatusIdTitle->setSizePolicy(lblStrankaImovinaStatusIdTitleSizePolicy);
    hboxLayout->addWidget(lblStrankaImovinaStatusIdTitle);
    // [1]
    m_txtStrankaImovinaStatus = new QLabel(tr(" "));
    m_txtStrankaImovinaStatus->setFrameShape(QFrame::StyledPanel);
    m_txtStrankaImovinaStatus->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    hboxLayout->addWidget(m_txtStrankaImovinaStatus);
    m_fraStrankaImovinaStatusTitle->setLayout(hboxLayout);
}

void WgDonatMenu4::createStrankaImovinaStatus()
{
    m_fraStrankaImovinaStatus = new QFrame();
    m_fraStrankaImovinaStatus->setContentsMargins(0, 0, 0, 0);
//    m_fraStrankaImovinaStatus->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 2, 0, 2);
    hboxLayout->setSpacing(1);
    //[0]
    m_lstStrankaImovinaStatus = new QListWidget();
    m_lstStrankaImovinaStatus->setMaximumHeight(90);

    QSizePolicy lstStrankaImovinaStatusSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    lstStrankaImovinaStatusSizePolicy.setHorizontalStretch(0);
    lstStrankaImovinaStatusSizePolicy.setVerticalStretch(0);
    m_lstStrankaImovinaStatus->setSizePolicy(lstStrankaImovinaStatusSizePolicy);

    hboxLayout->addWidget(m_lstStrankaImovinaStatus);

    m_fraStrankaImovinaStatus->setLayout(hboxLayout);
}

// [Event Handlers]
void WgDonatMenu4::on_btnStrankaGrupaImovineColapse_clicked()
{
    m_btnStrankaGrupaImovineColapse->icon().detach();
    if(m_btnStrankaGrupaImovineColapse->objectName() == tr("exp"))
    {
        m_btnStrankaGrupaImovineColapse->setObjectName(tr("col"));
        m_btnStrankaGrupaImovineColapse->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/col.gif")));
        m_treeStrankaGrupaImovine->expandAll();
    }
    else
    {
        m_btnStrankaGrupaImovineColapse->setObjectName(tr("exp"));
        m_btnStrankaGrupaImovineColapse->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/exp.gif")));
        m_treeStrankaGrupaImovine->collapseAll();
    }
}

void WgDonatMenu4::on_btnStrankaImovinaColapse_clicked()
{
    m_btnStrankaImovinaColapse->icon().detach();
    if(m_btnStrankaImovinaColapse->objectName() == tr("exp"))
    {
        m_btnStrankaImovinaColapse->setObjectName(tr("col"));
        m_btnStrankaImovinaColapse->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/col.gif")));
        m_treeStrankaImovina->expandAll();
    }
    else
    {
        m_btnStrankaImovinaColapse->setObjectName(tr("exp"));
        m_btnStrankaImovinaColapse->setIcon(QPixmap(QString::fromUtf8(":/InDonat/Forms/images/exp.gif")));
        m_treeStrankaImovina->collapseAll();
    }
}


WgDonatMenu4::~WgDonatMenu4()
{
    m_treeStrankaImovina->clear();
    m_treeStrankaGrupaImovine->clear();
    m_lstStrankaImovinaStatus->clear();
}

}   // namespace log
