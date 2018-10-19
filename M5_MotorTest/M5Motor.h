#ifndef M5Motor_h_
#define M5Motor_h_

//------------------------------------------
// Moter Driver
//------------------------------------------
#define TB_A1   12  // moterA IN1
#define TB_A2   13  // moterA IN2
#define TB_Ap   0   // moterA PWM
#define TB_B1   2   // moterB IN1
#define TB_B2   16  // moterB IN2
#define TB_Bp   15  // moterB PWM

#endif

/*
//  こんな感じでパラメータを設定して
//
    ledc_channel_config_t ledc_channel[LEDC_TEST_CH_NUM] = {
        {
            .channel    = LEDC_CHANNEL_0,
            .duty       = 0,
            .gpio_num   = LED_GPIO_Red,
            .speed_mode = LEDC_HIGH_SPEED_MODE,
            .timer_sel  = LEDC_TIMER_0
        },
        {
            .channel    = LEDC_CHANNEL_1,
            .duty       = 0,
            .gpio_num   = LED_GPIO_Green,
            .speed_mode = LEDC_HIGH_SPEED_MODE,
            .timer_sel  = LEDC_TIMER_0
        },
        {
            .channel    = LEDC_CHANNEL_2,
            .duty       = 0,
            .gpio_num   = LED_GPIO_Blue,
            .speed_mode = LEDC_HIGH_SPEED_MODE,
            .timer_sel  = LEDC_TIMER_0
        }
    };


// こんな初期化ルーチンを呼び出して、
//
void init_ledc(ledc_channel_config_t *ledc_channel) {
    int ch;
    
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HIGH_SPEED_MODE,   // timer mode
        .timer_num = LEDC_TIMER_0             // timer index
    };

    ledc_timer_config(&ledc_timer);

    for (ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
        ledc_channel_config(&ledc_channel[ch]);
    }

    ledc_fade_func_install(0);
}

以上で準備OK、あとはdutyに変化後の値、BlinkDurationに変化秒数を設定すれば、勝手に変化してくれます。

    for (int ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
        ledc_set_fade_with_time(ledc_channel[ch].speed_mode,
                ledc_channel[ch].channel, duty, BlinkDuration);
        ledc_fade_start(ledc_channel[ch].speed_mode,
                ledc_channel[ch].channel, LEDC_FADE_NO_WAIT);
    }            

 */
