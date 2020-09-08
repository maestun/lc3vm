//
//  vm.c
//  lc3vm
//

#include "vm.h"

enum { PC_START = 0x3000 };

sVM vm;

// =============================================================================
// MARK: - Virtual memory
// =============================================================================

void mem_write(uint16_t address, uint16_t val) {
    vm.memory[address] = val;
}

uint16_t mem_read(uint16_t address) {
    // reading the memory mapped keyboard register triggers a key check
    if (address == MR_KBSR) {
        if (sys_check_key()) {
            vm.memory[MR_KBSR] = (1 << 15);
            vm.memory[MR_KBDR] = sys_getc();
        }
        else {
            vm.memory[MR_KBSR] = 0;
        }
    }
    return vm.memory[address];
}



/* read and execute instruction */
void read_and_execute_instruction() {

    int is_max = (R_PC == UINT16_MAX);
    uint16_t instr = mem_read(vm.reg[R_PC]++);
    vm.running = op_exec(instr);
    if (vm.running && is_max) {
        printf("PC overflow!");
    }
}


// =============================================================================
// MARK: - Script loading
// =============================================================================
sScript * read_script(FILE * file) {
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
    
    return script;
}


// =============================================================================
// MARK: - Virtual Machine API
// =============================================================================
sScript * vm_load(const char * script_path) {
    sScript * script = NULL;
    FILE * fp = fopen(script_path, "rb");
    if (fp) {
        script = read_script(fp);
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

void vm_unload_script(sScript * script) {
    free(script->data);
    free(script);
    script = NULL;
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
//    while (vm.running) {
//        vm_step();
//    }
}

void vm_step() {
    if(vm.running) {
        read_and_execute_instruction();
    }
}
