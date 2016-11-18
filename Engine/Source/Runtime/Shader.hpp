#ifndef Shader_hpp
#define Shader_hpp

#include <set>
#include "GLEnvironment.hpp"
#include "Vector3.hpp"
#include "Matrix4x4.hpp"
#include "Common.hpp"
#include "ShaderProperty.hpp"

#define PositionIndex 0
#define NormalIndex 1
#define UVIndex 2
#define TangentIndex 3
#define BoneIndexIndex 4
#define BoneWeightIndex 5

namespace FishEngine
{
    class ShaderImpl;

    // https://docs.unity3d.com/Manual/SL-CullAndDepth.html
    enum class Cullface {
        Back = GL_BACK,
        Front = GL_FRONT,
        Off = GL_NONE,
    };

    inline const char* ToString(Cullface e)
    {
        switch (e) {
        case Cullface::Back: return "Back"; break;
        case Cullface::Front: return "Front"; break;
        case Cullface::Off: return "Off"; break;
        default: abort(); break;
        }
    }


    template<>
    inline Cullface ToEnum<Cullface>(const std::string& s)
    {
        if (s == "Back") return Cullface::Back;
        if (s == "Front") return Cullface::Front;
        if (s == "Off") return Cullface::Off;
        abort();
    }

    enum class ZWrite {
        On,
        Off,
    };

    inline const char* ToString(ZWrite e)
    {
        switch (e) {
        case ZWrite::On: return "On"; break;
        case ZWrite::Off: return "Off"; break;
        default: abort(); break;
        }
    }

    template<>
    inline ZWrite ToEnum<ZWrite>(const std::string& s)
    {
        if (s == "On") return ZWrite::On;
        if (s == "Off") return ZWrite::Off;
        abort();
    }

    enum class ZTest {
        Less = GL_LESS,
        Greater = GL_GREATER,
        LEqual = GL_LEQUAL,
        GEqual = GL_GEQUAL,
        Equal = GL_EQUAL,
        NotEqual = GL_NOTEQUAL,
        Always = GL_ALWAYS,
    };

    inline const char* ToString(ZTest e)
    {
        switch (e) {
        case ZTest::Less: return "Less"; break;
        case ZTest::Greater: return "Greater"; break;
        case ZTest::LEqual: return "LEqual"; break;
        case ZTest::GEqual: return "GEqual"; break;
        case ZTest::Equal: return "Equal"; break;
        case ZTest::NotEqual: return "NotEqual"; break;
        case ZTest::Always: return "Always"; break;
        default: abort(); break;
        }
    }

    template<>
    inline ZTest ToEnum<ZTest>(const std::string& s)
    {
        if (s == "Less") return ZTest::Less;
        if (s == "Greater") return ZTest::Greater;
        if (s == "LEqual") return ZTest::LEqual;
        if (s == "GEqual") return ZTest::GEqual;
        if (s == "Equal") return ZTest::Equal;
        if (s == "NotEqual") return ZTest::NotEqual;
        if (s == "Always") return ZTest::Always;
        abort();
    }
    
//    enum class ShaderType
//    {
//        VertexShader,
//        FragmentShader,
//        GeometryShader,
//        VertexAndFragmentShader,
//    };


    class Shader
    {
    public:
        Shader();
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        //Shader(Shader&&);

        ~Shader();

        static void Init();
        
        static ShaderPtr CreateFromFile(const std::string& path);


        void Use() const;

        //GLuint program() const
        //{
        //    return m_program;
        //}

        //GLuint getAttribLocation(const char* name) const;

        //void BindUniformFloat(const char* name, const float value) const;
        //void BindUniformVec3(const char* name, const glm::vec3& value) const;
        //void BindUniformMat3(const char* name, const glm::mat3& value) const;
        void BindUniformVec4(const char* name, const Vector4& value);
        void BindUniformMat4(const char* name, const Matrix4x4& value);

        //void BindUniformTexture(const char* name, const GLuint texture, const GLuint id, GLenum textureType = GL_TEXTURE_2D) const;

        void BindMatrixArray(const std::string& name, const std::vector<Matrix4x4>& matrixArray);
        void BindUniforms(const ShaderUniforms& uniforms);

        void BindTexture(const std::string& name, TexturePtr& texture);
        void BindTextures(const std::map<std::string, TexturePtr>& textures);

        void PreRender() const;
        void PostRender() const;

        void CheckStatus() const;

        const std::vector<UniformInfo>& uniforms() const
        {
            return m_uniforms;
        }

        std::vector<UniformInfo>& uniforms()
        {
            return m_uniforms;
        }

        static ShaderPtr builtinShader(const std::string& name);
        
        static const std::map<std::string, ShaderPtr>& allShaders()
        {
            // TODO
            return m_builtinShaders;
        }
        
        bool IsTransparent() const
        {
            return m_blend;
        }

        //std::shared_ptr<Shader> m_skinnedShader = nullptr;

        bool IsKeywordEnabled(ShaderKeyword keyword)
        {
            return (m_keywords & static_cast<ShaderKeywords>(keyword)) != 0;
        }

        void EnableLocalKeyword(ShaderKeyword keyword);

        void DisableLocalKeyword(ShaderKeyword keyword);

    private:
        friend class Material;

        //GLuint m_program = 0;
        std::unique_ptr<ShaderImpl> m_impl;
        //std::string m_shaderString;

        //void GetAllUniforms();
        bool FromFile(const std::string& path);

        // cache
        GLuint m_program = 0;
        //std::map<std::string, UniformInfo>* m_uniforms;
        std::vector<UniformInfo> m_uniforms;

        Cullface m_cullface = Cullface::Back;
        bool m_ZWrite = true;
        bool m_blend = false;
        bool m_applyNormalMap = false;
        bool m_receiveShadow = true;

        friend class RenderSystem;

        static std::map<std::string, ShaderPtr> m_builtinShaders;

        ShaderKeywords m_keywords = ShaderKeyword::Shadow;
    };
}

#endif
