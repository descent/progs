#include <stdio.h>
#include "mytype.h"

#pragma pack(push, 1)

    struct Data
    {
        u32                       suppressMBoxPolling : 1;
        u32                       reserved3               : 1;
        u32                       dcSyncMode              : 4;
        u32                       ioOpenStateInit     : 1;
        u32                       logTopologyChanges  : 1;
        u32                       disableContMeasuring    : 1;
        u32                       disableContCrcCheck : 1;
        u32                       dynamicTopology     : 1;
        u32                       waitForStartIo          : 1;
        u32                       forceReInit             : 1;
        // u32                       :0;
    };

#pragma pack( pop )

int main(int argc, char *argv[])
{
  printf("sizeof Data: %u\n", sizeof(struct Data));

  return 0;
}
