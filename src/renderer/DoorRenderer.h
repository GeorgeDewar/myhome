#pragma once

class Opening;
class QPainter;
class Wall;

class DoorRenderer final {
public:
    explicit DoorRenderer(QPainter *painter) : painter_(painter) {}

    void renderDoor(const Wall &wall, const Opening &door);

private:
    QPainter *painter_;
};