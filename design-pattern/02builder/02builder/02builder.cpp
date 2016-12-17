// 02builder.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>

constexpr int MOBIKE_HANDLERBAR_LENGTH = 25;//Ħ�ݵ��� ���ѳ���
constexpr int OFOBIKE_HANDELERBAR_LENGTH = 30;//Ħ�ݵ��� ���ְ뾶
constexpr int MOBIKE_WHELL_RADIUS = 40;//ofo���� ���ѳ���
constexpr int OFOBIKE_WHEEL_RADIUS = 43;//ofo���� ���ְ뾶
//�����Ʒ-����
class Handlerbar
{
public:
	Handlerbar() {}
	~Handlerbar() {}
	//���г����ѳ���
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
//�����Ʒ-����
class Wheel
{
public:
	Wheel() {}
	~Wheel() {}
	//���г����ְ뾶
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

//���г�,�ɳ��Ѻͳ������
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

//С�Ƴ�builder
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

//�����������Ʋ�Ʒ�Ĺ�������
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
		//��Ʒ�Ĺ������̣��û��ɿ��Ƹù��̣��ɸı��Ʒ�ڲ���ʾ�����ｫ���г�����ͱ�ʾ�Ĵ���ֿ�
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
	//����ʹ��С�Ƴ�builder�������պ�Ҫ����һ��mobikebuilder��ֻ��Ҫ���滻
	std::shared_ptr<Director> pDirector=std::make_shared<Director>(builder);
	auto p = pDirector->CreateBike();
	p->DumpInfo();
	getchar();
    return 0;
}

