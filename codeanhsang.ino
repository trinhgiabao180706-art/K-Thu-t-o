#include <Wire.h>
#include <BH1750.h>

// Định nghĩa chân LED (Sử dụng GPIO13)
const int ledPin = 13; 

// Ngưỡng ánh sáng Lux: Nếu Lux < 50, LED sẽ BẬT.
const float lightThresholdLux = 50.0; 

BH1750 lightMeter;

void setup(){
  Serial.begin(115200); // Nên dùng tốc độ cao hơn (115200) cho ESP32

  // Thiết lập chân LED là OUTPUT
  pinMode(ledPin, OUTPUT); 

  // Khởi tạo giao tiếp I2C
  // ESP32 mặc định là GPIO21 (SDA) và GPIO22 (SCL).
  Wire.begin(); 

  // Khởi tạo cảm biến BH1750
  // Kiểm tra lỗi trong quá trình khởi tạo (Tùy chọn, nhưng nên làm)
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Ready"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }

  // Tắt LED khi khởi động
  digitalWrite(ledPin, LOW); 
}

void loop() {
  float lux = lightMeter.readLightLevel();
  
  // Kiểm tra lỗi đọc giá trị
  if (lux != -1.0) {
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    // Logic điều khiển LED: Nếu ánh sáng tối hơn ngưỡng, bật LED
    if (lux < lightThresholdLux) {
      digitalWrite(ledPin, HIGH); // Bật LED
      Serial.println("-> ANH SANG YEU, BAT LED!");
    } else {
      digitalWrite(ledPin, LOW);  // Tắt LED
      Serial.println("-> ANH SANG MANH, TAT LED.");
    }
    
  } else {
    Serial.println("Loi doc cam bien BH1750!");
  }
  
  delay(1000);
}