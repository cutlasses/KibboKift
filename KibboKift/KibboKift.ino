
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
  constexpr int low_freq          = 10;
  constexpr float low_time        = 1.0f / low_freq;
  constexpr int low_time_us       = low_time * to_us;
  constexpr int half_low_time_us  = low_time_us / 2;
  constexpr int high_freq         = 10000;
  constexpr float high_time       = 1.0f / high_freq;
  constexpr int high_time_us      = high_time * to_us;
  constexpr int half_high_time_us = high_time_us / 2;
  constexpr int delta_time_us     = low_time_us - high_time_us;  // min time is higher because it's a lower frequency
  constexpr int update_freq       = 10;

  const int num_updates           = fade_time * update_freq;
  const int half_update_time_us   = ((fade_time / num_updates) * to_us) / 2;
  const int cycle_inc             = (delta_time_us / num_updates); // in us
  const int half_cycle_inc        = fade_in ? -(cycle_inc / 2) : (cycle_inc / 2);

  int half_cycle_time_us         = fade_in ? half_low_time_us : half_high_time_us;
  for( int u = 0; u < num_updates; ++u )
  {
    const int cycles_per_update = (half_update_time_us * 1000) / (half_cycle_time_us * 1000); // * 1000 to save float calc

    for( int c = 0; c < cycles_per_update; ++c )
    {
      all_leds_on();
      delayMicroseconds(half_cycle_time_us);
      all_leds_off();
      delayMicroseconds(half_cycle_time_us);
    }

    half_cycle_time_us          += half_cycle_inc;
  }
}

void loop()
{
  fade(5, true);
  fade(5, false);
  //digitalWrite(1,HIGH);

  delay(1000);
}
