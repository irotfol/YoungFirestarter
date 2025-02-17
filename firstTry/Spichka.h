#pragma once
#include <string>

#include <vector>
#include <list>

#include <iomanip>
#include <iostream>
#include <cmath>

#include "MyFunk.h"

struct xy {
	short int x;
	short int y;
	bool operator==(const xy & b) const {
		if ((x == b.x) && (y == b.y)) {
			return true;
		}
		else {
			return false;
		}
	};
	int output() {
		std::cout << x << ' ' << y << '\n';
		return 0;
	};
};

class Spichka {
public:
	bool operator==(const Spichka& b) const;
	bool operator==(const xy& b) const;
	bool operator%=(const Spichka& b) const;
	bool is_diagonal() const;
	int input(char* str);
	int set_diagonal(Spichka* diagonal);
	xy* get_point(bool n);
	Spichka* get_diag_spichka();
	unsigned int get_t() const;
	int output() const;

	Spichka();
private:
	xy point1;
	xy point2;
	Spichka* diagonal;
	unsigned int t;
};

class Spichka_on_fire {
public:
	bool operator<(const Spichka_on_fire& b)const;
	int operator-(float number);
	Spichka_on_fire(Spichka* spichka);
	int fire(xy point);
	int fire();
	int get_fire_points(xy* points[2]);
	float get_strenght();
	float get_min() const;
	Spichka* get_diag_spichka();
	Spichka* get_cur_spichka();
	bool is_on_fire();
	bool is_full_strenght();
	bool is_fire_centre();
	~Spichka_on_fire();
private:
	Spichka* current_spichka;
	bool* is_fire;
	float* fire_time;
};

class Vec_Spichka {
public:
	int input(char* str);
	int create_points();
	int ignite();
	float step();
	xy get_best_point();
	float get_min_time();
	double get_best_time() const;
	std::list <xy>* get_points();
	int output();
	Vec_Spichka(unsigned short int kolvo);
	~Vec_Spichka();
private:
	std::vector<Spichka*> vec;
	std::list<Spichka*> vec_on_fire;
	std::list<Spichka_on_fire*> list_of_fire;
	std::list<xy> points;
	xy* points_buf[2];

	double current_time;

	xy* best_point;
	double best_time;

	unsigned short int kolvo;
};