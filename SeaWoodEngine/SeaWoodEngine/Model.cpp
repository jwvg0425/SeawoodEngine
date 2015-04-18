#include "stdafx.h"
#include "Model.h"
#include "Director.h"
#include "Effect.h"
#include "InputLayout.h"
#include "Blend.h"
#include "Rasterizer.h"

USING_NS_SW;

SeaWood::Model::Model()
{

}

SeaWood::Model::~Model()
{

}

bool SeaWood::Model::init()
{
	if (!Figure<Vertex::PosBasic>::init())
	{
		return false;
	}

	setEffect(Effects::getBasicEffect());
	setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

Model* SeaWood::Model::createWithFile(const std::string& fileName)
{
	Model* model = new Model;

	if (model->init())
	{
		ModelInfo info;

		Director::getInstance()->loadModel(fileName, info);

		model->setBuffer(info.m_Vertices, info.m_Indices);
		model->setMaterial(info.m_Material);

		if (info.m_Texture != "")
		{
			model->setTexture(info.m_Texture);
		}

		model->autorelease();

		return model;
	}
	else
	{
		delete model;
		return nullptr;
	}
	
}
