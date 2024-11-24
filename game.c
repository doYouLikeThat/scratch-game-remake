#include <raylib.h>
#include <stdio.h>

typedef enum GameScreen { TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct Player {
  int speed;
  Vector2 dir;
  Rectangle collision;
  Texture2D texture;
} Player;

typedef struct Enemy {
  float speed;
  bool active;
  Rectangle collision;
  Texture2D texture;
} Enemy;

typedef struct Apple {
  int size;
  Rectangle collision;
  bool active;
  Vector2 position;
  Texture2D texture;
} Apple;

Vector2 getRandPos() {
  Vector2 randPos = {(float)GetRandomValue(0, GetScreenWidth()),
		     (float)GetRandomValue(0, GetScreenHeight())};
  return randPos;
}

int main(void) {

  int score = 0;
  const int screenWidth = 800;
  const int screenHeight = 600;
  
  InitWindow(screenWidth, screenHeight, "Collecting apples");
  SetTargetFPS(60);

  Texture2D playerUp = LoadTexture("assets/civicUp.png");
  Texture2D playerDown = LoadTexture("assets/civicDown.png");
  Texture2D playerLeft = LoadTexture("assets/civicLeft.png");
  Texture2D playerRight = LoadTexture("assets/civicRight.png");
  // X and Y integers are useless, I should remove and replace
  // them with Rectangles.
  Player player;
  player.texture = LoadTexture("assets/civicUp.png");
  player.dir = (Vector2){0,0};
  player.speed = 5;
  player.collision.x = screenWidth/2;
  player.collision.y = screenHeight/2;
  player.collision.width = 20;
  player.collision.height = 20;

  Apple apple;
  apple.size = 30;
  apple.active = false;
  apple.texture = LoadTexture("assets/applePixel.png");

  Enemy enemy;
  enemy.texture = LoadTexture("assets/ghost_blue.png");
  enemy.collision.x = screenWidth/2;
  enemy.collision.y = -30;
  enemy.collision.width = 20;
  enemy.collision.height = 20;
  enemy.active = false;

  Enemy enemy2;
  enemy2.texture = LoadTexture("assets/ghost_orange.png");
  enemy2.collision.x = screenWidth/2;
  enemy2.collision.y = -30;
  enemy2.collision.width = 20;
  enemy2.collision.height = 20;
  enemy2.active = false;

  Enemy enemy3;
  enemy3.texture = LoadTexture("assets/ghost_pink.png");
  int enemy3speedY = 6;
  enemy3.collision.x = getRandPos().x;
  enemy3.collision.y = -30;
  enemy3.collision.width = 20;
  enemy3.collision.height = 20;
  enemy3.active = false;

  Enemy enemy4;
  enemy4.texture = LoadTexture("assets/ghost_teal.png");
  enemy4.collision.x = getRandPos().x;
  enemy4.collision.y = 630;
  enemy4.collision.width = 20;
  enemy4.collision.height = 20;
  enemy4.active = false;

  GameScreen currentScreen = TITLE;
  bool collision = CheckCollisionRecs(enemy.collision, player.collision);
  
  while(!WindowShouldClose()) {
    
    switch (currentScreen) {
      
    case TITLE: {

      ClearBackground(RAYWHITE);
      DrawText("Let's collect some apples", screenWidth/4, screenHeight/2, 32, BLACK);
      DrawText("Press [Enter] to start", 420, 540, 32, BLACK);
      DrawText("Press [WASD] to move", 10, 540, 32, BLACK);

      if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
      
      break;
    }
      
    case GAMEPLAY: {

      // Player movement
      if (IsKeyDown(KEY_W)) {
	player.collision.y -= player.speed;
	player.dir = (Vector2){0, 1};
	player.texture = playerUp;
      }
      else if (IsKeyDown(KEY_S)) {
	player.collision.y += player.speed;
	player.dir = (Vector2){0, -1};
	player.texture = playerDown;
      }
      if (IsKeyDown(KEY_A)) {
	player.collision.x -= player.speed;
	player.dir = (Vector2){-1, 0};
	player.texture = playerLeft;
      }
      else if (IsKeyDown(KEY_D)) {
	player.collision.x += player.speed;
	player.dir = (Vector2){1, 0};
	player.texture = playerRight;
      }

      if (!apple.active) {
	apple.active = true;
	apple.position = getRandPos();
      }

      // Collision with apples
      if ((player.collision.x < (apple.position.x + apple.size) &&
	   (player.collision.x + player.texture.width/4) > apple.position.x) &&
	  (player.collision.y < (apple.position.y + apple.size) &&
	   (player.collision.y + player.texture.height/4) > apple.position.y)) {
      
	apple.active = false;
	score++;
      
      }
      
      enemy.active = true;
      
      // Enemies
      enemy.speed = (float)GetRandomValue(0, 5);
      if (enemy.active) {
	if (enemy.collision.x < player.collision.x) enemy.collision.x += enemy.speed;
	else if (enemy.collision.x > player.collision.x) enemy.collision.x -= enemy.speed;
	if (enemy.collision.y < player.collision.y) enemy.collision.y += enemy.speed;
	else if (enemy.collision.y > player.collision.y) enemy.collision.y -= enemy.speed;
	else if (enemy.collision.x == player.collision.x &&
		 enemy.collision.y == player.collision.y) currentScreen = ENDING;
      }

      // This is some shitty written code, but for a small game like this it should be fine.
      // I don't know how to use for loops and arrays for stuff like this.

      // Btw having more enemies that behave the same is kinda pointless
      if (score > 2) {
	enemy2.active = true;
      }

      // To make enemy no.2 more interesting, I'm giving him random speed.
      // Since the variable declaration is in the while loop, it should update
      // all the time.
      enemy2.speed = (float)GetRandomValue(0, 5);
      if (enemy2.active) {
	if (enemy2.collision.x < player.collision.x) enemy2.collision.x += enemy2.speed;
	else if (enemy2.collision.x > player.collision.x) enemy2.collision.x -= enemy2.speed;
	if (enemy2.collision.y < player.collision.y) enemy2.collision.y += enemy2.speed;
	else if (enemy2.collision.y > player.collision.y) enemy2.collision.y -= enemy2.speed;
	else if (enemy2.collision.x == player.collision.x &&
		 enemy2.collision.y == player.collision.y) currentScreen = ENDING;
      }

      if (score > 1) {
	enemy3.active = true;
      }

      enemy3.speed = (float)GetRandomValue(0, 3);
      if (enemy3.active) {
	if (enemy3.collision.x < player.collision.x) enemy3.collision.x += enemy3.speed;
	else if (enemy3.collision.x > player.collision.x) enemy3.collision.x -= enemy3.speed;
	else if (enemy3.collision.y < player.collision.y -1) enemy3.collision.y += enemy3speedY;
	else if (enemy3.collision.y > player.collision.y -1) enemy3.collision.y -= enemy3speedY;
	else if (enemy3.collision.x == player.collision.x &&
		 enemy3.collision.y == player.collision.y) currentScreen = ENDING;
      }

      if (score > 3) {
	enemy4.active = true;
      }

      enemy4.speed = (float)GetRandomValue(0, 4);
      if (enemy4.active) {
	if (enemy4.collision.x < player.collision.x) enemy4.collision.x += enemy4.speed;
	else if (enemy4.collision.x > player.collision.x) enemy4.collision.x -= enemy4.speed;
	else if (enemy4.collision.y < player.collision.y -1) enemy4.collision.y += enemy4.speed;
	else if (enemy4.collision.y > player.collision.y -1) enemy4.collision.y -= enemy4.speed;
	else if (enemy4.collision.x == player.collision.x &&
		 enemy4.collision.y == player.collision.y) currentScreen = ENDING;
      }
        
      // Screen boundries
      if (player.collision.x >= screenWidth) player.collision.x = screenWidth;
      else if (player.collision.x <= 0) player.collision.x = 0;
      if (player.collision.y >= screenHeight) player.collision.y = screenHeight;
      else if (player.collision.y <= 0) player.collision.y = 0;

      // Drawing the player
      DrawTexture(player.texture, player.collision.x - player.texture.width/2,
		  player.collision.y - player.texture.height/2, WHITE);
    
      ClearBackground(RAYWHITE);

      // Drawing the apples
      DrawTexture(apple.texture, apple.position.x - apple.texture.width/3,
		  apple.position.y - apple.texture.height/3, WHITE);
    
      DrawText(TextFormat("Score: %i", score), 10, 10, 40, BLACK);
      DrawFPS(10, 50);

      // Drawing the enemies
      DrawTexture(enemy.texture, enemy.collision.x - enemy.texture.width/2,
		  enemy.collision.y - enemy.texture.height/2, WHITE);
    
      /* DrawRectangleLines(enemy.collision.x - enemy.collision.width/2, */
      /* 			 enemy.collision.y - enemy.collision.height/2, */
      /* 			 enemy.collision.width, enemy.collision.height, RED); */

      if (enemy2.active) {
	DrawTexture(enemy2.texture, enemy2.collision.x - enemy2.texture.width/2,
		    enemy2.collision.y - enemy2.texture.height/2, WHITE);
      }

      if (enemy3.active) {
	DrawTexture(enemy3.texture, enemy3.collision.x - enemy3.texture.width/3,
		    enemy3.collision.y - enemy3.texture.height/2, WHITE);
      }

      if (enemy4.active) {
	DrawTexture(enemy4.texture, enemy4.collision.x - enemy4.texture.width/3,
		    enemy4.collision.y - enemy4.texture.height/2, WHITE);
      }

      // Debug stuff
      // Player hurtbox

      /* DrawRectangle(player.collision.x, */
      /* 		    player.collision.y, */
      /* 		    player.collision.width, player.collision.height, GREEN); */

      /* DrawRectangle(apple.position.x, */
      /* 		    apple.position.y, */
      /* 		    apple.size, */
      /* 		    apple.size, */
      /* 		    GREEN); */
    
      break;
    }
      
    case ENDING: {
      ClearBackground(RAYWHITE);
      DrawText("GAME OVER", 200, screenHeight/2, 64, RED);
      DrawText(TextFormat("Score: %i", score), 350, screenHeight - 200, 32, BLACK);
      DrawText("Press [ESC] to close the game", 165, screenHeight - 100, 32, BLACK);
      break;
    }
      
    default: break;
    }

    BeginDrawing();
    
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
