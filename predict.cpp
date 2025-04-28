#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class HoltPredictor {
public:
    HoltPredictor(double alpha, double beta)
      : alpha(alpha), beta(beta), initialized(false), S(0), B(0)
    {}

    // Feed in a new observation x_t.
    // Returns the one-step-ahead forecast for x_t.
    double addObservation(double x_t) {
        if (!initialized) {
            buffer.push_back(x_t);
            if (buffer.size() == 2) {
                // Initialize level & trend
                S = buffer[0];
                B = buffer[1] - buffer[0];
                initialized = true;
            }
            // No meaningful forecast yet—just echo the observation
            return x_t;
        }

        // Forecast for current time = S_prev + B_prev
        double forecast = S + B;

        // Update equations
        double S_new = alpha * x_t + (1.0 - alpha) * (S + B);
        double B_new = beta  * (S_new - S) + (1.0 - beta) * B;
        S = S_new;
        B = B_new;

        return forecast;
    }

    // Forecast m steps ahead
    double forecastAhead(int m = 1) const {
        if (!initialized) return 0.0;
        return S + m * B;
    }

private:
    double alpha, beta;
    bool initialized;
    double S, B;
    vector<double> buffer;
};

int main(){
    // Smoothing parameters (tune as needed)
    HoltPredictor predictor(0.5, 0.3);

    // Observed traffic counts (cars per minute)
    vector<double> data = {
        12, 15, 14, 17, 16, 18, 20, 19, 21, 23,
        25, 27, 30, 28, 26, 24, 22, 20, 19, 18
    };

    cout << left
         << setw(6) << "Time"
         << setw(8) << "Obs"
         << setw(10) << "Forecast"
         << "\n"
         << "----------------------\n";

    for (int t = 0; t < (int)data.size(); ++t) {
        double obs  = data[t];
        double pred = predictor.addObservation(obs);
        cout << setw(6) << t
             << setw(8) << obs
             << setw(10) << fixed << setprecision(2) << pred
             << "\n";
    }

    cout << "\n5-step ahead forecasts:\n";
    for (int m = 1; m <= 5; ++m) {
        cout << "  +" << m << ": " << predictor.forecastAhead(m) << "\n";
    }

    return 0;
}
