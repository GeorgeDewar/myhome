#include "Level.h"
#include <QJsonObject>
#include <QJsonArray>
#include <expected>
#include "Wall.h"

std::expected<Level, QString> Level::fromJson(const QJsonObject &json) {
    Level level;
    QJsonArray wallsArray = json.value("walls").toArray();
    for(int i = 0; i < wallsArray.size(); ++i) {
        qDebug() << "Parsing wall " << i;
        QJsonObject wallObj = wallsArray[i].toObject();
        Wall wall = Wall::fromJson(wallObj).value();
        level.walls_.push_back(wall);
    }
    return level;
}