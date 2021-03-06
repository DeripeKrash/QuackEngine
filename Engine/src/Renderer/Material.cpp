#include "Renderer/Material.hpp"
#include "Engine.hpp"

#include "Debug/Log.hpp"

using namespace Renderer;

Material::Material() : Resources::Asset(Resources::AssetType::A_MATERIAL){}

void Material::GenerateShader()
{

    ShaderConstructData scd{checkLight, colorTexture.GetID() != 0,
                            diffuseTexture.GetID() != 0,
                            specularTexture.GetID() != 0,
                            normalMap.GetID() != 0,
                            hasSkeleton};

    shader = Engine::Instance().GetResourcesManager().LoadObjectShader(scd);
}

ShaderConstructData Material::GetConstructData() const
{
    ShaderConstructData shaderConstructData{checkLight, colorTexture.GetID() != 0,
                                            diffuseTexture.GetID() != 0,
                                            specularTexture.GetID() != 0,
                                            normalMap.GetID() != 0,
                                            hasSkeleton};

    return shaderConstructData;
}

void Material::Apply()
{
  shader.Use();
  shader.SetVector4f("material.color", color);
  shader.SetVector3f("material.ambient", ambient);
  shader.SetVector3f("material.diffuse", diffuse);
  shader.SetVector3f("material.specular", specular);
  shader.SetFloat("material.shininess", shininess);

  if (colorTexture.GetID() != 0)
  {
    colorTexture.Bind(0);
    shader.SetSampler("material.colorTexture", 0);
  }

  if (diffuseTexture.GetID() != 0)
  {
    diffuseTexture.Bind(1);
    shader.SetSampler("material.diffuseTexture", 1);
  }

  if (specularTexture.GetID() != 0)
  {
    specularTexture.Bind(2);
    shader.SetSampler("material.specularTexture", 2);
  }

  if (normalMap.GetID() != 0)
  {
    normalMap.Bind(3);
    shader.SetSampler("material.normalMap", 3);
  }
}