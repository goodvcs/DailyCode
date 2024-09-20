import pygame
import os

# 初始化pygame
pygame.init()

# 定义颜色
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)

# 屏幕尺寸
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 400
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Super Mario')

# 加载背景图像（替换为你自己的背景路径）
background = pygame.image.load(os.path.join('background.png'))
background = pygame.transform.scale(background, (SCREEN_WIDTH, SCREEN_HEIGHT))

# 定义角色属性
mario_width = 40
mario_height = 60
mario_x = 50
mario_y = SCREEN_HEIGHT - mario_height - 50  # 地面高度
mario_speed_x = 0
mario_speed_y = 0
jump = False
gravity = 1  # 重力

# 游戏循环控制
running = True
clock = pygame.time.Clock()

# 主循环
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        # 检测按键按下
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                mario_speed_x = -5
            if event.key == pygame.K_RIGHT:
                mario_speed_x = 5
            if event.key == pygame.K_SPACE and not jump:  # 仅允许在地面上跳跃
                mario_speed_y = -15
                jump = True

        # 检测按键松开
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                mario_speed_x = 0

    # 更新角色位置
    mario_x += mario_speed_x
    mario_y += mario_speed_y

    # 限制马里奥在屏幕内
    if mario_x < 0:
        mario_x = 0
    if mario_x > SCREEN_WIDTH - mario_width:
        mario_x = SCREEN_WIDTH - mario_width

    # 应用重力
    if jump:
        mario_speed_y += gravity
    if mario_y >= SCREEN_HEIGHT - mario_height - 50:  # 当角色到达地面
        mario_y = SCREEN_HEIGHT - mario_height - 50
        jump = False
        mario_speed_y = 0

    # 绘制背景
    screen.fill(WHITE)
    screen.blit(background, (0, 0))

    # 绘制角色
    pygame.draw.rect(screen, BLUE, [mario_x, mario_y, mario_width, mario_height])

    # 更新显示
    pygame.display.flip()

    # 设置帧率
    clock.tick(30)

# 退出游戏
pygame.quit()
