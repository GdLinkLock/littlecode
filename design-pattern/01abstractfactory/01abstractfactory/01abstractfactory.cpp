// 01abstractfactory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <memory>
class Handlerbar
{
public:
	Handlerbar() {}
	~Handlerbar() {}
	virtual int GetLength() const { return 12; }
};
class MobikeHandlerbar :public Handlerbar
{
public:
	MobikeHandlerbar() {}
	~MobikeHandlerbar() {}
	virtual int GetLength() const { return 22; }
};
class OfobikeHandlerbar :public Handlerbar
{
public:
	OfobikeHandlerbar() {}
	~OfobikeHandlerbar() {}
	virtual int GetLength() const { return 32; }
};

class Wheel
{
public:
	Wheel() {}
	~Wheel() {}
	virtual int GetRadius() const { return 25; }
};

class MobikeWheel :public Wheel
{
public:
	MobikeWheel() {}
	~MobikeWheel() {}
	virtual int GetRadius() const { return 30; }
};
class OfobikeWheel :public Wheel
{
public:
	OfobikeWheel() {}
	~OfobikeWheel() {}
	virtual int GetRadius() const { return 40; }
};

class BikeFactory
{
public:
	virtual Handlerbar* ManufactureHandlerbar() { return nullptr; }
	virtual Wheel* ManufactureWheel() { return nullptr; }
};

class MobikeFactory :public BikeFactory
{
public:
	virtual Handlerbar* ManufactureHandlerbar()
	{
		return new MobikeHandlerbar;
	}
	virtual Wheel* ManufactureWheel()
	{
		return new MobikeWheel;
	}
};

class OfobikeFactory :public BikeFactory
{
public:
	virtual Handlerbar* ManufactureHandlerbar()
	{
		return new OfobikeHandlerbar;
	}
	virtual Wheel* ManufactureWheel()
	{
		return new OfobikeWheel;
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

		delete wl;
		delete hb;
		delete bf;
	}
	void MakeOfobike()
	{
		BikeFactory* bf = new OfobikeFactory;
		Handlerbar* hb = bf->ManufactureHandlerbar();
		Wheel* wl = bf->ManufactureWheel();

		std::cout << "Ofobike Handlerbar length=" << hb->GetLength() << std::endl;
		std::cout << "Ofobike Wheel radius=" << wl->GetRadius() << std::endl;

		delete wl;
		delete hb;
		delete bf;
	}
};

int main()
{
	std::shared_ptr<Client> pclient(new Client);
	pclient->MakeMobike();
	pclient->MakeOfobike();
    return 0;
}
