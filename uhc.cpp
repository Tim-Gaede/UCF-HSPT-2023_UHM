// HSPT 2023
// Ultra Hardcore Mindset
// Solution by Natalie Longtin

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int main() {
    int num_tasks; cin >> num_tasks;
    vector<ld> probability_of_passing(num_tasks);
    vector<int> time_to_pass(num_tasks);

    for (auto &x : probability_of_passing) cin >> x;
    for (auto &x : time_to_pass) cin >> x;

    // Solution idea:
    // Let our desired answer be represented by the variable ec.
    // Let p_i denote the probability that Steve will pass task i, given that he reaches it.
    // (i.e., the values given in the second line of input).
    // Let t_i denote the time that Steve needs to pass task i, given that he reaches it.
    // (i.e., the values given in the third line of input).

    // Observe that our quantity ec may be expressed in terms of itself, with the following rationale:

    // Assume that Steve fails the first task.
    // The probability that this will happen is equal to (1 - p_1).
    // At this point, Steve has used up t_1 units of time.
    // Steve must also start over from the beginning, which will take an additional ec units of time.
    // Therefore, with 1 - p_1 probability, Steve will spend t_1 + ec units of time to complete all of the missions.

    // Now, assume that Steve fails the second task.
    // The probability that this will happen is equal to p_1 * (1 - p_2)
    // (because Steve must have gotten past the first task in order to fail the second).
    // At this point, Steve has used up t_1 + t_2 units of time.
    // Steve must also start over from the beginning, which will take an additional ec units of time.
    // Therefore, with p_1 * (1 - p_2) probability, Steve will spend t_1 + t_2 + ec units of time to complete all the missions.

    // The remainder of the tasks may be evaluated in a similar manner.
    // Due to linearity of expectation, the following equation may be constructed:

    // ec = (1 - p_1) * (t_1 + ec) + (p_1 * (1 - p_2)) * (t_1 + t_2 + ec) + ... +
    //      (p_1 * p_2 * ... * (1 - p_n)) * (t_1 + t_2 + ... + t_n + ec) +
    //      (p_1 * p_2 * ... * p_n) * (t_1 + t_2 + ... + t_n)

    // Solving this equation for ec yields our desired answer.

    vector<ld> cumulative_vals(num_tasks + 1, 1);
    
    // each successive element of cumulative_vals stores
    // p_1 * p_2 * ... * p_(i-1) * (1 - p_i)
    // except for the last element, which stores p_1 * p_2 * ... * p_n.
    for (int i = 0; i <= num_tasks; i++) {
        for (int j = 0; j < i; j++) {
            cumulative_vals[i] *= probability_of_passing[j];
        }
        if (i < num_tasks) cumulative_vals[i] *= 1 - probability_of_passing[i];
    }

    // The equation we are trying to obtain may be reduced to
    // ec = coeff * ec + constant.
    // By obtaining the values of coeff and constant, we may
    // solve the equation for ec.
    ld constant = 0, coeff = 0;

    // cumulative_time_spent is a cumulative sum of the total time required for tasks 1 to i.
    int cumulative_time_spent = 0;

    for (int i = 0; i <= num_tasks; i++) {
        if (i < num_tasks) cumulative_time_spent += time_to_pass[i];
        constant += cumulative_vals[i] * cumulative_time_spent;
        if (i < num_tasks) coeff += cumulative_vals[i];
    }

    cout << constant / (1 - coeff) << '\n';
    return 0;
}
