# This script imports an ALIS Atari TOS program into Ghidra
#@author Christian Zietz / maestun
#@category Import
#@keybinding 
#@menupath 
#@toolbar 

# Copyright (c) 2019 Christian Zietz
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import struct
import jarray

#############################################
# CHANGE DATA HERE DEPENDING ON VM EXECUTABLE
reloc_addr = 0xaa9a

# ISHAR 1 / CR ELITE
# alis_jtab_opcodes = 0x10d22
# alis_jtab_opcodes_len = 454
# alis_jtab_opernames = 0x10ee8
# alis_jtab_opernames_len = 
# alis_jtab_storenames = 0x
# alis_jtab_storenames_len = 
# alis_jtab_addnames = 0x
# alis_jtab_addnames_len = 


# ISHAR 2 / CR ELITE
alis_jtab_opcodes = 0x12cb6
alis_jtab_opcodes_len = 462
alis_jtab_opernames = 0x12e84
alis_jtab_opernames_len = 170
alis_jtab_storenames = 0x12f2e
alis_jtab_storenames_len = 30
alis_jtab_addnames = 0x12f6a
alis_jtab_addnames_len = 30

# COMMON
alis_jtab_opcodes_names = ["cnul", "cesc1", "cesc2", "cesc3", "cbreakpt", "cjsr8", "cjsr16", "cjsr24", "cjmp8", "cjmp16", "cjmp24", "cjsrabs", "cjmpabs", "cjsrind16", "cjsrind24", "cjmpind16", "cjmpind24", "cret", "cbz8", "cbz16", "cbz24", "cbnz8", "cbnz16", "cbnz24", "cbeq8", "cbeq16", "cbeq24", "cbne8", "cbne16", "cbne24", "cstore", "ceval", "cadd", "csub", "cmul", "cdiv", "cvprint", "csprinti", "csprinta", "clocate", "ctab", "cdim", "crandom", "cloop8", "cloop16", "cloop24", "cswitch1", "cswitch2", "cstart8", "cstart16", "cstart24", "cleave", "cprotect", "casleep", "cclock", "cnul", "cscmov", "cscset", "cclipping", "cswitching", "cwlive", "cunload", "cwakeup", "csleep", "clive", "ckill", "cstop", "cstopret", "cexit", "cload", "cdefsc", "cscreen", "cput", "cputnat", "cerase", "cerasen", "cset", "cmov", "copensc", "cclosesc", "cerasall", "cforme", "cdelforme", "ctstmov", "ctstset", "cftstmov", "cftstset", "csuccent", "cpredent", "cnearent", "cneartyp", "cnearmat", "cviewent", "cviewtyp", "cviewmat", "corient", "crstent", "csend", "cscanon", "cscanoff", "cinteron", "cinteroff", "cscanclr", "callentity", "cpalette", "cdefcolor", "ctiming", "czap", "cexplode", "cding", "cnoise", "cinitab", "cfopen", "cfclose", "cfcreat", "cfdel", "cfreadv", "cfwritev", "cfwritei", "cfreadb", "cfwriteb", "cplot", "cdraw", "cbox", "cboxf", "cink", "cpset", "cpmove", "cpmode", "cpicture", "cxyscroll", "clinking", "cmouson", "cmousoff", "cmouse", "cdefmouse", "csetmouse", "cdefvect", "csetvect", "cnul", "capproach", "cescape", "cvtstmov", "cvftstmov", "cvmov", "cdefworld", "cworld", "cfindmat", "cfindtyp", "cmusic", "cdelmusic", "ccadence", "csetvolum", "cxinv", "cxinvon", "cxinvoff", "clistent", "csound", "cmsound", "credon", "credoff", "cdelsound", "cwmov", "cwtstmov", "cwftstmov", "ctstform", "cxput", "cxputat", "cmput", "cmputat", "cmxput", "cmxputat", "cmmusic", "cmforme", "csettime", "cgettime", "cvinput", "csinput", "cnul", "cnul", "cnul", "crunfilm", "cvpicprint", "cspicprint", "cvputprint", "csputprint", "cfont", "cpaper", "ctoblack", "cmovcolor", "ctopalet", "cnumput", "cscheart", "cscpos", "cscsize", "cschoriz", "cscvertic", "cscreduce", "cscscale", "creducing", "cscmap", "cscdump", "cfindcla", "cnearcla", "cviewcla", "cinstru", "cminstru", "cordspr", "calign", "cbackstar", "cstarring", "cengine", "cautobase", "cquality", "chsprite", "cselpalet", "clinepalet", "cautomode", "cautofile", "ccancel", "ccancall", "ccancen", "cblast", "cscback", "cscrolpage", "cmatent", "cshrink", "cdefmap", "csetmap", "cputmap", "csavepal", "csczoom", "ctexmap", "calloctab", "cfreetab", "cscantab", "cneartab", "cscsun", "cdarkpal", "cscdark", "caset", "camov", "cscaset", "cscamov", "cscfollow", "cscview", "cfilm", "cwalkmap", "catstmap", "cavtstmov", "cavmov", "caim", "cpointpix", "cchartmap", "cscsky", "czoom"]
alis_jtab_opernames_names = ["oimmb", "oimmw", "oimmp", "olocb", "olocw", "olocp", "oloctp", "oloctc", "olocti", "odirb", "odirw", "odirp", "odirtp", "odirtc", "odirti", "omainb", "omainw", "omainp", "omaintp", "omaintc", "omainti", "ohimb", "ohimw", "ohimp", "ohimtp", "ohimtc", "ohimti", "opile", "oeval", "ofin", "cnul", "cnul", "opushacc", "oand", "oor", "oxor", "oeqv", "oegal", "odiff", "oinfeg", "osupeg", "oinf", "osup", "oadd", "osub", "omod", "odiv", "omul", "oneg", "oabs", "ornd", "osgn", "onot", "oinkey", "okeyon", "ojoy", "oprnd", "oscan", "oshiftkey", "ofree", "omodel", "ogetkey", "oleft", "oright", "omid", "olen", "oasc", "ostr", "osadd", "osegal", "osdiff", "osinfeg", "ossupeg", "osinf", "ossup", "ospushacc", "ospile", "oval", "oexistf", "ochr", "ochange", "ocountry", "omip", "ojoykey", "oconfig"]
alis_jtab_storenames_names = ["cnul", "cnul", "cnul", "slocb", "slocw", "slocp", "sloctp", "sloctc", "slocti", "sdirb", "sdirw", "sdirp", "sdirtp", "sdirtc", "sdirti", "smainb", "smainw", "smainp", "smaintp", "smaintc", "smainti", "shimb", "shimw", "shimp", "shimtp", "shimtc", "shimti", "spile", "seval", "ofin"]
alis_jtab_addnames_names = ["cnul", "cnul", "cnul", "alocb", "alocw", "alocp", "aloctp", "aloctc", "alocti", "adirb", "adirw", "adirp", "adirtp", "adirtc", "adirti", "amainb", "amainw", "amainp", "amaintp", "amaintc", "amainti", "ahimb", "ahimw", "ahimp", "ahimtp", "ahimtc", "ahimti", "spile", "aeval", "ofin"]
#############################################

