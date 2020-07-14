#ifndef MAP_CHANGER_H
#define MAP_CHANGER_H

#include "../include/thread.h"
#include "map_manager.h"

class MapChanger : public Thread {
   private:
    MapManager& map_manager;

   public:
    MapChanger(MapManager& map_manager);
    ~MapChanger();

    void run() override;
};

#endif  // MAP_CHANGER_H
