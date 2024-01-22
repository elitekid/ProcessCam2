
#include "font_atlas.h"

FontAtlas::FontAtlas()
	:texture_id_(0), texture_width_(0), texture_height_(0), is_created_(false)
{
}

FontAtlas::~FontAtlas() {}

void FontAtlas::CreateAtlas() {
	// FreeType
	// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, "C:\\Windows\\Fonts\\arial.ttf", 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	else if(!is_created_)
	{
		// Clear the previous map (if any)
		ch_atlas_.clear();

		// set the font size
		FT_Set_Pixel_Sizes(face, 0, 512);

		// Below line keep the unpack alignment otherwise fonts will be skewed
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// initialize variables to keep track of texture atlas size
		int atlas_width = 0;
		int atlas_height = 0;

		const unsigned char* colorHexGlyphList[] = {
			reinterpret_cast<const unsigned char*>("a"),
			reinterpret_cast<const unsigned char*>("b"),
			reinterpret_cast<const unsigned char*>("c"),
			reinterpret_cast<const unsigned char*>("d"),
			reinterpret_cast<const unsigned char*>("e"),
			reinterpret_cast<const unsigned char*>("f"),
			reinterpret_cast<const unsigned char*>("0"),
			reinterpret_cast<const unsigned char*>("1"),
			reinterpret_cast<const unsigned char*>("2"),
			reinterpret_cast<const unsigned char*>("3"),
			reinterpret_cast<const unsigned char*>("4"),
			reinterpret_cast<const unsigned char*>("5"),
			reinterpret_cast<const unsigned char*>("6"),
			reinterpret_cast<const unsigned char*>("7"),
			reinterpret_cast<const unsigned char*>("8"),
			reinterpret_cast<const unsigned char*>("9")
		};

		for (const unsigned char* c : colorHexGlyphList) {
			if (FT_Load_Char(face, *c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			// update atlas size variables
			atlas_width += face->glyph->bitmap.width;
			atlas_height = std::max(atlas_height, static_cast<int>(face->glyph->bitmap.rows));
		}

		// generate texture for the atlas
		glDeleteTextures(1, &texture_id_); // Delete the existing texture
		glGenTextures(1, &texture_id_);
		glBindTexture(GL_TEXTURE_2D, texture_id_);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			atlas_width,
			atlas_height,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			nullptr
		);

		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// initialize x position for next glyph
		int x = 0;

		// loop through the characters again and add their glyphs to the atlas
		for (const unsigned char* c : colorHexGlyphList)
		{
			// load glyph
			if (FT_Load_Char(face, *c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			// add glyph to texture atlas
			glTexSubImage2D(
				GL_TEXTURE_2D,
				0,
				x,
				0,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			// store glyph information in character map
			Character character;

			character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
			character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
			character.advance = face->glyph->advance.x;

			// compute glyph texture coordinates
			character.top_left.x = static_cast<float>(x) / static_cast<float>(atlas_width);
			character.top_left.y = 0.0f;
			character.bot_right.x = static_cast<float>(x + character.size.x) / static_cast<float>(atlas_width);
			character.bot_right.y = static_cast<float>(character.size.y) / static_cast<float>(atlas_height);

			ch_atlas_.insert(std::pair<char, Character>(*c, character));

			// update x position for next glyph
			x += face->glyph->bitmap.width;
		}
	}

	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// atlas가 생성되었음을 표시
	is_created_ = true;
}