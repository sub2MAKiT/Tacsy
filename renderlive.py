import pygame
import sys
import mmap
import os
from PIL import Image  

def getPixValue(char):
    if char == '0':
        return (0,0,0)
    elif char == '1':
        return (255,0,0)
    elif char == '2':
        return (0,255,0)
    elif char == '3':
        return (255,255,0)
    elif char == '4':
        return (255,0,255)
    elif char == '5':
        return (0,255,255)
    return (100,100,100)

# Initialize Pygame
pygame.init()

# Set up the screen
screen_width = 400
screen_height = 300
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Pygame Sample")

# Set up colors
BLACK = (0, 0, 0)
RED = (255, 0, 0)


shmid = os.open("/tacsy.buff", os.O_RDWR)
    # Get the file size (use this for buffer size)
# size = os.fstat(f.fileno()).st_size 
st = os.fstat(shmid)

    # Map the file into memory
buf = mmap.mmap(shmid, st.st_size, access=mmap.ACCESS_READ)
    
    # Write to the buffer (e.g., 4 bytes)
    # buf[0:2] = b'AB'
    
    # Read from the buffer
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill(BLACK)

    # Draw the red square
    # pygame.draw.rect(screen, RED, (square_x, square_y, square_size, square_size))

    width = 400
    height = 300
    

    for i in range(height):
        for j in range(width):
            screen.set_at((j, i), getPixValue(chr(buf[j+i*(width+1)])))

    # Update the display
    pygame.display.flip()

    # Cap the frame rate
    pygame.time.Clock().tick(60)

# Quit Pygame
pygame.quit()
sys.exit()