"""
使用说明
串口发送16进制数据，爆头0x2C,包尾0x5B,中间117个0或1或2，对应113个位置信息，摄像头视角从左到右，从上到下
串口接收16进制数据。包头0xFF，没有包尾
第一位1，给摄像头初步定位
    1退出初步定位
    2检测棋盘范围

    3发送棋盘状态
    4初始化
注意：给摄像头初步定位，分辨率是160×120，lcd屏会显示多条横纵线，让棋盘在lcd屏上四条边都平行或者垂直，
退出定位后分辨路改为640×480，lcd只能显示左上角区域。lcd左上角出现“ok”才可以发送棋盘状态
"""

import pyb
from pyb import LED
import sensor, image, time,display, ustruct
from pyb import UART

# LED(1).on()
# LED(1).off()
LED(2).on()
# LED(2).off()
# LED(3).on()
# LED(3).off()

sensor.reset()
sensor.set_pixformat(sensor.RGB565)  # 灰度更快(160x120 max on OpenMV-M7)
sensor.set_framesize(sensor.VGA)
sensor.skip_frames(time=500)
lcd = display.SPIDisplay()
clock = time.clock()
uart = UART(3, 115200)  # OpenMV RT 注释掉这一行，用下一行UART(1)，P4(TX)，P5(RX)
uart.init(115200, bits=8, parity=None, stop=1)


# 全局标志变量用于主循环处理
received_data = None



def uart_callback(line):
    global received_data
    if uart.any():
        received_data = uart.read()  # 使用外部定义的uart实例
        if(received_data[0] == 0xFF):
            received_data = received_data
        else:
            received_data = None
        print(received_data)
uart.irq(trigger=UART.IRQ_RXIDLE, handler=uart_callback)  # 当数据到达时触发

#########定义摄像头初步定位########
def Preliminary_positioning():

    if(sensor.get_pixformat() != sensor.QQVGA2):
        sensor.set_framesize(sensor.QQVGA2)
        # sensor.skip_frames(time=500)
    img = sensor.snapshot().lens_corr(strength=1.6, zoom=1.0)
    # 绘制横线（水平方向）
    for y in range(10, 151, 20):  # y从15到150，间隔10（150是160边缘前10）
        img.draw_line((15, y, 115, y), color=(0, 255, 0))  # x从10到110（避开左右边缘）

    # 绘制纵线（垂直方向）
    for x in range(15, 116, 20):  # x从10到110，间隔10（110是120边缘前10）
        img.draw_line((x, 10, x, 150), color=(0, 255, 0))  # y从10到150（避开上下边缘）
    lcd.write(img)  # LCD显示图像。

#########定义棋盘四周检测########
def find_boundary_lines():
    # 定义角度阈值
    HORIZONTAL_THRESH = 15  # ±15度内视为水平线
    VERTICAL_THRESH = 15  # ±15度内视为垂直线

    # 初始化边界线
    top_line = bottom_line = left_line = right_line = None
    top_y = float('inf')  # 初始最小Y值（最上）
    bottom_y = 0  # 初始最大Y值（最下）
    left_x = float('inf')  # 初始最小X值（最左）
    right_x = 0  # 初始最大X值（最右）

    for i in range(20):
        while (1):
            clock.tick()
            img = sensor.snapshot().lens_corr(strength=1.6, zoom=1.0)
            thresholds = (0, 39, -18, 22, -28, 14)
            img.binary([thresholds])
            for l in img.find_lines(threshold=13000, theta_margin=5, rho_margin=5):
                theta = l.theta()
                # 水平线检测
                if (abs(theta - 90) < HORIZONTAL_THRESH):
                    # 计算线段中点Y坐标
                    y_mid = (l.y1() + l.y2()) // 2
                    # 更新最上横线
                    if y_mid < top_y:
                        top_line = l
                        top_y = y_mid
                    # 更新最下横线
                    if y_mid > bottom_y:
                        bottom_line = l
                        bottom_y = y_mid
                    img.draw_line(l.line(), color=(255, 0, 255))

                # 垂直线检测
                elif (theta < VERTICAL_THRESH) or theta > (180 - VERTICAL_THRESH):
                    # 计算线段中点X坐标
                    x_mid = (l.x1() + l.x2()) // 2
                    # 更新最左竖线
                    if x_mid < left_x:
                        left_line = l
                        left_x = x_mid
                    # 更新最右竖线
                    if x_mid > right_x:
                        right_line = l
                        right_x = x_mid
                    img.draw_line(l.line(), color=(0, 255, 255))

            # 绘制检测到的边界线
            if top_line:
                img.draw_line(top_line.line(), color=(0, 255, 0))  # 上横线 - 绿色
            if bottom_line:
                img.draw_line(bottom_line.line(), color=(0, 0, 255))  # 下横线 - 蓝色
            if left_line:
                img.draw_line(left_line.line(), color=(255, 0, 0))  # 左竖线 - 红色
            if right_line:
                img.draw_line(right_line.line(), color=(255, 255, 0))  # 右竖线 - 黄色

            # 当检测到所有边界线时退出
            if top_line and bottom_line and left_line and right_line:
                y=bottom_y-top_y
                x=right_x-left_x
                # print(x,y,x/y)
                if(y!=0):
                    if(1.2<x/y<1.8):
                        break
    return top_y ,bottom_y,left_x,right_x

