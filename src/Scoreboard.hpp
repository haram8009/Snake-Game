#pragma once

class Scoreboard{
    WINDOW *score_win;
public:
    Scoreboard()
    {
    }
    Scoreboard(int width, int y, int x)
    {
        score_win = newwin(2, width, y, x); // 윈도우 높이가 2! 늘려야할거임
    }
    void initialize(int initial_growth, int initial_poisoned)
    {
        clear();
        mvwprintw(score_win, 0, 0, "Growth:");
        mvwprintw(score_win, 1, 0, "Poisoned:");
        updateGrowth(initial_growth);
        updatePoisoned(initial_poisoned);
        refresh();
    }
    void updateGrowth(int growth)
    {
        mvwprintw(score_win, 0, score_win->_maxx-10, "%i", growth);
    }
    void updatePoisoned(int poisoned)
    {
        mvwprintw(score_win, 1, score_win->_maxx-10, "%i", poisoned);
    }
    void clear()
    {
        wclear(score_win);
    }
    void refresh()
    {
        wrefresh(score_win);
    }
};
