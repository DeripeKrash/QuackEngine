#ifndef _MATERIAL_
#define _MATERIAL_

#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include "Resources/Asset.hpp"

#include <memory>

namespace Renderer
{
    struct Material : public Resources::Asset
    {
        Shader shader;

        bool checkLight{true};

        Maths::Color4f color{1, 1, 1, 1};
        Maths::Color3f ambient{1, 1, 1};
        Maths::Color3f diffuse{1, 1, 1};
        Maths::Color3f specular{1, 1, 1};

        float shininess{128};

        Texture colorTexture;
        Texture diffuseTexture;
        Texture specularTexture;
        Texture normalMap;

        bool hasSkeleton{false};

        Material();
        void GenerateShader();
        ShaderConstructData GetConstructData() const;
        void Apply();

        template<class Archive>
        void save(Archive &archive) const
        {
            archive(CEREAL_NVP(checkLight),
                    CEREAL_NVP(color),
                    CEREAL_NVP(ambient),
                    CEREAL_NVP(diffuse),
                    CEREAL_NVP(specular),
                    CEREAL_NVP(shininess),
                    CEREAL_NVP(hasSkeleton),
                    cereal::make_nvp("colorTexture", colorTexture.GetPath()),
                    cereal::make_nvp("diffuseTexture", diffuseTexture.GetPath()),
                    cereal::make_nvp("specularTexture", specularTexture.GetPath()),
                    cereal::make_nvp("normalMap", normalMap.GetPath())
            );
        }


            template<class Archive>
            void load(Archive &archive)
            {
                std::string _colorTexture;
                std::string _diffuseTexture;
                std::string _specularTexture;
                std::string _normalMap;

                archive(CEREAL_NVP(checkLight),
                        CEREAL_NVP(color),
                        CEREAL_NVP(ambient),
                        CEREAL_NVP(diffuse),
                        CEREAL_NVP(specular),
                        CEREAL_NVP(shininess),
                        CEREAL_NVP(hasSkeleton),
                        cereal::make_nvp("colorTexture", _colorTexture),
                        cereal::make_nvp("diffuseTexture", _diffuseTexture),
                        cereal::make_nvp("specularTexture", _specularTexture),
                        cereal::make_nvp("normalMap", _normalMap)
                );

                colorTexture.SetPath(_colorTexture);
                diffuseTexture.SetPath(_diffuseTexture);
                specularTexture.SetPath(_specularTexture);
                normalMap.SetPath(_normalMap);

        }
    };

    using MaterialInterface = std::shared_ptr<Material>;
}

#endif //_MATERIAL_