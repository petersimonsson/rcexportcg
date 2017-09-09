/**************************************************************************
  RCExportCG
  Copyright (C) 2017  Peter Simonsson <peter.simonsson@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
#include "logmodel.h"

LogModel::LogModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

LogModel::~LogModel()
{
    qDeleteAll(m_items);
}

QVariant LogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch(section)
        {
        case 0:
            return tr("Timestamp");
        case 1:
            return tr("Type");
        case 2:
            return tr("Message");
        }
    }

    return QVariant();
}

QModelIndex LogModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column, m_items[row]);
}

QModelIndex LogModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)

    return QModelIndex();
}

int LogModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_items.count();
}

int LogModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return QVariant();

    Item *item = m_items[index.row()];

    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            return item->timestamp;
        case 1:
            return typeToString(item->type);
        case 2:
            return item->message;
        }
    }

    return QVariant();
}

void LogModel::append(Type type, const QString &message)
{
    beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
    Item *item = new Item;
    item->type = type;
    item->message = message;
    item->timestamp = QDateTime::currentDateTime();
    m_items.append(item);
    endInsertRows();
}

QString LogModel::typeToString(Type type) const
{
    switch(type)
    {
    case Error:
        return tr("Error");
    case Info:
        return tr("Info");
    case Debug:
        return tr("Debug");
    }

    return QString();
}
