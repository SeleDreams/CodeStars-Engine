#ifndef CODESTARS_MAIN_H
#define CODESTARS_MAIN_H

typedef struct csStartupInfos {
    int argc;
    const char **argv;
    unsigned int width;
    unsigned int height;
    const char *name;
} csStartupInfos;

extern int csMain(const csStartupInfos *infos);
#endif