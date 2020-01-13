#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include "object.h"

#define pi 3.141592653589793

void draw_cube(){
	// Funkcija za crtanje kocke
	glPushMatrix();
	glScalef(1,0.2,1);
	glutSolidCube(0.2);
	glPopMatrix();
}

void draw_sphere(double* move, double jump){
	/* ambijentalna refleksija za sferu*/
	GLfloat ambient_lopta[] = {1, 0, 0, 1};      
	
	/* difuzna refleksija za sferu*/
	GLfloat diffuse_lopta[] = {1, 0, 0, 1};        

	/* spekularna refleksija za sferu*/
	GLfloat specular_lopta[] = { 9/10, 0, 0, 1 };           

	GLfloat shininess = 5;

	glPushMatrix();
	/* crtamo sferu */
	glTranslatef(*move, jump, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_lopta);  
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_lopta);  
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_lopta);
	glMaterialf( GL_FRONT, GL_SHININESS, shininess);      

    glutSolidSphere(0.05, 50,50);
	
	glPopMatrix();
}

void iscrtaj_prepreke(double* poligon_x, double* poligon_y, double* ball_x_coord, double* broj_prepreka, double* koordinata_poslednje_prepreke, int pomeraj){

	if (*ball_x_coord + 3 > *koordinata_poslednje_prepreke){
		for (int i=0; i<*broj_prepreka; ++i){
			poligon_x[i] += pomeraj - 2 - 3;
		}
		*koordinata_poslednje_prepreke += pomeraj - 5;
	}

	for (int i=0; i<*broj_prepreka; i++){
		glPushMatrix();
			glTranslatef(poligon_x[i],  poligon_y[i],0);
			draw_cube();
		glPopMatrix();
	}
}

void draw_floor_1(int* i){

	/* Crtamo podlogu */
	glBegin(GL_POLYGON);
		glNormal3f(0,1,0);
		glVertex3f((*i)-2, -0.05, -0.2);
		glVertex3f((*i)-2, -0.05,  0.2);
		glVertex3f((*i)+4, -0.05,  0.2);
		glVertex3f((*i)+4, -0.05, -0.2);
	glEnd();
	
	/* crtanje prednje ivice podloge*/
	glBegin(GL_POLYGON);
		glNormal3f(0,0,-1);
		glVertex3f((*i)-2, -0.05, 0.2 );
		glVertex3f((*i)-2,    -5, 0.2 );
		glVertex3f((*i)+4,    -5, 0.2 );
		glVertex3f((*i)+4, -0.05, 0.2 );
	glEnd();

}

void draw_floor_2(int* i){

	/* Crtamo podlogu */

	glBegin(GL_POLYGON);
		glNormal3f(0,1,0);
		glVertex3f((*i)+4 , -0.05, -0.2);
		glVertex3f((*i)+4 , -0.05,  0.2);
		glVertex3f((*i)+10, -0.05,  0.2);
		glVertex3f((*i)+10, -0.05, -0.2);
	glEnd();
	
	/* crtanje prednje ivice podloge*/
	glBegin(GL_POLYGON);
		glNormal3f(0,0,-1);
		glVertex3f((*i)+4 , -0.05, 0.2 );
		glVertex3f((*i)+4 ,    -5, 0.2 );
		glVertex3f((*i)+10,    -5, 0.2 );
		glVertex3f((*i)+10, -0.05, 0.2 );
	glEnd();

}
/**
 * Funkcija koja iscrtava novcice koji igracu daju mogucnost
 * jednog duplog skoka ako hoce da se izvuce iz neke 
 * "nezgodne" situacije (pada pored prepreke).
 * 
 * @param ball_x - X koordinata loptice
 * @param ball_y - Y koordinata loptice
 * @param novcici - niz struktura
 */
void iscrtaj_novcice(double ball_x, double ball_y, Novcic* novcici){
	/* ambijentalna refleksija za novcic*/
	GLfloat ambient_novcic[] = {1, 1, 0, 1};      
	
	/* difuzna refleksija za novcic*/
	GLfloat diffuse_novcic[] = {1, 1, 0, 1};        

	/* spekularna refleksija za novcic*/
	GLfloat specular_novcic[] = { 9/10, 1, 0, 1 };           
	GLfloat shininess = 5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_novcic);  
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_novcic);  
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_novcic);
	glMaterialf( GL_FRONT, GL_SHININESS, shininess);      

	//iscrtavanje
	for(int i=0; i<100; ++i){
		if (!novcici[i].visible)
			continue;
		// ako je lopta dodirnula novcic pomeramo y koordinatu 
		// novcica da izgleda kao da je nestao i sprecavamo
		// ponovno iscrtavanje.
		if ((novcici[i].x_koordinata == ((int)(ball_x+0.2)+0.5))
			&& (ball_x >= ((int)(novcici[i].x_koordinata)+0.42)
				&& ball_x <= ((int)(novcici[i].x_koordinata)+0.58))
			&& ((ball_y >= 0.35) &&
				(ball_y  <= 0.45))){
			novcici[i].y_koordinata = 1.5;
			novcici[i].visible = false;
		}
		glPushMatrix();
			glTranslatef(novcici[i].x_koordinata, novcici[i].y_koordinata, 0);
			glutSolidTorus(0.01, 0.02, 10, 10);
		glPopMatrix();
	}
}

void inicijalizuj(Novcic* novcici){
	for (int i=0; i<100; ++i){
		novcici[i].x_koordinata = i*2 + 0.5;
		novcici[i].y_koordinata = 0.4;
		novcici[i].visible = true;
	}

}