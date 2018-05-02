#pragma once

#include "SDL_ttf.h"
#include "Texture.h"

class Font : public Texture { // Texture »ó¼Ó
private:
	TTF_Font* _font;
	SDL_Color _fontColor;
public :
	Font(const char* fontName, int fontSize);
	~Font();

	void SetText(const char* text);
};