#ifndef T2_TICKET_MACHINE_TICKETMACHINE_H
#define T2_TICKET_MACHINE_TICKETMACHINE_H

#include <memory>

#include <tulz/observer/ObservableNumber.h>

#include "hardware/CoinAcceptor.h"
#include "hardware/TicketPrinter.h"
#include "provider/TicketProvider.h"
#include "algorithm/ChangeCalculator.h"

namespace tmc {
class TicketMachine {
public:
    class EventListener;

protected:
    using Balance = tulz::ObservableNumber<CoinValue>;

public:
    virtual ~TicketMachine() = default;

    Balance::Subscription_t addBalanceChangeListener(const Balance::Observer_t &listener);
    CoinValue getBalance() const;

    void setEventListener(EventListener *listener);

    const std::vector<Ticket>& getTickets() const;
    void buyTicket(const Ticket &ticket);

    bool isChangeAvailable(const Ticket &ticket) const;
    CoinValue getAvailableChange(const Ticket &ticket) const;
    CoinValue getAvailableChange() const;
    void returnChange();

protected:
    using CoinAcceptorPtr = std::unique_ptr<CoinAcceptor>;
    using TicketPrinterPtr = std::unique_ptr<TicketPrinter>;
    using TicketProviderPtr = std::unique_ptr<TicketProvider>;
    using ChangeCalculatorPtr = std::unique_ptr<ChangeCalculator>;

protected:
    TicketMachine(CoinAcceptorPtr coinAcceptor,
                  TicketPrinterPtr ticketPrinter,
                  TicketProviderPtr ticketProvider,
                  ChangeCalculatorPtr changeCalculator);

protected:
    CoinAcceptorPtr m_coinAcceptor;
    TicketPrinterPtr m_ticketPrinter;
    TicketProviderPtr m_ticketProvider;
    ChangeCalculatorPtr m_changeCalculator;

private:
    CoinValue getAvailableChange(CoinValue delta) const;

private:
    Balance m_balance;
    EventListener *m_listener;
};

class TicketMachine::EventListener {
public:
    virtual void notEnoughBalance(const Ticket &ticket);

    virtual void onTicketBought(const IssuedTicket &ticket);
    virtual void onTicketFailed(const TicketProvider::ErrorDescription &errDesc);

    virtual void onPrint();
    virtual void onPrinted(const IssuedTicket &ticket);
    virtual void onPrintError(const HardwareError &error);

    virtual void onChangeReturned(const ChangeCalculator::Coins &coins);

    virtual void onHardwareError(const HardwareError &error);
};
} // tmc

#endif //T2_TICKET_MACHINE_TICKETMACHINE_H
