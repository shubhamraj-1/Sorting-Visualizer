
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int W = 900, H = 600, N = 60, DELAY = 30000;

void draw(sf::RenderWindow &win, vector<int> &a, int x=-1, int y=-1) {
    win.clear(sf::Color::Black);
    int bw = W / a.size();
    for (int i = 0; i < a.size(); i++) {
        sf::RectangleShape bar;
        bar.setSize(sf::Vector2f(bw - 2, a[i]));
        bar.setPosition(i * bw, H - a[i]);
        bar.setFillColor((i == x || i == y) ? sf::Color::Red : sf::Color::White);
        win.draw(bar);
    }
    win.display();
    usleep(DELAY);
}

// Bubble Sort
void bubble(sf::RenderWindow &w, vector<int> &a) {
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size() - i - 1; j++) {
            draw(w, a, j, j + 1);
            if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);
        }
}

// Selection Sort
void selection(sf::RenderWindow &w, vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        int min = i;
        for (int j = i + 1; j < a.size(); j++) {
            draw(w, a, min, j);
            if (a[j] < a[min]) min = j;
        }
        swap(a[i], a[min]);
    }
}

// Insertion Sort
void insertion(sf::RenderWindow &w, vector<int> &a) {
    for (int i = 1; i < a.size(); i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
            draw(w, a, j, j + 1);
        }
        a[j + 1] = key;
    }
}

// Quick Sort
int partition(sf::RenderWindow &w, vector<int> &a, int l, int h) {
    int p = a[h], i = l - 1;
    for (int j = l; j < h; j++) {
        draw(w, a, j, h);
        if (a[j] < p) swap(a[++i], a[j]);
    }
    swap(a[i + 1], a[h]);
    return i + 1;
}

void quick(sf::RenderWindow &w, vector<int> &a, int l, int h) {
    if (l < h) {
        int pi = partition(w, a, l, h);
        quick(w, a, l, pi - 1);
        quick(w, a, pi + 1, h);
    }
}

// Merge Sort
void merge(sf::RenderWindow &w, vector<int> &a, int l, int m, int r) {
    vector<int> t;
    int i = l, j = m + 1;
    while (i <= m && j <= r)
        t.push_back(a[i] < a[j] ? a[i++] : a[j++]);
    while (i <= m) t.push_back(a[i++]);
    while (j <= r) t.push_back(a[j++]);
    for (int k = 0; k < t.size(); k++) {
        a[l + k] = t[k];
        draw(w, a, l + k);
    }
}

void mergeSort(sf::RenderWindow &w, vector<int> &a, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(w, a, l, m);
        mergeSort(w, a, m + 1, r);
        merge(w, a, l, m, r);
    }
}

// Heap Sort
void heapify(sf::RenderWindow &w, vector<int> &a, int n, int i) {
    int l = 2*i+1, r = 2*i+2, mx = i;
    if (l < n && a[l] > a[mx]) mx = l;
    if (r < n && a[r] > a[mx]) mx = r;
    if (mx != i) {
        swap(a[i], a[mx]);
        draw(w, a, i, mx);
        heapify(w, a, n, mx);
    }
}

void heap(sf::RenderWindow &w, vector<int> &a) {
    for (int i = a.size()/2 - 1; i >= 0; i--)
        heapify(w, a, a.size(), i);
    for (int i = a.size()-1; i > 0; i--) {
        swap(a[0], a[i]);
        draw(w, a, 0, i);
        heapify(w, a, i, 0);
    }
}

int main() {
    srand(time(0));
    vector<int> a(N);
    for (int i = 0; i < N; i++)
        a[i] = rand() % (H - 50) + 20;

    cout << "SORTING VISUALIZER (C++ + SFML)\n";
    cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n";
    cout << "4. Quick Sort\n5. Merge Sort\n6. Heap Sort\n";
    cout << "Enter choice: ";

    int ch;
    cin >> ch;

    sf::RenderWindow win(sf::VideoMode(W, H), "Sorting Visualizer");

    bool done = false;
    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e))
            if (e.type == sf::Event::Closed) win.close();

        if (!done) {
            if (ch == 1) bubble(win, a);
            else if (ch == 2) selection(win, a);
            else if (ch == 3) insertion(win, a);
            else if (ch == 4) quick(win, a, 0, a.size()-1);
            else if (ch == 5) mergeSort(win, a, 0, a.size()-1);
            else if (ch == 6) heap(win, a);
            done = true;
        }
        draw(win, a);
    }
    return 0;
}
