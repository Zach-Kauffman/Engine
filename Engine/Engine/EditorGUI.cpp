#include "EditorGUI.hpp"

EditorGUI::EditorGUI()
{
	popData = false;
}

EditorGUI::~EditorGUI()
{

}

void EditorGUI::initialize(ResourceManager* resources)
{
	recMan = resources;	//set local resource manager


	MenuElement* selectedLayer;	//entry table
	selectedLayer = new EntryTable(50, 50, 20, sf::Vector2f(500, 500), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 20);
	//selectedLayer = new EntryTextBox(recMan->getFontPointerByName("EditorFont"), 5, sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(300, 150), recMan->getTexturePointerByName("EditorEntryBar"), sf::Vector2f(100, 200), 20);

	MenuElement* selectedObject;	//entry table
	selectedObject = new EntryTable(50, 50, 20, sf::Vector2f(500, 500), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 20);

	MenuElement* selectedResource;	//entry table
	selectedResource = new EntryTable(50, 50, 20, sf::Vector2f(500, 500), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 20);

	MenuElement* attributeEditor;	//entry table
	attributeEditor = new EntryTable(50, 50, 20, sf::Vector2f(500, 500), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 200);

	MenuElement* updateButton;
	updateButton = new BasicButton(sf::Vector2f(200, 800), recMan->getResourceGroupByName("EditorButton"), "Update Selection", sf::Color::Black, sf::Vector2f(200, 200), 10);

	MenuElement* newObject;	//button
	newObject = new BasicButton(sf::Vector2f(600, 800), recMan->getResourceGroupByName("EditorButton"), "New Object", sf::Color::Black, sf::Vector2f(200, 200), 12);

	MenuElement* newResource;	//button
	newResource = new BasicButton(sf::Vector2f(0, 800), recMan->getResourceGroupByName("EditorButton"), "New Resource", sf::Color::Black, sf::Vector2f(200, 200), 12);

	MenuElement* save;	//button
	save = new BasicButton(sf::Vector2f(400, 900), recMan->getResourceGroupByName("EditorButton"), "Save", sf::Color::Black, sf::Vector2f(200, 200), 14);

	
	Menu editorMenu;

	editorMenu.addMenuElement(selectedLayer, "selectedLayer");
	editorMenu.addMenuElement(selectedObject, "selectedObject");
	editorMenu.addMenuElement(selectedResource, "selectedResource");
	editorMenu.addMenuElement(attributeEditor, "attributeEditor");
	editorMenu.addMenuElement(updateButton, "updateButton");
	editorMenu.addMenuElement(newObject, "newObject");
	editorMenu.addMenuElement(newResource, "newResource");
	editorMenu.addMenuElement(save, "save");
	
	MenuElement* input;
	input = new EntryTable(50, 50, 20, sf::Vector2f(0, 0), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 20);

	MenuElement* okButton;
	okButton = new BasicButton(sf::Vector2f(0, 100), recMan->getResourceGroupByName("EditorButton"), "OK", sf::Color::Black, sf::Vector2f(100, 100), 10);

	MenuElement* cancelButton;
	cancelButton = new BasicButton(sf::Vector2f(200, 100), recMan->getResourceGroupByName("EditorButton"), "CANCEL", sf::Color::Black, sf::Vector2f(100, 100), 10);

	Menu popup;

	popup.addMenuElement(input, "input");
	popup.addMenuElement(okButton, "okButton");
	popup.addMenuElement(cancelButton, "cancelButton");

	this->addMenu(editorMenu, "editorMenu", sf::Vector2f(0, 0));
	this->addMenu(popup, "popup", sf::Vector2f(950, 540));

	this->getMenuPointerByName("popup")->deactivate();

	boost::function<void()> boundFxn = boost::bind(&EditorGUI::popup_OK, this);
	setButtonCallback("popup", "okButton", boundFxn, 12);

	boundFxn = boost::bind(&EditorGUI::popup_CANCEL, this);
	setButtonCallback("popup", "cancelButton", boundFxn, 12);

}

void EditorGUI::popup(std::map<std::string, std::string>& input)
{
	Menu* popup = this->getMenuPointerByName("popup");
	popup->activate();
	setMap("popup", "input", input);
}

void EditorGUI::popdown(bool which)
{
	this->getMenuPointerByName("popup")->deactivate();
	popData = which;
}

void EditorGUI::setMap(const std::string& menuName, const std::string& tableName, std::map<std::string, std::string>& newAttributes)
{
	Menu* editor = this->getMenuPointerByName(menuName);
	EntryTable* attributes = static_cast<EntryTable*>(editor->getPointerToElementByName(tableName));
	attributes->setMap(newAttributes);
}

void EditorGUI::setButtonCallback(const std::string menuName, const std::string& buttonName, boost::function<void()> fxn, int buttonState)
{
	Menu* menu = this->getMenuPointerByName(menuName);
	BasicButton* but = static_cast<BasicButton*>(menu->getPointerToElementByName(buttonName));
	but->addFunctionToDoOnButtonState(fxn, buttonState);
}

bool EditorGUI::getPopData()
{
	return popData;
}

void EditorGUI::setPopData(const bool& newData)
{
	popData = newData;
}

//PRIVATE FUNCTIONS

void EditorGUI::popup_OK()
{
	popdown(1);
}

void EditorGUI::popup_CANCEL()
{
	popdown(0);
}