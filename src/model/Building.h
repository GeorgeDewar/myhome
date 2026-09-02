#pragma once
#include <vector>
#include "Level.h"
#include <expected>
#include <QJsonObject>

class Building final
{
    public:
        Building();
        static std::expected<Building, QString> fromJson(const QJsonObject &json);
        const std::vector<Level>& getLevels() const {
            return levels_;
        }
    
    private:
        std::vector<Level> levels_;
};