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

# load sprite(game character)
character = pygame.image.load("/Users/terman/dev/cs-study/python/pygame_basic/character.png")
character_size = character.get_rect().size # 캐릭터 이미지 사이즈 구하기
character_width = character_size[0] # 캐릭터의 가로 크기
character_height = character_size[1] # 캐릭터의 세로 크기
character_x_pos = (screen_width / 2) - (character_width / 2) # 화면 가로의 1/2 크기에 해당하는 곳에 위치(가로, 화면 중앙)
character_y_pos = screen_height - character_height # 화면 세로크기 가장 아래에 해당하는 곳에 위치(세로)

#이벤트 루프
running = True # 게임이 진행중인지
while running:
    for event in pygame.event.get(): # 어떤 이벤트가 발생하였는지
        if event.type == pygame.QUIT: # 창이 닫히는 이벤트가 발생하였는지
            running = False # 게임이 진행중이 아님

    screen.blit(background, (0, 0)) # 배경 그리기
    screen.blit(character, (character_x_pos, character_y_pos)) # 캐릭터 그리기

    pygame.display.update() # 게임화면 그리기(반복해서 그리기)


# pygame 종료
pygame.quit()