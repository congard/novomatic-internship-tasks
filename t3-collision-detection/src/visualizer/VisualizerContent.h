#ifndef CD_VISUALIZER_VISUALIZERCONTENT_H
#define CD_VISUALIZER_VISUALIZERCONTENT_H

#include <algine/core/unified/UnifiedEventHandler.h>
#include <algine/core/Content.h>

using namespace algine;

namespace UI {
class VisualizerScene;
}

class VisualizerContent: public Content, public UnifiedEventHandler {
public:
    explicit VisualizerContent(Object *parent);

    void onShow() override;
    void render() override;

private:
    UI::VisualizerScene *m_scene;
};

#endif//CD_VISUALIZER_VISUALIZERCONTENT_H
