//
//  main.c
//  alis
//

#include "config.h"
#include "alis.h"

void usage() {
    printf("%s v%s\nUsage:\n\t%s <data_path>\n\n\t%s <script_path>\n",
           kProgName, kProgVersion, kProgName, kProgName);
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        usage();
    }
    else {
        // guess platform
        sPlatform pl = guess_platform(argv[1]);
        if(is_supported(pl)) {
            // run vm
            alis_init(pl);
            alis_main();
            alis_deinit();
        }
        else {
            debug(EDebugFatal,
                       "Platform '%s' is not supported.\n",
                       pl.desc);
        }
    }
    return 0;
}
