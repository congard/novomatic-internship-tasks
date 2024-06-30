#ifndef T2_TICKET_MACHINE_MAINPAGE_H
#define T2_TICKET_MACHINE_MAINPAGE_H

#include "Page.h"
#include "DemoTicketMachine.h"
#include "TicketPage.h"

class MainPage : public Page, public tmc::TicketMachine::EventListener {
public:
    explicit MainPage(Application *parent);

private:
    void onShow() override;
    void onClose() override;

    void onChangeReturned(const tmc::ChangeCalculator::Coins &coins) override;

private:
    TicketPage m_ticketPage;
};

#endif //T2_TICKET_MACHINE_MAINPAGE_H
