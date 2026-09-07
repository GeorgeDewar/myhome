#pragma once

#include "Opening.h"
#include <QPoint>
#include <QString>
#include <expected>
#include <QJsonObject>
#include <QVector2D>
#include <QtMath>

class Wall final
{
    public:
        Wall(QString id, QPointF startPoint, QPointF endPoint, double thickness);
        static std::expected<Wall, QString> fromJson(const QJsonObject &json);

        const QString& id() const { return id_; }
        QPointF startPoint() const { return startPoint_; }
        QPointF endPoint() const { return endPoint_; }
        double thickness() const { return thickness_; }
        const QVector2D& direction() const { return direction_; }
        const QVector2D& unitDirection() const { return unitDirection_; }
        const double angle() const { return qRadiansToDegrees(std::atan2(unitDirection_.y(), unitDirection_.x())); }
        /** Return the polygon representing the area of the wall, excluding linings */
        QPolygonF areaPolygon() const;
        /** Return the polygon representing the area of the given opening within the wall, with the same thickness as areaPolygon */
        QPolygonF openingPolygon(const Opening& opening) const;
        const std::vector<Opening>& openings() const { return openings_; }
    
    private:
        QString id_;
        QPointF startPoint_;
        QPointF endPoint_;
        double thickness_ {0.1}; // Default thickness in metres
        const QVector2D direction_ { QVector2D(endPoint_ - startPoint_) };
        const QVector2D unitDirection_ { direction_.normalized() };
        std::vector<Opening> openings_ {};
};