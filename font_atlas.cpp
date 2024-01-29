
#include "font_atlas.h"

FontAtlas::FontAtlas()
	:texture_id_(0), texture_width_(0), texture_height_(0), is_created_(false)
{
}

FontAtlas::~FontAtlas() {}

void FontAtlas::CreateAtlas() {
	FT_Library ft;

	// FreeType 초기화
	if (FT_Init_FreeType(&ft))
	{
		qDebug() << "ERROR::FREETYPE: Could not init FreeType Library";
		return;
	}

	// 폰트 로드
	FT_Face face;

    std::string stdStr = setting_manager_.GetFontPath().toStdString();
	const char* path = stdStr.c_str();

	if (FT_New_Face(ft, path, 0, &face)) {
		qDebug() << "ERROR::FREETYPE: Failed to load font";
		return;
	}
	else if(!is_created_)
	{
		// 이전 폰트 아틀라스 삭제
		ch_atlas_.clear();

		// 픽셀 사이즈 설정
		FT_Set_Pixel_Sizes(face, 0, 512);

		// 글꼴이 왜곡되지 않도록 언팩 정렬을 유지
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// 텍스처 아틀라스의 크기를 추적하기 위한 변수를 초기화
		int atlas_width = 0;
		int atlas_height = 0;
		
		// colorHexGlyphList : 아틀라스에 포함할 문자 목록(색상코드만 표현하기 때문에 16진수 문자들만 포함)
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
				qDebug() << "ERROR::FREETYTPE: Failed to load Glyph";
				continue;
			}

			// 텍스처 아틀라스의 크기를 업데이트
			atlas_width += face->glyph->bitmap.width;
			atlas_height = std::max(atlas_height, static_cast<int>(face->glyph->bitmap.rows));
		}

		// 텍스처 아틀라스를 생성
		glDeleteTextures(1, &texture_id_);
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

		// 텍스처의 옵션을 설정
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// 다음 글리프의 x 위치를 초기화
		int x = 0;

		// 문자의 글리프를 아틀라스에 하나씩 추가
		for (const unsigned char* c : colorHexGlyphList)
		{
			// 글리프 로드
			if (FT_Load_Char(face, *c, FT_LOAD_RENDER))
			{
				qDebug() << "ERROR::FREETYTPE: Failed to load Glyph";
				continue;
			}

			// 글리프를 텍스쳐에 추가
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

			// Characer 객체에 글리프 정보 저장
			Character character;

			character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
			character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
			character.advance = face->glyph->advance.x;

			// 글리프 텍스쳐의 좌표 계산
			character.top_left.x = static_cast<float>(x) / static_cast<float>(atlas_width);
			character.top_left.y = 0.0f;
			character.bot_right.x = static_cast<float>(x + character.size.x) / static_cast<float>(atlas_width);
			character.bot_right.y = static_cast<float>(character.size.y) / static_cast<float>(atlas_height);

			ch_atlas_.insert(std::pair<char, Character>(*c, character));

			// 다음 글리프의 x좌표 계산
			x += face->glyph->bitmap.width;
		}
	}

	// 모든 작업 종료후 FreeType 자원해제
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// atlas가 생성되었음을 표시
	is_created_ = true;
}

std::string FontAtlas::GetWindowsDrive() {
        char windowsPath[MAX_PATH];
        if (GetWindowsDirectoryA(windowsPath, MAX_PATH) == 0) {
                qDebug() << "ERROR: Failed to get Windows directory.";
                return "";
        }

        // 윈도우즈 경로에서 드라이브 문자만 추출
        std::string windowsDrive(windowsPath, 2);
        return windowsDrive;
}