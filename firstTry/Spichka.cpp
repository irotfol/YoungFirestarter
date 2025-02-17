#include "Spichka.h"

Spichka::Spichka() {
	this->point1 = { 0, 0 };
	this->point2 = { 0, 0 };
	this->t = 0;
	this->diagonal = nullptr;
}

int Spichka::input(char* str) {
	short int* coord[4] = { &this->point1.x, &this->point1.y, &this->point2.x, &this->point2.y };
	
	char delims[] = " ";
	char* next_token1 = NULL;
	char* token = strtok_s(str, delims, &next_token1);
	for (int i = 0; i < 4; ++i) {
		if (token != NULL) {
			if (my_atoi <short int>(token, -200, 200, coord[i]) != 0) {
				return 1;
			}
			token = strtok_s(NULL, delims, &next_token1);
		}
		else {
			std::cout << "incorrect amount of numbers" << '\n';
			return 2;
		}
	}

	if (this->point1 == this->point2) {
		std::cout << "Points of spichka is the same" << '\n';
		return 3;
	}

	if ((abs(this->point1.x - this->point2.x) > 1) || (abs(this->point1.y - this->point2.y) > 1)) {
		std::cout << "Spichka is too long" << '\n';
		return 4;
	}

	if (my_atoi <unsigned int>(token, 1, (unsigned int)pow(10, 7), &this->t) != 0) {
		std::cout << "Incorrect burning time of Spichka" << '\n';
		return 5;
	}
	return 0;
}

int Spichka::output() const{
	std::cout << this->point1.x << ' ' << this->point1.y << ' ' << this->point2.x << ' ' << this->point2.y << '\n';
	return 0;
}

int Spichka::set_diagonal(Spichka* diagonal) {
	if (diagonal == nullptr) {
		return 1;
	}
	else {
		this->diagonal = diagonal;
		return 0;
	}
}

xy* Spichka::get_point(bool n) {
	if (n) {
		return &this->point1;
	}
	else {
		return &this->point2;
	}
}

unsigned int Spichka::get_t() const {
	return this->t;
}

