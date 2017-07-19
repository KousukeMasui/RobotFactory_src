#pragma once

#include"../UI.h"
#include"Resources.h"
class FontSprite : public UI
{
public:
	FontSprite(Font_ID fontID,const MyVector2& position,const std::string& text,const Color& color);
	~FontSprite();
	void ChangeText(const std::string& text);
	std::string GetText() const;
	void Draw() const override;
private:
	Font_ID m_fontID;
	std::string m_text;
};
