#pragma once

#include<forward_list>
#include<unordered_map>
#include<memory>
#include<functional>
#include <iterator>     // std::back_inserter

//void Update(float),void Draw() const,bool IsDelete() const

//配列を呼び出すID,配列に入れる型(GetParamで第三引数と同じ型を返す関数を使う)、検索に使うfunctionの引数の型
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
	//特定のグループにメッセージを送る
	void Message(ID id, int message, const std::function<void(std::shared_ptr<Type> type)>& func)
	{
		auto types = GetVector(id);
		for (auto type : types)
		{
			func(type);
		}
	}

	//key間の移動
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
		if (result == nullptr) return;//prevにいない場合終了
		Delete(prevID, type);//前の場所から削除

		Add(currentID, result);//新しく追加

	}

	//追加
	void Add(ID id,std::shared_ptr<Type> type)
	{
		m_types[id].push_front(type);
	}

	std::forward_list<std::shared_ptr<Type>> Get(ID id)
	{
		return m_types[id];
	}
	//引数以外の条件を満たすオブジェクトを配列で返す
	std::vector<std::shared_ptr<Type>> GetOther(ID id)
	{
		std::vector<std::shared_ptr<Type>> result;
		if (m_types.empty()) return result;
		for (auto itr = m_types.begin(); itr != m_types.end(); ++itr)
		{
			if (itr->first != id)
			{
				//vectorの統合
				std::copy(itr->second.begin(), itr->second.end(), std::back_inserter(result));
			}
		}
		return result;
	}

	//引数以外の条件を満たすオブジェクトを配列で返す
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
	//引数以外の条件を満たすオブジェクトを配列で返す
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
	//IDに比較関数が無い可能性があるので
	std::unordered_map<ID,std::forward_list<std::shared_ptr<Type>>> m_types;
};