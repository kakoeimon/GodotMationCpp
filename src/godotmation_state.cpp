#include "godotmation_state.hpp"
#include "godotmation_resource.hpp"

GodotMation_State::GodotMation_State(){};

GodotMation_State::~GodotMation_State(){};

bool GodotMation_State::trigger()
{
    return trigger(0);
}

bool GodotMation_State::trigger(int value)
{
    if(!active || state_type > 8) return false;
    switch(state_type){
        case 0: //Normal flow
            end_node->change_input_state(state_number * value);
            break;
        case 1: //Change Interval
            //Cause it is a change in interval this means that we deal with resource connection
            if( GodotMation_Resource *resource = dynamic_cast<GodotMation_Resource*>(end_node)){
                resource->other_object_number->add_number(state_number * value);
            }
            break;
        case 2: //Change moultiplier
            if( GodotMation_Resource *resource = dynamic_cast<GodotMation_Resource*>(end_node)){
                resource->other_object_number->add_number(state_number * value);
            }
            break;
        case 3: //Change percentage
            if( GodotMation_Resource *resource = dynamic_cast<GodotMation_Resource*>(end_node)){
                resource->other_object_number->add_number(state_number * value * 0.01f);
            }
            break;
        case 4: //Range
            if(int(state_number) > start_node->get_changed_number() && start_node->get_changed_number() < other_number){
                end_node->active = false;
            }
            break;
        case 5: //Higher
            if(number >= start_node->get_changed_number()) end_node->active = false;
            break;
        case 6: //Lower
            if(number <= start_node->get_changed_number()) end_node->active = false;
            break;
        case 7: //Equal
            if(number != start_node->get_changed_number()) end_node->active = false;
            break;
        case 8: //Unequal
            if(number == start_node->get_changed_number()) end_node->active = false;
            break;
        
    }


    return true;
}

void GodotMation_State::change_input_state(int value){
    number += value;
}

void GodotMation_State::change_output_state(int value){
    number += value;
}


void GodotMation_State::apply_state(){
    active = true;
}

void GodotMation_State::convert_label(){
    if(caption.empty()){
        caption = "+1";
        state_number = 1.0f;
        return;
    }
    caption = caption.replace(" ", "");
    get_label_data(caption);
    
}

void GodotMation_State::get_label_data(godot::String in_label){
    int length = in_label.length();
    int i = 0;
    if(length){
        if(in_label[i] == '+' || in_label[i] == '-' || isdigit(in_label[i])){
            godot::String number_string = "";
            state_type = 0;
            if(in_label[0] == '+' || in_label[0] == '-'){
                i++;
                number_string += godot::String(in_label[0]);
            } 

            while(i < length && isdigit(in_label[i])){
                number_string += godot::String(in_label[i]);
                i++;
            }
            state_number = number_string.to_float();
            if(i < length){
                if(in_label[i] == '.'){
                    i++;
                    number_string += godot::String('.');
                }
                while(i < length && isdigit(in_label[i])){
                    i++;
                    number_string += godot::String(in_label[i]);
                }
                state_number = number_string.to_float();
            }
            if(i < length){
                switch(in_label[i]){
                    case 'i':
                        state_type = 1;
                        break;
                    case 'm':
                        state_type = 2;
                        break;
                    case '%':
                        state_type = 3;
                        break;
                    case '-':
                        state_type = 4; //Range
                        godot::String new_number_string = "";
                        i++;
                        while(i<length && isdigit(in_label[i])){
                            new_number_string += godot::String(in_label[i]);
                            i++;
                        }
                        if(!new_number_string.empty()){
                            other_number = new_number_string.to_int();
                        }
                        break;
                }
            }
        } else if(in_label[0] == '>'){
            i++;
            bool e = false;
            state_type = 5;
            if( i < length && in_label[i] == '='){
                i++;
                e = true;
            }
            godot::String number_string = "";
            while(i < length && isdigit(in_label[i])){
                number_string += godot::String(in_label[i]);
                i++;
            }
            
            if(!number_string.empty()){
                number = number_string.to_int();
            } else {
                number = 1;
            }
            
            if(e) number -=1;
        } else if(in_label[0] == '<'){
            i++;
            bool e = false;
            state_type = 6;
            if( i < length && in_label[i] == '='){
                i++;
                e = true;
            }
            godot::String number_string = "";
            while(i < length && isdigit(in_label[i])){
                number_string += godot::String(in_label[i]);
                i++;
            }
            if(!number_string.empty()){
                number = number_string.to_float();
            } else {
                number = 1;
            }
            if(e) number +=1;
        } else if(in_label[0] == '=' && length > 1 && in_label[1] == '='){
            state_type = 7;
            i +=2;
            godot::String number_string = "";
            while(i < length && isdigit(in_label[i])){
                number_string += godot::String(in_label[i]);
                i++;
            }
            if(!number_string.empty()){
                number = number_string.to_int();
            } else{
                number = 1;
            }
        } else if(in_label[0] == '!' && length > 1 && in_label[1] == '='){
            state_type = 8;
            i +=2;
            godot::String number_string = "";
            while(i < length && isdigit(in_label[i])){
                number_string += godot::String(in_label[i]);
                i++;
            }
            if(!number_string.empty()){
                number = number_string.to_int();
            } else{
                number = 1;
            }
        } else if(in_label[0] == '*' && length == 1){
            state_type = 9;
        } else if(in_label[0] == '!' && length == 1){
            state_type = 10;
        }
    }

}