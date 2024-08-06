#ifndef PHTREE_H
#define PHTREE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <phtree/phtree.h>

namespace godot {

class PHTree : public Node {
	GDCLASS(PHTree, Node)

private:
	improbable::phtree::PhTreeD<2, Node> tree = improbable::phtree::PhTreeD<2, Node>();

protected:
	static void _bind_methods();

public:
	PHTree();
	~PHTree();
	bool insert_node(Vector2 position, Node node);
	bool relocate_node(Vector2 old_position, Vector2 new_position, Node node);
	bool erase_node(Vector2 position, Node node);

};


}
/* doesn't work. figure out how to define an implicit conversion
improbable::phtree::PhPointD<2> (const godot::Vector2& vec) { 
	return { vec.x, vec.y }; 
};
*/
#endif