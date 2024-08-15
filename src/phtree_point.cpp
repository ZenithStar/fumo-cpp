#include "phtree_point.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


PHTreePointXZ::PHTreePointXZ() {}

PHTreePointXZ::~PHTreePointXZ() {}


String PHTreePointXZ::get_phtree_name() {
	return phtree_name;
}

void PHTreePointXZ::set_phtree_name(String p_phtree_name) {
	phtree_name = p_phtree_name;
	register_to_phtree();
}

void PHTreePointXZ::register_to_phtree() {
	if ( is_inside_tree() && phtree_name != ""){
		PHTree* new_tree = Object::cast_to<PHTree>(get_tree()->get_first_node_in_group(phtree_name));
		if( new_tree != nullptr && new_tree != phtree ) {
			phtree = new_tree;
			last_position = get_position_2d();
			if ( ! phtree->insert_node( last_position, this ) ) {
				phtree = nullptr;
			}
		}
	}
}

Vector2 PHTreePointXZ::get_position_2d() {
	Vector3 pos = get_global_position();
	return {pos.x, pos.z};
}

void PHTreePointXZ::_ready( ) {
	register_to_phtree();
	//set_notify_transform(true);
	if (phtree == nullptr ){
		UtilityFunctions::print( "PHTreePointXZ failed to initialize");
		set_physics_process(false);
	}
}

void PHTreePointXZ::_exit_tree( ) {
	if (phtree != nullptr ){
		phtree->erase_node(last_position);
	}
}

// void PHTreePointXZ::_notification( int p_what ) {
// 	if ( phtree != nullptr && p_what == Node3D::NOTIFICATION_TRANSFORM_CHANGED ) {
// 		Vector2 new_position = get_position_2d();
// 		phtree->relocate_node( last_position , new_position );
// 		last_position = new_position;
// 		// UtilityFunctions::print( "PHTreePointXZ moved: ", last_position );
// 	}
// }

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
}
