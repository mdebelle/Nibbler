#ifndef SFDISPLAY_H
# define SFDISPLAY_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <map>
# include <vector>
# include "IDisplay.h"
# include "Text.h"

# define UNIT_SIZE	20

class GlDisplay : public IDisplay
{
	public:
		GlDisplay();
		~GlDisplay();

		void			init(int width, int height) override;
		void			drawMenu(bool, bool) override;
		void			drawField() override;
		void			drawScoring(int pts, int player, int level, bool multi) override;
		void			drawPattern(int posX, int posY, Pattern::Type type) override;
		void			display() override;
		IDisplay::Key	getEvent() override;
		void			close() override;

		static int		_LastKey;

	private:
		GLFWwindow*		_Window;
		float				_Width;
		float				_Height;
		std::map<int, IDisplay::Key> _Key_map;

		Text			_Text;
		GLuint			_ProgramID;
		GLuint			_VertexArrayID;
		GLuint			_VertexBuffer;
		GLuint			_ColorBuffer;

		std::vector<GLfloat>	_Vertices;
		std::vector<GLfloat>	_Colors;
};

#endif
