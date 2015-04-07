#pragma once
#include "Vertex.h"
#include "Director.h"
#include "BasicEffect.h"
#include "Renderer.h"
#include "Figure.h"

NS_SW_BEGIN

class Model : public Figure<Vertex::PosBasic>
{
public:
	Model();
	~Model() override;

	bool init() override;

	static Model* createWithFile(const std::string& fileName);

private:
};


NS_SW_END