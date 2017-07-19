#ifndef _ACTOR_PTR_H_
#define _ACTOR_PTR_H_

#include<memory>
//アクター用のシェアドポインタ
class Actor3D;
using ActorPtr = std::shared_ptr<Actor3D>;


#endif