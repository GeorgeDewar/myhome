#include "WallRenderer.h"
#include "DoorRenderer.h"
#include "WindowRenderer.h"
#include "model/Plan.h"
#include <QPen>
#include <QPainterPath>

void WallRenderer::renderWalls(const Plan &plan, int currentLevel) {
    DoorRenderer doorRenderer(painter_);
    WindowRenderer windowRenderer(painter_);
    plan.forCurrentLevelOfEachBuilding(currentLevel, [this, &doorRenderer, &windowRenderer](const Building &, const Level &level) {
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
            
            for (const auto &door : wall.doors()) {
                const QPolygonF doorPolygon = wall.openingPolygon(door);
                if (!doorPolygon.isEmpty()) {
                    QPainterPath doorPath;
                    doorPath.addPolygon(doorPolygon);
                    doorPath.closeSubpath();
                    wallFramingPath = wallFramingPath.subtracted(doorPath);
                }
            }
            for (const auto &window : wall.windows()) {
                const QPolygonF windowPolygon = wall.openingPolygon(window);
                if (!windowPolygon.isEmpty()) {
                    QPainterPath windowPath;
                    windowPath.addPolygon(windowPolygon);
                    windowPath.closeSubpath();
                    wallFramingPath = wallFramingPath.subtracted(windowPath);
                }
            }

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

        for (const auto &wall : walls) {
            for (const auto &door : wall.doors()) {
                doorRenderer.renderDoor(wall, door);
            }
            for (const auto &window : wall.windows()) {
                windowRenderer.renderWindow(wall, window);
            }
        }
    });
}
