#include <glm/glm.hpp>
#include "uniforms.h"
#include "fragment.h"
#include <SDL.h>
#include "FastNoiseLite.h"
#include "./noises/earthNoise.h"
#include "./noises/sunNoise.h"
#include "./noises/slimePlanetNoise.h"

Vertex vertexShader(const Vertex& vertex, const Uniforms& uniforms) {
    // Aplicar las transformaciones al vértice utilizando las matrices de uniforms
    glm::vec4 clipSpaceVertex = uniforms.projection * uniforms.view * uniforms.model * glm::vec4(vertex.position, 1.0f);

    // Perspectiva
    glm::vec3 ndcVertex = glm::vec3(clipSpaceVertex) / clipSpaceVertex.w;

    // Aplicar transformación del viewport
    glm::vec4 screenVertex = uniforms.viewport * glm::vec4(ndcVertex, 1.0f);
    
    // Transformar la normal
    glm::vec3 transformedNormal = glm::mat3(uniforms.model) * vertex.normal;
    transformedNormal = glm::normalize(transformedNormal);

    return Vertex{
        glm::vec3(screenVertex),
        transformedNormal,
        vertex.position
    };
}

Fragment fragmentShader(Fragment& fragment) {

    float x = fragment.originalPos.x;
    float y = fragment.originalPos.y;
    float z = fragment.originalPos.z;

    fragment.color = getEarthNoise(x,y,z) * fragment.intensity;

    return fragment;
}

//Planeta gaseoso
/* Fragment fragmentShader(Fragment& fragment) {

    Color color;

    glm::vec3 baseColor = glm::vec3(0, 119, 182);

    float stripePattern = glm::abs(glm::cos(fragment.originalPos.y * 30.0f) * 50.0f);

    glm::vec3 tmpColor = baseColor + stripePattern;

    color = Color(static_cast<int>(tmpColor.x), static_cast<int>(tmpColor.y), static_cast<int>(tmpColor.z));
    
    fragment.color = color * fragment.intensity;

    return fragment;
} */
