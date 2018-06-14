#ifndef GODOTMATION_CONVERTER_H
#define GODOTMATION_CONVERTER_H

#include "godotmation_pool.hpp"

class GodotMation_Resource;
class GodotMation_State;

class GodotMation_Converter : public GodotMation_Pool{

public:
    GodotMation_Converter();
    ~GodotMation_Converter();
    virtual bool trigger();
    virtual int can_push(int) const;
};

#endif