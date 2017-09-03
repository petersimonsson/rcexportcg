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
#include "settingsmodel.h"

SettingsModel::SettingsModel(QObject *parent) : QAbstractItemModel(parent)
{
}

SettingsModel::~SettingsModel()
{
    clear();
}

void SettingsModel::clear()
{
    qDeleteAll(m_items);
    m_items.clear();
}

QModelIndex SettingsModel::append(SettingsModelItem* item)
{
    beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
    m_items.append(item);
    endInsertRows();

    return index(m_items.count() - 1, 0, QModelIndex());
}

QModelIndex SettingsModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column, m_items[row]);
}

QModelIndex SettingsModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)

    return QModelIndex();
}

int SettingsModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_items.count();
}

int SettingsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 2;
}

QVariant SettingsModel::data(const QModelIndex &index, int role) const
{
    if(!hasIndex(index.row(), index.column(), index.parent()))
        return QVariant();

    SettingsModelItem *item = m_items[index.row()];

    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            return item->object();
        case 1:
            return item->preset();
        }
        break;
    }

    return QVariant();
}

QVariant SettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal)
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
        switch(section)
        {
        case 0:
            return tr("Object");
        case 1:
            return tr("Preset");
        }
    }

    return QVariant();
}

bool SettingsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!hasIndex(index.row(), index.column(), index.parent()))
        return false;

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        SettingsModelItem *item = m_items[index.row()];

        switch(index.column())
        {
        case 0:
            item->setObject(value.toString());
            break;
        case 1:
            item->setPreset(value.toString());
            break;
        }

        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags SettingsModel::flags(const QModelIndex &index) const
{
    if(!hasIndex(index.row(), index.column(), index.parent()))
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool SettingsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int endRow = row + count - 1;

    if(parent.isValid() || row >= m_items.count() || endRow >= m_items.count())
        return false;

    beginRemoveRows(parent, row, endRow);
    for(int i = row; i <= endRow; ++i)
        delete m_items.takeAt(i);
    endRemoveRows();

    return true;
}
