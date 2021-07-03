import pygame

pygame.init() # 초기화(required)

# 화면 크기 설정
screen_width = 480
screen_height = 640
screen = pygame.display.set_mode((screen_width, screen_height))

# 화면 타이틀 설정
pygame.display.set_caption('Gyuchan\'s Game') # Game title

# load backgournd Image
background = pygame.image.load("/Users/terman/dev/cs-study/python/pygame_basic/background.png")

#이벤트 루프
running = True # 게임이 진행중인지
while running:
    for event in pygame.event.get(): # 어떤 이벤트가 발생하였는지
        if event.type == pygame.QUIT: # 창이 닫히는 이벤트가 발생하였는지
            running = False # 게임이 진행중이 아님

    # background color
    # screen.fill((0, 0, 255))
    screen.blit(background, (0, 0)) # 배경 그리기

    pygame.display.update() # 게임화면 그리기(반복해서 그리기)


# pygame 종료
pygame.quit()