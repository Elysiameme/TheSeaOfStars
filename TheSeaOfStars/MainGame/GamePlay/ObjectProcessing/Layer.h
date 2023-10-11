#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>


	using namespace std;

	enum RENDERSETTINGS
	{
		RENDERALL = 1,
		RENDERBYCHOOSE = 2
	};
	struct Object
	{
		void* ObjectAddress;
		string ObjectName;
		int TilesPosX, TilesPosY;
	};
	
	class Layer
	{
	private:
		int Render_Order;
		Uint8 Transparency;
		vector<Object> ObjectList;
	public:
		void GetRenderOrder(int Order)
		{
			Render_Order = Order;
		}
		template <class TemplateClass>
		void AddObjectToLayer(TemplateClass* ObjectAddToLayer, const char* Name, int TilePosX, int TilePosY)
		{
			if (ObjectAddToLayer)
			{
				Object Add;
				Add.ObjectAddress = ObjectAddToLayer;
				Add.ObjectName = Name;
				Add.TilesPosX = TilePosX;
				Add.TilesPosY = TilePosY;
				ObjectList.push_back(Add);
			}			
			else
				cout << "Error : The Object Pointer Is NULL!";
		}
		void Render(RENDERSETTINGS mode);
	};

	
	void Layer::Render(RENDERSETTINGS mode)
	{
		if (mode == RENDERALL)
		{
			for (int i = 0; i < ObjectList.size(); i++)
			{

			}
		}
	}
