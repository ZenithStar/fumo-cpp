#include "ph_cluster_seperation.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


PHClusterSeperation::PHClusterSeperation() {}

PHClusterSeperation::~PHClusterSeperation() {}


String PHClusterSeperation::get_phtree_name() {
	return phtree_name;
}

void PHClusterSeperation::set_phtree_name(String p_phtree_name) {
	phtree_name = p_phtree_name;
}

real_t PHClusterSeperation::get_radius() {
	return radius;
}

void PHClusterSeperation::set_radius(real_t p_radius) {
	radius = p_radius;
}

real_t PHClusterSeperation::get_velocity_scale() {
	return velocity_scale;
}

void PHClusterSeperation::set_velocity_scale(real_t p_velocity_scale) {
	velocity_scale = p_velocity_scale;
}

Vector2 PHClusterSeperation::get_position_2d() {
	Vector3 pos = control_target->get_global_position();
	return {pos.x, pos.z};
}

void PHClusterSeperation::_ready( ) {
	phtree = Object::cast_to<PHTree>(get_tree()->get_first_node_in_group(phtree_name));
	control_target = Object::cast_to<Node3D>(get_parent());
	position_offset = Vector2(-radius, -radius);
	query_size = Vector2(2.0 * radius, 2.0 * radius);
	if (phtree == nullptr || control_target == nullptr){
		UtilityFunctions::print( "PHClusterSeperation failed to initialize");
		set_physics_process(false);
	}
}

void PHClusterSeperation::_physics_process( double delta ) {
	Rect2 query(get_position_2d() + position_offset, query_size);
	TypedArray<Node> neighbors = phtree->get_window( query );
	Vector3 control_position = control_target->get_global_position();
	Vector3 aggregate_offsets = Vector3();
	for(int i = 0; i < neighbors.size(); i++){
		Node3D* neighbor = Object::cast_to<Node3D>(neighbors[i]);
		if ( neighbor != nullptr ){
			Vector3 control_position = control_target->get_global_position();
			Vector3 offset = neighbor->get_global_position() - control_position;
			aggregate_offsets = aggregate_offsets - (offset.normalized() / std::max(offset.length_squared(), MAX_DISPLACEMENT) );
		}//aggregate_offsets = aggregate_offsets + (offset.inverse() / offset.length()) .clamp(CLAMP_MIN, CLAMP_MAX);
	}
	aggregate_offsets.y = 0.0;
	control_target->set_global_position( control_position + (aggregate_offsets * velocity_scale * delta) );
		//UtilityFunctions::print( neighbors.size(), aggregate_offsets);
}

void PHClusterSeperation::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_phtree_name"), &PHClusterSeperation::get_phtree_name);
	ClassDB::bind_method(D_METHOD("set_phtree_name", "p_phtree_name"), &PHClusterSeperation::set_phtree_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "phtree_name"), "set_phtree_name", "get_phtree_name");
	ClassDB::bind_method(D_METHOD("get_radius"), &PHClusterSeperation::get_radius);
	ClassDB::bind_method(D_METHOD("set_radius", "p_radius"), &PHClusterSeperation::set_radius);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius"), "set_radius", "get_radius");
	ClassDB::bind_method(D_METHOD("get_velocity_scale"), &PHClusterSeperation::get_velocity_scale);
	ClassDB::bind_method(D_METHOD("set_velocity_scale", "p_velocity_scale"), &PHClusterSeperation::set_velocity_scale);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "velocity_scale"), "set_velocity_scale", "get_velocity_scale");
}
