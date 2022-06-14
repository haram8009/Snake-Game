#pragma once

class Scoreboard{
    WINDOW *score_win;
public:
    Scoreboard()
    {
    }
    Scoreboard(int width, int y, int x)
    {
        score_win = newwin(4, width, y, x); // 윈도우 높이가 4!
    }
    void initialize(int initial_growth, int initial_poisoned, int inital_curlength, int initial_maxlengt)
    {
        clear();
        mvwprintw(score_win, 0, 0, "Growth:");
        mvwprintw(score_win, 1, 0, "Poisoned:");
        mvwprintw(score_win, 2, 0, "Best(current/max):");
        mvwprintw(score_win, 3, 0, "Gate:");
        updateGrowth(initial_growth);
        updatePoisoned(initial_poisoned);
        updateBest(inital_curlength, initial_maxlengt);
        //updateGate()
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
    void updateBest(int curlength, int maxlengt)
    {
        mvwprintw(score_win, 2, score_win->_maxx-10, "(%i/%i)", curlength, maxlengt);
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
