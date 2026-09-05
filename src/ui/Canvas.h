#pragma once

#include <QWidget>

class Plan;
class Wall;
class Opening;
class QPaintEvent;
class QMouseEvent;
class QPoint;
class QPainter;
class QKeyEvent;
class QWheelEvent;

class Canvas final : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    double scale() const;
    QPointF offset() const;
    /** Convert a point from real-world coordinates (in metres) to canvas coordinates (in pixels) */
    QPointF toCanvasCoordinates(const QPointF &point);
    /** Convert a point from canvas coordinates (in pixels) to real-world coordinates (in metres) */
    QPointF toRealCoordinates(const QPointF &point);
    /** Set the current plan to be displayed on the canvas */
    void setPlan(const Plan *plan);
    int currentLevel() const { return currentLevel_; }
    /** Set the current level of the plan to be displayed */
    void setCurrentLevel(int level);
    /** Check if a point in real-world coordinates is currently visible on the canvas */
    bool isOnScreen(const QPointF &point) const;

signals:
    void cursorPositionChanged(const QPointF &position);
    void scaleChanged(double scale);
    void offsetChanged(const QPointF &offset);
    void wallSelected(const Wall &wall);
    void doorSelected(const Opening &door);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    static constexpr double minimumScale_ = 10.0; // pixels per metre, fully zoomed out
    static constexpr double maximumScale_ = 640.0; // pixels per metre, fully zoomed in
    static constexpr double keyboardPanDistance_ = 50.0; // pixels per key press

    /** Offset of the top-left of the canvas from the origin of the coordinate system, in metres */
    QPointF offset_ {-1.0, -1.0};
    /** Scale factor (i.e. zoom level) in pixels per metre */
    double scale_ {20.0};
    /** Last known mouse position, used for panning with the middle mouse button */
    QPoint lastMousePosition_;
    /** A reference to the current plan expected to be displayed on the canvas */
    const Plan *plan_ {nullptr};
    /** The current level of the plan to be displayed */
    int currentLevel_ {0};

    /** Paint the grid on the canvas */
    void paintGrid(QPainter &painter);
    /** Paint the origin marker on the canvas at real-world position (0,0) */
    void paintOriginMarker(QPainter &painter);
    /** Paint the current plan on the canvas */
    void paintPlan(QPainter &painter);
};