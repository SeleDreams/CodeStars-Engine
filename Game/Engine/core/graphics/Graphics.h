#ifndef CS_GRAPHICS_H
#define CS_GRAPHICS_H

struct csGraphicsContext;
struct Mesh;
int csGraphicsContextCreate(struct csGraphicsContext **context, int width, int height, const char *name);
void csGraphicsContextSetTargetFramerate(struct csGraphicsContext *context, int framerate);
void csGraphicsContextDestroy(struct csGraphicsContext **context);
void csGraphicsFrameStart(struct csGraphicsContext *context);
void csGraphicsFrameEnd(struct csGraphicsContext *context);
int csGraphicsUpdate(struct csGraphicsContext *context);
void csGraphicsWaitForNextFrame(int framerate);
void csGraphicsDrawMesh(struct csGraphicsContext *context, struct Mesh *mesh, unsigned int shader_program);
unsigned int csGraphicsLoadShader(struct csGraphicsContext *context, const char *vertex_shader_data,const char* fragment_shader_data);
#endif