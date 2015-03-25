#ifndef SFDISPLAY_H
# define SFDISPLAY_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <map>
# include "IDisplay.h"

# define UNIT_SIZE	20

class GlDisplay : public IDisplay
{
	public:
		GlDisplay();
		~GlDisplay();

		void			init(int width, int height) override;
		void			drawField() override;
		void			drawScoring( int pts ) override;
		void	drawPattern(
			int posX,
			int posY,
			int sizeX,
			int SizeY,
			Pattern::Type type
		) override;
		void			display() override;
		IDisplay::Key	getEvent() override;
		void			close() override;

	private:
		GLFWwindow*		_Window;
		std::map<int, IDisplay::Key> _Key_map;

		GLuint			_ProgramID;
		GLuint			_VertexArrayID;
		GLuint			_VertexBuffer;

		GLuint			loadShader(const char*, const char*);
		GLfloat			g_vertex_buffer_data[9];
};

#endif
