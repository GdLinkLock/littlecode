// 01abstractfactory.cpp : Defines the entry point for the console application.
//演示抽象工厂模式

#include "stdafx.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>

constexpr int MOBIKE_HANDLERBAR_LENGTH = 25;//摩拜单车 车把长度
constexpr int OFOBIKE_HANDELERBAR_LENGTH = 30;//摩拜单车 车轮半径
constexpr int MOBIKE_WHELL_RADIUS = 40;//ofo单车 车把长度
constexpr int OFOBIKE_WHEEL_RADIUS = 43;//ofo单车 车轮半径
class Handlerbar
{
public:
	Handlerbar() {}
	~Handlerbar() {}
	virtual int GetLength() const { return 0; }
};
class MobikeHandlerbar :public Handlerbar
{
public:
	MobikeHandlerbar() {}
	~MobikeHandlerbar() {}
	virtual int GetLength() const { return MOBIKE_HANDLERBAR_LENGTH; }
};
class OfobikeHandlerbar :public Handlerbar
{
public:
	OfobikeHandlerbar() {}
	~OfobikeHandlerbar() {}
	virtual int GetLength() const { return OFOBIKE_HANDELERBAR_LENGTH; }
};

class Wheel
{
public:
	Wheel() {}
	~Wheel() {}
	virtual int GetRadius() const { return 0; }
};

class MobikeWheel :public Wheel
{
public:
	MobikeWheel() {}
	~MobikeWheel() {}
	virtual int GetRadius() const { return MOBIKE_WHELL_RADIUS; }
};
class OfobikeWheel :public Wheel
{
public:
	OfobikeWheel() {}
	~OfobikeWheel() {}
	virtual int GetRadius() const { return OFOBIKE_WHEEL_RADIUS; }
};

class BikeFactory
{
public:
	BikeFactory() {}
	virtual ~BikeFactory()
	{
		for (auto& ptr : handlerbarCon)
		{
			delete ptr;
		}
		handlerbarCon.clear();
		for (auto& ptr : wheelCon)
		{
			delete ptr;
		}
		wheelCon.clear();
	}
	virtual Handlerbar* ManufactureHandlerbar() { return nullptr; }
	virtual Wheel* ManufactureWheel() { return nullptr; }

protected:
	std::vector<Handlerbar*> handlerbarCon;
	std::vector<Wheel*> wheelCon;
};

class MobikeFactory :public BikeFactory
{
public:
	virtual Handlerbar* ManufactureHandlerbar()
	{
		auto hb= new MobikeHandlerbar;
		handlerbarCon.push_back(hb);
		return hb;
	}
	virtual Wheel* ManufactureWheel()
	{
		auto mw= new MobikeWheel;
		wheelCon.push_back(mw);
		return mw;
	}
};

class OfobikeFactory :public BikeFactory
{
public:
	virtual Handlerbar* ManufactureHandlerbar()
	{
		auto hb = new OfobikeHandlerbar;
		handlerbarCon.push_back(hb);
		return hb;
	}
	virtual Wheel* ManufactureWheel()
	{
		auto ow = new OfobikeWheel;
		wheelCon.push_back(ow);
		return ow;
	}
};



class Client
{
public:
	void MakeMobike()
	{
		BikeFactory* bf = new MobikeFactory;
		Handlerbar* hb = bf->ManufactureHandlerbar();
		Wheel* wl = bf->ManufactureWheel();

		std::cout << "Mobike Handlerbar length=" << hb->GetLength() << std::endl;
		std::cout << "Mobike Wheel radius=" << wl->GetRadius() << std::endl;
	}
	void MakeOfobike()
	{
		BikeFactory* bf = new OfobikeFactory;
		Handlerbar* hb = bf->ManufactureHandlerbar();
		Wheel* wl = bf->ManufactureWheel();

		std::cout << "Ofobike Handlerbar length=" << hb->GetLength() << std::endl;
		std::cout << "Ofobike Wheel radius=" << wl->GetRadius() << std::endl;
	}
};

int main()
{
	std::shared_ptr<Client> pclient(new Client);
	pclient->MakeMobike();
	pclient->MakeOfobike();
	system("pause");
    return 0;
}
