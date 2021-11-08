#include "ClassHero.h"

int main()
{

    //default settings;
    srand(time(0));
    Player p[10];
    Hero h[10];
    TeamManager a;
    PlayerHero ph[10];
    Session s[5];
    GameManager mngr;
    string bot1, bot2, bot3, bot4, bot5, bot6, bot7, bot8, bot9, bot10;

    int ses = 0;
    bot1 = "BOT Freddie";
    bot2 = "BOT Tom";
    bot3 = "BOT Frank";
    bot4 = "BOT Oliver";
    bot5 = "BOT Harry";
    bot6 = "BOT Jack";
    bot7 = "BOT Jacob";
    bot8 = "BOT Thomas";
    bot9 = "BOT Charlie";
    bot10 = "BOT William";

    p[0].Setname(bot1);
    p[1].Setname(bot2);
    p[2].Setname(bot3);
    p[3].Setname(bot4);
    p[4].Setname(bot5);
    p[5].Setname(bot6);
    p[6].Setname(bot7);
    p[7].Setname(bot8);
    p[8].Setname(bot9);
    p[9].Setname(bot10);

    h[0].CreateHero(75, 100, "Archi-Magician");
    h[1].CreateHero(100, 30, "Warrior");
    h[2].CreateHero(110, 50, "Spearman");
    h[3].CreateHero(70, 15, "Weapon carrier");
    h[4].CreateHero(50, 70, "Sagittarius");
    h[5].CreateHero(50, 80, "Mage");
    h[6].CreateHero(40, 90, "Necromancer");
    h[7].CreateHero(180, 70, "Berserker");
    h[8].CreateHero(120, 90, "Swordsman");
    h[9].CreateHero(80, 30, "Thief");

    for (int i = 0; i < 10; i++) {
        p[i].SetPoints(0);
    }

    //creating players;
start:;
    for (int i = 0; i < 10; i++) {
        int sw;
        cout << "##############################\n" << "Do you wish to add player?\n1.Yes\n2.No\n" << "##############################" << endl;
        cin >> sw;
        switch (sw) {
        case 1:
            p[i].Createplayer();
            break;
        case 2:
            goto aftercreating;
            break;
        default:
            cout << "Invalid number. Skipping..." << endl;
        }
    }
aftercreating:;

    //Starting session;
    int st = mngr.PerformGameSession();
    if (st == 1) cout << "Initialising game session..." << endl;
    else if (st == 2) {
        cout << "Player creation is restarted" << endl;
        goto start;
    }
    else if (st != 2 && st != 1)cout << "Invalid option. Game session will be started anyway" << endl;

sessionbegin:;

    //Randomising player's and hero's ids;
    const int k = 10;
    int m[k];

    for (int i = 0; i < k; i++)
    {
    a: m[i] = 1 + rand() % k;
        for (int j = 0; j < i; j++)
            if (m[j] == m[i]) goto a;
    }
    int v[k];

    for (int i = 0; i < k; i++)
    {
    b: v[i] = 1 + rand() % k;
        for (int j = 0; j < i; j++)
            if (v[j] == v[i]) goto b;
    }
    for (int i = 0; i < 10; i++) {
        p[i].SetIId(m[i]);
    }
    for (int i = 0; i < 10; i++) {
        h[i].SetHeroIId(v[i]);
    }

    //Combining heroes with players using IID;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (p[i].GetIId() == h[j].GetHeroIId()) {
                ph[i].MatchingHeroPlayer(p[i], h[j], p[i].GetIId());
            }
        }
    }

    //Generating Teams;
    for (int i = 0; i < 10; i++) {
        a.GetPlayerHero(ph[i], i);
    }

    a.GenerateTeams();

    //session;
    a.TeamOne();
    a.TeamTwo();
    int win1;
    win1 = a.CalculateWinner();

    //adding and subtracting points;
    if (win1 == 1) {
        for (int i = 0; i < 10; i++) {
            if (p[i].GetIId() == 1)	p[i].RankWin();
            if (p[i].GetIId() == 2)	p[i].RankWin();
            if (p[i].GetIId() == 3)	p[i].RankWin();
            if (p[i].GetIId() == 4)	p[i].RankWin();
            if (p[i].GetIId() == 5)	p[i].RankWin();
            if (p[i].GetIId() == 6)	p[i].RankLose();
            if (p[i].GetIId() == 7)	p[i].RankLose();
            if (p[i].GetIId() == 8)	p[i].RankLose();
            if (p[i].GetIId() == 9)	p[i].RankLose();
            if (p[i].GetIId() == 10)p[i].RankLose();
        }
    }
    else if (win1 == 0) {
        for (int i = 0; i < 10; i++) {
            if (p[i].GetIId() == 10)p[i].RankWin();
            if (p[i].GetIId() == 9)	p[i].RankWin();
            if (p[i].GetIId() == 8)	p[i].RankWin();
            if (p[i].GetIId() == 7)	p[i].RankWin();
            if (p[i].GetIId() == 6)	p[i].RankWin();
            if (p[i].GetIId() == 5)	p[i].RankLose();
            if (p[i].GetIId() == 4)	p[i].RankLose();
            if (p[i].GetIId() == 3)	p[i].RankLose();
            if (p[i].GetIId() == 2)	p[i].RankLose();
            if (p[i].GetIId() == 1)	p[i].RankLose();
        }
    }

    //saving game session;
    s[ses].GetTeamManager(a);
    s[ses].SessionWinner(win1);
    mngr.GetSession(s[ses], ses);
    mngr.GetSessionWin(win1, ses);

    //Performing more sessions;
    if (ses < 4) {
        ses++;
        goto sessionbegin;
    }
    //sessions list;
    mngr.SessionsList();

    //adding ranks;
    for (int i = 0; i < 10; i++) {
        if (p[i].Points() == 1000)
            p[i].SetRank("The global elite");
        if (p[i].Points() == 125)
            p[i].SetRank("Supreme master first class");
        if (p[i].Points() == 100)
            p[i].SetRank("Legendary eagle master");
        if (p[i].Points() == 75)
            p[i].SetRank("Legendary eagle");
        if (p[i].Points() == 50)
            p[i].SetRank("Distinguished master guardian");
        if (p[i].Points() == 25)
            p[i].SetRank("Master Guardian Elite");
        if (p[i].Points() == 0)
            p[i].SetRank("Master Guardian ");
        if (p[i].Points() == -25)
            p[i].SetRank("Gold Nova Master");
        if (p[i].Points() == -50)
            p[i].SetRank("Gold Nova ");
        if (p[i].Points() == -75)
            p[i].SetRank("Silver III");
        if (p[i].Points() == -100)
            p[i].SetRank("Silver II");
        if (p[i].Points() == -125)
            p[i].SetRank("Silver I");
    }
    //results of all 5 games;
    cout << "\n\n\n" << "Final results" << endl;
    for (int i = 0; i < 10; i++) {
        p[i].ShowPlayerInfo();
    }

}