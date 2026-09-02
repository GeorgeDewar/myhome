#include "Building.h"
#include <QJsonArray>
#include <QJsonObject>
#include "Level.h"
#include <expected>

Building::Building() = default;

std::expected<Building, QString> Building::fromJson(const QJsonObject &json) {
    Building building = Building();
    QJsonArray levelsArray = json.value("levels").toArray();
    for(int i = 0; i < levelsArray.size(); ++i) {
        qDebug() << "Parsing level " << i;
        QJsonObject levelObj = levelsArray[i].toObject();
        Level level = Level::fromJson(levelObj).value();
        building.levels_.push_back(level);
    }
    return building;
}