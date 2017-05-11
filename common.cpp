
// functions with the direction and index translation

int dir2idx(int x, int y) {
     if (x == 1 && y == 0) { return 0; }
     if (x == 0 && y == -1) { return 1; }
     if (x == -1 && y == 0) { return 2; }
     if (x == 0 && y == 1) { return 3; }
}

char idx2dirName(int idx) {
     if (idx == 0) { return 'E'; };
     if (idx == 1) { return 'S'; };
     if (idx == 2) { return 'W'; };
     if (idx == 3) { return 'N'; };
}

int dirName2idx(char s) {
     if ((s == 'E') || (s == 'e')) { return 0; };
     if ((s == 'S') || (s == 's')) { return 1; };
     if ((s == 'W') || (s == 'w')) { return 2; };
     if ((s == 'N') || (s == 'n')) { return 3; };
}

char dir2dirName(int x, int y) {
     return idx2dirName(dir2idx(x, y));}