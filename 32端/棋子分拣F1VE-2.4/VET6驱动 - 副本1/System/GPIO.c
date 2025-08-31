#include "Headfile.h"

void GPIOx_Init(uint8_t GPIOx, uint8_t GPIOxMode, uint8_t Px_num)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_TypeDef* GPIOx_Port = 0;
    uint32_t RCC_APB2Periph_GPIOx = 0;

    // 有效性检查
    if(Px_num > 15) return;  // 引脚号超出范围

    // 选择GPIO端口
    switch(GPIOx)
    {
        case PA:
            GPIOx_Port = GPIOA;
            RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOA;
            break;
        case PB:
            GPIOx_Port = GPIOB;
            RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOB;
            break;
        case PC:
            GPIOx_Port = GPIOC;
            RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOC;
            break;
        case PD:
            GPIOx_Port = GPIOD;
            RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOD;
            break;
        case PE:
            GPIOx_Port = GPIOE;
            RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOE;
            break;
        default:
            return;  // 无效的GPIO端口
    }

    // 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);

    // 配置GPIO模式
    switch(GPIOxMode)
    {
        case PP:  // 推挽输出
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            break;
        
        case AIN: // 模拟输入
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            break;
        
        case IPU: // 上拉输入
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            break;
		
        case AFPP: // 上拉输入
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            break;
		
        default: break;
    }

    // 设置引脚并初始化
    GPIO_InitStructure.GPIO_Pin = (uint16_t)(1 << Px_num);
    GPIO_Init(GPIOx_Port, &GPIO_InitStructure);
}

/*使用示例：

// 初始化PA1为推挽输出
GPIOx_Init(PA, PP, 1);

// 初始化PB12为上拉输入
GPIOx_Init(PB, IPU, 12);

// 初始化PC5为模拟输入
GPIOx_Init(PC, AIN, 5);


*/
