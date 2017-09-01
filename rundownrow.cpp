#include "rundownrow.h"

RundownRow::RundownRow(quint32 rundownId, quint32 rowId) :
    m_rundownId(rundownId), m_rowId(rowId)
{
}

void RundownRow::appendObject(const QString &type, const QString &file)
{
    Object object;
    object.type = type;
    object.file = file;
    m_objects.append(object);
}
