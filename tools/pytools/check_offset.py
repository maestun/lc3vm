import glob

def list_offsets(folder):
    files = glob.glob(folder)
    ids = {}
    for file in files:
        f = open(file, "rb")
        bytes = f.read()
        offset = (bytes[8] << 8) + bytes[9]
        id = (bytes[0] << 8) + bytes[1]
        ids[id] = file
        print("" + file + ":")
        print("ID:" + hex(id) + " OFFSET:" + hex(offset))
        f.close()

list_offsets("/Users/developer/dev/perso/macos/alis/data/ishar/atari/depack/*.AO")