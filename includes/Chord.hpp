#pragma once
#include <string>
#include <utility>
#include <vector>

class Chord {
public:
  Chord(std::vector<std::vector<int>> frets, std::string name,
        std::pair<int, int> strum = {0, 6}, int fret_start = 0);
  ~Chord();
  std::string get();
  std::string get_name();

private:
  std::pair<int, int> strum;
  std::vector<std::vector<int>> frets;
  std::vector<int> not_open;
  std::string chords_str = "Invalid key.";
  std::string name = "";

  std::string create_fret(std::vector<int> &key);
  std::string create_top();
};

struct test {};
