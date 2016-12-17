// 02builder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>

constexpr int MOBIKE_HANDLERBAR_LENGTH = 25;//摩拜单车 车把长度
constexpr int OFOBIKE_HANDELERBAR_LENGTH = 30;//摩拜单车 车轮半径
constexpr int MOBIKE_WHELL_RADIUS = 40;//ofo单车 车把长度
constexpr int OFOBIKE_WHEEL_RADIUS = 43;//ofo单车 车轮半径
//抽象产品-车把
class Handlerbar
{
public:
	Handlerbar() {}
	~Handlerbar() {}
	//自行车车把长度
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
//抽象产品-车轮
class Wheel
{
public:
	Wheel() {}
	~Wheel() {}
	//自行车车轮半径
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

//自行车,由车把和车轮组成
class Bike
{
public:
	Bike() :m_pHandlerbar(nullptr),m_pWheel(nullptr)
	{  }
	~Bike() 
	{
		delete m_pHandlerbar; m_pHandlerbar = nullptr;
		delete m_pWheel; m_pWheel = nullptr;
	}
	void AssembleWheel(Wheel* p) { m_pWheel = p; }
	void AssembleHandlerbar(Handlerbar* p) { m_pHandlerbar = p; }

	void DumpInfo()
	{
		if(m_pHandlerbar)
			std::cout << "handlerbar,lenth=" << m_pHandlerbar->GetLength() << std::endl;
		if(m_pWheel)
			std::cout << "wheel,radius=" << m_pWheel->GetRadius() << std::endl;
	}
private:
	Handlerbar* m_pHandlerbar;
	Wheel* m_pWheel;
};
//builder
class BikeBuilder
{
public:
	virtual void ManufactureBike() {}
	virtual void ManufactureWheel() {}
	virtual void ManufactureHandlerbar() {}
	virtual Bike* GetBike() { return nullptr; }
};

//小黄车builder
class OfoBuilder :public BikeBuilder
{
public:
	OfoBuilder():m_pBike(nullptr)
	{}
	~OfoBuilder()
	{
		delete m_pBike;
		m_pBike = nullptr;
	}
	virtual void ManufactureBike() 
	{ 
		m_pBike = new Bike;
	}
	virtual void ManufactureWheel() 
	{
		m_pBike->AssembleWheel(new OfobikeWheel);
	}
	virtual void ManufactureHandlerbar()
	{
		m_pBike->AssembleHandlerbar(new OfobikeHandlerbar);
	}
	virtual Bike* GetBike()
	{ 
		return m_pBike; 
	}
private:
	Bike* m_pBike;
};

//导向器，控制产品的构建过程
class Director
{
public:
	Director(BikeBuilder& p):m_pBuilder(&p)
	{

	}
	Bike* CreateBike()
	{
		if (!m_pBuilder)
			return nullptr;
		//产品的构建过程；用户可控制该过程，可改变产品内部表示；这里将自行车构造和表示的代码分开
		m_pBuilder->ManufactureBike();
		m_pBuilder->ManufactureHandlerbar();
		m_pBuilder->ManufactureWheel();
		return m_pBuilder->GetBike();
	}

private:
	BikeBuilder* m_pBuilder;
};

int main()
{
	OfoBuilder builder;
	//这里使用小黄车builder；假如日后要增加一个mobikebuilder；只需要简单替换
	std::shared_ptr<Director> pDirector=std::make_shared<Director>(builder);
	auto p = pDirector->CreateBike();
	p->DumpInfo();
	getchar();
    return 0;
}

