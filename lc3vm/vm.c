//
//  vm.c
//  lc3vm-orig
//

#include "vm.h"

uint16_t memory[UINT16_MAX];
uint16_t reg[R_COUNT];



/* read and execute instruction */
int read_and_execute_instruction() {
  int running = 1;
  int is_max = R_PC == UINT16_MAX;

    /* FETCH */
    debug_instr("0x%04x:\t", reg[R_PC]);
    
    uint16_t instr = mem_read(reg[R_PC]++);
//    uint16_t op = instr >> 12;

    debug_instr("0x%04x\t", instr);
    running = op_exec(instr);

    if (running && is_max) {
        printf("Program counter overflow!");
        return 0;
    }

    return running;
}



/* load program into memory from a file */
void read_image_file(FILE *file) {
  /* the origin tells us where in memory to place the image */
  uint16_t origin;
  fread(&origin, sizeof(origin), 1, file);
  origin = swap16(origin);

  /* we know the maximum file size so we only need one fread */
  uint16_t max_read = UINT16_MAX - origin;
  uint16_t *p = memory + origin;
  size_t read = fread(p, sizeof(uint16_t), max_read, file);

  /* swap to little endian */
  while (read-- > 0) {
    *p = swap16(*p);
    ++p;
  }
}

int read_image(const char* image_path) {
  FILE *file = fopen(image_path, "rb");
  if (!file) { return 0; };
  read_image_file(file);
  fclose(file);
  return 1;
}
