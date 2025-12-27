#include <stdio.h>
void bestFit(int blockSize[], int m, int processSize[], int n) {
int allocation[n];
for (int i = 0; i < n; i++) {
allocation[i] = -1; // Initialize allocation array to -1 (unallocated)
}
for (int i = 0; i < n; i++) {
int bestFitIndex = -1;
for (int j = 0; j < m; j++) {
if (blockSize[j] >= processSize[i]) {
if (bestFitIndex == -1 || blockSize[j] < blockSize[bestFitIndex]) {
bestFitIndex = j;
}
}
}
if (bestFitIndex != -1) {
allocation[i] = bestFitIndex; // Allocate the block to the process
blockSize[bestFitIndex] -= processSize[i];
}
}
printf("Best Fit Allocation:\n");
for (int i = 0; i < n; i++) {
printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
}
}
int main() {
int blockSize[] = {100, 500, 200, 300, 600};
int processSize[] = {212, 417, 112, 426};
int m = sizeof(blockSize) / sizeof(blockSize[0]);
int n = sizeof(processSize) / sizeof(processSize[0]);
bestFit(blockSize, m, processSize, n);
return 0;
}
