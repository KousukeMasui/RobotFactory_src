#pragma once

#include<forward_list>
#include<unordered_map>
#include<memory>
#include<functional>
#include <iterator>     // std::back_inserter

//void Update(float),void Draw() const,bool IsDelete() const

//�z����Ăяo��ID,�z��ɓ����^(GetParam�ő�O�����Ɠ����^��Ԃ��֐����g��)�A�����Ɏg��function�̈����̌^
template <typename ID,typename Type,typename functionParam>
class TemplateManager
{
public:
	TemplateManager()
	{

	}

	void Update(float deltaTime)
	{
		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			for (auto type : itr->second)
			{
				type->Update(deltaTime);
			}
		}

		Remove();
	}

	void Draw() const
	{
		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			for (auto type : itr->second)
			{
				type->Draw();
			}
		}
	}

	void Delete()
	{
		m_types.clear();
	}

	void Delete(ID id, Type* t)
	{
		m_types[id].remove_if(
			[&](std::shared_ptr<Type> type)
		{
			return &*type == t;
		});
	}

	void Delete(ID id)
	{
		m_types[id].clear();
	}
	//����̃O���[�v�Ƀ��b�Z�[�W�𑗂�
	void Message(ID id, int message, const std::function<void(std::shared_ptr<Type> type)>& func)
	{
		auto types = GetVector(id);
		for (auto type : types)
		{
			func(type);
		}
	}

	//key�Ԃ̈ړ�
	void Move(ID prevID,ID currentID,Type* type)
	{
		std::shared_ptr<Type> result = nullptr;
		for (auto t : m_types[prevID])
		{
			if (&*t == type)
			{
				result = t;
				break;
			}
		}
		if (result == nullptr) return;//prev�ɂ��Ȃ��ꍇ�I��
		Delete(prevID, type);//�O�̏ꏊ����폜

		Add(currentID, result);//�V�����ǉ�

	}

	//�ǉ�
	void Add(ID id,std::shared_ptr<Type> type)
	{
		m_types[id].push_front(type);
	}

	std::forward_list<std::shared_ptr<Type>> Get(ID id)
	{
		return m_types[id];
	}
	//�����ȊO�̏����𖞂����I�u�W�F�N�g��z��ŕԂ�
	std::vector<std::shared_ptr<Type>> GetOther(ID id)
	{
		std::vector<std::shared_ptr<Type>> result;
		if (m_types.empty()) return result;
		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			if (itr->first != id)
			{
				//vector�̓���
				std::copy(itr->second.begin(), itr->second.end(), std::back_inserter(result));
			}
		}
		return result;
	}

	//�����ȊO�̏����𖞂����I�u�W�F�N�g��z��ŕԂ�
	std::vector<std::shared_ptr<Type>> GetOtherFunction(ID id,std::function<bool(const functionParam& param)> fun)
	{
		std::vector<std::shared_ptr<Type>> result;
		std::vector<std::shared_ptr<Type>> r1 = GetOther(id);

		for (auto type : r1)
		{
			if (fun(type->GetParam()))
			{
				result.push_back(type);
			}
		}

		return result;
	}
	//�����ȊO�̏����𖞂����I�u�W�F�N�g��z��ŕԂ�
	std::vector<std::shared_ptr<Type>> GetOtherFunctionPtr(ID id, std::function<bool(const std::shared_ptr<Type>& type)> fun)
	{
		std::vector<std::shared_ptr<Type>> result;
		std::vector<std::shared_ptr<Type>> r1 = GetOther(id);

		for (auto type : r1)
		{
			if (fun(type))
			{
				result.push_back(type);
			}
		}

		return result;
	}
	std::vector<std::shared_ptr<Type>> All()
	{
		std::vector<std::shared_ptr<Type>> result;

		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			for (auto type : m_types[itr->first])
			{
				result.push_back(type);
			}
		}
		return result;
	}

	std::vector<std::shared_ptr<Type>> GetVector(ID id) const
	{
		std::vector<std::shared_ptr<Type>> result;
		if (m_types.count(id) <= 0) return result;
		for (auto type : m_types.at(id))
		{
			result.push_back(type);
		}

		return result;
	}

	std::vector<std::shared_ptr<Type>> GetFunction(ID id,const std::function<bool(const functionParam& param)>& fun) const
	{
		std::vector<std::shared_ptr<Type>> result;
		if (m_types.count(id) <= 0) return result;
		for (auto type : m_types.at(id))
		{
			if (fun(type->GetParam()))
			{
				result.push_back(type);
			}
		}
		return result;
	}
	std::vector<std::shared_ptr<Type>> GetFunctionPtr(std::function<bool(const std::shared_ptr<Type>& type)> fun)
	{
		std::vector<std::shared_ptr<Type>> result;

		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr) 
		{
			for (auto type : m_types[itr->first])
			{
				if (fun(type))
				{
					result.push_back(type);
				}
			}
		}
		return result;
	}
	std::vector<std::shared_ptr<Type>> GetFunction(std::function<bool(const functionParam& param)> fun) const
	{
		std::vector<std::shared_ptr<Type>> result;

		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			if (m_types.count(itr->first) <= 0) continue;
			for (auto type : m_types.at(itr->first))
			{
				if (fun(type->GetParam()))
				{
					result.push_back(type);
				}
			}
		}
		return result;
	}

	void Function(std::function<void(std::shared_ptr<Type> type)> fun)
	{
		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			for (auto type : m_types[itr->first])
			{
				fun(type);
			}
		}
	}

	void Function(std::function<void(const std::shared_ptr<Type>& type)> fun) const
	{
		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			if (m_types.count(itr->first) <= 0) continue;
			for (auto type : m_types.at(itr->first))
			{
				fun(type);
			}
		}
	}
	
	void Function(ID id,std::function<void(std::shared_ptr<Type> type)> fun)
	{
		for (auto type : m_types[id])
		{
			fun(type);
		}
	}

	void Remove()
	{
		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			itr->second.remove_if(
				[](std::shared_ptr<Type> type)
			{
				return type->IsDelete();
			});
		}
	}

private:
	//ID�ɔ�r�֐��������\��������̂�
	std::unordered_map<ID,std::forward_list<std::shared_ptr<Type>>> m_types;
};