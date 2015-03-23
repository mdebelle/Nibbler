#ifndef SFDISPLAY_H
# define SFDISPLAY_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "IDisplay.h"

# define UNIT_SIZE	20

class GlDisplay : public IDisplay
{
	public:
		GlDisplay();
		~GlDisplay();

		void			init(int width, int height) override;
		void			drawField() override;
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
};

#endif
