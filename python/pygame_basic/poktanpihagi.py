import pygame #파이 게임 모듈 임포트
import random

pygame.init() #파이 게임 초기화
SCREEN_WIDTH = 480
SCREEN_HEIGHT = 640
pygame.display.set_caption('똥피하기') # Game title
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT)) #화면 크기 설정
clock = pygame.time.Clock() 

game_font = pygame.font.Font(None, 40) # 폰트 객체 생성(폰트, 크기)
count = 0

#변수
BLACK = (0, 0, 0)
RED = (255, 0, 0)
YELLOW = (255, 255, 0)

background_image = pygame.image.load("/Users/terman/dev/cs-study/python/pygame_basic/background.jpg")

ddong_image = pygame.image.load('/Users/terman/dev/cs-study/python/pygame_basic/ddong.png')
ddongs = []
for i in range(10):
    rect = ddong_image.get_rect()
    rect.left = random.randint(0, SCREEN_WIDTH - rect.width)
    rect.top = -100
    dy = random.randint(3, 8)
    ddongs.append({'rect': rect, 'dy': dy})

person_image = pygame.image.load('/Users/terman/dev/cs-study/python/pygame_basic/person.png')
person_rect = pygame.Rect(person_image.get_rect())
person = person_rect.inflate(5, 5)
person.left = SCREEN_WIDTH / 2 - person.width / 2
person.top = SCREEN_HEIGHT - person.height
person_dx = 0
person_dy = 0
running = True

while running: #게임 루프
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

    for ddong in ddongs:
        ddong['rect'].top += ddong['dy']
        if ddong['rect'].top > SCREEN_HEIGHT:
            count += 1
            ddongs.remove(ddong)
            rect = pygame.Rect(ddong_image.get_rect())
            rect.left = random.randint(0, SCREEN_WIDTH)
            rect.top = -100
            dy = random.randint(3, 9)
            ddongs.append({'rect': rect, 'dy': dy})

    person.left = person.left + person_dx
    if person.left < 0:
        person.left = 0
    elif person.left > SCREEN_WIDTH - person.width:
        person.left = SCREEN_WIDTH - person.width

    #화면 그리기
    for ddong in ddongs:
        screen.blit(ddong_image, ddong['rect'])
        # 충돌 조건
        if person.top + 10 <= ddong['rect'].bottom and person.top + ((person.bottom - person.top) / 2) > ddong['rect'].top:
            if person.left + 13 <= ddong['rect'].right and person.right >= ddong['rect'].left + 13:
                print("충돌!")
                running = False

    screen.blit(person_image, person)
    counter = game_font.render(str(int(count)), True, (0, 0, 0))
    # 출력할 글자, Ture, 글자색상(RGB)
    screen.blit(counter, (10, 10))

    pygame.display.update() #모든 화면 그리기 업데이트
    clock.tick(30) #30 FPS (초당 프레임 수) 를 위한 딜레이 추가, 딜레이 시간이 아닌 목표로 하는 FPS 값

# pygame 종료
pygame.quit()