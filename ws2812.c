#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "hardware/gpio.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define BUTTON_INCREMENT_PIN 5
#define BUTTON_DECREMENT_PIN 6
#define DEBOUNCE_TIME_US 300000 

const uint ledA_pin = 13;

// Definição das cores (valores iniciais)
uint8_t led_r = 0;
uint8_t led_g = 0;
uint8_t led_b = 20;

volatile uint8_t buffer_ativo = 0;
volatile bool atualizar_leds = false;

// Função para enviar um valor de cor para o LED
static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

// Função para converter RGB em 32 bits
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

// Definição dos 11 buffers de LEDs
bool led_buffers[11][NUM_PIXELS] = {
   {1, 0, 0, 0, 1,
    0, 1, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 1, 0, 1, 0,
    1, 0, 0, 0, 1},

   {0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0},

   {0, 1, 1, 1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 1, 1, 0, 0,
    0, 0, 1, 0, 0},


   {0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0},


   {0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0},

   {0, 1, 0, 0, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 0, 1, 0},

    {0, 1, 1, 1, 0,
     0, 0, 0, 1, 0, 
     0, 1, 1, 1, 0, 
     0, 1, 0, 0, 0, 
     0, 1, 1, 1, 0},

   {0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0},

   {0, 0, 1, 0, 0,
    0, 0, 1, 0, 0, 
    0, 1, 0, 0, 0,
    0, 0, 0, 0, 1,
    1, 1, 1, 1, 0},

   {0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0},


   {0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0}
};

// Função para atualizar os LEDs com base no buffer ativo
void set_one_led(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = urgb_u32(r, g, b);
    bool* buffer = led_buffers[buffer_ativo]; // Obtém o buffer atual

    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(buffer[i] ? color : 0);
    }
}

// Interrupção dos botões
void gpio_irq_handler(uint gpio, uint32_t events) {
    static uint32_t last_time = 0;
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (current_time - last_time > DEBOUNCE_TIME_US) {
        last_time = current_time;

        if (gpio == BUTTON_INCREMENT_PIN) {
            buffer_ativo = (buffer_ativo + 1) % 11; // Alterna entre 0 e 10
        } else if (gpio == BUTTON_DECREMENT_PIN) {
            buffer_ativo = (buffer_ativo == 0) ? 10 : buffer_ativo - 1;
        }


        atualizar_leds = true; // Define sinalizador para atualizar LEDs no loop principal
    }
}


int main() {
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    stdio_init_all();

    gpio_init(ledA_pin);
    gpio_set_dir(ledA_pin, GPIO_OUT);

    gpio_init(BUTTON_INCREMENT_PIN);
    gpio_set_dir(BUTTON_INCREMENT_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_INCREMENT_PIN);

    gpio_init(BUTTON_DECREMENT_PIN);
    gpio_set_dir(BUTTON_DECREMENT_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_DECREMENT_PIN);

   
    while (true) {


        gpio_put(ledA_pin, 1);
        sleep_ms(100);
        gpio_put(ledA_pin, 0);
        sleep_ms(100);

    gpio_set_irq_enabled_with_callback(BUTTON_INCREMENT_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_DECREMENT_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);


        if (atualizar_leds) {
            set_one_led(led_r, led_g, led_b);
            atualizar_leds = false;
        }
    }

    return 0;
}
