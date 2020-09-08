#include "config.h"
#include "sys.h"
#include "vm.h"
#include "vm_tests.h"

/* main program */
int main(int argc, const char* argv[]) {
    if (argc < 2) {
    /* show usage string */
        printf("lc3 --test | [image-file1] ...\n");
        exit(2);
    }

    // tests
    int didtest = 0;
    if (strcmp(argv[1], "--test") == 0) {
        didtest = 1;
        vm_run_tests();
    }
    
    // run script
    vm_init();
    sScript * script = vm_load(argv[1 + didtest]);
    if(script != NULL) {
        vm_run(script);
    }
    vm_deinit();
}
