#include "MenuStuff\MenuManager.hpp"
#include "Input\KeyboardData.hpp"
#include "Input\MouseData.hpp"
#include "boost\function.hpp"
#include "boost\bind.hpp"

class MainMenu : public MenuManager
{
public:
	MainMenu(sf::RenderWindow& window);

	~MainMenu();

	void initialize(ResourceManager* resources);

	void setButtonCallback(const std::string menuName, const std::string& buttonName, boost::function<void()> fxn, int buttonStates);

private:

	ResourceManager* recMan;
	sf::Vector2f size;
};

