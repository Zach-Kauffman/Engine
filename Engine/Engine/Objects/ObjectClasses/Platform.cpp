#include "Platform.hpp"

Platform::Platform()
{
    colliding = true;
    isActive = true;
}


    Platform::Platform(const sf::Vector2f& pos, const double& width, const double& height, sf::Texture* tex)
    {
            setup(pos, width, height, tex);

    }

    Platform::Platform(const sf::Vector2f& TL, const sf::Vector2f& BR, sf::Texture* tex)
    {
        setup(TL, BR, tex);

    }


Platform::~Platform()
{


}


    void Platform::setup(const sf::Vector2f& pos, const double& width, const double& height, sf::Texture* tex)
    {
            position = pos;
            siz = sf::Vector2f(width, height);
            sprite.setup(tex, sf::Vector2f(0,0), siz, 0);


    }

    void Platform::setup(const sf::Vector2f& TL, const sf::Vector2f& BR, sf::Texture* tex)
    {

        setup(sf::Vector2f((BR.x + TL.x) / 2, (BR.y + TL.y) / 2), BR.x - TL.x, BR.y - TL.y, tex);
    }

void Platform::draw(Layer& renderTarget)
{
   sprite.draw(renderTarget, position);
}		//renders object to given sf::RenderTexture&



void Platform::load(boost::property_tree::ptree& dataTree, ResourceManager&)
{

}	//defined in children to load from (INI?) file
void Platform::write()
{

}

sf::Vector2f Platform::getTlCorner()
{
    return sf::Vector2f(pos.x - siz.x / 2, pos.y - siz.y / 2);
}

sf::Vector2f Platform::getBRCorner()
{
     return sf::Vector2f(pos.x + siz.x / 2, pos.y + siz.y / 2);
}
