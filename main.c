#include "raylib.h"
#include <time.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void);

typedef struct Logo {
  Vector2 position;
  Vector2 speed;
  Texture2D texture;
  Vector2 size;
  size_t tint_idx;
} Logo;

Color tint[] = {BLUE, RED, ORANGE, YELLOW, GREEN, MAGENTA};

#define TINT_SIZE 6;

void LogoUpdate(Logo *logo) {
  logo->position.x += logo->speed.x;
  logo->position.y += logo->speed.y;

  if (logo->position.x < 0 ||
      (logo->position.x + logo->size.x) > GetScreenWidth()) {
    logo->speed.x *= -1;
    logo->tint_idx++;
  }

  if (logo->position.y < 0 ||
      (logo->position.y + logo->size.y) > GetScreenHeight()) {
    logo->speed.y *= -1;
    logo->tint_idx++;
  }
}

void LogoDraw(const Logo *logo) {
  size_t idx = logo->tint_idx % TINT_SIZE;
  Color c = tint[idx];
  DrawTextureV(logo->texture, logo->position, c);
}

Logo dvd_logo = {0};

int main() {

  const int screen_width = 800;
  const int screen_height = 600;

  InitWindow(screen_width, screen_height, "raylib example");

  Image image = LoadImage("resources/dvd.png");
  dvd_logo.speed = (Vector2){.x = 1.0, .y = 1.0};
  dvd_logo.size = (Vector2){.x = 162.0, .y = 88.0};
  dvd_logo.tint_idx = 0;
  ImageResize(&image, dvd_logo.size.x, dvd_logo.size.y);
  ImageColorInvert(&image);

  dvd_logo.texture = LoadTextureFromImage(image);
  UnloadImage(image);
  SetRandomSeed(time(NULL));

  float x = GetRandomValue(10, GetScreenWidth() - dvd_logo.size.x - 10);
  float y = GetRandomValue(10, GetScreenHeight() - dvd_logo.size.y - 10);

  dvd_logo.position = (Vector2){.x = x, .y = y};

  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

  UnloadTexture(dvd_logo.texture);
  CloseWindow();
  return (0);
}

void UpdateDrawFrame(void) {
  BeginDrawing();
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), LIGHTGRAY);
  ClearBackground(WHITE);
  LogoDraw(&dvd_logo);
  LogoUpdate(&dvd_logo);
  EndDrawing();
}
