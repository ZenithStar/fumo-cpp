#ifndef CHASE_PLAYER_H
#define CHASE_PLAYER_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


namespace godot {

class ChasePlayer : public Node {
	GDCLASS(ChasePlayer, Node)

private:
    Node3D* chase_target;
    Node3D* control_target;
    real_t velocity;


protected:
	static void _bind_methods();

public:
	ChasePlayer();
	~ChasePlayer();

    real_t get_velocity();
    void set_velocity(real_t p_velocity_scale);

    void _ready( ) override;
    void _physics_process( double delta ) override;

};
} // namespace godot

#endif // CHASE_PLAYER_H