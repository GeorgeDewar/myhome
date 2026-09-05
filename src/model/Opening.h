#pragma once

#include <QPoint>
#include <QString>
#include <expected>
#include <QJsonObject>

enum class HingeSide {
    Left,
    Right
};

enum class SwingDirection {
    Inward,
    Outward
};

class Opening final
{
    public:
        Opening(QString id, double distanceAlongWall, double distanceFromFloor, double width, double height, double thickness, HingeSide hingeSide, SwingDirection swingDirection)
            : id_(std::move(id)), distanceAlongWall_(distanceAlongWall), distanceFromFloor_(distanceFromFloor), width_(width), height_(height), thickness_(thickness), hingeSide_(hingeSide), swingDirection_(swingDirection) {}
        static std::expected<Opening, QString> fromJson(const QJsonObject &json);

        const QString& id() const { return id_; }
        double distanceAlongWall() const { return distanceAlongWall_; }
        double distanceFromFloor() const { return distanceFromFloor_; }
        double width() const { return width_; }
        double height() const { return height_; }
        double thickness() const { return thickness_; }
        double edgeDistanceFromWall() const { return distanceAlongWall_ - (width_ / 2.0); }
        HingeSide hingeSide() const { return hingeSide_; }
        SwingDirection swingDirection() const { return swingDirection_; }
    private:
        QString id_;
        double distanceAlongWall_;
        double distanceFromFloor_;
        double width_;
        double height_;
        // TODO: Only applicable to doors
        double thickness_ {0.035}; // Default door thickness in metres
        // TODO: Only applicable to doors
        HingeSide hingeSide_ {HingeSide::Left};
        // TODO: Only applicable to doors
        SwingDirection swingDirection_ {SwingDirection::Inward};
};