#include "chase_player.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


ChasePlayer::ChasePlayer() {}

ChasePlayer::~ChasePlayer() {}

real_t ChasePlayer::get_velocity() {
	return velocity;
}

void ChasePlayer::set_velocity(real_t p_velocity) {
	velocity = p_velocity;
}

void ChasePlayer::_ready( ) {
	chase_target = Object::cast_to<Node3D>(get_tree()->get_first_node_in_group("Player"));
	control_target = Object::cast_to<Node3D>(get_parent());
	if (chase_target == nullptr || control_target == nullptr){
		UtilityFunctions::print( "ChasePlayer failed to initialize");
		set_physics_process(false);
	}
}

void ChasePlayer::_physics_process( double delta ) {
	control_target->set_global_position( control_target->get_global_position().move_toward( chase_target->get_global_position(), velocity * delta) );
}

void ChasePlayer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_velocity"), &ChasePlayer::get_velocity);
	ClassDB::bind_method(D_METHOD("set_velocity", "p_velocity"), &ChasePlayer::set_velocity);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "velocity"), "set_velocity", "get_velocity");
}
