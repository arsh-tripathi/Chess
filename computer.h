#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "enums.h"
#include "player.h"
#include "tree.h"

class LevelOne : public Player {
   public:
	LevelOne(Colour c);
	bool move() override;
	void resign() override;
};

class LevelTwo : public Player {
   public:
	LevelTwo(Colour c);
	bool move() override;
	void resign() override;
};

class LevelThree : public Player {
   public:
	LevelThree(Colour c);
	bool move() override;
	void resign() override;
};

// class LevelFour : public Player {
//   public:
//	LevelFour(Colour c);
//	bool move() override;
//	void resign() override;
//};

#endif
