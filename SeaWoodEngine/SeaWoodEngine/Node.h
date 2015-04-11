#pragma once
#include "Ref.h"
#include "Light.h"
#include "MouseEvent.h"

NS_SW_BEGIN

class Camera;
class Node : public Ref
{
public:
	using Nodes = std::vector<Node*>;
	using ChildPair = std::pair<std::string, Node*>;
	using Childs = std::vector<ChildPair>;
	Node();
	~Node() override;

	virtual bool init();

	void setPosition(float x, float y, float z, bool relative = false);
	void setScale(float x, float y, float z, bool relative = false);
	void setRotate(float x, float y, float z, bool relative = false);

	//포인터로 넘어온 변수에 해당하는 값 저장해서 돌려줌
	void getPosition(float* x, float* y, float* z);
	void getScale(float* scaleX, float* scaleY, float* scaleZ);
	void getRotate(float* angleX, float* angleY, float* angleZ);

	XMMATRIX getWorld() const;
	XMMATRIX getParentWorld() const;

	const Material*	getMaterial();
	void			setMaterial(Material material);
	void			useRimLight(bool isUse);
	bool			isUsingRimLight();

	ID3D11ShaderResourceView* getTexture();
	void			setTexture(const std::wstring& fileName);
	void			setTexture(const std::string& fileName);
	void			setTextureTransform(CXMMATRIX matrix);
	XMFLOAT4X4		getTextureTransform();

	int				getRefCount();

	//그리기 함수.
	virtual void	render();

	//매 프레임 해야 하는 작업
	virtual void    update(float dTime);

	//부모 자식 관계 관련 함수
	virtual void	addChild(Node* child);
	void			addChild(Node* child, std::string name);
	Node*			getChild(std::string name);
	const Childs&	getChildList();
	//childs 배열에 해당 이름과 같은 이름을 가진 자식들을 전부 담아서 리턴
	void			getChilds(std::string name, Nodes* childs);
	Node*			getParent();
	void			setParent(Node* parent);
	void			removeChild(Node* child);
	void			removeAllChilds();
	void			removeFromParent();

	//렌더 스테이트 관련
	void				setInputLayout(ID3D11InputLayout* inputLayout, D3D11_PRIMITIVE_TOPOLOGY topology);
	void				setRasterizer(ID3D11RasterizerState* rasterizer);
	void				setBlend(ID3D11BlendState* blend, const FLOAT* blendFactor = nullptr);
	ID3D11BlendState*	getBlend() const;

	//이벤트 관련 함수
	virtual void	onMouseDown(MouseEvent e);
	virtual void	onMouseMove(MouseEvent e);
	virtual void	onMouseUp(MouseEvent e);

	void			setEvent(EventType e);

	//업데이트 등록
	void			scheduleUpdate();

	float			getDistanceToCamera(Camera* camera) const;

	//render 대상인지 확인.
	bool			isRender();

protected:
	void updateWorld();

	Childs		m_Childs;
	Node*		m_Parent = nullptr;
	bool		m_IsRender = true;
	bool		m_UseRimLight = false;

	std::vector<EventType> m_Events;

	//world를 구하기 위한 요소. 기본적으로 I.
	XMFLOAT4X4	m_Translation;
	XMFLOAT4X4	m_Scaling;
	XMFLOAT4X4	m_Rotation;
	XMFLOAT4X4	m_World;
	XMFLOAT4X4	m_TextureTransform;
	XMFLOAT4	m_CenterPos;
	float m_X = 0.0f, m_Y = 0.0f, m_Z = 0.0f;
	float m_ScaleX = 0.0f, m_ScaleY = 0.0f, m_ScaleZ = 0.0f;
	float m_AngleX = 0.0f, m_AngleY = 0.0f, m_AngleZ = 0.0f;
	Material*	m_Material = nullptr;
	ID3D11ShaderResourceView* m_DiffuseMapSRV = nullptr;

	//render state 관련
	D3D11_PRIMITIVE_TOPOLOGY m_Topology;
	ID3D11InputLayout*	m_InputLayout = nullptr;
	ID3D11RasterizerState* m_RasterizerState = nullptr;
	ID3D11BlendState* m_BlendState = nullptr;
	FLOAT m_BlendFactor[4];
};

NS_SW_END