#ifndef T2_TICKET_MACHINE_TICKETPAGE_H
#define T2_TICKET_MACHINE_TICKETPAGE_H

#include "Page.h"
#include "DemoTicketMachine.h"

class TicketPage : public Page, public tmc::TicketMachine::EventListener {
public:
    explicit TicketPage(Page *parent);

private:
    void onShow() override;
    void onClose() override;

    void notEnoughBalance(const tmc::Ticket &ticket) override;

    void onTicketBought(const tmc::IssuedTicket &ticket) override;
    void onTicketFailed(const tmc::TicketProvider::ErrorDescription &errDesc) override;

    void onPrint() override;
    void onPrinted(const tmc::IssuedTicket &ticket) override;
    void onPrintError(const tmc::HardwareError &error) override;

    void onChangeReturned(const tmc::ChangeCalculator::Coins &coins) override;

    void onHardwareError(const tmc::HardwareError &error) override;

private:
    void buyTicket(const tmc::Ticket &ticket, bool skipChangeCheck = false);

    ftxui::Component changeCannotBeReturnedModal();
    ftxui::Component purchaseModal();

private:
    struct {
        bool isShown {false};
        const tmc::Ticket *ticket {};
    } m_changeModal;

    struct PurchaseModal {
        enum class State {
            NA, InProgress, Done, Failed
        };

        bool isShown {false};
        State purchaseState {State::InProgress};
        State printState {State::NA};
        State changeState {State::NA};

        tmc::IssuedTicket ticket;
        tmc::ChangeCalculator::Coins change;
    } m_purchaseModal;
};


#endif //T2_TICKET_MACHINE_TICKETPAGE_H
