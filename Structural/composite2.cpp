// This acts as an interface for every Song (Leaf)
// and SongGroup (Composite) we create
#include <iostream>
#include <list>
#include <string>
#include <exception>

using namespace std;

//Component Interface
class SongComponent {
	public:
		virtual ~SongComponent();
		// When this is called by a class object that extends SongComponent it will
		// print out information specific to the Song or SongGroup
		virtual void displaySongInfo() = 0;
		virtual string getSongName() = 0;
		virtual string getBandName() = 0;
		virtual unsigned getReleaseYear() = 0;
};

//Composite
class SongGroup : public SongComponent {
	public:
		SongGroup(string& newGroupName, string& newGroupDescription)
			: groupName(newGroupName), groupDescription(newGroupDescription) {}
		string getGroupName() { return groupName; }
		string getGroupDescription() { return groupDescription; }
		void add(SongComponent& newSongComponent) { songComponents.push_front(newSongComponent); }
		void remove(SongComponent& newSongComponent) { songComponents.remove(newSongComponent); }
		void displaySongInfo() {
		// 	std::cout << getGroupName() + " " + getGroupDescription() + "\n";
		// 	// Cycles through and prints any Songs or SongGroups added
		// 	// to this SongGroups ArrayList songComponents
	    //     for (auto& song : songComponents){
	    //
	    //     }
	    //     Iterator songIterator = songComponents.iterator();
		// 	while(songIterator.hasNext()) {
		// 		SongComponent songInfo = (SongComponent) songIterator.next();
		// 		songInfo.displaySongInfo();
		// 	}
	    }
	private:
		// Contains any Songs or SongGroups that are added to this List
		list<SongComponent> songComponents;
		string groupName;
		string groupDescription;
};

//Leaf
// class Song : public SongComponent {
// 	public:
// 	    Song(string& newSongName, string& newBandName, unsigned& newReleaseYear) :
// 			songName(newSongName), bandName(newBandName), releaseYear(newReleaseYear) {}
// 		string getSongName() { return songName; }
// 		string getBandName() { return bandName; }
// 		unsigned getReleaseYear() { return releaseYear; }
// 		void displaySongInfo(){
// 			std::cout << getSongName() + " recorded by " << getBandName() << " in " << getReleaseYear();
// 		}
// 	private:
// 		string songName;
// 		string bandName;
// 		unsigned releaseYear;
// };


int main(){
	// SongComponent industrialMusic =
	// 		new SongGroup("Industrial",
	// 				"is a style of experimental music that draws on transgressive and provocative themes");
    //
	// SongComponent heavyMetalMusic =
	// 		new SongGroup("\nHeavy Metal",
	// 				"is a genre of rock that developed in the late 1960s, largely in the UK and in the US");
    //
	// SongComponent dubstepMusic =
	// 		new SongGroup("\nDubstep",
	// 				"is a genre of electronic dance music that originated in South London, England");
    //
	// // Top level component that holds everything
	// SongComponent everySong = new SongGroup("Song List", "Every Song Available");
    //
	// // Composite that holds individual groups of songs
	// // This holds Songs plus a SongGroup with Songs
	// everySong.add(industrialMusic);
    //
	// industrialMusic.add(new Song("Head Like a Hole", "NIN", 1990));
	// industrialMusic.add(new Song("Headhunter", "Front 242", 1988));
    //
	// industrialMusic.add(dubstepMusic);
    //
	// dubstepMusic.add(new Song("Centipede", "Knife Party", 2012));
	// dubstepMusic.add(new Song("Tetris", "Doctor P", 2011));
    //
	// // This is a SongGroup that just holds Songs
	// everySong.add(heavyMetalMusic);
    //
	// heavyMetalMusic.add(new Song("War Pigs", "Black Sabath", 1970));
	// heavyMetalMusic.add(new Song("Ace of Spades", "Motorhead", 1980));
    //
	// DiscJockey crazyLarry = new DiscJockey(everySong);
    //
	// crazyLarry.getSongList();

    return 0;
}
