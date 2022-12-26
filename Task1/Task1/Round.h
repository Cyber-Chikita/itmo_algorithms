#pragma once
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


const string INDEX_LABEL = "index";
const string STARVE_DEAD_PEOPLE_LABEL = "starve_dead_people";
const string PLAGUE_DEAD_PEOPLE_LABEL = "plague_dead_people";
const string INCOMING_PEOPLE_LABEL = "incoming_people";
const string IS_LOOSE_LABEL = "is_loose";
const string WHEAT_COLLECTED_LABEL = "wheat_collected";
const string WHEAT_LOST_LABEL = "wheat_lost";
const string TOWN_AREA_PRICE_LABEL = "town_area_price";
const string TOWN_AREA_BUY_LABEL = "town_area_buy";
const string TOWN_AREA_SELL_LABEL = "town_area_sell";
const string WHEAT_AS_FOOD_AMOUNT_LABEL = "wheat_as_food_amount_";
const string TOWN_AREA_FOR_WHEAT_LABEL = "town_area_for_wheat_";
const string TOWN_AREA_LABEL = "town_area";
const string PEOPLE_AMOUNT_LABEL = "people_amount";
const string WHEAT_AMOUNT_LABEL = "wheat_amount";

class Round
{
private:

	int index_;
	int starve_dead_people_;
	int plague_dead_people_;
	int incoming_people_;
	bool is_loose_;
	int wheat_collected_;
	int wheat_lost_;
	int town_area_price_;
	int town_area_buy_;
	int town_area_sell_;
	int wheat_as_food_amount_;
	int town_area_for_wheat_;
	int town_area_;
	int people_amount_;
	int wheat_amount_;

	Round() {
		index_ = 1;
		starve_dead_people_ = 0;
		plague_dead_people_ = 0;
		incoming_people_ = 0;
		is_loose_ = false;
		wheat_collected_ = 0;
		wheat_lost_ = 0;
		town_area_price_ = rand() % 9 + 17;
		town_area_buy_ = -1;
		town_area_sell_ = -1;
		wheat_as_food_amount_ = -1;
		town_area_for_wheat_ = -1;
		town_area_ = 1000;
		wheat_amount_ = 2800;
		people_amount_ = 100;
	}
public:
	Round(int index, int town_area, int people_amount, int wheat_amount, int town_area_for_wheat, int wheat_amount_for_food) {
		index_ = index;

		if (people_amount * 10 < town_area_for_wheat) {
			town_area_for_wheat -= town_area_for_wheat - people_amount * 10;
		}

		int wheat_from_one = rand() % 6 + 1;

		wheat_collected_ = town_area_for_wheat * wheat_from_one;

		wheat_amount += wheat_collected_;

		wheat_lost_ = wheat_amount == 0 ? 0 : wheat_amount - rand() % wheat_amount * 0.07;

		wheat_amount -= wheat_lost_;

		starve_dead_people_ = people_amount - wheat_amount_for_food / 20;

		is_loose_ = ((double)starve_dead_people_ / people_amount) > 0.45;

		incoming_people_ = starve_dead_people_ / 2 + (5 - wheat_from_one) * wheat_amount / 600 + 50;

		incoming_people_ = std::min(50, incoming_people_);
		incoming_people_ = std::max(0, incoming_people_);

		if (rand() % 101 < 15) {
			plague_dead_people_ = floor(people_amount / 2.0);
		}
		else {
			plague_dead_people_ = 0;
		}

		town_area_price_ = rand() % 9 + 17;

		town_area_buy_ = -1;
		town_area_sell_ = -1;
		wheat_as_food_amount_ = -1;
		town_area_for_wheat_ = -1;

		wheat_amount_ = wheat_amount;
		people_amount_ = people_amount - starve_dead_people_ + incoming_people_ - plague_dead_people_;
		town_area_ = town_area;
	};

	static Round first_round() {
		return Round();
	}

