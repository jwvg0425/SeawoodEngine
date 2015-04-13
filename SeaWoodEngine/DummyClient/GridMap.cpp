#include "GridMap.h"
#include "GeometryGenerator.h"

USING_NS_SW;

GridMap::GridMap()
{

}

GridMap::~GridMap()
{

}

bool GridMap::init()
{
	if (!Figure<FigureVertex>::init())
	{
		return false;
	}

	std::vector<FigureVertex> vertices;
	std::vector<UINT> indices;

	Material mat;

	mat.m_Ambient = XMFLOAT4(0.0f, 0.3f, 0.0f, 0.0f);
	mat.m_Diffuse = XMFLOAT4(0.1f, 0.4f, 0.1f, 1.0f);
	mat.m_Specular = XMFLOAT4(0.2f, 0.5f, 0.2f, 16.0f);

	setMaterial(mat);

	//컬링 없이 한다.
	setRasterizer(Rasterizer::getNoCull());

	setEffect(Effects::getBasicEffect());
	setInputLayout(InputLayouts::getPosBasic(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Director::getInstance()->registerEvent(EventType::PICK_TRIANGLE, this);
	scheduleUpdate();

	GeometryGenerator::createGrid(m_Width, m_Depth, m_M, m_N, vertices, indices);

	setBuffer(vertices, indices, true);

	return true;
}

void GridMap::onPickTriangle(int pick, XMVECTOR pickPos)
{
	m_Pick = pick;
	XMStoreFloat3(&m_PickPos, pickPos);
	//현재 픽된 위치 밝게 표시.
	pickHighlight();
}

void GridMap::pickHighlight()
{
	for (int i = 0; i < m_Vertices.size(); i++)
	{
		float x = m_Vertices[i].m_Pos.x;
		float z = m_Vertices[i].m_Pos.z;
		float d = sqrt((x - m_PickPos.x)*(x - m_PickPos.x) +
			(z - m_PickPos.z)*(z - m_PickPos.z));

		if (d < m_NowRadius)
		{
			float color = 0.3f * cos(d / m_NowRadius*PI / 2);
			m_Vertices[i].m_Color = XMFLOAT4(color, color, color, 1.0f);
		}
		else
		{
			m_Vertices[i].m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}
}

void GridMap::update(float dTime)
{
	//모드 갱신

	//높이 증가 = 1
	if (GET_KEY_MANAGER()->getKeyState(VK_1) & KeyManager::PRESS)
	{
		m_Mode = INCREASE;
	}
	//높이 감소 = 2
	else if (GET_KEY_MANAGER()->getKeyState(VK_2) & KeyManager::PRESS)
	{
		m_Mode = DECREASE;
	}
	//높이 평탄하게 = 3
	else if (GET_KEY_MANAGER()->getKeyState(VK_3) & KeyManager::PRESS)
	{
		m_Mode = FLAT;
	}

	//범위/속도 변경
	if (GET_KEY_MANAGER()->getKeyState(VK_SHIFT) & KeyManager::PRESS)
	{
		m_NowSpeed = m_Speed*m_UpMulti;
		m_NowRadius = m_Radius*m_UpMulti;
	}
	else
	{
		m_NowSpeed = m_Speed;
		m_NowRadius = m_Radius;
	}

	if (m_Pick == -1)
	{
		return;
	}

	UINT i0 = m_Indices[m_Pick * 3 + 0];
	UINT i1 = m_Indices[m_Pick * 3 + 1];
	UINT i2 = m_Indices[m_Pick * 3 + 2];

	//왼쪽 클릭시 해당 좌표 모드에 맞춰서 처리
	if (Director::getInstance()->getMouse()->m_Status & MouseEvent::LEFT)
	{
		for (int i = 0; i < m_Vertices.size(); ++i)
		{
			float deltaX = (m_PickPos.x - m_Vertices[i].m_Pos.x);
			float deltaZ = (m_PickPos.z - m_Vertices[i].m_Pos.z);
			float distance = sqrt(deltaX*deltaX + deltaZ*deltaZ);

			if (distance < m_NowRadius)
			{
				distance = distance / m_NowRadius * (PI / 2.0f);
				float delta = 0.0f;
				//mode에 따라 변경
				switch (m_Mode)
				{
				case INCREASE:
					delta = pow(cos(distance), 0.5f) * dTime;
					break;
				case DECREASE:
					delta = -pow(cos(distance), 0.5f) * dTime;
					break;
				case FLAT:
					if (m_Vertices[i].m_Pos.y < m_PickPos.y -0.1f)
					{
						delta = pow(cos(distance), 0.5f) * dTime;
					}
					else if (m_Vertices[i].m_Pos.y > m_PickPos.y + 0.1f)
					{
						delta = -pow(cos(distance), 0.5f) * dTime;
					}
					else
					{
						delta = 0.0f;
						m_Vertices[i].m_Pos.y = m_PickPos.y;
					}
					break;
				}
				m_Vertices[i].m_Pos.y += delta * m_NowSpeed;
			}

			//이후 계산을 위해 노멀 초기화
			m_Vertices[i].m_Normal.x = 0;
			m_Vertices[i].m_Normal.y = 0;
			m_Vertices[i].m_Normal.z = 0;
		}

		//벡터 계산
		for (int i = 0; i < m_Indices.size() / 3; ++i)
		{
			UINT i0 = m_Indices[i * 3 + 0];
			UINT i1 = m_Indices[i * 3 + 1];
			UINT i2 = m_Indices[i * 3 + 2];
			XMVECTOR a = XMLoadFloat3(&m_Vertices[i0].m_Pos);
			XMVECTOR b = XMLoadFloat3(&m_Vertices[i1].m_Pos);
			XMVECTOR c = XMLoadFloat3(&m_Vertices[i2].m_Pos);
			XMVECTOR ab = b - a;
			XMVECTOR ac = c - a;
			XMVECTOR n = XMVector3Cross(ab, ac);
			XMFLOAT3 normal;

			XMStoreFloat3(&normal, n);

			//해당 평면에 속하는 모든 정점들의 노멀값 갱신
			m_Vertices[i0].m_Normal.x += normal.x;
			m_Vertices[i0].m_Normal.y += normal.y;
			m_Vertices[i0].m_Normal.z += normal.z;

			m_Vertices[i1].m_Normal.x += normal.x;
			m_Vertices[i1].m_Normal.y += normal.y;
			m_Vertices[i1].m_Normal.z += normal.z;

			m_Vertices[i2].m_Normal.x += normal.x;
			m_Vertices[i2].m_Normal.y += normal.y;
			m_Vertices[i2].m_Normal.z += normal.z;
		}

		//법선 노멀라이즈
		for (int i = 0; i < m_Vertices.size(); ++i)
		{
			XMVECTOR n = XMLoadFloat3(&m_Vertices[i].m_Normal);
			n = XMVector3Normalize(n);
			XMStoreFloat3(&m_Vertices[i].m_Normal, n);
		}
	}

	updateBuffer();
}
