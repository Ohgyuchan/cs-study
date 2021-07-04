import pygame
from pygame.constants import K_RIGHT

pygame.init() # 초기화(required)

# 화면 크기 설정
screen_width = 480
screen_height = 640
screen = pygame.display.set_mode((screen_width, screen_height))

# 화면 타이틀 설정
pygame.display.set_caption('Gyuchan\'s Game') # Game title

# FPS
clock = pygame.time.Clock()

# load backgournd Image
background = pygame.image.load("/Users/terman/dev/cs-study/python/pygame_basic/background.png")

# load sprite(game character)
character = pygame.image.load("/Users/terman/dev/cs-study/python/pygame_basic/character.png")
character_size = character.get_rect().size # 캐릭터 이미지 사이즈 구하기
character_width = character_size[0] # 캐릭터의 가로 크기
character_height = character_size[1] # 캐릭터의 세로 크기
character_x_pos = (screen_width / 2) - (character_width / 2) # 화면 가로의 1/2 크기에 해당하는 곳에 위치(가로, 화면 중앙)
character_y_pos = screen_height - character_height # 화면 세로크기 가장 아래에 해당하는 곳에 위치(세로)

# 좌표 이동
to_x = 0
to_y = 0

# 이동 속도
charater_speed = 0.6

# enemy 캐릭터
enemy = pygame.image.load("/Users/terman/dev/cs-study/python/pygame_basic/enemy.png")
enemy_size = enemy.get_rect().size # 캐릭터 이미지 사이즈 구하기
enemy_width = enemy_size[0] # 캐릭터의 가로 크기
enemy_height = enemy_size[1] # 캐릭터의 세로 크기
enemy_x_pos = (screen_width / 2) - (enemy_width / 2) # 화면 가로의 1/2 크기에 해당하는 곳에 위치(가로, 화면 중앙)
enemy_y_pos = (screen_height / 2) - (enemy_height / 2) # 화면 세로크기 가장 아래에 해당하는 곳에 위치(세로)

# 폰트 정의
game_font = pygame.font.Font(None, 40) # 폰트 객체 생성(폰트, 크기)

# 총 시간
total_time = 10

# 시작 시간
start_ticks = pygame.time.get_ticks() # 시작 tick을 받아옴


#이벤트 루프
running = True # 게임이 진행중인지
while running:
    dt = clock.tick(60) # 게임화면의 초당 프레임 수 설정
    
    for event in pygame.event.get(): # 어떤 이벤트가 발생하였는지
        if event.type == pygame.QUIT: # 창이 닫히는 이벤트가 발생하였는지
            running = False # 게임이 진행중이 아님
        
        if event.type == pygame.KEYDOWN: # 키가 눌러졌는지 확인
            if event.key == pygame.K_LEFT:
                to_x -= charater_speed
            elif event.key == pygame.K_RIGHT:
                to_x += charater_speed
            elif event.key == pygame.K_UP:
                to_y -= charater_speed
            elif event.key == pygame.K_DOWN:
                to_y += charater_speed

        if event.type == pygame.KEYUP: # 키가 방향키를 떼면 멈춤
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                to_x = 0
            elif event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                to_y = 0

    character_x_pos += to_x * dt # 프레임에 따른 이동값 조정
    character_y_pos += to_y * dt

    # 가로 경계
    if character_x_pos < 0:
        character_x_pos = 0
    elif character_x_pos > screen_width - character_width:
        character_x_pos = screen_width - character_width

    # 세로 경계
    if character_y_pos < 0:
        character_y_pos = 0
    elif character_y_pos > screen_height - character_height:
        character_y_pos = screen_height - character_height

    # 충돌 처리를 위한 rect 정보 업데이트
    character_rect = character.get_rect()
    character_rect.left = character_x_pos
    character_rect.top = character_y_pos

    enemy_rect = enemy.get_rect()
    enemy_rect.left = enemy_x_pos
    enemy_rect.top = enemy_y_pos

    # 충돌 체크
    if character_rect.colliderect(enemy_rect):
        print("충돌!")
        running = False

    screen.blit(background, (0, 0)) # 배경 그리기
    screen.blit(character, (character_x_pos, character_y_pos)) # 캐릭터 그리기
    screen.blit(enemy, (enemy_x_pos, enemy_y_pos)) # enemy 캐릭터 그리기

    # 타이머 집어 넣기
    # 경과 시간 계산
    # 경과시간(ms)dmf 1000으로 나누어서 초(s) 단위로 표시
    elapsed_time = (pygame.time.get_ticks() - start_ticks) / 1000
    
    
    timer = game_font.render(str(int(total_time - elapsed_time)), True, (255, 255, 255))
    # 출력할 글자, Ture, 글자색상(RGB)
    screen.blit(timer, (10, 10))

    # 만약 시간이 0 이하이면 게임 종료
    if total_time - elapsed_time <= 0:
        print("타임아웃")
        running = False

    # 잠시 대기
    pygame.time.delay(2000) # 2초 대기(2000ms)

    pygame.display.update() # 게임화면 그리기(반복해서 그리기)


# pygame 종료
pygame.quit()