	Round(json data) {
		index_ = data[INDEX_LABEL].get<int>();
		cout << "DEBUG!!!!!!!!!!!!! " << data[INDEX_LABEL].get<int>() << endl;
		starve_dead_people_ = data[STARVE_DEAD_PEOPLE_LABEL].get<int>();
		plague_dead_people_ = data[PLAGUE_DEAD_PEOPLE_LABEL].get<int>();
		incoming_people_ = data[INCOMING_PEOPLE_LABEL].get<int>();
		is_loose_ = data[IS_LOOSE_LABEL].get<bool>();
		wheat_collected_ = data[WHEAT_COLLECTED_LABEL].get<int>();
		wheat_lost_ = data[WHEAT_LOST_LABEL].get<int>();
		town_area_price_ = data[TOWN_AREA_PRICE_LABEL].get<int>();
		town_area_buy_ = data[TOWN_AREA_BUY_LABEL].get<int>();
		town_area_sell_ = data[TOWN_AREA_SELL_LABEL].get<int>();
		wheat_as_food_amount_ = data[WHEAT_AS_FOOD_AMOUNT_LABEL].get<int>();
		town_area_for_wheat_ = data[TOWN_AREA_FOR_WHEAT_LABEL].get<int>();
		town_area_ = data[TOWN_AREA_BUY_LABEL].get<int>();
		wheat_amount_ = data[WHEAT_AMOUNT_LABEL].get<int>();
		people_amount_ = data[PEOPLE_AMOUNT_LABEL].get<int>();
	}

	json to_json() {
		json data = json();

		data[INDEX_LABEL] = index_;
		data[STARVE_DEAD_PEOPLE_LABEL] = starve_dead_people_;
		data[PLAGUE_DEAD_PEOPLE_LABEL] = plague_dead_people_;
		data[INCOMING_PEOPLE_LABEL] = incoming_people_;
		data[IS_LOOSE_LABEL] = is_loose_;
		data[WHEAT_COLLECTED_LABEL] = wheat_collected_;
		data[WHEAT_LOST_LABEL] = wheat_lost_;
		data[TOWN_AREA_PRICE_LABEL] = town_area_price_;
		data[TOWN_AREA_BUY_LABEL] = town_area_buy_;
		data[TOWN_AREA_SELL_LABEL] = town_area_sell_;
		data[WHEAT_AS_FOOD_AMOUNT_LABEL] = wheat_as_food_amount_;
		data[TOWN_AREA_FOR_WHEAT_LABEL] = town_area_for_wheat_;
		data[TOWN_AREA_BUY_LABEL] = town_area_;
		data[WHEAT_AMOUNT_LABEL] = wheat_amount_;
		data[PEOPLE_AMOUNT_LABEL] = people_amount_;

		return data;
	}

	bool get_index() {
		return index_;
	}

	bool get_starve_dead_people() {
		return starve_dead_people_;
	}

	bool get_plague_dead_people() {
		return plague_dead_people_;
	}

	bool get_incoming_people() {
		return incoming_people_;
	}

	bool get_is_loose() {
		return is_loose_;
	}

	int get_wheat_collected() {
		return wheat_collected_;
	}

	int get_wheat_lost() {
		return wheat_lost_;
	}

	int get_town_area_price() {
		return town_area_price_;
	}

	int get_town_area_buy() {
		return town_area_buy_;
	}

	int get_town_area_sell() {
		return town_area_sell_;
	}

	int get_wheat_as_food_amount() {
		return wheat_as_food_amount_;
	}

	int get_town_area_for_wheat() {
		return town_area_for_wheat_;
	}

	int get_town_area() {
		return town_area_;
	}

	int get_wheat_amount() {
		return wheat_amount_;
	}

	int get_people_amount() {
		return people_amount_;
	}

	bool is_town_area_buy_completed() {
		return town_area_buy_ >= 0;
	}

	bool is_town_area_sell_completed() {
		return  town_area_sell_ >= 0;
	}

