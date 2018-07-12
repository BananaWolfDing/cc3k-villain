#ifndef VAMPIRE_H
#define VAMPIRE_H

class vampire : public player {
public:
  vampire();
  void addHp(int inc) override;
};

#endif
