#include "Page.h"
#include "Application.h"

Page::Page(Application *parent)
    : m_application(parent),
      m_parent() {}

Page::Page(Page *parent)
    : m_application(parent->m_application),
      m_parent(parent) {}

void Page::show() {
    if (m_parent != nullptr)
        m_parent->onClose();
    onShow();
    m_application->screen().Loop(m_component);
}

void Page::close() {
    onClose();
    if (m_parent != nullptr)
        m_parent->onShow();
    m_application->screen().Exit();
}

void Page::onShow() {
    // empty
}

void Page::onClose() {
    // empty
}

ftxui::Component Page::notificationModal() {
    using namespace ftxui;

    auto component = Container::Vertical({
        Button("Ok", [this] {
            m_notification.isShown = false;
        }),
    });

    component |= Renderer([this](const Element &inner) {
        return vbox({
            text("Powiadomienie") | center,
            separator(),
            text(m_notification.content) | center,
            inner | center,
        }) | size(WIDTH, GREATER_THAN, 30) | border;
    });

    return component;
}

void Page::showNotification(std::string_view content) {
    m_notification.content = content;
    m_notification.isShown = true;
}

void Page::enableNotificationModal() {
    m_component |= ftxui::Modal(notificationModal(), &m_notification.isShown);
}
