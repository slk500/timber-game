#include <SFML/Graphics.hpp>
#include <experimental/random> 
#include <sstream>

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
  
  //clouds
  Texture textureCloud;
  textureCloud.loadFromFile("assets/graphics/cloud.png");
  Sprite spriteCloud;
  spriteCloud.setTexture(textureCloud);

  int cloud_y_position = 100;
  spriteCloud.setPosition(-200, cloud_y_position);

  int off_the_screen_position_x = 2000;
  int bee_y_position = 500;
  spriteBee.setPosition(off_the_screen_position_x, bee_y_position);
   
  Clock clock;

  bool paused = true;

  int score = 0;

  sf::Text messageText;
  sf::Text scoreText;

  Font font;
  font.loadFromFile("assets/fonts/KOMIKAP_.ttf");

  messageText.setFont(font);
  scoreText.setFont(font);

  messageText.setString("Press Enter to start!");
  scoreText.setString("Score = 0");

  messageText.setCharacterSize(75);
  scoreText.setCharacterSize(100);

  messageText.setFillColor(Color::White);
  scoreText.setFillColor(Color::White);

  //Position the text
  FloatRect textRect = messageText.getLocalBounds();
  messageText.setOrigin(textRect.left +
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);
  messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
  scoreText.setPosition(20,20);
  
  while(window.isOpen())
    {
      exit_game_on_kbd_escape();

      if(Keyboard::isKeyPressed(Keyboard::Return)){
	paused = false;
      }

      if(!paused){
	
	Time dt = clock.restart();
	
	int beeSpeed = std::experimental::randint(200,400); 
	int bee_x_position = spriteBee.getPosition().x - (beeSpeed * dt.asSeconds());
	spriteBee.setPosition(bee_x_position, bee_y_position);	 

	if (spriteBee.getPosition().x < -100){
	  spriteBee.setPosition(off_the_screen_position_x, 250);
	}
	
	int cloudSpeed = std::experimental::randint(200,400); 
	int cloud_x_position = spriteCloud.getPosition().x - (cloudSpeed * dt.asSeconds());
	spriteCloud.setPosition(cloud_x_position, cloud_y_position);	 
	
	if (spriteCloud.getPosition().x < -300){
	  spriteCloud.setPosition(off_the_screen_position_x, cloud_y_position);
	}

	std::stringstream ss;
	ss << "Score = " << score;
	scoreText.setString(ss.str());
	
      }

      
      //clear previous frame
      window.clear();

      //draw game scene
      window.draw(spriteBackground);

      window.draw(spriteCloud);
      window.draw(spriteTree);
      window.draw(spriteBee);

      window.draw(scoreText);
      if(paused)
	{
	  window.draw(messageText);
	}
       
      //draw new frame
      window.display();
    }
   
  return 0;  
}
