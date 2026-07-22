#include "raylib.h"

#include <iostream> 
#include <random>
#include <array>
#include <vector>

const size_t SCREEN_WIDTH = 1280; 
const size_t SCREEN_HEIGHT = 720; 
const size_t FPS = 60;

constexpr size_t OX = static_cast<size_t>(SCREEN_WIDTH/2);
constexpr size_t OY = static_cast<size_t>(SCREEN_HEIGHT/2);

const int32_t X_MAX = static_cast<int32_t>(SCREEN_WIDTH/2);
const int32_t X_MIN = -X_MAX; 

const int32_t Y_MAX = static_cast<int32_t>(SCREEN_HEIGHT/2);
const int32_t Y_MIN = -Y_MAX; 

const Color COLOR_BG = BLACK;

struct Particle { 
  size_t id;  
  int32_t x; 
  int32_t y; 
  Particle() : Particle (0, 0) { }

  Particle(int32_t start_x, int32_t start_y) : 
    x {start_x},
    y {start_y} {}  
};

void draw (const Particle &p) { 
  DrawCircle(OX + p.x, OY + p.y, 2, WHITE);
} 
void move (Particle &p, int32_t x, int32_t y) { 
  p.x = x; 
  p.y = y; 
}

namespace Brownian { 
  std::random_device rd; 
  std::mt19937 rng;  
  std::uniform_int_distribution<int32_t> dist_x (X_MIN, X_MAX); 
  std::uniform_int_distribution<int32_t> dist_y (Y_MIN, Y_MAX); 
  std::uniform_int_distribution<int32_t> step (-1, 1);

  const size_t PARTICLES_COUNT = 10000; 
  std::array<Particle, PARTICLES_COUNT> particles;
  
  void generate_particle() { 
    for(size_t idx = 0; idx < particles.size(); idx++) { 
      particles[idx].x = dist_x(rng); 
      particles[idx].y = dist_y(rng);
    }
  } 

  void render_particle() { 
    for(size_t idx = 0; idx < particles.size(); idx++) { 
      draw(particles[idx]);
    }
  }

  void update_particle() { 
    for(size_t idx = 0; idx < particles.size(); idx++) { 
      move(particles[idx], particles[idx].x + step(rng), particles[idx].y + step(rng));
    }
  }
};

int main(void) { 
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stochastic");
  SetTargetFPS(FPS);

  Brownian::generate_particle(); 

  while (!WindowShouldClose()) { 
    BeginDrawing();
    ClearBackground(COLOR_BG);
    Brownian::render_particle();
    Brownian::update_particle();  
    EndDrawing(); 
  }
  CloseWindow();
  return 0; 
}
