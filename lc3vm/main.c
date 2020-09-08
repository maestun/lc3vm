//
//  main.c
//  lc3vm
//

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
    
    // load script(s)
    int script_count = argc - 1 - didtest;
    sScript * scripts[script_count];
    for(int i = 0; i < script_count; i++) {
        sScript * script = vm_load(argv[1 + didtest + i]);
        scripts[i] = script;
    }
    
    // run vm
    vm_init();
    if(script_count > 0) {
        vm_run(scripts[0]);
    }
    vm_deinit();
}
