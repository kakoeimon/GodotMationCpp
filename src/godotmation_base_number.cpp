#include "godotmation_base_number.hpp"
#include "godotmation_number.hpp"
#include "godotmation_dice.hpp"

GodotMation_Base_Number::GodotMation_Base_Number(){};

GodotMation_Base_Number::~GodotMation_Base_Number()
{
    delete other_object_number;
}


int GodotMation_Base_Number::get_number() const {
    return 0;
}

void GodotMation_Base_Number::add_number(float) {
    return;
}

void GodotMation_Base_Number::set_from_string(godot::String value) {
    return;
}


GodotMation_Base_Number* GodotMation_Base_Number::from_string(godot::String value){
    godot::String label = value.replace(" ", "");
    int length = label.length();
    if (length) {
        if ( (label[0] != '+') && (label[0] != '-') && (label[0] != '!') && (label[0] != '=') && (label[0] != '>') && (label[0] != '<') ){
            godot::String r = "+" + label;
            return GodotMation_Base_Number::read_string(r);
        } else{
            return GodotMation_Base_Number::read_string(label);
        }
    } else {
        godot::String r = "+1";
        return GodotMation_Base_Number::read_string(r);
    }
}


GodotMation_Base_Number* GodotMation_Base_Number::read_string(godot::String value){
    int length = value.length();
    int i = 0;
    godot::String number_string = "";
    if (length){
        if (value[i] == '+'){
            number_string += "+";
            i++;
        } else if (value[i] == '-'){
            number_string += "-";
            i++;
        }
        if (std::isdigit(value[i])){
            while( (i < length) && ((std::isdigit(value[i]) || value[i] == '.') ) ){
                number_string += godot::String(value[i]);
                i++;
            }
            if (i < length){
                if (value[i] == '%'){
                    i++;
                    float tmp_val = number_string.to_float() * 0.01f;
                    GodotMation_Number *r = new GodotMation_Number();
                    r->type = 1;
                    r->set_from_string(godot::String::num(tmp_val));
                    if (i < length) {
                        r->other_object_number = GodotMation_Base_Number::read_string(value.right(i));
                    }
                    return r;
                } else if (value[i] == 'D'){
                    i++;
                    number_string +=godot::String("D");
                    if(i < length){
                        while( (i < length) && ((std::isdigit(value[i]) || value[i] == '.') ) ){
                            number_string += godot::String(value[i]);
                            i++;
                        }
                        GodotMation_Dice *r = new GodotMation_Dice();
                        r->set_from_string(number_string);
                        if (i < length) {
                            r->other_object_number = GodotMation_Base_Number::read_string(value.right(i));
                        }
                        return r;
                    }
                } else {
                    GodotMation_Number *r = new GodotMation_Number();
                    r->set_from_string(number_string);
                    if (i < length) {
                        r->other_object_number = GodotMation_Base_Number::read_string(value.right(i));
                    }
                    return r;
                }
            } else {
                GodotMation_Number *r = new GodotMation_Number();
                r->set_from_string(number_string);
                return r;
            }
        } else if(value[i] == 'D'){
            i++;
            number_string +=godot::String("1D");
            if(i < length){
                while( (i < length) && ((std::isdigit(value[i]) || value[i] == '.') ) ){
                    number_string += godot::String(value[i]);
                    i++;
                }
                GodotMation_Dice *r = new GodotMation_Dice();
                r->set_from_string(number_string);
                if (i < length) {
                    r->other_object_number = GodotMation_Base_Number::read_string(value.right(i));
                }
                return r;
            }
        }
    }
    
    return new GodotMation_Base_Number();
}