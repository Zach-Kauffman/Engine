#include "MainMenu.hpp"


MainMenu::MainMenu()
{

}

void MainMenu::initialize(ResourceManager* resources, const sf::Vector2f& windowSize)
{
	size = windowSize;

	recMan = resources;

	MenuElement* background;
	background = new MenuSprite(recMan->getTexturePointerByName("MenuBackground"), sf::Vector2f(0, 0), sf::Vector2f(size.x, size.y));

	MenuElement* startButton;
	startButton = new BasicButton(sf::Vector2f(size.x / 2, size.y / 6), recMan->getResourceGroupByName("MenuButton"), "Start", sf::Color::Black, sf::Vector2f(300, 100), 10, 10);

	MenuElement* optionsButton;
	optionsButton = new BasicButton(sf::Vector2f(size.x / 2, size.y / 2), recMan->getResourceGroupByName("MenuButton"), "Options", sf::Color::Black, sf::Vector2f(300, 100), 10, 10);
	
	MenuElement* quitButton;
	quitButton = new BasicButton(sf::Vector2f(size.x / 2, 2 * size.y / 3), recMan->getResourceGroupByName("MenuButton"), "Quit", sf::Color::Black, sf::Vector2f(300, 100), 10, 10);

	Menu mainMenu;

	mainMenu.addMenuElement(background, "background");
	mainMenu.addMenuElement(startButton, "startButton");
	mainMenu.addMenuElement(optionsButton, "optionsButton");
	mainMenu.addMenuElement(quitButton, "quitButton");


	///////////////////////////HIGHLY UNSTABLE OPTIONS MENU BELOW//////////////////////////////////

	
	
	MenuElement* backButton;
	backButton = new BasicButton(sf::Vector2f(size.x / 2, size.y / 6), recMan->getResourceGroupByName("MenuButton"), "Back", sf::Color::Black, sf::Vector2f(300, 100), 10, 10);

	MenuElement* volumeSlider;
	volumeSlider = new Slider(sf::Vector2f(size.x / 2, size.y / 2), *recMan->getTexturePointerByName("SliderBackground"), *recMan->getTexturePointerByName("OptionsSlider"), 100, 0, 50, "Volume", 30);

	MenuElement* brightnessSlider;
	brightnessSlider = new Slider(sf::Vector2f(size.x / 2, 3 * size.y / 4), *recMan->getTexturePointerByName("SliderBackground"), *recMan->getTexturePointerByName("OptionsSlider"), 100, 0, 50, "Brightness", 30);

	Menu optionsMenu;

	optionsMenu.addMenuElement(backButton, "backButton");
	optionsMenu.addMenuElement(volumeSlider, "volumeSlider");
	optionsMenu.addMenuElement(brightnessSlider, "brightnessSlider");

	optionsMenu.deactivate();
	

	

	this->addMenu(mainMenu, "mainMenu", sf::Vector2f(0, 0));
	this->addMenu(optionsMenu, "optionsMenu", sf::Vector2f(0, 0));

	/*
	boost::function<void()> boundFxn = boost::bind(&Game::begin, this);			 //goes in game
	setButtonCallback("start", "startButton", boundFxn, 12);
	*/

	boost::function<void()> boundFxn = boost::bind(&Menu::deactivate, this->getMenuPtr("mainMenu"));						 //MainMenu
	setButtonCallback("main", "optionsButton", boundFxn, 12);

	boundFxn = boost::bind(&Menu::activate, this->getMenuPtr("optionsMenu"));						 //OptionsMenu
	setButtonCallback("options", "optionsButton", boundFxn, 12);
	
	
	

}

void MainMenu::setButtonCallback(const std::string menuName, const std::string& buttonName, boost::function<void()> fxn, int buttonState)
{
	Menu* menu = this->getMenuPtr(menuName);
	BasicButton* but = static_cast<BasicButton*>(menu->getPointerToElementByName(buttonName).get());
	but->addFunctionOnButtonState(fxn, buttonState);
}


MainMenu::~MainMenu()
{
}
