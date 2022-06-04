#pragma once
#include "Header.h"

#define SIZE 9

class Board {
private:
	bool nInRegion(int, int, int);
	bool nInCol(int, int);

	std::vector<bool> getRegionPossibilities(int, int);
	std::vector<bool> getColPossibilites(int);
	std::vector<bool> getRowPossibilities(int);

	void setCellSolved(int, int, int);
	int checkSolvedCells();
	void checkRegion(int, int);
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
	void difficulty(int);
	void generate();
	bool solve();
	void draw();
	void drawSolution();
	int getCellSolValue(int, int);
	int getCellValue(int, int);
	void fillCell(int, int, int);
	void deleteCell(int, int);
	void setCell(int, int, int);
	void setSolCell(int, int, int);
};