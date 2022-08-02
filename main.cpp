#include "DxLib.h" 

//const�c�l�̕ς��Ȃ��萔�ɂ���(�萔����啶���ł���)

//DxLib�̃��t�@�����X
//https://dxlib.xsrv.jp/dxfunc.html

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //�E�B���h�E���[�h�ɐݒ� 
    ChangeWindowMode(true);

    //�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A 
    //���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ��� 
    SetWindowSizeChangeEnableFlag(false, false);
    //�E�B���h�E���̐ݒ�
    //SetMainWindowText("Game");

    SetGraphMode(400, 600, 32);

    SetWindowSizeExtendRate(1.0);
    //�w�i�J���[�̐ݒ�  R    G    B
    SetBackgroundColor(255, 255, 255);

    //���ߐF�̐ݒ�
    SetTransColor(255, 255, 255);

    //Dx���C�u������������ 
    if (DxLib_Init() == -1)
    {
        //�G���[���o����}�C�i�X�l��Ԃ��ďI�� 
        return -1;
    }

    //�����g�����p
    int Cr;
    Cr = GetColor(0, 0, 0);

    //x,y�̍��W��������
    int x, y;
    x = 0;
    y = 0;

    //�\��������ʂ��킯��
    enum Scene
    {
        Title,
        Play,
        End,
        GameOver,
        GameEnd
    };

    Scene scene = Title;

    enum Move
    {
        daiichi,
        daini
    };

    bool toujouFlag1;
    toujouFlag1 = false;

    //���@�̗v�f
    int kyara_x, kyara_y;
    int kyara_w, kyara_h;
    kyara_x = x;
    kyara_y = y;
    int kyara, kyaradame;
    bool kyaraflag;
    kyaraflag = true;
    kyara = LoadGraph("pic\\kyara.png", TRUE);
    kyaradame = LoadGraph("pic\\kyaradame.png", TRUE);
    GetGraphSize(kyara, &kyara_w, &kyara_h);

    //�e�̗v�f��錾
    int shot_x[40], shot_y[40], shotGraph, shotWait;
    int shot_w, shot_h;
    bool shotFlag[40];
    shotWait = 0;
    shotGraph = LoadGraph("pic\\tama.png");
    for (int i = 0; i < 40; i++)
    {
        shotFlag[i] = false;
    }
    GetGraphSize(shotGraph, &shot_w, &shot_h);

    //�G�̗v�f
    int teki_x, teki_y;
    teki_x = x;
    teki_y = y;
    teki_x = 10;
    teki_y = 80;
    int teki, tekidame;
    int teki_w, teki_h;
    bool teki_rightflag, tekiflag;
    teki_rightflag = true;
    tekiflag = true;
    teki = LoadGraph("pic\\teki.png", TRUE);
    tekidame = LoadGraph("pic\\tekidame.png", TRUE);
    GetGraphSize(teki, &teki_w, &teki_h);

    //2�̖ڂ̓G
    int tteki_x, tteki_y;
    tteki_x = x;
    tteki_y = y;
    tteki_x = 358;
    tteki_y = 80;
    int tteki, ttekidame;
    int tteki_w, tteki_h;
    bool tteki_rightflag;
    tteki_rightflag = true;
    tteki = LoadGraph("pic\\teki.png", TRUE);
    ttekidame = LoadGraph("pic\\tekidame.png", TRUE);
    GetGraphSize(tteki, &tteki_w, &tteki_h);

    //�G�̒e��錾
    int t_shot_x[40], t_shot_y[40], t_shotGraph, t_shotWait;
    bool t_shotFlag[40];
    int t_shot_w, t_shot_h;
    t_shotWait = 0;
    t_shotGraph = LoadGraph("pic\\tekitama.png");
    for (int i = 0; i < 40; i++)
    {
        t_shotFlag[i] = false;
    }
    GetGraphSize(t_shotGraph, &t_shot_w, &t_shot_h);

    //��̖ڂ̓G�̒e��錾
    int tt_shot_x[40], tt_shot_y[40], tt_shotGraph, tt_shotWait;
    bool tt_shotFlag[40];
    int tt_shot_w, tt_shot_h;
    tt_shotWait = 0;
    tt_shotGraph = LoadGraph("pic\\tekitama.png");
    for (int i = 0; i < 40; i++)
    {
        tt_shotFlag[i] = false;
    }
    GetGraphSize(tt_shotGraph, &tt_shot_w, &tt_shot_h);

    //hp�֌W
    int uewaku, sitawaku, kyarahpgraph, tekihpgraph, nokorihp0;
    uewaku = LoadGraph("pic\\uewaku.png");
    sitawaku = LoadGraph("pic\\sitawaku.png");
    kyarahpgraph = LoadGraph("pic\\kyarahp.png");
    tekihpgraph = LoadGraph("pic\\tekihp.png");
    nokorihp0 = LoadGraph("pic\\nokorihp0.png");

    //��ʕ\���n�̗v�f
    int ue, sita, rogo, haikei, waku, clear, gameover;
    ue = LoadGraph("pic\\ue.png");
    sita = LoadGraph("pic\\sita.png");
    rogo = LoadGraph("pic\\rogo.png");
    haikei = LoadGraph("pic\\haikei.png");
    waku = LoadGraph("pic\\waku.png");
    clear = LoadGraph("pic\\clear.png");
    gameover = LoadGraph("pic\\gameover.png");

    char keys[256];
    char prev[256];

    SetDrawScreen(DX_SCREEN_BACK);

    //���@��HP
    float kyarahp, nowkyarahp, kyarahpwidth, kyarahphaba;
    kyarahp = 10; //�ő�HP
    kyarahpwidth = 400; // �摜�̕��ő�l

    //�G��HP
    float tekihp, nowtekihp, tekihpwidth, tekihphaba;
    tekihp = 100; // �{�X�̍ő�HP
    tekihpwidth = 400; // �摜�̕��ő�l




    while (true)
    {
        // ��ʂɕ`����Ă�����̂����ׂď���
        ClearDrawScreen();

        //�V�[������
        switch (scene)
        {
        case Title:

            DrawGraph(10, 100, rogo, TRUE);
            DrawString(150, 450, "E�L�[�ŃX�^�[�g", Cr);

            if (CheckHitKey(KEY_INPUT_E) == 1)
            {
                scene = Play;
                nowtekihp = 100;
                nowkyarahp = 10;
                kyara_x = 200;
                kyara_y = 460;
                for (int i = 0; i < 40; i++)
                {
                    shotFlag[i] = false;
                    tt_shotFlag[i] = false;
                    t_shotFlag[i] = false;
                }
            }

            break;

        case Play:

            DrawGraph(0, 0, haikei, TRUE);
            DrawGraph(5, 55, waku, TRUE);

            // �㉺���E�̃L�[���͂ɑΉ����� x, y �̍��W�l��ύX����
            if (CheckHitKey(KEY_INPUT_LEFT) == 1)
            {
                kyara_x -= 5;
                if (kyara_x < 8)
                {
                    kyara_x = 8;
                }
            }

            if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
            {
                kyara_x += 5;
                if (kyara_x > 382)
                {
                    kyara_x = 382;
                }
            }

            if (CheckHitKey(KEY_INPUT_UP) == 1)
            {
                kyara_y -= 5;
                if (kyara_y < 7)
                {
                    kyara_y = 7;
                }
            }

            if (CheckHitKey(KEY_INPUT_DOWN) == 1)
            {
                kyara_y += 5;
                if (kyara_y > 518)
                {
                    kyara_y = 518;
                }
            }

            //�L�����`��
            DrawGraph(kyara_x, kyara_y, kyara, TRUE);

            //�X�y�[�X�Œe��������
            if (shotWait == 0)
            {
                if (CheckHitKey(KEY_INPUT_SPACE) == 1)
                {
                    //�g�p�\��Ԃ̒e��T��
                    for (int i = 0; i < 40; i++)
                    {
                        if (shotFlag[i] == false)
                        {
                            shotFlag[i] = true;
                            shot_y[i] = kyara_y + 7;
                            shot_x[i] = kyara_x + 3;

                            //�e�����݂��邱�Ƃɂ���
                            shotWait = 2;
                            break;
                        }
                    }
                    //���݂̃L�����ʒu��`
                }
            }
            else
            {
                shotWait--;
            }
            for (int i = 0; i < 40; i++)
            {
                //�o��������T��
                if (shotFlag[i] == true)
                {
                    DrawGraph(shot_x[i], shot_y[i] - 16, shotGraph, TRUE);
                    shot_y[i] -= 20;

                    //�e����ʊO�ŏ���
                    if (shot_y[i] < -30)
                    {
                        shotFlag[i] = 0;
                    }
                }

            }

            //�G�̈ړ�
            if (teki_rightflag == true)
            {
                teki_x += 3;

                if (teki_x >= 358)
                {
                    teki_rightflag = false;

                }
            }
            else
            {
                teki_x -= 3;
                if (teki_x <= 10)
                {
                    teki_rightflag = true;
                }
            }

            //�G�̒e
            if (t_shotWait == 0)
            {
                for (int i = 0; i < 40; i++)
                {
                    if (t_shotFlag[i] == false)
                    {
                        t_shotFlag[i] = true;
                        t_shot_y[i] = teki_y + 14;
                        t_shot_x[i] = teki_x + 13;

                        //�e�����݂��邱�Ƃɂ���
                        t_shotWait = 8;
                        break;
                    }
                }
            }
            else
            {
                t_shotWait--;
            }
            for (int i = 0; i < 40; i++)
            {
                //�o��������T��
                if (t_shotFlag[i] == true)
                {
                    DrawGraph(t_shot_x[i], t_shot_y[i], t_shotGraph, TRUE);
                    t_shot_y[i] += 4;

                    //�e����ʊO�ŏ���
                    if (t_shot_y[i] > 600)
                    {
                        t_shotFlag[i] = 0;
                    }
                }

            }

            //2�̖�
            if (tteki_rightflag == true)
            {
                tteki_x += 3;

                if (tteki_x >= 358)
                {
                    tteki_rightflag = false;

                }
            }
            else
            {
                tteki_x -= 3;
                if (tteki_x <= 10)
                {
                    tteki_rightflag = true;
                }
            }

            //�G�̒e
            if (tt_shotWait == 0)
            {
                for (int i = 0; i < 40; i++)
                {
                    if (tt_shotFlag[i] == false)
                    {
                        tt_shotFlag[i] = true;
                        tt_shot_y[i] = tteki_y + 14;
                        tt_shot_x[i] = tteki_x + 13;

                        //�e�����݂��邱�Ƃɂ���
                        tt_shotWait = 8;
                        break;
                    }
                }
            }
            else
            {
                tt_shotWait--;
            }
            for (int i = 0; i < 40; i++)
            {
                //�o��������T��
                if (tt_shotFlag[i] == true)
                {
                    DrawGraph(tt_shot_x[i], tt_shot_y[i], tt_shotGraph, TRUE);
                    tt_shot_y[i] += 4;

                    //�e����ʊO�ŏ���
                    if (tt_shot_y[i] > 600)
                    {
                        tt_shotFlag[i] = 0;
                    }
                }
            }

            //�G�z�u
            DrawGraph(teki_x, teki_y, teki, TRUE);
            DrawGraph(tteki_x, tteki_y, tteki, TRUE);

            tekihphaba = nowtekihp / tekihp * tekihpwidth;
            kyarahphaba = nowkyarahp / kyarahp * kyarahpwidth;

            //�g�̊O�̒e���B�����߂�
            DrawGraph(0, 0, ue, TRUE);
            DrawGraph(5, 537, sita, TRUE);

            //HP�֌W�̕\��
            DrawGraph(1, 20, nokorihp0, TRUE);
            DrawGraph(1, 550, nokorihp0, TRUE);
            DrawGraph(3, 20, kyarahp, TRUE);
            DrawExtendGraph(1, 20, 1 + tekihphaba, 20 + 30, tekihpgraph, TRUE);
            DrawExtendGraph(1, 550, 1 + kyarahphaba, 550 + 30, kyarahpgraph, TRUE);
            DrawGraph(1, 20, uewaku, TRUE);
            DrawGraph(1, 550, sitawaku, TRUE);

            //�����蔻��
            for (int i = 0; i < 40; i++)
            {
                if (shotFlag[i] == true)
                {
                    if (((shot_x[i] > teki_x && shot_x[i] < teki_x + teki_w) ||
                        (teki_x > shot_x[i] && teki_x < shot_x[i] + shot_w)) &&
                        ((shot_y[i] > teki_y && shot_y[i] < teki_y + teki_h) ||
                            (teki_y > shot_y[i] && teki_y < shot_y[i] + shot_h)))
                    {
                        shotFlag[i] = false;
                        nowtekihp--;
                        DrawGraph(teki_x, teki_y, tekidame, TRUE);
                    }
                }
            }

            for (int i = 0; i < 40; i++)
            {
                if (t_shotFlag[i] == true)
                {
                    if (((t_shot_x[i] > kyara_x + 2 && t_shot_x[i] < kyara_x + kyara_w - 2) ||
                        (kyara_x + 2 > t_shot_x[i] && kyara_x + 8 < t_shot_x[i] + t_shot_w)) &&
                        ((t_shot_y[i] > kyara_y + 7 && t_shot_y[i] < kyara_y + kyara_h - 6) ||
                            (kyara_y + 8 > t_shot_y[i] && kyara_y + 15 < t_shot_y[i] + t_shot_h)))
                    {
                        t_shotFlag[i] = false;
                        nowkyarahp--;
                        DrawGraph(kyara_x, kyara_y, kyaradame, TRUE);
                    }
                }
            }

            for (int i = 0; i < 40; i++)
            {
                if (shotFlag[i] == true)
                {
                    if (((shot_x[i] > tteki_x && shot_x[i] < tteki_x + tteki_w) ||
                        (tteki_x > shot_x[i] && tteki_x < shot_x[i] + shot_w)) &&
                        ((shot_y[i] > tteki_y && shot_y[i] < tteki_y + tteki_h) ||
                            (tteki_y > shot_y[i] && tteki_y < shot_y[i] + shot_h)))
                    {
                        shotFlag[i] = false;
                        nowtekihp--;
                        DrawGraph(tteki_x, tteki_y, ttekidame, TRUE);
                    }
                }
            }

            for (int i = 0; i < 40; i++)
            {
                if (tt_shotFlag[i] == true)
                {
                    if (((tt_shot_x[i] > kyara_x + 2 && tt_shot_x[i] < kyara_x + kyara_w - 2) ||
                        (kyara_x + 2 > tt_shot_x[i] && kyara_x + 8 < tt_shot_x[i] + tt_shot_w)) &&
                        ((tt_shot_y[i] > kyara_y + 7 && tt_shot_y[i] < kyara_y + kyara_h - 6) ||
                            (kyara_y + 8 > tt_shot_y[i] && kyara_y + 15 < tt_shot_y[i] + tt_shot_h)))
                    {
                        tt_shotFlag[i] = false;
                        nowkyarahp--;
                        DrawGraph(kyara_x, kyara_y, kyaradame, TRUE);
                    }
                }
            }
         
            //���������̉�ʂɈڍs
            if (nowkyarahp <= 0)
            {
                scene = GameOver;
            }

            //�|�������̉�ʂɈڍs
            if (nowtekihp <= 0)
            {
                scene = End;
            }

            break;

            //�N���A�����
        case End:

            DrawGraph(0, 200, clear, TRUE);
            DrawString(150, 400, "C�L�[�Ŏn�߂���", Cr);
            DrawString(150, 460, "V�L�[�Ń^�C�g��", Cr);

            if (CheckHitKey(KEY_INPUT_C) == 1)
            {
                scene = Play;
                nowtekihp = 100;
                nowkyarahp = 10;
                kyara_x = 200;
                kyara_y = 400;
                for (int i = 0; i < 40; i++)
                {
                    shotFlag[i] = false;
                    tt_shotFlag[i] = false;
                    t_shotFlag[i] = false;
                }
            }
            if (CheckHitKey(KEY_INPUT_V) == 1)
            {
                scene = Title;
            }



            break;

            //�s�k�����
        case GameOver:
            DrawGraph(10, 180, gameover, TRUE);
            DrawString(150, 400, "C�L�[�ŃR���e�B�j���[", Cr);
            DrawString(150, 460, "V�L�[�Ń^�C�g��", Cr);

            if (CheckHitKey(KEY_INPUT_C) == 1)
            {
                scene = Play;
                nowtekihp = 100;
                nowkyarahp = 10;
                kyara_x = 200;
                kyara_y = 400;
                for (int i = 0; i < 40; i++)
                {
                    shotFlag[i] = false;
                    tt_shotFlag[i] = false;
                    t_shotFlag[i] = false;
                }
            }
            if (CheckHitKey(KEY_INPUT_V) == 1)
            {
                scene = Title;
            }

            nowtekihp = 100;
            nowkyarahp = 10;
            kyara_x = 200;
            kyara_y = 400;
            for (int i = 0; i < 40; i++)
            {
                shotFlag[i] = false;
                tt_shotFlag[i] = false;
                t_shotFlag[i] = false;
            }
            break;
        }

        ScreenFlip();

        //���̏�܂łɃ��W�b�N������
        WaitTimer(20);//�~���b(20ms�҂��Ă��珈�����s��) 
        if (ProcessMessage() == -1) break; //WindowsAPI�̃G���[���������Ɋ��m����While�𔲂���
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
    }

    //Dx���C�u�����I������ 
    DxLib_End();

    return 0;
}