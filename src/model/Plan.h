#pragma once

#include <QJsonObject>
#include <QString>

#include <expected>
#include <vector>

#include "Building.h"

class Plan final
{
public:
    Plan() = default;
    static std::expected<Plan, QString> fromJson(const QJsonObject &json);
    const std::vector<Building>& getBuildings() const {
        return buildings_;
    }
    template <typename Function>
    void forCurrentLevelOfEachBuilding(int currentLevel, Function &&function) const {
        for (const auto &building : buildings_) {
            const auto &levels = building.getLevels();
            if (currentLevel < 0 || currentLevel >= levels.size()) {
                continue;
            }
            function(building, levels[currentLevel]);
        }
    }
    int minLevel() const { return 0; } // TODO: Calculate based on buildings
    int maxLevel() const { return 3; } // TODO: Calculate based on buildings

private:
    std::vector<Building> buildings_;
};