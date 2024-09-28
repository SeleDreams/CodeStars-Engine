//
// Created by SeleDreams on 28/09/2024.
//

#ifndef NDSGRAPHICSFUNCTIONS_H
#define NDSGRAPHICSFUNCTIONS_H
#include <core/graphics/Graphics.h>
#include "NDSGraphics.h"

int csNDSGraphicsInit(void);
int csNDSGraphicsContextCreate(csGraphicsContext **context, int width, int height, const char *name);
void csNDSGraphicsContextDestroy(csGraphicsContext *context);
void csNDSGraphicsWindowDestroy(csGraphicsWindow *window);
int csNDSGraphicsRemoveWindow(csGraphicsContext *context,int window_id);
int csNDSGraphicsCreateWindow(csGraphicsContext *context, unsigned int width,unsigned int height, const char *name);
int csNDSGraphicsCreate(csGraphicsContext *context,unsigned int width, unsigned int height, const char *name);
void csNDSGraphicsTerminate(csGraphicsContext *context);
void csNDSGraphicsFrameStart(csGraphicsContext *context);
void csNDSGraphicsFrameEnd(csGraphicsContext *context);
int csNDSGraphicsUpdate(csGraphicsContext *context);
#endif //NDSGRAPHICSFUNCTIONS_H
