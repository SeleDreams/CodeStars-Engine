#include "CodeStarsEngine.h"
int main(int argc,const char **argv)
{
    csStartupInfos infos = {
        .argc = argc,
        .argv = argv,
        .width = 800,
        .height = 600,
        .name = "Code Stars"
    };
    return csMain(&infos);
    
}