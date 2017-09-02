#ifndef RUNDOWNROW_H
#define RUNDOWNROW_H

#include <QString>
#include <QList>

class RundownRow
{
public:
    RundownRow(const QString &type, const QString &file);

    QString type() const { return m_type; }
    QString file() const { return m_file; }

    void setRundownId(quint32 id) { m_rundownId = id; }
    quint32 rundownId() const { return m_rundownId; }
    void setRowId(quint32 id) { m_rowId = id; }
    quint32 rowId() const { return m_rowId; }

    void setPageNumber(const QString &number) { m_pageNumber = number; }
    QString pageNumber() const { return m_pageNumber; }

    void setStorySlug(const QString &slug) { m_storySlug = slug; }
    QString storySlug () const { return m_storySlug; }

private:
    QString m_type;
    QString m_file;

    quint32 m_rundownId;
    quint32 m_rowId;
    QString m_pageNumber;
    QString m_storySlug;
};

#endif // RUNDOWNROW_H
