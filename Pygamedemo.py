import sys, pygame
pygame.init()

black = 0,0,0
size = width, height = 1280, 800
screen = pygame.display.set_mode(size)
LEFT = 1
RECORDEVENT = 5
theDrawing = []

while True:
	for event in pygame.event.get():
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
