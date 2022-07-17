
constexpr int NUM_LED_PINS = 7;
uint8_t led_pins[NUM_LED_PINS] = { 0, 1, 2, 3, 4, 5, 6 };

void setup()
{
  for( uint8_t i = 0; i < NUM_LED_PINS; ++i )
  {
    pinMode( i, OUTPUT );
  }
}

void all_leds_on()
{
  for( uint8_t i = 0; i < NUM_LED_PINS; ++i )
  {
    digitalWrite( i, HIGH );
  }  
}

void all_leds_off()
{
  for( uint8_t i = 0; i < NUM_LED_PINS; ++i )
  {
    digitalWrite( i, LOW );
  }  
}

void fade(float fade_time, bool fade_in)
{
  constexpr int to_us             = 1000 * 1000;
  constexpr int duty_frequency    = 200;
  constexpr int duty_time_us      = (1.0f / duty_frequency) * to_us;
  
  constexpr float min_width       = 0.01f;
  constexpr int min_time_us       = min_width * duty_time_us;
  
  constexpr float max_width       = 0.99f;
  constexpr int max_time_us       = max_width * duty_time_us;
  constexpr int delta_width_us    = max_time_us - min_time_us;
  
  constexpr int update_freq       = 10; // rate of change of pwm
  constexpr int cycles_per_update = ((1.0f / update_freq) * to_us)  / duty_time_us;
  const int num_updates           = fade_time * update_freq;
  const int cycle_inc_us          = fade_in ? (delta_width_us / num_updates) : -(delta_width_us / num_updates);
  
  int on_time_us                  = fade_in ? min_time_us : max_time_us;
  for( int u = 0; u < num_updates; ++u )
  {
    for( int c = 0; c < cycles_per_update; ++c )
    {
      const int off_time_us       = duty_time_us - on_time_us;

      all_leds_on();
      delayMicroseconds(on_time_us);
      all_leds_off();
      delayMicroseconds(off_time_us);
    }
    
    on_time_us                    += cycle_inc_us;
  }
}

void loop()
{
  fade(5, true);
  fade(5, false);
  //digitalWrite(1,HIGH);

  delay(1000);
}
