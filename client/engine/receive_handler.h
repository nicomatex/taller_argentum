#include "../../include/th_event_handler.h"
#include "ECS/entity_manager.h"

class ClientHandler : public ThEventHandler{
    EntityManager &entity_manager;
    private:
        void handle(Event& ev) override;
    public:
        ClientHandler(EntityManager &entity_manager);
        
};