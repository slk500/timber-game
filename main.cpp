#include <SFML/Graphics.hpp>
#include <experimental/random> 

using namespace sf;

  VideoMode vm(1920, 1080);
  RenderWindow window(vm, "Timber Game", Style::Fullscreen);   

void exit_game_on_kbd_escape(){

  if (Keyboard::isKeyPressed(Keyboard::Escape)) {
    window.close();
  }
  
}

int main()
{
  Texture textureBackground;
  textureBackground.loadFromFile("assets/graphics/background.png");

  Sprite spriteBackground;
  spriteBackground.setTexture(textureBackground);
  spriteBackground.setPosition(0,0);

  //tree
  Texture textureTree;
  textureTree.loadFromFile("assets/graphics/tree.png");
  Sprite spriteTree;
  spriteTree.setTexture(textureTree);
  spriteTree.setPosition(810,0);

  //bee
  Texture textureBee;
  textureBee.loadFromFile("assets/graphics/bee.png");
  Sprite spriteBee;
  spriteBee.setTexture(textureBee);
  bool beeActive = false;
   
  //clouds
  Texture textureCloud;
  textureCloud.loadFromFile("assets/graphics/cloud.png");
  Sprite spriteCloud;
  spriteCloud.setTexture(textureCloud);
  spriteCloud.setPosition(0,250);

  int off_the_screen_position_x = 2000;
  int bee_y_position = 250;
  spriteBee.setPosition(off_the_screen_position_x, bee_y_position);
  
  bool cloudActive = false;
  float cloudSpeed = 0.0f;
   
  Clock clock;
   
  while(window.isOpen())
    {
      exit_game_on_kbd_escape();
	
      Time dt = clock.restart();

      int beeSpeed = std::experimental::randint(200,400); 
      int bee_x_position = spriteBee.getPosition().x - (beeSpeed * dt.asSeconds());
      spriteBee.setPosition(bee_x_position, bee_y_position);	 
      if (spriteBee.getPosition().x < 1){
	spriteBee.setPosition(2000, 250);
      }

      
      //clear previous frame
      window.clear();

      //draw game scene
      window.draw(spriteBackground);

      window.draw(spriteCloud);
      window.draw(spriteTree);
      window.draw(spriteBee);
       
      //draw new frame
      window.display();
    }
   
  return 0;  
}
