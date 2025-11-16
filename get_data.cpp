#define _USE_MATH_DEFINES
#include "bits/stdc++.h"
using namespace std;

#define pii pair<long long, long long>

random_device rd;
mt19937 gen(rd());

struct Circle {
    long double x, y, r;
};

struct Rectangle {
    long double x_min, x_max, y_min, y_max;

    long double get_s() {
        return (x_max - x_min) * (y_max - y_min);
    }
};

bool is_point_in_circle(long double x, long double y, const Circle& c) {
    return (x - c.x) * (x - c.x) + (y - c.y) * (y - c.y) <= c.r * c.r;
}

template<typename T>
long double monte_carlo_area(Circle* circles, Rectangle& rect, T& dis_x, T& dis_y, int N) {
    long double ans = 0.0;
    int n = 0;
    int m = 0;
    for (int i = 0; i < N; i++) {
        long double rnd_x = dis_x(gen), rnd_y = dis_y(gen);
        bool ok = true;
        for (int j = 0; j < 3; j++) {
            if (!is_point_in_circle(rnd_x, rnd_y, circles[j])) {
                ok = false;
                break;
            }
        }
        n++;
        if (ok) m++;
        ans = rect.get_s() * m / n;
    }
    return ans;
}

void solve() {
    Circle circles[3] = {
        {1.0, 1.0, 1.0},
        {1.5, 2, sqrt(5) / 2.0},
        {2.0, 1.5, sqrt(5) / 2.0}
    };
    Rectangle wide_rect, narrow_rect;
    wide_rect.x_min = wide_rect.y_min = 1e9;
    wide_rect.x_max = wide_rect.y_max = -1e9;
    narrow_rect.x_min = narrow_rect.y_min = -1e9;
    narrow_rect.x_max = narrow_rect.y_max = 1e9;

    for (const auto& c : circles) {
        wide_rect.x_min = std::min(wide_rect.x_min, c.x - c.r);
        wide_rect.x_max = std::max(wide_rect.x_max, c.x + c.r);
        wide_rect.y_min = std::min(wide_rect.y_min, c.y - c.r);
        wide_rect.y_max = std::max(wide_rect.y_max, c.y + c.r);
        
        narrow_rect.x_min = std::max(narrow_rect.x_min, c.x - c.r);
        narrow_rect.x_max = std::min(narrow_rect.x_max, c.x + c.r);
        narrow_rect.y_min = std::max(narrow_rect.y_min, c.y - c.r);
        narrow_rect.y_max = std::min(narrow_rect.y_max, c.y + c.r);
    }
    // cout << wide_rect.x_min << " " << wide_rect.x_max << " " << wide_rect.y_min << " " << wide_rect.y_max << '\n'; 
    // cout << narrow_rect.x_min << " " << narrow_rect.x_max << " " << narrow_rect.y_min << " " << narrow_rect.y_max << '\n'; 
    uniform_real_distribution dis1_x(wide_rect.x_min, wide_rect.x_max);
    uniform_real_distribution dis1_y(wide_rect.y_min, wide_rect.y_max);
    uniform_real_distribution dis2_x(narrow_rect.x_min, narrow_rect.x_max);
    uniform_real_distribution dis2_y(narrow_rect.y_min, narrow_rect.y_max);

    std::ofstream data_file("data.csv");
    data_file << "N,Wide_Area,Narrow_Area,Wide_Error,Narrow_Error\n";

    long double exact_area = 0.25 * M_PI + 1.25 * asin(0.8) - 1.0;
    for (int i = 100; i < 100000; i += 500) {
        long double wide_area = monte_carlo_area(circles, wide_rect, dis1_x, dis1_y, i);
        long double narrow_area = monte_carlo_area(circles, narrow_rect, dis2_x, dis2_y, i);
        
        long double wide_error = std::abs(wide_area - exact_area) / exact_area * 100;
        long double narrow_error = std::abs(narrow_area - exact_area) / exact_area * 100;

        data_file << i << "," << wide_area << "," << narrow_area << ","
                  << wide_error << "," << narrow_error << "\n";
    }
    data_file.close();
    // cout << exact_area << '\n';
}

int32_t main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}
