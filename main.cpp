#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <atomic>
#include <cstdint>
#include <string>
#include <tbb/tbb.h>

uint64_t solve_seq(std::vector<int8_t>& board, int k, int n) {
    if (k == 0) return 1;
    uint64_t count = 0;
    const int len = 2 * n;
    const int max_i = (k == n) ? (n - 2) / 2 : (len - k - 2);

    for (int i = 0; i <= max_i; ++i) {
        const int j = i + k + 1;
        if (board[i] == 0 && board[j] == 0) {
            board[i] = board[j] = static_cast<int8_t>(k);
            count += solve_seq(board, k - 1, n);
            board[i] = board[j] = 0;
        }
    }
    return count;
}

// Параллельное ветвление верхних уровней
void solve_task_group(std::vector<int8_t> board, int k, int n, int cutoff_k,
                      tbb::task_group& tg, std::atomic<uint64_t>& counter) {
    if (k <= cutoff_k) {
        // Достигнут порог: переключаемся на чистый последовательный бэктрекинг по ссылке
        uint64_t local = solve_seq(board, k, n);
        counter.fetch_add(local, std::memory_order_relaxed);
        return;
    }

    const int len = 2 * n;
    const int max_i = (k == n) ? (n - 2) / 2 : (len - k - 2);

    for (int i = 0; i <= max_i; ++i) {
        const int j = i + k + 1;
        if (board[i] == 0 && board[j] == 0) {
            auto next_board = board; // Копируем 24 байта только для нового асинхронного таска
            next_board[i] = next_board[j] = static_cast<int8_t>(k);
            tg.run([next_board, k, n, cutoff_k, &tg, &counter]() {
                solve_task_group(next_board, k - 1, n, cutoff_k, tg, counter);
            });
        }
    }
}

int main(int argc, char* argv[]) {
    int n = 12;
    if (argc > 1) n = std::stoi(argv[1]);
    const unsigned int p = tbb::info::default_concurrency();

    std::cout << "PVA Aufgabe 4: Variante 1 (tbb::task_group mit Cut-Off)\n";
    std::cout << "Ordnung n = " << n << " | Threads = " << p << "\n";

    std::vector<int8_t> board(2 * n, 0);
    std::atomic<uint64_t> counter{0};
    tbb::task_group tg;
    const int cutoff_k = n - 3; // Отсечение на 3 уровне глубины

    auto t1 = std::chrono::high_resolution_clock::now();
    solve_task_group(board, n, n, cutoff_k, tg, counter);
    tg.wait();
    auto t2 = std::chrono::high_resolution_clock::now();

    double t_par = std::chrono::duration<double, std::milli>(t2 - t1).count();
    std::cout << "Loesungen: " << counter.load() << "\n";
    std::cout << "Laufzeit:  " << std::fixed << std::setprecision(2) << t_par << " ms\n";

    return 0;
}