# Ask user for the file to import
file = askFile("Please specify a file to import", "Import")

# Import as binary file for 68k CPU since there is no builtin support for TOS program file format
lang = getDefaultLanguage(ghidra.program.model.lang.Processor.findOrPossiblyCreateProcessor("68000"))
comp = lang.getDefaultCompilerSpec()
program = importFileAsBinary(file, lang, comp)
flat = ghidra.program.flatapi.FlatProgramAPI(program)

# Initialize some variables
txn = program.startTransaction("Import program")
mem = program.getMemory()
start = mem.getMinAddress()

# Check if the extension is CPX (control panel file)
if file.toString()[-4:].upper() == ".CPX":
    # remove CPX header
    prg_start = start.add(512)
    mem.split(mem.getBlocks()[0], prg_start)
    mem.removeBlock(mem.getBlocks()[0], ghidra.util.task.TaskMonitor.DUMMY)
    # move actual program start to 0
    mem.moveBlock(mem.getBlocks()[0], start, ghidra.util.task.TaskMonitor.DUMMY)

# Check for "magic" number in header
start = mem.getMinAddress()
magic = mem.getShort(start)
if magic != 0x601a:
    raise Exception("Not a TOS program!")

# Data from PRG header
len_text = mem.getInt(start.add(0x2))
len_data = mem.getInt(start.add(0x6))
len_bss  = mem.getInt(start.add(0xa))
len_sym  = mem.getInt(start.add(0xe))

