#include <windows.h>
#include <gl/gl.h>     
#include <gl/glut.h>   
#include <list>
#include<time.h>
#include "Sprite.h"
#include "Amoeba.h"
#include "GraphicState.h"

std::list<Sprite*> sprites;
Amoeba player;

int screenLeft = 0;
int screenRight = 500;
int screenTop = 500;
int screenBottom = 0;
clock_t currentTime;
clock_t lastTime = clock();
int FPS = 0;

void init ( GLvoid )   
{
	player = Amoeba();
	sprites.push_back( (Sprite*) (&player) );
	sprites.push_back((Sprite*) (new Amoeba()));
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable ( GL_COLOR_MATERIAL );
}

void display ( void )   
{

	FPS++;
	currentTime = clock();
	if( currentTime - lastTime >= CLOCKS_PER_SEC){
		printf("FPS = %d\n", FPS);
		lastTime = currentTime;
		FPS = 0;
	}

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
	
	gluOrtho2D(screenLeft, screenRight, screenBottom, screenTop);
	glMatrixMode( GL_MODELVIEW );  
}


void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
		player.setLeftMousePos(x,y);
		player.extendArm();
    }

    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
		player.setRightMousePos(x,y);
    }
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

		case('q'):
			player.incAngle();
			break;

		case('w'):
			player.decAngle();
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
	glutMouseFunc(mouse);
	glutKeyboardFunc( keyboard );
	glutSpecialFunc( arrow_keys );
	glutMainLoop();

	return 0;
}
>>>>>>> 624e7fa1cd4417bf983686ab8996bc3edcf922f6
