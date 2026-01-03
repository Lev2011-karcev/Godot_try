#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

    class GDExample : public CharacterBody3D {
        GDCLASS(GDExample, CharacterBody3D)

    private:
        double speed;
        double jump_velocity;

    protected:
        static void _bind_methods();

    public:
        GDExample();
        ~GDExample();

        void _physics_process(double p_delta) override;
    };

}

#endif
