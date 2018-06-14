#include "godotmation_base_node.hpp"


GodotMation_Base_Node::GodotMation_Base_Node(){}

GodotMation_Base_Node::~GodotMation_Base_Node(){}


void GodotMation_Base_Node::_register_methods()
{
    godot::register_property((char *)"GodotMation/type", &GodotMation_Base_Node::type, int(0));

    godot::register_method("trigger", &GodotMation_Base_Node::trigger);

    godot::register_method("get_type", &GodotMation_Base_Node::get_type);

    godot::register_method("get_caption", &GodotMation_Base_Node::get_caption);
    godot::register_method("set_caption", &GodotMation_Base_Node::set_caption);

    godot::register_method("get_number", &GodotMation_Base_Node::get_number);
    godot::register_method("set_number", &GodotMation_Base_Node::set_number);

    godot::register_method("get_activation_mode", &GodotMation_Base_Node::get_activation_mode);
    godot::register_method("set_activation_mode", &GodotMation_Base_Node::set_activation_mode);

    godot::register_method("get_pull_mode", &GodotMation_Base_Node::get_pull_mode);
    godot::register_method("set_pull_mode", &GodotMation_Base_Node::set_pull_mode);

    godot::register_method("get_color", &GodotMation_Base_Node::get_color);
    godot::register_method("set_color", &GodotMation_Base_Node::set_color);

    godot::register_method("get_actions", &GodotMation_Base_Node::get_actions);
    godot::register_method("set_actions", &GodotMation_Base_Node::set_actions);

    godot::register_method("get_capacity", &GodotMation_Base_Node::get_capacity);
    godot::register_method("set_capacity", &GodotMation_Base_Node::set_capacity);

    godot::register_method("get_starting_resources", &GodotMation_Base_Node::get_starting_resources);
    godot::register_method("set_starting_resources", &GodotMation_Base_Node::set_starting_resources);

    godot::register_method("get_x", &GodotMation_Base_Node::get_x);
    godot::register_method("set_x", &GodotMation_Base_Node::set_x);

    godot::register_method("get_y", &GodotMation_Base_Node::get_y);
    godot::register_method("set_y", &GodotMation_Base_Node::set_y);

    godot::register_method("get_start", &GodotMation_Base_Node::get_start);
    godot::register_method("set_start", &GodotMation_Base_Node::set_start);

    godot::register_method("get_end", &GodotMation_Base_Node::get_end);
    godot::register_method("set_end", &GodotMation_Base_Node::set_end);

    godot::register_method("get_emit_state_changed", &GodotMation_Base_Node::get_emit_state_changed);
    godot::register_method("set_emit_state_changed", &GodotMation_Base_Node::set_emit_state_changed);

}


int GodotMation_Base_Node::get_type() const{
    return node->type;
}

void GodotMation_Base_Node::trigger()
{
   bool tmp = node->trigger();
}

godot::String GodotMation_Base_Node::get_caption() const{
    return node->caption;
}

void GodotMation_Base_Node::set_caption(godot::String value){
    node->caption = value;
}

int GodotMation_Base_Node::get_number() const{
    return node->number;
}

void GodotMation_Base_Node::set_number(int value){
    node->number = value;
}

int GodotMation_Base_Node::get_activation_mode() const{
    return node->activation_mode;
}

void GodotMation_Base_Node::set_activation_mode(int value){
    node->activation_mode = value;
}

int GodotMation_Base_Node::get_pull_mode() const{
    return node->pull_mode;
}

void GodotMation_Base_Node::set_pull_mode(int value){
    node->pull_mode = value;
}

int GodotMation_Base_Node::get_color() const{
    return node->color;
}

void GodotMation_Base_Node::set_color(int value){
    node->color = value;
}

int GodotMation_Base_Node::get_actions() const{
    return node->actions;
}

void GodotMation_Base_Node::set_actions(int value){
    node->actions = value;
}

int GodotMation_Base_Node::get_capacity() const{
    return node->capacity;
}

void GodotMation_Base_Node::set_capacity(int value){
    node->capacity = value;
}

int GodotMation_Base_Node::get_starting_resources() const {
    return node->starting_resources;
}

void GodotMation_Base_Node::set_starting_resources(int value){
    node->starting_resources = value;
}

float GodotMation_Base_Node::get_x() const{
    return node->x;
}
void GodotMation_Base_Node::set_x(float value){
    node->x = value;
}

float GodotMation_Base_Node::get_y() const{
    return node->y;
}
void GodotMation_Base_Node::set_y(float value){
    node->y = value;
}

int GodotMation_Base_Node::get_start() const{
    return node->start;
}
void GodotMation_Base_Node::set_start(int value){
    node->start = value;
}

int GodotMation_Base_Node::get_end() const{
    return node->end;
}
void GodotMation_Base_Node::set_end(int value){
    node->end = value;
}

bool GodotMation_Base_Node::get_emit_state_changed() const{
    return node->emit_state_changed;
}
void GodotMation_Base_Node::set_emit_state_changed(bool value) {
    node->emit_state_changed = value;
}
