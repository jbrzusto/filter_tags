#ifndef RUN_FINDER_HPP
#define RUN_FINDER_HPP

#include "filter_tags_common.hpp"

#include "Known_Tag.hpp"
#include "Freq_Setting.hpp"
#include "DFA_Graph.hpp"
#include "DFA_Node.hpp"
#include <unordered_map>
#include <list>

typedef std::unordered_map < Lotek_Tag_ID, DFA_Graph > Graph_Map;

// forward declaration for inclusion of Tag_Filter

class Run_Foray;
class Run_Finder;
class Run_Candidate;
#include "Run_Candidate.hpp"

// Set of running DFAs representing possible tags burst sequences
typedef std::list < Run_Candidate > Cand_List;

// Map from Lotek ID to vectors of lists of Run_Candidates
typedef std::unordered_map < Lotek_Tag_ID, std::vector < Cand_List >  > Cand_List_Map;

class Run_Finder {

  /*
    Find runs of tag detections from all antennas on a single nominal
    frequency.  Each run contains only bursts from a single physical
    tag, but there can be simultaneous runs of different tags.
  */

public:
  static const int NUM_CAND_LISTS = 3; // 0 = confirmed, 1 = unconfirmed, 2 = clones

  Run_Foray * owner;

  std::unordered_set < Lotek_Tag_ID > tags_not_in_db;

  // - internal representation of tag database
  // the set of tags at a single nominal frequency and with the same Lotek ID is a "Tag_Set"

  Nominal_Frequency_kHz nom_freq;

  Graph_Map G;  // a DFA graph for each lotek tag ID at this frequency

  Cand_List_Map cands; // for each Lotek ID, a list of run candidates; within each list, confirmed
  // candidates precede unconfirmed candidates; within confirmed candidates, order is from earliest
  // to latest confirmed

  // algorithmic parameters

  Gap burst_slop;	// (seconds) allowed slop in timing between
                        // consecutive tag bursts, in seconds this is
                        // meant to allow for measurement error at tag
                        // registration and detection times

  static Gap default_burst_slop;


  Gap burst_slop_expansion; // (seconds) how much slop in timing
			    // between tag bursts increases with each
  // skipped pulse; this is meant to allow for clock drift between
  // the tag and the receiver.
  static Gap default_burst_slop_expansion;

  // how many consecutive bursts can be missing without terminating a
  // run?

  unsigned int max_skipped_bursts;
  static unsigned int default_max_skipped_bursts;

  // by how many integer seconds can the clock jump (up or down)?
  // .DTA files show evidence of +/-1 s jumps, presumably due
  // to something like the integer portion of the clock being
  // set directly to a GPS timestamp, while leaving the fractional
  // part as-is.  Of course, it could be happening somewhere in
  // the software that generates .DTA files...

  static unsigned int timestamp_wonkiness;

  // output parameters

  static ostream * out_stream;

  string prefix;   // prefix before each tag record (e.g. port number then comma)

  Run_Finder(Run_Foray * owner);

  Run_Finder(Run_Foray * owner, Nominal_Frequency_kHz nom_freq, string prefix="");

  void add_tag(Known_Tag * t); // add a known tag to this run finder; it will be on the same
                               // frequency as the run finder

  void setup_graphs(); // after all known tags for this frequency have been added, this creates
  // the corresponding DFA graphs

  static void set_default_burst_slop_ms(float burst_slop_ms);

  static void set_default_burst_slop_expansion_ms(float burst_slop_expansion_ms);

  static void set_default_max_skipped_bursts(unsigned int skip);

  static void set_out_stream(ostream *os);

  static void set_timestamp_wonkiness(unsigned int wonk);

  void init();

  virtual void process (Hit &h);

  virtual void end_processing();

};


#endif // RUN_FINDER_HPP
