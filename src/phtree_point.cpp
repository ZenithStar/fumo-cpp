#include "phtree_point.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


PHTreePointXZ::PHTreePointXZ(): active(false), phtree(nullptr) {}

PHTreePointXZ::~PHTreePointXZ() {}


String PHTreePointXZ::get_phtree_name() {
	return phtree_name;
}

void PHTreePointXZ::set_phtree_name(String p_phtree_name) {
	phtree_name = p_phtree_name;
	if (active) register_to_phtree();
}

bool PHTreePointXZ::get_active() {
	return active;
}

void PHTreePointXZ::set_active(bool p_active) {
	if (active != p_active) {
		active = p_active;
		if (active) register_to_phtree();
		else unregister_from_phtree();
	}
}

void PHTreePointXZ::register_to_phtree() {
	if (phtree != nullptr ){
		phtree->erase_node(last_position);
		phtree = nullptr;
	}
	if ( is_inside_tree() && phtree_name != ""){
		PHTree* new_tree = Object::cast_to<PHTree>(get_tree()->get_first_node_in_group(phtree_name));
		if( new_tree != nullptr && new_tree != phtree ) {
			phtree = new_tree;
			last_position = get_position_2d();
			if ( ! phtree->insert_node( last_position, get_parent() ) ) {
				phtree = nullptr;
			}
		}
	}
	if (phtree == nullptr ){
		UtilityFunctions::print( "PHTreePointXZ failed to initialize");
		set_physics_process(false);
	}
	else{
		set_physics_process(true);
	}
}
void PHTreePointXZ::unregister_from_phtree() {
	if (phtree != nullptr ){
		phtree->erase_node(last_position);
		phtree = nullptr;
	}
	set_physics_process(false);
}

Vector2 PHTreePointXZ::get_position_2d() {
	Vector3 pos = get_global_position();
	return {pos.x, pos.z};
}

void PHTreePointXZ::_ready( ) {
	if (active) register_to_phtree();
	else set_physics_process(false);
}

void PHTreePointXZ::_exit_tree( ) {
	unregister_from_phtree();
}

void PHTreePointXZ::_physics_process( double delta ) {
	Vector2 new_position = get_position_2d();
	if ( last_position != new_position){
		if (phtree->relocate_node( last_position , new_position ) ) last_position = new_position;
	}
}

void PHTreePointXZ::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_phtree_name"), &PHTreePointXZ::get_phtree_name);
	ClassDB::bind_method(D_METHOD("set_phtree_name", "p_phtree_name"), &PHTreePointXZ::set_phtree_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "phtree_name"), "set_phtree_name", "get_phtree_name");

	ClassDB::bind_method(D_METHOD("get_active"), &PHTreePointXZ::get_active);
	ClassDB::bind_method(D_METHOD("set_active", "p_active"), &PHTreePointXZ::set_active);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "active"), "set_active", "get_active");
}
