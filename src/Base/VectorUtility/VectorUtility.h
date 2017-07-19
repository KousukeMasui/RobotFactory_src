#pragma once
#include<vector>
#include<functional>
//vector���g���ۂɗǂ��s���������܂Ƃ߂��N���X MyVector�̕��ł͂Ȃ��̂Œ���
class VectorUtility
{
public:
	template<typename Object>
	static std::vector<Object> SortObject(const std::vector<Object>& objects, std::function<Object(const Object& o1, const Object& o2)> fun)
	{
		std::vector<Object> result;
		//�\�[�g����K�v���Ȃ��ꍇ�@���̂܂ܕԂ�
		if (objects.size() <= 1) return objects;
		auto objs = objects;//�R�s�[
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
		} while (!objs.empty());//�Ԃ��z���objects���S�ē�������I��

		return result;
	}
	//objects�ɂȂ�base���擾����
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
	//�����ɂ���v�f�̔z���Ԃ�
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

	//object��base���珜�O���ĕԂ�
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

	//object��base���珜�O���ĕԂ�
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
	//object��base���珜�O���ĕԂ�
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
	//objects�ɗv�f�����邩���ׂ�
	template<typename Object>
	static bool IsExistence(const std::vector<Object>& objects,const Object& obj)
	{
		for (auto o : objects)
		{
			//���݂�����true
			if (obj == o) return true;
		}
		return false;
	}

	//objects�ɂ���v�f�̂����A���func�𖞂����Ă���v�f��Ԃ�
	template<typename Object>
	static Object GetMostObject(const std::vector<Object>& objects, const std::function<Object(const Object& o1, const Object& o2)>& func)
	{
		//���g���Ȃ��ꍇ�A���Ԃ�
		if (objects.empty()) return Object();
		Object result = objects.front();
		for (auto obj : objects)
		{
			result = func(result, obj);
		}
		return result;
	}

	//objects�ɗv�f�����邩���ׂ� �����Ō��݂̃C���f�b�N�X�𒲂ׂ�
	template<typename Object>
	static bool IsExistence(const std::vector<Object>& objects, Object obj,int& index)
	{
		for (unsigned int i = 0; i < objects.size();i++)
		{
			//���݂�����true
			if (obj == objects[i])
			{
				index = i;
				return true;
			}
		}
		return false;
	}
	
	//objects�ɗv�f�����邩���ׂ� �����Ō��݂̃C���f�b�N�X�𒲂ׂ�
	template<typename Object,typename Param>
	static bool IsExistence(const std::vector<Object>& objects, Param obj, int& index,std::function<Param(const Object& obj)> paramFunc)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			//���݂�����true
			if (obj == paramFunc(objects[i]))
			{
				index = i;
				return true;
			}
		}
		return false;
	}
};