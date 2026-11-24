
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> locations;
vector<int> u, v, w;

void addLocation(){
    string name;
    cout << "Enter location name: ";
    cin >> name;
    locations.push_back(name);
    cout << "Location added successfully!\n";
}

void addConnection(){
    if (locations.size() < 2){
        cout << "Add at least two locations first!\n";
        return;
    }
    int a, b, cost;
    cout << "\nAvailable Locations:\n";
    for (int i = 0; i < locations.size(); i++){
        cout << i << ". " << locations[i] << endl;
    }
    cout << "Enter first location index: ";
    cin >> a;
    cout << "Enter second location index: ";
    cin >> b;
    if (a < 0 || b < 0 || a >= locations.size() ||
        b >= locations.size() || a == b){
        cout << "Invalid location selection!\n";
        return;
    }
    cout << "Enter installation cost: ";
    cin >> cost;
    if (cost < 0) {
        cout << "Cost cannot be negative!\n";
        return;
    }
 
    for (int i = 0; i < u.size(); i++){
        if ((u[i] == a && v[i] == b) ||
            (u[i] == b && v[i] == a)){
            cout << "Connection already exists!\n";
            return;
        }
    }
    u.push_back(a);
    v.push_back(b);
    w.push_back(cost);
    cout << "Connection added successfully!\n";
}


void displayNetwork()
{
    if (locations.empty()){
        cout << "No locations available!\n";
        return;
    }
    cout << "\n===== ELECTRICITY NETWORK =====\n";
    for (int i = 0; i < locations.size(); i++) {
        cout << locations[i] << " -> ";

        bool found = false;

        for (int j = 0; j < u.size(); j++) {
            if (u[j] == i){
                cout << locations[v[j]]
                     << "(" << w[j] << ") ";
                found = true;
            }
            else if (v[j] == i) {
                cout << locations[u[j]]
                     << "(" << w[j] << ") ";
                found = true;
            }
        }
        if (!found)
            cout << "No connections";
        cout << endl;
    }
}

int findParent(vector<int>& parent, int x){
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent, parent[x]);
}

void kruskalsAlgorithm(){
    int n = locations.size();
    int e = u.size();
    if (n == 0) {
        cout << "No locations available!\n";
        return;
    }
    vector<int> a = u;
    vector<int> b = v;
    vector<int> c = w;
    
    for (int i = 0; i < e; i++) {
        for (int j = i + 1; j < e; j++) {
            if (c[i] > c[j]) {
                swap(c[i], c[j]);
                swap(a[i], a[j]);
                swap(b[i], b[j]);  }  } }
    vector<int> parent(n);
    for (int i = 0; i < n; i++){
        parent[i] = i;}
    int totalCost = 0;
    int count = 0;
    cout << "\n===== MINIMUM COST NETWORK =====\n";
    cout << "Selected Connections:\n";
    for (int i = 0; i < e; i++){
        int x = findParent(parent, a[i]);
        int y = findParent(parent, b[i]);
        if (x != y){
            cout << locations[a[i]] << " - "
                 << locations[b[i]]
                 << " | Cost: " << c[i] << endl;
            totalCost += c[i];
            count++;
            parent[x] = y;}
        if (count == n - 1)
            break;}
    if (count != n - 1){
        cout << "\nNetwork is not fully connected!\n";
        cout << "Minimum cost network cannot be completed.\n";
        return; }
    cout << "\nTotal Installation Cost: "
<< totalCost << endl;
}

int main(){
    int choice;
    while (true)
    {
        cout << "\n";
        cout << "===== ELECTRICITY DISTRIBUTION OPTIMIZER =====\n";
        cout << "1. Add Location\n";
        cout << "2. Add Connection\n";
        cout << "3. Display Network\n";
        cout << "4. Find Minimum Cost Network\n";
        cout << "5. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice){
            case 1:
                addLocation();
                break;
            case 2:
                addConnection();
                break;
            case 3:
                displayNetwork();
                break;
            case 4:
                kruskalsAlgorithm();
                break;
            case 5:
                cout << "Thank you for using the system!\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n"; } }
return 0;
}
