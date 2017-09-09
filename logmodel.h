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
#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QAbstractItemModel>
#include <QDateTime>
#include <QIcon>

class LogModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Type
    {
        Error,
        Info,
        Debug
    };

    struct Item
    {
        Type type;
        QDateTime timestamp;
        QString message;
    };

    explicit LogModel(QObject *parent = nullptr);
    ~LogModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void append(Type type, const QString &message);

private:
    QString typeToString(Type type) const;

    QList<Item*> m_items;

    QIcon m_errorIcon;
    QIcon m_infoIcon;
    QIcon m_debugIcon;
};

#endif // LOGMODEL_H
