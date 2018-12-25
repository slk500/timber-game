#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
   VideoMode vm(1920, 1080);

   RenderWindow window(vm, "Timber Game", Style::Fullscreen);

   return 0;  
}
