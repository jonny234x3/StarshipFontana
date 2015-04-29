#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp(std::shared_ptr<SFWindow>);
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  void    OnUpdateWorld();
  void    OnRender();
  void    FireProjectileUp();
  void    FireProjectileLeft();
  void    FireProjectileDown();
  void    FireProjectileRight();

private:
  SDL_Surface           * surface;
  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectilesup;
  list<shared_ptr<SFAsset> > projectilesleft;
  list<shared_ptr<SFAsset> > projectilesdown;
  list<shared_ptr<SFAsset> > projectilesright;
  list<shared_ptr<SFAsset> > aliens;
  list<shared_ptr<SFAsset> > walls;
  list<shared_ptr<SFAsset> > diamondC;
  list<shared_ptr<SFAsset> > rubyC;
  list<shared_ptr<SFAsset> > emeraldC;
  list<shared_ptr<SFAsset> > sapphireC;
  list<shared_ptr<SFAsset> > endgames;

  int fire1;
  int fire2;
  int fire3;
  int fire4;
  int score = 0;
  int collectable = 0;
  SFError OnInit();
};
#endif
