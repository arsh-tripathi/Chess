#include "human.h"

using namespace std;

Human::Human(Colour c) : Player{c} {}

bool Human::move() {

    return true;
}

void Human::resign() {
    b->status = State::Resign;
}
