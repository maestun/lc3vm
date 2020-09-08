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

    int didtest = 0;
    if (strcmp(argv[1], "--test") == 0) {
        didtest = 1;
        vm_run_tests();
    }

    for (int j = 1 + didtest; j < argc; ++j) {
        if (!read_image(argv[j])) {
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
  }

  sys_init(stdin, stdout);
    
  /* set the PC to starting position */
  /* 0x3000 is the default */
  enum { PC_START = 0x3000 };
  vm.reg[R_PC] = PC_START;

  int running = 1;
  while (running) {
    running = read_and_execute_instruction();
  }
    
    sys_deinit();
//  restore_input_buffering();
}
