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

private:
    std::vector<Building> buildings_;
};