#include "PickupZone.hpp"

using namespace objects;

PickupZone::PickupZone()
{
	displaying = true;
}


PickupZone::~PickupZone()
{
}



void PickupZone::setManagerPtrs(ResourceManager& rman, ObjectManager& obMan)
{
	resMan = &rman;
	objMan = &obMan;
}


void PickupZone::draw(Layer& renderTarget)
{
	if (displaying)
	{
		if (!isActive){ return; }
		tex.update();
		tex.draw(*renderTarget.getRenderTexture());
	}
}

void PickupZone::update(InputData& inpData)
{
	if (!isActive){ return; }
	for (int pickIt = 0; pickIt < pickups.size(); pickIt++)
	{
		if (pickups[pickIt] == NULL)	//if the pickup has been deleted (picked up)
		{
			pickups.erase(pickups.begin()+pickIt);	//erase it
			pickIt -= 1;							//move back b/c vector is shorter now
		}
	}
}

void PickupZone::load(boost::property_tree::ptree& dataTree, ResourceManager& rman)
{
	XMLParser parser;
	parser.readValue<double>("y_value", yVal, dataTree);	//loading x coord
	parser.readValue<double>("x_value_left", xValLeft, dataTree);	//loading y coord
	parser.readValue<double>("x_value_right", xValRight, dataTree);
	parser.readValue<double>("thickness", thickness, dataTree);
	parser.readValue<double>("gap_distance", gapDist, dataTree);
	parser.readValue<std::string>("season_name", seasonName, dataTree);

	//resMan = &rman;

	size = sf::Vector2f(xValRight - xValLeft, thickness);
	position = sf::Vector2f((xValRight + xValLeft) / 2, yVal + thickness/2);


	//loading texture

	parser.readValue<std::string>("texture", textureName, dataTree);

	sf::Texture* tmpTex = rman.getTexturePointerByName(textureName);
	
	tex = Texture(tmpTex, &position, &size);
}


boost::property_tree::ptree PickupZone::write()
{
	boost::property_tree::ptree properties;
	properties.put("y_value", yVal);
	properties.put("x_value_left", xValLeft);
	properties.put("x_value_right", xValLeft); 
	properties.put("season_name", seasonName);
	properties.put("thickness", thickness);
	properties.put("gap_distance", gapDist);
	properties.put("texture_name", textureName);
	properties.put("type", type);

	return properties;
}


void PickupZone::changeSeason(const std::string& newSeason)
{
	seasonName = newSeason;
}


void PickupZone::generatePickup()
{

	typedef std::map<std::pair<int, int>, std::string>::iterator it_type;



	int randNum = rand() % distrMax;

	std::string typName;
	for (it_type iterator = distribution.begin(); iterator != distribution.end(); iterator++) {

		// iterator->first = key
		// iterator->second = value
		if (isInBounds(randNum, iterator->first))
		{
			typName = iterator->second;
		}
	}


	double randXPos = rand() / RAND_MAX * (xValRight - xValLeft) + xValLeft;
	

	const sf::Vector2f default_size(100, 100);

	boost::shared_ptr<Object> protoPickup = objMan->getPrototype("Pickup");

	boost::shared_ptr<Pickup> newPickup = util::downcast<Pickup>(protoPickup);
	newPickup->setup(sf::Vector2f(randXPos, yVal + default_size.y / 2 + gapDist), default_size, seasonName, typName, *resMan);

	objMan->addObject(protoPickup, "Layers.Layer0");
	objMan->addObject(protoPickup, "Collidables");
}

void PickupZone::createDistribution()
{
	distribution.clear();
	double sum = 0;


	std::string snames[2] = { "YearRound", seasonName };
	std::vector<std::string> pickupNames;
	std::vector<double> rarities;



	INIParser options("PickupList.ini");

	for (unsigned int j = 0; j < 2; j++)
	{
		
		options.setSection(snames[j]);

		std::string keystr;
		int maxValue;
		options.readValue<std::string>("Key", keystr);
		options.readValue<int>("Max", maxValue);


		for (unsigned int i = 0; i < maxValue; i++)
		{
			std::string numstr = boost::lexical_cast<std::string>(i + 1);

			std::string pname;
			options.readValue<std::string>(keystr + numstr, pname);

			pickupNames.push_back(pname);

		}
	}


	double sumOld = 0;
	for (unsigned int i = 0; i < pickupNames.size(); i++)
	{
		options.setSection(pickupNames[i]);
		double tmprar;
		options.readValue<double>("Rarity", tmprar);

		distribution[std::make_pair(sumOld, sum)] = pickupNames[i];

	}

	distrMax = sum;
}


bool PickupZone::isInBounds(const int& val, const std::pair<int, int>& bound)
{
	return ((val < bound.second) && (val >= bound.first));
}
