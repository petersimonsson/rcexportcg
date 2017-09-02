#ifndef CASPARCGSTILLMETADATA_H
#define CASPARCGSTILLMETADATA_H

#include "casparcgmediametadata.h"

class CasparCGStillMetaData : public CasparCGMediaMetaData
{
public:
    CasparCGStillMetaData();
    CasparCGStillMetaData(const CasparCGStillMetaData &other);

    virtual QString type() const override { return "STILL"; }

    void setUseAuto(bool use) { m_useAuto = use; }
    bool useAuto() const { return m_useAuto; }

    virtual void createItem(QXmlStreamWriter *writer, const QString &label, const QString &name) const override;

    virtual void readSettings() override;
    virtual void writeSettings() const override;

private:
    bool m_useAuto;
};

#endif // CASPARCGSTILLMETADATA_H
