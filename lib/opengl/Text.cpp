#include <vector>
#include <cstring>

#include <GL/glew.h>

#include "loaders.h"
#include "Text.h"

Text::
Text()
{}

Text::
~Text()
{
	glDeleteBuffers(1, &_VertexBufferID);
	glDeleteBuffers(1, &_UVBufferID);
	glDeleteTextures(1, &_TextureID);
	glDeleteProgram(_ShaderID);
}

void Text::
init(const std::string& path)
{
	try { _TextureID = loadDDS(path); }
	catch(std::exception& ex) { throw; }

	glGenBuffers(1, &_VertexBufferID);
	glGenBuffers(1, &_UVBufferID);

	try { _ShaderID = loadShaders("textVertex.glsl", "textFragment.glsl"); }
	catch(std::exception& ex) { throw; }

	_UniformID = glGetUniformLocation( _ShaderID, "myTextureSampler" );
}

void Text::
print(const std::string& text, float x, float y, float size)
{
	std::vector<float> vertices;
	std::vector<float> UVs;

	for (unsigned int i = 0; i < text.size(); i++)
	{
		float vertex_up_left[2]		{ x + i * size			, y + size };
		float vertex_up_right[2]	{ x + i * size + size	, y + size };
		float vertex_down_right[2]	{ x + i * size + size	, y };
		float vertex_down_left[2]	{ x + i * size			, y };

		vertices.insert(vertices.end(), {
			vertex_up_left[0], vertex_up_left[1],
			vertex_down_left[0], vertex_down_left[1],
			vertex_up_right[0], vertex_up_right[1]
		});
		vertices.insert(vertices.end(), {
			vertex_down_right[0], vertex_down_right[1],
			vertex_up_right[0], vertex_up_right[1],
			vertex_down_left[0], vertex_down_left[1]
		});

		float uv_x = (text[i] % 16) / 16.0f;
		float uv_y = (text[i] / 16) / 16.0f;

		float uv_up_left[2]		{ uv_x					, uv_y };
		float uv_up_right[2]	{ uv_x + 1.0f / 16.0f	, uv_y };
		float uv_down_right[2]	{ uv_x + 1.0f / 16.0f	, (uv_y + 1.0f / 16.0f) };
		float uv_down_left[2]	{ uv_x					, (uv_y + 1.0f / 16.0f) };

		UVs.insert(UVs.end(), {
			uv_up_left[0], uv_up_left[1],
			uv_down_left[0], uv_down_left[1],
			uv_up_right[0], uv_up_right[1]
		});
		UVs.insert(UVs.end(), {
			uv_down_right[0], uv_down_right[1],
			uv_up_right[0], uv_up_right[1],
			uv_down_left[0], uv_down_left[1]
		});
	}

	glBindBuffer(GL_ARRAY_BUFFER, _VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _UVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(float), UVs.data(), GL_STATIC_DRAW);

	glUseProgram(_ShaderID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _TextureID);
	glUniform1i(_UniformID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _VertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _UVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}