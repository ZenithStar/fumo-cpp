#include "phtree.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void PHTree::_bind_methods() {
}

PHTree::PHTree() {
	// Initialize any variables here.
}

PHTree::~PHTree() {
	// Add your cleanup here.
}

bool PHTree::insert_node(Vector2 position, Node node){
	return tree.insert({ position.x, position.y }, node).second;
}

bool PHTree::relocate_node(Vector2 old_position, Vector2 new_position, Node node){
	// validate
	return tree.relocate({ old_position.x, old_position.y }, { new_position.x, new_position.y });
}

bool PHTree::erase_node(Vector2 position, Node node){
	// validate
	return tree.erase({ position.x, position.y });
}

