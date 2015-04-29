#include "SFApp.h"

SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire1(0), fire2(0), fire3(0), fire4(0),is_running(true), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);

// Place Player
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2((canvas_w/2), 88.0f);
  player->SetPosition(player_pos);

// Place Alien
  const int number_of_aliens = 10;
  for(int i=0; i<number_of_aliens; i++) {
    int canvas_w, canvas_h;
    SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos = Point2(rand() % (canvas_w) + 15, rand() % (canvas_h/2) + 250 );
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

//Place Lines of Horizontal Walls1
  const int number_of_wallsh1 = 2;
  for(int i=0; i<number_of_wallsh1; i++) {
    auto wall = make_shared<SFAsset>(SFASSET_WALLH, sf_window);
    auto pos   = Point2(((canvas_w/number_of_wallsh1) * i) + (canvas_w/number_of_wallsh1)/2, 132.0f);
    wall->SetPosition(pos);
    walls.push_back(wall);
   }

//Place Lines of Vertical Walls1
  const int number_of_wallsv1 = 4;
  for(int i=0; i<number_of_wallsv1; i++) {
    auto wall = make_shared<SFAsset>(SFASSET_WALLV, sf_window);
    auto pos   = Point2(((canvas_w/number_of_wallsv1) * i) + (canvas_w/number_of_wallsv1)/2, 200.0f);
    wall->SetPosition(pos);
    walls.push_back(wall);
   }

//Place Lines of Horizontal Walls2
  const int number_of_wallsh2 = 2;
  for(int i=0; i<number_of_wallsh2; i++) {
    auto wall = make_shared<SFAsset>(SFASSET_WALLH, sf_window);
    auto pos   = Point2((580 * i), (canvas_w/2));
    wall->SetPosition(pos);
    walls.push_back(wall);
   }

//Place Lines of Vertical Walls2
  const int number_of_wallsv2 = 2;
  for(int i=0; i<number_of_wallsv2; i++) {
    auto wall = make_shared<SFAsset>(SFASSET_WALLV, sf_window);
    auto pos   = Point2((175 * i) + 233, 525.0f);
    wall->SetPosition(pos);
    walls.push_back(wall);
   }

//Place Lines of Horizontal Walls3
  const int number_of_wallsh3 = 2;
  for(int i=0; i<number_of_wallsh3; i++) {
    auto wall = make_shared<SFAsset>(SFASSET_WALLH, sf_window);
    auto pos   = Point2(((canvas_w/number_of_wallsh3) * i) + (canvas_w/number_of_wallsh3)/2, 440.0f);
    wall->SetPosition(pos);
    walls.push_back(wall);
   }

//Place Diamond
  auto diamond = make_shared<SFAsset>(SFASSET_DIAMOND, sf_window);
  auto pos  = Point2(160, 470);
  diamond->SetPosition(pos);
  diamondC.push_back(diamond);

//Place Ruby
  auto ruby = make_shared<SFAsset>(SFASSET_RUBY, sf_window);
  auto posRuby  = Point2(160, 170);
  ruby->SetPosition(posRuby);
  rubyC.push_back(ruby);

//Place Emerald
  auto emerald = make_shared<SFAsset>(SFASSET_EMERALD, sf_window);
  auto posEmerald  = Point2(470, 470);
  emerald->SetPosition(posEmerald);
  emeraldC.push_back(emerald);

//Place Sapphire
  auto sapphire = make_shared<SFAsset>(SFASSET_SAPPHIRE, sf_window);
  auto posSapphire  = Point2(470, 170);
  sapphire->SetPosition(posSapphire);
  sapphireC.push_back(sapphire);

}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
    player->GoWest();
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();
    break;
  case SFEVENT_PLAYER_UP:
    player->GoNorth();
    break;
  case SFEVENT_PLAYER_DOWN:
    player->GoSouth();
    break;
  case SFEVENT_FIRE_UP:
    fire1 ++;
    FireProjectileUp();
    break;
  case SFEVENT_FIRE_LEFT:
    fire2 ++;
    FireProjectileLeft();
    break;
  case SFEVENT_FIRE_DOWN:
    fire3 ++;
    FireProjectileDown();
    break;
  case SFEVENT_FIRE_RIGHT:
    fire4 ++;
    FireProjectileRight();
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then its in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {
  // Update projectile positions
  for(auto pup: projectilesup) {
    pup->GoNorth();
  }
  for(auto pleft: projectilesleft) {
    pleft->GoWest();
  }
  for(auto pdown: projectilesdown) {
    pdown->GoSouth();
  }
  for(auto pright: projectilesright) {
    pright->GoEast();
  }

// Enemy Movement
/*
  for(auto a : aliens) {
     a->GoEast();
  }
*/

 // Projectile to Alien Detect collision
  for(auto pup : projectilesup) {
    for(auto a : aliens) {
	if(pup->CollidesWith(a)) {
         pup->HandleCollision();
         a->HandleCollision();
         cout << "Projectile Hit Alien" << endl;
	 score = score +100;
         cout << "Total Score : " << score << endl;
	}
    }
  }

 for(auto pleft : projectilesleft) {
    for(auto a : aliens) {
	if(pleft->CollidesWith(a)) {
         pleft->HandleCollision();
         a->HandleCollision();
         cout << "Projectile Hit Alien" << endl;
	 score = score +100;
         cout << "Total Score : " << score << endl;
	}
    }
  }

 for(auto pdown : projectilesright) {
    for(auto a : aliens) {
	 if(pdown->CollidesWith(a)) {
         pdown->HandleCollision();
         a->HandleCollision();
         cout << "Projectile Hit Alien" << endl;
	 score = score +100;
         cout << "Total Score : " << score << endl;
	}
    }
  }

 for(auto pright : projectilesdown) {
    for(auto a : aliens) {
	if(pright->CollidesWith(a)) {
         pright->HandleCollision();
         a->HandleCollision();
         cout << "Projectile Hit Alien" << endl;
	 cout << "+100" << endl;
	 score = score +100;
         cout << "Total Score : " << score << endl;
	}
    }
  }

// Projectile to Wall Detect collision
  for(auto pup : projectilesup) {
    for(auto w : walls) {
      if(pup->CollidesWith(w)) {
         pup->HandleCollision();
         w->HandleCollision(); 
        cout << "Projectile Hit Wall" << endl;
      }
    }
  }
 for(auto pleft : projectilesleft) {
    for(auto w : walls) {
      if(pleft->CollidesWith(w)) {
         pleft->HandleCollision();
         w->HandleCollision(); 
        cout << "Projectile Hit Wall" << endl;
      }
    }
  }
 for(auto pdown : projectilesdown) {
    for(auto w : walls) {
      if(pdown->CollidesWith(w)) {
         pdown->HandleCollision();
         w->HandleCollision();
        cout << "Projectile Hit Wall" << endl;
      }
    }
  }
 for(auto pright : projectilesright) {
    for(auto w : walls) {
      if(pright->CollidesWith(w)) {
         pright->HandleCollision();
         w->HandleCollision();
        cout << "Projectile Hit Wall" << endl;
      }
    }
  }

// Player to Alien Detect collision
 for(auto a : aliens) {
   if(player->CollidesWith(a)) {
      player->HandleCollision();
      score = score -500;
     cout << "Player Hit Alien" << endl;
     cout << "-500" << endl;
     cout << "Total Score : " << score << endl;

   }
  }

//Player to Wall Detect collision    
 for(auto w : walls) {
   if(player->CollidesWith(w)) {
      auto pb = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
      auto v = player->GetPosition();
      pb->SetPosition(v);
     cout << "Player Hit Wall" << endl;
   }
  }

//Alien to Wall Detect collision 
  for(auto a : aliens) {
    for(auto w : walls) {
      if(a->CollidesWith(w)) {
         a->HandleCollision();
         w->HandleCollision();
      cout << "Alien Hit Wall" << endl;
      }
    }
  }

//Player to Diamond collision
 for(auto d : diamondC) {
   if(player->CollidesWith(d)) {
      d->HandleCollision();
      collectable++;
      score = score +550;
     cout << "Player Hit Diamond" << endl;
   }
  }

//Player to Ruby collision
 for(auto r : rubyC) {
   if(player->CollidesWith(r)) {
      r->HandleCollision();
      collectable++;
      score = score +450;
     cout << "Player Hit Ruby" << endl;
   }
  }

//Player to Emerald collision
 for(auto e : emeraldC) {
   if(player->CollidesWith(e)) {
      e->HandleCollision();
      collectable++;
      score = score +750;
     cout << "Player Hit Emerald" << endl;
   }
  }

//Player to Sapphire collision
 for(auto s : sapphireC) {
   if(player->CollidesWith(s)) {
      s->HandleCollision();
      collectable++;
      score = score +250;
     cout << "Player Hit Sapphire" << endl;
   }
  }


// Remove destoried aliens (the long way)
  list<shared_ptr<SFAsset>> tmpAlien;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmpAlien.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmpAlien);

