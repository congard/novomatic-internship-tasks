#include "TicketMachine.h"

#include <atomic>
#include <tulz/observer/USubscription.h>

namespace tmc {
TicketMachine::Balance::Subscription_t TicketMachine::addBalanceChangeListener(
    const Balance::Observer_t &listener
) {
    return m_balance.subscribe(listener);
}

CoinValue TicketMachine::getBalance() const {
    return *m_balance;
}

void TicketMachine::setEventListener(EventListener *listener) {
    m_listener = listener;
}

const std::vector<Ticket>& TicketMachine::getTickets() const {
    return m_ticketProvider->getTickets();
}

#define pushEvent(...) if (m_listener) m_listener->__VA_ARGS__

void TicketMachine::buyTicket(const Ticket &ticket) {
    if (*m_balance < ticket.price) {
        pushEvent(notEnoughBalance(ticket));
        return;
    }

    m_ticketProvider->buyTicket(ticket, [this](const TicketProvider::Result &result) {
        if (auto ticket = get_if<IssuedTicket>(&result); ticket != nullptr) {
            m_balance -= ticket->ticket.price;

            pushEvent(onTicketBought(*ticket));
            pushEvent(onPrint());

            m_ticketPrinter->print(*ticket, [this](const TicketPrinter::Result &result) {
                if (auto ticket = get_if<IssuedTicket>(&result); ticket != nullptr) {
                    pushEvent(onPrinted(*ticket));
                } else {
                    pushEvent(onPrintError(get<HardwareError>(result)));
                }
            });
        } else {
            pushEvent(onTicketFailed(get<TicketProvider::ErrorDescription>(result)));
        }

        returnChange();
    });
}

bool TicketMachine::isChangeAvailable(const Ticket &ticket) const {
    return m_changeCalculator->isAvailable(*m_balance - ticket.price, m_coinAcceptor->getCoins());
}

CoinValue TicketMachine::getAvailableChange(const Ticket &ticket) const {
    return getAvailableChange(ticket.price);
}

CoinValue TicketMachine::getAvailableChange() const {
    return getAvailableChange(0);
}

static CoinValue calcTotalValue(const ChangeCalculator::Coins &coins) {
    CoinValue total = 0;

    for (auto [coin, count] : coins)
        total += coin * count;

    return total;
}

CoinValue TicketMachine::getAvailableChange(CoinValue delta) const {
    auto coins = m_changeCalculator->calculate(*m_balance - delta, m_coinAcceptor->getCoins());
    return calcTotalValue(coins);
}

void TicketMachine::returnChange() {
    struct Details {
        CoinAcceptor::CoinSubject::Subscription_t sub;
        std::atomic<CoinValue> remainder;
        ChangeCalculator::Coins coins;
    };

    auto details = new Details();
    details->coins = m_changeCalculator->calculate(*m_balance, m_coinAcceptor->getCoins());
    details->remainder = calcTotalValue(details->coins);

    details->sub = m_coinAcceptor->addOnCoinReturnedListener([this, details](CoinValue value) {
        if ((details->remainder -= value) == 0) {
            pushEvent(onChangeReturned(details->coins));
            details->sub.unsubscribe();
            delete details;
        }
    });

    for (auto [coinVal, count] : details->coins) {
        for (size_t i = 0; i < count; ++i) {
            m_coinAcceptor->returnCoin(coinVal);
        }
    }
}

TicketMachine::TicketMachine(
    CoinAcceptorPtr coinAcceptor,
    TicketPrinterPtr ticketPrinter,
    TicketProviderPtr ticketProvider,
    ChangeCalculatorPtr changeCalculator
) : m_coinAcceptor(std::move(coinAcceptor)),
    m_ticketPrinter(std::move(ticketPrinter)),
    m_ticketProvider(std::move(ticketProvider)),
    m_changeCalculator(std::move(changeCalculator)),
    m_balance(0),
    m_listener()
{
    m_coinAcceptor->addOnCoinAcceptedListener([this](CoinValue value) {
        m_balance += value;
    });

    m_coinAcceptor->addOnCoinReturnedListener([this](CoinValue value) {
        m_balance -= value;
    });

    auto hwErrorHandler = [this](const HardwareError &error) {
        pushEvent(onHardwareError(error));
    };

    m_coinAcceptor->addOnErrorListener(hwErrorHandler);
    m_ticketPrinter->addOnErrorListener(hwErrorHandler);
}

// TODO: doc
void TicketMachine::EventListener::notEnoughBalance(const Ticket &ticket) {}
void TicketMachine::EventListener::onTicketBought(const IssuedTicket &ticket) {}
void TicketMachine::EventListener::onTicketFailed(const TicketProvider::ErrorDescription &errDesc) {}
void TicketMachine::EventListener::onPrint() {}
void TicketMachine::EventListener::onPrinted(const IssuedTicket &ticket) {}
void TicketMachine::EventListener::onPrintError(const HardwareError &error) {}
void TicketMachine::EventListener::onChangeReturned(const ChangeCalculator::Coins &coins) {}
void TicketMachine::EventListener::onHardwareError(const HardwareError &error) {}
} // tmc