import sys, pygame
pygame.init()

black = 0,0,0
RED =   (255,   0,   0)
WHITE = (255,255,255)
BLACK = (0,0,0)
size = width, height = 400, 300
screen = pygame.display.set_mode(size)
#screen.fill(WHITE)
LEFT = 1
RIGHT = 3
MID = 2
RECORDEVENT = 5
theDrawing = []
down = 0
lastx = 0
lasty = 0


while True:
	for event in pygame.event.get():
		
		screen.fill(WHITE)
		x,y = pygame.mouse.get_pos()
		#theDrawing.append((x,y))
		if event.type == pygame.MOUSEBUTTONDOWN and event.button == RIGHT:
			theDrawing = []
		if event.type == pygame.MOUSEBUTTONDOWN and event.button == LEFT:
			down = 1
			x,y = pygame.mouse.get_pos()
		if down == 1:
			#pygame.draw.line(screen,BLACK,[lastx, lasty], [x,y],8)
			#lastx = x
			#lasty = y
			theDrawing.append([x,y])
		if event.type == pygame.MOUSEBUTTONUP and event.button == LEFT:
			down = 0
		#for _ in theDrawing:
		if len(theDrawing) > 2:
			pygame.draw.lines(screen,BLACK,False,theDrawing,4)
		pygame.display.flip()
		print(theDrawing)
		
		if event.type == pygame.MOUSEBUTTONDOWN and event.button == MID:
			pygame.image.save(screen, "screenshot.png")
'''		
		if event.type == pygame.QUIT:
			done = True
		elif event.type == pygame.MOUSEMOTION:
			motion = True
			x, y = event.pos
		elif event.type == pygame.MOUSEBUTTONDOWN and event.button == LEFT:
			x, y = event.pos
			del theDrawing[:]
			startRecording = True
			downFlag = True
			shape = "undefinded"
			print(event.type)
			print("location: x=" + str(x) + " y=" + str(y))
		elif event.type == pygame.MOUSEBUTTONUP and event.button == LEFT:
			print("mouse up")
			upFlag = True
			startRecording = False
			#connectpoints(screen, theDrawing)
			#detectline(theDrawing)
		elif event.type == RECORDEVENT and startRecording and motion:
			temp = (x,y)
			theDrawing.append((x,y))
'''
