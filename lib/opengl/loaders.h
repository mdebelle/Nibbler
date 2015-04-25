#ifndef		LOADERS_H
# define	LOADERS_H

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

# include	<string>
# include	<GL/glew.h>

unsigned int	loadShaders(const std::string&, const std::string&);
GLuint			loadDDS(const std::string&);

#endif