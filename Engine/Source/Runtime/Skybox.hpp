#ifndef Skybox_hpp
#define Skybox_hpp

#include "FishEngine.hpp"
#include "Behaviour.hpp"

namespace FishEngine
{
    // A script interface for the skybox component.
    // see: https://docs.unity3d.com/ScriptReference/Skybox.html
    // see: https://docs.unity3d.com/Manual/class-Skybox.html
    class Skybox : public Behaviour
    {
    public:
        MaterialPtr material()
        {
            return m_material;
        }

        void setMaterial(MaterialPtr material)
        {
            m_material = material;
        }

    private:

        // The material used by the skybox.
        MaterialPtr m_material;
    };
}

#endif // Skybox_hpp