#ifndef FRMBUNDLEINFO_H
#define FRMBUNDLEINFO_H

#include <QDialog>
#include <QTreeWidget>
#include <QMetaType>

#include "Bundle/nodetag_bundle.h"
#include "Bundle/bundle.h"
#include "donat.h"

namespace Ui {
class FrmBundleInfo;
}


namespace Sporazumi {
class FrmBundleInfo : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmBundleInfo(QWidget *parent = 0);
    explicit FrmBundleInfo(unsigned int iKupacId, QWidget *parent = 0);
    ~FrmBundleInfo();
    
private:
    Ui::FrmBundleInfo *ui;

    Bundle m_Bundle;
    QList<Bundle> m_lstBundle;

    unsigned int m_iKupacId;

    list<NodeTag_BundleView> m_lstBundleView;
    list<NodeTag_BundleAnaliza> m_lstBundleAnaliza;
    list<NodeTag_BundleInfo> m_lstBundleInfo;
    list<BundleSporazum> m_lstBundleSporazumi;

    NodeTag_BundleInfo m_BundleInfo;

    void popuniKupca(const unsigned int iKupacId);
    void popuniBundleZaKupca();
    void popuniBundleAnaliza(const unsigned int iGrupaImovineId);

    void popuniBundle();
    void popuniBundleAnaliza();
    void popuniBundleInfo();
    void popuniBUndleSporazumi();

    string jeLiBundle(const unsigned int iGrupaImovineId);
    unsigned int vratiBundleAsset(const unsigned int iGrupaImovineId);
    unsigned int vratiBundleAsset(const string strIdentifikator);

};

}   // namespace sporazumi

#endif // FRMBUNDLEINFO_H