	bool is_wheat_as_food_amount_completed() {
		return wheat_as_food_amount_ >= 0;
	}

	bool is_town_area_for_wheat_completed() {
		return town_area_for_wheat_ >= 0;
	}

	bool validate_value_for_town_area_buy(int value) {
		if (value * town_area_price_ > wheat_amount_) {
			cout << "Недостаточно пшеницы, текущее кол-во пшеницы - " + to_string(wheat_amount_) << endl;
			return false;
		}
		else return true;
	}

	bool validate_value_for_town_area_sell(int value) {
		if (value > town_area_) {
			cout << "Мы не можем столько продать, текущий размер города - " + to_string(town_area_) << endl;
			return false;
		}
		else return true;
	}

	bool validate_wheat_as_food_amount(int value) {
		if (value > wheat_amount_) {
			cout << "Недостаточно пшеницы, текущее кол-во пшеницы - " + to_string(wheat_amount_) << endl;
			return false;
		}
		else return true;
	}

	bool validate_town_area_for_wheat(int value) {
		if (value > town_area_) {
			cout << "Мы не можем столько засеять, текущий размер города - " + to_string(town_area_) << endl;
			return false;
		}
		else if (value * 0.5 > wheat_amount_) {
			cout << "Мы не можем столько засеять, текущее кол-во пшеницы - " + to_string(wheat_amount_) << endl;
			return false;
		}
		else return true;
	}

	void set_town_area_buy(int amount) {
		town_area_buy_ = amount;
		town_area_ + amount;
		wheat_amount_ -= amount * town_area_price_;
	}

	void set_town_area_sell(int amount) {
		town_area_sell_ = amount;
		town_area_ - amount;
		wheat_amount_ += amount * town_area_price_;

	}

	void set_wheat_as_food_amount(int amount) {
		wheat_as_food_amount_ = amount;
		wheat_amount_ -= wheat_as_food_amount_;
	}

	void set_town_area_for_wheat(int amount) {
		town_area_for_wheat_ = amount;
		wheat_amount_ -= ceil(amount * 0.5);
	}

	bool is_finised() {
		return (is_town_area_buy_completed() || is_town_area_sell_completed()) && is_wheat_as_food_amount_completed() && is_town_area_for_wheat_completed();
	}

	string create_round_info() {
		string info = "";

		info += "Год " + to_string(index_) + "\n";
		info += "Размер города " + to_string(town_area_) + " акров\n";
		info += "Число пшеницы " + to_string(wheat_amount_) + " б.\n";
		info += "Численность " + to_string(people_amount_) + " человек\n";
		if (starve_dead_people_ > 0)
			info += "Умерло " + to_string(starve_dead_people_) + " от голода\n";
		if (plague_dead_people_ > 0)
			info += "Чума унесла " + to_string(plague_dead_people_) + " жизней ваших достопочтенных граждан\n";
		if (incoming_people_ > 0)
			info += "В ваш город прибыло " + to_string(incoming_people_) + " граждан\n";
		if (wheat_collected_ > 0)
			info += "Было собрано " + to_string(wheat_collected_) + " пшеницы\n";
		if (wheat_lost_ > 0)
			info += "Крысы съели " + to_string(wheat_lost_) + " пшеницы\n";
		if (town_area_price_ > 0)
			info += "В этом году земля стоит " + to_string(town_area_price_) + " пшеницы\n";
		if (town_area_buy_ > 0)
			info += "Вы купили " + to_string(town_area_buy_) + " акров\n";
		if (town_area_sell_ > 0)
			info += "Вы продали " + to_string(town_area_sell_) + " акров\n";
		if (wheat_as_food_amount_ > 0)
			info += "Вы решили оставить " + to_string(wheat_as_food_amount_) + " пшеницы для пропитания\n";
		if (town_area_for_wheat_ > 0)
			info += "Ваши поданные засеяли " + to_string(town_area_for_wheat_) + " акров\n";

		return info;
	}

};