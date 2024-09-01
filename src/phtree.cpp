#include "phtree.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


PHTree::PHTree(): converter(), tree(converter) {}

PHTree::~PHTree() {}

void PHTree::_ready( ) {
	Node::add_to_group(get_name());
}

bool PHTree::insert_node( Vector2 p_position, Node* p_node ) {
	return tree.insert( p_position, p_node ).second;
}

bool PHTree::relocate_node( Vector2 p_old_position, Vector2 p_new_position) {
	return tree.relocate( p_old_position, p_new_position );
}

bool PHTree::erase_node( Vector2 p_position) {
	return tree.erase( p_position );
}

Node* PHTree::get_nearest( Vector2 p_position ){
	auto it = tree.begin_knn_query(1, p_position, improbable::phtree::DistanceEuclideanGD());
	if (it != tree.end())	return *it;
	else return nullptr;
}

TypedArray<Node> PHTree::get_k_nearest(int p_k, Vector2 p_position ){
	TypedArray<Node> output = new TypedArray<Node>();
	for (auto it = tree.begin_knn_query(p_k, p_position, improbable::phtree::DistanceEuclideanGD()); it != tree.end(); ++it){
		output.push_back(*it);
	}
	return output;
}

TypedArray<Node> PHTree::get_window(Rect2 p_box ){
	TypedArray<Node> output = new TypedArray<Node>();
	for (auto it = tree.begin_query( p_box ); it != tree.end(); ++it){
		output.push_back(*it);
	}
	return output;
}

TypedArray<Node> PHTree::get_radius( Vector2 p_position, real_t p_radius ){
	TypedArray<Node> output = new TypedArray<Node>();
	Rect2 p_box(p_position - p_radius*Vector2(1.0,1.0), p_radius*Vector2(2.0,2.0));
	for (auto it = tree.begin_query( p_box , 
			improbable::phtree::FilterSphereGD(
				p_position, p_radius, 
				improbable::phtree::ConverterGD2(), 
				improbable::phtree::DistanceEuclideanGD()
				)
			); it != tree.end(); ++it){
		output.push_back(*it);
	}
	return output;
}

void PHTree::_bind_methods() {
	ClassDB::bind_method(D_METHOD("insert_node", "position", "node"), &PHTree::insert_node);
	ClassDB::bind_method(D_METHOD("relocate_node", "old_position", "new_position"), &PHTree::relocate_node);
	ClassDB::bind_method(D_METHOD("erase_node", "position"), &PHTree::erase_node);
	ClassDB::bind_method(D_METHOD("get_nearest", "position"), &PHTree::get_nearest);
	ClassDB::bind_method(D_METHOD("get_k_nearest", "k", "position"), &PHTree::get_k_nearest);
	ClassDB::bind_method(D_METHOD("get_window", "box"), &PHTree::get_window);
	ClassDB::bind_method(D_METHOD("get_radius", "position", "radius"), &PHTree::get_radius);
}