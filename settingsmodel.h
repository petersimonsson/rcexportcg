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
#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QAbstractItemModel>

class SettingsModelItem;

class SettingsModel : public QAbstractItemModel
{
public:
    explicit SettingsModel(QObject *parent = nullptr);
    ~SettingsModel();

    void clear();
    QModelIndex append(SettingsModelItem* item);
    QList<SettingsModelItem*> items() const { return m_items; }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;

private:
    QList<SettingsModelItem*> m_items;
};

class SettingsModelItem
{
public:
    SettingsModelItem() {}

    void setObject(const QString &object) { m_object = object; }
    QString object() const { return m_object; }

    void setPreset(const QString &preset) { m_preset = preset; }
    QString preset() const { return m_preset; }

private:
    QString m_object;
    QString m_preset;
};

#endif // SETTINGSMODEL_H
