CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = cc3k
OBJECTS = src/cell.o src/chamber.o src/character.o src/findChamber.o src/floor.o src/item.o src/main.o src/potion.o src/readMap.o src/item/gold.o src/item/potions/boostAttack.o src/item/potions/boostDefence.o src/item/potions/poisonHealth.o src/item/potions/restoreHealth.o src/item/potions/woundAttack.o src/item/potions/woundDefence.o src/character/enemy/dragon.o src/character/enemy/dwarf.o src/character/enemy/elf.o src/character/enemy/enemy.o src/character/enemy/halfling.o src/character/enemy/human.o src/character/enemy/merchant.o src/character/enemy/orc.o src/character/player/drow.o src/character/player/goblin.o src/character/player/player.o src/character/player/shade.o src/character/player/troll.o src/character/player/vampire.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
