#include "Board.h"

typedef std::mt19937 RandGenerator;
RandGenerator rng;

Board::Board() {
	// Clear grid memory
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j) {
			grid[i][j] = 0;
			solution[i][j] = 0;
		}
	// Populate random number generator seed
	rng.seed(time(nullptr));
}

void Board::difficulty(int n)
{
	CELLS_TO_REMOVE = n;
}

void Board::fillCell(int x, int y, int z)
{
	grid[x][y] = z;
}

void Board::deleteCell(int x, int y)
{
	if (grid[x][y] != 0)
	{
		grid[x][y] = 0;
	}
	else {
		std::cout << std::endl << "Cell is already empty!" << std::endl;
	}
}

int Board::getCellValue(int x, int y)
{
	return grid[x][y];
}

int Board::getCellSolValue(int x, int y)
{
	return solution[x][y];
}

bool Board::nInRegion(int n, int i, int j) {
	// translate region coords to center position in grid
	int center[2] = { i * 3 + 1, j * 3 + 1 };
	// iterate over region to check if n exists in it
	for (int x = center[0] - 1; x <= center[0] + 1; ++x) {
		for (int y = center[1] - 1; y <= center[1] + 1; ++y) {
			if (solution[x][y] == 0) return false;
			if (n == solution[x][y]) return true;
		}
	}
	return false;
}

bool Board::nInCol(int n, int j) {
	// iterate over the col to check if n exists in it
	for (int i = 0; i < SIZE; ++i) {
		if (solution[i][j] == 0) break;
		if (solution[i][j] == n) return true;
	}
	return false;
}

std::vector<bool> Board::getRegionPossibilities(int i, int j) {
	std::vector<bool> output(9, true);
	// translate region coords to center position in grid
	int center[2] = { i * 3 + 1, j * 3 + 1 };
	// iterate over region to check if n exists in it
	for (int x = center[0] - 1; x <= center[0] + 1; ++x) {
		for (int y = center[1] - 1; y <= center[1] + 1; ++y) {
			if (this->grid[x][y] != 0)
				output[this->grid[x][y] - 1] = false;
		}
	}
	return output;
}

std::vector<bool> Board::getColPossibilites(int j) {
	std::vector<bool> output(9, true);
	for (int i = 0; i < SIZE; ++i) {
		if (this->grid[i][j] != 0)
			output[this->grid[i][j] - 1] = false;
	}
	return output;
}

std::vector<bool> Board::getRowPossibilities(int i) {
	std::vector<bool> output(9, true);
	for (int j = 0; j < SIZE; ++j) {
		if (this->grid[i][j] != 0)
			output[this->grid[i][j] - 1] = false;
	}
	return output;
}

int possiblesCount(std::vector<bool> possibles) {
	int count = 0;
	for (int i = 0; i < possibles.size(); ++i) {
		if (possibles[i]) ++count;
	}
	return count;
}

void Board::generate() {
	std::vector<bool> oneToNine(9, true);

	// Generate grid
	for (int i = 0; i < SIZE; ++i) {
		// Generate horizontal possibles
		std::vector<bool> h_possibles = oneToNine;

		int j = 0;
		while (j < SIZE) {
			// If not initialized yet store the possibles of the row in that pos
			if (this->possibles[i][j].size() == 0) {
				this->possibles[i][j] = h_possibles;
			}

			// Check if we are out of possible numbers
			if (possiblesCount(this->possibles[i][j]) == 0) {
				// Replenish this square numbers
				this->possibles[i][j].resize(0);

				--j; // Go back 1 cell
				// Remove the chosen one from the possibles
				this->possibles[i][j][solution[i][j] - 1] = false;
				h_possibles[solution[i][j] - 1] = true;
				solution[i][j] = 0;
			}
			else {
				// Get a number randomly from the available numbers
				std::uniform_int_distribution<uint32_t> tempGenerator(0, possiblesCount(this->possibles[i][j]) - 1);
				int n = tempGenerator(rng) + 1;
				int choosen = 0;
				while (true) { // Choose from the possible ones the n-one
					if (this->possibles[i][j][choosen]) --n;
					if (n == 0) break;
					++choosen;
				}

				// Check if it conflicts
				if (nInRegion(choosen + 1, i / 3, j / 3) || nInCol(choosen + 1, j)) {
					// Remove from available numbers for this square
					this->possibles[i][j][choosen] = false;
				}
				else {
					// Use it and continue
					solution[i][j] = choosen + 1;
					h_possibles[choosen] = false;
					++j;
				}
			}
		}
	}

	// remove from grid according to the only-one-solution rule
	copySol();
}

// Solving

// n is 0-based
void Board::setCellSolved(int i, int j, int n) {
	int center[2] = { (i / 3) * 3 + 1, (j / 3) * 3 + 1 };
	// iterate over region to remove n from possibles
	for (int x = center[0] - 1; x <= center[0] + 1; ++x) {
		for (int y = center[1] - 1; y <= center[1] + 1; ++y) {
			this->possibles[x][y][n] = false;
		}
	}

	// Vertical and horizontal removal
	for (int x = 0; x < SIZE; ++x) {
		this->possibles[x][j][n] = false;
		this->possibles[i][x][n] = false;
	}

	this->solution_changes++;
	this->grid[i][j] = n + 1;
}

