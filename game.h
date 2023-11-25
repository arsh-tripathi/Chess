

class Game {

    // Fields
    Player* p1;
    Player* p2;
    Board* b;

    public:
    Game();
    Game(Player* p1, Player* p2, Board* b);

    void startGame(); // starts the game (after initialization of piecse)
    void initDefaultGame(); // setup normal pieces by placing on board
    void setPlayer1(Player *p1);
    void setPlyaer2(Player* p2);  

}