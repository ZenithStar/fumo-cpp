#ifndef PH_CLUSTER_SEPERATION
#define PH_CLUSTER_SEPERATION

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "phtree.h"

namespace godot {

class PHClusterSeperation : public Node {
	GDCLASS(PHClusterSeperation, Node)

private:
    String phtree_name;
    PHTree* phtree;
    Node3D* control_target;
    real_t radius;
    real_t velocity_scale;
    Vector2 position_offset;
    Vector2 query_size;
    const real_t MAX_DISPLACEMENT = 0.01;
    //const real_t MAX_DISPLACEMENT = 100.0;
    //const Vector3 CLAMP_MAX = Vector3(MAX_DISPLACEMENT, MAX_DISPLACEMENT, MAX_DISPLACEMENT);
    //const Vector3 CLAMP_MIN = Vector3(-MAX_DISPLACEMENT, -MAX_DISPLACEMENT, -MAX_DISPLACEMENT);


protected:
    Vector2 get_position_2d();
	static void _bind_methods();

public:
	PHClusterSeperation();
	~PHClusterSeperation();

    String get_phtree_name();
    void set_phtree_name(String p_phtree_name);

    real_t get_radius();
    void set_radius(real_t p_radius);

    real_t get_velocity_scale();
    void set_velocity_scale(real_t p_velocity_scale);

    void _ready( ) override;
    void _physics_process( double delta ) override;

};
} // namespace godot

#endif // PH_CLUSTER_SEPERATION