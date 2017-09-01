#include "rundown.h"

Rundown::Rundown(quint32 id, const QString &title) :
    m_id(id), m_title(title), m_frozen(false), m_locked(false),
    m_archived(false), m_template(false), m_deleted(false)
{
}
