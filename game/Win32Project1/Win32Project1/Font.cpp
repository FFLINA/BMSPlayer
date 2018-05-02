#include "sdl_ttf.h"
#include "GameSystem.h"
#include "Font.h"

Font::Font(const char* fontName, int fontSize) 
{
	_font = TTF_OpenFont("../Resources/Font/arialbd.ttf", 24);
	_fontColor = { 255, 255, 255 };

	SetText("Score : 0000 \nCombo : 0000");
}

Font::~Font() {


}

void Font::SetText(const char* text)
{
	//SDL_Surface* fontSurface = TTF_RenderText_Solid(_font, text, _fontColor);
	SDL_Surface* fontSurface = TTF_RenderText_Blended_Wrapped(_font, text, _fontColor, 500); // 줄바꿈 가능하게

	_texture = SDL_CreateTextureFromSurface(
		GameSystem::GetInstance()->GetRenderer(),
		fontSurface);

	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);

	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.x = 500;
	_destRect.y = 500;
	_destRect.w = _srcRect.w;
	_destRect.h = _srcRect.h;
}