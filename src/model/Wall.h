#pragma once

#include <QPoint>
#include <QString>
#include <expected>
#include <QJsonObject>
#include "Opening.h"

class Wall final
{
    public:
        Wall(QString id, QPointF startPoint, QPointF endPoint, double thickness);
        static std::expected<Wall, QString> fromJson(const QJsonObject &json);

        const QString& id() const { return id_; }
        QPointF startPoint() const { return startPoint_; }
        QPointF endPoint() const { return endPoint_; }
        double thickness() const { return thickness_; }
        /** Return the polygon representing the area of the wall, excluding linings */
        QPolygonF areaPolygon() const;
        /** Return the polygon representing the area of the given opening within the wall, with the same thickness as areaPolygon */
        QPolygonF openingPolygon(const Opening& opening) const;
        const std::vector<Opening>& doors() const { return doors_; }
        const std::vector<Opening>& windows() const { return windows_; }
    
    private:
        QString id_;
        QPointF startPoint_;
        QPointF endPoint_;
        double thickness_ {0.1}; // Default thickness in metres
        std::vector<Opening> doors_ {};
        std::vector<Opening> windows_ {};
};