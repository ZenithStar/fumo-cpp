#ifndef PHTREE_POINT_H
#define PHTREE_POINT_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "phtree.h"

namespace godot {

class PHTreePointXZ : public Node3D {
	GDCLASS(PHTreePointXZ, Node3D)

private:
    Vector2 last_position;
    String phtree_name;
    PHTree* phtree;

protected:
    void register_to_phtree();
    Vector2 get_position_2d();
	static void _bind_methods();
    //void _notification( int p_what ) ;

public:
	PHTreePointXZ();
	~PHTreePointXZ();
    String get_phtree_name();
    void set_phtree_name(String p_phtree_name);
    void _ready( ) override;
    void _exit_tree( ) override;
    void _physics_process( double delta ) override;

};
} // namespace godot

#endif // PHTREE_POINT_H