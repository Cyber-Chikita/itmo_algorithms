#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Round.h"

using namespace std;
using json = nlohmann::json;

#pragma once
class Game
{
private:

	vector<Round> rounds_;

	Game() {
		rounds_ = vector<Round>();
	};

	Game(vector<Round> rounds) {
		rounds_ = rounds;
	};


	void next_round(Round round) {
		if (rounds_.size() == 10)
		{
			check_out_results();
		}
		else
		{
			Round n_round = Round(rounds_.size(), round.get_town_area(), round.get_people_amount(), round.get_wheat_amount(), round.get_town_area_for_wheat(), round.get_wheat_as_food_amount());
			if (!n_round.get_is_loose()) {
				do_round(n_round);
			}
			else {
				cout << "Вы проиграли" << endl;
			}
		}
	}

	void next_round() {
		Round first_round = Round::first_round();
		do_round(first_round);
	}

	void do_round(Round& round) {

		cout << round.create_round_info();

		if (!round.is_finised()) {
			cout << "-------------------------" << endl;
			if (!round.is_town_area_buy_completed()) {
				string text = "Введите кол-во акров для покупки. Стоймость одного акра:"
					+ to_string(round.get_town_area_price()) + "\nТекущее кол-во пшеницы - "
					+ to_string(round.get_wheat_amount()) + "\nТекущий размер города - "
					+ to_string(round.get_town_area());
				int value = read_and_check_value(text, round, [](int x, Round r) { return r.validate_value_for_town_area_buy(x); });
				round.set_town_area_buy(value);
			}
			if (!round.is_town_area_sell_completed() && round.get_town_area_buy() == 0) {
				string text = "Введите кол-во акров для продажи. Стоймость одного акра:"
					+ to_string(round.get_town_area_price())
					+ "\nТекущий размер города - " + to_string(round.get_town_area());
				int value = read_and_check_value(text, round, [](int x, Round r) { return r.validate_value_for_town_area_sell(x); });
				round.set_town_area_sell(value);
			}
			if (!round.is_wheat_as_food_amount_completed()) {
				string text = "Введите кол-во пшеницы для пропитания. Текущее кол-во пшеницы - "
					+ to_string(round.get_wheat_amount());
				int value = read_and_check_value(text, round, [](int x, Round r) { return r.validate_wheat_as_food_amount(x); });
				round.set_wheat_as_food_amount(value);
			}
			if (!round.is_town_area_for_wheat_completed()) {
				string text = "Введите кол-во акров для засева.\nТекущее кол-во пшеницы - "
					+ to_string(round.get_wheat_amount())
					+ "\nТекущий размер города - " + to_string(round.get_town_area());
				int value = read_and_check_value(text, round, [](int x, Round r) { return r.validate_wheat_as_food_amount(x); });
				round.set_town_area_for_wheat(value);
			}
			rounds_.push_back(round);
			save();
			next_round(round);
		}
		else {
			next_round(round);
		}
	}

	void check_out_results() {
		double starve_deth_round_percent = 0;
		int round_count = 0;
		for (int i = 1; i < rounds_.size(); i++)
		{
			starve_deth_round_percent += (double)rounds_[i].get_starve_dead_people() / rounds_[i].get_people_amount();
		}
		double town_area_per_people = (double)rounds_[rounds_.size() - 1].get_people_amount() / rounds_[rounds_.size() - 1].get_town_area();
		double starve_deth_percent = starve_deth_round_percent / round_count;
		cout << "Игра закончена\nВы справились " << endl;
		if (starve_deth_percent > 0.33 || town_area_per_people < 7) {
			cout << "ПЛОХО" << endl;
		}
		else if (starve_deth_percent > 0.1 || town_area_per_people < 9) {
			cout << "НОРМАЛЬНО" << endl;
		}
		else if (starve_deth_percent > 0.03 || town_area_per_people < 10) {
			cout << "ХОРОШО" << endl;
		}
		else {
			cout << "ОТЛИЧНО" << endl;
		}
	}

	template <typename IsValidFunction>
	int read_and_check_value(string text, Round round, IsValidFunction check_is_valid) {
		cout << text << endl;
		int value;
		cin >> value;
		while (!check_is_valid(value, round))
		{
			cin >> value;
		}
		return value;
	}

	void save() {
		ofstream savefile;
		savefile.open("./save.json");
		savefile << to_json();
		savefile.close();
	}

	json to_json() {
		json::array_t rounds_data = json::array_t();

		for (int i = 0; i < rounds_.size(); i++)
		{
			rounds_data.push_back(rounds_[i].to_json());
		}

		json data = json();

		data["rounds"] = rounds_data;

		return rounds_data;
	}

	static Game from_json(json::array_t data) {
		vector<Round> rounds = vector<Round>();

		for (int i = 0; i < data.size(); i++)
		{
			rounds.push_back(Round(data[i]));
		}

		return Game(rounds);
	}
public:
	static Game create_new_game() {
		return Game();
	}

	static Game load_from_file() {
		ifstream savefile("./save.json");
		json data = json::parse(savefile);
		savefile.close();
		return from_json(data);
	}

	void start() {
		if (rounds_.size() == 0)
			next_round();
		else
		{
			for (int i = 0; i < rounds_.size() - 1; i++)
			{
				cout << "-------------------------------------";
				cout << rounds_[i].create_round_info() << endl;
			}
			do_round(rounds_[rounds_.size() - 1]);
		}
	}




};

