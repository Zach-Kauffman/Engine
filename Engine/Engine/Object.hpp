#pragma once

//sfml includes
#include "SFML/Graphics.hpp"

//project includes
#include "Utilities.hpp"

namespace objects
{
	class Object	//virtual class template for basic Object type
	{
	public:
		Object();
		~Object();

		//public interfaces to private members
		int getID();
		void setID(int newID);

		bool getActive();
		void setActive(bool activity);


		//base virtual functions
		virtual void draw(sf::RenderTexture& renderTarget) = 0;		//renders object to given sf::RenderTexture&
		virtual void update() = 0;

		virtual void load() = 0;	//defined in children to load from (INI?) file
		virtual void write() = 0;	//defined in children to write to (INI?) file

	private:
		int ID;				//unique ID for this instance of object
		bool isActive;		//wether or not the object will be drawn/updated etc
	};
}