int Board::checkSolvedCells() {
	int solved = 0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (this->grid[i][j] == 0 &&
				possiblesCount(this->possibles[i][j]) == 1) {
				// Get the only possible one
				for (int x = 0; x < 9; ++x) {
					if (this->possibles[i][j][x]) {
						solved++;
						setCellSolved(i, j, x);
						break;
					}
				}
			}
		}
	}
	return solved;
}

// Last Remaining Cell in a Box
void Board::checkRegion(int i, int j) {
	// Get region center coords
	int center[2] = { (i / 3) * 3 + 1, (j / 3) * 3 + 1 };

	// Check for repeated in region
	int times[SIZE] = { 0 };
	for (int x = center[0] - 1; x <= center[0] + 1; ++x)
		for (int y = center[1] - 1; y <= center[1] + 1; ++y)
			if (x != i && y != j) {
				// When cell is different Count the possibles
				for (int n = 0; n < 9; ++n) {
					if (this->possibles[x][y][n]) times[n]++;
				}
			}
	for (int n = 0; n < SIZE; ++n) {
		if (times[n] == 1) {
			// Only one possible n in region
			setCellSolved(i, j, n);
		}
	}

	// Check for repeated in row and col
	std::fill_n(times, SIZE, 0); // reset times array
	int times_col[SIZE] = { 0 };
	for (int x = 0; x < SIZE; ++x) {
		for (int n = 0; n < 9; ++n) {
			// Count the possibles of the row
			if (this->possibles[i][x][n]) times[n]++;
			// Count the possibles of the col
			if (this->possibles[x][j][n]) times_col[n]++;
		}
	}
	for (int n = 0; n < SIZE; ++n) {
		if (times[n] == 1) {
			// Only one possible n in row
			setCellSolved(i, j, n);
		}
		else if (times_col[n] == 1) {
			// Only one possible n in col
			setCellSolved(i, j, n);
		}
	}
}

bool Board::solve() {
	this->solution_changes = 0;
	// clear memory from possibles array
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			this->possibles[i][j] = std::vector<bool>(9, false);
		}
	}

	while (true) {
		int lastChanges = this->solution_changes;
		// Get absolute vertical possibilities
		std::vector<bool> v_possibles[SIZE];
		std::vector<bool> h_possibles[SIZE];
		for (int j = 0; j < SIZE; ++j) {
			v_possibles[j] = getColPossibilites(j);
		}

		// Calculate all possibles of each cell
		for (int i = 0; i < SIZE; ++i) {
			h_possibles[i] = getRowPossibilities(i);
			for (int j = 0; j < SIZE; ++j) {
				std::vector<bool> q_possibles = getRegionPossibilities(i / 3, j / 3);
				for (int n = 0; n < 9; ++n) {
					this->possibles[i][j][n] = (h_possibles[i][n] &&
						v_possibles[j][n] &&
						q_possibles[n]);
				}
			}
		}

		// Check for solved cells
		if (checkSolvedCells() == 0) {
			for (int i = 0; i < SIZE; ++i) {
				for (int j = 0; j < SIZE; ++j) {
					if (this->grid[i][j] != 0) continue;
					checkRegion(i, j);
				}
			}
		}

		// Avoid infinite loops
		if (lastChanges == this->solution_changes) break;
	}

	return isSolRight();
}

void Board::copySol() {
	// Save the removed cells coordinates
	// int x_removed[CELLS_TO_REMOVE];
	// int y_removed[CELLS_TO_REMOVE];

	int* x_removed = new int[CELLS_TO_REMOVE];
	int* y_removed = new int[CELLS_TO_REMOVE];

	while (true) { // while more than one solution
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				this->grid[i][j] = this->solution[i][j];
			}
		}
		std::uniform_int_distribution<uint32_t> tempGenerator(0, 8);
		for (int i = 0; i < CELLS_TO_REMOVE; ++i) {
			x_removed[i] = tempGenerator(rng);
			y_removed[i] = tempGenerator(rng);
			// Avoid repeated cells
			while (this->grid[x_removed[i]][y_removed[i]] == 0) {
				x_removed[i] = tempGenerator(rng);
				y_removed[i] = tempGenerator(rng);
			}
			this->grid[x_removed[i]][y_removed[i]] = 0;
		}
		if (this->solve()) break; // End loop when found only one solution Board
	}

	for (int i = 0; i < CELLS_TO_REMOVE; ++i) {
		this->grid[x_removed[i]][y_removed[i]] = 0;
	}
}

bool Board::isSolRight() {
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (this->grid[i][j] != this->solution[i][j]) {
				return false;
			}
		}
	}
	return true;
}

// Printing the Board board
void draw_separator() {
	std::cout << "+-------+-------+-------+" << std::endl;
}

char draw_cell_content(const int n) {
	// if cell holds a 0 , draw a ' ' instead
	if (n == 0) return ' ';
	else return n + '0';
}

void drawBoard(int grid[][SIZE]) {
	for (int i = 0; i < SIZE; ++i) {
		if (i % 3 == 0) draw_separator();
		for (int j = 0; j < SIZE; ++j) {
			// draw col separator
			if (j % 3 == 0) std::cout << (!j ? "" : " ") << "|";
			std::cout << " " << draw_cell_content(grid[i][j]);
		}
		std::cout << " |" << std::endl;
	}
	draw_separator();
}

void Board::draw() {
	drawBoard(this->grid);
}

void Board::drawSolution() {
	drawBoard(this->solution);
}

void Board::setCell(int x, int y, int z) {
	grid[x][y] = z;
}

void Board::setSolCell(int x, int y, int z)
{
	solution[x][y] = z;
}