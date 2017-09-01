#ifndef RUNDOWNROW_H
#define RUNDOWNROW_H

#include <QString>
#include <QList>

class RundownRow
{
public:
    struct Object
    {
        QString type;
        QString file;
    };

    RundownRow(quint32 rundownId, quint32 rowId);

    quint32 rundownId() const { return m_rundownId; }
    quint32 rowId() const { return m_rowId; }

    void setPageNumber(const QString &number) { m_pageNumber = number; }
    QString pageNumber() const { return m_pageNumber; }

    void setStorySlug(const QString &slug) { m_storySlug = slug; }
    QString storySlug () const { return m_storySlug; }

    void appendObject(const QString &type, const QString &file);
    QList<RundownRow::Object> objects() const { return m_objects; }

private:
    quint32 m_rundownId;
    quint32 m_rowId;
    QString m_pageNumber;
    QString m_storySlug;
    QList<Object> m_objects;
};

#endif // RUNDOWNROW_H
