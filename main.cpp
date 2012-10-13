
#include <windows.h>
#include <list>
#include "Sprite.h"
#include "Amoeba.h"
#include "GraphicState.h"
#include <gl/gl.h>  
#include <gl/glut.h>  

std::list<Sprite*> sprites;

void init ( GLvoid )   
{
	sprites.push_back( (Sprite*) (new Amoeba()) );
	/*glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glEnable ( GL_COLOR_MATERIAL );
	*/

	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,50.0,0.0,50.0);
	glMatrixMode(GL_MODELVIEW);
}

void display ( void )   
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glLoadIdentity();

	for( std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++){
		Sprite* s = *it;
		s->update();
		for( std::list<Sprite*>::iterator it2 = sprites.begin(); it2 != sprites.end(); it2++){
			s->collision(*it);
		}
		s->draw();
		s->setVel(0,0);
	}

	
}

void reshape ( int w, int h )
{
	glViewport( 0, 0, w , h );
	glMatrixMode( GL_PROJECTION );  
	glLoadIdentity();                
	gluOrtho2D(SCREEN_LEFT, SCREEN_RIGHT, SCREEN_BOTTOM, SCREEN_TOP);
	glMatrixMode( GL_MODELVIEW );  
}

void keyboard ( unsigned char key, int x, int y )
{
}

void arrow_keys ( int a_keys, int x, int y )
{
  switch ( a_keys ) 
  {
    case GLUT_KEY_UP:

		for( std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++)
		{
			Sprite* s = *it;
			s->setVel(0,100);
		}

      break;
    case GLUT_KEY_DOWN:

		puts("hello");
		for( std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++)
		{
			Sprite* s = *it;
			s->setVel(0,-100);
		}

      break;
    default:
      break;
  }
}

void animateScene(void)
{
	glutPostRedisplay();
}

int main ( int argc, char** argv )
{
	glutInit( &argc, argv );
	init();
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize( 500, 500 ); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow( "Amoeba Boxing" );
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutSpecialFunc( arrow_keys );
	glutIdleFunc(animateScene);
	glutMainLoop();

	return 0;
}

