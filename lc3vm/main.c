//
//  main.c
//  lc3vm
//

#include "config.h"
#include "sys.h"
#include "vm.h"
#include "vm_tests.h"

int __main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("%s --test | [image-file1] ...\n", kProgName);
        exit(2);
    }

    // tests
    int didtest = 0;
    if (strcmp(argv[1], "--test") == 0) {
        didtest = 1;
        vm_run_tests();
    }
    
    // load script(s)
    int script_count = argc - 1 - didtest;
    sScript * scripts[script_count];
    for(int i = 0; i < script_count; i++) {
        const char * path = argv[1 + didtest + i];
        sScript * script = vm_load(path);
        if(script != NULL) {
            scripts[i] = script;
        }
        else {
            printf("FATAL: Cannot load script file %s.\n", path);
            exit(1);
        }
    }
    
    // run vm
    vm_init();
    if(script_count > 0) {
        vm_run(scripts[0]);
    }
    vm_deinit();
    return 0;
}
