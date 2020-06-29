#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class GameManager {
   private:
    GameManager();

   public:
    GameManager& get_instance();
    ~GameManager();
};

#endif  // GAME_MANAGER_H
