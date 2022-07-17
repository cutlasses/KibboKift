
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
  constexpr int min_freq          = 200;
  constexpr float min_time        = 1.0f / min_freq;
  constexpr int to_us             = 1000 * 1000;
  constexpr int min_time_us       = min_time * to_us;
  constexpr int half_min_time_us  = min_time_us / 2;
  constexpr int max_freq          = 1000;
  constexpr float max_time        = 1.0f / max_freq;
  constexpr int max_time_us       = max_time * to_us;
  constexpr int half_max_time_us  = max_time_us / 2;
  constexpr int delta_time_us     = min_time_us - max_time_us;  // min time is higher because it's a lower frequency
  constexpr int update_freq       = 10;

  const int num_updates           = fade_time * update_freq;
  const int update_time_us        = (fade_time / num_updates) * to_us;
  const int cycle_inc             = (delta_time_us / num_updates); // in us
  const int half_cycle_inc        = fade_in ? -(cycle_inc / 2) : (cycle_inc / 2);

  Serial.print("num_updates ");
  Serial.print(num_updates);
  Serial.print(" half_cycle_inc ");
  Serial.println(cycle_inc);

  int half_cycle_time_us        = fade_in ? half_min_time_us : half_max_time_us;
  for( int u = 0; u < num_updates; ++u )
  {
    const int cycles_per_update = update_time_us / (half_cycle_time_us);
    Serial.print(half_cycle_time_us);
    Serial.print(" ");
    Serial.println(cycles_per_update);
    for( int u = 0; u < cycles_per_update; ++u )
    {
      all_leds_on();
      delayMicroseconds(half_cycle_time_us);
      all_leds_off();
      delayMicroseconds(half_cycle_time_us);
    }

    half_cycle_time_us          += half_cycle_inc;
  }

  Serial.println("end");
}

void loop()
{
  fade(5, true);
  //fade(1, false);
  //digitalWrite(1,HIGH);

  delay(10000);
}
