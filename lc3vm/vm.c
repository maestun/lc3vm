//
//  vm.c
//  lc3vm
//

#include "vm.h"

enum { PC_START = 0x3000 };

sVM vm;



/* read and execute instruction */
void read_and_execute_instruction() {
    int is_max = R_PC == UINT16_MAX;
    
    uint16_t instr = mem_read(vm.reg[R_PC]++);

    debug_instr("0x%04x\t", instr);
    vm.running = op_exec(instr);

    if (vm.running && is_max) {
        printf("PC overflow!");
        // return 0;
    }
}



/* load program into memory from a file */
sScript * read_image_file(FILE * file) {
    sScript * script = (sScript *)malloc(sizeof(sScript));
    
    // word: origin (big endian)
    script->org = (fgetc(file) << 8) + fgetc(file);
    
    // get data size (in bytes and words)
    long prev = ftell(file);
    fseek(file, 0L, SEEK_END);
    long bcount = ftell(file) - prev;
    script->len = (uint32_t)(bcount >> 1);
    
    // words: data (big endian)
    script->data = (uint16_t *)malloc(script->len * sizeof(uint16_t));
    fseek(file, sizeof(uint16_t), SEEK_SET);
    for(long i = 0; i < script->len; i++) {
        script->data[i] = (fgetc(file) << 8) + fgetc(file);
    }
    
    /* the origin tells us where in memory to place the image */
//    uint16_t origin;
//    fread(&origin, sizeof(origin), 1, file);
//    script->org = swap16(origin);

    /* we know the maximum file size so we only need one fread */
//    uint16_t max_read = UINT16_MAX - origin;
//    uint16_t *p = vm.memory + origin;
//    size_t read = fread(p, sizeof(uint16_t), max_read, file);
//    script->len = max_read;

    /* swap to little endian */
//    while (read-- > 0) {
//        *p = swap16(*p);
//        ++p;
//    }
    return script;
}



sScript * vm_load(const char * script_path) {
    sScript * script = NULL;
    FILE * fp = fopen(script_path, "rb");
    if (fp) {
        script = read_image_file(fp);
        strcpy(script->name, strrchr(script_path, kPathSeparator) + 1);
        printf("Loaded script from file '%s'\nOrigin address: 0x%04x\nWord count: 0x%04x (%d bytes)\nName: %s\n",
               script_path,
               script->org,
               script->len,
               script->len,
               script->name);
        
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
    // copy script to vm memory
    memcpy(vm.memory + script->org, script->data, script->len * sizeof(uint16_t));
    vm.reg[R_PC] = script->org;
    
    // run
    vm.running = 1;
    while (vm.running) {
        read_and_execute_instruction();
    }
}