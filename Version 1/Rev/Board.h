#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <filesystem>
#define SIZE 9

//const int GRID_SIZE = 9;

class Board {
private:
	bool nInRegion(int n, int i, int j);
	bool nInCol(int n, int j);

	std::vector<bool> getRegionPossibilities(int i, int j);
	std::vector<bool> getColPossibilites(int j);
	std::vector<bool> getRowPossibilities(int i);

	void setCellSolved(int i, int j, int n);
	int checkSolvedCells();
	void checkRegion(int i, int j);
	void copySol();

	int grid[SIZE][SIZE];
	int solution[SIZE][SIZE];
	std::vector<bool> possibles[SIZE][SIZE];

	int CELLS_TO_REMOVE = 50;
	int solution_changes;
public:
	Board();
	~Board() = default;

	bool isSolRight();
	void difficulty(int n);
	void generate();
	bool solve();
	void draw();
	void drawSolution();
	int getCellSolValue(int x, int y);
	int getCellValue(int x, int y);
	void fillCell(int x, int y, int z);
	void deleteCell(int x, int y);
	void setCell(int x, int y, int z);
	void setSolCell(int x, int y, int z);
};