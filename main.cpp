#include <windows.h>
#include <gl/gl.h>     
#include <gl/glut.h>   
#include <list>
#include "Sprite.h"
#include "Amoeba.h"
#include "GraphicState.h"

std::list<Sprite*> sprites;
Amoeba player;

int screenLeft = 0;
int screenRight = 0;
int screenTop = 0;
int screenBottom = 0;

void init ( GLvoid )   
{
	player = Amoeba();
	sprites.push_back( (Sprite*) (&player) );
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable ( GL_COLOR_MATERIAL );
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
	}

	glutSwapBuffers ( );
	glutPostRedisplay();
}

void reshape ( int w, int h )
{
	glViewport( 0, 0, w , h );
	glMatrixMode( GL_PROJECTION );  
	glLoadIdentity();   
	
	screenRight = w;
	screenTop = h;
	gluOrtho2D(screenLeft, screenRight, screenBottom, screenTop);
	glMatrixMode( GL_MODELVIEW );  
}

void keyboard ( unsigned char key, int x, int y )
{
	switch ( key ) 
	{

		case('e'):
			player.extendArm();
			break;

		case('r'):
			player.retractArm();
			break;

		default:
			break;
	}
}

void arrow_keys ( int a_keys, int x, int y )
{
  switch ( a_keys ) {
    case GLUT_KEY_UP:
		player.setVely( 5.0f);
		break;
    case GLUT_KEY_DOWN:
		player.setVely( -5.0f);
		break;
	case GLUT_KEY_LEFT:
		player.setVelx(-5.0f);
		break;
	case GLUT_KEY_RIGHT:
		player.setVelx(5.0f);
		break;
    default:
      break;
  }
}

int main ( int argc, char** argv )
{
	glutInit( &argc, argv );
	init();
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize( 500, 500 ); 
	glutCreateWindow( "Amoeba Boxing" );
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutSpecialFunc( arrow_keys );
	glutMainLoop();

	return 0;
}