// Remove destoried diamond (the long way)
  list<shared_ptr<SFAsset>> tmpDiamondC;
  for(auto d : diamondC) {
    if(d->IsAlive()) {
      tmpDiamondC.push_back(d);
    }
  }
  diamondC.clear();
  diamondC = list<shared_ptr<SFAsset>>(tmpDiamondC);

// Remove destoried ruby (the long way)
  list<shared_ptr<SFAsset>> tmpRubyC;
  for(auto r : rubyC) {
    if(r->IsAlive()) {
      tmpRubyC.push_back(r);
    }
  }
  rubyC.clear();
  rubyC = list<shared_ptr<SFAsset>>(tmpRubyC);

// Remove destoried diamond (the long way)
  list<shared_ptr<SFAsset>> tmpEmeraldC;
  for(auto e : emeraldC) {
    if(e->IsAlive()) {
      tmpEmeraldC.push_back(e);
    }
  }
  emeraldC.clear();
  emeraldC = list<shared_ptr<SFAsset>>(tmpEmeraldC);

// Remove destoried diamond (the long way)
  list<shared_ptr<SFAsset>> tmpSapphireC;
  for(auto s : sapphireC) {
    if(s->IsAlive()) {
      tmpSapphireC.push_back(s);
    }
  }
  sapphireC.clear();
  sapphireC = list<shared_ptr<SFAsset>>(tmpSapphireC);


