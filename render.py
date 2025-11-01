import mmap
import os
from PIL import Image  

def getPixValue(char):
    if char == '0':
        return (0,0,0,255)
    elif char == '1':
        return (255,0,0,255)
    elif char == '2':
        return (0,255,0,255)
    elif char == '3':
        return (255,255,0,255)
    elif char == '4':
        return (255,0,255,255)
    elif char == '5':
        return (0,255,255,255)
    return (100,100,100,255)


# Open the file (use O_RDWR for read/write access)
with open("tacsy.buff", "r+b") as f:
    # Get the file size (use this for buffer size)
    size = os.fstat(f.fileno()).st_size
    
    # Map the file into memory
    buf = mmap.mmap(f.fileno(), size)
    
    # Write to the buffer (e.g., 4 bytes)
    # buf[0:2] = b'AB'
    
    # Read from the buffer
    # print(buf[0:2].decode())  # Output: 'AB'



    width = 400
    height = 300


    img  = Image.new( mode = "RGB", size = (width, height), color = (0,0,0) )
    
    for i in range(height):
        for j in range(width):
            img.putpixel( (j, i), getPixValue(chr(buf[j+i*(width+1)])) )
        # print(chr(buf[j+i*width]))
    img.save("testtemp.png")