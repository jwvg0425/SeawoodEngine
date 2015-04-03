#pragma once
#include "Ref.h"
#include "Light.h"
#include "MouseEvent.h"

NS_SW_BEGIN

class Node : public Ref
{
public:
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

	XMMATRIX getWorld();
	XMMATRIX getParentWorld();

	const Material*	getMaterial();
	void			setMaterial(Material material);

	ID3D11ShaderResourceView* getTexture();
	void			setTexture(const std::wstring& fileName);
	void			setTextureTransform(CXMMATRIX matrix);
	XMFLOAT4X4		getTextureTransform();

	using Nodes = std::vector<Node*>;
	const			Point2& getPosition();
	void			setPosition(Point2 position);
	int				getRefCount();

	//그리기 함수.
	virtual void	render();

	//매 프레임 해야 하는 작업
	virtual void    update(float dTime);

	//부모 자식 관계 관련 함수
	virtual void	addChild(Node* child);
	void			addChild(Node* child, std::string name);
	Node*			getChild(std::string name);
	//childs 배열에 해당 이름과 같은 이름을 가진 자식들을 전부 담아서 리턴
	void			getChilds(std::string name, Nodes* childs);
	Node*			getParent();
	void			setParent(Node* parent);
	void			removeChild(Node* child);
	void			removeAllChilds();
	void			removeFromParent();

	//이벤트 관련 함수
	virtual void	onMouseDown(MouseEvent e);
	virtual void	onMouseMove(MouseEvent e);
	virtual void	onMouseUp(MouseEvent e);

	void			setEvent(EventType e);

protected:
	void updateWorld();

	using Childs = std::vector<std::pair<std::string, Node*>>;

	Childs		m_Childs;
	Point2		m_Position;
	Size		m_Size;
	Node*		m_Parent = nullptr;

	std::vector<EventType> m_Events;

	//world를 구하기 위한 요소. 기본적으로 I.
	XMFLOAT4X4	m_Translation;
	XMFLOAT4X4	m_Scaling;
	XMFLOAT4X4	m_Rotation;
	XMFLOAT4X4	m_World;
	XMFLOAT4X4	m_TextureTransform;
	float m_X = 0.0f, m_Y = 0.0f, m_Z = 0.0f;
	float m_ScaleX = 0.0f, m_ScaleY = 0.0f, m_ScaleZ = 0.0f;
	float m_AngleX = 0.0f, m_AngleY = 0.0f, m_AngleZ = 0.0f;
	Material*	m_Material = nullptr;
	ID3D11ShaderResourceView* m_DiffuseMapSRV = nullptr;
};

NS_SW_END