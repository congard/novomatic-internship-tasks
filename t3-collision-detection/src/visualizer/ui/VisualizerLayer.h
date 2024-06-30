#ifndef CD_VISUALIZER_VISUALIZERLAYER_H
#define CD_VISUALIZER_VISUALIZERLAYER_H

#include <algine/core/widgets/Layer.h>

using namespace algine;

namespace UI {
class VisualizerLayer: public Widgets::Layer {
public:
    explicit VisualizerLayer(Widgets::Scene *parent);
};
}// namespace UI

#endif//CD_VISUALIZER_VISUALIZERLAYER_H
