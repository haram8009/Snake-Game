#pragma once

class Scoreboard{
    WINDOW *score_win;
public:
    Scoreboard()
    {
    }
    Scoreboard(int width, int y, int x)
    {
        score_win = newwin(12, width, y, x);
    }
    void initialize(int initial_growth, int initial_poisoned, int inital_curlength, int initial_maxlengt, int initial_score)
    {
        clear();

        mvwprintw(score_win, 0, 0, "Press [P] to Pause/Resume");
        mvwprintw(score_win, 2, 0, "[ScoreBoard]");
        mvwprintw(score_win, 3, 0, "Seconds:");
        mvwprintw(score_win, 4, 0, "Growth:");
        mvwprintw(score_win, 5, 0, "Poisoned:");
        mvwprintw(score_win, 6, 0, "Best(current/max):");

        mvwprintw(score_win, 7, 0, "SCORE: ");


        updateGrowth(initial_growth);
        updatePoisoned(initial_poisoned);
        updateBest(inital_curlength, initial_maxlengt);
        updateScore(initial_score);
        //updateGate()
        refresh();
    }

    void updateSeconds(int seconds)
    {
        mvwprintw(score_win, 1, score_win->_maxx-10, "%i", seconds);
    }
    void updateGrowth(int growth)
    {
        mvwprintw(score_win, 2, score_win->_maxx-10, "%i", growth);
    }
    void updatePoisoned(int poisoned)
    {
        mvwprintw(score_win, 3, score_win->_maxx-10, "%i", poisoned);
    }
    void updateBest(int curlength, int maxlengt)
    {
        mvwprintw(score_win, 4, score_win->_maxx-10, "(%i/%i)", curlength, maxlengt);
    }
    void updateScore(int score)
    {
        mvwprintw(score_win, 7, score_win->_maxx-10, "(%i/%i)", score, 50);
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
