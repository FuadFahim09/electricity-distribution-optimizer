#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> locations;
vector<vector<int>> graph;
vector<int> u, v, w;

void addLocation()
{
    string name;

    cout << "Enter location name: ";
    cin >> name;

    locations.push_back(name);
    graph.push_back({});

    cout << "Location added successfully!\n";
}

void addConnection()
{
    if (locations.size() < 2)
    {
        cout << "Add at least two locations first!\n";
        return;
    }

    int a, b, cost;

    cout << "\nAvailable Locations:\n";

    for (int i = 0; i < locations.size(); i++)
    {
        cout << i << ". " << locations[i] << endl;
    }

    cout << "Enter first location index: ";
    cin >> a;

    cout << "Enter second location index: ";
    cin >> b;

    if (a < 0 || b < 0 || a >= locations.size() ||
        b >= locations.size() || a == b)
    {
        cout << "Invalid location selection!\n";
        return;
    }

    cout << "Enter cable installation cost: ";
    cin >> cost;

    if (cost < 0)
    {
        cout << "Cost cannot be negative!\n";
        return;
    }

    u.push_back(a);
    v.push_back(b);
    w.push_back(cost);

    graph[a].push_back(b);
    graph[b].push_back(a);

    cout << "Connection added successfully!\n";
}

void displayNetwork()
{
    if (locations.empty())
    {
        cout << "No locations available!\n";
        return;
    }

    cout << "\n===== ELECTRICITY NETWORK =====\n";

    for (int i = 0; i < locations.size(); i++)
    {
        cout << locations[i] << " -> ";

        for (int j = 0; j < graph[i].size(); j++)
        {
            int connected = graph[i][j];

            for (int k = 0; k < u.size(); k++)
            {
                if ((u[k] == i && v[k] == connected) ||
                    (v[k] == i && u[k] == connected))
                {
                    cout << locations[connected]
                         << "(" << w[k] << ") ";
                    break;
                }
            }
        }

        cout << endl;
    }
}

void kruskalsAlgorithm()
{
    int n = locations.size();
    int e = u.size();

    if (n == 0)
    {
        cout << "No locations available!\n";
        return;
    }

    vector<int> a = u;
    vector<int> b = v;
    vector<int> c = w;

    for (int i = 0; i < e - 1; i++)
    {
        for (int j = i + 1; j < e; j++)
        {
            if (c[i] > c[j])
            {
                swap(c[i], c[j]);
                swap(a[i], a[j]);
                swap(b[i], b[j]);
            }
        }
    }

    vector<int> parent(n);

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }

    int totalCost = 0;
    int count = 0;

    cout << "\n===== MINIMUM COST NETWORK =====\n";
    cout << "Selected Connections:\n";

    for (int i = 0; i < e; i++)
    {
        int s = a[i];
        int d = b[i];

        while (parent[s] != s)
            s = parent[s];

        while (parent[d] != d)
            d = parent[d];

        if (s != d)
        {
            cout << locations[a[i]] << " - "
                 << locations[b[i]]
                 << " | Cost: " << c[i] << endl;

            totalCost += c[i];
            count++;

            parent[s] = d;
        }

        if (count == n - 1)
            break;
    }

    if (count != n - 1)
    {
        cout << "\nNetwork is not fully connected!\n";
        return;
    }

    cout << "\nTotal Installation Cost: "
         << totalCost << endl;
}

int main()
{
    int choice;

    while (true)
    {
        cout << endl;
        cout << " #####ELECTRICITY DISTRIBUTION OPTIMIZER#####\n";
        cout << endl;

        cout << "1. Add Location\n";
        cout << "2. Add Connection\n";
        cout << "3. Display Network\n";
        cout << "4. Find Minimum Cost Network\n";
        cout << "5. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
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
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
