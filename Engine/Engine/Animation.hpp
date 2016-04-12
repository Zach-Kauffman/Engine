#include <SFML\Graphics.hpp>
#include "boost/timer/timer.hpp"

class Animation
{
public:

	Animation();
	Animation(const sf::Texture* sprites, int fps);
	~Animation();

	void setFPS(const int& newFPS);
	int getFPS();

	void setSpriteSheet(const sf::Texture* newSprites);
	sf::Texture* getSpriteSheet();

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition();

	void drawNextFrame(sf::RenderTexture& texture);

private:
	void prepareNextFrame();

	int fps;						//the frames per second of the animation
	boost::timer::cpu_timer timer;	//clock object for determining which frame to draw
	
	sf::Vector2f textureAmounts;
	sf::Vector2f frameSize;
	sf::Texture* spriteSheet;

	sf::Vector2f texCoords;			//coordinates on the spritesheet for drawing frame
	sf::Vector2f position;

};