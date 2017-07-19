#pragma once
class BillBoard;
#include<vector>
#include<memory>

#include"Base/Manager/TemplateManager.h"
#include"Resources.h"
#include"Math/Vector/MyVector3.h"
class IWorld;
class Camera;
enum class BillBoardID
{
	HAVE_UI,
	AUTO_UI
};

class BillBoardManager
{
public:
	explicit BillBoardManager(IWorld* world);
	~BillBoardManager();

	void Create(BillBoardID billBoardID,TEXTURE_ID id,MyVector3* position,const MyVector3& addPos,float size);
	void Delete();
	std::shared_ptr<BillBoard> Find(MyVector3* pos);
	std::shared_ptr<BillBoard> Find(BillBoardID billBoardID,MyVector3* pos);
	void Update();
	void Draw() const;
private:
	//これをラッピングして使う
	//テンプレマネージャー
	TemplateManager<BillBoardID, BillBoard, int> m_manager;

	IWorld* m_world;
};