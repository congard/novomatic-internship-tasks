#ifndef T3_COLLISION_DETECTION_VISUALIZERWIDGET_H
#define T3_COLLISION_DETECTION_VISUALIZERWIDGET_H

#include <algine/core/widgets/Widget.h>
#include <tulz/observer/Subject.h>

#include "CollisionDetector/triangle.h"

using namespace algine;

namespace UI {
class VisualizerWidget : public Widget {
    STATIC_INITIALIZER_DECL

public:
    enum class Mode {
        None,
        Add,
        Remove
    };

    using ModeSubject = tulz::Subject<Mode>;

public:
    VisualizerWidget();

    void enterAddMode();
    void enterRemoveMode();

    Mode getMode() const;

    ModeSubject::Subscription_t addOnModeChangedListener(const ModeSubject::Observer_t &listener);

private:
    void onDraw(algine::Painter &painter) override;

    void setMode(Mode mode);

    void addPoint(const cd::vec2 &p);
    void removeTriangle(const cd::vec2 &p);

    void calcCollisions();

private:
    std::vector<Color> m_colors;
    int m_colorIndex;

private:
    std::vector<std::pair<cd::triangle, Color>> m_triangles;
    std::vector<cd::vec2> m_tmpPoints;
    Mode m_mode;

    int m_pressedTriangleIndex;
    cd::vec2 m_prevCoords;

    // contains bounding boxes of collisions
    std::vector<RectF> m_collisions;

    ModeSubject m_onModeChanged;

private:
    decltype(m_triangles)::iterator findTriangleAt(const cd::vec2 &p);
};
} // UI

#endif //T3_COLLISION_DETECTION_VISUALIZERWIDGET_H
