// Task 3
#include <iostream>
#include <string>
#include <vector>

class Entity {
public:
    Entity() { ++entity_alive; }

    virtual ~Entity() { --entity_alive; }

    static int entity_alive;

    virtual std::string type() const { return "Entity"; }
};

int Entity::entity_alive = 0;

class Player : public Entity {
public:
    Player() { ++player_alive; }
    ~Player() override { --player_alive; }

    static int player_alive;
    std::string type() const override { return "Player"; }
};

int Player::player_alive = 0;

class Enemy : public Entity {
public:
    Enemy() { ++enemy_alive; }
    ~Enemy() override { --enemy_alive; }

    static int enemy_alive;
    std::string type() const override { return "Enemy"; }
};

int Enemy::enemy_alive = 0;

int main() {
    std::cout << "Создание объектов\n";
    {
        Player p1, p2;
        Enemy e1;
        std::cout << "Entity alive: " << Entity::entity_alive << '\n';
        std::cout << "Player alive: " << Player::player_alive << '\n';
        std::cout << "Enemy  alive: " << Enemy::enemy_alive  << '\n';
    }
    std::cout << "\nПосле выхода из блока\n";
    std::cout << "Entity alive: " << Entity::entity_alive << '\n';
    std::cout << "Player alive: " << Player::player_alive << '\n';
    std::cout << "Enemy  alive: " << Enemy::enemy_alive  << '\n';

    std::cout << "\nМассив указателей на базовый класс\n";
    std::vector<Entity*> entities;
    entities.push_back(new Player());
    entities.push_back(new Enemy());
    entities.push_back(new Player());

    std::cout << "Entity alive: " << Entity::entity_alive << '\n';

    for (Entity* e : entities) {
        delete e;
    }
    entities.clear();

    std::cout << "\nПосле удаления через базовый указатель\n";
    std::cout << "Entity alive: " << Entity::entity_alive << '\n';
    std::cout << "Player alive: " << Player::player_alive << '\n';
    std::cout << "Enemy  alive: " << Enemy::enemy_alive  << '\n';

    return 0;
}
