#include "TicketPage.h"

#include <utility>
#include "Application.h"

TicketPage::TicketPage(Page *parent)
    : Page(parent)
{
    using namespace ftxui;

    auto mkTicketContainer = [this](const tmc::Ticket &ticket) {
        return Container::Vertical({
            Button("Kup", [this, ticket] {
                buyTicket(ticket);
            }) | center | Renderer([ticket](const Element &inner) {
                return vbox({
                    text(ticket.category == tmc::Ticket::Category::Normal ? "Normalny" : "Ulgowy") | center,
                    text(std::format("{} zł", ticket.price)) | center,
                    text(std::format("{} minutowy", ticket.timeMinutes)),
                    inner
                }) | border;
            })
        });
    };

    std::vector<Component> tickets;

    for (auto &ticket : m_application->ticketMachine().getTickets())
        tickets.emplace_back(mkTicketContainer(ticket));

    auto btnReturn = Button("Wróć", [this] {
        close();
    });

    m_component = Renderer([=, this] {
        std::vector<Element> elements;
        elements.reserve(tickets.size());

        for (auto &ticket : tickets)
            elements.emplace_back(ticket->Render() | center);

        return vbox({
            text("Wybierz bilet") | center,
            text(std::format("Saldo: {}", m_application->ticketMachine().getBalance())) | center,
            separator(),
            hbox(elements),
            separator(),
            btnReturn->Render() | center
        }) | flex | border;
    });

    m_component->Add(std::move(btnReturn));

    for (auto &comp : tickets)
        m_component->Add(std::move(comp));

    enableNotificationModal();

    m_component |= Modal(changeCannotBeReturnedModal(), &m_changeModal.isShown);
    m_component |= Modal(purchaseModal(), &m_purchaseModal.isShown);
}

void TicketPage::onShow() {
    m_application->ticketMachine().setEventListener(this);
}

void TicketPage::onClose() {
    m_application->ticketMachine().setEventListener(nullptr);
}

void TicketPage::notEnoughBalance(const tmc::Ticket &ticket) {
    m_purchaseModal = {};
    auto balance = m_application->ticketMachine().getBalance();
    showNotification(std::format("Brak środków: wrzuć jeszcze {} zł", ticket.price - balance));
}

void TicketPage::onTicketBought(const tmc::IssuedTicket &ticket) {
    m_purchaseModal.ticket = ticket;
    m_purchaseModal.purchaseState = PurchaseModal::State::Done;
}

void TicketPage::onTicketFailed(const tmc::TicketProvider::ErrorDescription &errDesc) {
    m_purchaseModal = {};
    showNotification("Wystąpił błąd podczas zakupu: " + errDesc);
}

void TicketPage::onPrint() {
    m_purchaseModal.printState = PurchaseModal::State::InProgress;
}

void TicketPage::onPrinted(const tmc::IssuedTicket &ticket) {
    m_purchaseModal.printState = PurchaseModal::State::Done;
}

void TicketPage::onPrintError(const tmc::HardwareError &error) {
    m_purchaseModal.printState = PurchaseModal::State::Failed;
    onHardwareError(error);
}

void TicketPage::onChangeReturned(const tmc::ChangeCalculator::Coins &coins) {
    m_purchaseModal.changeState = PurchaseModal::State::Done;
    m_purchaseModal.change = coins;
}

void TicketPage::onHardwareError(const tmc::HardwareError &error) {
    showNotification(std::format(
            "HWErr: id={}, devId={}, desc='{}'",
            error.id, error.deviceId, error.description));
}

void TicketPage::buyTicket(const tmc::Ticket &ticket, bool skipChangeCheck) {
    auto &machine = m_application->ticketMachine();

    if (!skipChangeCheck && ticket.price <= machine.getBalance() && !machine.isChangeAvailable(ticket)) {
        m_changeModal.ticket = &ticket;
        m_changeModal.isShown = true;
        return;
    }

    m_purchaseModal.isShown = true;

    machine.buyTicket(ticket);
}

ftxui::Component TicketPage::changeCannotBeReturnedModal() {
    using namespace ftxui;

    auto component = Container::Vertical({
        Button("Tak", [this] {
            buyTicket(*m_changeModal.ticket, true);
            m_changeModal.isShown = false;
        }),
        Button("Nie", [this] {
            m_changeModal.isShown = false;
        }),
    });

    component |= Renderer([](const Element &inner) {
        return vbox({
            text("Uwaga") | center,
            separator(),
            text("Brak monet w automacie. Automat nie wyda całej reszty.") | center,
            text("Kontynuować?") | center,
            separator(),
            inner | center,
        }) | size(WIDTH, GREATER_THAN, 30) | border;
    });

    return component;
}

ftxui::Component TicketPage::purchaseModal() {
    using namespace ftxui;

    auto component = Container::Vertical({
        Button("Zakończ", [this] {
            m_purchaseModal = {};
            close();
        })
    });

    component |= Renderer([this](const Element &inner) {
        std::vector<Element> elements {
            text("Zakup biletu") | center,
            separator()
        };

        switch (m_purchaseModal.purchaseState) {
            case PurchaseModal::State::InProgress:
                elements.emplace_back(text("Zakup biletu... Proszę czekać") | center);
                break;
            case PurchaseModal::State::Done:
                elements.emplace_back(text("Bilet został zakupiony: " + m_purchaseModal.ticket.id) | center);

                switch (m_purchaseModal.printState) {
                    case PurchaseModal::State::NA:
                        elements.emplace_back(text("Czekam na drukarkę...") | center);
                        break;
                    case PurchaseModal::State::InProgress:
                        elements.emplace_back(text("Drukowanie biletu...") | center);
                        break;
                    case PurchaseModal::State::Done:
                        elements.emplace_back(text("Bilet został wydrukowany") | center);
                        break;
                    case PurchaseModal::State::Failed:
                        elements.emplace_back(text("Wystąpił błąd podczas drukowania biletu") | center);
                        break;
                }

                switch (m_purchaseModal.changeState) {
                    case PurchaseModal::State::Done: {
                        if (m_purchaseModal.change.empty())
                            break;

                        std::string content;
                        for (auto [coin, count] : m_purchaseModal.change)
                            content += std::format("{}*{} zł, ", count, coin);
                        content.erase(content.end() - 2);

                        elements.emplace_back(text("Twoja reszta: " + content) | center);

                        break;
                    }
                    default:
                        break;
                }
                break;
            case PurchaseModal::State::Failed:
            case PurchaseModal::State::NA:
                elements.emplace_back(text("Wystąpił błąd") | center);
                break;
        }

        elements.emplace_back(separator());
        elements.emplace_back(inner | center);

        return vbox(elements) | size(WIDTH, GREATER_THAN, 30) | border;
    });

    return component;
}
