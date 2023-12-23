#include "Chord.hpp"
#include <algorithm>
#include <string>

Chord::Chord(std::vector<std::vector<int>> frets, std::string name,
             std::pair<int, int> strum, int fret_start)
    : frets(frets), strum(strum), name(name) {

  std::string str = this->create_top() + "\n┌─┬─┬─┬─┬─┐" +
                    (fret_start ? std::to_string(fret_start) : "") + "\n";
  size_t len = this->frets.size() - 1;
  if (len < 1) {
    return;
  }

  for (size_t i = 0; i < len; i++) {
    str += this->create_fret(this->frets[i]) + "\n├─┼─┼─┼─┼─┤\n";
  }

  str += create_fret(this->frets[len]) + "\n└─┴─┴─┴─┴─┘" + name;
  this->chords_str = str;
}

std::string Chord::get_name() { return this->name; }
std::string Chord::get() { return this->chords_str; }

std::string Chord::create_fret(std::vector<int> &fret) {
  std::string fret_str = "";
  for (int i = 1; i <= 6; i++) {
    if (std::find(fret.begin(), fret.end(), i) != fret.end()) {
      fret_str += "● ";
    } else {
      fret_str += "│ ";
    }
  }

  return fret_str;
};

std::string Chord::create_top() {
  std::string top_str = "";
  std::vector<int> not_open = {};
  for (auto &fret : this->frets) {
    for (int &str_index : fret) {
      if (std::find(not_open.begin(), not_open.end(), str_index) ==
          not_open.end()) {
        not_open.push_back(str_index);
      }
    }
  }

  for (int x = 1; x <= 6; x++) {
    if (x < this->strum.first) {
      top_str += "X ";
    } else {
      if (std::find(not_open.begin(), not_open.end(), x) != not_open.end()) {
        top_str += "  ";
      } else {
        top_str += "◯ ";
      }
    }
  }

  return top_str;
}

Chord::~Chord() {}
