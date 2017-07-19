#include "BillBoardManager.h"
#include"../BillBoard.h"
#include"Actor\Camera\Camera.h"
#include"World/World.h"
BillBoardManager::BillBoardManager(IWorld* world):
	m_world(world)
{
}

BillBoardManager::~BillBoardManager()
{
}

void BillBoardManager::Create(BillBoardID billBoardID, TEXTURE_ID id, MyVector3* position, const MyVector3& addPos, float size)
{
	m_manager.Add(billBoardID, std::make_shared<BillBoard>(id, position, addPos, size));
}
void BillBoardManager::Delete()
{
	m_manager.Delete();
}
std::shared_ptr<BillBoard> BillBoardManager::Find(MyVector3* pos)
{
	std::shared_ptr<BillBoard> result;
	m_manager.Function([&](std::shared_ptr<BillBoard> billBoard)
	{
		if (billBoard->IsThis(pos))
		{
			result = billBoard;
		}
	});

	return result;
}

std::shared_ptr<BillBoard> BillBoardManager::Find(BillBoardID billBoardID, MyVector3 * pos)
{
	std::shared_ptr<BillBoard> result;
	m_manager.Function(billBoardID, [&](std::shared_ptr<BillBoard> billBoard) {
		if (billBoard->IsThis(pos)) result = billBoard; });
	return result;
}

void BillBoardManager::Update()
{
	m_manager.Function(
		[&](std::shared_ptr<BillBoard> billBoard) {
		auto cameraRotate = m_world->GetCamera()->Rotate();

		//MyMatrix4 invXRot = MyMatrix4::InverseMatrix(MyMatrix4::RotateX(MyMatrix4::GetRad(cameraRotate).x));
		//cameraRotate *= invXRot;
		auto top = cameraRotate.GetForward();
		auto forward = -cameraRotate.GetTop();
		auto left = cameraRotate.GetLeft();

		MyVector3 pos = left * billBoard->GetFirstPosition().x + top * billBoard->GetFirstPosition().y +forward * billBoard->GetFirstPosition().z;
		pos.y = billBoard->GetFirstPosition().y;
		billBoard->Position(pos);
	});

	m_manager.Remove();
}

void BillBoardManager::Draw() const
{
	m_manager.Draw();
}
