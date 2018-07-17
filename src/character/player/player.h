#ifndef PLAYER_H
#define PLAYER_H

class player : public character {
  int gold;
public:
  player(int hpMax, int atk, int def, std::string race, char display);
  int getGold() const;
  void setGold(int gold);
}
