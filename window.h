#define WIDTH 640
#define HEIGHT 480
#define POSX 320
#define POSY 240
float fac=0.0;
int const fbo_width = 320;
int const fbo_height = 240;
int AA=0;
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
GLuint fb, color, depth;
bool minus=false;
void CHECK_FRAMEBUFFER_STATUS()
{                                                         
    GLenum status;
    status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER); 
    switch(status) {
    case GL_FRAMEBUFFER_COMPLETE:
        break;

    case GL_FRAMEBUFFER_UNSUPPORTED:
    /* choose different formats */
        break;

    default:
        /* programming error; will fail on all hardware */
        fputs("Framebuffer Error\n", stderr);
        exit(-1);
    }
}

float const light_dir[]={1,1,1,0};
float const light_color[]={1,0.95,0.9,1};

void init()
{
    glGenFramebuffers(1, &fb);
    glGenTextures(1, &color);
    glGenRenderbuffers(1, &depth);

    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    glBindTexture(GL_TEXTURE_2D, color);
    glTexImage2D(   GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            fbo_width, fbo_height,
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, fbo_width, fbo_height);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

    CHECK_FRAMEBUFFER_STATUS();
}
void render()
{
	if (1==1){
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0,0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glColor3f(1.0, 0.0,0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glColor3f(0.0, 1.0,0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0,1.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glEnd();
	}
}
void prepare()
{
    
    static float a=0, b=0, c=0;
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_TEXTURE_2D);
    glViewport(0,0, fbo_width, fbo_height);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);
    glClearColor(0.2+fac,0,0,1);
    glClear( GL_COLOR_BUFFER_BIT);
    render();
}
int A=0;
void final()
{

    int win_width  = glutGet(GLUT_WINDOW_WIDTH);
    int win_height = glutGet(GLUT_WINDOW_HEIGHT);
    double ratioX = (double) win_width / 320;
    double ratioY = (double) win_height / 240;
    double ratio = ratioX < ratioY ? ratioX : ratioY;
    win_width = (320 * ratio);
    win_height = (240 * ratio);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int winx=(glutGet(GLUT_WINDOW_WIDTH)-win_width)/2;
	int winy=(glutGet(GLUT_WINDOW_HEIGHT)-win_height)/2;
	glViewport(winx,winy, win_width, win_height);
//	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
    //glClearColor(0.,0.,0.,0.);
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, color);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.1, -2.1, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.1, -2.1, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.1, 2.1, 0.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.1, 2.1, 0.0);
    glEnd();
if (A == 0){
    Shader source("src/shaders/screen.vert","src/shaders/screen.shader");
    source.Activate();
    printf("something");
    A=1;}
}

void display()
{
	if (minus==false){fac+=0.004;}
	else {fac -=0.004;}
	if (fac<=-0.0){minus=false;}
	if (fac>=1.0){minus=true;}
	
    prepare();
    final();
    glutSwapBuffers();
    glFlush();

}
