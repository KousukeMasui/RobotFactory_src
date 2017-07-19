#ifndef		  _MY_VECTOR3_H_
#define		  _MY_VECTOR3_H_

///<summary>Vector3クラス	何か足りない物があったら連絡下さい</summary>
class MyVector3
{
public:

	///<summary>コンストラクタ</summary>
	///<param name='x'>X成分</param>
	///<param name='y'>Y成分</param>
	///<param name='z'>Z成分</param>
	MyVector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	
	///<summary>内積の計算</summary>
	///<param name='vec'>自分と計算するvector</param>
	///<returns>内積</returns>
	float Dot(const MyVector3& vec);

	///<summary>内積を計算する</summary>
	///<param name='v1'>内積を計算するvector</param>
	///<param name='v2'>内積を計算するvector</param>
	///<returns>内積</returns>
	static float Dot(const MyVector3& v1, const MyVector3& v2);

	///<summary>外積を計算する</summary>
	///<param name='vec'>自分と計算するvector</param>
	///<returns>外積</returns>
	MyVector3 Cross(const MyVector3& vec);
	///<summary>外積を計算する</summary>
	///<param name='v1'>外積を計算するvector</param>
	///<param name='v2'>外積を計算するvector</param>
	///<returns>外積</returns>
	static MyVector3 Cross(const MyVector3& v1, const MyVector3& v2);


	///<summary>2点間の距離を計算する</summary>
	///<param name='v1'>点の位置</param>
	///<param name='v2'>点の位置</param>
	///<returns>距離</returns>
	static float Distance(const MyVector3& v1, const MyVector3& v2);

	///<summary>ベクトルの長さを計算する</summary>
	///<returns>長さ</returns>
	float Length() const;

	///<summary>ベクトルの長さを計算する</summary>
	///<param name='vec'>長さを計算するベクトル</param>
	///<returns>距離</returns>
	static float Length(const MyVector3& vec);

	///<summary>2ベクトルの角度差を計算する</summary>
	///<param name='vec'>自分と計算するベクトル</param>
	///<returns>角度（0～180度のrad法）</returns>
	float Angle(const MyVector3& vec);

	///<summary>2ベクトルの角度差を計算する</summary>
	///<param name='v1'>角度差を計算するベクトル</param>
	///<param name='v2'>角度差を計算するベクトル</param>
	///<returns>角度（0～180度のrad法）</returns>
	static float Angle(const MyVector3& v1, const MyVector3& v2);

	///<summary>ベクトルの正規化</summary>
	///<returns>正規化されたベクトル</returns>
	MyVector3 Normalize();

	///<summary>ベクトルの正規化</summary>
	///<param name='vec'>正規化するベクトル</param>
	///<returns>正規化されたベクトル</returns>
	static MyVector3 Normalize(const MyVector3& vec);

	///<summary>ゼロベクトルを返す</summary>
	///<returns>ゼロベクトル</returns>
	static MyVector3 Zero();

	///<summary>ベクトルの線間補正</summary>
	///<param name='begin'>スタート位置</param>
	///<param name='end'>終了位置</param>
	///<param name='rate'>割合(0.0～1.0)</param>
	static MyVector3 Lerp(const MyVector3& begin, const MyVector3& end, float rate);

public:
	float x;
	float y;
	float z;
};

// 単項演算子オーバーロード
MyVector3 operator - (const MyVector3& v);

// 代入演算子オーバーロード
MyVector3& operator +=(MyVector3& v1, const MyVector3& v2);

MyVector3& operator -= (MyVector3& v1, const MyVector3& v2);
MyVector3& operator *= (MyVector3& v, float s);
MyVector3& operator /= (MyVector3& v, float s);
// ２項演算子オーバーロード
MyVector3 operator + (const MyVector3& v1, const MyVector3& v2);
MyVector3 operator - (const MyVector3& v1, const MyVector3& v2);
MyVector3 operator * (const MyVector3& v, float s);
MyVector3 operator * (float s, const MyVector3& v);
MyVector3 operator / (const MyVector3& v, float s);

#endif