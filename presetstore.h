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
#ifndef PRESETSTORE_H
#define PRESETSTORE_H

#include <QObject>
#include <QHash>

class Preset;

class PresetStore : public QObject
{
    Q_OBJECT
public:
    explicit PresetStore(QObject *parent = nullptr);
    ~PresetStore();

    void loadPresets();

    QString createObject(const QString &presetName, const QVariantHash &attributes);

protected:
    void clear();

private:
    QHash<QString, Preset*> m_presets;
};

#endif // PRESETSTORE_H
