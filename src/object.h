#ifndef OBJECT_H
#define OBJECT_H

typedef struct {
	float x_koordinata;
	float y_koordinata;
    bool visible;
} Novcic;

void draw_sphere(double* move, double jump);
void draw_floor_1(int* i);
void draw_floor_2(int* i);
void iscrtaj_prepreke(double* poligon_x, double* poligon_y, double* ball_x_coord, double* broj_prepreka,double* koordinata_poslednje_prepreke, int pomeraj, double k);
void iscrtaj_novcice(double ball_x, double ball_y, Novcic* novcici, int* brojac_novcica);


#endif