#########定义棋盘顶点检测########
def Chessboard_rotation():
    max_rect = None  # 用来存储最大矩形
    max_area_found = 0  # 最大矩形的面积
    # 设置中间区域的限制
    frame_width = 640  # 图像宽度
    frame_height = 480  # 图像高度
    center_x = frame_width // 2
    center_y = frame_height // 2
    center_width = 160  # 中心区域宽度
    center_height = 120  # 中心区域高度
    # 设置最小和最大面积，以排除噪声区域
    min_area = 20000
    max_area = 200000
    # 设置允许的宽高比范围，接近正方形的矩形
    min_aspect_ratio = 0.6
    max_aspect_ratio = 1.4
    for i in range(20):
        while(1):
            clock.tick()
            img = sensor.snapshot().lens_corr(strength = 1.6, zoom = 1.0)
            thresholds = (1, 42, -11, 11, 1, 40)
            img.binary([thresholds])
            img.draw_string(0, 0, "ing...1", color=(0, 255, 0),scale=1,x_spacing=-2)
            roi100 = [0, 0, 640, 480]
            for r in img.find_rects(roi100, threshold=20000):
                x, y, w, h = r.rect()  # 获取矩形的x, y, 宽度和高度
                area = w * h  # 计算矩形面积
                # 计算宽高比，如果接近正方形，则认为符合条件
                aspect_ratio = max(w, h) / min(w, h)
                # 计算矩形中心点坐标
                rect_center_x = x + w // 2
                rect_center_y = y + h // 2
                # 限制矩形在图像中心区域
                if (center_x - center_width // 2 <= rect_center_x <= center_x + center_width // 2) and \
                   (center_y - center_height // 2 <= rect_center_y <= center_y + center_height // 2):
                    # 仅选择面积在指定范围内且接近正方形的矩形
                    if min_area <= area <= max_area and  min_aspect_ratio < aspect_ratio < max_aspect_ratio:
                        if area > max_area_found:
                            max_area_found = area  # 更新最大面积
                            max_rect = r  # 更新最大矩形
            # 如果找到了最大矩形，则绘制并输出其信息
            if max_rect:
                for p in r.corners():
                    img.draw_circle(p[0], p[1], 5, color=(0, 255, 0))  # 绘制圆点
                x, y, w, h = max_rect.rect()  # 获取矩形的坐标和尺寸4.
                print(x, y, w, h)
                h = int(0.5775*h)
                img.draw_rectangle(x, y, w, h, color=(255, 0, 0))  # 绘制红色矩形框
                rrr = r.corners()
                break
            lcd.write(img)  # LCD显示图像。
    return rrr,x, y, w, h

#########定义位置检测########
def detect_piece(img, x, y, position):
    # 这部分显示数据
    if(last_stable_result == None):
        img.draw_string(0, 0, "ing...2", color=(255, 0, 0),scale=1,x_spacing=-2)
    elif(last_stable_result != None):
        img.draw_string(0, 0, "ok", color=(0, 255, 0),scale=1,x_spacing=-2)

    c = 40 # 检测框边长
    white_threshold = [75, 100, -29, -1, -23, 3]
    black_threshold = [0, 24, -21, 4, -23, 12]
    roi = (int(x - c / 2), int(y - c / 2), c, c)
    blobs51 = img.find_blobs([white_threshold], roi=roi, x_stride=25, y_stride=25, invert=False,
                            area_threshold=900,pixels_threshold=700, merge=True)
    blobs52 = img.find_blobs([black_threshold], roi=roi, x_stride=25, y_stride=25, invert=False,
                            area_threshold=1100,pixels_threshold=800, merge=True)
    img.draw_rectangle(roi, color=(0, 0, 255))
    img.draw_string(int(x), int(y), str(position), color=(255, 255, 255),scale=1,x_spacing=-4)
    if blobs51:
        for b in blobs51:
            img.draw_rectangle(b[0:4], color=(0, 0, 0),thickness=1)
            img.draw_cross(b[5], b[6], color=(0, 0, 0),thickness=1)
        return 1
    elif blobs52:
        for b in blobs52:
            img.draw_rectangle(b[0:4], color=(255, 255, 255),thickness=1)
            img.draw_cross(b[5], b[6], color=(255, 255, 255),thickness=1)
        return 2
    else:
        return 0

#########定义棋盘感知########
def Perceived_chessboard(top_y ,bottom_y,left_x,right_x):
    clock.tick()
    img = sensor.snapshot().lens_corr(strength = 1.6, zoom = 1.0)
    top_left_x = left_x     # 左上角x坐标
    top_left_y = top_y     # 左上角y坐标
    bottom_right_x = right_x  # 右下角x坐标
    bottom_right_y = bottom_y  # 右下角y坐标
    # 交叉点数量（行和列）
    cross_rows = 9     # 交叉点行数
    cross_cols = 13     # 交叉点列数

    # c1=int([(bottom_y-top_y)/(cross_rows-1) + (right_x-left_x)/(cross_cols-1)]/2-2)

    # 计算每个点的间隔
    x_interval = (bottom_right_x - top_left_x) / (cross_cols - 1)
    y_interval = (bottom_right_y - top_left_y) / (cross_rows - 1)
    number_d = []
    position = 1
    for i in range(cross_rows):
        for j in range(cross_cols):
            # 计算交叉点坐标
            x = top_left_x + j * x_interval
            y = top_left_y + i * y_interval
            d = detect_piece(img, x, y, position)
            number_d.append(d)
            position += 1
    lcd.write(img)  # LCD显示图像。
    return number_d


#########定义检测滤波########
def filtering(top_y ,bottom_y,left_x,right_x):
    global filter_buffer, last_stable_result  # 声明使用全局变量
    # 滤波器参数
    FILTER_LENGTH = 5  # 连续相同结果的次数
    # 获取当前检测结果
    current_result = Perceived_chessboard(top_y ,bottom_y,left_x,right_x)
    # print(f"当前检测结果: {current_result}")
    # 更新滤波器缓冲区
    filter_buffer.append(current_result)
    # 保持缓冲区长度固定
    if len(filter_buffer) > FILTER_LENGTH:
        filter_buffer.pop(0)
    # 检查是否连续FILTER_LENGTH次结果相同
    if len(filter_buffer) == FILTER_LENGTH:
        all_same = True
        for i in range(1, FILTER_LENGTH):
            if filter_buffer[i] != filter_buffer[0]:
                all_same = False
                break
        if all_same:
            stable_result = filter_buffer[0]
            # 只有当稳定结果变化时才输出
            if stable_result != last_stable_result:
                print(f"稳定检测结果: {stable_result}")
                last_stable_result = stable_result
    return last_stable_result

#########验证棋盘范围########
def Verify_chessboard(top_y ,bottom_y,left_x,right_x):
    img = sensor.snapshot().lens_corr(strength = 1.6, zoom = 1.0)
    # 输出
    a=[0,0,0,0]
    # 边框阈值
    frame_threshold = (0, 77, -23, 26, -18, 30)
    # 整体宽高，中点
    long_1 = right_x - left_x # 宽
    long_2 = bottom_y - top_y # 高
    midpoint_x = (left_x + right_x)*0.5 # 上下边中点
    midpoint_y = (top_y + bottom_y)*0.5 # 左右边中点
    # 检测宽度
    Detection_width = int((long_1/12)/2) # 宽度为半格
    # 4条边检测区
    roi_top_y = [int(midpoint_x - long_1 / 2), int(top_y - Detection_width / 2), long_1, Detection_width]
    roi_bottom_y = [int(midpoint_x - long_1 / 2), int(bottom_y - Detection_width / 2), long_1, Detection_width]
    roi_left_x = [int(left_x - Detection_width / 2), int(midpoint_y - long_2 / 2), Detection_width, long_2]
    roi_right_x = [int(right_x - Detection_width / 2), int(midpoint_y - long_2 / 2), Detection_width, long_2]
    # 开始检测
    blobs_top_y = img.find_blobs([frame_threshold], roi=roi_top_y, x_stride=160, y_stride=2, invert=False,
                             area_threshold=5000, pixels_threshold=3000, merge=True)
    blobs_bottom_y = img.find_blobs([frame_threshold], roi=roi_bottom_y, x_stride=160, y_stride=2, invert=False,
                                 area_threshold=5000, pixels_threshold=3000, merge=True)
    blobs_left_x = img.find_blobs([frame_threshold], roi=roi_left_x, x_stride=2, y_stride=100, invert=False,
                                    area_threshold=4000, pixels_threshold=2500, merge=True)
    blobs_right_x = img.find_blobs([frame_threshold], roi=roi_right_x, x_stride=2, y_stride=100, invert=False,
                                  area_threshold=4000, pixels_threshold=2500, merge=True)

    img.draw_rectangle(roi_top_y, color=(0, 0, 255))
    img.draw_rectangle(roi_bottom_y, color=(0, 0, 255))
    img.draw_rectangle(roi_left_x, color=(0, 0, 255))
    img.draw_rectangle(roi_right_x, color=(0, 0, 255))
    img.draw_string(int(midpoint_x), int(top_y), str('top_y'), color=(255, 255, 255),scale=1,x_spacing=-3)
    img.draw_string(int(midpoint_x), int(bottom_y), str('bottom_y'), color=(255, 255, 255),scale=1,x_spacing=-3)
    img.draw_string(int(left_x), int(midpoint_y), str('left_x'), color=(255, 255, 255),scale=1,x_spacing=-3)
    img.draw_string(int(right_x), int(midpoint_y), str('right_x'), color=(255, 255, 255),scale=1,x_spacing=-3)

    if blobs_top_y:
        a[0]=1
        for b in blobs_top_y:
            img.draw_rectangle(b[0:4], color=(255, 0, 0), thickness=1)
            img.draw_cross(b[5], b[6], color=(255, 0, 0), thickness=1)
    if blobs_bottom_y:
        a[1] = 1
        for b in blobs_bottom_y:
            img.draw_rectangle(b[0:4], color=(255, 0, 0), thickness=1)
            img.draw_cross(b[5], b[6], color=(255, 0, 0), thickness=1)
    if blobs_left_x:
        a[2] = 1
        for b in blobs_left_x:
            img.draw_rectangle(b[0:4], color=(255, 0, 0), thickness=1)
            img.draw_cross(b[5], b[6], color=(255, 0, 0), thickness=1)
    if blobs_right_x:
        a[3] = 1
        for b in blobs_right_x:
            img.draw_rectangle(b[0:4], color=(255, 0, 0), thickness=1)
            img.draw_cross(b[5], b[6], color=(255, 0, 0), thickness=1)
    return a

while (True):
    # 用于确定顶点位置
    top_y ,bottom_y,left_x,right_x=None,None,None,None
    # 初始化滤波器缓冲区
    filter_buffer = []
    last_stable_result = None
    a = None
    d = None

    while (True):

        clock.tick()
        top_y,bottom_y,left_x,right_x = 37, 443, 16, 624 # 检测棋盘范围

        if(top_y and bottom_y and left_x and right_x):
            a = filtering(top_y ,bottom_y,left_x,right_x)
        else:
            img = sensor.snapshot().lens_corr(strength = 1.6, zoom = 1.0)
            lcd.write(img)  # LCD显示图像。

            # print(f"长度: {len(a)}")  # 添加此行
        if(a != None):
            d = bytearray([0x2C]) # 打包发送
            for item in a:
                try:
                    num = int(item)
                    d.append(num)
                except ValueError:
                    print(f"警告: 无法将 {item} 转换为整数，已忽略")
            d.append(0x5B)

        if (received_data != None):
            if (received_data[1] == 1):
                received_data= None

                uart.write(bytearray([0x2C,0x5B]))
                while(1):
                    if(received_data):
                        if (received_data[1] == 1):
                            received_data= None
                            sensor.set_framesize(sensor.VGA)
                            break
                    else:
                        Preliminary_positioning()
            elif (received_data[1] == 2):
                received_data= None
                top_y,bottom_y,left_x,right_x = find_boundary_lines() # 检测棋盘范围
            elif (received_data[1] == 3 and d):
                received_data = None
                print(d)
                uart.write(d) # 发送棋盘状态
            elif (received_data[1] == 4):
                break


