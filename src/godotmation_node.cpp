#include "godotmation_node.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"

GodotMation_Node::GodotMation_Node(){}

GodotMation_Node::~GodotMation_Node(){}

bool GodotMation_Node::trigger()
{
    godot::Godot::print("Node trigger");
    return true;
}

void GodotMation_Node::pull_resources(GodotMation_Resource* r){
    return;
}

void GodotMation_Node::apply_satisfaction(){
    for(auto r : input_resources){
        if (!r->used) satisfied = false;
        if (!r->satisfied || !r->used){
            for( auto s : reverse_trigger_states){
                s->end_node->trigger();
            }
            break;
        }
    }
    if (satisfied){
        for(auto r : input_resources){
            r->update_flow();
        }
    }
    pushed = false;
}

int GodotMation_Node::can_push(int value) const{
    return 0;
}



void GodotMation_Node::change_input_state(int value)
{
    return;
}

void GodotMation_Node::change_output_state(int value)
{
    return;
}

int GodotMation_Node::get_input_number() const{
    return 0;
}

int GodotMation_Node::get_output_number() const{
    return 0;
}

int GodotMation_Node::get_changed_number() const{
    return number;
}

void GodotMation_Node::apply_state(){
    return;
}

godot::Dictionary GodotMation_Node::get_dict() const{
    return godot::Dictionary();
}

