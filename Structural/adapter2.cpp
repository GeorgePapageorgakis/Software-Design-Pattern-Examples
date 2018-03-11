#include <iostream>
#include <ctime>
#include <cstdlib>

// Target Interface : This is what the client expects to work with.
// It is the adapters job to make new classes compatible with this one.
class EnemyAttacker {
	public:
		virtual void fireWeapon() = 0;
		virtual void driveForward() = 0;
		virtual void assignDriver(std::string driverName) = 0;
};

// We have to make classes with different methods work with the EnemyAttacker interface
class EnemyTank : public EnemyAttacker{
	public:
		void fireWeapon() override {
			int attackDamage = rand() % 10 + 1;
			std::cout << "Enemy Tank Does " << attackDamage << " Damage\n";
		}
		void driveForward() override {
			int movement = rand() % 5 + 1;
			std::cout << "Enemy Tank moves " << movement << " squares\n";
		}
		void assignDriver(std::string driverName) override {
			std::cout << driverName + " is driving the tank\n";
		}
};
// This is the Adaptee. The Adapter redirects method calls to objects that use
// the EnemyAttacker interface to the equivalent methods defined in EnemyRobot
class EnemyRobot{
	public:
		void meleeSmash() {
			int attackDamage = rand() % 20 + 1;
			std::cout << "Enemy Robot Causes " << attackDamage << " Damage Melee hit\n";
		}
		void walkForward() {
			int movement = rand() % 5 + 1;
			std::cout << "Enemy Robot Walks Forward " << movement << " squares\n";
		}
 		void reactToHuman(std::string driverName) {
			std::cout << "Enemy Robot Fixates on " << driverName << "\n";
		}
};
// The Adapter must provide an alternative action for the the methods that need
// to be used because EnemyAttacker was implemented.
// This adapter does this by containing an object of the same type as the Adaptee
// (EnemyRobot). All calls to EnemyAttacker methods are sent instead to methods
// used by EnemyRobot
class EnemyRobotAdapter : public EnemyAttacker{
	private:
		EnemyRobot theRobot;
	public:
		EnemyRobotAdapter(EnemyRobot newRobot) { theRobot = newRobot; }
		void fireWeapon() {	theRobot.meleeSmash(); }
		void driveForward() { theRobot.walkForward(); }
		void assignDriver(std::string driverName) { theRobot.reactToHuman(driverName); }
};

int main(){
	srand(time(0));

	EnemyTank T80Tank;
	EnemyRobot RoboCop;
	EnemyAttacker* robotAdapter = new EnemyRobotAdapter(RoboCop);

	std::cout << "RoboCop:" << std::endl;
	RoboCop.reactToHuman("Alex");
	RoboCop.walkForward();
	RoboCop.meleeSmash();
	std::cout << std::endl;

	std::cout << "The Enemy Tank:" << std::endl;
	T80Tank.assignDriver("Kim Jong-un");
	T80Tank.driveForward();
	T80Tank.fireWeapon();
	std::cout << std::endl;

	std::cout << "The Robot with Adapter" << std::endl;
	robotAdapter->assignDriver("C-3PO");
	robotAdapter->driveForward();
	robotAdapter->fireWeapon();

	return EXIT_SUCCESS;
}
