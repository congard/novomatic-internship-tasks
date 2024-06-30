#ifndef TMC_DEMO_DEMOCOINACCEPTOR_H
#define TMC_DEMO_DEMOCOINACCEPTOR_H

#include <unordered_map>

#include "hardware/CoinAcceptor.h"

namespace tmc::demo {
class DemoCoinAcceptor : public CoinAcceptor {
public:
    size_t getCoinCount(CoinValue value) const override;
    Coins getCoins() const override;

    void inserted(CoinValue value) override;
    void returnCoin(CoinValue value) override;

private:
    std::unordered_map<CoinValue, size_t> m_coins;
};
}

#endif //TMC_DEMO_DEMOCOINACCEPTOR_H
