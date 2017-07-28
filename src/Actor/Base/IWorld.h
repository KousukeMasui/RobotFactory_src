#ifndef	_IWORLD_H_
#define	_IWORLD_H_


#include<string>
enum class ActorGroup;
enum class EventMessage;
#include "ActorPtr.h"
#include"Field\Field.h"

#include"Actor\Unit\Unit.h"
#include"Base/GameUsing.h"
#include"Actor/Camera/Camera.h"


class CommandUI;
class GameManager;
class UnitFactory;
class UIManager;
class Effect3D;
enum class EffectID;

class BillBoardManager;
enum class CameraMode;
//ワールド抽象インターフェース
class IWorld
{
public:
	//仮想デストラクタ
	virtual ~IWorld(){}
	//アクターの追加
	virtual void AddActor(ActorGroup group, const ActorPtr& actor) = 0;
	virtual std::shared_ptr<Camera> GetCamera() const = 0;
	//アクターの検索
	virtual ActorPtr FindActor(const std::string& name) = 0;
	virtual std::vector<ActorPtr> FindActors(const ActorGroup& group) = 0;
	virtual std::shared_ptr<Field> GetField() const = 0;

	//メッセージの送信
	virtual void MessageSend(EventMessage message, void* param = nullptr) = 0;
	virtual  UIManager& GetUIManager() = 0;
	virtual GameManager& GetGameManager() = 0;

	virtual void Command(const FactoryPtr& facotry = nullptr) = 0;
	virtual FactoryPtr GetCommandFactory() const = 0;

	virtual std::shared_ptr<Effect3D> CreateEffect(EffectID effect, const MyVector3& position, const MyVector3& scale = MyVector3(1, 1, 1)) = 0;

	virtual BillBoardManager& GetBillBoardManager() =0;
	virtual void AddCamera(CameraMode mode, const std::shared_ptr<Camera>& camera) = 0;
};

#endif