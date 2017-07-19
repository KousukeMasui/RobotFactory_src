#pragma once
#include<vector>
#include<functional>
//vectorを使う際に良く行う処理をまとめたクラス MyVectorの方ではないので注意
class VectorUtility
{
public:
	template<typename Object>
	static std::vector<Object> SortObject(const std::vector<Object>& objects, std::function<Object(const Object& o1, const Object& o2)> fun)
	{
		std::vector<Object> result;
		//ソートする必要がない場合　そのまま返す
		if (objects.size() <= 1) return objects;
		auto objs = objects;//コピー
		do
		{
			Object obj = objs.front();
			for (auto o1 : objs)
			{
				for (auto o2 : objs)
				{
					if (o1 == o2) continue;
					obj = fun(obj, o2);
				}
			}
			result.push_back(obj);
			objs = NonObjects(objs, obj);
		} while (!objs.empty());//返す配列にobjectsが全て入ったら終了

		return result;
	}
	//objectsにないbaseを取得する
	template<typename Object>
	static std::vector<Object> NonObjects(const std::vector<Object>& base, const std::vector<Object>& objects)
	{
		std::vector<Object> result = base;
		for (auto obj : objects)
		{
			result = NonObjects(result, obj);
		}

		return result;
	}
	//両方にある要素の配列を返す
	template<typename Object>
	static std::vector<Object> CommonObjects(const std::vector<Object>& obj1, const std::vector<Object>& obj2)
	{
		std::vector<Object> result;
		for (auto o1 : obj1)
		{
			for (auto o2 : obj2)
			{
				if(o1 == o2)
				{
					result.push_back(o1);
					break;
				}
			}
		}

		return result;
	}

	//objectをbaseから除外して返す
	template<typename Object>
	static std::vector<Object> NonObjects(const std::vector<Object>& base,const Object& object)
	{
		std::vector<Object> result;

		for (auto obj1 : base)
		{
			if (obj1 != object)
				result.push_back(obj1);
		}

		return result;
	}

	//objectをbaseから除外して返す
	template<typename Object, typename Param>
	static std::vector<Object> NonObjects(const std::vector<Object>& base, const std::vector<Param>& object,const std::function<Param(const Object& obj)>& paramFunc)
	{
		std::vector<Object> result = base;

		for (auto obj : object)
		{
			result = NonObjects(result, obj, paramFunc);
		}

		return result;
	}
	//objectをbaseから除外して返す
	template<typename Object,typename Param>
	static std::vector<Object> NonObjects(const std::vector<Object>& base, const Param& object, std::function<Param(const Object& obj)> paramFunc)
	{
		std::vector<Object> result;

		for (auto obj1 : base)
		{
			if (paramFunc(obj1) != object)
				result.push_back(obj1);
		}

		return result;
	}
	//objectsに要素があるか調べる
	template<typename Object>
	static bool IsExistence(const std::vector<Object>& objects,const Object& obj)
	{
		for (auto o : objects)
		{
			//存在したらtrue
			if (obj == o) return true;
		}
		return false;
	}

	//objectsにある要素のうち、一番funcを満たしている要素を返す
	template<typename Object>
	static Object GetMostObject(const std::vector<Object>& objects, const std::function<Object(const Object& o1, const Object& o2)>& func)
	{
		//中身がない場合、空を返す
		if (objects.empty()) return Object();
		Object result = objects.front();
		for (auto obj : objects)
		{
			result = func(result, obj);
		}
		return result;
	}

	//objectsに要素があるか調べる 引数で現在のインデックスを調べる
	template<typename Object>
	static bool IsExistence(const std::vector<Object>& objects, Object obj,int& index)
	{
		for (unsigned int i = 0; i < objects.size();i++)
		{
			//存在したらtrue
			if (obj == objects[i])
			{
				index = i;
				return true;
			}
		}
		return false;
	}
	
	//objectsに要素があるか調べる 引数で現在のインデックスを調べる
	template<typename Object,typename Param>
	static bool IsExistence(const std::vector<Object>& objects, Param obj, int& index,std::function<Param(const Object& obj)> paramFunc)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			//存在したらtrue
			if (obj == paramFunc(objects[i]))
			{
				index = i;
				return true;
			}
		}
		return false;
	}
};