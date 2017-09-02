#ifndef CASPARCGVIDEOMETADATA_H
#define CASPARCGVIDEOMETADATA_H

#include "casparcgmediametadata.h"

class CasparCGVideoMetaData : public CasparCGMediaMetaData
{
public:
    CasparCGVideoMetaData();
    CasparCGVideoMetaData(const CasparCGVideoMetaData &other);

    virtual QString type() const override { return "MOVIE"; }

    void setSeek(quint32 frames) { m_seek = frames; }
    quint32 seek() const { return m_seek; }
    void setLength(quint32 frames) { m_length = frames; }
    quint32 length() const { return m_length; }
    void setLoop(bool loop) { m_loop = loop; }
    bool loop() const { return m_loop; }
    void setFreezeOnLoad(bool freeze) { m_freezeOnLoad = freeze; }
    bool freezeOnLoad() const { return m_freezeOnLoad; }
    void setAutoPlay(bool autoPlay) { m_autoPlay = autoPlay; }
    bool autoPlay() const { return m_autoPlay; }

    virtual void createItem(QXmlStreamWriter *writer, const QString &label, const QString &name) const override;

    virtual void readSettings() override;
    virtual void writeSettings() const override;

private:
    quint32 m_seek;
    quint32 m_length;
    bool m_loop;
    bool m_freezeOnLoad;
    bool m_autoPlay;
};

#endif // CASPARCGVIDEOMETADATA_H
