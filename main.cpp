#include <curses.h>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "TrajectoryCalculation.h"

namespace {

int RunMenu(const std::string& title, const std::vector<std::string>& options) {
    int selected = 0;
    keypad(stdscr, TRUE);

    while (true) {
        clear();
        mvprintw(1, 2, "%s", title.c_str());
        mvprintw(2, 2, "Use Up/Down and Enter");

        for (int i = 0; i < static_cast<int>(options.size()); ++i) {
            if (i == selected) attron(A_REVERSE);
            mvprintw(4 + i, 4, "%s", options[i].c_str());
            if (i == selected) attroff(A_REVERSE);
        }

        refresh();
        int key = getch();
        if (key == KEY_UP)
            selected = (selected - 1 + static_cast<int>(options.size())) % static_cast<int>(options.size());
        else if (key == KEY_DOWN)
            selected = (selected + 1) % static_cast<int>(options.size());
        else if (key == 10 || key == KEY_ENTER)
            return selected;
    }
}

std::string PromptString(const std::string& label) {
    echo();
    curs_set(1);
    clear();
    mvprintw(1, 2, "%s", label.c_str());
    mvprintw(3, 2, "> ");
    char buffer[256] = {};
    getnstr(buffer, 255);
    noecho();
    curs_set(0);
    return buffer;
}

void ShowMessage(const std::string& message) {
    clear();
    mvprintw(1, 2, "%s", message.c_str());
    refresh();
    getch();
}

double PromptDouble(const std::string& label) {
    while (true) {
        std::string input = PromptString(label);
        try {
            return std::stod(input);
        } catch (...) {
            ShowMessage("Invalid input, try again");
        }
    }
}

void ShowTrajectoryPoints(const ListSequence<Vec<ArraySequence, double>>& traj) {
    int scroll = 0;
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    int visible = rows - 5;
    int total = static_cast<int>(traj.GetLenght());
    keypad(stdscr, TRUE);

    while (true) {
        clear();
        mvprintw(1, 2, "Trajectory points (%d total). Up/Down to scroll, Q to exit", total);
        mvprintw(2, 2, "%-6s %-8s %-8s", "Step", "x (m)", "y (m)");

        for (int i = 0; i < visible && (scroll + i) < total; ++i) {
            int idx = scroll + i;
            const auto& pt = traj.Get(idx);
            mvprintw(3 + i, 2,  "%-6d", idx);
            mvprintw(3 + i, 9, "%-10.3f", pt[0]);
            mvprintw(3 + i, 18, "%-10.3f", pt[1]);
        }

        mvprintw(rows - 1, 2, "Scroll: %d/%d", scroll, total);
        refresh();

        int key = getch();
        if (key == KEY_UP && scroll > 0) scroll--;
        else if (key == KEY_DOWN && scroll + visible < total) scroll++;
        else if (key == 'q' || key == 'Q') break;
    }
}

void RunTrajectoryMenu() {
    while (true) {
        int choice = RunMenu(
            "Trajectory calculation",
            {"Calculate Trajectory", "Exit"}
        );

        if (choice == 1) return;

        double x1     = PromptDouble("Set start x1 (m)");
        double x2     = PromptDouble("Set end   x2 (m)");
        double v0_min = PromptDouble("v min (m/s)");
        double v0_max = PromptDouble("v max (m/s)");
        double v0_step= PromptDouble("v step (m/s)");
        double dt     = PromptDouble("Time step dt (s), like 0.01");

        auto result = solve(x1, x2, v0_min, v0_max, v0_step);

        if (!result.has_value()) {
            ShowMessage("No solution found for this parameters");
            continue;
        }

        std::ostringstream msg;
        msg << std::fixed << std::setprecision(4);
        msg << "Solution found!\n\n";
        msg << "  v0     = " << result->v0    << " m/s\n";
        msg << "  angle  = " << result->angle * 180.0 / PI << " deg\n";
        msg << "  range  = " << result->range << " m\n\n";
        msg << "  Min v0 for x1: " << minV0ForRange(x1) << " m/s\n";
        msg << "  Min v0 for x2: " << minV0ForRange(x2) << " m/s\n\n"; 
        msg << "Press any key to see trajectory!";
        ShowMessage(msg.str());

        auto traj = generateTrajectory(result->v0, result->angle, dt);
        ShowTrajectoryPoints(traj);
    }
}

}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    RunTrajectoryMenu();
    endwin();
    return 0;
}