#include "loaders.h"

#include <fstream>
#include <stdexcept>
#include <vector>

static unsigned int
loadShader(const std::string& file, GLenum type)
{
	GLuint shaderID = glCreateShader(type);

	std::string		shaderCode;
	std::ifstream	shaderStream("lib/opengl/shader/" + file, std::ios::in);
	if (!shaderStream.is_open())
		throw std::runtime_error(std::string("Impossible to open ") + file + ".");
	std::string line = "";
	while (getline(shaderStream, line))
		shaderCode += "\n" + line;
	shaderStream.close();

	GLint result = GL_FALSE;

	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer , NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int					InfoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char>	errorMessage(InfoLogLength);
		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &errorMessage[0]);
		throw std::runtime_error(std::string("Shader building failed: ") + errorMessage.data());
	}

	return shaderID;
}

unsigned int
loadShaders(const std::string& vertex, const std::string& fragment)
{
	unsigned int programID = glCreateProgram();
	unsigned int vertexShader, fragmentShader;

	try {
		vertexShader = loadShader(vertex, GL_VERTEX_SHADER);
		fragmentShader = loadShader(fragment, GL_FRAGMENT_SHADER);
	}
	catch (std::exception& ex) { throw; }

	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint result = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int InfoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		throw std::runtime_error(std::string("Shader linking failed: ") + ProgramErrorMessage.data());
	}

	return programID;
}

GLuint loadDDS(const std::string& path)
{
	char header[124];

	std::ifstream file; 
 
	file.open(path, std::ios::in | std::ios::binary); 
	if (!file.is_open())
		throw std::runtime_error(std::string("Impossible to open ") + path + ".");

	char filecode[4];
	file.read(filecode, 4); 
	if (std::string(filecode) != "DDS ")
		throw std::runtime_error(path + ": not a DDS texture.");
	
	file.read(header, 124); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

	unsigned int bufsize;
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	std::vector<char> buffer(bufsize * sizeof(unsigned char));

	file.read(&buffer[0], bufsize);
	file.close();

	unsigned int format;
	switch(fourCC)
	{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			throw std::runtime_error(path + ": unsupported compression.");
	}

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, &buffer[offset]);

		offset += size;
		width  /= 2;
		height /= 2;

		if(width < 1)
			width = 1;
		if(height < 1)
			height = 1;
	}
	return textureID;
}