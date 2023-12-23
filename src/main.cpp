#include "Chord.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
  std::string help_msg =
      "Usage: chordshuffle -d [duration in milisecond] -c [chord name list]\n"
      "Available commands:\n"
      "\t-p print chords name\n"
      "\t-c input chord name to shuffle\n"
      "\t-d delay between chord output\n"
      "\t-n only print chord name\n"
      "Example:\n"
      "\tchordshuffle -c Am G -d 500 -> shuffle Am and G every 500 milisecond\n"
      "\tchordshuffle -d 500 -c C F -> shuffle C and F every 500 milisecond\n";

  std::vector<Chord> chordsShuffle = {};
  std::map<std::string, Chord *> chords;

  chords["C"] = new Chord({{5}, {3}, {2}}, "C", {2, 6});
  chords["G"] = new Chord({{}, {2}, {1, 5, 6}}, "G", {1, 6});
  chords["A"] = new Chord({{}, {3, 4, 5}}, "A", {2, 6});
  chords["E"] = new Chord({{3}, {2, 3}}, "E", {1, 6});
  chords["D"] = new Chord({{}, {4, 6}, {5}}, "D", {3, 6});
  chords["F"] = new Chord({{5}, {4}, {2, 3}}, "F", {2, 6});
  chords["Am"] = new Chord({{3}, {2, 3}}, "Am", {2, 6});
  chords["Dm"] = new Chord({{6}, {4}, {5}}, "Dm", {3, 6});
  chords["Em"] = new Chord({{}, {2, 3}}, "Em", {1, 6});

  int delay = -1;

  bool gather_chords = false;
  bool name_only = false;
  for (int x = 1; x < argc; x++) {
    std::string arg = std::string(argv[x]);
    if (arg == "-c") {
      gather_chords = true;
    } else if (arg == "-d") {
      gather_chords = false;
      x++;
      if (x < argc) {
        delay = atoi(argv[x]);
      }
    } else if (gather_chords) {
      if (chords.find(arg) != chords.end()) {
        chordsShuffle.push_back(*chords[arg]);
      } else {
        std::cout << "Unrecognized chord " << arg << "." << std::endl;
      }
    } else if (arg == "-p") {
      std::cout << "Avaliable chords: ";
      unsigned int iter = 0;
      int total = chords.size();
      for (auto &chord : chords) {
        std::cout << chord.second->get_name();
        if (iter < total - 1) {
          std::cout << ", ";
        }
        iter++;
      }
      std::cout << "." << std::endl;
      exit(EXIT_SUCCESS);
    } else if (arg == "-n") {
      name_only = true;
    } else if (arg == "--help") {
      std::cout << help_msg;
      exit(EXIT_SUCCESS);
    } else {
      std::cout << "Unrecognized command " << arg << "." << std::endl;
    }
  }

  if (delay < 0 || !chordsShuffle.size()) {
    std::cout << "Invalid usage please check --help.";
    exit(EXIT_FAILURE);
  }

  int totalshuffle = chordsShuffle.size();
  unsigned int idx_prev = rand() % totalshuffle;
  while (true) {

    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    // prevent repeating chords.
    int index = rand() % totalshuffle;
    if (index == idx_prev) {
      index = (index + 1) % totalshuffle;
    }
    idx_prev = index;
    std::cout << std::endl
              << (name_only ? chordsShuffle[index].get_name()
                            : chordsShuffle[index].get())
              << std::endl;
  }

  return 0;
}
