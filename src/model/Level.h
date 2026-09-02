#pragma once
#include <vector>
#include <expected>
#include <QJsonObject>
#include "Wall.h"

class Level final
{
    public:
        Level() = default;
        static std::expected<Level, QString> fromJson(const QJsonObject &json);
        const std::vector<Wall>& getWalls() const {
            return walls_;
        }
    
    private:
        std::vector<Wall> walls_;
};