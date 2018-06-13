#include "godotmation_resource.hpp"
#include "godotmation.hpp"

GodotMation_Resource::GodotMation_Resource(){}

GodotMation_Resource::~GodotMation_Resource()
{
    delete object_number;
    delete other_object_number;
}

void GodotMation_Resource::change_input_state(float value){
    object_number->add_number(value);
}

bool GodotMation_Resource::trigger()
{
    if (!active || used || !start_node->active || number <=0) return false;
    used = true;

    int flow = start_node->can_push(number);
    start_node->change_output_state(-flow);
    end_node->change_input_state(flow);
    pushed_resources += flow;
    satisfied = flow >= number;
    //godot::Godot::print(godot::String::num(number));
    return pushed_resources >= number;
}

bool GodotMation_Resource::check_flow() const {
    return pushed_resources >= number;
}

void GodotMation_Resource::update_flow(){
    pushed_resources -= number;
}

bool GodotMation_Resource::can_push_all() const{
    if (!active || used) return false;
    if (number <0) return false;
    return start_node->can_push(number) >= number;
}

void GodotMation_Resource::apply_state(){
    used = false;
    active = true;
    for(auto s : input_conditional_states){
        s->trigger();
    }
    if(active) apply_number();
}

void GodotMation_Resource::apply_number(){
    if(resource_type == 0){
        number = start_node->number;
    } else if(resource_type == 1){
        number = object_number->get_number();
        //godot::Godot::print(godot::String::num(number));
    } else if(resource_type == 2){
        int parent_ticks = parent->ticks;
        if(parent_ticks >= previous_interval + ticks){
            ticks = parent_ticks;
            previous_interval = other_object_number->get_number();
            number = object_number->get_number();
        } else{
            number = 0;
        }
    } else if(resource_type == 3){
        number = object_number->get_number() * other_object_number->get_number();
    }
}

void GodotMation_Resource::convert_label(){
    if(caption.empty()) caption = "+1";
    if(caption == "all"){
        resource_type = 0;
        return;
    }
    

    int loc = caption.find("/",0);

    if(loc > 0){
        resource_type = 2;
        object_number = GodotMation_Base_Number::from_string(caption.left(loc));
        other_object_number = GodotMation_Base_Number::from_string(caption.right(loc+1));
        previous_interval = other_object_number->get_number();
        return;
    }
    loc = caption.find("*",0);
    if(loc > 0){
        resource_type = 3;
        object_number = GodotMation_Base_Number::from_string(caption.left(loc));
        other_object_number = GodotMation_Base_Number::from_string(caption.right(loc+1));
        return;
    }
    if ( (caption[0] != '!') && (caption[0] != '=') && (caption[0] != '>') && (caption[0] != '<')){
        resource_type = 1;
        object_number = GodotMation_Base_Number::from_string(caption);
    }
	else if(caption[0] == '>'){
        resource_type = 4;
        object_number = GodotMation_Base_Number::from_string(caption.right(0));
        if(caption.length() > 1 && caption[1] == '='){
            object_number->add_number(-1);
        }
    }
	
    //object_number = GodotMation_Base_Number::from_string(caption);
    //printf("Object NUmber : %d", object_number->get_number());
    
}



