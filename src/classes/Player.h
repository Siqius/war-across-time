#ifndef PLAYER_H
#define PLAYER_H



class Player {
    int _coins = 0;
    int _stage = 1;
    int _health;
public:
    Player();

    int coins() const;
    void add_coins(int value);
    void remove_coins(int value);

    int stage() const;
    void next_stage();

    int health() const;
    void set_health(int value);
    void remove_health(int value);
};



#endif //PLAYER_H
