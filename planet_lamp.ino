const int red_light_pin = 11;
const int green_light_pin = 10;
const int blue_light_pin = 9;

const int NUM_COLORS = 8;

int current_color_selection_index = 0;

// colors pulled from "Planetary Magick" in color scale of Briah
int color_selections[NUM_COLORS][3] = {
  // white
  { 255, 255, 255},
  // Saturn, Indigo, #4b0082
  { 75, 0, 82},
  // Jupiter, Blue, #0000FF
  { 0, 0, 255},
  // Mars, Red, #FF0000
  {255, 0, 0},
  // Sun, Yellow, #FFFF00
  {255, 255, 0},
  // Venus, Green, #00FF00
  {0, 255, 0},
  // Mercury, Orange, #FFA500
  {255, 165, 0},
  // Moon, Violet, #7F00FF
  {127, 0, 225}
};

const int button_pin = 2;
const int led_pin = 13;

int led_state = HIGH;
int button_state;
int last_button_state = LOW;

unsigned long last_debounce_time = 0;
// increase if jagged results
unsigned long debounce_delay = 50;

void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);

  digitalWrite(led_pin, led_state);
}

void loop() {
  int reading = digitalRead(button_pin);

  if (reading != last_button_state) {
    last_debounce_time = millis();
  }

  if ((millis() - last_debounce_time) > debounce_delay) {
    if (reading != button_state) {
      button_state = reading;

      if (button_state == HIGH) {
        led_state = !led_state;
        inc_current_color_selection();

      }
    }
  }

  // TODO: optimize by only doing work if it changed or is the first run (perhaps setup() could handle first)
  RGB_color(color_selections[current_color_selection_index][0],
            color_selections[current_color_selection_index][1],
            color_selections[current_color_selection_index][2]);

  last_button_state = reading;
}

void inc_current_color_selection() {
  if (current_color_selection_index >= (NUM_COLORS - 1)) {
    current_color_selection_index = 0;
  } else {
    ++current_color_selection_index;
  }
}

void RGB_color(int red, int green, int blue) {
  analogWrite(red_light_pin, red);
  analogWrite(green_light_pin, green);
  analogWrite(blue_light_pin, blue);
}
