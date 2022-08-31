#include "pch.h"
#include "B911400.h"

//spotlight 실행
void B911400::initialize()
{
	
}
//앞선 조명 2개 끄기
void B911400::destroy()
{
	
}

//구현
void	B911400::drawSphere()
{
	//키보드 선언 구현을 위한 전역변수 때문에, 여기서는 빛에 대해서만 구현하고 나머지는 OpenGLtestView.cpp안에 DrawGLScene에 구현을 하였습니다.(18줄~30줄, 165줄~175줄,193줄~276줄, 385줄~459줄)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	GLfloat light0_ambient[] = { 0.05, 0.2, 0.05, 1.0 };
	GLfloat light0_diffuse[] = { 0.6, 0.8, 0.4, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_position[] = { 0.2, 2.2, 5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	GLfloat light1_ambient[] = { 0.1, 0.0, 0.2, 1.0 };
	GLfloat light1_diffuse[] = { 0.6, 0.2, 0.5, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { -1, 2, -3.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	GLfloat light2_ambient[] = { 0.0, 0.0, 0.1, 1.0 };
	GLfloat light2_diffuse[] = { 0.2, 0.5, 0.2, 1.0 };
	GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light2_position[] = { -1, -2, 3.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);


	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.5, 0.3, 0.7, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat high_shininess[] = { 70.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	
	return;
}

