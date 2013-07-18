#include "Entity.h"

#include "DrawSomeTime.h"
#include "String.hpp"
#include "Font.h"

extern std::vector<DrawSomeTime<se::String>> damageString;
extern se::Font *font;

Entity::Entity(int x, int y, int health, int experience, int speed, int maxJump) : PhysicsObject(x, y), inAir(STADING), health(health), experience(experience),
 maxJump(maxJump), currentJump(0), speed(speed),
 damage(se::Color(1.0f, 0.4f, 0.4f, 1.0f)),
 stun(se::Color(0.6f, 0.6f, 0.6f, 1.0f)), freeze(se::Color(0.4f, 0.4f, 1.0f, 0.5f)) {
  for (int i = 0; i < Damage::ALL; i++)
    immunity[i] = false;
}

void Entity::TryToMove(int offsetX, int offsetY, std::vector<PhysicsObject *> floors) {
  if (!stun.UnderEffect()) {
    int speedX = !freeze.UnderEffect() ? speed*offsetX : speed*offsetX/2;
    int speedY = !freeze.UnderEffect() ? speed*offsetY : speed*offsetY/2;
    this->Move(speedX, speedY);
    bool canMove = true;
    for (auto i = floors.begin(); i != floors.end(); i++)
      if (CheckCollision(*i)) {
        canMove = false;
        break;
      }
    int lolka = x + speedX;
    if (lolka <= 2)
      canMove = false;
    if (!canMove)
      this->Move(-speedX, -speedY);
  }
}

void Entity::Tick(std::vector<PhysicsObject *> things) {
  bool floorUnderFoot = false;

  se::Color result;
  if (stun.CheckEffect())
    result *= stun.GetColor();
  if (freeze.CheckEffect())
    result *= freeze.GetColor();
  if (damage.CheckEffect())
    result *= damage.GetColor();
  SetColor(result);
  switch (inAir) {
  case STADING:
    SetY(y - G);
    for (auto i = things.begin(); i != things.end(); i++)
      if ((*i)->CheckCollision(this)) {
        floorUnderFoot = true;
        break;
      }
    SetY(y + G);
    if (!floorUnderFoot) {
      inAir = FALLING;
      currentJump = 0;
    }
    break;
  case INAIR:
    if (currentJump <= 0)
      inAir = FALLING;
    else {
      currentJump -= G;
      SetY(y + currentJump);
      for (auto i = things.begin(); i != things.end(); i++)
        if ((*i)->CheckCollision(this))
          inAir = FALLING;
      break;
    }
    break;
  case FALLING:
    currentJump += G;
    SetY(y - currentJump);
    for (auto i = things.begin(); i != things.end(); i++)
      if ((*i)->CheckCollision(this)) {
        this->SetY((*i)->GetY()+(*i)->GetHeight());
        inAir = STADING;
        break;
      }
    break;
  case ONSTAIR:
    break;
  }
}

void Entity::Jump() {
  if (inAir != STADING) return;
  inAir = INAIR;
  currentJump = maxJump;
}

void Entity::DamageHim(Damage damage) {
  if (immunity[damage.GetType()])
    return;
  if (health - damage.damage <= 0)
    health = 0;
  else
    health -= damage.damage;
  char text[5];
  sprintf_s(text, 5, "%d", damage.damage);
  damageString.push_back(DrawSomeTime<se::String>(std::shared_ptr<se::String>(new se::String(text, font, x+GetWidth(), y+GetHeight(), se::Color(1.0f, 1.0f, 1.0f), false)), 1000));
  this->damage.SetLong(500);
  this->damage.MakeEffect();
}

void Entity::Freeze(DWORD howLong) {
  freeze.SetLong(howLong);
  freeze.MakeEffect();
}

void Entity::Stun(DWORD howLong) {
  stun.SetLong(howLong);
  stun.MakeEffect();
}

bool Entity::IsAlive() const {
  return health != 0;
}

int Entity::GetHealth() const {
  return health;
}

void Entity::SetHealth(int health) {
  this->health = health;
}

bool Entity::CheckCollision(PhysicsObject *other) {
  int width = GetX() + GetWidth();
	int height = GetY() + GetHeight();
	int aWidth = other->GetX() + other->GetWidth();
	int aHeight = other->GetY() + other->GetHeight();

	return (GetX() < aWidth && GetY() < aHeight && other->GetX() < width && other->GetY() < height);
}