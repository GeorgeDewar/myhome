#include "WallRenderer.h"
#include "model/Plan.h"
#include <QPen>
#include <QPainterPath>

void WallRenderer::renderWalls(const Plan &plan, int currentLevel) {
    plan.forCurrentLevelOfEachBuilding(currentLevel, [this](const Building &, const Level &level) {
        const auto &walls = level.getWalls();
        QPainterPath wallArea;
        for (const auto &wall : walls) {
            const QPolygonF polygon = wall.areaPolygon();
            if (polygon.isEmpty()) {
                qWarning() << "Wall has zero length, skipping.";
                continue;
            }

            QPainterPath wallFramingPath;
            wallFramingPath.addPolygon(polygon);
            wallFramingPath.closeSubpath();

            wallArea = wallArea.united(wallFramingPath);
        }

        // Fill in the wall area, representing the framing, in solid yellow
        painter_->setPen(Qt::NoPen);
        painter_->setBrush(QColor(255, 215, 0));
        painter_->drawPath(wallArea);

        // Draw the wall outlines in black
        QPen liningPen(Qt::black);
        liningPen.setWidth(0); // Cosmetic: always one physical screen pixel.
        painter_->setPen(liningPen);
        painter_->setBrush(Qt::NoBrush);
        painter_->drawPath(wallArea);
    });
}