# Keep symbol table for later use
if len_sym > 0:
    sym_table = jarray.zeros(len_sym, "b")
    mem.getBytes(start.add(0x1c+len_text+len_data), sym_table)
    sym_table = bytearray(sym_table) # to native Python type

# Relocate program
prg = start.add(0x1c)
ptr = start.add(0x1c+len_text+len_data+len_sym) # start of relocation table
rea = mem.getInt(ptr) # first address to relocate
ptr = ptr.add(4)
if rea != 0:
    # print("Relocating %x (%08x => %08x)" % (rea, mem.getInt(prg.add(rea)), mem.getInt(prg.add(rea))+reloc_addr))
    mem.setInt(prg.add(rea), mem.getInt(prg.add(rea)) + reloc_addr)
    while True:
        offs = mem.getByte(ptr)
        if offs<0: # byte is *signed* in Java/Jython
            offs=256+offs
        ptr = ptr.add(1)
        if offs == 0: # end of table
            break
        if offs == 1: # advance by 254
            rea = rea + 254
            continue
        rea = rea + offs
        # print("Relocating %x (%08x => %08x)" % (rea, mem.getInt(prg.add(rea)), mem.getInt(prg.add(rea))+reloc_addr))
        mem.setInt(prg.add(rea), mem.getInt(prg.add(rea)) + reloc_addr)


# Header Block, split off actual TEXT, DATA sections
bl_hdr = mem.getBlocks()[0] # only one block exists right now
bl_hdr.setName("Program Header")
mem.split(bl_hdr, start.add(0x1c))

# Create TEXT and DATA sections at relocated address
bl_text = mem.getBlocks()[-1] # newly split block
bl_text.setName("TEXT")
text_start = start.add(reloc_addr)
data_start = text_start.add(len_text)
bss_start =  data_start.add(len_data)
mem.moveBlock(bl_text, text_start, ghidra.util.task.TaskMonitor.DUMMY)

# Split off data block
if len_data!=0:
    mem.split(bl_text, data_start)
    bl_data = mem.getBlocks()[-1] # newly split block
    bl_data.setName("DATA")
else:
    bl_data = bl_text

# Delete everything after end of DATA, create new empty BSS block instead
if len_bss!=0:
    mem.split(bl_data, bss_start)
    bl_bss = mem.getBlocks()[-1] # new block
    mem.removeBlock(bl_bss, ghidra.util.task.TaskMonitor.DUMMY)
    bl_bss = mem.createUninitializedBlock("BSS", bss_start, len_bss, False)
    bl_bss.setRead(True)
    bl_bss.setWrite(True)

# Change the name of the fragment created when program was loaded
frag = program.getTreeManager().getFragment(ghidra.program.database.module.TreeManager.DEFAULT_TREE_NAME, start)
frag.setName("Header, TEXT, DATA")

# Import symbol table if the user wants to
# Primitive plausibility check: a DRI/GST symbol table size always is a multiple of 14
if len_sym > 0 and (len_sym % struct.calcsize(">8sHL")) == 0 and askYesNo("Import", "Import symbol table?") == True:
    s_ptr = 0
    while s_ptr < len_sym:
        s_name, s_id, s_addr = struct.unpack_from(">8sHL", bytes(sym_table), s_ptr)
        s_ptr += struct.calcsize(">8sHL")
        if s_addr == 0xFFFFFFFF:
            continue

        # extended GST format: read name from next slot
        if s_id & 0x48 != 0:
            s_name = s_name + struct.unpack_from(">14s",  bytes(sym_table), s_ptr)[0]
            s_ptr += struct.calcsize(">14s")

        s_name = s_name.rstrip("\0")

        # skip symbols containing file names
        if s_name[-2:] == ".o" or s_name[-2:] == ".a" or s_name[0] == "/":
            continue

        s_type = s_id & 0xf00
        if s_type == 0x200: # TEXT
            flat.createLabel(text_start.add(s_addr), s_name, False)
        elif s_type == 0x400: # DATA
            flat.createLabel(data_start.add(s_addr), s_name, False)
        elif s_type == 0x100: # BSS
            flat.createLabel(bss_start.add(s_addr),  s_name, False)
        else: # unsupported type
            pass

