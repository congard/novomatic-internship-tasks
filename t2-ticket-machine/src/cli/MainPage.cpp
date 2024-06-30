#include "MainPage.h"
#include "Application.h"

#include <format>

MainPage::MainPage(Application *parent)
    : Page(parent),
      m_ticketPage(this)
{
    using namespace ftxui;

    auto mkCoinBtn = [this](tmc::CoinValue value) {
        return Button(std::format("{} zł", value), [this, value] {
            m_application->ticketMachine().insertCoin(value);
        });
    };

    auto btnContinue = Button("Kontynuuj", [this] {
        m_ticketPage.show();
    });

    auto btnCancel = Button("Cofnij", [this] {
        m_application->ticketMachine().returnChange();
    });

    int row = 0;

    auto btnCoins = Container::Vertical({
        Container::Horizontal({mkCoinBtn(1), mkCoinBtn(2), mkCoinBtn(5)}, &row) | flex
    });

    auto btnCtrl = Container::Vertical({
        btnContinue | center,
        btnCancel | center
    });

    m_component = Renderer(btnCoins, [=, this] {
        return vbox({
            text("Automat Biletowy miasta Kraków") | center,
            text("Witaj!") | center,
            text(std::format("Saldo: {} zł", m_application->ticketMachine().getBalance())) | center,
            separator(),
            text("Wybierz monetę") | center,
            btnCoins->Render() | center | flex,
            separator(),
            btnCtrl->Render() | center | flex
        }) | flex | border;
    });
    m_component->Add(std::move(btnCtrl));

    enableNotificationModal();
}

void MainPage::onShow() {
    m_application->ticketMachine().setEventListener(this);
}

void MainPage::onClose() {
    m_application->ticketMachine().setEventListener(nullptr);
}

void MainPage::onChangeReturned(const tmc::ChangeCalculator::Coins &coins) {
    if (coins.empty())
        return;

    std::string content = "Monety zostały zwrócone: ";

    for (auto [coin, count] : coins)
        content += std::format("{}*{} zł, ", count, coin);

    content.erase(content.end() - 2);

    showNotification(content);
}
