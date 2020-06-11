#ifndef COMPONENT_UTIL_H
#define COMPONENT_UTIL_H

typedef unsigned int ComponentId;

inline ComponentId get_unique_id() {
	static ComponentId id = 0;
	return id++;
}

class ComponentUtil {
   public:
	ComponentUtil();
	~ComponentUtil();
	template <class T>
	static ComponentId get_type_id() {
		static ComponentId type_id = get_unique_id(); 
		return type_id;
	}
};

#endif // COMPONENT_UTIL_H
