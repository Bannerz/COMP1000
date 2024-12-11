#include <iostream>
using namespace std;


float calculateDistance(float x1, float y1, float x2, float y2) {
	
	float x = x1 - x2; //calculating number to square in next step
	float y = y1 - y2;
	float dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);

	cout << "Output: " << dist << endl;

	return dist;


}

int main() {


	float cx1;
	float cx2;
	float cy1;
	float cy2;

	cout << "Input co-ordinate x1: ";
	cin >> cx1;

	cout << "Input co-ordinate y1: ";
	cin >> cy1;

	cout << "Input co-ordinate x2: ";
	cin >> cx2;

	cout << "Input co-ordinate x2: ";
	cin >> cy2;

	calculateDistance(cx1, cy1, cx2, cy2);



	return 0;
}