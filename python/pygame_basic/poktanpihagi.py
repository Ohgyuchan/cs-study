import pygame #파이 게임 모듈 임포트
import random

pygame.init() #파이 게임 초기화
SCREEN_WIDTH = 480
SCREEN_HEIGHT = 640
pygame.display.set_caption('똥피하기') # Game title
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT)) #화면 크기 설정
clock = pygame.time.Clock() 

#변수
BLACK = (0, 0, 0)
RED = (255, 0, 0)
YELLOW = (255, 255, 0)

background_image = pygame.image.load("/Users/terman/dev/cs-study/python/pygame_basic/background.jpg")

bomb_image = pygame.image.load('/Users/terman/dev/cs-study/python/pygame_basic/ddong.png')
bombs = []
for i in range(30):
    rect = pygame.Rect(bomb_image.get_rect())
    rect.left = random.randint(0, SCREEN_WIDTH)
    rect.top = -100
    dy = random.randint(3, 9)
    bombs.append({'rect': rect, 'dy': dy})

person_image = pygame.image.load('/Users/terman/dev/cs-study/python/pygame_basic/person.png')
person = pygame.Rect(person_image.get_rect())
person.left = SCREEN_WIDTH // 2 - person.width // 2
person.top = SCREEN_HEIGHT - person.height
person_dx = 0
person_dy = 0

while True: #게임 루프
    screen.blit(background_image, (0, 0)) #단색으로 채워 화면 지우기

    #변수 업데이트

    event = pygame.event.poll() #이벤트 처리
    if event.type == pygame.QUIT:
        break
    elif event.type == pygame.KEYDOWN:
        if event.key == pygame.K_LEFT:
            person_dx = -5
        elif event.key == pygame.K_RIGHT:
            person_dx = 5
    elif event.type == pygame.KEYUP:
        if event.key == pygame.K_LEFT:
            person_dx = 0
        elif event.key == pygame.K_RIGHT:
            person_dx = 0

    for bomb in bombs:
        bomb['rect'].top += bomb['dy']
        if bomb['rect'].top > SCREEN_HEIGHT:
            bombs.remove(bomb)
            rect = pygame.Rect(bomb_image.get_rect())
            rect.left = random.randint(0, SCREEN_WIDTH)
            rect.top = -100
            dy = random.randint(3, 9)
            bombs.append({'rect': rect, 'dy': dy})

    person.left = person.left + person_dx

    if person.left < 0:
        person.left = 0
    elif person.left > SCREEN_WIDTH - person.width:
        person.left = SCREEN_WIDTH - person.width

    #화면 그리기

    for bomb in bombs:
        screen.blit(bomb_image, bomb['rect'])

    screen.blit(person_image, person)

    pygame.display.update() #모든 화면 그리기 업데이트
    clock.tick(30) #30 FPS (초당 프레임 수) 를 위한 딜레이 추가, 딜레이 시간이 아닌 목표로 하는 FPS 값
