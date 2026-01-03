#ifndef DIE_ZONE_H
#define DIE_ZONE_H

#include <godot_cpp/classes/area3d.hpp>

namespace godot {

    class DieZone : public Area3D {
        GDCLASS(DieZone, Area3D)

    protected:
        static void _bind_methods();

    public:
        DieZone();
        ~DieZone();

        void _on_body_entered(Node* body);
    };

}

#endif
