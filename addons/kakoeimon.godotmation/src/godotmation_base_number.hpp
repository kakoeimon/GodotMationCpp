#ifndef GODOTMATION_BASE_NUMBER_H
#define GODOTMATION_BASE_NUMBER_H

#include "Godot.hpp"
#include "String.hpp"

class GodotMation_Base_Number{

public:
    GodotMation_Base_Number();
    virtual ~GodotMation_Base_Number();
    int type = 0;
    godot::String label;
    GodotMation_Base_Number *other_object_number = nullptr;
    virtual int get_number() const;
    virtual void add_number(float);
    virtual void set_from_string(godot::String);

    static GodotMation_Base_Number* from_string(godot::String);
    static GodotMation_Base_Number* read_string(godot::String);

};

#endif