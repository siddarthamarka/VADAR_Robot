#include "esp_camera.h"
#include <WiFi.h>
#include "config.h"

void startCameraServer();
void sendToDrive();

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  camera_config_t config = {
    .pin_pwdn = 32, .pin_reset = -1,
    .pin_xclk = 0, .xclk_freq_hz = 20000000, .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0, .pixel_format = PIXFORMAT_JPEG,
    .frame_size = FRAMESIZE_QVGA, .jpeg_quality = 12, .fb_count = 1
  };
  esp_camera_init(&config);

  delay(2000);
  sendToDrive();
}

void sendToDrive() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) return;

  WiFiClient client;
  HTTPClient http;
  http.begin(client, DRIVE_UPLOAD_URL);
  http.addHeader("Content-Type", "image/jpeg");
  int httpResponseCode = http.POST(fb->buf, fb->len);

  Serial.println(httpResponseCode > 0 ? "Uploaded to Drive" : "Upload failed");

  esp_camera_fb_return(fb);
  http.end();
}

void loop() {}
