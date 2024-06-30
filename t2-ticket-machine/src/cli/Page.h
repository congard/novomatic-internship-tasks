#ifndef T2_TICKET_MACHINE_PAGE_H
#define T2_TICKET_MACHINE_PAGE_H

#include "ftxui/component/component.hpp"

class Application;

class Page {
public:
    void show();
    void close();

protected:
    explicit Page(Application *parent);
    explicit Page(Page *parent);

    virtual void onShow();
    virtual void onClose();

    ftxui::Component notificationModal();
    void showNotification(std::string_view content);
    void enableNotificationModal();

protected:
    ftxui::Component m_component;
    Application *const m_application;
    Page *const m_parent;

private:
    struct {
        std::string content;
        bool isShown {false};
    } m_notification;
};

#endif //T2_TICKET_MACHINE_PAGE_H
