#include "Mesh.h"
#include <stdlib.h>
#include <string.h>
#include "../components/transform.h"
#include "../memory/includes.h"
ECS_COMPONENT_DECLARE(csMesh);

// Vertices of the pyramid (fixed-point format)
const csFixed pyramid_vertices[] = {
    csFixedFromFloat(-1.0), csFixedFromFloat(1.0), csFixedFromFloat(-1.0),  // Top front left
    csFixedFromFloat(1.0), csFixedFromFloat(1.0), csFixedFromFloat(-1.0),   // Top front right
    csFixedFromFloat(1.0), csFixedFromFloat(-1.0), csFixedFromFloat(-1.0),  // Bottom front right
    csFixedFromFloat(-1.0), csFixedFromFloat(-1.0), csFixedFromFloat(-1.0), // Bottom front left
    csFixedFromFloat(-1.0), csFixedFromFloat(1.0), csFixedFromFloat(1.0),   // Top back left
    csFixedFromFloat(1.0), csFixedFromFloat(1.0), csFixedFromFloat(1.0),    // Top back right
    csFixedFromFloat(1.0), csFixedFromFloat(-1.0), csFixedFromFloat(1.0),   // Bottom back right
    csFixedFromFloat(-1.0), csFixedFromFloat(-1.0), csFixedFromFloat(1.0)   // Bottom back left
};

// Indices for the cube faces
const unsigned char pyramid_indices[] = {
    0, 1, 2, 2, 3, 0, // Front face
    4, 5, 6, 6, 7, 4, // Back face
    0, 1, 5, 5, 4, 0, // Top face
    2, 3, 7, 7, 6, 2, // Bottom face
    0, 3, 7, 7, 4, 0, // Left face
    1, 2, 6, 6, 5, 1  // Right face
};

// Colors for each vertex
const unsigned char pyramid_colors[] = {
    255, 0, 0, 255,   // Red for top front left
    0, 255, 0, 255,   // Green for top front right
    0, 0, 255, 255,   // Blue for bottom front right
    255, 255, 0, 255, // Yellow for bottom front left
    0, 255, 255, 255, // Cyan for top back left
    255, 0, 255, 255, // Magenta for top back right
    192, 192, 192, 255, // Silver for bottom back right
    128, 0, 128, 255  // Purple for bottom back left
};

void csMeshCreatePrimitivePyramid(csMesh *mesh)
{
    mesh->vertices = pyramid_vertices;
    mesh->indices = pyramid_indices;
    mesh->colors = pyramid_colors;
    mesh->indices_count = sizeof(pyramid_indices) / sizeof(char);
    mesh->vertices_count = sizeof(pyramid_vertices) / sizeof(csFixed);
    mesh->colors_count = sizeof(pyramid_colors) / sizeof(char);
}

void csMeshModuleImport(ecs_world_t *ecs) {
    ECS_MODULE(ecs,csMeshModule);
    ECS_COMPONENT_DEFINE(ecs,csMesh);
    ecs_system(ecs, {
         .entity = ecs_entity(ecs, {
             .name = "csMeshDraw",
             .add = ecs_ids( ecs_dependson(EcsOnUpdate) )
         }),
         .query.terms = {
             { .id = ecs_id(csMesh)},
             {.id=ecs_id(csTransform),.inout = EcsIn}
         },
         .callback = csMeshDraw
    });
    ecs_set_hooks(ecs, csMesh, {
        .dtor = csMeshFree
    });
}