#include "hardware/DemoCoinAcceptor.h"

#include <format>

namespace tmc::demo {
size_t DemoCoinAcceptor::getCoinCount(CoinValue value) const {
    if (auto it = m_coins.find(value); it != m_coins.end())
        return it->second;
    return 0;
}

CoinAcceptor::Coins DemoCoinAcceptor::getCoins() const {
    Coins result;

    for (auto [coin, count] : m_coins)
        result.emplace_back(coin, count);

    return result;
}

void DemoCoinAcceptor::inserted(CoinValue value) {
    ++m_coins.try_emplace(value, 0).first->second;
    coinAccepted(value);
}

void DemoCoinAcceptor::returnCoin(CoinValue value) {
    if (auto it = m_coins.find(value); it != m_coins.end()) {
        --it->second;
        coinReturned(value);
    } else {
        error(HardwareError {
            .id = 0,
            .deviceId = 0x01, // just some random id
            .description = std::format("Coin count mismatch: coin of value {} cannot be returned", value)
        });
    }
}
}