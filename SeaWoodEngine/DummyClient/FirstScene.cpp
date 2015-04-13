#include "FirstScene.h"
#include "EyeLight.h"
#include "RoundLight.h"
#include "GeometryGenerator.h"
#include "MovingCamera.h"
#include "Box.h"
#include "RoundFigure.h"
#include <atomic>

USING_NS_SW;


FirstScene::FirstScene()
{
}

FirstScene::~FirstScene()
{
}

bool FirstScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto camera = MovingCamera::createWithPos(XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f), XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	GET_RENDERER()->registerCamera(camera);

	auto body = Model::createWithFile("body.swm");
	body->setScale(0.1f, 0.1f, 0.1f);

	auto track = Model::createWithFile("track.swm");
	track->setScale(0.1f, 0.1f, 0.1f);

	addChild(body);
	addChild(track);

	Material boxMaterial;

	boxMaterial.m_Ambient = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	boxMaterial.m_Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	boxMaterial.m_Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 200.0f);

	auto box = Box::create();

	box->setBoxWithMaterial(2.0f, 2.0f, 2.0f, boxMaterial);

	box->setPosition(20.0f, 40.0f, -30.0f);
	box->setScale(2.0f, 1.0f, 1.0f);
	box->setRotate(0.3f, 0.7f, 0.2f);
	box->setTexture(L"Textures/WoodCrate01.dds");
	addChild(box);

	auto getRoundFigure = [](float radius) -> RoundFigure<Vertex::PosBasic>*
	{
		auto sphere = RoundFigure<Vertex::PosBasic>::createWithEffect(
			Effects::getBasicEffect());

		float xN = 0.1f;
		float yN = 0.1f;
		float zN = 0.1f;

		if (rand() % 2)
		{
			xN = -xN;
		}

		if (rand() % 2)
		{
			yN = -yN;
		}

		if (rand() % 2)
		{
			zN = -zN;
		}
		sphere->setOption(5 + rand() % 10, XMFLOAT3(xN * (rand() % 10), yN * (rand() % 10), zN * (rand() % 10)), 1 + rand() % 5);

		Material material;

		material.m_Ambient = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 1.0f);
		material.m_Diffuse = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.5f + 0.1f * (rand() % 4));
		material.m_Specular = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 16.0f);
		sphere->setMaterial(material);

		std::vector<Vertex::PosBasic> vertices;
		std::vector<UINT> indices;

		GeometryGenerator::createSphere(radius, 50, 50, vertices, indices);
		sphere->setBuffer(vertices, indices);

		sphere->setInputLayout(InputLayouts::getPosBasic(),
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		sphere->setTexture(L"Textures/sphere.jpg");
		sphere->setPosition(-50 + rand() % 100, -50 + rand() % 100, -50 + rand() % 100);

		return sphere;
	};


	for (int i = 0; i < 3; i++)
	{
		auto sphere = Figure<Vertex::PosBasic>::createWithEffect(
			Effects::getBasicEffect());

		Material material;

		material.m_Ambient = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 1.0f);
		material.m_Diffuse = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.5f + 0.1f * (rand() % 4));
		material.m_Specular = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 16.0f);
		material.m_RimLight = XMFLOAT4(0.7f, 0.7f, 0.7f, 2.0f);
		sphere->setMaterial(material);

		std::vector<Vertex::PosBasic> vertices;
		std::vector<UINT> indices;

		GeometryGenerator::createSphere(2.0f, 50, 50, vertices, indices);
		sphere->setBuffer(vertices, indices);

		sphere->setInputLayout(InputLayouts::getPosBasic(),
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		sphere->setTexture(L"Textures/sphere.jpg");
		sphere->setPosition(-30 + rand() % 60, -30 + rand() % 60, -30 + rand() % 60);
		sphere->useRimLight(true);

		addChild(sphere);

		auto roundSphere = getRoundFigure(1.0f);
		auto roundRound = getRoundFigure(0.5f);

		sphere->addChild(roundSphere);
		roundSphere->addChild(roundRound);
	}

	auto light = EyeLight::createWithScene(this);

	addChild(light);

	auto direct = DirectionalLight();

	direct.m_Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	direct.m_Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	direct.m_Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	direct.m_Direction = XMFLOAT3(0.3f, 0.7f, 0.5f);

	auto light2 = Light<DirectionalLight>::createWithScene(this, direct);

	addChild(light2);

	setFogEnable(true);
	setFog(20.0f, 100.0f, XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));


	return true;
}