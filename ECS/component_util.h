#ifndef COMPONENT_UTIL_H
#define COMPONENT_UTIL_H

typedef unsigned int ComponentId;

inline ComponentId getUniqueId() {
	static ComponentId id = 0;
	return id++;
}

class ComponentUtil {
   public:
	ComponentUtil();
	~ComponentUtil();
	template <class T>
	static ComponentId getTypeId() {
		static ComponentId type_id = getUniqueId(); 
		return type_id;
	}
};

#endif // COMPONENT_UTIL_H
