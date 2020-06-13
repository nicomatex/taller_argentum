#include "th_observer.h"

ThObserver::ThObserver(Map& map, ThEventHandler& handler)
: Thread(), map(map), handler(handler) {}

void ThObserver::run() {
	/*
	while (running) {
		std::unordered_map<unsigned int, position_t> u_map = map.get_position_map();
		json json_update;
		json_update["ev_id"] = 1;
		json_update["entities"] = u_map;
		handler.push(Event(json_update));
	}

	typedef struct position { <--- definido en Map
    	unsigned int x;
    	unsigned int y;
	} position_t;

	void to_json(json& j, const position& p) {
    	j["pos"] = {p.x, p.y};
	}

	void from_json(const json& j, position& p) {
    	j.at("pos")[0].get_to(p.x);
    	j.at("pos")[1].get_to(p.y);
	}

	Those methods MUST be in your type's namespace
	(which can be the global namespace), or the library will not be able
	to locate them (namespace/header).

	Those methods MUST be available (e.g., proper headers must be included)
	everywhere you use these conversions.

	Ejemplo con 2 entidades:
	{"entities":[[5,{"pos":[100,90]}],[1,{"pos":[20,20]}]],"ev_id":1}

	*/
}

ThObserver::~ThObserver() {}


