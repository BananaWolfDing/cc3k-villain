#include "gold.h"
#include "../character/player/player.h"

std::string goldName(int amount) {
  switch (amount) {
    case 1: return "small";
    case 2: return "normal";
    case 4: return "merchant hoard";
    case 6: return "dragon hoard";
    default: "unknown";
  }
}

gold::gold(int amount): item{goldName(amount), 'G'}, amount{amount} {}

int gold::getAmount() const {
  return amount;
}

void gold::use() {
  PC->addGold(amount);
}
