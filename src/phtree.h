#ifndef PHTREE_H
#define PHTREE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include "phtree-cpp/include/phtree/phtree.h"

namespace godot {

class PHTree : public Node {
	GDCLASS(PHTree, Node)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	PHTree();
	~PHTree();
};

}

#endif