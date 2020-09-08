//
//  vm.c
//  lc3vm-orig
//

#include "vm.h"

enum { PC_START = 0x3000 };

sVM vm;



/* read and execute instruction */
int read_and_execute_instruction() {
    int running = 1;
    int is_max = R_PC == UINT16_MAX;
    
    uint16_t instr = mem_read(vm.reg[R_PC]++);

    debug_instr("0x%04x\t", instr);
    running = op_exec(instr);

    if (running && is_max) {
        printf("PC overflow!");
        return 0;
    }
    return running;
}



/* load program into memory from a file */
sScript * read_image_file(FILE * file) {
    sScript * script = (sScript *)malloc(sizeof(sScript));
    
    /* the origin tells us where in memory to place the image */
    uint16_t origin;
    fread(&origin, sizeof(origin), 1, file);
    script->org = swap16(origin);

    /* we know the maximum file size so we only need one fread */
    uint16_t max_read = UINT16_MAX - origin;
    uint16_t *p = vm.memory + origin;
    size_t read = fread(p, sizeof(uint16_t), max_read, file);
    script->len = max_read;

    /* swap to little endian */
    while (read-- > 0) {
        *p = swap16(*p);
        ++p;
    }
    return script;
}



sScript * vm_load(const char * script_path) {
    sScript * script = NULL;
    FILE * fp = fopen(script_path, "rb");
    if (fp) {
        script = read_image_file(fp);
        
        printf("Loaded script from file '%s'\nOrigin: 0x%04x\nLength: 0x%04x\n",
               script_path,
               script->org,
               script->len);
        
        fclose(fp);
    }
    return script;
}

void vm_init() {
    
    /* clear memory */
    memset(vm.reg, 0, sizeof(vm.reg));
    memset(vm.memory, 0, sizeof(vm.memory));
    
    /* system */
    sys_init(stdin, stdout);
    
    /* set the PC to starting position */
    /* 0x3000 is the default */
    vm.reg[R_PC] = PC_START;
}

void vm_deinit() {
    sys_deinit();
}

void vm_run(sScript * script) {
    
    vm.reg[R_PC] = script->org;
    
    int running = 1;
    while (running) {
        running = read_and_execute_instruction();
    }
}
