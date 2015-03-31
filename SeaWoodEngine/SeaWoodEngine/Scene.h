#pragma once
#include "Seawood.h"
#include "Node.h"
#include "Light.h"

NS_SW_BEGIN

//화면 담당 클래스
class Scene : public Node
{
public:
	using DLights = std::vector<const DirectionalLight*>;
	using PLights = std::vector<const PointLight*>;
	using SLights = std::vector<const SpotLight*>;

	Scene();
	~Scene() override;

	bool init() override;

	void update(float dTime) override;

	void addChild(Node* child) override;

	//빛 처리
	void			registerLight(const DirectionalLight* directionalLight);
	void			registerLight(const PointLight* pointLight);
	void			registerLight(const SpotLight* spotLight);
	void			deleteLight(const DirectionalLight* directionalLight);
	void			deleteLight(const PointLight* pointLight);
	void			deleteLight(const SpotLight* spotLight);

	const DLights&	getDirectionalLight();
	const PLights&	getPointLight();
	const SLights&	getSpotLight();

	//안개 관련 처리
	void			setFog(float fogStart, float fogRange, XMVECTOR fogColor);
	void			setFogEnable(bool isEnable);
	bool			getFogEnable();
	float			getFogStart();
	float			getFogRange();
	XMFLOAT4		getFogColor();

protected:
	Childs		m_AddingChilds;
	DLights		m_DirectionalLight;
	PLights		m_PointLight;
	SLights		m_SpotLight;
	float		m_FogStart = 0.0f;
	float		m_FogRange = 0.0f;
	XMFLOAT4	m_FogColor;
	bool		m_IsFogEnabled = false;
};

NS_SW_END