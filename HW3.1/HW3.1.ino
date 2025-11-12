// === 腳位設定 ===
const int buttonPin = 2;  // 按鈕接 GND
const int RPin = 3;
const int GPin = 5;
const int BPin = 6;

// === 狀態參數 ===
int colorMode = 0;              // 0=橘, 1=藍, 2=粉
int lastReading = HIGH;
int stableState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 30;

unsigned long pressStart = 0;
bool longPressFired = false;
const unsigned long longPressMs = 1000; // 長按1秒啟動
bool flashing = false;                  // 是否在閃爍模式

// === 共陽輸出（反相） ===
static inline void writeRGB(int r, int g, int b) {
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);
  analogWrite(RPin, 255 - r);
  analogWrite(GPin, 255 - g);
  analogWrite(BPin, 255 - b);
}

// === 顯示顏色 ===
void showColor(int mode) {
  switch (mode) {
    case 0: writeRGB(255, 100, 0); break;    // 橘
    case 1: writeRGB(0, 0, 255); break;      // 藍
    case 2: writeRGB(255, 100, 180); break;  // 粉
  }
}

void setup() {
  pinMode(RPin, OUTPUT);
  pinMode(GPin, OUTPUT);
  pinMode(BPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);
  unsigned long now = millis();

  // === 去彈跳 ===
  if (reading != lastReading) lastDebounceTime = now;
  if ((now - lastDebounceTime) > debounceDelay) {

    // ---- 按下瞬間 ----
    if (stableState == HIGH && reading == LOW) {
      pressStart = now;
      longPressFired = false;
    }

    // ---- 按住超過1秒：進入閃爍模式 ----
    if (reading == LOW && !longPressFired && (now - pressStart > longPressMs)) {
      longPressFired = true;
      flashing = true;
    }

    // ---- 放開瞬間 ----
    if (stableState == LOW && reading == HIGH) {
      if (!longPressFired) {
        // 短按：切換顏色
        colorMode++;
        if (colorMode > 2) colorMode = 0;
      }
      // 放開後停止閃爍
      flashing = false;
    }

    stableState = reading;
  }
  lastReading = reading;

  // === 顯示邏輯 ===
  if (flashing) {
    // 1 秒閃一次：亮 1 秒，滅 1 秒
    bool on = ((now / 400) % 2) == 0;
    if (on) showColor(colorMode);
    else writeRGB(0, 0, 0);
  } else {
    showColor(colorMode);
  }
}
