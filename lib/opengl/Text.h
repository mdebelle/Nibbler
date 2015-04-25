#ifndef		TEXT_H
# define	TEXT_H

# include	<string>

class Text
{
public:
	Text();
	~Text();

	void			init(const std::string&);
	void			print(const std::string& text, float x, float y, float size);

private:
	Text(const Text&);
	Text&			operator=(const Text&);

	unsigned int	_TextureID;
	unsigned int	_VertexBufferID;
	unsigned int	_UVBufferID;
	unsigned int	_ShaderID;
	unsigned int	_UniformID;

};

#endif
