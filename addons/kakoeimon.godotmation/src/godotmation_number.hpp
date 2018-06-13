#ifndef GODOTMATION_NUMBER_H
#define GODOTMATION_NUMBER_H

#include "godotmation_base_number.hpp"




class GodotMation_Number: public GodotMation_Base_Number{

public:
    GodotMation_Number();
    ~GodotMation_Number();
    int base = 0;
    float chance = 0;
    float number = 0.0f;

    void add_number(float);
    void set_from_string(godot::String);
    int get_number() const;

};

#endif