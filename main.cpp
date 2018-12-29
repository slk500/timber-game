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

//function declarations
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPosition[NUM_BRANCHES];

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

  int off_the_screen_position = 2000;
  int bee_y_position = 500;
  spriteBee.setPosition(off_the_screen_position, bee_y_position);

  //prepare 6 branches
  Texture textureBranch;
  textureBranch.loadFromFile("assets/graphics/branch.png");

  for (int i = 0; i < NUM_BRANCHES; ++i) {
    branches[i].setTexture(textureBranch);
    branches[i].setPosition(off_the_screen_position, off_the_screen_position);

    branches[i].setOrigin(220, 20);
  }

  //prepare the player
  Texture texturePlayer;
  texturePlayer.loadFromFile("assets/graphics/player.png");
  Sprite spritePlayer;
  spritePlayer.setTexture(texturePlayer);
  spritePlayer.setPosition(580,720);

  side playerSide = side::LEFT;

  Texture textureRIP;
  textureRIP.loadFromFile("assets/graphics/rip.png");
  Sprite spriteRIP;
  spriteRIP.setTexture(textureRIP);
  spriteRIP.setPosition(600, 860);

  Texture textureAxe;
  textureAxe.loadFromFile("assets/graphics/axe.png");
  Sprite spriteAxe;
  spriteAxe.setTexture(textureAxe);
  spriteAxe.setPosition(700, 830);

  //line the axe up with the tree
  const float AXE_POSITION_LEFT = 700;
  const float AXE_POSITION_RIGHT = 1075;

  //prepare flying log
  Texture textureLog;
  textureLog.loadFromFile("assets/graphics/log.png");
  Sprite spriteLog;
  spriteLog.setTexture(textureLog);
  spriteLog.setPosition(810, 720);
  
  //some other useful log related variables
  bool logActive = false;
  float logSpeedX = 1000;
  float logSpeedY = -1500;
  
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

  //time bar
  RectangleShape timeBar;
  float timeBarStartWidth = 400;
  float timeBarHeight = 80;
  timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
  timeBar.setFillColor(Color::Red);
  timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

  Time gameTimeTotal;
  float timeRemaining = 6.0f;
  float timeBarWitdhPerSecond = timeBarStartWidth / timeRemaining;
  
  
  while(window.isOpen())
    {
      exit_game_on_kbd_escape();

      if(Keyboard::isKeyPressed(Keyboard::Return)){
	paused = false;

	//reset the time and the score
	score = 0;
	timeRemaining = 5;
      }
      
      if(!paused){
	
	Time dt = clock.restart();
	
	//substract from the amout of time remaining
	timeRemaining -= dt.asSeconds();
	//size up the time bar
	timeBar.setSize(Vector2f(timeBarWitdhPerSecond *
				 timeRemaining, timeBarHeight));

	if(timeRemaining <= 0.0f)
	  {
	    paused = true;

	    messageText.setString("Out of time");

	    FloatRect textRect = messageText.getLocalBounds();
	    messageText.setOrigin(textRect.left +
				  textRect.width / 2.0f,
				  textRect.top +
				  textRect.height / 2.0f);
	    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	  }
	
	int beeSpeed = std::experimental::randint(200,400); 
	int bee_x_position = spriteBee.getPosition().x - (beeSpeed * dt.asSeconds());
	spriteBee.setPosition(bee_x_position, bee_y_position);	 

	if (spriteBee.getPosition().x < -100){
	  spriteBee.setPosition(off_the_screen_position, 250);
	}
	
	int cloudSpeed = std::experimental::randint(200,400); 
	int cloud_x_position = spriteCloud.getPosition().x - (cloudSpeed * dt.asSeconds());
	spriteCloud.setPosition(cloud_x_position, cloud_y_position);	 
	
	if (spriteCloud.getPosition().x < -300){
	  spriteCloud.setPosition(off_the_screen_position, cloud_y_position);
	}

	std::stringstream ss;
	ss << "Score = " << score;
	scoreText.setString(ss.str());

	//update the branch sprites
	for (int i = 0; i < NUM_BRANCHES; ++i) {
	    
	  float height = i * 150;
	  
	  if(branchPosition[i] == side::LEFT) {

	    branches[i].setPosition(610, height);
	    branches[i].setRotation(180);
	  }
	  else if (branchPosition[i] == side::RIGHT)
	    {
	      branches[i].setPosition(1330, height);
	      branches[i].setRotation(0);
	    }
	  else {
	    branches[i].setPosition(3000, height);
	  }
	  
	}
	
	
      }
      
      //clear previous frame
      window.clear();

      //draw game scene
      window.draw(spriteBackground);

      window.draw(spriteCloud);

      for (int i = 0; i < NUM_BRANCHES; ++i) {
	window.draw(branches[i]);
      }


      window.draw(spriteTree);

      window.draw(spritePlayer);

      window.draw(spriteAxe);

      window.draw(spriteLog);

      window.draw(spriteRIP);
      
      window.draw(spriteBee);

      window.draw(scoreText);

      window.draw(timeBar);
      
      if(paused)
	{
	  window.draw(messageText);
	}
       
      //draw new frame
      window.display();
    }
   
  return 0;  
}

void updateBranches(int seed)
{
  for (int i = NUM_BRANCHES - 1; i > 0; i--) {
    branchPosition[i] = branchPosition[i - 1];
  }

  srand((int)time(0) + seed);
  int r = (rand() % 5);
  switch(r)
    {
    case 0:
      branchPosition[0] = side::LEFT;
      break;

    case 1:
      branchPosition[0] = side::RIGHT;
      break;

    default:
      branchPosition[0] = side::NONE;
      break;

    }
  
}
