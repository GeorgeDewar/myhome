#pragma once

#include "OpeningItem.h"
#include "Opening.h"
#include <QString>
#include <QJsonObject>
#include <expected>

enum class HingeSide {
    Left,
    Right
};

enum class SwingDirection {
    Inward,
    Outward
};

class StandardDoor final : public OpeningItem
{
    public:
        StandardDoor() : OpeningItem() { }
        std::string type() const override { return "StandardDoor"; }

        static void from_json(const QJsonObject &json, StandardDoor &standardDoor);
        HingeSide hingeSide;
        SwingDirection swingDirection;
        double thickness {0.035}; // Default thickness in metres
    private:
        
};