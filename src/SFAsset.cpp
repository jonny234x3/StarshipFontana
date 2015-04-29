#include "SFAsset.h"

int SFAsset::SFASSETID=0;

SFAsset::SFAsset(SFASSETTYPE type, std::shared_ptr<SFWindow> window): type(type), sf_window(window) {
  this->id   = ++SFASSETID;

  switch (type) {
  case SFASSET_PLAYER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/player.png");
    break;
  case SFASSET_PROJECTILEUP:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/projectile_up.png");
    break;
  case SFASSET_PROJECTILELEFT:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/projectile_left.png");
    break;
  case SFASSET_PROJECTILEDOWN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/projectile_down.png");
    break;
  case SFASSET_PROJECTILERIGHT:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/projectile_right.png");
    break;
  case SFASSET_ALIEN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/enemy.png");
    break;
  case SFASSET_WALLH:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/wall1.png");
    break;
  case SFASSET_WALLV:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/wall2.png");
    break;
  case SFASSET_DIAMOND:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/diamond.png");
    break;
  case SFASSET_RUBY:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/ruby.png");
    break;
  case SFASSET_EMERALD:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/emerald.png");
    break;
  case SFASSET_SAPPHIRE:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sapphire.png");
    break;
  case SFASSET_ENDGAME:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/end_game.png");
    break;
  }

  if(!sprite) {
    cerr << "Could not load asset of type " << type << endl;
    throw SF_ERROR_LOAD_ASSET;
  }

  // Get texture width & height
  int w, h;
  SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

  // Initialise bounding box
  bbox = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(0.0f, 0.0f), w, h));
}

SFAsset::SFAsset(const SFAsset& a) {
  sprite = a.sprite;
  sf_window = a.sf_window;
  bbox   = a.bbox;
  type   = a.type;
}

SFAsset::~SFAsset() {
  bbox.reset();
  if(sprite) {
    SDL_DestroyTexture(sprite);
    sprite = nullptr;
  }
}

/**
 * The logical coordinates in the game assume that the screen
 * is indexed from 0,0 in the bottom left corner.  The blittable
 * coordinates of the screen map 0,0 to the top left corner. We
 * need to convert between the two coordinate spaces.  We assume
 * that there is a 1-to-1 quantisation.
 */
Vector2 GameSpaceToScreenSpace(SDL_Renderer* renderer, Vector2 &r) {
  int w, h;
  SDL_GetRendererOutputSize(renderer, &w, &h);

  return Vector2 (
                  r.getX(),
                  (h - r.getY())
                  );
}

void SFAsset::SetPosition(Point2 & point) {
  Vector2 v(point.getX(), point.getY());
  bbox->SetCentre(v);
}

Point2 SFAsset::GetPosition() {
  return Point2(bbox->centre->getX(), bbox->centre->getY());
}

SFAssetId SFAsset::GetId() {
  return id;
}

void SFAsset::OnRender() {
  // 1. Get the SDL_Rect from SFBoundingBox
  SDL_Rect rect;

  Vector2 gs = (*(bbox->centre) + (*(bbox->extent_x) * -1)) + (*(bbox->extent_y) * -1);
  Vector2 ss = GameSpaceToScreenSpace(sf_window->getRenderer(), gs);
  rect.x = ss.getX();
  rect.y = ss.getY();
  rect.w = bbox->extent_x->getX() * 2;
  rect.h = bbox->extent_y->getY() * 2;

  // 2. Blit the sprite onto the level
  SDL_RenderCopy(sf_window->getRenderer(), sprite, NULL, &rect);
}

void SFAsset::GoWest() {
  int w, h;
  if(SFASSET_PLAYER == type){
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  Vector2 c = *(bbox->centre) + Vector2(-7.0f, 0.0f);
   if(!(c.getX()-12.0f < 0)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
   } else {
    this->SetNotAlive();
     }
}

  if(SFASSET_PROJECTILELEFT == type){
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  Vector2 c = *(bbox->centre) + Vector2(-5.0f, 0.0f);
   if(!(c.getX()-12.0f < 0)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
   } else {
    this->SetNotAlive();
     }
  }
}

void SFAsset::GoEast() {
  int w, h;
  if(SFASSET_PLAYER == type){
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  Vector2 c = *(bbox->centre) + Vector2(7.0f, 0.0f);
   if(!(c.getX()+12.0f > w)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
   } else {
    this->SetNotAlive();
     }
  }

  if(SFASSET_PROJECTILERIGHT == type){
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  Vector2 c = *(bbox->centre) + Vector2(5.0f, 0.0f);
   if(!(c.getX()+12.0f > w)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
   } else {
    this->SetNotAlive();
     }
  }
}

void SFAsset::GoNorth() {
  int w, h;
  if(SFASSET_PLAYER == type){
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  Vector2 c = *(bbox->centre) + Vector2(0.0f, 7.0f);
    if(!(c.getY()-26.0f > h)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
    }
  }

  if(SFASSET_PROJECTILEUP == type){
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  Vector2 c = *(bbox->centre) + Vector2(0.0f, 5.0f);
   if(!(c.getY()-26.0f > h)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
   } else {
    this->SetNotAlive();
     }
  }
}

void SFAsset::GoSouth() {
  int w, h;
  if(SFASSET_PLAYER == type){
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  Vector2 c = *(bbox->centre) + Vector2(0.0f, -7.0f);
   if(!(c.getX()< 70.0f > w)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
   } else {
    this->SetNotAlive();
     }
  }

  if(SFASSET_PROJECTILEDOWN == type){
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  Vector2 c = *(bbox->centre) + Vector2(0.0f, -5.0f);
  if(!(c.getY() < 70.0f)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
  } else {
    this->SetNotAlive();
     }

  }
}


bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) {
  return bbox->CollidesWith(other->bbox);
}

shared_ptr<SFBoundingBox> SFAsset::GetBoundingBox() {
  return bbox;
}

void SFAsset::SetNotAlive() {
  type = SFASSET_DEAD;
}

bool SFAsset::IsAlive() {
  return (SFASSET_DEAD != type);
}

void SFAsset::HandleCollision() {
// Alien Respawn
    if(SFASSET_ALIEN == type) {
	int canvas_w, canvas_h;
	SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);
	// Random Position     ~ problem can spawn just above walls
	auto pos = Point2(rand() % (canvas_w), rand() % (canvas_h/2) + 200 );
    	this->SetPosition(pos);
    }

// Projectile Destroy
    if(SFASSET_PROJECTILEUP == type || SFASSET_PROJECTILELEFT == type || SFASSET_PROJECTILEDOWN == type || SFASSET_PROJECTILERIGHT == type) {
		SetNotAlive();
    }

// Player Hit Alien - Then Respawn Player and Collectables
    if(SFASSET_PLAYER == type) {
	int canvas_w, canvas_h;
	SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);
  	auto player_pos = Point2((canvas_w/2), 88.0f);
	this->SetPosition(player_pos);
    }

// Gem Destory
    if(SFASSET_DIAMOND == type || SFASSET_RUBY == type  || SFASSET_EMERALD == type  || SFASSET_SAPPHIRE == type ) {
		 SetNotAlive();
    }

} // HandleCollision close