# Add some labels
flat.createDwords(start.add(0x2), 4)
flat.createLabel(start.add(0x2), "TEXT_LEN", True)
flat.createLabel(start.add(0x6), "DATA_LEN", True)
flat.createLabel(start.add(0xa), "BSS_LEN", True)
flat.createLabel(start.add(0xe), "SYM_LEN", True)
flat.createLabel(text_start, "ENTRY_POINT", True)

# Run disassembler on entry point
flat.disassemble(text_start)

# Open for user to see and to start analyzing
program.endTransaction(txn, True)
openProgram(program)

# ALIS / OPCODES
alis_jtab_opcodes_addr = start.getNewAddress(alis_jtab_opcodes)
for opcode in range(0, alis_jtab_opcodes_len / 2):
    # read big endian word at address (alis_jtab_opcodes + code)
    print("Opcode: " + hex(opcode))
    offset_addr = start.getNewAddress(alis_jtab_opcodes + (opcode * 2))
    print("Offset addr: " + offset_addr.toString())
    offset = mem.getShort(offset_addr, True)
    print("Offset value: " + hex(offset))
    opcode_addr = start.getNewAddress(alis_jtab_opcodes + offset)
    print("Opcode addr: " + opcode_addr.toString())
    function_name = "OPCODE_" + alis_jtab_opcodes_names[opcode].upper() + "_" + hex(opcode)
    print("Creating function: " + function_name + " at addr $" + opcode_addr.toString())
    print("----------------------------------")
    createFunction(opcode_addr, function_name)

# ALIS / OPERNAMES
alis_jtab_opernames_addr = start.getNewAddress(alis_jtab_opernames)
for opername in range(0, alis_jtab_opernames_len / 2):
    # read big endian word at address
    print("Opername: " + hex(opername))
    offset_addr = start.getNewAddress(alis_jtab_opernames + (opername * 2))
    print("Offset addr: " + offset_addr.toString())
    offset = mem.getShort(offset_addr, True)
    print("Offset value: " + hex(offset))
    opername_addr = start.getNewAddress(alis_jtab_opernames + offset)
    print("Opername addr: " + opername_addr.toString())
    function_name = "OPERNAME_" + alis_jtab_opernames_names[opername].upper() + "_" + hex(opername)
    print("Creating function: " + function_name + " at addr $" + opername_addr.toString())
    print("----------------------------------")
    createFunction(opername_addr, function_name)

# ALIS / STORENAMES
alis_jtab_storenames_addr = start.getNewAddress(alis_jtab_storenames)
for storename in range(0, alis_jtab_storenames_len / 2):
    # read big endian word at address
    print("Storename: " + hex(storename))
    offset_addr = start.getNewAddress(alis_jtab_storenames + (storename * 2))
    print("Offset addr: " + offset_addr.toString())
    offset = mem.getShort(offset_addr, True)
    print("Offset value: " + hex(offset))
    storename_addr = start.getNewAddress(alis_jtab_storenames + offset)
    print("Storename addr: " + storename_addr.toString())
    function_name = "STORENAME_" + alis_jtab_storename_names[storename].upper() + "_" + hex(storename)
    print("Creating function: " + function_name + " at addr $" + storename_addr.toString())
    print("----------------------------------")
    createFunction(storename_addr, function_name)

# ALIS / addnameS
alis_jtab_addnames_addr = start.getNewAddress(alis_jtab_addnames)
for addname in range(0, alis_jtab_addnames_len / 2):
    # read big endian word at address
    print("Addname: " + hex(addname))
    offset_addr = start.getNewAddress(alis_jtab_addnames + (addname * 2))
    print("Offset addr: " + offset_addr.toString())
    offset = mem.getShort(offset_addr, True)
    print("Offset value: " + hex(offset))
    addname_addr = start.getNewAddress(alis_jtab_addnames + offset)
    print("Addname addr: " + addname_addr.toString())
    function_name = "ADDNAME_" + alis_jtab_addnames_names[addname].upper() + "_" + hex(addname)
    print("Creating function: " + function_name + " at addr $" + addname_addr.toString())
    print("----------------------------------")
    createFunction(addname_addr, function_name)
