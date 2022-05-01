#include <iostream>
#include <cmath>
#include <glm/vec4.hpp>
#include "matrices.h"

// Testa colisao entre os cubos
bool collisionBetweenCubes(glm::vec4 box1min, glm::vec4 box1max, glm::vec4 box2min, glm::vec4 box2max) {
    // Para cada eixo xyz
    for(int i = 0; i<3; i++) {
        // Verificsa se NAO ha interseccao entre os pontos minimos e maximos dos cubos
        if ((box1min[i] < box2min[i] &&  
            box1min[i] < box2max[i] && 
            box1max[i] < box2min[i] &&  
            box1max[i] < box2max[i])
            ||
            (box2min[i] < box1min[i] &&  
            box2min[i] < box1max[i] && 
            box2max[i] < box1min[i] &&  
            box2max[i] < box1max[i]))
            return false;
    }
    return true;
}

// Testa colisao entre esferas
bool collisionBetweenSpheres(glm::vec4 box1min, glm::vec4 box1max, glm::vec4 box2min, glm::vec4 box2max) {
    // Fonte: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

    glm::vec4 center_sphere1 = 0.5f*(box1max - box1min) + box1min;
    glm::vec4 center_sphere2 = 0.5f*(box2max - box2min) + box2min;
    
    float radius1 = (sqrt((center_sphere1.x - center_sphere1.x) * 
                         (box1min.x - center_sphere1.x) 
                         + 
                         (box1min.y - center_sphere1.y) * 
                         (box1min.y - center_sphere1.y) 
                         + (box1min.z - center_sphere1.z) * 
                         (box1min.z-center_sphere1.z)))/1.732;

    float radius2 = (sqrt((center_sphere2.x - center_sphere2.x) * 
                         (box2min.x - center_sphere2.x) 
                         + 
                         (box2min.y - center_sphere2.y) * 
                         (box2min.y - center_sphere2.y) 
                         + (box2min.z - center_sphere2.z) * 
                         (box2min.z-center_sphere2.z)))/1.732;

     float distance = glm::sqrt((center_sphere1.x - center_sphere2.x) * 
                               (center_sphere1.x - center_sphere2.x) 
                               +
                               (center_sphere1.y - center_sphere2.y) *
                               (center_sphere1.y - center_sphere2.y)
                               +
                               (center_sphere1.z - center_sphere2.z) *
                               (center_sphere1.z - center_sphere2.z));
    
    bool collision = distance < (radius1 + radius2);

    return collision;
}

// Testa colisao entre cubo e esfera
bool collisionBetweenCubeSphere(glm::vec4 box_cube_min, glm::vec4 box_cube_max, glm::vec4 box_sphere_min, glm::vec4 box_sphere_max) {
    // Fonte: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

    glm::vec4 center_sphere = 0.5f*(box_sphere_max - box_sphere_min) + box_sphere_min;
    
    float radius = (sqrt((box_sphere_min.x - center_sphere.x) * 
                         (box_sphere_min.x - center_sphere.x) 
                         + 
                         (box_sphere_min.y - center_sphere.y) * 
                         (box_sphere_min.y - center_sphere.y) 
                         + (box_sphere_min.z - center_sphere.z) * 
                         (box_sphere_min.z-center_sphere.z)))/1.732;

    float x = glm::max(box_cube_min.x, glm::min(center_sphere.x, box_cube_max.x));
    float y = glm::max(box_cube_min.y, glm::min(center_sphere.y, box_cube_max.y));
    float z = glm::max(box_cube_min.z, glm::min(center_sphere.z, box_cube_max.z));

    float distance = glm::sqrt((x - center_sphere.x) * 
                               (x - center_sphere.x) 
                               +
                               (y - center_sphere.y) *
                               (y - center_sphere.y)
                               +
                               (z - center_sphere.z) *
                               (z - center_sphere.z));

    bool collision = distance < radius;

    return collision;
}


