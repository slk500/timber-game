#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
   VideoMode vm(1920, 1080);

   RenderWindow window(vm, "Timber Game", Style::Fullscreen);   
   
   while(window.isOpen())
     {
       //handle player input
       if (Keyboard::isKeyPressed(Keyboard::Escape)) {
	 window.close();
       }

       //update the scene

       //clear previous frame
       window.clear();

       //draw new frame
       window.display();
     }
   
   return 0;  
}