// Remove projectilesup (the long way)
  list<shared_ptr<SFAsset>> tmpProjectileup;
  for(auto pup : projectilesup) {
    if(pup->IsAlive()) {
      tmpProjectileup.push_back(pup);
    }
  }
  projectilesup.clear();
  projectilesup = list<shared_ptr<SFAsset>>(tmpProjectileup);

// Remove projectilesleft (the long way)
  list<shared_ptr<SFAsset>> tmpProjectileleft;
  for(auto pleft : projectilesleft) {
    if(pleft->IsAlive()) {
      tmpProjectileleft.push_back(pleft);
    }
  }
  projectilesleft.clear();
  projectilesleft = list<shared_ptr<SFAsset>>(tmpProjectileleft);

// Remove projectilesdown (the long way)
  list<shared_ptr<SFAsset>> tmpProjectiledown;
  for(auto pdown : projectilesdown) {
    if(pdown->IsAlive()) {
      tmpProjectiledown.push_back(pdown);
    }
  }
  projectilesdown.clear();
  projectilesdown = list<shared_ptr<SFAsset>>(tmpProjectiledown);

// Remove projectilesright (the long way)
  list<shared_ptr<SFAsset>> tmpProjectileright;
  for(auto pright : projectilesright) {
    if(pright->IsAlive()) {
      tmpProjectileright.push_back(pright);
    }
  }
  projectilesright.clear();
  projectilesright = list<shared_ptr<SFAsset>>(tmpProjectileright);

// Remove destoried walls (the long way)
  list<shared_ptr<SFAsset>> tmpWall;
  for(auto w : walls) {
    if(w->IsAlive()) {
      tmpWall.push_back(w);
    }
  }
  walls.clear();
  walls = list<shared_ptr<SFAsset>>(tmpWall);

// INIALISE END OF GAME ~~ repeats atm
 for(auto a : aliens) {
  for(auto w : walls) {
   if (collectable == 4){
								// Place Player
	a->SetNotAlive();  // Clear Aliens
	w->SetNotAlive();  // Clear Walls
	cout << "GAME OVER" << endl;
	cout << "Total Score : " << score << endl;
        
       int canvas_w, canvas_h;
       SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);
	// Reposition Player
  	player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  	auto player_pos = Point2((canvas_w/2), 88.0f);
  	player->SetPosition(player_pos);
	// Place End Game
       auto endgame = make_shared<SFAsset>(SFASSET_ENDGAME, sf_window);
       auto pos   = Point2(canvas_w/2, (canvas_h/2)+150);
       endgame->SetPosition(pos);
       endgames.push_back(endgame);

    }
   }
  }

}// closes SFApp::OnUpdateWorld

void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

// Draw the Assets

  player->OnRender();

  for(auto pup: projectilesup) {
    if(pup->IsAlive()) {pup->OnRender();}
  }
  for(auto pleft: projectilesleft) {
    if(pleft->IsAlive()) {pleft->OnRender();}
  }
  for(auto pdown: projectilesdown) {
    if(pdown->IsAlive()) {pdown->OnRender();}
  }
  for(auto pright: projectilesright) {
    if(pright->IsAlive()) {pright->OnRender();}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto d: diamondC) {
    if(d->IsAlive()) {d->OnRender();}    
  }

  for(auto r: rubyC) {
    if(r->IsAlive()) {r->OnRender();}    
  }

  for(auto e: emeraldC) {
    if(e->IsAlive()) {e->OnRender();}    
  }

  for(auto s: sapphireC) {
    if(s->IsAlive()) {s->OnRender();}    
  }

  for(auto w: walls) {
    w->OnRender();
  }

  for(auto eg: endgames) {
    eg->OnRender();
  }

  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}

void SFApp::FireProjectileUp() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILEUP, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectilesup.push_back(pb);
}

void SFApp::FireProjectileLeft() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILELEFT, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectilesleft.push_back(pb);
}

void SFApp::FireProjectileDown() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILEDOWN, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectilesdown.push_back(pb);
}

void SFApp::FireProjectileRight() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILERIGHT, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectilesright.push_back(pb);
}