bool Spichka::is_diagonal() const {
	if (this->diagonal == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

Spichka* Spichka::get_diag_spichka() {
	return this->diagonal;
}

bool Spichka::operator==(const Spichka& b) const{
	if (
		((this->point1 == b.point1) && (this->point2 == b.point2))
		||
		((this->point1 == b.point2) && (this->point2 == b.point1))
		) {
		return true;
	}
	else {
		return false;
	}
}

bool Spichka::operator==(const xy& b) const {
	if ((this->point1 == b) || (this->point2 == b)) {
		return true;
	}
	else {
		return false;
	}
}

bool Spichka::operator%=(const Spichka& b) const {
	if (((point1.x + point2.x) == (b.point1.x + b.point2.x)) && ((point1.y + point2.y) == (b.point1.y + b.point2.y))) {
		return true;
	}
	else {
		return false;
	}
}

Spichka_on_fire::Spichka_on_fire(Spichka* spichka) {
	this->current_spichka = spichka;
	int i = 0;
	if (this->current_spichka->is_diagonal()) {
		this->fire_time = new float[4];
		this->is_fire = new bool[3];
		for (i = 0; i < 3; ++i) {
			this->is_fire[i] = false;
			this->fire_time[i] = 0.0f;
		}
		this->fire_time[3] = 0.0f;
	}
	else {
		this->fire_time = new float[2];
		this->is_fire = new bool[2];
		for (i = 0; i < 2; ++i) {
			this->is_fire[i] = false;
			this->fire_time[i] = 0.0f;
		}
	}
}

float Spichka_on_fire::get_min() const{
	int i = 0;
	int j = 0;
	int n = 2;
	float min = 0.0f;
	if (this->current_spichka->is_diagonal()) {
		n = 4;
	}
	for (i = 0; i < n; ++i) {
		if ((min == 0.0f) && (this->fire_time[i] != 0.0f)) {
			min = this->fire_time[i];
			break;
		}
	}
	for (j = i + 1; j < n; ++j) {
		if ((min > this->fire_time[j]) && (this->fire_time[j] != 0.0f)) {
			min = this->fire_time[j];
		}
	}
	return min;
}

bool Spichka_on_fire::operator<(const Spichka_on_fire& b)const {
	bool result = false;
	if (this->get_min() < b.get_min()) {
		return true;
	}
	else {
		return result;
	}
}

int Spichka_on_fire::operator-(float number) {
	int i = 0;
	int n = 2;
	if (this->current_spichka->is_diagonal()) {
		n = 4;
	}
	for (i = 0; i < n; ++i) {
		if (this->fire_time[i] != 0.0f) {
			this->fire_time[i] -= number;
		}
	}
	return 0;
}

float Spichka_on_fire::get_strenght() {
	float sum_float = 0.0f;
	int i = 0;
	int n = 2;
	if (this->current_spichka->is_diagonal()) {
		n = 4;
	}
	for (i = 0; i < n; ++i) {
		sum_float += this->fire_time[i];
	}
	return sum_float;
}

bool Spichka_on_fire::is_on_fire() {
	int i = 0;
	int n = 2;
	if (this->current_spichka->is_diagonal()) {
		n = 3;
	}
	for (i = 0; i < n; ++i) {
		if (this->is_fire[i]) {
			return true;
		}
	}
	return false;
}

bool Spichka_on_fire::is_full_strenght() {
	if ((this->get_strenght() == 0.0f) && (!this->is_on_fire())) {
		return true;
	}
	return false;
}

int Spichka_on_fire::fire(xy point) {
	bool full_strenght = this->is_full_strenght();

	if ((*this->current_spichka->get_point(0) == point) && (this->is_fire[0] == false)) {
		this->is_fire[0] = true;
		if (full_strenght) {
			if (this->current_spichka->is_diagonal()) {
				this->fire_time[0] = ((float)this->current_spichka->get_t()) / 2.0f;
			}
			else {
				this->fire_time[0] = ((float)this->current_spichka->get_t());
			}
		}
		else {
			if (this->current_spichka->is_diagonal()) {
				if (this->is_fire[2] && (this->fire_time[2] != 0.0f)) {
					this->fire_time[2] = this->fire_time[2] / 2.0f;
					this->fire_time[0] = this->fire_time[2];
					this->is_fire[0] = true;
				}
			}
			else {
				if (this->is_fire[1] && (this->fire_time[1] != 0.0f)) {
					this->fire_time[1] = this->fire_time[1] / 2.0f;
					this->fire_time[0] = this->fire_time[1];
				}
			}
		}
	}
	else {
		if ((*this->current_spichka->get_point(1) == point) && (this->is_fire[1] == false)) {
			this->is_fire[1] = true;
			if (full_strenght) {
				if (this->current_spichka->is_diagonal()) {
					this->fire_time[1] = ((float)this->current_spichka->get_t()) / 2.0f;
				}
				else {
					this->fire_time[1] = ((float)this->current_spichka->get_t());
				}
			}
			else {
				if (this->current_spichka->is_diagonal()) {
					if (this->is_fire[3] && (this->fire_time[3] != 0.0f)) {
						this->fire_time[3] = this->fire_time[3] / 2.0f;
						this->fire_time[1] = this->fire_time[3];
					}
				}
				else {
					if (this->is_fire[0] && (this->fire_time[0] != 0.0f)) {
						this->fire_time[0] = this->fire_time[0] / 2.0f;
						this->fire_time[1] = this->fire_time[0];
						this->is_fire[1] = true;
					}
				}
			}
		}
		else {
			return 1;
		}
	}
	return 0;
}
int Spichka_on_fire::fire() {
	bool full_strenght = this->is_full_strenght();
	if (this->is_fire[2] == false) {
		this->is_fire[2] = true;
		if (full_strenght) {
			this->fire_time[2] = ((float)this->current_spichka->get_t()) / 2.0f;
			this->fire_time[3] = this->fire_time[2];
		}
		else {
			if (this->is_fire[0]) {
				if (this->fire_time[0] != 0.0f) {
					this->fire_time[0] = this->fire_time[0] / 2.0f;
					this->fire_time[2] = this->fire_time[0];
				}
			}
			else {
				this->fire_time[2] = ((float)this->current_spichka->get_t()) / 2.0f;
			}
			if (this->is_fire[1]) {
				if (this->fire_time[1] != 0.0f) {
					this->fire_time[1] = this->fire_time[1] / 2.0f;
					this->fire_time[3] = this->fire_time[1];
				}
			}
			else {
				this->fire_time[3] = ((float)this->current_spichka->get_t()) / 2.0f;
			}
		}
		return 0;
	}
	else {
		return 1;
	}
}

bool Spichka_on_fire::is_fire_centre() {
	if (this->current_spichka->is_diagonal()) {
		if ((!this->is_fire[2]) && (this->is_fire[0] ^ this->is_fire[1]) && (this->fire_time[0] == 0.0f) && (this->fire_time[1] == 0.0f)) {
			return true;
		}
	}
	return false;
}

Spichka* Spichka_on_fire::get_diag_spichka() {
	return this->current_spichka->get_diag_spichka();
}

Spichka* Spichka_on_fire::get_cur_spichka() {
	return this->current_spichka;
}

int Spichka_on_fire::get_fire_points(xy* points[2]) {
	int result = 1;
	points[0] = nullptr;
	points[1] = nullptr;
	if ((this->is_fire[0]) && (!this->is_fire[1])) {
		points[1] = this->current_spichka->get_point(1);
		result = 0;
	}
	if ((this->is_fire[1]) && (!this->is_fire[0])) {
		points[0] = this->current_spichka->get_point(0);
		result = 0;
	}
	return result;
}

Spichka_on_fire::~Spichka_on_fire() {
	if (this->fire_time != nullptr) {
		delete[] this->fire_time;
		this->fire_time = nullptr;
	}
	if (this->is_fire != nullptr) {
		delete[] this->is_fire;
		this->is_fire = nullptr;
	}
}


Vec_Spichka::Vec_Spichka(unsigned short int kolvo) {
	this->kolvo = kolvo;
	this->vec.reserve(kolvo);

	this->current_time = 0.0;

	this->best_point = nullptr;
	this->best_time = 0.0;

	points_buf[0] = { nullptr };
	points_buf[1] = { nullptr };
}

float Vec_Spichka::get_min_time() {
	float min = 0.0f;
	for (std::list<Spichka_on_fire*>::iterator it = this->list_of_fire.begin(); it != this->list_of_fire.end(); ++it) {
		if (min == 0.0f) {
			min = (*it)->get_min();
		}
		else {
			if (min > (*it)->get_min()) {
				min = (*it)->get_min();
			}
		}
	}
	return min;
}

float Vec_Spichka::step() {
	float min = this->get_min_time();

	if (min == 0.0f) {
		return 0.0f;
	}
	int i = 0;
	int j = 0;
	bool is_new_spichka = true;
	Spichka_on_fire* temp_spichka = nullptr;
	std::list<Spichka_on_fire*>::iterator it = this->list_of_fire.begin();
	std::list<Spichka*>::iterator it2 = this->vec_on_fire.begin();
	//Subtracting the burning time from the matches
	for (it = this->list_of_fire.begin(); it != this->list_of_fire.end(); ++it) {
		(*it)->operator-(min);
	}
	//Iterating through all matches that are supposed to ignite other matches
	for (it = this->list_of_fire.begin(); it != this->list_of_fire.end(); ++it) {
		if ((*it)->get_strenght() != 0.0f) {
			continue;
		}
		else {
			//If a match has burned to the center and has an intersecting match, continue burning and spread the fire further
			if ((*it)->is_fire_centre()) {
				(*it)->fire();
				is_new_spichka = true;
				for (it2 = this->vec_on_fire.begin(); it2 != this->vec_on_fire.end(); ++it2) {
					if ((*it2) == (*it)->get_diag_spichka()) {
						is_new_spichka = false;
						break;
					}
				}
				//If the ignited match is new, add it to the list of burning matches
				if (is_new_spichka) {
					this->vec_on_fire.push_back((*it)->get_diag_spichka());
					temp_spichka = new Spichka_on_fire((*it)->get_diag_spichka());
					temp_spichka->fire();
					this->list_of_fire.push_back(temp_spichka);
				}
				else {
					//If the match is already in the list, distribute the match's strength across the burning segments
					for (std::list<Spichka_on_fire*>::iterator it3 = this->list_of_fire.begin(); it3 != this->list_of_fire.end(); ++it3) {
						if ((*it3)->get_cur_spichka() == (*it)->get_diag_spichka()) {
							(*it3)->fire();
							break;
						}
					}
				}
			}
			else {
				//Get the points that should be ignited next
				(*it)->get_fire_points(this->points_buf);
				for (j = 0; j < 2; ++j) {
					if (this->points_buf[j] != nullptr) {
						for (i = 0; i < this->vec.size(); ++i) {
							if (*this->vec[i] == *(this->points_buf[j])) {
								is_new_spichka = true;
								for (it2 = this->vec_on_fire.begin(); it2 != this->vec_on_fire.end(); ++it2) {
									if ((*it2) == this->vec[i]) {
										is_new_spichka = false;
										break;
									}
								}
								//Igniting the next point on an existing match or a new one, and distribute the match's strength across the burning segments
								if (is_new_spichka) {
									this->vec_on_fire.push_back(this->vec[i]);
									temp_spichka = new Spichka_on_fire(this->vec[i]);
									temp_spichka->fire(*(this->points_buf[j]));
									this->list_of_fire.push_back(temp_spichka);
								}
								else {
									for (std::list<Spichka_on_fire*>::iterator it3 = this->list_of_fire.begin(); it3 != this->list_of_fire.end(); ++it3) {
										(*it3)->fire(*(this->points_buf[j]));
									}
								}
							}
						}
					}
				}
			}
			
		}
	}
	//Removing burned-out matches
	it = this->list_of_fire.begin();
	while (it != this->list_of_fire.end()) {
		if ((*it)->get_strenght() == 0.0f) {
			temp_spichka = *it;
			it = this->list_of_fire.erase(it);
			delete temp_spichka;
			temp_spichka = nullptr;
		}
		else {
			if (it != this->list_of_fire.end()) {
				it++;
			}
		}
	}
	return min;
}

int Vec_Spichka::input(char* str) {
	int i = 0;
	int j = 0;
	for (i = 0; i < this->kolvo; ++i) {
		if (my_getline(str, 29) != 0) {
			return 3;
		}
		vec.push_back(new Spichka);
		if (this->vec[i]->input(str) != 0) {
			return 4;
		}
		for (j = i - 1; j >= 0; --j) {
			if (*vec[i] == *vec[j]) {
				std::cout << "Spichka can't share same coordinates with other Spichka" << '\n';
				return 5;
			}
			if (*vec[i] %= *vec[j]) {
				vec[i]->set_diagonal(vec[j]);
				vec[j]->set_diagonal(vec[i]);
			}
		}
	}
	return 0;
}

int Vec_Spichka::ignite() {
	int i = 0;
	float node_time = 0.0f;
	Spichka_on_fire* temp_spichka = nullptr;
	std::list<Spichka_on_fire*>::iterator it2 = this->list_of_fire.begin();
	//Simulation for all points
	for (std::list<xy>::iterator it = this->points.begin(); it != this->points.end(); ++it) {
		this->current_time = 0.0;
		this->vec_on_fire.clear();
		//Clearing lists from the previous simulation
		it2 = this->list_of_fire.begin();
		while (it2 != this->list_of_fire.end()) {
			temp_spichka = *it2;
			delete temp_spichka;
			temp_spichka = nullptr;
			it2++;
		}
		this->list_of_fire.clear();
		//Adding the first matches for burning
		for (i = 0; i < this->vec.size(); ++i) {
			if (*this->vec[i] == *it) {
				this->vec_on_fire.push_back(this->vec[i]);
				temp_spichka = new Spichka_on_fire(this->vec[i]);
				temp_spichka->fire(*it);
				this->list_of_fire.push_back(temp_spichka);
			}
		}
		//Calculating the minimum burning time until the next ignition point and subtracting the burning time from the matches
		do { 
			node_time = this->step();
			this->current_time += node_time;
		} while (node_time != 0.0f);
		/*If not all matches have been affected, the program terminates prematurely,
		indicating that not all matches are connected into a complete figure*/
		if (this->vec.size() != this->vec_on_fire.size()) {
			std::cout << "Spichkas didn't linked together" << '\n';
			return 1;
		}
		//Recording the best result
		if ((current_time < this->best_time) || (this->best_time == 0.0f)) {
			this->best_time = current_time;
			this->best_point = &(*it);
		}
	}
	return 0;
}

int Vec_Spichka::create_points() {
	this->points.clear();
	int i = 0;
	bool contain[2] = {false, false};
	for (i = 0; i < this->vec.size(); ++i) {
		for (std::list<xy>::iterator it = this->points.begin(); it != this->points.end(); ++it) {
			if (contain[0] == false) {
				if (*this->vec[i]->get_point(0) == *it) {
					contain[0] = true;
				}
			}
			if (contain[1] == false) {
				if (*this->vec[i]->get_point(1) == *it) {
					contain[1] = true;
				}
			}
			if (contain[0] && contain[1]) {
				break;
			}
		}
		if (contain[0] == false) {
			this->points.push_back(*this->vec[i]->get_point(0));
		}
		if (contain[1] == false) {
			this->points.push_back(*this->vec[i]->get_point(1));
		}
		contain[0] = false;
		contain[1] = false;
	}
	return 0;
}

std::list <xy>* Vec_Spichka::get_points() {
	return &this->points;
}

xy Vec_Spichka::get_best_point() {
	return *this->best_point;
}
double Vec_Spichka::get_best_time() const {
	return this->best_time;
}

int Vec_Spichka::output() {
	this->best_point->output();
	std::cout << std::fixed << std::setprecision(2) << this->best_time;
	return 0;
}

Vec_Spichka::~Vec_Spichka() {
	int i = 0;
	for (i = (int)(this->vec.size() - 1); i >= 0; --i) {
		if (this->vec[i] != nullptr) {
			delete this->vec[i];
			this->vec[i] = nullptr;
		}
	}
	this->vec.clear();
	for (std::list<Spichka_on_fire*>::iterator it = this->list_of_fire.begin(); it != this->list_of_fire.end(); ++it) {
		delete* it;
	}
	this->list_of_fire.clear();
}